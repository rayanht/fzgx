"""Register-allocation search: close a body whose only differences are which saved register
holds which local.

MWCC's allocation of non-volatile registers follows the order in which locals are declared
(and, second, where they are declared: a local in an inner block is allocated after the
enclosing block's). The agents cannot see that through the diff, so the search is deterministic:
every permutation of the local declarations (staged: order first, then scope moves and
declaration splits on the best orders, then pairs), compiled in batches, scored by masked
machine words without objdiff. A winner is confirmed by the real oracle before it is returned.

Cost: mwcc ~8 ms per candidate in a batch, 12 batches in parallel; scoring is a word compare.
720 candidates take about a second.
"""

from __future__ import annotations

import itertools
import re
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import oracle
from .project import STATE_DIR, Project

TYPE = (r'(?:(?:register|const|volatile)\s+){0,3}'
        r'(?:(?:unsigned|signed)\s+)?'
        r'(?:(?:long\s+long|long|short)(?:\s+int)?|(?:struct|union|enum)\s+\w+|[A-Za-z_]\w*)'
        r'(?:\s*\*+)?')
DECL_RE = re.compile(r'^\s*(' + TYPE + r')(?:(?<=\*)\s*|\s+)([A-Za-z_]\w*)'
                     r'((?:\[[^\]]*\])*)\s*(?:=\s*([^;]+))?;\s*(?:(?:/\*.*?\*/|//[^\n]*)\s*)?$')
WORKERS = 12


def masked_words(obj: Path, name: str) -> Optional[List[int]]:
    return oracle.words(obj, name)


def score(target: List[int], ours: List[int]) -> Tuple[float, List[Tuple[int, int, int]]]:
    """(percent, [(index, target word, our word)]) for the unequal words."""
    pct, bad = oracle.word_score(target, ours)
    return pct, [(i, target[i], ours[i]) for i in bad if i < len(ours)]


REG_FIELDS = 0x03FFF800  # bits 6..20: rD/rS, rA, rB


def register_only(bad: List[Tuple[int, int, int]]) -> bool:
    """True when every differing word differs only in its register fields."""
    return bool(bad) and all((t & ~REG_FIELDS) == (o & ~REG_FIELDS) for _, t, o in bad)


def _function_body_span(body: str, name: str) -> Optional[Tuple[int, int, int]]:
    m = re.search(rf"\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{", body)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    while i < len(body):
        if body[i] == "{":
            depth += 1
        elif body[i] == "}":
            depth -= 1
            if depth == 0:
                return m.start(), m.end(), i
        i += 1
    return None


def _locals(body: str, span) -> List[Tuple[int, int, str, str, str]]:
    """Leading local declarations, one per line: (start, end, type, name, dims). Declarations
    with initializers count (their text keeps the initializer)."""
    out = []
    for m in re.finditer(r"[^\n]*\n", body[span[1]:span[2]]):
        line = m.group(0)
        s0 = span[1] + m.start()
        if not line.strip():
            continue
        dm = DECL_RE.match(line.rstrip("\n"))
        if not dm:
            break
        out.append((s0, s0 + len(line), dm.group(1), dm.group(2), dm.group(3)))
    return out


def _init_of(line: str) -> Optional[str]:
    dm = DECL_RE.match(line.rstrip("\n"))
    return dm.group(4).strip() if dm and dm.group(4) else None


def _order_ok(locs, lines: List[str], order: Tuple[int, ...]) -> bool:
    """An initializer may only name locals declared before it."""
    placed = set()
    for i in order:
        init = _init_of(lines[i])
        if init and any(re.search(rf"\b{re.escape(locs[j][3])}\b", init) for j in range(len(locs)) if j not in placed and j != i):
            return False
        placed.add(i)
    return True


