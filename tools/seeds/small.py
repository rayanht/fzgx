#!/usr/bin/env python3
"""Freeze all small unmatched functions, retaining saved C before lifting gaps."""
from __future__ import annotations

import argparse
import json
import shlex
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from fzgx import lift, oracle
from recovered import SavedCandidates, digest


def prepare(output, max_size):
    if (output / 'manifest.json').exists():
        raise ValueError(f'{output}: frozen manifest already exists')
    output.mkdir(parents=True, exist_ok=True)
    saved = SavedCandidates(-1)
    saved.rows = {name: row for name, row in saved.rows.items() if row['size'] <= max_size}
    stale = [name for name in saved.rows if (sym := saved.project.resolve(name)) is None or sym.kind != 'function']
    saved.rows = {name: row for name, row in saved.rows.items() if name not in stale}
    saved.collect()
    manifest, errors = {}, {}
    with oracle.build_lock():
        for name, row in sorted(saved.rows.items(), key=lambda item: (item[1]['size'], item[0])):
            candidates = saved.candidates[name]
            # A score belongs to both the C and its compiler settings. Prefer
            # archived settings for identical older bodies before choosing C.
            settings = {r['sha256']: r for r in candidates if r['settings_recorded']}
            for candidate in candidates:
                if not candidate['settings_recorded'] and candidate['sha256'] in settings:
                    candidate.update({k: settings[candidate['sha256']][k]
                                      for k in ('mw', 'flags', 'settings_recorded')})
            if candidates:
                best = max(candidates, key=lambda r: (r['percent'], r['settings_recorded'],
                                                      r['origin'].startswith('.fzgx/checks/')))
                body = best['body']
                seed = {k: v for k, v in best.items() if k != 'body'}
                seed['kind'] = 'recovered'
                if isinstance(seed.get('flags'), list):
                    seed['flags'] = shlex.join(seed['flags'])
            else:
                sym = saved.project.resolve(name)
                body = lift.lift_total(saved.project, row['module'], sym.name)
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
    (output / 'selection.json').write_text(json.dumps(dict(max_size=max_size, rows=saved.rows,
                                                         stale=stale, errors=errors), indent=2) + '\n')
    if errors:
        raise ValueError(f'{len(errors)} functions lack a seed; see selection.json')
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    summary = dict(functions=len(manifest), bytes=sum(r['size'] for r in manifest.values()),
                   max_size=max_size, kinds=dict(Counter(r['kind'] for r in manifest.values())),
                   excluded_stale=stale,
                   manifest=str(output / 'manifest.json'))
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--max-size', type=int, default=1023)
    args = parser.parse_args()
    if args.max_size < 1:
        parser.error('--max-size must be positive')
    print(json.dumps(prepare(args.output.resolve(), args.max_size)))
