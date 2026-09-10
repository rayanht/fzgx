"""The oracle: compile one unit, diff it against retail, relink everything.

check(symbol)  -> compile the unit's object, objdiff it, return per-symbol
                  percentages and a compact instruction diff for `symbol`.
relink()       -> full `ninja`; the CHECK step fails unless every target in
                  build.sha1 is byte-identical.
"""

from __future__ import annotations

import base64
import fcntl
import json
import os
import re
import shlex
import shutil
import struct
import subprocess
import sys
from contextlib import contextmanager
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import poolfix
from .project import ROOT, STATE_DIR, Project, Symbol

OBJDIFF = ROOT / "build" / "tools" / "objdiff-cli"


@dataclass
class CheckResult:
    ok: bool  # compiled and objdiff ran
    symbol: str
    unit: str
    percent: float = 0.0
    matched: bool = False
    symbols: Dict[str, float] = field(default_factory=dict)  # every function in the unit
    data_sections: Dict[str, float] = field(default_factory=dict)
    diff: List[str] = field(default_factory=list)
    error: str = ""
    missing_in_base: List[str] = field(default_factory=list)
    extra_in_base: List[str] = field(default_factory=list)
    # every remaining diff is a relocation to a literal-pool constant whose value we reproduce
    # privately (an int->float conversion constant, or a literal shared with a neighbour):
    # per-function linking cannot express that; the TU's whole-unit compile will
    matched_pool: bool = False
    pool: List[str] = field(default_factory=list)
    # private literal -> retail pooled symbol, applied to the object after compiling (poolfix);
    # with this the function matches outright and links from C
    pool_map: Dict[str, str] = field(default_factory=dict)
    uncarved: bool = False           # diffed against the retail auto object: this symbol only
    pool_rows: int = 0               # differing rows that are only pool relocations
    percent_adjusted: float = 0.0    # match % with the pool rows counted as matching
    mw_version: Optional[str] = None  # the compiler version this verdict came from (candidates: the best)
    extra_cflags: Optional[str] = None  # the extra flags of that build (e.g. -use_lmw_stmw on)

    def to_json(self) -> dict:
        return {k: v for k, v in self.__dict__.items() if not k.startswith("_")}


def run(cmd: List[str], cwd: Path = ROOT, timeout: int = 600) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, cwd=cwd, text=True, capture_output=True, timeout=timeout)


@contextmanager
def build_lock(name: str = "build.lock", timeout_s: float = 120.0):
    """The build lock. Never waits silently: after `timeout_s` it raises and names the lock,
    so a child of an interrupted run that still holds it is found instead of waited on."""
    import time as _time  # scoped: one polling loop
    path = STATE_DIR / name
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w") as f:
        t0 = _time.time(); warned = False
        while True:
            try:
                fcntl.flock(f, fcntl.LOCK_EX | fcntl.LOCK_NB)
                break
            except BlockingIOError:
                if _time.time() - t0 > timeout_s:
                    raise TimeoutError(f"{path.name}: held by another process for over {int(timeout_s)} s (an interrupted run's child? see `pgrep -fl 'dtk|ninja|mwld'`)")
                if not warned and _time.time() - t0 > 5:
                    print(f"  waiting for {path.name} (held by another process)...", file=sys.stderr, flush=True); warned = True
                _time.sleep(0.2)
        try:
            yield
        finally:
            fcntl.flock(f, fcntl.LOCK_UN)


def configure(project: Project) -> subprocess.CompletedProcess:
    return run([sys.executable, "configure.py", "--version", project.version])


def relink(project: Project, keep_going: bool = False) -> subprocess.CompletedProcess:
    """Relink every target and verify build.sha1.

    Targets `build/<VERSION>/ok` (the dtk shasum check) rather than the default
    target, so only Matching units are compiled: another agent's broken
    in-progress unit cannot fail this step. keep_going reports every failing
    unit instead of stopping at the first.
    """
    cmd = ["ninja"] + (["-k", "0"] if keep_going else []) + [project.rel(project.build_dir / "ok")]
    return run(cmd, timeout=1800)


def _base_object(project: Project, unit: str) -> Path:
    units = project.objdiff_units()
    if unit in units and "base_path" in units[unit]:
        return ROOT / units[unit]["base_path"]
    module, rest = unit.split("/", 1)
    return project.build_dir / "src" / f"{rest}.o"


def _render_diff(left_rows: List[dict], right_rows: List[dict], max_lines: int,
                 pool_rows: Optional[set] = None) -> List[str]:
    """Side-by-side rendering: `target | ours`, with a marker on differing rows
    (`p` = literal-pool relocation the tooling retargets; not yours to fix)."""
    out: List[str] = []
    n = max(len(left_rows), len(right_rows))
    for i in range(n):
        l = left_rows[i] if i < len(left_rows) else {}
        r = right_rows[i] if i < len(right_rows) else {}
        kind = l.get("diff_kind") or r.get("diff_kind") or "DIFF_NONE"
        lf = l.get("instruction", {}).get("formatted", "")
        rf = r.get("instruction", {}).get("formatted", "")
        mark = " " if kind == "DIFF_NONE" else {"DIFF_REPLACE": "~", "DIFF_DELETE": "<", "DIFF_INSERT": ">",
                                                "DIFF_OP_MISMATCH": "!", "DIFF_ARG_MISMATCH": "?"}.get(kind, "*")
        if pool_rows and i in pool_rows:
            mark = "p"
        if kind != "DIFF_NONE" or len(out) < 4:
            out.append(f"{mark} {i * 4:04X}  {lf:<34} | {rf}")
    if len(out) > max_lines:
        head = out[: max_lines - 1]
        head.append(f"... {len(out) - (max_lines - 1)} more differing rows")
        out = head
    return out


