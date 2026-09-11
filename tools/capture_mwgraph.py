#!/usr/bin/env python3
"""Capture and validate stock MWCC allocation on a frozen near-miss corpus."""
import argparse
import hashlib
import gzip
import json
import os
import signal
import shlex
import subprocess
import time
from pathlib import Path

from fzgx import mwgraph, mwconstraints, oracle
from fzgx.project import Project


def replay_archive(path):
    data = json.loads(gzip.decompress(path.read_bytes()))
    if data['format'] != 'fzgx-mwcc-graphs-v1':
        raise ValueError('unsupported graph archive')
    passes = 0
    start = time.perf_counter_ns()
    for record in data['functions']:
        for capture in record['captures']:
            before, after = capture['before'], capture['after']
            order = mwgraph.simplify(before)
            if order != before['simplify_order']:
                raise ValueError(f"{record['symbol']}: simplify replay differs")
            colors = mwgraph.replay(before, order)
            if any(colors[n['virtual_register']] != n['physical_register'] for n in after['nodes']):
                raise ValueError(f"{record['symbol']}: color replay differs")
            passes += 1
    elapsed = time.perf_counter_ns() - start
    print(json.dumps({'functions': len(data['functions']), 'allocation_passes': passes,
                      'replay_ms': elapsed / 1e6, 'errors': 0}, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--corpus', type=Path)
    mode.add_argument('--archive', type=Path, help='validate saved real allocator graphs without MWCC or LLDB')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--symbols', nargs='+')
    parser.add_argument('--all-near', action='store_true', help='include every saved near miss with a supported compiler')
    parser.add_argument('--replay', action='store_true', help='read existing captures without running MWCC')
    args = parser.parse_args()
    if args.archive:
        replay_archive(args.archive)
        return
    if args.output is None:
        parser.error('--output is required with --corpus')
    root = Path(__file__).resolve().parents[1]
    project = Project()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    inputs = json.loads((args.corpus / 'inputs.json').read_text())
    results = json.loads((args.corpus / 'results.json').read_text())
    jobs = []
    compiler_hashes = {}
    headers_sha256 = mwgraph.header_fingerprint(root, project.version)
    for symbol, record in inputs.items():
        if args.symbols and symbol not in args.symbols:
            continue
        if not args.all_near and results[symbol]['baseline']['pure'] != 'regalloc':
            continue
        source = Path(record['source']).resolve()
        if hashlib.sha256(source.read_bytes()).hexdigest() != record['sha256']:
            raise ValueError(f'{symbol}: frozen C changed')
        flags, default_mw = oracle.module_flags(project, project.resolve(symbol).module)
        mw = record['mw'] or default_mw
        compiler = root / 'build/compilers' / mw / 'mwcceppc.exe'
        if compiler not in compiler_hashes:
            compiler_hashes[compiler] = hashlib.sha256(compiler.read_bytes()).hexdigest()
        if compiler_hashes[compiler] not in mwgraph.PROFILES:
            if args.all_near:
                print(json.dumps({'symbol': symbol, 'skipped': 'unsupported compiler', 'compiler': mw}))
                continue
            raise ValueError(f'{symbol}: unsupported compiler {record["mw"]}')
        stem = symbol.replace(':', '__')
        obj = output / (stem + '.o')
        captured_source = output / 'sources' / (stem + '.c')
        if not args.replay:
            captured_source.parent.mkdir(parents=True, exist_ok=True)
            captured_source.write_bytes(source.read_bytes())
        extra = shlex.split(record['flags'] or '')
        levels = [f for f in extra if f.startswith('-O')]
        compiler_flags = [levels[-1] if levels and f.startswith('-O') else f for f in shlex.split(flags)]
        compiler_flags += [f for f in extra if not f.startswith('-O')]
        jobs.append({'symbol': symbol, 'capture': str(output / (stem + '.json')),
                     'compiler': mw, 'name': project.resolve(symbol).name,
                     'source_sha256': record['sha256'], 'headers_sha256': headers_sha256,
                     'args': [str(compiler), *compiler_flags,
                              '-c', str(captured_source), '-o', str(obj)]})
    if not jobs:
        parser.error('no register-allocation candidates selected')
    config = output / 'config.json'
    expected = {'root': str(root), 'wibo': str(root / 'build/tools/wibo'),
                'jobs': jobs, 'report': str(output / 'capture-report.json')}
    if args.replay:
        saved = json.loads(config.read_text())
        saved_jobs = {j['symbol']: j for j in saved['jobs']}
        if any(saved_jobs.get(j['symbol']) != j for j in jobs):
            raise ValueError('capture configuration changed; recapture required')
        capture_seconds = None
    else:
        config.write_text(json.dumps(expected))
        start = time.perf_counter()
        script = root / 'tools/fzgx/mwgraph_lldb.py'
        with oracle.build_lock(), (output / 'lldb.log').open('w') as log:
            command = ['xcrun', 'lldb', '-b', '-o', f'command script import "{script}"',
                       '-o', f'script mwgraph_lldb.run(lldb.debugger, {str(config)!r})',
                       '-o', 'quit']
            process = subprocess.Popen(command, cwd=root, stdout=log, stderr=subprocess.STDOUT,
                                       start_new_session=True)
            try:
                code = process.wait(timeout=max(60, len(jobs) * 20))
                if code:
                    raise subprocess.CalledProcessError(code, command)
            except (subprocess.TimeoutExpired, KeyboardInterrupt):
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()
                raise
        capture_seconds = time.perf_counter() - start
    rows = []
    for job in jobs:
        symbol = job['symbol']
        result = json.loads(Path(job['capture']).read_text())
        if 'error' in result:
            rows.append(result)
            continue
        baseline = Path(results[symbol]['baseline']['object'])
        captured_words = oracle.words(Path(job['args'][-1]), job['name'])
        baseline_words = oracle.words(baseline, job['name'])
        same_code = bool(captured_words) and captured_words == baseline_words
        same_object, object_percent = oracle.function_score(project, job['name'], baseline, Path(job['args'][-1]))
        errors, simplify_errors, witnesses, count = [], [], 0, 0
        start = time.perf_counter_ns()
        for capture in result['captures']:
            before, after = capture['before'], capture['after']
            order = mwgraph.simplify(before)
            if order != before['simplify_order']:
                simplify_errors.append(before['register_class'])
            colors = mwgraph.replay(before)
            errors.extend((n['virtual_register'], colors[n['virtual_register']], n['physical_register'])
                          for n in after['nodes'] if colors[n['virtual_register']] != n['physical_register'])
            count += len(before['simplify_order'])
        replay_ns = time.perf_counter_ns() - start
        start = time.perf_counter_ns()
        for capture in result['captures']:
            before, after = capture['before'], capture['after']
            active = set(before['simplify_order'])
            desired = {n['virtual_register']: n['physical_register'] for n in after['nodes']
                       if n['virtual_register'] in active}
            if all(c >= 0 for c in desired.values()):
                witnesses += mwgraph.selection_order(before, desired) is not None
        inverse_ns = time.perf_counter_ns() - start
        start = time.perf_counter_ns()
        target_words = oracle.words(Path(inputs[symbol]['target']), job['name'])
        constraints = mwconstraints.target_mapping(target_words, baseline_words)
        projections = []
        if constraints['status'] == 'fixed-graph-hypothesis':
            constraints['graphs'] = mwconstraints.constrain(result['captures'], constraints['mapping'])
            for capture, witness in zip(result['captures'], constraints['graphs']):
                candidate = mwconstraints.declaration_projection(
                    Path(inputs[symbol]['source']).read_text(), job['name'], capture, witness)
                if candidate is not None:
                    projections.append(candidate)
        target_ns = time.perf_counter_ns() - start
        if projections:
            for i, candidate in enumerate(dict.fromkeys(projections)):
                (output / (symbol.replace(':', '__') + f'.projection-{i}.c')).write_text(candidate)
        rows.append({'symbol': symbol, 'compiler': job['compiler'],
                     'source_sha256': inputs[symbol]['sha256'], 'same_code': same_code,
                     'same_object': same_object, 'object_percent': object_percent,
                     'passes': len(result['captures']), 'active_nodes': count,
                     'replay_errors': errors, 'simplify_errors': simplify_errors, 'replay_ns': replay_ns,
                     'baseline_order_witnesses': witnesses, 'inverse_ns': inverse_ns,
                     'target_constraints': constraints, 'target_ns': target_ns,
                     'source_projections': len(set(projections))})
    report = {'capture_seconds': capture_seconds, 'functions': rows}
    (output / ('replay-report.json' if args.replay else 'report.json')).write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    if any(r.get('error') or not r['same_code'] or not r['same_object'] or r['replay_errors'] or r['simplify_errors'] for r in rows):
        raise SystemExit(1)


if __name__ == '__main__':
    main()
