"""Failure modes of plateaued attempts, from the object diff. No model involved.

For every unmatched function whose best saved body scores at least `min_percent`, the
body is recompiled and diffed row by row against retail (objdiff). Each differing row is
classified, and the function gets the set of modes it exhibits plus a "pure" mode when
one kind of difference explains everything. Pure modes are the deterministic-repair
candidates: the spelling search for register allocation and scheduling, a symbol or pool
fix for relocations, a type change for missing sign extensions.
"""

from __future__ import annotations

import json
import re
import sqlite3
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import oracle
from .project import STATE_DIR, Project

REG_RE = re.compile(r"\b(?:r|f|cr|p)\d+\b")
EXT_MNEMONICS = {"extsh", "extsb", "clrlwi", "rlwinm", "rlwimi", "andi.", "clrlslwi", "extlwi", "extrwi"}
FLOAT_MNEMONICS = {"frsp", "fmr", "fneg", "fabs", "fnabs", "fmadds", "fmsubs", "fnmadds", "fnmsubs", "fmadd", "fmsub",
                   "fmuls", "fmul", "fadds", "fadd", "fsubs", "fsub", "fdivs", "fdiv", "fctiwz", "fcmpu", "fcmpo", "fsel", "fres", "frsqrte"}
BRANCH_MNEMONICS = {"b", "bl", "blr", "bctr", "bctrl", "beq", "bne", "blt", "bgt", "ble", "bge", "bdnz", "bdz", "bc", "bso", "bns",
                    "beq+", "bne+", "blt+", "bgt+", "ble+", "bge+", "beq-", "bne-", "blt-", "bgt-", "ble-", "bge-", "bl+", "bctrl+"}
CMP_MNEMONICS = {"cmpw", "cmplw", "cmpwi", "cmplwi", "cmp", "cmpl", "cmpi", "cmpli"}
STACK_RE = re.compile(r"-?0x[0-9a-f]+\(r1\)|^(?:stwu|addi|subi) r1,|\br1\b")


def _mn(row: dict) -> str:
    ins = row.get("instruction") or {}
    for part in ins.get("parts", []):
        if "opcode" in part:
            return part["opcode"].get("mnemonic", "")
    return (ins.get("formatted") or "").split(" ")[0]


def _fmt(row: dict) -> str:
    return (row.get("instruction") or {}).get("formatted", "")


def _reloc(row: dict) -> Optional[str]:
    rel = (row.get("instruction") or {}).get("relocation")
    # target_symbol is an index into each object's own symbol table, so equal
    # references can have different indices. Compare the printed symbol/addend.
    return None if not rel else f"{rel.get('type_name')}:{REG_RE.sub('R', _fmt(row))}"


def _has_reloc(row: dict) -> bool:
    return (row.get("instruction") or {}).get("relocation") is not None


def _norm_regs(s: str) -> str:
    return REG_RE.sub("R", s)


def _strip_reloc(s: str) -> str:
    return re.sub(r"(?<![\w.$@])[\w$@.+-]+@(?:ha|h|l|sda21)\b", "SYM", s)


def classify_rows(lrows: List[dict], rrows: List[dict]) -> Dict[str, int]:
    """Counts per row category. Categories:
    regalloc   same instruction, only register numbers differ
    reloc      same instruction and registers, different relocation target (a symbol or pool literal)
    frame      same instruction, only a stack-frame offset differs
    imm        same mnemonic and registers, another immediate differs (struct offset, constant)
    op         different mnemonic on the same row (cmpw/cmplw, lwz/lhz, addi/addic ...)
    ext/float/branch/cmp/other  rows present on one side only, by mnemonic family
    """
    c: Counter = Counter()
    for l, r in zip(lrows, rrows):
        lk, rk = l.get("diff_kind") or "DIFF_NONE", r.get("diff_kind") or "DIFF_NONE"
        if lk == "DIFF_NONE" and rk == "DIFF_NONE":
            continue
        lf, rf = _fmt(l), _fmt(r)
        if not lf or not rf:  # a row present on one side only
            m = _mn(l if lf else r)
            fam = ("ext" if m in EXT_MNEMONICS else "float" if m in FLOAT_MNEMONICS else "branch" if m in BRANCH_MNEMONICS
                   else "cmp" if m in CMP_MNEMONICS else "other")
            c["ins:" + fam] += 1
            c["ins"] += 1
            continue
        if _mn(l) != _mn(r):
            c["op"] += 1
            c[f"op:{_mn(l)}/{_mn(r)}"] += 1
            continue
        if _norm_regs(lf) == _norm_regs(rf) and (not _has_reloc(l) or _reloc(l) == _reloc(r) or _strip_reloc(lf) != _strip_reloc(rf)):
            # registers only (a relocation that also differs is counted as reloc below)
            if _has_reloc(l) and _reloc(l) != _reloc(r) and _strip_reloc(_norm_regs(lf)) == _strip_reloc(_norm_regs(rf)):
                c["reloc"] += 1
            else:
                c["regalloc"] += 1
            continue
        if _has_reloc(l) and _has_reloc(r) and _strip_reloc(lf) == _strip_reloc(rf):
            c["reloc"] += 1
            continue
        if REG_RE.sub("", lf) != REG_RE.sub("", rf) and _norm_regs(_strip_reloc(lf)) != _norm_regs(_strip_reloc(rf)):
            if STACK_RE.search(lf) and STACK_RE.search(rf):
                c["frame"] += 1
            elif _norm_regs(_strip_reloc(lf)).split(" ")[0] == _norm_regs(_strip_reloc(rf)).split(" ")[0]:
                c["imm"] += 1
                if _norm_regs(lf) != _norm_regs(rf):
                    c["regalloc"] += 1
            else:
                c["op"] += 1
            continue
        c["regalloc"] += 1
    return dict(c)


