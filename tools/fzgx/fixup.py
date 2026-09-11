"""One deterministic repair engine for sessions, lifters and whole saved corpora.

All generators share content-addressed compilation, scoring, search budgets and
verification. Source/evidence helpers never compile, search or submit independently.
"""
from __future__ import annotations

from collections import defaultdict
import gzip
import hashlib
import json
from pathlib import Path
import shlex
import time

from . import fixup_evidence as evidence, fixup_source as source, mwgraph, oracle
from .project import ROOT, STATE_DIR, Project


def digest(value):
    return hashlib.sha256(value).hexdigest()


class Engine:
    def __init__(self, project, output, verbose=False):
        self.project, self.output, self.verbose = project, output, verbose
        output.mkdir(parents=True, exist_ok=True)
        self.headers = mwgraph.header_fingerprint(ROOT, project.version)
        self.environment = digest((self.headers + ''.join(digest((ROOT/'tools/fzgx'/f).read_bytes()) for f in
            ('oracle.py', 'poolfix.py', 'project.py'))).encode())
        self.cache_path = output / 'cache.json'
        self.cache = json.loads(self.cache_path.read_text()) if self.cache_path.exists() else {}
        self.targets, self.words, self.checks, self.compilers = {}, {}, {}, {}
        provenance = ROOT/'state/repairs/fixup_imports.json'
        self.rejected = json.loads(provenance.read_text()) if provenance.exists() else {}
        self.compiled = self.cached = 0
        self.compile_seconds = 0.0

    def emit(self, value):
        if self.verbose:
            print(json.dumps(value), flush=True)

    def record(self, symbol, body, mw=None, flags=None, **metadata):
        sym = self.project.resolve(symbol)
        if sym is None:
            raise ValueError(f'unknown or ambiguous symbol: {symbol}')
        symbol = self.project.key(sym)
        mw = mw or oracle.module_flags(self.project, sym.module)[1]
        flags = flags or ''
        if mw not in self.compilers:
            self.compilers[mw] = digest((ROOT/'build/compilers'/mw/'mwcceppc.exe').read_bytes())
        if symbol not in self.targets:
            path = self.project.target_object_for(sym)
            if path is None:
                raise ValueError(f'{symbol}: missing retail object')
            self.targets[symbol] = (path, oracle.words(path, sym.name), digest(path.read_bytes()))
        target, words, target_hash = self.targets[symbol]
        if not words or len(words)*4 != sym.size:
            raise ValueError(f'{symbol}: invalid retail target size')
        sha = digest(body.encode())
        identity = digest(json.dumps([self.environment, symbol, sha, mw, flags, oracle.module_flags(self.project, sym.module)[0], self.compilers[mw], target_hash]).encode())
        path = self.output / 'sources' / (identity[:24]+'.c')
        path.parent.mkdir(exist_ok=True)
        if not path.exists():
            path.write_text(body)
        elif digest(path.read_bytes()) != sha:
            raise ValueError(f'changed content-addressed source: {path}')
        return dict(metadata, symbol=symbol, source=str(path), sha256=sha, mw=mw, flags=flags,
                    target=str(target), id=identity)

    def evaluate(self, rows):
        groups = defaultdict(list)
        unique = {r['id']: r for r in rows}
        for row in unique.values():
            cached = self.cache.get(row['id'])
            if cached and (not cached.get('object') or Path(cached['object']).exists()):
                row.update(cached); self.cached += 1
                if row.get('object'):
                    self.words[row['id']] = oracle.words(Path(row['object']), self.project.resolve(row['symbol']).name)
                continue
            sym = self.project.resolve(row['symbol'])
            groups[sym.module, row['mw'], row['flags']].append(row)
        tick = time.monotonic()
        progress = time.monotonic()
        for (module, mw, flags), pending in groups.items():
            group = digest(json.dumps([module,mw,flags]).encode())[:16]
            objects = oracle.compile_many(self.project, module, [Path(r['source']) for r in pending], self.output/'objects'/group, mw, flags)
            self.compiled += len(pending)
            for row in pending:
                obj = objects.get(Path(row['source']))
                words = oracle.words(obj, self.project.resolve(row['symbol']).name) if obj else None
                target = self.targets[row['symbol']][1]
                self.words[row['id']] = words
                row.update(object=str(obj) if obj else None, score=oracle.word_score(target, words)[0] if words else -1,
                           bit_errors=(sum((a^b).bit_count() for a,b in zip(target,words))+32*abs(len(target)-len(words))) if words else 10**9)
                if row['score'] == 100:
                    check = self.check(row)
                    row['matched'] = bool(check.matched or check.matched_pool)
                self.cache[row['id']] = {k:row[k] for k in ('object','score','bit_errors','matched') if k in row}
            if time.monotonic()-progress >= 10:
                self.cache_path.write_text(json.dumps(self.cache))
                self.emit({'stage': 'compile', 'compiled': self.compiled, 'cached': self.cached})
                progress = time.monotonic()
        self.compile_seconds += time.monotonic()-tick
        self.cache_path.write_text(json.dumps(self.cache))
        for row in rows:
            row.update({k:v for k,v in unique[row['id']].items() if k in ('object','score','bit_errors','matched')})
            # An exact function diff ignores other emitted functions. REL links
            # retain static helper copies, shifting text and dependent modules.
            sym = self.project.resolve(row['symbol'])
            if row.get('matched') and sym.module != 'main' and row.get('object'):
                from .poolfix import Elf
                elf = Elf(Path(row['object']).read_bytes())
                extras = [s['name'] for s in elf.symbols() if s['info'] & 15 == 2 and s['shndx'] and s['size'] and s['name'] != sym.name]
                if extras:
                    row.update(matched=False, object_matched=True, extra_helpers=extras)
            failed = self.rejected.get(row['symbol'], {})
            if (failed.get('link') == 'rejected' and failed.get('generated_sha256') == row['sha256']
                    and failed.get('compiler') == row['mw'] and (failed.get('flags') or '') == row['flags']
                    and failed.get('headers_sha256') == self.headers
                    and failed.get('oracle_sha256') == digest(Path(oracle.__file__).read_bytes())):
                row.update(matched=False, link_rejected=True)

    def check(self, row):
        if row['id'] not in self.checks:
            sym = self.project.resolve(row['symbol'])
            self.checks[row['id']] = oracle._diff(self.project, sym.module, sym.name, '', 0,
                                                target=self.targets[row['symbol']][0], base=Path(row['object']))
        return self.checks[row['id']]

    def proposals(self, row, capture=None, max_orders=50000):
        body = Path(row['source']).read_text()
        name = self.project.resolve(row['symbol']).name
        families = []
        check = self.check(row)
        if check.ok:
            families.append(evidence.candidates(self.project, row['symbol'], body, check))
        if row.get('score') == 100:
            families.insert(0, list(source.inline_helpers(body,name)))
        if capture:
            constraints = source.web_constraints(capture, self.targets[row['symbol']][1], self.words[row['id']])
            decls, _ = source.declaration_candidates(body, name, capture, constraints, max_orders)
            families.append([('graph declaration-order',t) for t in decls]+source.carrier_candidates(body,name,capture,constraints))
        families.extend([source.missing_values(body,name), source.expression_trees(body,name),
                         source.commutations(body,name), source.probes(body,name,64),
                         [(family+': '+label,text) for family,label,text in source.all_rewrites(body,name)]])
        # Round-robin preserves access to each family within the shared budget.
        for i in range(max(map(len,families),default=0)):
            for family in families:
                if i < len(family):
                    yield family[i]

    def run(self, rows, rounds=2, beam=3, max_candidates=80, budget_s=None, captures=None):
        start=time.monotonic(); history=list(rows); seen={r['id'] for r in rows}; initial={}
        self.evaluate(rows)
        self.emit({'stage': 'baseline', 'functions': len({r['symbol'] for r in rows}),
                   'variants': len(rows), 'compiled': self.compiled, 'cached': self.cached})
        self.save(history, stats=[], start=start)
        for r in rows:
            initial[r['symbol']]=max(initial.get(r['symbol'],-1),r['score'])
        stats=[]
        for step in range(rounds):
            if budget_s is not None and time.monotonic()-start >= budget_s:
                break
            winners={r['symbol'] for r in history if r.get('matched')}
            frontier=defaultdict(list); shapes=defaultdict(set)
            for row in sorted(history,key=lambda r:(-r['score'],r['bit_errors'],r['id'])):
                symbol=row['symbol']; words=self.words.get(row['id'])
                if symbol in winners or not words or len(frontier[symbol])>=beam:
                    continue
                shape=tuple(words)
                if shape in shapes[symbol]:
                    continue
                shapes[symbol].add(shape);frontier[symbol].append(row)
            pending=[]; parents={}; generated=time.monotonic()
            for symbol, seeds in frontier.items():
                for seed in seeds:
                    if budget_s is not None and time.monotonic()-start >= budget_s:
                        break
                    cap=(captures or {}).get((symbol,seed['sha256'],seed['mw'],seed['flags']))
                    count=0
                    for label,text in self.proposals(seed,cap):
                        row=self.record(symbol,text,seed['mw'],seed['flags'],label=label,parent=seed['id'],seed=seed.get('seed',seed['id']))
                        if row['id'] in seen:
                            continue
                        seen.add(row['id']); pending.append(row);parents[seed['id']]=seed;count+=1
                        if count>=max_candidates:
                            break
            if not pending:
                break
            generation_seconds=time.monotonic()-generated
            self.evaluate(pending)
            # Compose observed independent bit repairs; no private compile loop.
            responses=defaultdict(list)
            for row in pending:
                responses[row['parent']].append((row['label'],Path(row['source']).read_text(),self.words.get(row['id'])))
            combined=[]
            for parent, values in responses.items():
                seed=parents[parent]; body=Path(seed['source']).read_text(); target=self.targets[seed['symbol']][1]; baseline=self.words[parent]
                if len(baseline)!=len(target):
                    continue
                choices=source.linear_compositions(body,target,baseline,values)
                greedy=source.compose(body,target,baseline,values)
                if greedy: choices.append(greedy)
                for label,text in choices:
                    row=self.record(seed['symbol'],text,seed['mw'],seed['flags'],label=label,parent=parent,seed=seed.get('seed',parent))
                    if row['id'] not in seen:
                        seen.add(row['id']);combined.append(row)
            self.evaluate(combined);pending+=combined;history+=pending
            stat=dict(round=step+1,probes=len(pending),generation_seconds=generation_seconds,
                      matches=len({r['symbol'] for r in history if r.get('matched')}),
                      improved=len({r['symbol'] for r in history if r['score']>initial[r['symbol']]}))
            stats.append(stat);self.emit(stat)
            self.save(history,stats,start)
        return self.save(history,stats,start)

    def save(self,history,stats,start):
        best={}
        for r in sorted(history,key=lambda r:(not r.get('matched',False),-r['score'],r['bit_errors'],r['id'])):
            best.setdefault(r['symbol'],r)
        for row in best.values():
            if row['score'] >= 0:
                result = self.check(row)
                row['percent'] = max(result.percent, result.percent_adjusted) if result.ok else 0
        report=dict(generator_sha256=digest((Path(__file__).read_bytes()+Path(source.__file__).read_bytes()+Path(evidence.__file__).read_bytes())), records=history, best=best, rounds=stats, compiled=self.compiled,cached=self.cached,
                    compile_seconds=self.compile_seconds,seconds=time.monotonic()-start,environment=self.environment)
        (self.output/'report.json').write_text(json.dumps(report))
        return report