def split_inits(body: str, name: str) -> List[Tuple[str, str]]:
    """`T x = e;` -> `T x;` ... `x = e;` as the first statement (all at once, and one at a
    time); the reverse for a local whose first statement is a plain assignment."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    if not locs:
        return out
    lines = [body[s:e] for s, e, *_ in locs]
    inits = [(i, _init_of(l)) for i, l in enumerate(lines)]
    with_init = [i for i, e in inits if e]
    indent = re.match(r"\s*", lines[0]).group(0)

    def rebuild(split_idx: List[int]) -> str:
        decls, assigns = [], []
        for i, l in enumerate(lines):
            if i in split_idx:
                dm = DECL_RE.match(l.rstrip("\n"))
                decls.append(f"{indent}{dm.group(1)} {dm.group(2)}{dm.group(3)};\n")
                assigns.append(f"{indent}{dm.group(2)} = {dm.group(4).strip()};\n")
            else:
                decls.append(l)
        return body[:locs[0][0]] + "".join(decls) + "".join(assigns) + body[locs[-1][1]:]

    if with_init:
        out.append(("split all inits", rebuild(with_init)))
        if len(with_init) > 1:
            for i in with_init:
                out.append((f"split init {locs[i][3]}", rebuild([i])))
    # the reverse: the first statements `x = e;` for locals without initializers, folded in
    rest = body[locs[-1][1]:span[2]]
    text = body
    folded = 0
    for i, l in enumerate(lines):
        if _init_of(l):
            continue
        m = re.match(r"\s*\n?(\s*)" + re.escape(locs[i][3]) + r" = ([^;]+);\n", rest)
        if not m:
            break
        dm = DECL_RE.match(l.rstrip("\n"))
        new_line = f"{indent}{dm.group(1)} {dm.group(2)}{dm.group(3)} = {m.group(2)};\n"
        text = text.replace(l, new_line, 1)
        text = text.replace(m.group(0), "\n" if m.group(0).startswith("\n") else "", 1)
        rest = rest[m.end():]
        folded += 1
        out.append((f"fold {folded} inits", text))
    return out


def hoists(body: str, name: str) -> List[Tuple[str, str]]:
    """A local declared in an inner block moved to the top of the function."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    top = locs[-1][1] if locs else span[1] + (1 if body[span[1]] == "\n" else 0)
    names = {l[3] for l in locs}
    for m in re.finditer(r"^([ \t]+)(?:register\s+)?(?:const\s+)?((?:struct\s+\w+\s*\*?|[A-Za-z_]\w*(?:\s*\*)?)\s+([A-Za-z_]\w*)((?:\[[^\]]*\])*))\s*(?:=\s*([^;]+))?;[ \t]*\n", body[top:span[2]], re.M):
        nm = m.group(3)
        if nm in names or nm == name:
            continue
        indent = re.match(r"\s*", body[locs[0][0]:locs[0][1]]).group(0) if locs else "    "
        s0, e0 = top + m.start(), top + m.end()
        decl = f"{indent}{m.group(2)};\n"
        repl = f"{m.group(1)}{nm} = {m.group(5).strip()};\n" if m.group(5) else ""
        text = body[:s0] + repl + body[e0:]
        text = text[:top] + decl + text[top:]
        out.append((f"hoist {nm}", text))
    return out


