"""Incremental live link verification; isolate rejected units only on failure."""

from __future__ import annotations

import subprocess
import time
import json
import os
import signal
from typing import Dict, List, Optional
from pathlib import Path

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
    changed = False
    for u in units:
        if u["source"] in sources and u['status'] != status:
            u["status"] = status
            changed = True
    if changed:
        p.save_units(units)


def _relink(p: Project) -> bool:
    # Ninja tracks units.json, split config, sources and headers, including its
    # own configure edge. Explicit configure invalidated otherwise clean work.
    cp = oracle.relink(p)
    with (STATE_DIR / 'verify_builds.jsonl').open('a') as log:
        log.write(json.dumps(dict(t=time.time(), ok=cp.returncode == 0, output=cp.stdout + cp.stderr)) + '\n')
    if cp.returncode:
        (STATE_DIR / 'verify_last_failure.log').write_text(cp.stdout + cp.stderr)
    return cp.returncode == 0


@oracle.build_lock('submit.lock', timeout_s=1800)
def verify(p: Project, message: Optional[str] = None) -> Dict[str, object]:
    """Relink with every pending unit Matching; commit on success; bisect on failure."""
    l = Ledger()
    keys = pending(l)
    journal = STATE_DIR / 'verify_dependencies.jsonl'
    dependencies = [str(ROOT / path) for line in journal.read_text().splitlines() for path in json.loads(line)] if journal.exists() else []
    if not keys and not dependencies:
        return {"ok": True, "verified": [], "rejected": [], "note": "nothing pending"}
    units = _units_for(p, keys)
    if missing := sorted(set(keys) - units.keys()):
        return dict(ok=False, error=f'pending functions have no units: {missing}', verified=[], rejected=[])
    sources = []
    for source in units.values():
        rec = p.unit_record(source)
        sources.append(ROOT / 'src' / (rec['tu'] if rec and rec.get('tu') else source))
    t0 = time.time()
    with oracle.build_lock():
        _set_status(p, list(units.values()), 'matching')
        if _relink(p):
            good, bad = list(units), []
            fast_path = True
        else:
            # Establish a known-good baseline only after an actual failure.
            # This distinguishes a bad candidate from a pre-existing breakage.
            _set_status(p, list(units.values()), "nonmatching")
            if not _relink(p):
                _set_status(p, list(units.values()), 'matching')
                return {"ok": False, "error": "baseline relink failed with all pending units held back; "
                        "the tree is broken independently of them; pending status restored",
                        "verified": [], "rejected": [], 'secs': round(time.time() - t0, 3)}
            good, bad = _bisect(p, list(units), units, known_failure=True)
            fast_path = False
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
                return {"ok": False, "error": "relink failed after removing rejected units; accepted units remain matching",
                        "rejected": bad, "verified": []}
        commit = None
        if good or bad or dependencies:
            files = [str(p.units_path)]
            # Rejection also changes existing TU files. Include those and tracked
            # deletions, but not removed candidates that were never committed.
            for source in sources:
                if source.exists() or subprocess.run(['git', 'ls-files', '--error-unmatch', str(source)],
                        cwd=ROOT, capture_output=True).returncode == 0:
                    files.append(str(source))
            for mod in {p.resolve(k).module for k in good + bad}:
                d = p.module_config_dir(mod)
                files += [str(d / "splits.txt"), str(d / "symbols.txt")]
            files.extend(dependencies)
            files = sorted(set(files))
            subprocess.run(["git", "add", '--', *files], cwd=ROOT, capture_output=True, check=True)
            msg = message or f"match: {len(good)} functions link-verified"
            names = ", ".join(p.key(p.resolve(k)) for k in good[:8]) + (" ..." if len(good) > 8 else "")
            changed = subprocess.run(['git', 'diff', '--cached', '--quiet', '--', *files], cwd=ROOT).returncode
            if changed:
                subprocess.run(["git", "commit", '--only', "-q", "-m", msg + (f" ({names})" if names else ''), '--', *files],
                               cwd=ROOT, capture_output=True, check=True)
            commit = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=ROOT, text=True,
                                    capture_output=True).stdout.strip()
            for k in good:
                l.db.execute("UPDATE functions SET link_state='verified', matched_commit=? WHERE symbol=?", (commit, k))
            journal.unlink(missing_ok=True)
    return {"ok": True, "verified": good, "rejected": bad, "commit": commit,
            "fast_path": fast_path, "secs": round(time.time() - t0, 3)}


def _bisect(p: Project, keys: List[str], units: Dict[str, str], known_failure=False) -> tuple[List[str], List[str]]:
    """Return (good, bad). Assumes the caller holds the build lock."""
    _set_status(p, [units[k] for k in keys], "matching")
    if not known_failure and _relink(p):
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


def watch(version: str, interval: float, until_pid: Optional[int] = None,
          stop_file: Optional[Path] = None, message: Optional[str] = None):
    """Drain completed work periodically; an outlier model cannot delay commits.

    Stop signals are observed between transactions, never in the middle of
    a link, rejection rollback or commit. Parent death triggers a final drain.
    """
    stop_requested = False

    def request_stop(signum, frame):
        nonlocal stop_requested
        stop_requested = True

    signal.signal(signal.SIGTERM, request_stop)
    signal.signal(signal.SIGINT, request_stop)
    while True:
        if pending(Ledger()) or (STATE_DIR / 'verify_dependencies.jsonl').exists():
            try:
                result = verify(Project(version), message)
            except Exception as error:
                result = dict(ok=False, error=str(error), verified=[], rejected=[])
            print(json.dumps(dict(timestamp=time.time(), **result)), flush=True)
        deadline = time.monotonic() + interval
        while True:
            stopping = stop_requested or (stop_file is not None and stop_file.exists())
            if until_pid:
                try:
                    os.kill(until_pid, 0)
                except ProcessLookupError:
                    stopping = True
            if stopping:
                # A submit may have completed during the last sleep.
                if pending(Ledger()) or (STATE_DIR / 'verify_dependencies.jsonl').exists():
                    result = verify(Project(version), message)
                    print(json.dumps(dict(timestamp=time.time(), **result)), flush=True)
                return
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                break
            time.sleep(min(1.0, remaining))
