"""The spelling search: a body whose structure is right (the lifter's calls, layouts and loops
come from retail) and whose spelling is wrong is closed by search, not by hand.

Every single-step rewrite the lab, the regalloc search and a few families here can make is
a candidate; a beam search keeps the best few texts at every level and rewrites them again.
Candidates are compiled in batches and scored by masked machine words with an alignment
(a fix that shifts every later instruction still counts as progress); a candidate with no
difference left is confirmed by the retail oracle before it is reported. Cost is a few
milliseconds a candidate, so a body gets hundreds of them in seconds.
"""

from __future__ import annotations

import difflib
import json
import re
import time
from concurrent.futures import ThreadPoolExecutor
from typing import Dict, List, Optional, Tuple

from . import lab, oracle, regalloc
from .project import STATE_DIR, Project

# which rewrite families the objdiff row kinds of a diff point at (fixup's targeting)
KIND_FAMILIES = {
    "regalloc": ("decl-order", "inner-scope", "regalloc", "inline-temp", "repeat-to-local", "stmt-swap", "commute", "ptr-local"),
    "ins": ("inline-temp", "inner-scope", "void-return", "return-to-block", "local-type", "hoist-arg", "repeat-to-local"),
    "ins:ext": ("local-type", "param-type", "field-type", "compare-cast"),
    "ins:cmp": ("compare-cast", "local-type", "compare-form"),
    "op": ("local-type", "compare-cast", "field-type", "param-type"),
    "op:cmpw/cmplw": ("compare-cast", "local-type"), "op:cmplw/cmpw": ("compare-cast", "local-type"),
    "op:cmpwi/cmplwi": ("compare-cast", "local-type"), "op:cmplwi/cmpwi": ("compare-cast", "local-type"),
    "reloc": ("near-far", "address-form", "ptr-local"),
    "imm": ("struct-pad", "field-type"),
    "frame": ("decl-order", "inner-scope", "hoist-arg"),
    "schedule": ("stmt-swap", "commute", "inline-temp", "decl-order"),
}
BEAM = 4
LEVELS = 4
MAX_CANDIDATES = 700
FIELD_FLIP = {"u16": "s16", "s16": "u16", "u8": "s8", "s8": "u8", "u32": "s32", "s32": "u32"}


def _fn_span(body: str, name: str):
    return regalloc._function_body_span(body, name)