def through_local(body: str, name: str) -> List[Tuple[str, str]]:
    """`x = A op B;` where A is a load -> `x = A; x = x op B;` (the loaded value is the local's
    own register), and `if (p->f OP k)` -> `t = p->f; if (t OP k)` with a fresh local."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    inner = body[span[1]:span[2]]
    for m in re.finditer(r"^(\s*)([A-Za-z_]\w*) = ([A-Za-z_][\w>.\-\[\]\(\)\* ]*?) (>>|<<|\+|-|&|\||\*) ([^;]+);\n", inner, re.M):
        ind, x, a, op, b = m.groups()
        if x in a or "(" in a and not a.startswith("*("):
            continue
        s0, e0 = span[1] + m.start(), span[1] + m.end()
        out.append((f"through {x}", body[:s0] + f"{ind}{x} = {a};\n{ind}{x} = {x} {op} {b};\n" + body[e0:]))
    if locs:
        top = locs[-1][1]
        indent = re.match(r"\s*", body[locs[0][0]:locs[0][1]]).group(0)
        k = 0
        for m in re.finditer(r"^(\s*)(if|while) \(\(?([A-Za-z_]\w*(?:->|\.)\w+) (==|!=|<|>|<=|>=|&)", inner, re.M):
            if span[1] + m.start() < top:
                continue
            k += 1
            t = f"tmp_ra{k}"
            s0 = span[1] + m.start()
            expr = m.group(3)
            text = body[:s0] + f"{m.group(1)}{t} = {expr};\n" + body[s0:s0 + m.start(3) - m.start()] + t + body[s0 + m.end(3) - m.start():]
            text = text[:top] + f"{indent}s32 {t};\n" + text[top:]
            out.append((f"temp for {expr}", text))
    return out


def rewrites(body: str, name: str) -> List[Tuple[str, str]]:
    """Every single second-stage rewrite of a body."""
    out: List[Tuple[str, str]] = []
    for fn in (scope_moves, split_inits, hoists, through_local, return_values):
        try:
            out += fn(body, name)
        except Exception:
            continue
    return out


def return_values(body: str, name: str) -> List[Tuple[str, str]]:
    """Recover an omitted result when a void draft leaves the value outside r3.

    Tail calls forward their own result; preserving a local across the call would
    create a different live range and hide the actual return convention.
    """
    signature = re.search(rf'\bvoid\s+{re.escape(name)}\s*\(', body)
    span = _function_body_span(body, name)
    if not signature or not span:
        return []
    locals_ = _locals(body, span)
    values = [nm for _, _, ty, nm, dims in locals_ if not dims and
              (ty.strip() in ('u32', 's32', 'int', 'unsigned', 'u16', 's16', 'u8', 's8') or '*' in ty)]
    out = []
    for value in values:
        inner = body[span[1]:span[2]]
        inner = re.sub(r'\breturn\s*;', f'return (u32){value};', inner)
        inner += f'    return (u32){value};\n'
        text = body[:span[1]] + inner + body[span[2]:]
        text = text[:signature.start()] + 'u32' + text[signature.start() + 4:]
        out.append((f'return {value}', text))
        calls = set()
        def forward(match):
            callee = match[2]
            if not re.search(rf'\bextern\s+void\s+{re.escape(callee)}\s*\(', text):
                return match[0]
            calls.add(callee)
            return f'{match[1]}return {callee}({match[3]});'
        inner = re.sub(r'(?m)^([ \t]*)(\w+)\(([^;\n]*)\);(?=\s*})', forward, inner)
        if calls:
            text = body[:span[1]] + inner + body[span[2]:]
            text = text[:signature.start()] + 'u32' + text[signature.start() + 4:]
            for callee in calls:
                text = re.sub(rf'\bextern\s+void(?=\s+{re.escape(callee)}\s*\()', 'extern u32', text)
            out.append((f'return {value}, forward tail calls', text))
    return out


def _orders(n: int, cap: int) -> List[Tuple[int, ...]]:
    ident = tuple(range(n))
    if n <= 6:
        return [q for q in itertools.permutations(range(n)) if q != ident]
    out: List[Tuple[int, ...]] = [tuple(reversed(ident))]
    for i in range(n):
        for j in range(i + 1, n):
            q = list(ident); q[i], q[j] = q[j], q[i]; out.append(tuple(q))
    for i in range(n):  # move one to the front / to the back
        rest = [k for k in ident if k != i]
        out.append(tuple([i] + rest)); out.append(tuple(rest + [i]))
    for k in range(1, n):  # rotations
        out.append(ident[k:] + ident[:k])
    seen, uniq = set(), []
    for q in out:
        if q != ident and q not in seen:
            seen.add(q); uniq.append(q)
    return uniq[:cap]


def reorder(body: str, locs, order: Tuple[int, ...]) -> str:
    lines = [body[s:e] for s, e, *_ in locs]
    return body[:locs[0][0]] + "".join(lines[i] for i in order) + body[locs[-1][1]:]


def scope_moves(body: str, name: str) -> List[Tuple[str, str]]:
    """Each local re-declared in an inner block around its uses; each local split off
    into its own declaration block after a blank line (a second declaration group)."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    if not locs:
        return out
    inner = body[span[1]:span[2]]
    for s, e, typ, nm, dims in locs:
        uses = [span[1] + m.start() for m in re.finditer(rf"\b{re.escape(nm)}\b", inner)]
        uses = [u for u in uses if u >= locs[-1][1]]
        if not uses:
            continue
        line_start = body.rfind("\n", 0, uses[0]) + 1
        line_end = body.find("\n", uses[-1]) + 1
        # only when the use range is a run of whole statements at one nesting depth
        seg = body[line_start:line_end]
        if seg.count("{") != seg.count("}"):
            continue
        decl = body[s:e]
        text = body[:s] + body[e:]
        a, b = line_start - (e - s), line_end - (e - s)
        out.append((f"scope {nm}", text[:a] + "{\n" + decl + text[a:b] + "}\n" + text[b:]))
    return out