def check(project: Project, symbol: str, max_diff_lines: int = 80, source: Optional[Path] = None,
          mw_version: Optional[str] = None, extra_cflags: Optional[str] = None) -> CheckResult:
    """Compile the unit (or `source`, an agent's work copy) into the unit's object and diff it.
    For an uncarved function, `mw_version`/`extra_cflags` are the unit options being proposed."""
    sym = project.resolve(symbol)
    if sym is None:
        return CheckResult(False, symbol, "", error="unknown or ambiguous symbol (use module:name)")
    symbol = sym.name  # objdiff symbol name is the bare C name
    unit_src = project.unit_of(sym)
    if not unit_src:
        # not carved: nothing in the link yet. Diff the work copy against the retail auto
        # object that already contains the function (two-object mode, this symbol only).
        if source is None:
            return CheckResult(False, symbol, "", error="not matched yet and no work copy to check")
        target = project.target_object_for(sym)
        if target is None or not target.exists():
            return CheckResult(False, symbol, "", error="no retail object defines this function (run ninja)")
        base_obj = STATE_DIR / "work" / (project.key(sym).replace(":", "__") + ".o")
        chosen: Tuple[Optional[str], Optional[str]] = (mw_version, extra_cflags)
        cands = [(mw_version, extra_cflags)] if (mw_version or extra_cflags) else version_candidates(project, sym.module)
        if len(cands) > 1:
            # one compile per candidate build, the best by masked words is the one diffed
            tw = words(target, symbol)
            best = None
            for ver, ex in cands:
                o = base_obj.with_name(base_obj.stem + "." + ver.replace("/", "_") + ("_stmw" if ex else "") + ".o")
                cp = compile_source(project, sym.module, source, o, ver, ex)
                if cp.returncode != 0 or not o.exists():
                    continue
                ow = words(o, symbol)
                pct = word_score(tw, ow)[0] if tw and ow else -1.0
                if best is None or pct > best[0]:
                    best = (pct, (ver, ex), o, cp)
            if best is None:
                cp = compile_source(project, sym.module, source, base_obj, cands[0][0], cands[0][1])
            else:
                chosen = best[1]
                shutil.copy(best[2], base_obj); cp = best[3]
        else:
            cp = compile_source(project, sym.module, source, base_obj, cands[0][0], cands[0][1])
        if cp.returncode != 0 or not base_obj.exists():
            err = "\n".join(l for l in (cp.stdout + cp.stderr).splitlines() if "Usage Warning" not in l)
            return CheckResult(False, symbol, "", error=err.strip()[-4000:])
        res = _diff(project, sym.module, symbol, "", max_diff_lines, target=target, base=base_obj)
        res.mw_version, res.extra_cflags = chosen
        if res.ok and res.matched_pool:
            mapping = {private: pooled for private, pooled, _ in res._pool_pairs}
            r = poolfix.apply(base_obj, mapping)
            if not r["skipped"] and r["rodata_emptied"]:
                res2 = _diff(project, sym.module, symbol, "", max_diff_lines, target=target, base=base_obj)
                if res2.ok and res2.matched:
                    res2.pool_map, res2.pool = mapping, res.pool
                    res2.mw_version, res2.extra_cflags = chosen; res2.uncarved = True
                    return res2
        res.uncarved = True
        if res.ok and res.matched_pool:
            # the pool retarget path returns res2 above; here keep the version on the plain result
            pass
        return res
    unit = project.objdiff_unit_name(sym.module, unit_src)
    base_obj = _base_object(project, unit)

    if source is not None:
        # a body that is not the unit's own text (a candidate, an agent's work copy) never goes
        # into the link's object: ninja would keep the foreign object as up to date and the REL
        # would stop hashing. Scratch object, two-object diff against the retail unit object.
        target = project.target_object_for(sym)
        if target is not None and target.exists():
            scratch_obj = STATE_DIR / "work" / (project.key(sym).replace(":", "__") + ".o")
            scratch_obj.parent.mkdir(parents=True, exist_ok=True)
            ucfg = project.unit_record(unit_src) or {}
            cp = compile_source(project, sym.module, source, scratch_obj, mw_version or ucfg.get("mw_version"),
                                extra_cflags or (" ".join(ucfg.get("extra_cflags") or []) or None))
            if cp.returncode != 0 or not scratch_obj.exists():
                err = "\n".join(l for l in (cp.stdout + cp.stderr).splitlines() if "Usage Warning" not in l)
                return CheckResult(False, symbol, unit, error=err.strip()[-4000:])
            res = _diff(project, sym.module, symbol, unit, max_diff_lines, target=target, base=scratch_obj)
            if res.ok and res.matched_pool:
                mapping = {private: pooled for private, pooled, _ in res._pool_pairs}
                r = poolfix.apply(scratch_obj, mapping)
                if not r["skipped"] and r["rodata_emptied"]:
                    res2 = _diff(project, sym.module, symbol, unit, max_diff_lines, target=target, base=scratch_obj)
                    if res2.ok and res2.matched:
                        res2.pool_map, res2.pool = mapping, res.pool
                        return res2
            return res

    # the unit's own text: direct mwcc compile into this unit's own object, no ninja, no build lock
    cp = compile_unit(project, unit, unit_src, None)
    if cp.returncode != 0 or not base_obj.exists():
        err = "\n".join(l for l in (cp.stdout + cp.stderr).splitlines() if "Usage Warning" not in l)
        return CheckResult(False, symbol, unit, error=err.strip()[-4000:])

    res = _diff(project, sym.module, symbol, unit, max_diff_lines)
    if res.ok and res.matched_pool:
        # retarget the private literals to the pooled symbols and diff again
        mapping = {private: pooled for private, pooled, _ in res._pool_pairs}
        r = poolfix.apply(base_obj, mapping)
        if not r["skipped"] and r["rodata_emptied"]:
            res2 = _diff(project, sym.module, symbol, unit, max_diff_lines)
            if res2.ok and res2.matched:
                res2.pool_map = mapping
                res2.pool = res.pool
                return res2
    return res


