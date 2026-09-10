"""Deferred link verification.

`submit` accepts a unit on the per-object oracle (objdiff 100% for every
function in the unit, data sections equal, lint clean) and flips it to
Matching without relinking. This module relinks once for many accepted units,
verifies every hash, commits them together, and on the rare failure bisects
to find the units whose objects do not link byte-exact.

Why: a relink costs configure (~1 s) + link + hash (~1–3 s) and runs under the
single build lock, so at 16–24 agents in parallel each submit waited ~20 s in
the queue. One relink per batch removes that from the critical path entirely.
"""

from __future__ import annotations

import subprocess
import time
from typing import Dict, List, Optional

from . import oracle, tufile
from .ledger import Ledger
from .project import ROOT, STATE_DIR, Project

STUB = '#include "types.h"\n\n// {symbol}: carved by fzgx; {note}\n'


def pending(l: Ledger) -> List[str]:
    """Symbols (ledger keys) accepted but not yet link-verified."""
    return [r["symbol"] for r in l.db.execute("SELECT symbol FROM functions WHERE link_state='pending' ORDER BY addr")]


def _units_for(p: Project, keys: List[str]) -> Dict[str, str]:
    """ledger key -> unit source path."""
    out = {}
    for k in keys:
        sym = p.resolve(k)
        if sym:
            u = p.unit_of(sym)
            if u:
                out[k] = u
    return out


def _set_status(p: Project, sources: List[str], status: str) -> None:
    units = p.load_units()
    for u in units:
        if u["source"] in sources:
            u["status"] = status
    p.save_units(units)


def _relink(p: Project) -> bool:
    cp = oracle.configure(p)
    if cp.returncode != 0:
        (STATE_DIR / 'verify_last_failure.log').write_text(cp.stdout + cp.stderr)
        return False
    cp = oracle.relink(p)
    if cp.returncode:
        (STATE_DIR / 'verify_last_failure.log').write_text(cp.stdout + cp.stderr)
    return cp.returncode == 0


def verify(p: Project, message: Optional[str] = None) -> Dict[str, object]:
    """Relink with every pending unit Matching; commit on success; bisect on failure."""
    l = Ledger()
    keys = pending(l)
    if not keys:
        return {"ok": True, "verified": [], "rejected": [], "note": "nothing pending"}
    units = _units_for(p, keys)
    t0 = time.time()
    with oracle.build_lock():
        # baseline first: if the tree does not link with every pending unit held back, the
        # fault is elsewhere (a header, a tool change) and bisecting would blame them all
        _set_status(p, list(units.values()), "nonmatching")
        if not _relink(p):
            _set_status(p, list(units.values()), "nonmatching")
            return {"ok": False, "error": "baseline relink failed with all pending units held back; "
                    "the tree is broken independently of them (byte-diff the REL); nothing changed",
                    "verified": [], "rejected": []}
        good, bad = _bisect(p, list(units.keys()), units)
        # final state: good units Matching, bad units uncarved (no unit without matched code); relink once more if we bisected
        if bad:
            from .uncarve import uncarve
            for k in bad:
                keep = STATE_DIR / "attempts" / f"{k}.linkfail.{int(time.time())}.c"
                keep.parent.mkdir(parents=True, exist_ok=True)
                rec = p.unit_record(units[k])
                if rec and rec.get("tu"):
                    keep.write_text(tufile.remove(p, rec) or "")
                else:
                    src = ROOT / "src" / units[k]
                    if src.exists():
                        keep.write_bytes(src.read_bytes())
                l.db.execute("UPDATE functions SET status='unmatched', link_state=NULL, attempts=attempts+1 WHERE symbol=?", (k,))
                l.db.execute("UPDATE attempts SET outcome='link-mismatch', notes=COALESCE(notes,'')||' [object matched but link differed]' "
                             "WHERE id=(SELECT id FROM attempts WHERE symbol=? ORDER BY id DESC LIMIT 1)", (k,))
            uncarve(p, [units[k] for k in bad], split=False)  # the unit, its split range and gen stub
            _set_status(p, [units[k] for k in good], "matching")
            if not _relink(p):
                return {"ok": False, "error": "relink failed even after bisect; tree left with all pending units nonmatching",
                        "rejected": bad, "verified": []}
        commit = None
        if good:
            files = [str(p.units_path)]
            for k in good:
                rec = p.unit_record(units[k])
                files.append(str(ROOT / "src" / (rec["tu"] if rec and rec.get("tu") else units[k])))
            for mod in {p.resolve(k).module for k in good}:
                d = p.module_config_dir(mod)
                files += [str(d / "splits.txt"), str(d / "symbols.txt")]
            subprocess.run(["git", "add", *files], cwd=ROOT, capture_output=True)
            msg = message or f"match: {len(good)} functions link-verified"
            names = ", ".join(p.resolve(k).name for k in good[:8]) + (" ..." if len(good) > 8 else "")
            subprocess.run(["git", "commit", "-q", "-m", f"{msg} ({names})"], cwd=ROOT, capture_output=True)
            commit = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=ROOT, text=True,
                                    capture_output=True).stdout.strip()
            for k in good:
                l.db.execute("UPDATE functions SET link_state='verified', matched_commit=? WHERE symbol=?", (commit, k))
    return {"ok": True, "verified": good, "rejected": bad, "commit": commit, "secs": round(time.time() - t0, 1)}


def _bisect(p: Project, keys: List[str], units: Dict[str, str]) -> tuple[List[str], List[str]]:
    """Return (good, bad). Assumes the caller holds the build lock."""
    _set_status(p, [units[k] for k in keys], "matching")
    if _relink(p):
        return keys, []
    if len(keys) == 1:
        _set_status(p, [units[keys[0]]], "nonmatching")
        return [], keys
    mid = len(keys) // 2
    left, right = keys[:mid], keys[mid:]
    # test each half in isolation (other half nonmatching)
    _set_status(p, [units[k] for k in right], "nonmatching")
    lg, lb = _bisect(p, left, units)
    _set_status(p, [units[k] for k in left], "nonmatching")
    rg, rb = _bisect(p, right, units)
    _set_status(p, [units[k] for k in lg + rg], "matching")
    return lg + rg, lb + rb