def try_fix(p, symbol, body, budget_s=30.0, max_candidates=80, base=None):
    """Session/lifter adapter; same engine and transformations as corpus repair."""
    start=time.monotonic()
    if base and not base.ok:
        return dict(matched=False,body=None,tried=0,best=0,secs=0,error=base.error)
    if base and (base.matched or base.matched_pool):
        return dict(matched=True,body=body,tried=0,best=100,secs=0)
    sym=p.resolve(symbol)
    engine=Engine(p,STATE_DIR/'fixup'/'sessions'/p.key(sym).replace(':','__'))
    mw=base.mw_version if base else None;flags=base.extra_cflags if base else None
    if not mw:
        mw,flags=oracle.version_for(p,sym,p.work_path(symbol))
    row=engine.record(symbol,body,mw,flags,label='input')
    report=engine.run([row],rounds=2,beam=2,max_candidates=max_candidates,budget_s=budget_s)
    best=report['best'][p.key(sym)]; matched=best.get('matched',False)
    check=engine.check(best) if best['score']>=0 else None
    return dict(matched=matched,body=Path(best['source']).read_text() if matched else None,
                best_body=Path(best['source']).read_text(),label=best.get('label'),
                best=max(check.percent,check.percent_adjusted) if check and check.ok else 0,
                base=base.percent if base else row['score'],tried=report['compiled'],secs=time.monotonic()-start,
                mw_version=best['mw'],extra_cflags=best['flags'])


