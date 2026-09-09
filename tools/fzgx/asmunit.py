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
        with oracle.build_lock("units.lock"):
            units = p.load_units()
            for u in units:
                if u["module"] == cr.module and u["source"] == cr.source:
                    u["source"] = s_source; u["status"] = "matching"; u["asm"] = True
                    u.pop("tu", None)
            p.save_units(units)
        if c_src.exists():
            c_src.unlink()  # the carve's stub: the unit is assembly
        made.append((s, cr.module, cr.source, s_source))
    if not made:
        return {"ok": True, "made": [], "note": "nothing to do"}
    with oracle.build_lock():
        cp = oracle.configure(p)
        if cp.returncode != 0:
            raise RuntimeError(cp.stderr[-1500:])
        cp = oracle.run(["ninja", p.rel(p.build_dir / "config.json")])  # the split writes the units' asm
        if cp.returncode != 0:
            raise RuntimeError((cp.stdout + cp.stderr)[-1500:])
        for s, module, c_source, s_source in made:
            asm = p.build_dir / "asm" / s_source
            if not asm.exists():
                uncarve(p, [x[3] for x in made], split=False)
                return {"ok": False, "error": f"{s}: no split assembly at {asm}", "made": []}
            dst = ROOT / "src" / s_source
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(asm, dst)
        cp = oracle.configure(p)
        linked = cp.returncode == 0 and oracle.relink(p).returncode == 0
        if not linked:
            for s, module, c_source, s_source in made:
                (ROOT / "src" / s_source).unlink(missing_ok=True)
            uncarve(p, [x[3] for x in made], split=True)
            return {"ok": False, "error": "the tree no longer hashes with these units; rolled back", "made": []}
    for s, module, c_source, s_source in made:
        l.db.execute("UPDATE functions SET status='asm', claimed_by=NULL, unit=? WHERE symbol=?", (s_source, s))
    l.db.commit()
    files = [str(ROOT / "src" / x[3]) for x in made] + [str(p.units_path)]
    for module in {x[1] for x in made}:
        d = p.module_config_dir(module)
        files += [str(d / "splits.txt"), str(d / "symbols.txt")]
    subprocess.run(["git", "add", *files], cwd=ROOT, capture_output=True)
    subprocess.run(["git", "commit", "-q", "-m", f"asm units: {len(made)} assembly-only functions link from their own assembly ({', '.join(x[0] for x in made[:6])}{'...' if len(made) > 6 else ''})"], cwd=ROOT, capture_output=True)
    return {"ok": True, "made": [x[0] for x in made]}
