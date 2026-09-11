#!/usr/bin/env python3
"""Compare completed near misses with retail, preserving the running batch's work copies."""
import argparse
import hashlib
import json
import shutil
import time
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from fzgx import fixup, oracle, stuck
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
            metadata = Path(attempt['best_body_path']).with_suffix('.json')
            index = STATE_DIR / 'checks' / symbol.replace(':', '__') / 'index.jsonl'
            if index.exists():
                for line in index.read_text().splitlines():
                    checked = json.loads(line)
                    path = index.parent / f'{checked["n"]:03d}.c'
                    if (attempt['started'] <= checked['t'] <= attempt['ended'] and path.exists()
                            and hashlib.sha256(path.read_bytes()).hexdigest() == sha):
                        record = checked
            if metadata.exists():
                saved = json.loads(metadata.read_text())
                if saved['sha256'] != sha:
                    raise ValueError(f'{symbol}: release metadata does not match saved C')
                record = saved
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


def mine_transcripts(batch, output):
    """Count recurrent tool/transport failures separately from released code."""
    directory = STATE_DIR / 'runs' / batch
    results = [json.loads(line) for line in (directory / 'results.jsonl').read_text().splitlines()]
    ledger = Ledger()
    functions = {}
    for row in results:
        symbol = row['symbol']
        attempt = ledger.db.execute('SELECT * FROM attempts WHERE id=?', (row['attempt_id'],)).fetchone()
        notes = (attempt['notes'] or '') if attempt else ''
        reason = ('interrupted' if row['outcome'].startswith('interrupted') else
                  'stale_limit' if notes.startswith('plateau:') else 'check_limit' if notes.startswith('budget exhausted:')
                  else 'model_ended' if notes.startswith('model ended') else 'matched' if row['outcome'] == 'matched' else 'voluntary_release')
        events = [json.loads(line) for line in (directory / f'{symbol}.log').read_text().splitlines()]
        errors, samples = Counter(), {}
        responses, output_tokens, reasoning_tokens, retries = 0, 0, 0, 0
        previous_usage = {}
        tools = Counter()
        for event in events:
            params, method = event.get('params', {}), event.get('method')
            if method == 'error':
                error = params.get('error', {})
                detail = error.get('additionalDetails') or error.get('message') or 'unknown'
                kind = ('output_token_limit' if 'max_output_tokens' in detail else 'stream_timeout' if 'timeout' in detail
                        else 'stream_network' if 'network error' in detail else 'transport_other')
                errors[kind] += 1
                retries += bool(params.get('willRetry'))
                samples.setdefault(kind, detail)
            elif method == 'item/tool/call':
                tools[params['tool']] += 1
            elif method == 'fzgx/tool/result':
                result = params['result']
                if not result.get('ok', True):
                    detail = result.get('error', '')
                    kind = 'patch_anchor' if '`old` occurs' in detail else 'tool_error'
                    errors[kind] += 1
                    samples.setdefault(kind, detail)
                check = result.get('check', '')
                if isinstance(check, str) and check.startswith('CHECK FAILED:'):
                    patterns = ('illegal implicit conversion', 'undefined identifier', 'declaration syntax',
                                'expression syntax', 'illegal operands', 'illegal explicit conversion')
                    kind = 'compile:' + next((p for p in patterns if p in check), 'other')
                    errors[kind] += 1
                    samples.setdefault(kind, check[:1600])
            elif method == 'thread/tokenUsage/updated':
                usage = params['tokenUsage']['total']
                delta = max(0, usage['outputTokens'] - previous_usage.get('outputTokens', 0))
                responses += bool(delta)
                output_tokens += delta
                reasoning_tokens += max(0, usage.get('reasoningOutputTokens', 0) - previous_usage.get('reasoningOutputTokens', 0))
                previous_usage = usage
        functions[symbol] = dict(outcome=row['outcome'], reason=reason, percent=row['percent'], checks=row['checks'],
                                 tool_calls=dict(tools), errors=dict(errors), examples=samples, responses=responses,
                                 output_tokens=output_tokens, reasoning_tokens=reasoning_tokens, retries=retries,
                                 secs=row['secs'], setup_secs=row['setup_secs'], tool_secs=row['tool_secs'],
                                 queue_secs=row['tool_queue_secs'], notes=notes)
    errors = Counter()
    affected = defaultdict(list)
    for symbol, row in functions.items():
        errors.update(row['errors'])
        for kind in row['errors']:
            affected[kind].append(symbol)
    summary = dict(batch=batch, functions=len(functions), outcomes=dict(Counter(r['outcome'] for r in functions.values())),
                   release_reasons=dict(Counter(r['reason'] for r in functions.values())),
                   errors={k: dict(events=v, functions=len(affected[k])) for k, v in errors.items()},
                   provider_responses=sum(r['responses'] for r in functions.values()),
                   output_tokens=sum(r['output_tokens'] for r in functions.values()),
                   reasoning_tokens=sum(r['reasoning_tokens'] for r in functions.values()),
                   builtin_patch_errors=(directory / 'app-server.stderr.log').read_text().count('apply_patch verification failed'))
    output.mkdir(parents=True, exist_ok=True)
    (output / 'transcripts.json').write_text(json.dumps(dict(summary=summary, functions=functions), indent=2) + '\n')
    print(json.dumps(summary, indent=2))