def integrate(project, report, inputs, output):
    from . import api
    from .ledger import Ledger
    ledger = Ledger()
    provenance_path = ROOT / 'state/repairs/fixup_imports.json'
    provenance = json.loads(provenance_path.read_text()) if provenance_path.exists() else {}
    headers_sha256 = mwgraph.header_fingerprint(ROOT, project.version)
    oracle_sha256 = digest(Path(oracle.__file__).read_bytes())
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
        check = oracle._diff(project, sym.module, sym.name, '', 0, target=target, base=Path(probe['object'])) if target else None
        exact = check and check.ok and (check.matched or check.matched_pool)
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
        previous = provenance.get(symbol, {})
        if (previous.get('link') == 'rejected' and previous.get('generated_sha256') == digest(Path(probe['source']).read_bytes())
                and previous.get('compiler') == record['mw'] and (previous.get('flags') or '') == (record['flags'] or '')
                and previous.get('headers_sha256') == headers_sha256 and previous.get('oracle_sha256') == oracle_sha256):
            skipped.append({'symbol': symbol, 'reason': 'this source/settings already failed the link'})
            continue
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
            previous_sha = hashlib.sha256(work.read_bytes()).hexdigest()
            backup = output / (symbol.replace(':', '__') + '.previous-' + previous_sha[:12] + '.c')
            backup.write_bytes(work.read_bytes())
        work.write_text(source)
        mw = record['mw'] or oracle.module_flags(project, project.resolve(symbol).module)[1]
        result = api.submit(project, symbol, agent='deterministic-fixup',
                            message=probe['label'], harness='fixup', mw_version=mw,
                            extra_cflags=record['flags'] or '')
        if not result.get('ok'):
            failed.append({'symbol': symbol, 'result': result})
            continue
        accepted.append(symbol)
        provenance[symbol] = {'seed_symbol': seed_symbol, 'generator': 'fzgx fixup', 'transform': probe['label'],
                              'seed': Path(record['source']).read_text(), 'seed_sha256': record['sha256'],
                              'generated_sha256': hashlib.sha256(source.encode()).hexdigest(), 'generated_source': source,
                              'compiler': mw, 'flags': record['flags'], 'source': result['unit'],
                              'bytes': project.resolve(symbol).size, 'headers_sha256': headers_sha256, 'oracle_sha256': oracle_sha256, 'recipe': row.get('recipe', []), 'link': 'pending'}
        provenance_path.write_text(json.dumps(provenance, indent=2) + '\n')
    message = 'Integrate deterministic fixup matches'
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


