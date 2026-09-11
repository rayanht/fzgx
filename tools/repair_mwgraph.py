#!/usr/bin/env python3
"""Generate graph-directed C repairs and verify them with the stock compiler."""
import argparse
from collections import defaultdict
import hashlib
import gzip
import json
import shlex
from pathlib import Path
import time

from fzgx import api, mwgraph, mwrepair, oracle
from fzgx.ledger import Ledger
from fzgx.project import Project


def integrate(project, report, inputs, output):
    ledger = Ledger()
    provenance_path = Path(__file__).resolve().parents[1] / 'state/repairs/mwgraph_imports.json'
    provenance = json.loads(provenance_path.read_text()) if provenance_path.exists() else {}
    accepted, failed, skipped, rebound = [], [], [], []
    for row in report['functions']:
        symbol = row['symbol']
        probe = next((p for p in row['probes'] if p.get('matched')), None)
        if probe is None:
            continue
        record = inputs[symbol]
        seed_symbol = symbol
        sym = project.resolve(symbol)
        target = project.target_object_for(sym)
        exact = target and oracle.function_score(project, sym.name, target, Path(probe['object']))[0]
        if not exact:
            alternatives = []
            if sym.name in project.ambiguous_names():
                for module in project.modules:
                    other = project.resolve(module + ':' + sym.name)
                    if other is None:
                        continue
                    obj = project.target_object_for(other)
                    if obj and oracle.function_score(project, other.name, obj, Path(probe['object']))[0]:
                        alternatives.append(project.key(other))
            if len(alternatives) != 1:
                failed.append({'symbol': symbol, 'error': 'saved result does not match its module target',
                               'alternatives': alternatives})
                continue
            symbol = alternatives[0]
            rebound.append({'from': seed_symbol, 'to': symbol})
        state = ledger.get(symbol)
        if state and state['status'] in ('matched', 'asm'):
            skipped.append({'symbol': symbol, 'reason': 'already integrated'})
            continue
        if state is None or state['status'] == 'claimed':
            failed.append({'symbol': symbol, 'error': 'not unclaimed/unmatched'})
            continue
        if hashlib.sha256(Path(record['source']).read_bytes()).hexdigest() != record['sha256']:
            failed.append({'symbol': symbol, 'error': 'changed seed'})
            continue
        source = Path(probe['source']).read_text()
        if api.lint(project, [probe['source']]):
            failed.append({'symbol': symbol, 'error': 'source lint'})
            continue
        work = project.work_path(symbol)
        work.parent.mkdir(parents=True, exist_ok=True)
        if work.exists() and work.read_text() != source:
            digest = hashlib.sha256(work.read_bytes()).hexdigest()
            backup = output / (symbol.replace(':', '__') + '.previous-' + digest[:12] + '.c')
            backup.write_bytes(work.read_bytes())
        work.write_text(source)
        mw = record['mw'] or oracle.module_flags(project, project.resolve(symbol).module)[1]
        result = api.submit(project, symbol, agent='deterministic-mwgraph',
                            message=probe['label'], harness='mwgraph', mw_version=mw,
                            extra_cflags=record['flags'] or '')
        if not result.get('ok'):
            failed.append({'symbol': symbol, 'result': result})
            continue
        accepted.append(symbol)
        provenance[symbol] = {'seed_symbol': seed_symbol, 'generator': ('tools/audit_target_bindings.py' if probe['label'] == 'correct-module-target' else 'tools/repair_mwgraph.py'), 'transform': probe['label'],
                              'seed': Path(record['source']).read_text(), 'seed_sha256': record['sha256'],
                              'generated_sha256': hashlib.sha256(source.encode()).hexdigest(),
                              'compiler': mw, 'flags': record['flags'], 'source': result['unit'],
                              'bytes': project.resolve(symbol).size, 'link': 'pending'}
        provenance_path.write_text(json.dumps(provenance, indent=2) + '\n')
    message = ('Recover matches hidden by cross-module target lookup'
               if accepted and all(provenance[s]['transform'] == 'correct-module-target' for s in accepted)
               else 'Match graph-directed scalar-home repairs')
    verification = api.verify_links(project, message) if accepted else None
    if verification:
        for symbol in verification.get('verified', []):
            if symbol in provenance:
                provenance[symbol]['link'] = 'verified'
                provenance[symbol]['commit'] = verification.get('commit')
        for symbol in verification.get('rejected', []):
            if symbol in provenance:
                provenance[symbol]['link'] = 'rejected'
        provenance_path.write_text(json.dumps(provenance, indent=2) + '\n')
    outcome = {'accepted': accepted, 'failed': failed, 'skipped': skipped, 'rebound': rebound,
               'verification': verification}
    (output / 'integration.json').write_text(json.dumps(outcome, indent=2) + '\n')
    print(json.dumps(outcome, indent=2))
    if failed or (verification and (not verification.get('ok') or verification.get('rejected'))):
        raise SystemExit(1)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--archive', type=Path, help='reproduce archived repairs without compiler or scratch files')
    parser.add_argument('--corpus', type=Path)
    parser.add_argument('--captures', type=Path)
    parser.add_argument('--saved', action='store_true', help='read this output directory’s existing report')
    parser.add_argument('--apply', action='store_true', help='submit exact matches and verify all target hashes')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--next-corpus', type=Path, help='save improved unmatched seeds for another capture/repair pass')
    parser.add_argument('--max-orders', type=int, default=50000)
    args = parser.parse_args()
    if args.archive:
        archive = json.loads(gzip.decompress(args.archive.read_bytes()))
        for symbol, record in archive['repairs'].items():
            source = record['seed']
            if hashlib.sha256(source.encode()).hexdigest() != record['seed_sha256']:
                raise ValueError(f'{symbol}: seed hash mismatch')
            if record['transform'] == 'correct-module-target':
                candidates = [('correct-module-target', source)]
            else:
                constraints = mwrepair.web_constraints(record['captures'], record['target_words'], record['baseline_words'])
                candidates = mwrepair.carrier_candidates(source, symbol.split(':')[-1], record['captures'], constraints)
            if not any(label == record['transform'] and hashlib.sha256(body.encode()).hexdigest() == record['generated_sha256']
                       for label, body in candidates):
                raise ValueError(f'{symbol}: generated source not reproduced')
        print(json.dumps({'reproduced': len(archive['repairs']), 'improved_seeds': len(archive['improved_seeds'])}))
        return
    if args.corpus is None or args.output is None:
        parser.error('--corpus and --output are required unless --archive is used')
    out = args.output.resolve(); out.mkdir(parents=True, exist_ok=True)
    project = Project()
    inputs = json.loads((args.corpus / 'inputs.json').read_text())
    if args.saved:
        report = json.loads((out / 'report.json').read_text())
        if args.apply:
            integrate(project, report, inputs, out)
        else:
            print(json.dumps(report, indent=2))
        return
    if args.captures is None:
        parser.error('--captures is required unless --saved is used')
    baselines = json.loads((args.corpus / 'results.json').read_text())
    capture_config = json.loads((args.captures / 'config.json').read_text())
    capture_jobs = {j['symbol']: j for j in capture_config['jobs']}
    headers_sha256 = mwgraph.header_fingerprint(Path(__file__).resolve().parents[1], project.version)
    ledger = Ledger()
    groups, rows = defaultdict(list), []
    start = time.perf_counter()
    for path in args.captures.glob('*.json'):
        capture = json.loads(path.read_text())
        if not isinstance(capture, dict) or 'captures' not in capture:
            continue
        symbol = capture['symbol']; record = inputs[symbol]; name = project.resolve(symbol).name
        state = ledger.get(symbol)
        if state and state['status'] != 'unmatched':
            rows.append({'symbol': symbol, 'skipped': state['status'], 'probes': []})
            continue
        job = capture_jobs[symbol]
        flags, default_mw = oracle.module_flags(project, project.resolve(symbol).module)
        extra = shlex.split(record['flags'] or '')
        levels = [f for f in extra if f.startswith('-O')]
        expected_flags = [levels[-1] if levels and f.startswith('-O') else f for f in shlex.split(flags)]
        expected_flags += [f for f in extra if not f.startswith('-O')]
        if (job['headers_sha256'] != headers_sha256 or job['compiler'] != (record['mw'] or default_mw)
                or job['args'][1:-4] != expected_flags):
            raise ValueError(f'{symbol}: capture settings or headers changed; recapture required')
        if capture_jobs[symbol]['source_sha256'] != record['sha256']:
            raise ValueError(f'{symbol}: capture belongs to another source')
        if not all('pcode' in c for c in capture['captures']):
            raise ValueError(f'{symbol}: recapture with PCode support')
        source = Path(record['source']).read_text()
        if hashlib.sha256(source.encode()).hexdigest() != record['sha256']:
            raise ValueError(f'{symbol}: changed frozen source')
        before = oracle.words(Path(baselines[symbol]['baseline']['object']), name)
        target = oracle.words(Path(record['target']), name)
        if target is None or len(target) * 4 != project.resolve(symbol).size:
            rows.append({'symbol': symbol, 'error': 'stale target identity; regenerate the corpus', 'probes': []})
            continue
        constraints = mwrepair.web_constraints(capture['captures'], target, before)
        candidates, search = mwrepair.declaration_candidates(source, name, capture['captures'], constraints, args.max_orders)
        proposals = [('declaration-order', c) for c in candidates]
        proposals.extend(mwrepair.carrier_candidates(source, name, capture['captures'], constraints))
        row = {'symbol': symbol, 'source_sha256': record['sha256'], 'constraints': constraints,
               'search': search, 'baseline_score': oracle.word_score(target, before)[0], 'probes': []}
        rows.append(row)
        seen = {source}
        for label, body in proposals:
            if body in seen:
                continue
            seen.add(body)
            path = out / (symbol.replace(':', '__') + f'.{len(row["probes"])}.c')
            path.write_text(body)
            probe = {'label': label, 'source': str(path), 'sha256': hashlib.sha256(body.encode()).hexdigest()}; row['probes'].append(probe)
            groups[project.resolve(symbol).module, record['mw'], record['flags']].append((row, probe, path))
    generate_seconds = time.perf_counter() - start
    start = time.perf_counter()
    with oracle.build_lock():
        for n, ((module, mw, flags), items) in enumerate(groups.items()):
            objects = oracle.compile_many(project, module, [item[2] for item in items], out / str(n), mw, flags)
            for row, probe, source in items:
                symbol = row['symbol']; name = project.resolve(symbol).name
                if source not in objects:
                    probe['error'] = 'compile'
                    continue
                obj = objects[source]
                target = Path(inputs[symbol]['target'])
                words = oracle.words(obj, name)
                if words is None:
                    probe['error'] = 'missing-function'
                    continue
                probe.update(object=str(obj), score=oracle.word_score(oracle.words(target, name), words)[0])
                if probe['score'] == 100:
                    result = oracle._diff(project, module, name, '', 0, target=target, base=obj)
                    probe.update(matched=result.matched, percent=result.percent, pool=result.pool)
    if args.next_corpus:
        next_inputs, next_results = {}, {}
        for row in rows:
            if row.get('error') or row.get('skipped'):
                continue
            best = max(row['probes'], key=lambda p: p.get('score', 0), default={})
            if best.get('matched') or best.get('score', 0) <= row['baseline_score']:
                continue
            symbol = row['symbol']
            record = dict(inputs[symbol], source=best['source'],
                          sha256=hashlib.sha256(Path(best['source']).read_bytes()).hexdigest())
            next_inputs[symbol] = record
            next_results[symbol] = {'baseline': dict(baselines[symbol]['baseline'], object=best['object'])}
        args.next_corpus.mkdir(parents=True, exist_ok=True)
        (args.next_corpus / 'inputs.json').write_text(json.dumps(next_inputs, indent=2))
        (args.next_corpus / 'results.json').write_text(json.dumps(next_results, indent=2))
    report = {'generate_seconds': generate_seconds, 'compile_seconds': time.perf_counter()-start, 'functions': rows}
    (out / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
    if args.apply:
        integrate(project, report, inputs, out)
    print(json.dumps({'functions': len(rows), 'probes': sum(len(r['probes']) for r in rows),
                      'generate_seconds': generate_seconds, 'compile_seconds': report['compile_seconds'],
                      'matches': [r['symbol'] for r in rows if any(p.get('matched') for p in r['probes'])],
                      'improved': sum(any(p.get('score', 0) > r['baseline_score'] for p in r['probes']) for r in rows)}, indent=2))


if __name__ == '__main__':
    main()
