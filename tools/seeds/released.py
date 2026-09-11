#!/usr/bin/env python3
"""Freeze still-unmatched releases from one batch, with their saved C and compiler settings."""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from fzgx.ledger import Ledger
from fzgx.project import STATE_DIR, Project


def prepare(batch: str, output: Path, seeds: Path | None = None, resume: bool = False):
    if (output / 'manifest.json').exists():
        raise ValueError(f'{output}: frozen manifest already exists; use a new directory')
    ledger, project = Ledger(), Project()
    original = json.loads(seeds.read_text()) if seeds else {}
    if resume and not seeds:
        raise ValueError('--resume requires the original --seeds manifest')
    results = STATE_DIR / 'runs' / batch / 'results.jsonl'
    completed = {r['symbol'] for line in results.read_text().splitlines()
                 if (r := json.loads(line))['outcome'] in ('matched', 'released') and not r.get('error')} if resume and results.exists() else set()
    # Old harnesses could reopen a function with suffixed worker identities.
    # Use its final attempt, not any earlier release followed by a successful retry.
    pattern = re.compile(re.escape(batch) + r'-(?:codex|claude)-\d+(?:-.*)?$')
    attempts = {}
    for row in ledger.db.execute('SELECT * FROM attempts ORDER BY id'):
        if pattern.fullmatch(row['agent'] or ''):
            attempts[row['symbol']] = dict(row)
    if not attempts and not resume:
        raise ValueError(f'{batch}: no worker attempts found')
    if active := [s for s, r in attempts.items() if r['ended'] is None]:
        raise ValueError(f'{batch}: stop and release active attempts first: {active}')
    manifest, bodies, skipped = {}, {}, {}
    for symbol, attempt in attempts.items():
        if symbol in completed:
            skipped[symbol] = dict(reason='completed before interruption')
            continue
        status = ledger.get(symbol)['status']
        if attempt['outcome'] != 'released' or status != 'unmatched':
            skipped[symbol] = dict(outcome=attempt['outcome'], status=status)
            continue
        if not attempt['best_body_path']:
            raise ValueError(f'{symbol}: released attempt has no saved C')
        source = Path(attempt['best_body_path'])
        body = source.read_bytes()
        sha = hashlib.sha256(body).hexdigest()
        metadata = source.with_suffix('.json')
        if metadata.exists():
            record = json.loads(metadata.read_text())
            if record['sha256'] != sha:
                raise ValueError(f'{source}: saved C hash changed')
            compiler_origin = str(metadata)
        else:
            # Older releases omitted metadata; recover settings from a real
            # compile of the identical body, never from another candidate's score.
            index = STATE_DIR / 'checks' / symbol.replace(':', '__') / 'index.jsonl'
            records = []
            for line in index.read_text().splitlines() if index.exists() else []:
                item = json.loads(line)
                checked = index.parent / f"{item['n']:03d}.c"
                if ('mw' in item and 'flags' in item and checked.exists()
                        and checked.read_bytes() == body):
                    score = item.get('adjusted') if item.get('rows') else item.get('percent')
                    records.append({**item, 'percent': score or 0})
            if records:
                record = max(records, key=lambda r: (r['t'] >= attempt['started'], r['percent'],
                                                    bool(r.get('matched')), r['t']))
                compiler_origin = f"{index}:{record['n']}"
            elif original.get(symbol, {}).get('sha256') == sha:
                record = original[symbol]
                compiler_origin = f'{seeds}:{symbol}'
            else:
                raise ValueError(f'{symbol}: saved C has no recorded compiler settings')
        if 'mw' not in record or 'flags' not in record:
            raise ValueError(f'{symbol}: incomplete compiler metadata in {compiler_origin}')
        sym = project.resolve(symbol)
        if sym is None:
            raise ValueError(f'{symbol}: no current retail symbol')
        path = output / (symbol.replace(':', '__') + '.c')
        manifest[symbol] = dict(path=str(path), sha256=sha, kind='recovered',
                                module=sym.module, size=sym.size, mw=record['mw'], flags=record['flags'],
                                percent=record.get('percent', attempt['best_in_attempt']),
                                origin=f"ledger:attempt/{attempt['id']}", original_path=str(source),
                                compiler_origin=compiler_origin, previous_notes=attempt['notes'])
        bodies[symbol] = body
    if resume:
        for symbol, record in original.items():
            if symbol in attempts or symbol in completed or ledger.get(symbol)['status'] != 'unmatched':
                continue
            body = Path(record['path']).read_bytes()
            if hashlib.sha256(body).hexdigest() != record['sha256']:
                raise ValueError(f'{symbol}: original seed changed')
            manifest[symbol] = {**record, 'path': str(output / (symbol.replace(':', '__') + '.c'))}
            bodies[symbol] = body
    output.mkdir(parents=True, exist_ok=True)
    for symbol, body in bodies.items():
        Path(manifest[symbol]['path']).write_bytes(body)
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    summary = dict(source_batch=batch, resume=resume, functions=len(manifest), bytes=sum(r['size'] for r in manifest.values()),
                   size_cap=None, score_cutoff=None, prior_outcomes=dict(Counter(r['outcome'] for r in attempts.values())),
                   skipped=skipped, manifest=str(output / 'manifest.json'))
    (output / 'selection.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--batch', required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--seeds', type=Path, help='original manifest: recover metadata only for byte-identical C')
    parser.add_argument('--resume', action='store_true', help='resume interrupted/failed attempts and unstarted seeds, excluding completed work')
    args = parser.parse_args()
    summary = prepare(args.batch, args.output.resolve(), args.seeds, args.resume)
    print(json.dumps({k: v for k, v in summary.items() if k != 'skipped'}), flush=True)


if __name__ == '__main__':
    main()