def replay_archive(path):
    archive=json.loads(gzip.decompress(path.read_bytes()))
    if archive.get('format')=='fzgx-mwcc-graphs-v1':
        return mwgraph.replay_archive(path)
    for symbol,record in archive['repairs'].items():
        body=record['seed']
        if digest(body.encode())!=record['seed_sha256']:
            raise ValueError(f'{symbol}: seed hash mismatch')
        if record['transform']=='correct-module-target':
            choices=[('correct-module-target',body)]
        else:
            constraints=source.web_constraints(record['captures'],record['target_words'],record['baseline_words'])
            choices=source.carrier_candidates(body,symbol.split(':')[-1],record['captures'],constraints)
        if not any(label==record['transform'] and digest(text.encode())==record['generated_sha256'] for label,text in choices):
            raise ValueError(f'{symbol}: source not reproduced')
    result=dict(reproduced=len(archive['repairs']),improved_seeds=len(archive['improved_seeds']))
    print(json.dumps(result));return result


def load_records(engine,args):
    from .ledger import Ledger
    from seeds.recovered import SavedCandidates
    p=engine.project;ledger=Ledger();rows=[]
    def add(symbol,body,mw=None,flags=None,**metadata):
        sym=p.resolve(symbol);state=ledger.get(symbol)
        if not sym or not state or state['status']!='unmatched':
            return
        if args.module and sym.module!=args.module or args.max_size is not None and sym.size>args.max_size:
            return
        rows.append(engine.record(symbol,body,mw,flags,**metadata))
    if args.symbol:
        from . import api
        body=Path(args.body).read_text() if args.body else api._attempt_text(p,args.symbol)
        if body is None:
            raise ValueError('no saved C for '+args.symbol)
        sym=p.resolve(args.symbol)
        mw,flags=oracle.version_for(p,sym,Path(args.body) if args.body else p.work_path(args.symbol))
        add(args.symbol,body,mw,flags,label='saved-body')
    elif args.corpus:
        prepared=args.corpus/'prepared.json'
        if prepared.exists():
            inputs=json.loads(prepared.read_text())['records']
        else:
            inputs=[dict(r,symbol=s) for s,r in json.loads((args.corpus/'inputs.json').read_text()).items()]
        for r in inputs:
            body=Path(r['source']).read_text()
            if digest(body.encode())!=r['sha256']:
                raise ValueError(f"{r['symbol']}: frozen source changed")
            add(r['symbol'],body,r['mw'],r['flags'],label='saved-body',origin=r.get('origin'))
    else:
        saved=SavedCandidates(args.min_percent-0.000001);saved.collect()
        for symbol,choices in saved.candidates.items():
            options={r['sha256']:r for r in choices if r['settings_recorded']}
            for r in choices:
                if r['percent']>args.max_percent:
                    continue
                chosen=r if r['settings_recorded'] else options.get(r['sha256'],r)
                add(symbol,r['body'],chosen['mw'],chosen['flags'],label='saved-body',origin=r['origin'])
        if args.drafts:
            for symbol,r in json.loads((STATE_DIR/'lift/scores.json').read_text()).items():
                if r.get('text') and args.min_percent<=r.get('percent',0)<=args.max_percent:
                    add(symbol,r['text'],r.get('mw'),r.get('flags'),label='lifted-body')
    rows=list({r['id']:r for r in rows}.values())
    if args.limit:
        selected=set(sorted({r['symbol'] for r in rows})[:args.limit]);rows=[r for r in rows if r['symbol'] in selected]
    return rows


