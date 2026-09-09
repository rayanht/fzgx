"""The line-targeted repair loop: the first instruction that differs from retail is mapped to
the C line that produced it (MWCC's `-g` line table leaves the code unchanged and objdiff
reports the line), and only rewrites that touch that line (or the declarations) are tried.
The best candidate by (matching prefix, aligned words) becomes the new body; repeat.

Where the spelling search is blind and broad, this is narrow and deep: a body far from
matching is walked forward one divergence at a time.
"""

from __future__ import annotations

import difflib
import json
import re
import time
from typing import Dict, List, Optional, Tuple

from . import oracle, spell
from .project import STATE_DIR, Project


def first_divergence(p: Project, sym, target, obj) -> Optional[Tuple[int, Optional[int], int]]:
    """(row index of the first differing row, our source line at that row, row count)."""
    rows = oracle.function_rows(p, sym.name, target, obj)
    if not rows:
        return None
    l, r, _ = rows
    for k, (a, b) in enumerate(zip(l, r)):
        if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" or (b.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE":
            line = None
            for j in range(k, -1, -1):
                ln = (r[j].get("instruction") or {}).get("line_number")
                if ln:
                    line = ln; break
            return k, line, len(l)
    if len(l) != len(r):
        return min(len(l), len(r)), None, len(l)
    return None


def changed_lines(a: str, b: str) -> set:
    al, bl = a.splitlines(), b.splitlines()
    out = set()
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, al, bl, autojunk=False).get_opcodes():
        if tag != "equal":
            out.update(range(i1 + 1, max(i2, i1 + 1) + 1))
    return out


def search(p: Project, symbol: str, body: str, budget_s: float = 20.0, max_steps: int = 16) -> Dict[str, object]:
    t0 = time.time()
    sym = p.resolve(symbol)
    out: Dict[str, object] = {"matched": False, "body": None, "steps": [], "tried": 0, "base": 0.0, "best": 0.0}
    if sym is None:
        return out
    target = p.target_object_for(sym)
    if target is None:
        return out
    tw = oracle.words(target, sym.name)
    if not tw:
        return out
    root = STATE_DIR / "repair" / p.key(sym).replace(":", "__")
    root.mkdir(parents=True, exist_ok=True)
    base_src = root / "base.c"; base_src.write_text(body)
    mw, extra = oracle.version_for(p, sym, base_src)
    gflags = ((extra + " ") if extra else "") + "-g"

    def compile_g(text: str):
        src = root / "cur.c"; src.write_text(text)
        o = root / "cur.o"
        cp = oracle.compile_source(p, sym.module, src, o, mw, gflags)
        return o if cp.returncode == 0 and o.exists() else None

    def fitness(text_objs: List[Tuple[str, Optional[object]]]) -> List[Optional[Tuple[int, float]]]:
        res = []
        for text, o in text_objs:
            ow = oracle.words(o, sym.name) if o else None
            if not ow:
                res.append(None); continue
            pct, bad = oracle.word_score(tw, ow)
            prefix = bad[0] if bad else min(len(tw), len(ow))
            res.append((prefix, spell.fitness(tw, ow)[0]))
        return res

    cur = body
    o = compile_g(cur)
    if o is None:
        out["error"] = "base does not compile"; return out
    cur_fit = fitness([(cur, o)])[0]
    out["base"] = cur_fit[1]
    seen = {cur}
    for step in range(max_steps):
        if time.time() - t0 > budget_s:
            break
        div = first_divergence(p, sym, target, o)
        if div is None:
            r = oracle.check(p, symbol, 0, source=root / "cur.c", mw_version=mw)
            if r.ok and (r.matched or r.matched_pool) and oracle.unit_fully_matches(r) is None:
                out.update(matched=True, body=cur, best=100.0)
            break
        k, line, nrows = div
        cands = []
        for fam, label, t2 in spell.all_rewrites(cur, sym.name, max_per_family=40):
            if t2 in seen:
                continue
            ch = changed_lines(cur, t2)
            near = line is not None and any(abs(x - line) <= 1 for x in ch)
            decl = all(x <= _first_stmt_line(cur, sym.name) for x in ch)
            if near or decl:
                seen.add(t2); cands.append((1 if near else 0, fam, label, t2))
        if not cands:
            out["steps"].append(f"row {k} line {line}: no candidates"); break
        cands.sort(key=lambda c: -c[0])
        d = root / "b"; d.mkdir(exist_ok=True)
        for old in d.glob("*.c"):
            old.unlink()
        srcs = []
        for j, (_, fam, label, t2) in enumerate(cands):
            f = d / f"c{j}.c"; f.write_text(t2); srcs.append(f)
        objs = oracle.compile_many(p, sym.module, srcs, d / "obj", mw, extra)
        fits = fitness([(t2, objs.get(f)) for (_, _, _, t2), f in zip(cands, srcs)])
        out["tried"] += len(cands)
        best = None
        for (near, fam, label, t2), fit in zip(cands, fits):
            if fit is None:
                continue
            if best is None or fit > best[0]:
                best = (fit, fam, label, t2)
        if best is None or best[0] <= cur_fit:
            out["steps"].append(f"row {k} line {line}: no improvement among {len(cands)}"); break
        cur, cur_fit = best[3], best[0]
        out["steps"].append(f"row {k} line {line}: {best[1]}: {best[2]} -> prefix {best[0][0]}/{nrows}, aligned {best[0][1]:.1f}")
        o = compile_g(cur)
        if o is None:
            break
    out.update(body=cur if cur != body else None, best=cur_fit[1], secs=round(time.time() - t0, 2))
    return out


def _first_stmt_line(body: str, name: str) -> int:
    lines = body.splitlines()
    start = next((i for i, l in enumerate(lines) if re.search(rf"\b{re.escape(name)}\s*\(", l) and l.rstrip().endswith("{")), 0)
    for i in range(start + 1, len(lines)):
        l = lines[i].strip()
        if not l or l.startswith("/*"):
            continue
        if re.match(r"^(struct\s+\w+\s*\*?|[A-Za-z_]\w*\s*\*?)\s*[A-Za-z_]\w*(\s*,\s*[A-Za-z_]\w*)*(\[[^\]]*\])*;$", l) or re.match(r"^\w[\w ]*\*?\s+\w+(, \w+)*;$", l):
            continue
        return i + 1
    return start + 1