def row_kinds(lrows: List[dict], rrows: List[dict]) -> List[Optional[str]]:
    """One label per aligned row (None when equal), the same categories classify_rows counts."""
    out: List[Optional[str]] = []
    for l, r in zip(lrows, rrows):
        lk, rk = l.get("diff_kind") or "DIFF_NONE", r.get("diff_kind") or "DIFF_NONE"
        if lk == "DIFF_NONE" and rk == "DIFF_NONE":
            out.append(None); continue
        c = classify_rows([l], [r])
        keys = [k for k in c if ":" in k] or [k for k in c]
        out.append(keys[0] if keys else "other")
    return out


def _pure(counts: Dict[str, int], lrows: List[dict], rrows: List[dict]) -> str:
    """One word when a single kind of difference explains the whole diff."""
    kinds = {k for k in counts if ":" not in k}
    if not kinds:
        return "none"
    if len(lrows) == len(rrows):
        lm, rm = Counter(_fmt(r) for r in lrows), Counter(_fmt(r) for r in rrows)
        if lm == rm:
            return "schedule"
        if Counter(_norm_regs(_fmt(r)) for r in lrows) == Counter(_norm_regs(_fmt(r)) for r in rrows):
            return "regalloc+schedule" if kinds != {"regalloc"} else "regalloc"
    if kinds == {"regalloc"}:
        return "regalloc"
    if kinds == {"reloc"}:
        return "reloc"
    if kinds == {"frame"} or kinds == {"frame", "regalloc"}:
        return "frame"
    if kinds == {"imm"} or kinds == {"imm", "regalloc"}:
        return "imm"
    if kinds == {"ins"} and set(k for k in counts if k.startswith("ins:")) == {"ins:ext"}:
        return "ext"
    if kinds <= {"ins", "regalloc"} and set(k for k in counts if k.startswith("ins:")) <= {"ins:ext"}:
        return "ext+regalloc"
    if kinds == {"op"} and all(k.split(":")[1] in ("cmpw/cmplw", "cmplw/cmpw", "cmpwi/cmplwi", "cmplwi/cmpwi") for k in counts if k.startswith("op:")):
        return "signedness"
    return "mixed"


def best_bodies(p: Project, min_percent: float, module: Optional[str] = None,
                max_size: Optional[int] = None) -> Dict[str, Tuple[str, float, int, str]]:
    """{symbol: (body path, best %, size, module)} for unmatched functions at or above min_percent."""
    db = sqlite3.connect(str(STATE_DIR / "ledger.db"))
    q = """select f.symbol, f.best_percent, f.size, f.module, a.best_body_path, a.best_in_attempt from functions f
           join attempts a on a.symbol=f.symbol where f.status='unmatched' and f.best_percent>=? and a.best_body_path is not null"""
    args = [min_percent]
    if module:
        q += " and f.module=?"
        args.append(module)
    if max_size is not None:
        q += " and f.size<=?"
        args.append(max_size)
    out: Dict[str, tuple] = {}
    for s, bp, size, mod, path, pct in db.execute(q, args):
        if not Path(path).exists():
            path = str(STATE_DIR / "attempts" / Path(path).name)
        if Path(path).exists() and (s not in out or (pct or 0) > out[s][1]):
            out[s] = (path, pct or 0.0, size, mod)
    return out