def normalise(body: str) -> str:
    """One declarator per line (`u32 a, b;` -> `u32 a;\n u32 b;`), so every family sees every local."""
    lines = []
    for line in body.splitlines(keepends=True):
        # Match only a declaration prefix before splitting declarators. A repeated
        # declaration regex backtracks exponentially on long generated call lines.
        match = re.fullmatch(r'([ \t]+)(struct[ \t]+\w+|[A-Za-z_]\w*)[ \t]+([^;]+);[ \t]*(\n?)', line)
        if match and ',' in match[3]:
            decls = match[3].split(',')
            if all(re.fullmatch(r'\*?\s*[A-Za-z_]\w*(?:\[[^\]]*\])*\s*', decl) for decl in decls):
                lines.append('\n'.join(f'{match[1]}{match[2]} {decl.strip()};' for decl in decls) + match[4])
                continue
        lines.append(line)
    return ''.join(lines)


def search(p: Project, symbol: str, body: str, budget_s: float = 8.0, max_orders: int = 720,
           top_k: int = 6, workers: int = WORKERS, mw_version: Optional[str] = None,
           extra_cflags: Optional[str] = None) -> Dict[str, object]:
    """Returns {"matched", "body", "tried", "best", "secs", "stage", "label"}."""
    t0 = time.time()
    body = normalise(body)
    sym = p.resolve(symbol)
    out: Dict[str, object] = {"matched": False, "body": None, "tried": 0, "best": 0.0, "secs": 0.0, "stage": None, "label": None}
    if sym is None:
        return out
    target = p.target_object_for(sym)
    if target is None:
        return out
    tw = masked_words(target, sym.name)
    if not tw:
        return out
    key = p.key(sym).replace(":", "__")
    root = STATE_DIR / "regalloc" / key
    root.mkdir(parents=True, exist_ok=True)
    base_src = root / "base.c"; base_src.write_text(body)
    mw, extra = oracle.version_for(p, sym, base_src)
    if mw_version:
        mw = mw_version
    if extra_cflags is not None:
        extra = extra_cflags

    def evaluate(texts: List[str]) -> List[Optional[Tuple[float, List[Tuple[int, int, int]]]]]:
        """Batched compile in parallel, masked-word score each; None when it did not compile."""
        n = len(texts)
        if n == 0:
            return []
        per = max(8, (n + workers - 1) // workers)
        chunks = [list(range(i, min(i + per, n))) for i in range(0, n, per)]

        def run(ci: int):
            d = root / f"b{ci}"
            d.mkdir(exist_ok=True)
            for old in d.glob("*.c"):
                old.unlink()
            srcs = []
            for j in chunks[ci]:
                f = d / f"c{j}.c"; f.write_text(texts[j]); srcs.append((j, f))
            objs = oracle.compile_many(p, sym.module, [f for _, f in srcs], d / "obj", mw, extra)
            res = {}
            for j, f in srcs:
                o = objs.get(f)
                ow = masked_words(o, sym.name) if o else None
                res[j] = score(tw, ow) if ow else None
            return res

        results: List[Optional[Tuple[float, list]]] = [None] * n
        if len(chunks) == 1:
            for j, r in run(0).items():
                results[j] = r
            return results
        with ThreadPoolExecutor(max_workers=workers) as ex:
            for part in ex.map(run, range(len(chunks))):
                for j, r in part.items():
                    results[j] = r
        return results

    def confirm(text: str) -> bool:
        scratch = root / "winner.c"
        scratch.write_text(text)
        res = oracle.check(p, symbol, 0, source=scratch, mw_version=mw, extra_cflags=extra)
        return bool(res.ok and (res.matched or res.matched_pool))

    base = evaluate([body])[0]
    if base is None:
        out["error"] = "base does not compile"
        return out
    out["best"] = base[0]
    if not base[1]:
        if confirm(body):
            out.update(matched=True, body=body, stage="base")
        return out
    out["register_only"] = register_only(base[1])
    span = _function_body_span(body, sym.name)
    if not span:
        return out
    locs = _locals(body, span)
    best_text, best_pct = body, base[0]
    tried = 0
    # stage 1: declaration order
    stage1: List[Tuple[str, str]] = []
    if len(locs) >= 2:
        lines = [body[s_:e_] for s_, e_, *_ in locs]
        stage1 = [("order " + ",".join(locs[i][3] for i in q), reorder(body, locs, q)) for q in _orders(len(locs), max_orders) if _order_ok(locs, lines, q)]
    ranked: List[Tuple[float, str, str]] = [(base[0], "base", body)]
    for stage, cands in (("order", stage1),):
        if not cands or time.time() - t0 > budget_s:
            break
        res = evaluate([t for _, t in cands])
        tried += len(cands)
        for (label, text), r in zip(cands, res):
            if r is None:
                continue
            pct, bad = r
            ranked.append((pct, label, text))
            if not bad and confirm(text):
                out.update(matched=True, body=text, tried=tried, best=100.0, stage=stage, label=label, secs=round(time.time() - t0, 2))
                return out
            if pct > best_pct:
                best_pct, best_text = pct, text; out["label"] = label
    # stage 2: every rewrite family on the best orders (the base included)
    ranked.sort(key=lambda x: -x[0])
    seen = set()
    stage2: List[Tuple[str, str]] = []
    for pct, label, text in ranked[:top_k]:
        for l2, t2 in rewrites(text, sym.name):
            if t2 not in seen:
                seen.add(t2); stage2.append((f"{label} + {l2}", t2))
    if stage2 and time.time() - t0 < budget_s:
        res = evaluate([t for _, t in stage2])
        tried += len(stage2)
        keepers: List[Tuple[float, str, str]] = []
        for (label, text), r in zip(stage2, res):
            if r is None:
                continue
            pct, bad = r
            if not bad and confirm(text):
                out.update(matched=True, body=text, tried=tried, best=100.0, stage="scope", label=label, secs=round(time.time() - t0, 2))
                return out
            if pct > best_pct:
                best_pct, best_text = pct, text; out["label"] = label
            if pct >= base[0]:
                keepers.append((pct, label, text))
        # stage 3: a second rewrite on the best stage-2 results
        keepers.sort(key=lambda x: -x[0])
        stage3: List[Tuple[str, str]] = []
        for pct, label, text in keepers[:top_k]:
            for l3, t3 in rewrites(text, sym.name):
                if t3 not in seen:
                    seen.add(t3); stage3.append((f"{label} + {l3}", t3))
        if stage3 and time.time() - t0 < budget_s:
            res = evaluate([t for _, t in stage3])
            tried += len(stage3)
            for (label, text), r in zip(stage3, res):
                if r is None:
                    continue
                pct, bad = r
                if not bad and confirm(text):
                    out.update(matched=True, body=text, tried=tried, best=100.0, stage="scope2", label=label, secs=round(time.time() - t0, 2))
                    return out
                if pct > best_pct:
                    best_pct, best_text = pct, text; out["label"] = label
    out.update(tried=tried, best=best_pct, body=best_text if best_pct > base[0] else None, secs=round(time.time() - t0, 2))
    return out


def run(p: Project, min_pct: float = 90.0, limit: int = 2000, submit: bool = True) -> Dict[str, object]:
    """Every plateaued attempt and lifter draft at min_pct or better through the search;
    matches are submitted in the name `regalloc`. Serial over bodies (each search is
    already 12-wide), a quarter of a second per body."""
    from . import lab
    t0 = time.time()
    items = lab.corpus(p, min_pct, limit)
    matched: List[Tuple[str, str]] = []
    improved = 0
    tried = 0
    # bodies in parallel, each search single-threaded: a body's candidate sets are small, so
    # the parallelism is across bodies (one mwcc process per stage per body)
    with ThreadPoolExecutor(max_workers=WORKERS) as ex:
        searched = list(ex.map(lambda it: (it, search(p, it[0], it[1], budget_s=8.0, workers=1)), items))
    for (s, body, pct, kind), res in searched:
        tried += res.get("tried", 0)
        if res.get("matched") and res.get("body"):
            label = f"{res.get('stage')}: {res.get('label')}"
            if submit:
                from . import api
                sym = p.resolve(s)
                work = p.work_path(s if ":" in s else p.key(sym)); work.parent.mkdir(parents=True, exist_ok=True)
                work.write_text(res["body"])
                sr = api.submit(p, s, agent="regalloc", message=f"regalloc {label}", harness="fzgx", model="regalloc")
                if sr.get("ok"):
                    matched.append((s, label))
            else:
                matched.append((s, label))
        elif res.get("body"):
            improved += 1
    return {"bodies": len(items), "matched": matched, "improved": improved, "candidates": tried, "secs": round(time.time() - t0, 1)}
