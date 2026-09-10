#!/usr/bin/env python3
"""Freeze full-size lifter drafts for the largest unmatched functions."""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from fzgx import lift, oracle
from fzgx.ledger import Ledger
from fzgx.project import Project


def prior_attempt(ledger, symbol):
    row = ledger.db.execute(
        'SELECT * FROM attempts WHERE symbol=? AND ended IS NOT NULL AND best_body_path IS NOT NULL '
        'ORDER BY best_in_attempt DESC,id DESC LIMIT 1', (symbol,)).fetchone()
    if not row:
        return None
    path = Path(row['best_body_path'])
    body = path.read_text()
    metadata = json.loads(path.with_suffix('.json').read_text())
    if hashlib.sha256(body.encode()).hexdigest() != metadata['sha256']:
        raise ValueError(f'{symbol}: prior candidate hash changed')
    return dict(source=body, sha256=metadata['sha256'], mw=metadata.get('mw'), flags=metadata.get('flags'),
                percent=metadata.get('percent', row['best_in_attempt']), attempt_id=row['id'],
                instruction='Reuse this previously recovered code where it is more complete than the new lifter draft.')


def prepare(output: Path, count: int):
    project, ledger = Project(), Ledger()
    rows = [dict(row) for row in ledger.db.execute(
        "SELECT * FROM functions WHERE status='unmatched' ORDER BY size DESC,module,addr LIMIT ?", (count,))]
    if len(rows) != count:
        raise ValueError(f'only {len(rows)} unmatched functions remain, requested {count}')
    output.mkdir(parents=True, exist_ok=False)
    (output / 'selection.json').write_text(json.dumps(rows, indent=2) + '\n')
    manifest, errors = {}, {}
    # Freeze against one retail split state. Do not impose the small-function
    # default: every selected function must supply its whole instruction stream.
    with oracle.build_lock():
        for i, row in enumerate(rows, 1):
            symbol = row['symbol']
            sym = project.resolve(symbol)
            if sym is None:
                errors[symbol] = 'ledger symbol is absent from the current project'
                continue
            max_ins = max(1200, (row['size'] + 3) // 4)
            body = lift.lift_total(project, row['module'], sym.name, max_ins=max_ins)
            if body is None:
                errors[symbol] = 'lift_total returned no draft'
            else:
                path = output / (symbol.replace(':', '__') + '.c')
                path.write_text(body)
                manifest[symbol] = dict(path=str(path.resolve()), sha256=hashlib.sha256(body.encode()).hexdigest(),
                                        kind='lift_total', size=row['size'], module=row['module'],
                                        unresolved=body.count('???'), max_ins=max_ins)
                prior = prior_attempt(ledger, symbol)
                if prior:
                    manifest[symbol]['prior_attempt'] = prior
            print(f'{i}/{count} {symbol} {row["size"]} B: '
                  f'{manifest[symbol]["unresolved"]} unresolved' if symbol in manifest
                  else f'{i}/{count} {symbol}: {errors[symbol]}', flush=True)
    (output / 'errors.json').write_text(json.dumps(errors, indent=2) + '\n')
    if errors:
        raise RuntimeError(f'{len(errors)} functions have no lifter seed; see {output / "errors.json"}')
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    summary = dict(functions=len(manifest), bytes=sum(r['size'] for r in rows),
                   smallest=min(r['size'] for r in rows), largest=max(r['size'] for r in rows),
                   modules=dict(Counter(r['module'] for r in rows)),
                   partial=sum(r['unresolved'] > 0 for r in manifest.values()),
                   manifest=str(output / 'manifest.json'))
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--count', type=int, default=50)
    args = parser.parse_args()
    if args.count < 1:
        parser.error('--count must be positive')
    print(json.dumps(prepare(args.output.resolve(), args.count)))
