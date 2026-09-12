"""Compile a TU file as one unit and score every function inside it against retail.

Per-function units cannot reproduce a translation unit's literal pool (retail
addresses it through one base register plus offsets). The whole-TU compile
can, once the TU's functions use the same literals in the same order. This
trial compiles `src/<tu>.c` as a single object and diffs each function's symbol
against that function's retail split object (objdiff two-object mode), so we
can see which functions still match inside the whole-TU compile and which
pool-bound functions start matching only there.
"""

from __future__ import annotations

from pathlib import Path
from typing import Dict, List, Optional

from .project import ROOT, Project
from . import oracle, tufile

def compile_tu(p: Project, tu_source: str, extra_blocks: Optional[Dict[str, str]] = None) -> tuple:
    """Compile the TU file (optionally with extra function bodies appended) as one object.
    Returns (object path or None, compiler text)."""
    module = tu_source.split("/")[1] if tu_source.startswith("rel/") else "main"
    units = [u for u in p.load_units() if u.get("tu") == tu_source]
    flags = ' '.join(units[0].get('extra_cflags') or []) if units else None
    mw = (units[0].get("mw_version") if units else None) or ("GC/1.2.5n" if module == "main" else "GC/1.3.2")
    tf = tufile.load(p, tu_source)
    text = tf.render()
    if extra_blocks:
        for name, body in extra_blocks.items():
            inc, rest = tufile.split_includes(body)
            text += "\n" + tufile.Block(name, "\n".join(inc + [""]) + rest if inc else rest).render()
    d = p.build_dir / "gen" / "tu_trial"
    d.mkdir(parents=True, exist_ok=True)
    src = d / (Path(tu_source).stem + ".c")
    src.write_text(text)
    out = src.with_suffix(".o")
    cp = oracle.compile_source(p, module, src, out, mw_version=mw, extra_cflags=flags)
    msg = "\n".join(l for l in (cp.stdout + cp.stderr).splitlines() if "Usage Warning" not in l).strip()
    return (out if cp.returncode == 0 and out.exists() else None), msg[-3000:]


def score(p: Project, tu_source: str, obj: Path) -> Dict[str, Optional[float]]:
    """Per-function match % of the whole-TU object against each function's retail object."""
    module = tu_source.split("/")[1] if tu_source.startswith("rel/") else "main"
    tf = tufile.load(p, tu_source)
    out: Dict[str, Optional[float]] = {}
    for b in tf.blocks:
        sym = p.find_symbol(b.name, module)
        unit_src = p.unit_of(sym) if sym else None
        meta = p.objdiff_units().get(p.objdiff_unit_name(module, unit_src), {}) if unit_src else {}
        target = ROOT / meta.get("target_path", "") if meta.get("target_path") else None
        if not target or not target.exists():
            out[b.name] = None
            continue
        check = oracle._diff(p, module, b.name, '', 0, target=target, base=obj)
        out[b.name] = (100.0 if check.matched or check.matched_pool else check.percent) if check.ok else None
    return out


def trial(p: Project, tu_source: str, extra_blocks: Optional[Dict[str, str]] = None) -> Dict[str, object]:
    obj, msg = compile_tu(p, tu_source, extra_blocks)
    if obj is None:
        return {"ok": False, "tu": tu_source, "error": msg}
    scores = score(p, tu_source, obj)
    full = sum(1 for v in scores.values() if v is not None and v >= 100.0)
    return {"ok": True, "tu": tu_source, "functions": len(scores), "at_100": full,
            "below": {k: v for k, v in scores.items() if v is None or v < 100.0}, "object": p.rel(obj)}