def analyse(p: Project, symbol: str, path: str, res: Optional[oracle.CheckResult] = None) -> Dict[str, object]:
    if res is None:
        res = oracle.check(p, symbol, 0, source=Path(path))
    if not res.ok:
        return {"symbol": symbol, "ok": False, "error": res.error[-300:]}
    lrows, rrows = getattr(res, "_rows", ([], []))
    counts = classify_rows(lrows, rrows)
    # the differing rows themselves (index, target, ours): every later question is a JSON read
    diffs = [(i, _fmt(a), _fmt(b)) for i, (a, b) in enumerate(zip(lrows, rrows))
             if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" or (b.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE"]
    pure = _pure(counts, lrows, rrows)
    flow = None
    if pure == 'regalloc':
        from . import regflow
        flow = regflow.analyse_rows(lrows, rrows)
        if flow['value_flow']:
            pure = 'value-flow'
    return {"symbol": symbol, "ok": True, "percent": res.percent, "percent_adjusted": res.percent_adjusted,
            "pool_rows": res.pool_rows, "matched_pool": res.matched_pool, "rows": (len(lrows), len(rrows)),
            "counts": counts, "pure": pure, "diffs": diffs, "register_flow": flow}


def run(p: Project, min_percent: float = 80.0, module: Optional[str] = None, workers: int = 12,
        max_size: Optional[int] = None, seeds: Optional[Path] = None) -> Dict[str, object]:
    options = {}
    if seeds is not None:
        db = sqlite3.connect(str(STATE_DIR / 'ledger.db'))
        unmatched = {r[0] for r in db.execute("SELECT symbol FROM functions WHERE status='unmatched'")}
        bodies = {}
        for key, record in json.loads(seeds.read_text()).items():
            sym = p.resolve(key)
            if not sym or p.key(sym) not in unmatched or record['percent'] < min_percent:
                continue
            if (module and sym.module != module) or (max_size is not None and sym.size > max_size):
                continue
            bodies[key] = (record['path'], record['percent'], sym.size, sym.module)
            options[key] = (record.get('mw'), record.get('flags'))
    else:
        bodies = best_bodies(p, min_percent, module, max_size)
    items = sorted(bodies.items())
    # one parallel batched compile for every body, then the row analysis in threads
    groups = defaultdict(list)
    for symbol, record in items:
        groups[options.get(symbol, (None, None))].append((symbol, Path(record[0])))
    checks = {}
    for (mw, flags), group in groups.items():
        checks.update(oracle.check_many(p, group, mw_version=mw, extra_cflags=flags))
    with ThreadPoolExecutor(max_workers=workers) as ex:
        results = list(ex.map(lambda kv: analyse(p, kv[0], kv[1][0], checks.get(kv[0])), items))
    for r in results:
        _, pct, size, mod = bodies[r["symbol"]]
        r.update({"ledger_best": pct, "size": size, "module": mod})
    out = {"min_percent": min_percent, "max_size": max_size, "n": len(results), "results": results}
    path = STATE_DIR / "stuck.json"
    path.write_text(json.dumps(out, indent=1))
    return out


def summary(out: Dict[str, object]) -> str:
    rs = [r for r in out["results"] if r.get("ok")]
    bad = [r for r in out["results"] if not r.get("ok")]
    lines = [f"{len(rs)} plateaued bodies recompiled ({len(bad)} failed to compile), best >= {out['min_percent']}%", ""]
    by: Dict[str, list] = defaultdict(list)
    for r in rs:
        by[r["pure"]].append(r)
    lines.append("| pure mode | functions | bytes | mean % | example |")
    lines.append("|---|---|---|---|---|")
    for k, v in sorted(by.items(), key=lambda kv: -len(kv[1])):
        ex = ", ".join(x["symbol"] for x in sorted(v, key=lambda x: -x["percent"])[:3])
        lines.append(f"| {k} | {len(v)} | {sum(x['size'] for x in v)} | {sum(x['percent'] for x in v)/len(v):.1f} | {ex} |")
    lines.append("")
    kinds: Counter = Counter()
    for r in rs:
        for k in r["counts"]:
            if ":" not in k:
                kinds[k] += 1
    lines.append("functions exhibiting each row category (multi-label): " + ", ".join(f"{k} {n}" for k, n in kinds.most_common()))
    ops: Counter = Counter()
    for r in rs:
        for k, n in r["counts"].items():
            if k.startswith("op:") or k.startswith("ins:"):
                ops[k] += n
    lines.append("most common row-level op/insert kinds: " + ", ".join(f"{k} {n}" for k, n in ops.most_common(15)))
    return "\n".join(lines)
