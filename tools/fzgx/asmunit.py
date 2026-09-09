"""Assembly units: a function whose retail body no C can produce (a privileged instruction
and `blr`: the SDK wrote it in assembly) links from its own assembly, the file dtk's split
writes for the unit, copied into src/ and assembled by the build. Byte-exact by construction;
the ledger records the function as `asm`, done but not decompiled.
"""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path
from typing import Dict, List

from . import carve, oracle
from .ledger import Ledger
from .project import ROOT, Project
from .uncarve import uncarve


import re

_BRANCH_RE = re.compile(r"^(/\* [0-9A-F]{8} [0-9A-F]{8}  ([0-9A-F]{2}) ([0-9A-F]{2}) ([0-9A-F]{2}) ([0-9A-F]{2}) \*/\t)(b\w+?)([+-])( .*)$")


def fix_branch_hints(text: str) -> tuple:
    """dtk prints the raw branch-hint bit (y=1 as `+`); GNU as reads `+`/`-` relative to the
    branch direction (a backward branch is predicted taken by default, so `+` encodes y=0).
    A hinted backward conditional branch must be spelled `-` to assemble to retail's bytes."""
    out, n = [], 0
    for line in text.splitlines():
        m = _BRANCH_RE.match(line)
        if m:
            word = int("".join(m.group(2, 3, 4, 5)), 16)
            if (word >> 26) == 16 and word & 0x8000 and m.group(7) == "+":  # bc, BD < 0, y=1
                line = f"{m.group(1)}{m.group(6)}-{m.group(8)}  # `+` in dtk's output: raw hint bit, backward branch"
                n += 1
        out.append(line)
    return "\n".join(out) + "\n", n


def make(p: Project, symbols: List[str]) -> Dict[str, object]:
    """Carve each symbol into an assembly-backed unit, split, copy the asm, relink and hash.
    On a hash failure every unit of this call is uncarved and nothing is kept."""
    l = Ledger()
    made: List[tuple] = []
    for s in symbols:
        sym = p.resolve(s)
        if sym is None or p.unit_of(sym):
            continue
        cr = carve.carve(p, s)
        c_src = ROOT / "src" / cr.source
        s_source = cr.source[:-2] + ".s"
        # the unit keeps its .c name (the split's unit name, what uncarve knows); `asm` makes
        # configure compile src/<name>.s instead
        with oracle.build_lock("units.lock"):
            units = p.load_units()
            for u in units:
                if u["module"] == cr.module and u["source"] == cr.source:
                    u["status"] = "matching"; u["asm"] = True
                    u.pop("tu", None)
            p.save_units(units)
        if c_src.exists():
            c_src.unlink()  # the carve's stub: the unit is assembly
        made.append((s, cr.module, cr.source, s_source))
    if not made:
        return {"ok": True, "made": [], "note": "nothing to do"}
    return finalize(p, made)


def resume(p: Project) -> Dict[str, object]:
    """Finish asm units that were carved but not yet linked and recorded."""
    l = Ledger()
    done = {r[0] for r in l.db.execute("select symbol from functions where status='asm'")}
    made = []
    for u in p.load_units():
        if u.get("asm") and u["symbols"] and u["symbols"][0] not in done:
            made.append((u["symbols"][0], u["module"], u["source"], u["source"][:-2] + ".s"))
    if not made:
        return {"ok": True, "made": [], "note": "nothing to resume"}
    return finalize(p, made)


def finalize(p: Project, made: List[tuple]) -> Dict[str, object]:
    import time  # scoped: phase timing
    l = Ledger()
    t0 = time.time()
    def phase(msg: str) -> None:
        print(f"  asm-unit: {msg} ({time.time() - t0:.1f}s)", flush=True)
    with oracle.build_lock():
        phase("build lock acquired")
        cp = oracle.configure(p)
        if cp.returncode != 0:
            raise RuntimeError(cp.stderr[-1500:])
        phase("configured")
        cp = oracle.run(["ninja", p.rel(p.build_dir / "config.json")])  # the split writes the units' asm
        if cp.returncode != 0:
            raise RuntimeError((cp.stdout + cp.stderr)[-1500:])
        phase("split")
        for s, module, c_source, s_source in made:
            asm = p.module_build_dir(module) / "asm" / s_source
            if not asm.exists():
                uncarve(p, [x[2] for x in made], split=False)
                return {"ok": False, "error": f"{s}: no split assembly at {asm}", "made": []}
            dst = ROOT / "src" / s_source
            dst.parent.mkdir(parents=True, exist_ok=True)
            text, n = fix_branch_hints(asm.read_text())
            dst.write_text(text)
            if n:
                phase(f"{s}: {n} backward branch hint(s) respelled for GNU as")
        phase("assembly copied")
        cp = oracle.configure(p)
        if cp.returncode == 0:
            cp = oracle.relink(p)
        linked = cp.returncode == 0
        phase("relinked" if linked else "relink FAILED")
    if not linked:
        # outside the lock: uncarve takes it again (flock is not reentrant)
        tail = (cp.stdout + cp.stderr)[-3000:]
        print(tail, flush=True)
        for s, module, c_source, s_source in made:
            (ROOT / "src" / s_source).unlink(missing_ok=True)
        uncarve(p, [x[2] for x in made], split=True)
        return {"ok": False, "error": "the tree no longer hashes with these units; rolled back", "made": [], "log": tail}
    for s, module, c_source, s_source in made:
        l.db.execute("UPDATE functions SET status='asm', claimed_by=NULL, unit=? WHERE symbol=?", (c_source, s))
    l.db.commit()
    files = [str(ROOT / "src" / x[3]) for x in made] + [str(p.units_path)]
    for module in {x[1] for x in made}:
        d = p.module_config_dir(module)
        files += [str(d / "splits.txt"), str(d / "symbols.txt")]
    subprocess.run(["git", "add", *files], cwd=ROOT, capture_output=True)
    subprocess.run(["git", "commit", "-q", "-m", f"asm units: {len(made)} assembly-only functions link from their own assembly ({', '.join(x[0] for x in made[:6])}{'...' if len(made) > 6 else ''})"], cwd=ROOT, capture_output=True)
    return {"ok": True, "made": [x[0] for x in made]}