def extra_families(body: str, name: str) -> List[Tuple[str, str, str]]:
    """(family, label, text): near/far externs, pointer locals for globals, field signedness,
    loop direction, compare casts, call-result temps."""
    out: List[Tuple[str, str, str]] = []
    span = _fn_span(body, name)
    if not span:
        return out
    # 1. near <-> far: a scalar extern becomes an unknown-size array (far) or back
    for m in re.finditer(r"^extern ((?:struct \w+|[us](?:8|16|32)|f32|f64)) ([A-Za-z_]\w*);$", body, re.M):
        t, g = m.groups()
        text = body[:m.start()] + f"extern {t} {g}[];" + body[m.end():]
        if t.startswith("struct"):
            text = re.sub(rf"(?<![\w>.]){re.escape(g)}\.unk_", f"{g}[0].unk_", text)
        else:
            text = re.sub(rf"(?<![\w>.&]){re.escape(g)}\b(?!\s*\[|\s*=\s*\()", f"{g}[0]", text)
        out.append(("near-far", f"{g} far", text))
    for m in re.finditer(r"^extern ((?:struct \w+|[us](?:8|16|32)|f32|f64)) ([A-Za-z_]\w*)\[\];$", body, re.M):
        t, g = m.groups()
        text = body[:m.start()] + f"extern {t} {g};" + body[m.end():]
        text = text.replace(f"{g}[0]", g)
        out.append(("near-far", f"{g} near", text))
    # 2. a global struct accessed several times through a pointer local
    inner = body[span[1]:span[2]]
    for m in re.finditer(r"^extern struct (\w+) ([A-Za-z_]\w*)(\[\])?;$", body, re.M):
        st, g, arr = m.groups()
        uses = re.findall(rf"(?<![\w>.]){re.escape(g)}(?:\[0\])?\.unk_", inner)
        if len(uses) < 2 or f"p_{g}" in body:
            continue
        acc = f"{g}[0].unk_" if arr else f"{g}.unk_"
        new_inner = inner.replace(acc, f"p_{g}->unk_")
        # the assignment goes before the first statement; the declaration with the locals
        first_stmt = re.search(r"\n(\s*)(?![A-Za-z_][\w ]*\*?\s*[A-Za-z_]\w*(\[[^\]]*\])*;\n)([^\n]*;)", new_inner)
        if not first_stmt:
            continue
        at = first_stmt.start(3)
        new_inner = new_inner[:at] + f"p_{g} = (struct {st} *)&{g};\n    " + new_inner[at:]
        new_inner = f"\n    struct {st} *p_{g};" + new_inner
        out.append(("ptr-local", f"pointer local for {g}", body[:span[1]] + new_inner + body[span[2]:]))
    # 3. field signedness in block-private structs
    for m in re.finditer(r"^(    )([us](?:8|16|32)) (unk_[0-9A-F]+)(\[[^\]]*\])?;$", body, re.M):
        t = m.group(2)
        out.append(("field-type", f"{m.group(3)}: {t}->{FIELD_FLIP[t]}", body[:m.start(2)] + FIELD_FLIP[t] + body[m.end(2):]))
    # 4. counted loop direction
    for m in re.finditer(r"for \((\w+) = ([^;]+); \1 != 0; \1--\)", body):
        v, n = m.groups()
        out.append(("loop-form", "count down -> up", body[:m.start()] + f"for ({v} = 0; {v} < {n}; {v}++)" + body[m.end():]))
    for m in re.finditer(r"for \((\w+) = 0; \1 < ([^;]+); \1\+\+\)", body):
        v, n = m.groups()
        out.append(("loop-form", "count up -> down", body[:m.start()] + f"for ({v} = {n}; {v} != 0; {v}--)" + body[m.end():]))
    # 5. compare casts: drop or flip the cast on a compare operand
    for m in re.finditer(r"\((s32|u32)\)([A-Za-z_][\w>.\-\[\]]*) (==|!=|<|>|<=|>=)", inner):
        s0 = span[1] + m.start(); e0 = span[1] + m.end()
        other = "u32" if m.group(1) == "s32" else "s32"
        out.append(("compare-cast", f"drop ({m.group(1)}) on {m.group(2)}", body[:s0] + f"{m.group(2)} {m.group(3)}" + body[e0:]))
        out.append(("compare-cast", f"({m.group(1)})->({other}) on {m.group(2)}", body[:s0] + f"({other}){m.group(2)} {m.group(3)}" + body[e0:]))
    # 6. a returned parameter or constant on a function whose r3 is scratch: a void function
    ret = re.search(r"^(\s*)return ((?:arg\d+|v\d+|-?\d+|0x[0-9A-Fa-f]+));\n\}\s*$", body, re.M)
    if ret:
        sig = re.search(rf"^(u32|s32|s16|u16|s8|u8)( {re.escape(name)}\()", body, re.M)
        if sig:
            text = body[:sig.start(1)] + "void" + body[sig.end(1):]
            text = text.replace(ret.group(0), "}\n", 1)
            out.append(("void-return", "drop the returned value", text))
    # 7. an early return is the source's if-block around the tail: `if (c) { return; } S` -> `if (!c) { S }`
    for m in re.finditer(r"^(\s*)if \((.+?)\) \{ return; \}[^\n]*\n", inner, re.M):
        cond = m.group(2)
        tail = inner[m.end():]
        close = tail.rfind("\n")
        stmts_tail = tail[:close] if close >= 0 else tail
        if "{" in stmts_tail or "}" in stmts_tail or "return" in stmts_tail or not stmts_tail.strip():
            continue
        inv = {"==": "!=", "!=": "==", "<": ">=", ">": "<=", "<=": ">", ">=": "<"}
        mm = re.fullmatch(r"(.+?) (==|!=|<|>|<=|>=) (.+)", cond)
        ncond = f"{mm.group(1)} {inv[mm.group(2)]} {mm.group(3)}" if mm else f"!({cond})"
        new_inner = inner[:m.start()] + f"{m.group(1)}if ({ncond}) {{\n" + stmts_tail + f"\n{m.group(1)}}}" + tail[close:]
        out.append(("return-to-block", "early return -> if block", body[:span[1]] + new_inner + body[span[2]:]))
    # 8a. a call assigned to a field or global goes through a local first (the scheduler places
    #     the store differently when the value has a home)
    for m in re.finditer(r"^(\s*)([A-Za-z_][\w>.\-\[\]]*) = ([A-Za-z_]\w*\([^;]*\));\n", inner, re.M):
        ind, lhs, call = m.groups()
        if re.fullmatch(r"[A-Za-z_]\w*", lhs) and not re.search(rf"(?:->|\.)", lhs):
            continue  # already a plain local
        decl_at = regalloc._locals(body, span)
        ins_at = decl_at[-1][1] if decl_at else span[1] + 1
        new_inner = inner[:m.start()] + f"{ind}spell_call = {call};\n{ind}{lhs} = spell_call;\n" + inner[m.end():]
        text = body[:span[1]] + new_inner + body[span[2]:]
        text = text[:ins_at] + "    u32 spell_call;\n" + text[ins_at:]
        out.append(("call-to-local", f"local for {call[:30]}", text))
    # 8. a temporary for a call result used once: inline it
    for m in re.finditer(r"^(\s*)(t\d+) = ([A-Za-z_]\w*\([^;]*\));\n", inner, re.M):
        tn, call = m.group(2), m.group(3)
        rest = inner[m.end():]
        if len(re.findall(rf"\b{tn}\b", rest)) == 1:
            new_inner = inner[:m.start()] + re.sub(rf"\b{tn}\b", call, rest, count=1)
            out.append(("inline-call", f"inline {tn}", body[:span[1]] + new_inner + body[span[2]:]))
    return out