def load_captures(engine,path,rows):
    if path is None:
        return {}
    jobs=json.loads((path/'config.json').read_text())['jobs'];result={}
    seeds={(r['symbol'],r['sha256'],r['mw'],r['flags']):r for r in rows}
    for job in jobs:
        matching=[(key,r) for key,r in seeds.items() if key[:3]==(job['symbol'],job['source_sha256'],job['compiler'])]
        for key,row in matching:
            flags,_=oracle.module_flags(engine.project,engine.project.resolve(row['symbol']).module)
            extra=shlex.split(row['flags']);levels=[f for f in extra if f.startswith('-O')]
            expected=[levels[-1] if levels and f.startswith('-O') else f for f in shlex.split(flags)]
            expected += [f for f in extra if not f.startswith('-O')]
            if job['headers_sha256']!=engine.headers or job['args'][1:-4]!=expected:
                raise ValueError(f"{row['symbol']}: stale capture; recapture required")
            capture=json.loads((path/(job['symbol'].replace(':','__')+'.json')).read_text())
            if capture.get('error'):
                continue
            if not all('pcode' in c for c in capture['captures']):
                raise ValueError('capture lacks PCode; recapture required')
            result[key]=capture['captures']
    return result


def command(p,args):
    if args.rounds < 0 or args.beam < 1 or args.max_candidates < 1 or (args.budget is not None and args.budget <= 0):
        raise ValueError('rounds must be nonnegative; beam, max-candidates and budget must be positive')
    if args.archive:
        return replay_archive(args.archive)
    if args.capture:
        if args.corpus is None or args.output is None:
            raise ValueError('--capture requires --corpus and --output')
        args.symbols=[args.symbol] if args.symbol else None;args.all_near=True
        return mwgraph.capture(p,args)
    output=(args.output or STATE_DIR/'fixup'/'corpus').resolve()
    if args.saved:
        report=json.loads((output/'report.json').read_text())
    else:
        engine=Engine(p,output,verbose=True);rows=load_records(engine,args)
        captures=load_captures(engine,args.captures,rows)
        with oracle.build_lock():
            report=engine.run(rows,args.rounds,args.beam,args.max_candidates,args.budget,captures)
        # One canonical corpus format for capture and future repair, all variants
        # remain in report.json rather than separate per-algorithm stores.
        best={s:r for s,r in report['best'].items() if r['score']>=0 and not r.get('matched')}
        (output/'inputs.json').write_text(json.dumps(best))
        (output/'results.json').write_text(json.dumps({s:{'baseline':{'object':r['object'],'pure':'unclassified'}} for s,r in best.items()}))
    if args.apply:
        by_id={r['id']:r for r in report['records']};inputs={};functions=[]
        for symbol,row in report['best'].items():
            if not row.get('matched'):
                continue
            seed=by_id[row.get('seed',row['id'])]
            inputs[symbol]=seed
            recipe=[]; current=row
            while current.get('parent'):
                parent=by_id[current['parent']]
                recipe.append(dict(label=current['label'], input_sha256=parent['sha256'], output_sha256=current['sha256']))
                current=parent
            functions.append(dict(symbol=symbol,probes=[dict(row,matched=True)],recipe=list(reversed(recipe))))
        try:
            integrate(p,{'functions':functions},inputs,output)
        finally:
            result_path=output/'integration.json'
            if result_path.exists():
                result=json.loads(result_path.read_text())
                rejected=(result.get('verification') or {}).get('rejected', [])
                cache_path=output/'cache.json'
                cache=json.loads(cache_path.read_text()) if cache_path.exists() else {}
                for symbol in rejected:
                    row=report['best'][symbol]
                    row.update(matched=False,link_rejected=True)
                    if row['id'] in cache:
                        cache[row['id']].update(matched=False,link_rejected=True)
                cache_path.write_text(json.dumps(cache))
                (output/'report.json').write_text(json.dumps(report))
    summary={k:report[k] for k in ('compiled','cached','compile_seconds','seconds')}
    summary.update(functions=len(report['best']),variants=len(report['records']),
                   matches=[s for s,r in report['best'].items() if r.get('matched')])
    print(json.dumps(summary,indent=2));return summary
