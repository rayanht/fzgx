#!/usr/bin/env python3
"""Freeze unmatched seeds; optionally compare fresh full-size lifts with the best saved C."""
from __future__ import annotations

import argparse
import json
import multiprocessing
import time
from concurrent.futures import ProcessPoolExecutor
import shlex
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from fzgx import fixup, lift, oracle, signatures
from recovered import SavedCandidates, digest


_PROJECT = None


def lift_one(item):
    name, row = item
    sym = _PROJECT.resolve(name)
    return name, lift.lift_total(_PROJECT, row['module'], sym.name,
                                 max_ins=max(1200, (sym.size + 3) // 4))


def prepare(output, max_size, fresh_lift=False):
    if (output / 'manifest.json').exists():
        raise ValueError(f'{output}: frozen manifest already exists')
    output.mkdir(parents=True, exist_ok=True)
    started = time.monotonic()
    saved = SavedCandidates(-1)
    saved.rows = {name: row for name, row in saved.rows.items() if not max_size or row['size'] <= max_size}
    stale = [name for name in saved.rows if (sym := saved.project.resolve(name)) is None or sym.kind != 'function']
    saved.rows = {name: row for name, row in saved.rows.items() if name not in stale}
    saved.collect()
    manifest, errors = {}, {}
    engine = fixup.Engine(saved.project, output / "comparison", verbose=True) if fresh_lift else None
    comparisons = []
    with oracle.build_lock(), signatures.frozen(saved.project):
        global _PROJECT
        _PROJECT = saved.project
        fresh = {}
        if fresh_lift:
            pending = [(name, row) for name, row in saved.rows.items()
                       if not (output / 'lifts' / (name.replace(':', '__') + '.c')).exists()]
            for module in {row['module'] for _, row in pending}:
                saved.project.function_asm(module)
            (output / 'lifts').mkdir(exist_ok=True)
            print(f'lifting {len(pending)} functions with 12 processes', flush=True)
            # Fork the warmed read-only project; each worker owns mutable lifter globals.
            with ProcessPoolExecutor(max_workers=12, mp_context=multiprocessing.get_context('fork')) as pool:
                for name, body in pool.map(lift_one, pending, chunksize=8):
                    fresh[name] = body
                    if body is not None:
                        (output / 'lifts' / (name.replace(':', '__') + '.c')).write_text(body)
            print(f'lifts ready after {time.monotonic() - started:.2f}s', flush=True)
        for name, row in sorted(saved.rows.items(), key=lambda item: (item[1]['size'], item[0])):
            candidates = saved.candidates[name]
            # A score belongs to both the C and its compiler settings. Prefer
            # archived settings for identical older bodies before choosing C.
            settings = {r['sha256']: r for r in candidates if r['settings_recorded']}
            for candidate in candidates:
                if not candidate['settings_recorded'] and candidate['sha256'] in settings:
                    candidate.update({k: settings[candidate['sha256']][k]
                                      for k in ('mw', 'flags', 'settings_recorded')})
            if fresh_lift:
                sym = saved.project.resolve(name)
                lift_path = output / 'lifts' / (name.replace(':', '__') + '.c')
                lift_path.parent.mkdir(exist_ok=True)
                body = lift_path.read_text() if lift_path.exists() else fresh.get(name)
                if body is None:
                    errors[name] = 'lifter did not produce C'
                    continue
                lift_path.write_text(body)
                lifted = engine.record(name, body, kind='lift_total', origin='lift_total',
                                       historical_percent=0, unresolved=body.count('???'))
                comparisons.append(lifted)
                if candidates:
                    candidate = max(candidates, key=lambda r: (r['percent'], r['settings_recorded'],
                                                               r['origin'].startswith('.fzgx/checks/')))
                    flags = candidate.get('flags')
                    if isinstance(flags, list):
                        flags = shlex.join(flags)
                    comparisons.append(engine.record(name, candidate['body'], candidate.get('mw'), flags,
                        kind='recovered', origin=candidate['origin'], historical_percent=candidate['percent']))
                seed = dict(kind='lift_total', origin='lift_total', lift_path=str(lift_path))
            elif candidates:
                best = max(candidates, key=lambda r: (r['percent'], r['settings_recorded'],
                                                      r['origin'].startswith('.fzgx/checks/')))
                body = best['body']
                seed = {k: v for k, v in best.items() if k != 'body'}
                seed['kind'] = 'recovered'
                if isinstance(seed.get('flags'), list):
                    seed['flags'] = shlex.join(seed['flags'])
            else:
                sym = saved.project.resolve(name)
                body = lift.lift_total(saved.project, row['module'], sym.name,
                                       max_ins=max(1200, (sym.size + 3) // 4))
                if body is None:
                    errors[name] = 'lifter did not produce C'
                    continue
                seed = dict(kind='lift_total', unresolved=body.count('???'), origin='lift_total')
            path = output / (name.replace(':', '__') + '.c')
            path.write_text(body)
            manifest[name] = {**seed, 'path': str(path), 'sha256': digest(body),
                              'module': row['module'], 'size': row['size']}
            if len(manifest) % 100 == 0:
                print(f'prepared {len(manifest)}/{len(saved.rows)}', flush=True)
        if fresh_lift:
            print(f'comparing {len(comparisons)} saved/lift candidates for {len(manifest)} functions', flush=True)
            engine.evaluate(comparisons)
            best = {}
            for candidate in comparisons:
                name = candidate['symbol']
                rank = (candidate.get('matched', False), candidate['score'], -candidate['bit_errors'],
                        candidate['historical_percent'])
                if name not in best or rank > best[name][0]:
                    best[name] = rank, candidate
            for name, (_, candidate) in best.items():
                body = Path(candidate['source']).read_text()
                Path(manifest[name]['path']).write_text(body)
                manifest[name].update({k: candidate[k] for k in ('kind', 'origin', 'mw', 'flags', 'sha256')})
                manifest[name].update(current_word_percent=candidate['score'], unresolved=body.count('???'))
            (output / 'comparison.json').write_text(json.dumps(comparisons, indent=2) + '\n')
    (output / 'selection.json').write_text(json.dumps(dict(max_size=max_size, rows=saved.rows,
                                                         stale=stale, errors=errors), indent=2) + '\n')
    if errors:
        raise ValueError(f'{len(errors)} functions lack a seed; see selection.json')
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    summary = dict(functions=len(manifest), bytes=sum(r['size'] for r in manifest.values()),
                   elapsed_seconds=round(time.monotonic() - started, 3),
                   max_size=max_size, kinds=dict(Counter(r['kind'] for r in manifest.values())),
                   excluded_stale=stale,
                   manifest=str(output / 'manifest.json'))
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--max-size', type=int, default=1023, help='0 selects every unmatched function')
    parser.add_argument('--fresh-lift', action='store_true', help='lift every function and compare the best saved C using the unified engine')
    args = parser.parse_args()
    if args.max_size < 0:
        parser.error('--max-size must be nonnegative')
    print(json.dumps(prepare(args.output.resolve(), args.max_size, args.fresh_lift)))