def _diff(project: Project, module: str, symbol: str, unit: str, max_diff_lines: int,
          target: Optional[Path] = None, base: Optional[Path] = None) -> CheckResult:
    if target is not None:
        cp = run([str(OBJDIFF), "diff", "-1", str(target), "-2", str(base), "-o", "-", "--format", "json", symbol])
    else:
        cp = run([str(OBJDIFF), "diff", "-p", str(ROOT), "-u", unit, "-o", "-", "--format", "json"])
    if cp.returncode != 0:
        return CheckResult(False, symbol, unit, error=(cp.stderr or cp.stdout).strip()[-4000:])
    data = json.loads(cp.stdout)
    left, right = data.get("left", {}), data.get("right", {})
    res = CheckResult(True, symbol, unit)
    res._pool_pairs = []
    res._rows = ([], [])  # objdiff's instruction rows (target, ours) for classifiers
    left_syms = {s["name"]: s for s in left.get("symbols", []) if s.get("kind") == "SYMBOL_FUNCTION"}
    right_syms = {s["name"]: s for s in right.get("symbols", []) if s.get("kind") == "SYMBOL_FUNCTION"}
    if target is not None:  # the retail auto object holds many functions; only ours is in question
        left_syms = {k: v for k, v in left_syms.items() if k == symbol}
        right_syms = {k: v for k, v in right_syms.items() if k == symbol}
    for name, s in left_syms.items():
        res.symbols[name] = float(s.get("match_percent", 0.0))
    res.missing_in_base = sorted(set(left_syms) - set(right_syms))
    res.extra_in_base = sorted(set(right_syms) - set(left_syms))
    for sec in left.get("sections", []):
        if sec.get("kind") in ("SECTION_DATA", "SECTION_BSS") and "match_percent" in sec:
            res.data_sections[sec["name"]] = float(sec["match_percent"])
    res.percent = res.symbols.get(symbol, 0.0)
    res.percent_adjusted = res.percent
    res.matched = res.percent >= 100.0
    if not res.matched:
        lrows = left_syms.get(symbol, {}).get("instructions", [])
        rrows = right_syms.get(symbol, {}).get("instructions", [])
        res._rows = (lrows, rrows)
        if symbol not in right_syms:
            res.diff = [f"(symbol {symbol} not present in our object: define it, check the name)"]
        else:
            pool_rows, res._pool_pairs = _pool_rows(project, module, left, right, lrows, rrows)
            if base is not None:
                data_rows, data_pairs = _data_pool_rows(project, module, base, left, right, lrows, rrows)
                pool_rows |= data_rows
                res._pool_pairs += data_pairs
                bss_rows, bss_pairs = _bss_base_rows(project, module, base, left, right, lrows, rrows)
                pool_rows |= bss_rows
                res._pool_pairs += bss_pairs
            res.pool = [d for _, _, d in res._pool_pairs]
            abs_rows = _abs_rows(right, lrows, rrows)
            abs_rows |= _equivalent_reloc_rows(project, module, base, left, right, lrows, rrows)
            res.diff = _render_diff(lrows, rrows, max_diff_lines, pool_rows | abs_rows)
            # what is left once the pool rows are taken out: what the agent can still act on
            real = sum(1 for i, (l, r) in enumerate(zip(lrows, rrows))
                       if (l.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" and i not in pool_rows and i not in abs_rows)
            n = max(len(lrows), len(rrows), 1)
            res.pool_rows = len(pool_rows)
            res.percent_adjusted = round(100.0 * (n - real - abs(len(lrows) - len(rrows))) / n, 2) if (pool_rows or abs_rows) else res.percent
            res.matched_pool = bool(pool_rows) and real == 0 and len(lrows) == len(rrows)
            if abs_rows and not pool_rows and real == 0 and len(lrows) == len(rrows):
                # only linker-defined absolute symbols differ (ours a relocation, retail the
                # resolved literal): the link produces retail's bytes; verify's hash is the guard
                res.matched = True
    return res


def _equivalent_reloc_rows(project, module, obj, left, right, lrows, rrows):
    """A split data label and an external base plus addend resolve to the same address."""
    undefined = {s['name'] for s in poolfix.Elf(obj.read_bytes()).symbols() if s['shndx'] == 0}
    addresses = {s.name: s.addr for s in project.symbols(module).values()}
    addresses.update({f'{s.name}_{s.addr:08X}': s.addr for s in project.symbols(module).values()})
    rows = set()
    for i, (l, r) in enumerate(zip(lrows, rrows)):
        li, ri = l.get('instruction', {}), r.get('instruction', {})
        lr, rr = li.get('relocation'), ri.get('relocation')
        if not lr or not rr or lr.get('type') != rr.get('type'):
            continue
        if [x for x in li.get('parts', []) if 'reloc' not in json.dumps(x)] != [x for x in ri.get('parts', []) if 'reloc' not in json.dumps(x)]:
            continue
        lname = left['symbols'][lr['target_symbol']]['name']
        rname = right['symbols'][rr['target_symbol']]['name']
        if rname not in undefined or lname not in addresses or rname not in addresses:
            continue
        if addresses[lname] + int(lr.get('addend') or 0) == addresses[rname] + int(rr.get('addend') or 0):
            rows.add(i)
    return rows


def _bss_base_rows(project, module, obj, left, right, lrows, rrows):
    """A compiler section base and its named BSS object denote the same storage."""
    elf = poolfix.Elf(obj.read_bytes())
    section = elf.section('.bss')
    if not section:
        return set(), []
    symbols = {s['name']: s for s in elf.symbols()}
    rows, pairs = set(), []
    for i, (l, r) in enumerate(zip(lrows, rrows)):
        li, ri = l.get('instruction', {}), r.get('instruction', {})
        lr, rr = li.get('relocation'), ri.get('relocation')
        if not lr or not rr or lr.get('type') != rr.get('type') or int(lr.get('addend') or 0) != int(rr.get('addend') or 0):
            continue
        if [x for x in li.get('parts', []) if 'reloc' not in json.dumps(x)] != [x for x in ri.get('parts', []) if 'reloc' not in json.dumps(x)]:
            continue
        lname = left['symbols'][lr['target_symbol']]['name']
        rname = right['symbols'][rr['target_symbol']]['name']
        anchor, owned = symbols.get(rname), symbols.get(lname)
        if not rname.startswith('...bss') or not anchor or not owned:
            continue
        retail = project.symbols(module).get(lname)
        if retail is None:
            retail = next((s for s in project.symbols(module).values() if lname == f'{s.name}_{s.addr:08X}'), None)
        if not retail or retail.section != '.bss' or owned['size'] != retail.size:
            continue
        if anchor['shndx'] != section['index'] or owned['shndx'] != section['index'] or anchor['value'] != owned['value']:
            continue
        rows.add(i)
        pair = (rname, lname, f'{lname}=owned BSS base')
        if pair not in pairs:
            pairs.append(pair)
    return rows, pairs


def _data_pool_rows(project, module, obj, left, right, lrows, rrows):
    """Retarget a compiler-owned string pool only when its entire byte range agrees."""
    elf = poolfix.Elf(obj.read_bytes())
    section = elf.section('.data')
    if not section or not section['size']:
        return set(), []
    if any(s['type'] == 4 and s['info'] == section['index'] and s['size'] for s in elf.sections):
        return set(), []
    symbols = elf.symbols()
    defined = [s for s in symbols if s['shndx'] == section['index'] and s['size']]
    if not defined or any(not s['name'].startswith('@') for s in defined):
        return set(), []
    payload = bytes(elf.data[section['offset']:section['offset'] + section['size']])
    rows, pairs = set(), []
    for i, (l, r) in enumerate(zip(lrows, rrows)):
        li, ri = l.get('instruction', {}), r.get('instruction', {})
        lr, rr = li.get('relocation'), ri.get('relocation')
        if not lr or not rr or lr.get('type') != rr.get('type'):
            continue
        if [x for x in li.get('parts', []) if 'reloc' not in json.dumps(x)] != [x for x in ri.get('parts', []) if 'reloc' not in json.dumps(x)]:
            continue
        lname = left['symbols'][lr['target_symbol']]['name']
        rname = right['symbols'][rr['target_symbol']]['name']
        ours = next((s for s in symbols if s['name'] == rname), None)
        target = project.symbols(module).get(lname)
        if target is None:
            suffix = re.search(r'_([0-9A-Fa-f]{8})$', lname)
            target = next((s for s in project.symbols(module).values() if suffix and s.addr == int(suffix[1], 16)), None)
        if not ours or ours['shndx'] != section['index'] or not target:
            continue
        address = target.addr + int(lr.get('addend') or 0) - ours['value'] - int(rr.get('addend') or 0)
        actual = next((raw[address - base:address - base + len(payload)]
                       for base, raw in project._rel_layout(module).values()
                       if base <= address and address + len(payload) <= base + len(raw)), None)
        if payload != actual:
            continue
        rows.add(i)
        if ours['value'] == 0 and (lr.get('addend') or 0) == (rr.get('addend') or 0):
            pair = (rname, lname, f'{lname}=string pool[{len(payload)}]')
            if pair not in pairs:
                pairs.append(pair)
    return rows, pairs


_ABS_SYMS: Optional[Dict[str, int]] = None


def abs_symbols() -> Dict[str, int]:
    """Absolute symbols the link script defines (`NAME = 0xADDR;` in config/<v>/ldscript.tpl):
    hardware register blocks retail addressed through the linker."""
    global _ABS_SYMS
    if _ABS_SYMS is None:
        out: Dict[str, int] = {}
        for tpl in (ROOT / "config").glob("*/ldscript.tpl"):
            for m in re.finditer(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", tpl.read_text(), re.M):
                out[m.group(1)] = int(m.group(2), 16)
        _ABS_SYMS = out
    return _ABS_SYMS


def _abs_rows(right: dict, lrows: List[dict], rrows: List[dict]) -> set:
    """Rows where ours relocates against a link-script absolute symbol and retail carries the
    resolved literal: `lis r3, __DIRegs@ha` / `addi r3, r3, __DIRegs@l` vs `lis r3, 0xcc00` /
    `addi r3, r3, 0x6000`. The instruction text must be identical once the symbol is resolved."""
    table = abs_symbols()
    if not table:
        return set()
    rsyms = right.get("symbols", [])
    rows: set = set()
    for i, (l, r) in enumerate(zip(lrows, rrows)):
        if (l.get("diff_kind") or "DIFF_NONE") == "DIFF_NONE":
            continue
        li, ri = l.get("instruction", {}), r.get("instruction", {})
        rrel = ri.get("relocation")
        if not rrel or li.get("relocation"):
            continue
        try:
            name = rsyms[rrel["target_symbol"]]["name"]
        except (IndexError, KeyError, TypeError):
            continue
        if name not in table:
            continue
        addr = table[name] + int(rrel.get("addend") or 0)
        ha = ((addr + 0x8000) >> 16) & 0xFFFF
        lo = addr & 0xFFFF
        lo_s = lo - 0x10000 if lo >= 0x8000 else lo
        ours = ri.get("formatted", "")
        forms = set()
        for hi_txt in (f"0x{ha:x}", f"-0x{(0x10000 - ha) & 0xFFFF:x}" if ha >= 0x8000 else f"0x{ha:x}"):
            for lo_txt in (f"0x{lo:x}", f"-0x{-lo_s:x}" if lo_s < 0 else f"0x{lo_s:x}"):
                forms.add(ours.replace(f"{name}@ha", hi_txt).replace(f"{name}@h", hi_txt).replace(f"{name}@l", lo_txt))
        if li.get("formatted", "") in forms:
            rows.add(i)
    return rows


def _pool_rows(project: Project, module: str, left: dict, right: dict,
               lrows: List[dict], rrows: List[dict]):
    """Rows that differ only by `relocation to a pooled constant (retail)` vs `relocation to
    our private literal with the same bytes`. Returns (row indices, [(private, pooled, desc)])."""
    lsyms, rsyms = left.get("symbols", []), right.get("symbols", [])
    syms = project.symbols(module)
    rows: set = set()
    pairs: List[tuple] = []
    for i, (l, r) in enumerate(zip(lrows, rrows)):
        if (l.get("diff_kind") or "DIFF_NONE") == "DIFF_NONE" and (r.get("diff_kind") or "DIFF_NONE") == "DIFF_NONE":
            continue
        li, ri = l.get("instruction", {}), r.get("instruction", {})
        lrel, rrel = li.get("relocation"), ri.get("relocation")
        if not lrel or not rrel or lrel.get("type") != rrel.get("type"):
            continue
        lp = [x for x in li.get("parts", []) if "reloc" not in json.dumps(x)]
        rp = [x for x in ri.get("parts", []) if "reloc" not in json.dumps(x)]
        if lp != rp:
            continue
        try:
            lname = lsyms[lrel["target_symbol"]]["name"]
            rsym = rsyms[rrel["target_symbol"]]
        except (IndexError, KeyError, TypeError):
            continue
        s = syms.get(lname)
        if s and s.kind == "object" and lname.startswith("jumptable_") and rsym.get("name", "").startswith("@") \
                and int(rsym.get("size") or 0) == s.size:
            # a switch jump table: ours is a private data symbol of the same size; the unit owns
            # the retail table's range (carve), so ours is renamed in place, not dropped
            rows.add(i)
            pair = (rsym["name"], lname, f"{lname}=jumptable[{s.size}]")
            if pair not in pairs:
                pairs.append(pair)
            continue
        if not s or s.kind != "object" or s.section not in (".rodata", ".sdata2"):
            continue
        # dtk often merges a run of pooled literals into one symbol (0x18, 0x1C, even 5504 bytes):
        # the constant is the retail bytes at the relocation's addend, whatever the symbol's size
        addend = int(lrel.get("addend") or 0)
        ours = b"".join(base64.b64decode(d.get("data", "")) for d in rsym.get("data_diff", []))
        whole = project.bytes_at(module, lname) or b""
        retail = whole[addend:addend + len(ours)] if ours and len(ours) in (4, 8) else b""
        if not retail or ours != retail or not rsym.get("name", "").startswith("@"):
            continue
        v = struct.unpack(">d", retail)[0] if len(retail) == 8 else struct.unpack(">f", retail)[0]
        rows.add(i)
        pair = (rsym["name"], lname, f"{lname}={v!r}")
        if pair not in pairs:
            pairs.append(pair)
    return rows, pairs


_FLAGS_CACHE: Dict[tuple, Tuple[str, str]] = {}
# the DOL holds SDK code built by 1.2.5n next to game code built by 1.3.2, interleaved by address,
# and some of that game code (and movie_module) was built with `-use_lmw_stmw on` (stmw/lmw
# prologues): an uncarved function is compiled under every candidate (version, extra flags)
# pair and the best one is its build
STMW = "-use_lmw_stmw on"
VERSION_CANDIDATES = {"main": [("GC/1.2.5n", None), ("GC/1.3.2", None), ("GC/1.3.2", STMW)],
                      "movie_module": [("GC/1.3.2", None), ("GC/1.3.2", STMW)]}


def version_candidates(project: Project, module: str) -> List[Tuple[str, Optional[str]]]:
    return VERSION_CANDIDATES.get(module, [(module_flags(project, module)[1], None)])


def _join_flags(*parts: Optional[str]) -> Optional[str]:
    joined = " ".join(x for x in parts if x)
    return joined or None


def version_for(project: Project, sym: Symbol, source: Optional[Path] = None) -> Tuple[Optional[str], Optional[str]]:
    """(mw_version, extra_cflags) for compiling candidates of this function: the unit's own
    options when carved; otherwise, in a module with several candidate versions, the one under
    which `source` scores best (one compile per candidate); else the module default."""
    unit_src = project.unit_of(sym)
    if unit_src:
        u = project.unit_record(unit_src) or {}
        return u.get("mw_version"), (" ".join(u.get("extra_cflags") or []) or None)
    cands = version_candidates(project, sym.module)
    if len(cands) == 1 or source is None:
        return None, None
    target = project.target_object_for(sym)
    tw = words(target, sym.name) if target else None
    if not tw:
        return None, None
    best = None
    d = STATE_DIR / "work" / "ver"
    d.mkdir(parents=True, exist_ok=True)
    for ver, ex in cands:
        o = d / f"{project.key(sym).replace(':', '__')}.{ver.replace('/', '_')}{'_stmw' if ex else ''}.o"
        cp = compile_source(project, sym.module, source, o, ver, ex)
        ow = words(o, sym.name) if cp.returncode == 0 and o.exists() else None
        pct = word_score(tw, ow)[0] if ow else -1.0
        if best is None or pct > best[0]:
            best = (pct, ver, ex)
    return (best[1], best[2]) if best else (None, None)


def module_flags(project: Project, module: str) -> Tuple[str, str]:
    """(compiler flags, mw version) of a module, from any configured unit of it. Cached per
    objdiff.json version: the lookup used to parse the whole file on every check."""
    oj = ROOT / "objdiff.json"
    try:
        stamp = oj.stat().st_mtime_ns
    except OSError:
        stamp = None
    key = (project.version, module, stamp)
    hit = _FLAGS_CACHE.get(key)
    if hit:
        return hit
    hit = _module_flags(project, module)
    _FLAGS_CACHE[key] = hit
    return hit


def _module_flags(project: Project, module: str) -> Tuple[str, str]:
    for name, meta in project.objdiff_units().items():
        if name.split("/", 1)[0] == module and meta.get("scratch", {}).get("c_flags"):
            flags = meta["scratch"]["c_flags"].replace(" -lang=c", "") + f" -i include -i build/{project.version}/include"
            return flags, ("GC/1.2.5n" if module == "main" else "GC/1.3.2")
    flags = ("-nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto "
             '-pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on '
             f"-str reuse -multibyte -i include -i build/{project.version}/include -DBUILD_VERSION=0 -DVERSION_{project.version} -DNDEBUG=1")
    if module != "main":
        flags += " -sdata 0 -sdata2 0"
    return flags, ("GC/1.2.5n" if module == "main" else "GC/1.3.2")


def compile_many(project: Project, module: str, sources: List[Path], out_dir: Path,
                 mw_version: Optional[str] = None, extra_cflags: Optional[str] = None) -> Dict[Path, Path]:
    """One mwcc invocation over many standalone sources: the process start dominates a single
    compile (63 ms for one file, 80 ms for ten), so candidate bodies are compiled together.
    Returns {source: object} for the objects that exist afterwards; a source that fails to
    compile is simply absent (mwcc goes on with the next file)."""
    flags, mw = module_flags(project, module)
    mw = mw_version or mw
    if extra_cflags:
        extra = shlex.split(extra_cflags)
        olevel = [f for f in extra if f.startswith("-O")]
        if olevel:
            flags = " ".join(shlex.quote(olevel[-1] if f.startswith("-O") else f) for f in shlex.split(flags))
        flags = " ".join([flags] + [shlex.quote(f) for f in extra if not f.startswith("-O")])
    out_dir.mkdir(parents=True, exist_ok=True)
    out: Dict[Path, Path] = {}
    # mwcc names each object after its source in the -o directory; sources must have distinct stems
    base_cmd = [str(ROOT / "build" / "tools" / "wibo"), str(ROOT / "build" / "compilers" / mw / "mwcceppc.exe")]
    # -nofail: a source that fails to compile is skipped and the rest of the batch still compiles
    base_cmd += shlex.split(flags) + ["-nofail", "-c", "-o", str(out_dir)]
    for o in (out_dir / (s.stem + ".o") for s in sources):
        o.unlink(missing_ok=True)

    def one_chunk(chunk: List[Path]) -> None:
        result = subprocess.run(base_cmd + [str(s) for s in chunk], cwd=ROOT, text=True, capture_output=True, timeout=900)
        # Retain actual compiler diagnostics for deterministic repair passes.
        (out_dir / (chunk[0].stem + '.log')).write_text(result.stdout + result.stderr)

    # parallel: chunks of up to COMPILE_CHUNK sources, COMPILE_WORKERS mwcc processes at once
    # (a process start is ~80 ms, a source in a batch ~2-8 ms)
    n = len(sources)
    if n > COMPILE_CHUNK:
        per = min(COMPILE_CHUNK_MAX, max(COMPILE_CHUNK, (n + COMPILE_WORKERS - 1) // COMPILE_WORKERS))
        chunks = [sources[i:i + per] for i in range(0, n, per)]
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=COMPILE_WORKERS) as ex:
            list(ex.map(one_chunk, chunks))
    elif n:
        one_chunk(sources)
    for s_ in sources:
        o = out_dir / (s_.stem + ".o")
        if o.exists():
            out[s_] = o
    return out


COMPILE_CHUNK = 24
COMPILE_CHUNK_MAX = 240
COMPILE_WORKERS = 12


def check_many(project: Project, items: List[Tuple[str, Path]], max_diff_lines: int = 0,
               mw_version: Optional[str] = None, extra_cflags: Optional[str] = None) -> Dict[str, CheckResult]:
    """`check` for many (symbol, source) pairs at once: the uncarved ones are compiled in
    parallel batches (one mwcc process per chunk instead of one per function), then diffed
    one by one; carved ones go through `check`. Returns {symbol: result}."""
    results: Dict[str, CheckResult] = {}
    # groups by module and unit options (a unit may carry its own compiler version / flags);
    # carved units are diffed against their own retail object, with their own text when no
    # source is given
    groups: Dict[tuple, List[Tuple[str, Symbol, Optional[Path], str]]] = {}
    for symbol, source in items:
        sym = project.resolve(symbol)
        if sym is None:
            results[symbol] = CheckResult(False, symbol, "", error="unknown or ambiguous symbol (use module:name)")
            continue
        unit_src = project.unit_of(sym)
        if project.target_object_for(sym) is None or (unit_src is None and source is None):
            results[symbol] = check(project, symbol, max_diff_lines, source=source,
                                    mw_version=mw_version, extra_cflags=extra_cflags)
            continue
        ucfg = (project.unit_record(unit_src) or {}) if unit_src else {}
        key = (sym.module, mw_version or ucfg.get("mw_version"),
               extra_cflags or " ".join(ucfg.get("extra_cflags") or []) or None)
        unit = project.objdiff_unit_name(sym.module, unit_src) if unit_src else ""
        groups.setdefault(key, []).append((symbol, sym, source if source is not None else unit_source_path(project, unit_src), unit))
    for (module, mw, extra), group in groups.items():
        cdir = STATE_DIR / "work" / "many" / module
        cdir.mkdir(parents=True, exist_ok=True)
        srcs: List[Path] = []
        for symbol, sym, source, unit in group:
            f = cdir / (project.key(sym).replace(":", "__") + ".c")
            f.write_text(source.read_text())
            srcs.append(f)
        cands = [(mw, extra)] if (mw or extra) else version_candidates(project, module)
        chosen_ver: Dict[Path, Tuple[Optional[str], Optional[str]]] = {}
        if len(cands) > 1 and any(not unit for _, _, _, unit in group):
            # uncarved functions: every candidate build, the best object per function is kept
            per_ver = {c: compile_many(project, module, srcs, cdir / "obj" / (c[0].replace("/", "_") + ("_stmw" if c[1] else "")), c[0], c[1]) for c in cands}
            objs = {}
            for (symbol, sym, source, unit), f in zip(group, srcs):
                if unit:
                    o = per_ver[cands[0]].get(f)
                    if o: objs[f] = o; chosen_ver[f] = cands[0]
                    continue
                tw = words(project.target_object_for(sym), sym.name)
                best = None
                for c in cands:
                    o = per_ver[c].get(f)
                    if not o: continue
                    ow = words(o, sym.name)
                    pct = word_score(tw, ow)[0] if tw and ow else -1.0
                    if best is None or pct > best[0]:
                        best = (pct, c, o)
                if best:
                    objs[f] = best[2]; chosen_ver[f] = best[1]
        else:
            objs = compile_many(project, module, srcs, cdir / "obj", cands[0][0], cands[0][1])
            chosen_ver = {f: cands[0] for f in objs}

        def diff_one(arg) -> Tuple[str, CheckResult]:
            (symbol, sym, source, unit), f = arg
            obj = objs.get(f)
            if obj is None:
                # name the error the slow way, one process for this function only
                return symbol, check(project, symbol, max_diff_lines, source=source,
                                      mw_version=mw, extra_cflags=extra)
            target = project.target_object_for(sym)
            res = _diff(project, module, sym.name, unit, max_diff_lines, target=target, base=obj)
            if res.ok and res.matched_pool:
                mapping = {private: pooled for private, pooled, _ in res._pool_pairs}
                r = poolfix.apply(obj, mapping)
                if not r["skipped"] and r["rodata_emptied"]:
                    res2 = _diff(project, module, sym.name, unit, max_diff_lines, target=target, base=obj)
                    if res2.ok and res2.matched:
                        res2.pool_map, res2.pool = mapping, res.pool
                        res = res2
            if not unit:
                res.uncarved = True
            res.mw_version, res.extra_cflags = chosen_ver.get(f, (None, None))
            return symbol, res

        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=COMPILE_WORKERS) as ex:
            for symbol, res in ex.map(diff_one, zip(group, srcs)):
                results[symbol] = res
    return results


def words(obj: Path, name: str) -> Optional[List[int]]:
    """The function's machine words with every relocation field zeroed: the cheap, exact
    comparison for candidate loops (no objdiff, ~0.3 ms). None when the object or symbol is missing."""
    import struct
    from .poolfix import Elf
    try:
        data = obj.read_bytes()
        elf = Elf(data)
    except (OSError, ValueError):
        return None
    # the symbol's own code section: .text for almost everything, .init for the boot and
    # cache code (dtk keeps retail's section; our objects carry the declspec'd section)
    exec_idx = {sec["index"]: sec for sec in elf.sections if sec["flags"] & 4}
    sym = next((s_ for s_ in elf.symbols() if s_["name"] == name and s_["shndx"] in exec_idx), None)
    if sym is None:
        return None
    text = exec_idx[sym["shndx"]]
    lo, hi = sym["value"], sym["value"] + sym["size"]
    buf = poolfix.masked_code(elf, text, lo, hi - lo)
    n = len(buf) // 4
    return list(struct.unpack(f">{n}I", bytes(buf[:n * 4])))


def word_score(target: List[int], ours: List[int]) -> Tuple[float, List[int]]:
    """(percent of equal words, indices of the unequal ones). Positional: a shifted body
    scores low, which is what candidate loops want (the objdiff verdict runs on the winner)."""
    n = max(len(target), len(ours))
    if n == 0:
        return 0.0, []
    bad = [i for i, (t, o) in enumerate(zip(target, ours)) if t != o]
    extra = abs(len(target) - len(ours))
    return 100.0 * (n - len(bad) - extra) / n, bad


def function_score(project: Project, symbol_name: str, target: Path, obj: Path) -> Tuple[bool, float]:
    """(matched, positional score) from one objdiff run without the rendered diff: the cheap
    verdict for candidate loops (a pool match is not detected here; the full check is run on
    the winner)."""
    cp = run([str(OBJDIFF), "diff", "-1", str(target), "-2", str(obj), "-o", "-", "--format", "json", symbol_name])
    if cp.returncode != 0:
        return False, -1.0
    try:
        data = json.loads(cp.stdout)
    except ValueError:
        return False, -1.0
    for s_ in data.get("left", {}).get("symbols", []):
        if s_.get("name") == symbol_name and "match_percent" in s_:
            pct = float(s_["match_percent"])
            return pct >= 100.0, pct
    return False, 0.0


def function_rows(project: Project, symbol_name: str, target: Path, obj: Path):
    """objdiff's aligned instruction rows (target, ours) for one object, or None."""
    cp = run([str(OBJDIFF), "diff", "-1", str(target), "-2", str(obj), "-o", "-", "--format", "json", symbol_name])
    if cp.returncode != 0:
        return None
    try:
        data = json.loads(cp.stdout)
    except ValueError:
        return None
    l = next((s_ for s_ in data.get("left", {}).get("symbols", []) if s_.get("name") == symbol_name), None)
    r = next((s_ for s_ in data.get("right", {}).get("symbols", []) if s_.get("name") == symbol_name), None)
    if l is None or r is None:
        return None
    return l.get("instructions", []), r.get("instructions", []), float(l.get("match_percent", 0.0))


def compile_source(project: Project, module: str, source: Path, obj: Path,
                   mw_version: Optional[str] = None, extra_cflags: Optional[str] = None) -> subprocess.CompletedProcess:
    """Compile a standalone source with the module's flags into `obj` (no unit involved);
    a unit-specific compiler version or extra flags (last flag wins in mwcc) override them."""
    flags, mw = module_flags(project, module)
    mw = mw_version or mw
    if extra_cflags:
        extra = shlex.split(extra_cflags)
        olevel = [f for f in extra if f.startswith("-O")]
        if olevel:  # mwcc keeps the first -O it sees: replace the module's
            flags = " ".join(shlex.quote(olevel[-1] if f.startswith("-O") else f) for f in shlex.split(flags))
        flags = " ".join([flags] + [shlex.quote(f) for f in extra if not f.startswith("-O")])
    obj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [str(ROOT / "build" / "tools" / "wibo"), str(ROOT / "build" / "compilers" / mw / "mwcceppc.exe")]
    cmd += shlex.split(flags) + ["-c", str(source), "-o", str(obj)]
    return subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True, timeout=120)


def unit_source_path(project: Project, unit_src: str) -> Path:
    """Where the unit's C lives: src/ for standalone units, build/<v>/gen/ for block units."""
    u = project.unit_record(unit_src)
    if u and u.get("tu"):
        return project.build_dir / "gen" / unit_src
    return ROOT / "src" / unit_src


def compile_unit(project: Project, unit: str, unit_src: str,
                 source: Optional[Path] = None) -> subprocess.CompletedProcess:
    """Compile one unit straight with mwcc (via wibo) into its objdiff base object.

    No ninja and no build lock: two agents compile two different files, so nothing
    is shared. The flags come from objdiff.json (the same ones ninja uses) plus the
    include dirs the ninja rule adds. ninja will still consider the object up to
    date at relink time because the object is newer than its source. `source`
    overrides the input (an agent's work copy, already assembled with the TU prologue).
    """
    meta = project.objdiff_units().get(unit, {})
    flags = meta.get("scratch", {}).get("c_flags", "").replace(" -lang=c", "")
    flags += f" -i include -i build/{project.version}/include"
    ucfg = project.unit_record(unit_src) or {}
    mw = ucfg.get("mw_version") or ("GC/1.2.5n" if unit.startswith("main/") else "GC/1.3.2")
    obj = _base_object(project, unit)
    obj.parent.mkdir(parents=True, exist_ok=True)
    src = source or unit_source_path(project, unit_src)
    cmd = [str(ROOT / "build" / "tools" / "wibo"), str(ROOT / "build" / "compilers" / mw / "mwcceppc.exe")]
    cmd += shlex.split(flags) + ucfg.get("extra_cflags", []) + ["-c", str(src), "-o", str(obj)]
    return subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True, timeout=120)


CANDIDATE_VERSIONS = ["GC/1.2.5", "GC/1.2.5n", "GC/1.3", "GC/1.3.2", "GC/2.0", "GC/2.5", "GC/2.7"]


def check_versions(project: Project, symbol: str, versions: List[str]) -> Dict[str, float]:
    """Compile the unit under several compiler versions; return symbol match % per version.

    Uses the unit's flags from objdiff.json, wibo + build/compilers/<ver>/mwcceppc.exe,
    and objdiff-cli in two-object mode. Never touches the ninja build.
    """
    sym = project.resolve(symbol)
    unit_src = project.unit_of(sym) if sym else None
    if not sym or not unit_src:
        return {}
    symbol = sym.name
    unit = project.objdiff_unit_name(sym.module, unit_src)
    meta = project.objdiff_units().get(unit, {})
    # objdiff's scratch flags omit the include dirs the ninja rule adds per unit
    flags = meta.get("scratch", {}).get("c_flags", "").replace(" -lang=c", "")
    flags += f" -i include -i build/{project.version}/include"
    target = ROOT / meta.get("target_path", "")
    src = unit_source_path(project, unit_src)
    wibo = ROOT / "build" / "tools" / "wibo"
    out: Dict[str, float] = {}
    tmp = STATE_DIR / "versions" / symbol
    tmp.mkdir(parents=True, exist_ok=True)
    for ver in versions:
        mwcc = ROOT / "build" / "compilers" / ver / "mwcceppc.exe"
        if not mwcc.exists():
            out[ver] = -1.0
            continue
        obj = tmp / (ver.replace("/", "_") + ".o")
        # flags carry quoted pragmas: -pragma "cats off"
        cmd = [str(wibo), str(mwcc)] + shlex.split(flags) + ["-c", str(src), "-o", str(obj)]
        cp = subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True)
        if cp.returncode != 0 or not obj.exists():
            (tmp / (ver.replace("/", "_") + ".err")).write_text(cp.stdout + cp.stderr)
            out[ver] = -2.0
            continue
        cp = run([str(OBJDIFF), "diff", "-1", str(target), "-2", str(obj), "-o", "-", "--format", "json"])
        if cp.returncode != 0:
            out[ver] = -3.0
            continue
        data = json.loads(cp.stdout)
        pct = 0.0
        for s in data.get("left", {}).get("symbols", []):
            if s.get("name") == symbol and "match_percent" in s:
                pct = float(s["match_percent"])
        out[ver] = pct
    return out


