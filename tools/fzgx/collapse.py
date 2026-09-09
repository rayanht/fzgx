"""Collapse a complete translation unit into one split range and one compiled unit.

Once every function of a TU is matched, the TU file is compiled as one object:
its literal pool, string pool and data then come out in the compiler's own
order, which is retail's order if the source is right. The per-function split
ranges are replaced by one unit covering the TU's .text plus the data sections
the object actually produces, sized from that object; the link's hash check is
the oracle. On failure everything is put back and the first divergent byte is
reported by function, exactly like a batch verify.

Data extents: the start of a section's chunk is the lowest address of a symbol
of that section referenced by the TU's functions and by no other TU's, aligned
down to the object's section alignment; the end is start + the object's
section size. Both must land on symbol boundaries. Shared globals defined by
the TU fall inside naturally; if the object is smaller or larger than the
retail chunk (an unmatched function's data, a string reused elsewhere), the
hash fails and the reported byte says where.
"""

from __future__ import annotations

import json
import re
import shutil
import struct
import subprocess
import time
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import oracle, poolfix, tufile, tutrial
from .project import ROOT, STATE_DIR, Project

SECTION_TYPE = {".text": "code", ".rodata": "rodata", ".data": "data", ".bss": "bss",
                ".sdata": "data", ".sbss": "bss", ".sdata2": "rodata", ".sbss2": "bss"}


def _module_of(tu_source: str) -> str:
    return tu_source.split("/")[1] if tu_source.startswith("rel/") else "main"


def _tu_entry(p: Project, module: str, tu_source: str) -> Optional[dict]:
    stem = Path(tu_source).stem
    for t in json.loads((p.module_config_dir(module) / "tus.json").read_text())["tus"]:
        if t["file"].rsplit(".", 1)[0] == stem:
            return t
    return None


def _object_sections(obj: Path) -> Dict[str, Tuple[int, int]]:
    """section name -> (size, alignment) for allocatable sections of the compiled object."""
    elf = poolfix.Elf(obj.read_bytes())
    out = {}
    for s in elf.sections:
        if s["flags"] & 2 and s["name"] in SECTION_TYPE:  # SHF_ALLOC
            out[s["name"]] = (s["size"], max(s["addralign"], 1))
    return out


def _exclusive_symbols(p: Project, module: str, funcs: List[str]) -> Dict[str, List]:
    """section -> symbols referenced by these functions and by no function outside the TU."""
    syms = p.symbols(module)
    idx = p.function_asm(module)
    inside = set(funcs)
    users: Dict[str, set] = defaultdict(set)
    for fn in idx.values():
        for r in fn.refs:
            if r in syms and syms[r].kind == "object":
                users[r].add(fn.symbol.name)
    out: Dict[str, List] = defaultdict(list)
    for name, u in users.items():
        if u and u <= inside:
            out[syms[name].section].append(syms[name])
    return out


def _pool_map(p: Project, module: str, funcs: List[str], obj: Path) -> Dict[str, str]:
    """private literal symbol -> retail pooled symbol, over every function of the TU object."""
    out: Dict[str, str] = {}
    for name in funcs:
        sym = p.symbols(module).get(name)
        target = p.target_object_for(sym) if sym else None
        if target is None:
            continue
        cp = oracle.run([str(oracle.OBJDIFF), "diff", "-1", str(target), "-2", str(obj), "-o", "-", "--format", "json", name])
        if cp.returncode != 0:
            continue
        try:
            data = json.loads(cp.stdout)
        except ValueError:
            continue
        left, right = data.get("left", {}), data.get("right", {})
        l = next((s_ for s_ in left.get("symbols", []) if s_.get("name") == name), None)
        r = next((s_ for s_ in right.get("symbols", []) if s_.get("name") == name), None)
        if l is None or r is None:
            continue
        _, pairs = oracle._pool_rows(p, module, left, right, l.get("instructions", []), r.get("instructions", []))
        for private, pooled, _desc in pairs:
            out.setdefault(private, pooled)
    return out


