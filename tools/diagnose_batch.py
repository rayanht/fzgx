#!/usr/bin/env python3
"""Compare completed near misses with retail, preserving the running batch's work copies."""
import argparse
import hashlib
import json
import shutil
from collections import Counter, defaultdict
from pathlib import Path

from fzgx import oracle, stuck
from fzgx.ledger import Ledger
from fzgx.project import ROOT, STATE_DIR, Project


def diagnose(batch, seeds, output, minimum):
    ledger = Ledger()
    attempts = [dict(r) for r in ledger.db.execute(
        "SELECT a.*,f.size,f.module FROM attempts a JOIN functions f ON f.symbol=a.symbol "
        "WHERE a.agent LIKE ? AND a.ended IS NOT NULL AND a.best_in_attempt>=? "
        "AND a.outcome='released' AND f.status='unmatched' ORDER BY a.id", (batch + '%', minimum))]
    seed_records = json.loads(seeds.read_text())
    output.mkdir(parents=True, exist_ok=False)
    records = {}
    # The running batch may re-split retail objects on submit. Freeze those inputs
    # under the build lock, then do the actual analysis in private directories.
    with oracle.build_lock():
        project = Project()
        for attempt in attempts:
            symbol = attempt['symbol']
            sym = project.resolve(symbol)
            body = Path(attempt['best_body_path']).read_text()
            sha = hashlib.sha256(body.encode()).hexdigest()
            directory = output / symbol.replace(':', '__')
            directory.mkdir()
            source, target = directory / 'candidate.c', directory / 'target.o'
            source.write_text(body)
            shutil.copyfile(project.target_object_for(sym), target)
            record = seed_records[symbol]
            index = STATE_DIR / 'checks' / symbol.replace(':', '__') / 'index.jsonl'
            if index.exists():
                for line in index.read_text().splitlines():
                    checked = json.loads(line)
                    path = index.parent / f'{checked["n"]:03d}.c'
                    if (attempt['started'] <= checked['t'] <= attempt['ended'] and path.exists()
                            and hashlib.sha256(path.read_bytes()).hexdigest() == sha):
                        record = checked
            records[symbol] = dict(attempt=attempt, source=str(source), target=str(target), sha256=sha,
                                   mw=record.get('mw'), flags=record.get('flags'))
    (output / 'inputs.json').write_text(json.dumps(records, indent=2) + '\n')
    variants = [('baseline', None, None)]
    variants += [(version, version, None) for version in ('GC/1.2.5n', 'GC/1.3', 'GC/1.3.2')]
    variants += [(flag, None, flag) for flag in
                 ('-schedule off', '-opt nolifetimes', '-opt nodeadstore', '-inline deferred', '-inline off')]
    results = defaultdict(dict)
    for vi, (label, version, extra) in enumerate(variants):
        groups = defaultdict(list)
        for symbol, record in records.items():
            source = output / 'sources' / (symbol.replace(':', '__') + '.c')
            source.parent.mkdir(exist_ok=True)
            if not source.exists():
                shutil.copyfile(record['source'], source)
            flags = ' '.join(x for x in (record['flags'], extra) if x) or None
            groups[(record['attempt']['module'], version or record['mw'], flags)].append((symbol, source))
        for gi, ((module, mw, flags), items) in enumerate(groups.items()):
            objects = oracle.compile_many(project, module, [src for _, src in items], output / 'objects' / f'{vi}-{gi}', mw, flags)
            for symbol, source in items:
                obj = objects.get(source)
                if obj is None:
                    results[symbol][label] = dict(ok=False)
                    continue
                target = Path(records[symbol]['target'])
                name = project.resolve(symbol).name
                res = oracle._diff(project, module, name, '', 1000, target=target, base=obj)
                row = stuck.analyse(project, symbol, str(source), res)
                tw, ow = oracle.words(target, name), oracle.words(obj, name)
                row.update(mw=mw, flags=flags, matched=res.matched or res.matched_pool,
                           word_percent=oracle.word_score(tw, ow)[0] if tw and ow else 0,
                           pool=res.pool, object=str(obj))
                results[symbol][label] = row
        print(f'{label}: {sum(r[label].get("matched", False) for r in results.values())} exact matches', flush=True)
    (output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
    save_matches(output)
    print(json.dumps(dict(functions=len(records), bytes=sum(r['attempt']['size'] for r in records.values()),
                         modes=Counter(r['baseline'].get('pure', 'compile-failed') for r in results.values()),
                         output=str(output))))


def save_matches(output):
    """Feed exact compiler repairs back through the ordinary import preflight."""
    inputs = json.loads((output / 'inputs.json').read_text())
    results = json.loads((output / 'results.json').read_text())
    manifest = {}
    for symbol, variants in results.items():
        match = next((r for r in variants.values() if r.get('matched')), None)
        if match:
            source = inputs[symbol]
            manifest[symbol] = dict(path=source['source'], sha256=source['sha256'],
                                    mw=match['mw'], flags=match['flags'], percent=100, kind='compiler-repair')
    (output / 'matches.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'{len(manifest)} saved exact candidates: {output / "matches.json"}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--batch')
    parser.add_argument('--seeds', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--min-percent', type=float, default=97)
    parser.add_argument('--saved', action='store_true', help='export exact candidates from saved results without recompiling')
    args = parser.parse_args()
    if args.saved:
        save_matches(args.output.resolve())
    elif args.batch and args.seeds:
        diagnose(args.batch, args.seeds, args.output.resolve(), args.min_percent)
    else:
        parser.error('--batch and --seeds are required unless --saved')