def unit_fully_matches(res: CheckResult) -> Optional[str]:
    """Reason the unit may not be flipped to Matching, or None if it is safe."""
    if not res.ok:
        return res.error or "check failed"
    if res.uncarved:  # only this symbol was compared, against the retail auto object
        return None if (res.matched or res.matched_pool) else f"{res.symbol}={res.percent:.1f}%"
    bad = [f"{n}={p:.1f}%" for n, p in res.symbols.items() if p < 100.0 and not (res.matched_pool and n == res.symbol)]
    if bad:
        return "functions below 100%: " + ", ".join(bad)
    if res.missing_in_base:
        return "missing from our object: " + ", ".join(res.missing_in_base)
    if res.extra_in_base:
        return "extra functions in our object: " + ", ".join(res.extra_in_base)
    bad_data = [f"{n}={p:.1f}%" for n, p in res.data_sections.items()
                if p < 100.0 and not (res.matched_pool and n in (".rodata", ".sdata2"))]
    if bad_data:
        return "data sections differ: " + ", ".join(bad_data)
    return None


def byte_diff(project: Project, module: str) -> Dict[str, object]:
    """Compare the linked module against retail: differing bytes by function, plus section
    size differences. Cheap, and it names the culprit when a hash check fails."""
    import struct as _struct
    from collections import Counter
    cfg = (project.config_dir / "config.yml").read_text().splitlines()
    obj = "sys/main.dol" if module == "main" else None
    for i, line in enumerate(cfg):
        if obj is None and line.strip() == f"name: {module}":
            obj = next(l.split(":", 1)[1].strip() for l in reversed(cfg[:i]) if l.startswith("- object:"))
            break
    if obj is None:
        return {"error": f"{module} not in config.yml"}
    retail = (ROOT / "orig" / project.version / obj).read_bytes()
    ours_path = project.module_build_dir(module) / f"{module}.rel" if module != "main" else project.build_dir / "main.dol"
    if not ours_path.exists():
        return {"error": f"{ours_path} missing"}
    ours = ours_path.read_bytes()
    out: Dict[str, object] = {"size_retail": len(retail), "size_ours": len(ours)}
    if module == "main":
        # DOL header: 7 text + 11 data sections (file offset, load address, size)
        offs = _struct.unpack(">18I", retail[0:72]); addrs = _struct.unpack(">18I", retail[72:144]); sizes = _struct.unpack(">18I", retail[144:216])
        funcs = project.functions(module)
        def fn_at(addr):
            lo, hi = 0, len(funcs) - 1
            while lo <= hi:
                m = (lo + hi) // 2
                f = funcs[m]
                if f.addr <= addr < f.end:
                    return f.name
                if addr < f.addr:
                    hi = m - 1
                else:
                    lo = m + 1
            return None
        c = Counter()
        other = 0
        for i in range(18):
            if not sizes[i]:
                continue
            for k in range(sizes[i]):
                o = offs[i] + k
                if o < len(ours) and retail[o] != ours[o]:
                    if i < 7:
                        c[fn_at(addrs[i] + k)] += 1
                    else:
                        other += 1
        out["text_diffs"] = c.most_common(12)
        out["other_diffs"] = other
        out["sections"] = []
        return out
    def secs(d):
        n, off = _struct.unpack(">II", d[12:20])
        return [(i,) + _struct.unpack(">II", d[off + 8 * i:off + 8 * i + 8]) for i in range(n)]
    sa, sb = secs(retail), secs(ours)
    out["sections"] = [(i, hex(oa & ~3), sza, szb) for (i, oa, sza), (_, ob, szb) in zip(sa, sb) if sza != szb or (oa & ~3) != (ob & ~3)]
    to, ts = sa[1][1] & ~3, sa[1][2]
    funcs = project.functions(module)
    def fn_at(off):
        lo, hi = 0, len(funcs) - 1
        while lo <= hi:
            m = (lo + hi) // 2
            f = funcs[m]
            if f.addr <= off < f.end:
                return f.name
            if off < f.addr:
                hi = m - 1
            else:
                lo = m + 1
        return None
    c = Counter()
    for i in range(to, min(to + ts, len(retail), len(ours))):
        if retail[i] != ours[i]:
            c[fn_at(i - to)] += 1
    out["text_diffs"] = c.most_common(12)
    out["other_diffs"] = sum(1 for i in range(min(len(retail), len(ours))) if retail[i] != ours[i]) - sum(c.values())
    return out