def plan(p: Project, tu_source: str) -> Dict[str, object]:
    """Compute the collapsed unit's ranges without touching anything."""
    module = _module_of(tu_source)
    t = _tu_entry(p, module, tu_source)
    if t is None:
        return {"ok": False, "error": "TU not in tus.json"}
    funcs = t["functions"]
    ledger_status = {u["symbols"][0]: u["status"] for u in p.load_units() if u.get("tu") == tu_source}
    missing = [f for f in funcs if ledger_status.get(f) != "matching"]
    if missing:
        return {"ok": False, "error": f"{len(missing)} functions not matched", "missing": missing[:12]}
    obj, msg = tutrial.compile_tu(p, tu_source)
    if obj is None:
        return {"ok": False, "error": "whole-TU compile failed: " + msg[-600:]}
    # the TU's private literals that retail pooled elsewhere (the 2^52 int-to-double constant,
    # shared floats): the same retarget the per-function units get (units.json `pool`, applied
    # by the mwcc_pool rule), so the private .rodata disappears and needs no placement
    pool = _pool_map(p, module, funcs, obj)
    if pool:
        fixed = obj.with_name(obj.stem + ".pool.o")
        shutil.copy(obj, fixed)
        poolfix.apply(fixed, pool)
        obj = fixed
    secs = _object_sections(obj)
    syms = p.symbols(module)
    by_addr = sorted((s.addr, s.end, s.name) for s in syms.values() if s.kind == "object")
    excl = _exclusive_symbols(p, module, funcs)
    ranges: List[Tuple[str, int, int, int]] = []
    notes: List[str] = []
    text_lo, text_hi = t["text"]
    tsize = secs.get(".text", (0, 4))[0]
    if tsize != text_hi - text_lo:
        notes.append(f".text: object {tsize:#x} B, TU range {text_hi - text_lo:#x} B")
    ranges.append((".text", text_lo, text_hi, 4))
    for sec, (size, align) in secs.items():
        if sec == ".text" or size == 0:
            continue
        cands = [s for s in excl.get(sec, [])]
        if not cands:
            notes.append(f"{sec}: object has {size:#x} B but no symbol of that section is exclusive to the TU")
            return {"ok": False, "error": "cannot place " + sec, "notes": notes, "object": p.rel(obj)}
        start = min(s.addr for s in cands)
        start -= start % align
        end = start + size
        # both ends must be symbol boundaries of the retail section
        starts = {a for a, _, n in by_addr if syms[n].section == sec}
        ends = {e for _, e, n in by_addr if syms[n].section == sec}
        if start not in starts:
            notes.append(f"{sec}: start {start:#x} is not a symbol boundary")
        if end not in ends and end not in starts:
            notes.append(f"{sec}: end {end:#x} is not a symbol boundary (last exclusive symbol ends {max(s.end for s in cands):#x})")
        outside = [s.name for s in cands if not (start <= s.addr < end)]
        if outside:
            notes.append(f"{sec}: exclusive symbols outside the placed range: {outside[:6]}")
        ranges.append((sec, start, end, align))
    return {"ok": True, "tu": tu_source, "module": module, "functions": funcs, "ranges": ranges,
            "notes": notes, "object": p.rel(obj), "pool": pool}


def _splits_without(text: str, units: List[str]) -> str:
    out, skip = [], False
    for ln in text.split("\n"):
        if ln.endswith(":") and not ln.startswith(("\t", " ")):
            skip = ln[:-1] in units
        if not skip:
            out.append(ln)
    return re.sub(r"\n{3,}", "\n\n", "\n".join(out))


def collapse(p: Project, tu_source: str, keep_on_failure: bool = False) -> Dict[str, object]:
    """Replace the TU's per-function units by one unit and verify the link. Reverts on failure."""
    pl = plan(p, tu_source)
    if not pl["ok"]:
        return pl
    module = pl["module"]
    cfg = p.module_config_dir(module)
    spath, upath = cfg / "splits.txt", p.units_path
    backup = STATE_DIR / "collapse" / f"{Path(tu_source).stem}.{int(time.time())}"
    backup.mkdir(parents=True, exist_ok=True)
    shutil.copy(spath, backup / "splits.txt")
    shutil.copy(upath, backup / "units.json")
    with oracle.build_lock():
        units = p.load_units()
        old = [u for u in units if u.get("tu") == tu_source]
        old_sources = [u["source"] for u in old]
        mw = next((u.get("mw_version") for u in old if u.get("mw_version")), None)
        extra = sorted({f for u in old for f in (u.get("extra_cflags") or [])})
        text = _splits_without(spath.read_text(), old_sources)
        text = text.rstrip("\n") + f"\n\n{tu_source}:\n"
        for sec, lo, hi, align in pl["ranges"]:
            text += f"\t{sec:<11} start:0x{lo:08X} end:0x{hi:08X} align:{align}\n"
        spath.write_text(text)
        units = [u for u in units if u.get("tu") != tu_source]
        rec = {"module": module, "source": tu_source, "symbols": list(pl["functions"]),
               "status": "matching", "mw_version": mw, "extra_cflags": extra, "collapsed": True}
        if pl.get("pool"):
            rec["pool"] = dict(pl["pool"])  # ninja retargets the literals after compiling
        units.append(rec)
        p.save_units(units)
        for src in old_sources:  # the generated per-function units are gone
            tufile.gen_path(p, src).unlink(missing_ok=True)
        cp = oracle.configure(p)
        ok = cp.returncode == 0 and oracle.relink(p).returncode == 0
        if not ok and not keep_on_failure:
            shutil.copy(backup / "splits.txt", spath)
            shutil.copy(backup / "units.json", upath)
            tufile.regenerate(p)
            oracle.configure(p)
            oracle.relink(p)
    return {"ok": ok, "tu": tu_source, "ranges": pl["ranges"], "notes": pl["notes"], "backup": p.rel(backup),
            "error": None if ok else "link/hash failed; splits and units restored"}
