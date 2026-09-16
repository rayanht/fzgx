"""The fast path of the repair engine: every cheap family (evidence, source and declaration
moves) over a whole selection at once, one `compile_many` per module per round, word scores
for ranking and objdiff only on the per-function winner. 66,000 candidates a round take four
minutes; `fzgx fixup`'s per-seed rounds took hours over the same corpus (2026-09-16: 686
bodies at 90%+, four rounds, 17 minutes: 5 matches, 167 improved).

`fzgx sweep --min-percent 90` climbs every saved best body at 90%+; `--land` submits exact
matches (pool matches included) and saves improved bodies as attempts.
"""
from __future__ import annotations

import collections
import json
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import api, fixup_evidence, fixup_layout, fixup_source, linemap, oracle, stuck
from .project import Project, STATE_DIR

Candidate = Tuple[str, str]


def row_lines(p: Project, sym, path: Path, check, outdir: Path) -> Dict[int, int]:
    """{differing row: source line} from a `-sym on` compile (the code is byte-identical)."""
    obj = outdir / 'sym' / (path.stem + '.sym.o')
    obj.parent.mkdir(parents=True, exist_ok=True)
    try:
        if not obj.exists():
            oracle.compile_source(p, sym.module, path, obj, None, '-sym on')
        table = linemap.tables(obj).get(sym.name, []) if obj.exists() else []
    except Exception:
        return {}
    lrows, rrows = check._rows
    accepted = check.__dict__.get('_accepted_rows', set())
    out: Dict[int, int] = {}
    for k, (a, b) in enumerate(zip(lrows, rrows)):
        if k in accepted or ((a.get('diff_kind') or 'DIFF_NONE') == 'DIFF_NONE'
                             and (b.get('diff_kind') or 'DIFF_NONE') == 'DIFF_NONE'):
            continue
        for j in (k, k - 1, k + 1):
            if 0 <= j < len(rrows):
                ins = rrows[j].get('instruction') or {}
                if ins.get('address') is not None:
                    ln = linemap.line_of(table, int(ins['address']))
                    if ln:
                        out[k] = ln
                        break
    return out


def decl_moves(body: str, name: str) -> List[Candidate]:
    """Every single move of one leading local declaration to another position."""
    a = fixup_source._decl_anchor(body, name)
    if not a:
        return []
    span, locs, top, indent = a
    n = len(locs)
    if n < 2 or n > 14:
        return []
    texts = [body[s:e] for s, e, _, _, _ in locs]
    head, tail = body[:locs[0][0]], body[locs[-1][1]:]
    out: List[Candidate] = []
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            order = list(range(n))
            order.pop(i)
            order.insert(j, i)
            out.append((f'move {locs[i][3]} to {j}', head + ''.join(texts[k] for k in order) + tail))
    return out