def why_link(project: Project, symbol: str) -> Dict[str, object]:
    """Link with just this function's unit flipped to Matching and name where the bytes
    differ. The unit must exist (a rejected match keeps its split range). Restores the
    status afterwards. Deterministic diagnosis for 'matched at the object, not at link'."""
    from .ledger import Ledger  # scoped: avoid the ledger import at oracle load
    sym = project.resolve(symbol)
    unit_src = project.unit_of(sym) if sym else None
    if not unit_src:
        return {"ok": False, "error": "no unit for this function"}
    key = project.key(sym)
    body = None
    for cand in sorted((STATE_DIR / "attempts").glob(f"{key}.linkfail.*.c"), reverse=True):
        body = cand.read_text()
        break
    with build_lock():
        rec = project.unit_record(unit_src)
        src_path = unit_source_path(project, unit_src)
        saved_src = src_path.read_text() if src_path.exists() else None
        units = project.load_units()
        for u in units:
            if u["source"] == unit_src:
                u["status"] = "matching"
        project.save_units(units)
        if body and rec and not rec.get("tu"):
            src_path.write_text(body)
        elif body and rec and rec.get("tu"):
            from . import tufile  # scoped: same reason
            tufile.splice(project, rec, body)
        configure(project)
        cp = relink(project, keep_going=True)
        diag = byte_diff(project, sym.module)
        diag["relink_rc"] = cp.returncode
        text = cp.stdout + cp.stderr
        diag["failed_units"] = re.findall(r"FAILED: \[code=\d+\] (\S+)", text)[:8]
        diag["errors"] = [l for l in text.splitlines() if l.startswith("#") and "Usage" not in l and "---" not in l][:12]
        diag["tail"] = text.strip().splitlines()[-4:]
        # restore
        units = project.load_units()
        for u in units:
            if u["source"] == unit_src:
                u["status"] = "nonmatching"
        project.save_units(units)
        if saved_src is not None and rec and not rec.get("tu"):
            src_path.write_text(saved_src)
        elif rec and rec.get("tu"):
            from . import tufile  # scoped
            tufile.remove(project, rec)
        configure(project)
        relink(project)
    return {"ok": True, "symbol": symbol, "unit": unit_src, "diag": diag}
