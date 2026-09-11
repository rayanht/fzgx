#!/usr/bin/env python3
"""Re-score saved ambiguous-name attempts after the module-qualified target fix."""
import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import time

from fzgx import oracle
from fzgx.ledger import Ledger
from fzgx.project import Project


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=True)
    p, ledger = Project(), Ledger()
    keys = [r['symbol'] for r in ledger.db.execute("SELECT symbol FROM functions WHERE status='unmatched'")
            if ':' in r['symbol'] and p.resolve(r['symbol']).name in p.ambiguous_names()]
    migration = Path(__file__).resolve().parents[1] / 'state/repairs/target_binding_v4.json'
    cutoff = (json.loads(migration.read_text())['cutoff_attempt_id'] if migration.exists() else
              ledger.db.execute('SELECT COALESCE(MAX(id),0) FROM attempts').fetchone()[0])
    groups, history, measured = defaultdict(list), [], []
    for key in keys:
        for row in ledger.db.execute('SELECT * FROM attempts WHERE symbol=? AND ended IS NOT NULL AND id<=?', (key, cutoff)):
            record = dict(row)
            # Already-audited histories and their replacement scores are stable.
            if record['harness'] == 'target-binding-audit' or '[target-v4 invalidated]' in (record['notes'] or ''):
                continue
            history.append(record)
            if not record['best_body_path'] or not Path(record['best_body_path']).exists():
                continue
            original = Path(record['best_body_path']); source = original.read_bytes()
            metadata = original.with_suffix('.json')
            options = json.loads(metadata.read_text()) if metadata.exists() else {}
            if options.get('sha256') not in (None, hashlib.sha256(source).hexdigest()):
                options = {}
            path = output / f"attempt_{record['id']}.c"; path.write_bytes(source)
            groups[p.resolve(key).module, options.get('mw'), options.get('flags')].append((record, path))
    with oracle.build_lock():
        for n, ((module, mw, flags), rows) in enumerate(groups.items()):
            objects = oracle.compile_many(p, module, [r[1] for r in rows], output / str(n), mw, flags)
            for record, path in rows:
                symbol = p.resolve(record['symbol'])
                score = None
                if path in objects:
                    _, score = oracle.function_score(p, symbol.name, p.target_object_for(symbol), objects[path])
                measured.append({'symbol': record['symbol'], 'attempt': record['id'], 'source': str(path),
                                 'percent': max(score, 0) if score is not None else None,
                                 'object': str(objects[path]) if path in objects else None,
                                 'mw': mw or oracle.module_flags(p, module)[1], 'flags': flags})
    report = {'cutoff_attempt_id': cutoff, 'invalidated_history': history, 'rescored': measured, 'applied': False}
    (output / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
    if args.apply and history:
        now = int(time.time())
        with ledger.db:
            for record in history:
                note = (' [target-v4 invalidated] prior scores compared ambiguous names through a global index; '
                        f"best={record['best_in_attempt']}, final={record['final_percent']}")
                ledger.db.execute('UPDATE attempts SET best_in_attempt=NULL,final_percent=NULL,notes=COALESCE(notes,\'\')||? WHERE id=?',
                                  (note, record['id']))
            for key in {r['symbol'] for r in history}:
                choices = [r for r in measured if r['symbol'] == key and r['percent'] is not None]
                if choices:
                    best = max(choices, key=lambda r: r['percent'])
                    dest = p.work_path(key).parent.parent / 'attempts' / (key.replace(':', '__') + f'.target-v4.{now}.c')
                    dest.parent.mkdir(parents=True, exist_ok=True); dest.write_bytes(Path(best['source']).read_bytes())
                    dest.with_suffix('.json').write_text(json.dumps({'sha256': hashlib.sha256(dest.read_bytes()).hexdigest(),
                                                                   'mw': best['mw'], 'flags': best['flags']}) + '\n')
                    ledger.db.execute('INSERT INTO attempts(symbol,agent,harness,started,ended,checks,final_percent,outcome,notes,best_body_path,best_in_attempt) VALUES(?,?,?,?,?,?,?,?,?,?,?)',
                                      (key, 'deterministic-target-binding', 'target-binding-audit', now, now, 1,
                                       best['percent'], 'released', 'Re-scored against the correct module target', str(dest), best['percent']))
                ledger.db.execute('UPDATE functions SET best_percent=COALESCE((SELECT MAX(best_in_attempt) FROM attempts WHERE symbol=?),0) WHERE symbol=?', (key, key))
        report['applied'] = True
        if not migration.exists():
            migration.write_text(json.dumps(report, indent=2) + '\n')
        (output / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
    if args.apply:
        from repair_mwgraph import integrate
        inputs, functions = {}, []
        for item in measured:
            key = item['symbol']
            if item['percent'] != 100 or key in inputs:
                continue
            inputs[key] = {'source': item['source'], 'sha256': hashlib.sha256(Path(item['source']).read_bytes()).hexdigest(),
                           'target': str(p.target_object_for(p.resolve(key))), 'mw': item['mw'], 'flags': item['flags']}
            functions.append({'symbol': key, 'probes': [{'matched': True, 'source': item['source'],
                              'object': item['object'], 'label': 'correct-module-target'}]})
        if functions:
            integrate(p, {'functions': functions}, inputs, output)
    print(json.dumps({'functions': len({r['symbol'] for r in history}), 'history': len(history),
                      'compiled_sources': len(measured), 'applied': report['applied']}, indent=2))


if __name__ == '__main__':
    main()