def generate(p: Project, s: str, sym, path: Path, body: str, check, outdir: Path,
             families: Optional[List[str]]) -> List[Candidate]:
    c: List[Candidate] = []

    def add(fam, fn):
        if families and fam not in families:
            return
        try:
            c.extend((fam + ': ' + label, text) for label, text in fn())
        except Exception:
            pass

    add('paramcopy', lambda: fixup_evidence.parameter_copies(p, s, body, check))
    add('pool', lambda: fixup_evidence.native_pool_literals(p, s, body, check))
    add('primer', lambda: fixup_evidence.shared_pool_primer(p, s, body, check))
    add('fusion', lambda: fixup_evidence.fusion_control(p, s, body, check))
    add('psvec', lambda: fixup_evidence.paired_vector_kernels(p, s, body, check))
    add('convargs', lambda: fixup_evidence.conversion_arguments(p, s, body, check))
    add('callres', lambda: fixup_evidence.call_result_types(p, s, body, check))
    add('lifetimes', lambda: fixup_evidence.scalar_lifetimes(p, s, body, check))
    add('storevals', lambda: fixup_evidence.store_values(body, sym.name, check))
    add('callargs', lambda: fixup_evidence.call_arguments(p, s, body, check))
    add('frame', lambda: fixup_evidence.frame_padding(p, s, body, check))
    add('signed', lambda: fixup_source.signedness_flips(body, sym.name))
    add('floatprec', lambda: fixup_source.float_precision(body, sym.name))
    add('heldcall', lambda: fixup_source.call_results_to_locals(body, sym.name))
    add('through', lambda: fixup_source.through_local(body, sym.name))
    add('splits', lambda: fixup_source.variable_splits(body, sym.name))
    add('carriers', lambda: fixup_source.scalar_carriers(body, sym.name))
    add('constptr', lambda: fixup_source.wrap_constant_pointers(body, sym.name))
    add('decse', lambda: fixup_source.decse_repeated_expressions(body, sym.name))
    add('decl', lambda: decl_moves(body, sym.name))
    add('pragmas', lambda: fixup_evidence.optimizer_pragmas(body, sym.name))
    add('layout', lambda: fixup_layout.tu_section_layout(p, s, body, check))
    if not families or 'attr' in families:
        try:
            rl = row_lines(p, sym, path, check, outdir)
            if rl:
                c.extend(('attrflip: ' + l, t) for l, t in fixup_evidence.attributed_type_flips(p, s, body, check, rl))
                c.extend(('attrinline: ' + l, t) for l, t in fixup_evidence.attributed_inlines(p, s, body, check, rl))
                c.extend(('induction: ' + l, t) for l, t in fixup_evidence.induction_indexing(p, s, body, check, rl))
        except Exception:
            pass
    seen = set()
    out: List[Candidate] = []
    for label, text in c:
        if text != body and text not in seen:
            seen.add(text)
            out.append((label, text))
    return out


def climb(p: Project, selection: Dict[str, str], outdir: Path, rounds: int = 4,
          families: Optional[List[str]] = None) -> Dict[str, dict]:
    """Hill-climb every selected body: the best candidate by word score replaces the body when
    objdiff confirms the gain. Returns {symbol: {base, percent, file, matched, history}}."""
    outdir.mkdir(parents=True, exist_ok=True)
    cur = {s: Path(f) for s, f in selection.items()}
    checks = oracle.check_many(p, list(cur.items()))
    state: Dict[str, dict] = {}
    for s, f in cur.items():
        r = checks.get(s)
        if r and r.ok:
            state[s] = dict(base=r.percent, percent=r.percent, file=str(f), matched=r.matched, history=[], check=r)
    print('functions', len(state))
    for rnd in range(rounds):
        active = [s for s, x in state.items() if not x['matched']]
        gen: Dict[str, list] = collections.defaultdict(list)
        nc = 0
        for s in active:
            sym = p.resolve(s)
            path = Path(state[s]['file'])
            body = path.read_text()
            for k, (label, text) in enumerate(generate(p, s, sym, path, body, state[s]['check'], outdir, families)):
                f = outdir / f'r{rnd}' / f'{s}__{k}.c'
                f.parent.mkdir(exist_ok=True)
                f.write_text(text)
                gen[sym.module].append((s, f, label))
                nc += 1
        print(f'round {rnd}: {len(active)} functions, {nc} candidates')
        if not nc:
            break
        best: Dict[str, tuple] = {}
        targets: Dict[str, Optional[List[int]]] = {}
        for module, lst in gen.items():
            objs = oracle.compile_many(p, module, [f for _, f, _ in lst], outdir / f'r{rnd}' / 'obj' / module)
            for s, f, label in lst:
                o = objs.get(f)
                if not o:
                    continue
                sym = p.resolve(s)
                if s not in targets:
                    targets[s] = oracle.words(p.target_object_for(sym), sym.name)
                ow = oracle.words(o, sym.name)
                if not targets[s] or not ow:
                    continue
                # aligned first: a structural fix shifts every later word and only the
                # alignment-tolerant score sees the gain (the engine's best-by-shape slot)
                aligned, pos = fixup_source.fitness(targets[s], ow)
                if s not in best or (aligned, pos) > (best[s][0], best[s][1]):
                    best[s] = (aligned, pos, f, label)
        # the current body's word score, per module in one compile
        basew: Dict[str, float] = {}
        by_module: Dict[str, list] = collections.defaultdict(list)
        for s in active:
            by_module[p.resolve(s).module].append(s)
        for module, syms in by_module.items():
            objs = oracle.compile_many(p, module, [Path(state[s]['file']) for s in syms], outdir / f'r{rnd}' / 'base' / module)
            for s in syms:
                sym = p.resolve(s)
                o = objs.get(Path(state[s]['file']))
                ow = oracle.words(o, sym.name) if o else None
                tw = targets.get(s) or oracle.words(p.target_object_for(sym), sym.name)
                basew[s] = fixup_source.fitness(tw, ow) if ow and tw else (-1.0, -1.0)
        winners = [(s, b[2]) for s, b in best.items() if (b[0], b[1]) > basew.get(s, (-1.0, -1.0))]
        res = oracle.check_many(p, winners)
        gained = 0
        for s, f in winners:
            r = res.get(s)
            if not r or not r.ok:
                continue
            # accepted on the aligned gain: objdiff's percent may dip while the shape improves
            if r.matched or r.matched_pool or r.percent > state[s]['percent'] - 2.0:
                state[s].update(percent=r.percent, file=str(f), matched=bool(r.matched or r.matched_pool), check=r)
                state[s]['history'].append(best[s][3])
                gained += 1
        print(f'round {rnd}: {gained} improved, matched so far {sum(1 for x in state.values() if x["matched"])}')
        if not gained:
            break
    rep = {s: {k: v for k, v in x.items() if k != 'check'} for s, x in state.items()}
    (outdir / 'report.json').write_text(json.dumps(rep, indent=1))
    matched = [s for s, x in rep.items() if x['matched']]
    improved = [s for s, x in rep.items() if x['percent'] > x['base'] + 0.05]
    print('matched', len(matched), matched)
    print('improved', len(improved))
    for s in sorted(improved, key=lambda s: -rep[s]['percent'])[:25]:
        print(f"  {s:16s} {rep[s]['base']:6.2f} -> {rep[s]['percent']:6.2f}  {rep[s]['history']}")
    return rep