def all_rewrites(body: str, name: str, max_per_family: int = 16) -> List[Tuple[str, str, str]]:
    """Every single-step rewrite, at most `max_per_family` of any one family (the declaration
    permutations alone would be a hundred; the regalloc search covers them for near matches)."""
    out: List[Tuple[str, str, str]] = []
    for fn in (lambda b, n: lab.perturbations(b, n),
               lambda b, n: [("regalloc", l, t) for l, t in regalloc.rewrites(b, n)],
               extra_families):
        try:
            out += fn(body, name)
        except Exception:
            continue
    counts: Dict[str, int] = {}
    kept = []
    by_fam: Dict[str, List[str]] = {}
    for fam, label, text in out:
        counts[fam] = counts.get(fam, 0) + 1
        by_fam.setdefault(fam, []).append(text)
        if counts[fam] <= max_per_family:
            kept.append((fam, label, text))
    # every edit of a family applied together (the same fix at every site): the composition of
    # the per-site texts when their edits do not overlap
    for fam, texts in by_fam.items():
        if len(texts) < 2 or fam in ("decl-order", "regalloc", "param-count", "struct-pad"):
            continue
        base_lines = body.splitlines(keepends=True)
        merged = list(base_lines); ok = True; touched: set = set()
        for t in texts[:24]:
            sm = difflib.SequenceMatcher(None, base_lines, t.splitlines(keepends=True), autojunk=False)
            ops = [(tag, i1, i2, j1, j2) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal"]
            if any(set(range(i1, max(i2, i1 + 1))) & touched for _, i1, i2, _, _ in ops):
                continue
            tl = t.splitlines(keepends=True)
            for tag, i1, i2, j1, j2 in reversed(ops):
                merged[i1:i2] = tl[j1:j2]
                touched.update(range(i1, max(i2, i1 + 1)))
        text = "".join(merged)
        if text != body and text not in texts:
            kept.append((fam, f"{fam} at every site", text))
    return kept


def fitness(tw: List[int], ow: List[int]) -> Tuple[float, float]:
    """(aligned matched words as a percent, positional percent)."""
    if not tw or not ow:
        return (0.0, 0.0)
    sm = difflib.SequenceMatcher(None, tw, ow, autojunk=False)
    matched = sum(b.size for b in sm.get_matching_blocks())
    n = max(len(tw), len(ow))
    pos, _ = oracle.word_score(tw, ow)
    return (100.0 * matched / n, pos)


def search(p: Project, symbol: str, body: str, budget_s: float = 10.0, beam: int = BEAM, levels: int = LEVELS,
           max_candidates: int = MAX_CANDIDATES) -> Dict[str, object]:
    t0 = time.time()
    sym = p.resolve(symbol)
    out: Dict[str, object] = {"matched": False, "body": None, "tried": 0, "base": 0.0, "best": 0.0, "path": [], "secs": 0.0}
    if sym is None:
        return out
    target = p.target_object_for(sym)
    if target is None:
        return out
    tw = oracle.words(target, sym.name)
    if not tw:
        return out
    key = p.key(sym).replace(":", "__")
    root = STATE_DIR / "spell" / key
    root.mkdir(parents=True, exist_ok=True)
    base_src = root / "base.c"; base_src.write_text(body)
    mw, extra = oracle.version_for(p, sym, base_src)
    seen: Dict[str, Tuple[float, float]] = {}

    def evaluate(texts: List[str]) -> List[Optional[Tuple[float, float]]]:
        d = root / "b"
        d.mkdir(exist_ok=True)
        for old in d.glob("*.c"):
            old.unlink()
        srcs = []
        for j, text in enumerate(texts):
            f = d / f"c{j}.c"; f.write_text(text); srcs.append(f)
        objs = oracle.compile_many(p, sym.module, srcs, d / "obj", mw, extra)
        res: List[Optional[Tuple[float, float]]] = []
        for f in srcs:
            o = objs.get(f)
            ow = oracle.words(o, sym.name) if o else None
            res.append(fitness(tw, ow) if ow else None)
        return res

    def confirm(text: str) -> bool:
        w = root / "winner.c"; w.write_text(text)
        r = oracle.check(p, symbol, 0, source=w, mw_version=mw)
        return bool(r.ok and (r.matched or r.matched_pool) and oracle.unit_fully_matches(r) is None)

    base_fit = evaluate([body])[0]
    if base_fit is None:
        out["error"] = "base does not compile"
        return out
    # the objdiff rows of the base, once: their kinds say which families are likely
    weights: Dict[str, float] = {}
    try:
        from . import stuck  # scoped: stuck imports oracle; kept local to this optional seeding
        o0 = root / "b" / "obj" / "c0.o"
        rows = oracle.function_rows(p, sym.name, target, o0) if o0.exists() else None
        if rows:
            kinds = {k for k in stuck.row_kinds(rows[0], rows[1]) if k}
            for k in kinds:
                for fam in KIND_FAMILIES.get(k.split(":")[0], ()):
                    weights[fam] = weights.get(fam, 0) + 1
                for fam in KIND_FAMILIES.get(k, ()):
                    weights[fam] = weights.get(fam, 0) + 2
    except Exception:
        weights = {}
    out["base"] = base_fit[1]
    seen[body] = base_fit
    if base_fit[1] >= 100.0 and confirm(body):
        out.update(matched=True, body=body, best=100.0)
        return out
    frontier: List[Tuple[Tuple[float, float], str, List[str]]] = [(base_fit, body, [])]
    best = (base_fit, body, [])
    tried = 0
    for _level in range(levels):
        if time.time() - t0 > budget_s or tried >= max_candidates:
            break
        cands: List[Tuple[str, List[str]]] = []
        for fit, text, path in frontier:
            for fam, label, t2 in all_rewrites(text, sym.name):
                if t2 in seen or t2 == text:
                    continue
                seen[t2] = (-1.0, -1.0)
                cands.append((t2, path + [f"{fam}: {label}"]))
                if len(cands) >= max_candidates - tried:
                    break
            if len(cands) >= max_candidates - tried:
                break
        if not cands:
            break
        if weights:
            # the families the diff rows point at first: a budget cut keeps the likely ones
            cands.sort(key=lambda c: -weights.get(c[1][-1].split(":")[0], 0))
        res = evaluate([t for t, _ in cands])
        tried += len(cands)
        scored: List[Tuple[Tuple[float, float], str, List[str]]] = []
        for (text, path), r in zip(cands, res):
            if r is None:
                continue
            seen[text] = r
            scored.append((r, text, path))
            if r[1] >= 100.0 and confirm(text):
                out.update(matched=True, body=text, best=100.0, tried=tried, path=path, secs=round(time.time() - t0, 2))
                return out
        scored.sort(key=lambda x: (-x[0][0], -x[0][1]))
        if scored and scored[0][0] > best[0]:
            best = scored[0]
        # the beam: the best few at or above the base (no drifting down)
        frontier = [x for x in scored[:beam] if x[0] >= base_fit]
        if not frontier:
            break
    out.update(tried=tried, best=best[0][1], body=best[1] if best[1] != body else None, path=best[2],
               aligned=best[0][0], secs=round(time.time() - t0, 2))
    if best[1] != body:
        (root / "best.c").write_text(best[1])  # the next round starts here
    return out


def run_drafts(p: Project, min_pct: float = 0.0, max_pct: float = 100.0, limit: int = 5000, workers: int = 3,
               budget_s: float = 10.0, submit: bool = True, only: Optional[List[str]] = None) -> Dict[str, object]:
    """The search over the lifter's current drafts (.fzgx/draftscan): every draft that compiles
    and scores in [min_pct, max_pct). A draft the last round improved starts from that body.
    Matches are submitted as `spell`."""
    d = STATE_DIR / "draftscan"
    scores = json.loads((d / "scores.json").read_text())
    items = []
    for s, m, size, pct, k in scores:
        if pct < 0 or pct >= 100 or pct < min_pct or pct >= max_pct:
            continue
        if only and s not in only:
            continue
        sym = p.resolve(s)
        if sym is None or p.unit_of(sym):
            continue
        f = d / f"{m}__{s}.c"
        best = STATE_DIR / "spell" / p.key(sym).replace(":", "__") / "best.c"
        src = best if best.exists() and best.stat().st_mtime >= f.stat().st_mtime else f
        if f.exists():
            items.append((s, m, size, pct, src.read_text()))
    items.sort(key=lambda x: -x[3])
    return run_bodies(p, items[:limit], workers, budget_s, submit, agent="spell")


def run_attempts(p: Project, min_pct: float = 60.0, limit: int = 5000, workers: int = 3, budget_s: float = 10.0,
                 submit: bool = True, module: Optional[str] = None) -> Dict[str, object]:
    """The search over the agents' saved plateau bodies (the ledger's best attempts)."""
    import sqlite3  # scoped: only this reader touches the ledger directly
    db = sqlite3.connect(str(STATE_DIR / "ledger.db"))
    q = ("select f.symbol, f.module, f.size, a.best_body_path, max(a.best_in_attempt) from functions f join attempts a on a.symbol=f.symbol "
         "where f.status='unmatched' and a.best_body_path is not null and a.best_in_attempt>=?" + (" and f.module=?" if module else "") + " group by f.symbol order by 5 desc")
    rows = db.execute(q, [min_pct] + ([module] if module else [])).fetchall()
    items = []
    from pathlib import Path  # scoped: a single path test
    for s, m, size, path, pct in rows:
        if path and Path(path).exists():
            items.append((s, m, size, pct or 0.0, Path(path).read_text()))
    return run_bodies(p, items[:limit], workers, budget_s, submit, agent="spell")


def _env_digest() -> str:
    import hashlib  # scoped: one digest
    from .project import ROOT  # scoped: same
    h = hashlib.sha256()
    for f in sorted((ROOT / "include").rglob("*.h")):
        h.update(f.read_bytes())
    for f in ("spell.py", "lab.py", "regalloc.py", "oracle.py"):
        h.update((ROOT / "tools" / "fzgx" / f).read_bytes())
    return h.hexdigest()[:16]


class _Body:
    """One body's search state in the lockstep run."""
    def __init__(self, p: Project, s: str, m: str, size: int, pct: float, text: str):
        self.symbol, self.module, self.size, self.pct, self.text = s, m, size, pct, text
        self.sym = p.resolve(s)
        self.target = p.target_object_for(self.sym) if self.sym else None
        self.tw = oracle.words(self.target, self.sym.name) if self.target else None
        self.root = STATE_DIR / "spell" / p.key(self.sym).replace(":", "__")
        self.root.mkdir(parents=True, exist_ok=True)
        (self.root / "base.c").write_text(text)
        self.mw, self.extra = (None, None)  # decided for every body at once (see _pick_versions)
        self.seen: Dict[str, Tuple[float, float]] = {}
        self.frontier: List[Tuple[Tuple[float, float], str, List[str]]] = []
        self.best: Optional[Tuple[Tuple[float, float], str, List[str]]] = None
        self.base_fit: Optional[Tuple[float, float]] = None
        self.tried = 0
        self.weights: Dict[str, float] = {}
        self.done = False
        self.matched: Optional[Tuple[str, List[str]]] = None
        self.error: Optional[str] = None

    def candidates(self, cap: int) -> List[Tuple[str, List[str]]]:
        cands: List[Tuple[str, List[str]]] = []
        for fit, text, path in self.frontier:
            for fam, label, t2 in all_rewrites(text, self.sym.name):
                if t2 in self.seen or t2 == text:
                    continue
                self.seen[t2] = (-1.0, -1.0)
                cands.append((t2, path + [f"{fam}: {label}"]))
        if self.weights:
            cands.sort(key=lambda c: -self.weights.get(c[1][-1].split(":")[0], 0))
        return cands[:cap]


def run_bodies(p: Project, items, workers: int = 3, budget_s: float = 10.0, submit: bool = True, agent: str = "spell",
               levels: int = LEVELS, beam: int = 3, cap: int = 120, cap_later: int = 60) -> Dict[str, object]:
    """The search over many bodies in lockstep: every body's candidates of a level are compiled
    together (a few hundred files per compiler process instead of a few dozen), scored, and the
    beams advance together. Bodies searched before under the same headers and tooling with no
    match are skipped (.fzgx/spell/memo.json)."""
    import hashlib  # scoped: memo keys
    from . import api, stuck  # scoped: api imports the search modules; importing it at load would be a cycle
    t0 = time.time()
    env = _env_digest()
    memo_path = STATE_DIR / "spell" / "memo.json"
    try:
        memo: Dict[str, dict] = json.loads(memo_path.read_text()) if memo_path.exists() else {}
    except ValueError:
        memo = {}
    bodies: List[_Body] = []
    skipped = 0
    for s, m, size, pct, text in items:
        key = f"{env}:{hashlib.sha256(text.encode()).hexdigest()[:24]}"
        if key in memo and not memo[key].get("matched"):
            skipped += 1; continue
        b = _Body(p, s, m, size, pct, text)
        b.memo_key = key
        if b.sym is None or b.tw is None or p.unit_of(b.sym):
            continue
        bodies.append(b)

    CHUNK = 240

    def _pick_versions(bs: List[_Body]) -> None:
        """Each body's compiler version: the unit's when carved, else the best of the module's
        candidates for its base text, one batched compile per candidate version."""
        by_mod: Dict[str, List[_Body]] = {}
        for b in bs:
            cands = oracle.version_candidates(p, b.module)
            if len(cands) == 1:
                b.mw, b.extra = (None, None); continue
            by_mod.setdefault(b.module, []).append(b)
        for module, members in by_mod.items():
            cands = oracle.version_candidates(p, module)
            d = STATE_DIR / "spell" / "_ver" / module
            d.mkdir(parents=True, exist_ok=True)
            srcs = []
            for j, b in enumerate(members):
                f = d / f"v{j}.c"; f.write_text(b.text); srcs.append(f)
            per = {}
            for c in cands:
                vd = d / (c[0].replace("/", "_") + ("_stmw" if c[1] else ""))
                if vd.exists():
                    for old in vd.glob("*.o"):
                        old.unlink()
                per[c] = oracle.compile_many(p, module, srcs, vd, c[0], c[1])
            for b, f in zip(members, srcs):
                best = None
                for c in cands:
                    o = per[c].get(f)
                    ow = oracle.words(o, b.sym.name) if o else None
                    pct = oracle.word_score(b.tw, ow)[0] if ow else -1.0
                    if best is None or pct > best[0]:
                        best = (pct, c)
                b.mw, b.extra = best[1] if best else (None, None)

    def compile_score(groups: Dict[tuple, List[Tuple[_Body, str, List[str]]]]) -> None:
        """Every body's candidates of a level, in chunks of CHUNK files, each chunk in a fresh
        directory (mwcc under wibo slows 16x in a directory of thousands of files), 12 at a time."""
        jobs = []
        for (module, mw, extra), members in groups.items():
            for ci in range(0, len(members), CHUNK):
                jobs.append((module, mw, extra, members[ci:ci + CHUNK], len(jobs)))

        def run(job):
            module, mw, extra, members, k = job
            d = STATE_DIR / "spell" / "_batch" / f"k{k}"
            d.mkdir(parents=True, exist_ok=True)
            for old in list(d.glob("*.c")) + list((d / "obj").glob("*.o")) if (d / "obj").exists() else list(d.glob("*.c")):
                old.unlink()
            srcs = []
            for j, (b, text, path) in enumerate(members):
                f = d / f"c{j}.c"; f.write_text(text); srcs.append(f)
            objs = oracle.compile_many(p, module, srcs, d / "obj", mw, extra)
            out_ = []
            for (b, text, path), f in zip(members, srcs):
                o = objs.get(f)
                ow = oracle.words(o, b.sym.name) if o else None
                out_.append((b, text, path, f, fitness(b.tw, ow) if ow else None))
            return out_

        with ThreadPoolExecutor(max_workers=12) as ex:
            for part in ex.map(run, jobs):
                for b, text, path, f, fit in part:
                    b.seen[text] = fit if fit else (-1.0, -1.0)
                    b.results.append((fit, text, path, f))

    _pick_versions(bodies)
    # level 0: every base, one compile
    for b in bodies:
        b.results = []
    groups: Dict[tuple, List[Tuple[_Body, str, List[str]]]] = {}
    for b in bodies:
        groups.setdefault((b.module, b.mw, b.extra), []).append((b, b.text, []))
    compile_score(groups)
    for b in bodies:
        fit = b.results[0][0] if b.results else None
        if fit is None:
            b.error = "base does not compile"; b.done = True; continue
        b.base_fit = fit; b.best = (fit, b.text, []); b.frontier = [(fit, b.text, [])]
        # the diff rows of the base: which families are likely
        try:
            o0 = b.results[0][3].with_suffix(".o").parent / "obj" / b.results[0][3].with_suffix(".o").name
            rows = oracle.function_rows(p, b.sym.name, b.target, o0) if o0.exists() else None
            if rows:
                for k in {k for k in stuck.row_kinds(rows[0], rows[1]) if k}:
                    for fam in KIND_FAMILIES.get(k.split(":")[0], ()):
                        b.weights[fam] = b.weights.get(fam, 0) + 1
                    for fam in KIND_FAMILIES.get(k, ()):
                        b.weights[fam] = b.weights.get(fam, 0) + 2
        except Exception:
            pass
    matched: List[Tuple[str, float, List[str]]] = []

    def confirm_and_submit(b: _Body, text: str, path: List[str]) -> None:
        w = b.root / "winner.c"; w.write_text(text)
        r = oracle.check(p, b.symbol, 0, source=w, mw_version=b.mw)
        if not (r.ok and (r.matched or r.matched_pool) and oracle.unit_fully_matches(r) is None):
            return
        b.matched = (text, path); b.done = True
        if submit:
            work = p.work_path(p.key(b.sym)); work.parent.mkdir(parents=True, exist_ok=True); work.write_text(text)
            sr = api.submit(p, b.symbol, agent=agent, message="spelling search: " + " + ".join(path)[:200], harness="fzgx", model="spell")
            if not sr.get("ok"):
                return
        matched.append((b.symbol, b.pct, path))

    for level in range(levels):
        active = [b for b in bodies if not b.done]
        if not active:
            break
        groups = {}
        for b in active:
            b.results = []
            for text, path in b.candidates(cap if level == 0 else cap_later):
                groups.setdefault((b.module, b.mw, b.extra), []).append((b, text, path))
        n = sum(len(v) for v in groups.values())
        if n == 0:
            break
        tl = time.time()
        compile_score(groups)
        print(f"  spell level {level + 1}: {len(active)} bodies, {n} candidates, {time.time() - tl:.1f}s", flush=True)
        for b in active:
            scored = [(fit, text, path) for fit, text, path, _ in b.results if fit is not None]
            b.tried += len(b.results)
            for fit, text, path in scored:
                if fit[1] >= 100.0 and not b.done:
                    confirm_and_submit(b, text, path)
            if b.done:
                continue
            scored.sort(key=lambda x: (-x[0][0], -x[0][1]))
            if scored and scored[0][0] > b.best[0]:
                b.best = scored[0]
            b.frontier = [x for x in scored[:beam] if x[0] >= b.base_fit]
            if not b.frontier:
                b.done = True
    improved = 0; tried = 0
    families: Dict[str, int] = {}
    results = []
    for b in bodies:
        tried += b.tried
        if b.matched:
            for step in b.matched[1]:
                fam = step.split(":")[0]; families[fam] = families.get(fam, 0) + 1
        elif b.best and b.best[1] != b.text:
            improved += 1
            (b.root / "best.c").write_text(b.best[1])
        memo[b.memo_key] = {"matched": bool(b.matched), "best": b.best[0][1] if b.best else None}
        results.append((b.symbol, b.module, b.size, b.pct, {"matched": bool(b.matched), "best": b.best[0][1] if b.best else None,
                                                             "aligned": b.best[0][0] if b.best else None, "tried": b.tried,
                                                             "path": (b.matched[1] if b.matched else (b.best[2] if b.best else [])), "error": b.error}))
    memo_path.parent.mkdir(parents=True, exist_ok=True)
    memo_path.write_text(json.dumps(memo))
    out = {"drafts": len(items), "searched": len(bodies), "skipped": skipped, "matched": matched, "improved": improved,
           "candidates": tried, "families": families, "secs": round(time.time() - t0, 1), "results": results}
    (STATE_DIR / "spell" / "results.json").write_text(json.dumps(out, indent=1))
    return out