def repair_saved(output):
    """Replay release fixup on frozen candidates; never claim or install code."""
    inputs = json.loads((output / 'inputs.json').read_text())
    started = time.monotonic()
    results, manifest = {}, {}
    # A submit may replace retail split objects. Keep them stable for the pass;
    # individual functions have separate compiler scratch directories.
    with oracle.build_lock():
        project = Project()
        def repair(item):
            symbol, record = item
            source = Path(record['source'])
            body = source.read_text()
            if hashlib.sha256(body.encode()).hexdigest() != record['sha256']:
                raise ValueError(f'{symbol}: frozen source changed')
            base = oracle.check(project, symbol, 1000, source=source,
                                mw_version=record['mw'], extra_cflags=record['flags'])
            result = fixup.try_fix(project, symbol, body, budget_s=6, base=base)
            if result.get('matched'):
                path = source.with_name('repaired.c')
                path.write_text(result.pop('body'))
                result['candidate'] = dict(path=str(path), sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                                           mw=base.mw_version, flags=base.extra_cflags, percent=100,
                                           kind='deterministic-repair', repair=result.get('label', 'baseline'))
            result.pop('body', None)
            result.pop('best_body', None)
            return symbol, result
        with ThreadPoolExecutor(max_workers=4) as workers:
            for symbol, result in workers.map(repair, inputs.items()):
                results[symbol] = result
                if result.get('candidate'):
                    manifest[symbol] = result['candidate']
                    print(f'{symbol}: {result.get("label", "baseline")}', flush=True)
    summary = dict(functions=len(results), matched=len(manifest), candidates=sum(r['tried'] for r in results.values()),
                   secs=round(time.monotonic() - started, 3))
    (output / 'repairs.json').write_text(json.dumps(dict(summary=summary, functions=results), indent=2) + '\n')
    (output / 'repair-manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(json.dumps(summary))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--batch')
    parser.add_argument('--seeds', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--min-percent', type=float, default=97)
    parser.add_argument('--saved', action='store_true', help='export exact candidates from saved results without recompiling')
    parser.add_argument('--transcripts', action='store_true', help='mine completed app-server logs without compiling or calling models')
    parser.add_argument('--repair', action='store_true', help='run current release fixup on frozen inputs, saving exact candidates')
    args = parser.parse_args()
    if args.repair:
        repair_saved(args.output.resolve())
    elif args.transcripts and args.batch:
        mine_transcripts(args.batch, args.output.resolve())
    elif args.saved:
        save_matches(args.output.resolve())
    elif args.batch and args.seeds:
        diagnose(args.batch, args.seeds, args.output.resolve(), args.min_percent)
    else:
        parser.error('--batch and --seeds are required for compilation; --transcripts requires --batch')