def land(p: Project, rep: Dict[str, dict], label: str) -> Dict[str, list]:
    """Submit exact matches (pool matches included); save improved bodies as attempts."""
    agent = 'claude-' + label
    submitted, saved, failed = [], [], []
    for s, r in rep.items():
        pct = r.get('percent')
        if pct is None or not r.get('file'):
            continue
        if not r.get('matched') and pct <= r['base'] + 0.05:
            continue
        body = Path(r['file']).read_text()
        c = api.claim(p, s, agent, max_attempts=999, no_carve=True)
        if not c.get('ok'):
            failed.append((s, 'claim', c.get('error')))
            continue
        work = p.work_path(s)
        work.parent.mkdir(parents=True, exist_ok=True)
        work.write_text(body)
        ck = api.check(p, s, 0)
        if r.get('matched') and ck.get('matched'):
            sub = api.submit(p, s, agent=agent, message=f'{s}: {label}', harness='deterministic')
            if sub.get('ok'):
                submitted.append(s)
            else:
                failed.append((s, 'submit', str(sub)[:200]))
                api.release(p, s, 'submit failed', agent=agent)
        else:
            rel = api.release(p, s, f'{label}: {r["base"]:.2f} -> {pct:.2f}', agent=agent)
            if rel.get('ok'):
                saved.append(s)
            else:
                failed.append((s, 'release', rel.get('error')))
    print('submitted', len(submitted), submitted)
    print('saved', len(saved))
    print('failed', len(failed), failed[:10])
    return dict(submitted=submitted, saved=saved, failed=failed)


def run(p: Project, min_percent: float, max_percent: float, outdir: Optional[Path], rounds: int,
        families: Optional[List[str]], do_land: bool, symbols: Optional[List[str]] = None) -> Dict[str, dict]:
    bodies = stuck.best_bodies(p, min_percent)
    sel = {s: r[0] for s, r in bodies.items() if r[1] <= max_percent and (not symbols or s in symbols)}
    outdir = outdir or (STATE_DIR / 'work' / f'sweep-{int(min_percent)}')
    rep = climb(p, sel, outdir, rounds, families)
    if do_land:
        land(p, rep, 'sweep')
    return rep
