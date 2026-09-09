"""Library layer shared by the CLI (tools/fzgx.py) and the MCP server (tools/fzgx_mcp.py).

Every function takes plain arguments and returns JSON-serialisable data; no
printing, no sys.exit. Each call opens its own Ledger (SQLite connections are
per-thread) so the MCP server can run calls concurrently.

An agent never edits the tree. `claim` gives it a private work copy under
.fzgx/work/, `write_unit` rewrites that copy and checks it, `submit` splices the
copy into the canonical source (a block of the TU file, or the standalone unit
file) once the oracle accepts it, and `release` keeps the best copy under
.fzgx/attempts/ and discards the rest.
"""

from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import time
from pathlib import Path
from typing import Any, Dict, List, Optional

from . import oracle, tufile, verify
from .carve import carve
from .context import build_context
from .ledger import Ledger
from .lint import lint_paths
from .project import ROOT, STATE_DIR, Project

DEFAULT_TTL = 1800
MAX_ATTEMPTS = int(os.environ.get("FZGX_MAX_ATTEMPTS", 3))  # a stronger-tier round raises it for its agents
MAX_CHECKS = 8       # per attempt
MAX_STALE = 2        # consecutive checks without improving the attempt's best %
STUB = '#include "types.h"\n\n// {symbol}: carved by fzgx; {note}\n'
SHADOW_PREFIX = "shadow-"   # agent ids with this prefix run A/B trials that never relink or commit
REVISE_PREFIX = "revise-"   # rewrite an already-matched unit for readability; kept only if still 100%


def _is_shadow(agent: Optional[str]) -> bool:
    return bool(agent) and (agent.startswith(SHADOW_PREFIX) or agent.startswith(REVISE_PREFIX))


def _is_revise(agent: Optional[str]) -> bool:
    return bool(agent) and agent.startswith(REVISE_PREFIX)


def _git(*args: str) -> subprocess.CompletedProcess:
    return subprocess.run(["git", *args], cwd=ROOT, text=True, capture_output=True)


def _reconfigure_and_split(p: Project) -> None:
    with oracle.build_lock():
        cp = oracle.configure(p)
        if cp.returncode != 0:
            raise RuntimeError(cp.stderr[-2000:])
        cp = oracle.run(["ninja", p.rel(p.build_dir / "config.json")])
        if cp.returncode != 0:
            raise RuntimeError((cp.stdout + cp.stderr)[-2000:])


def _unit_source(p: Project, symbol: str) -> Optional[str]:
    sym = p.resolve(symbol)
    return p.unit_of(sym) if sym else None


def _key(p: Project, symbol: str) -> str:
    sym = p.resolve(symbol)
    return p.key(sym) if sym else symbol


def _unit_label(p: Project, unit_src: str) -> str:
    """Where the unit's C is shown to live: the TU file (block units) or its own file."""
    u = p.unit_record(unit_src)
    return f"src/{u['tu']}#{u['symbols'][0]}" if u and u.get("tu") else f"src/{unit_src}"


def _canonical_text(p: Project, unit_src: str) -> str:
    u = p.unit_record(unit_src)
    if u:
        return tufile.unit_text(p, u)
    path = ROOT / "src" / unit_src
    return path.read_text() if path.exists() else ""


def _work_source(p: Project, key: str, unit_src: str) -> Optional[Path]:
    """The file to compile for a check: the agent's work copy, exactly as written."""
    work = p.work_path(key)
    return work if work.exists() else None


def _prologue_conflict(p: Project, key: str, unit_src: str) -> Optional[str]:
    """For a block unit: does the work copy also compile under its TU prologue? The compiler's
    complaint if not (the block would be spliced `noprologue` and queued for revision)."""
    u = p.unit_record(unit_src)
    work = p.work_path(key)
    if not u or not u.get("tu") or not work.exists():
        return None
    tf = tufile.load(p, u["tu"])
    if not tf.prologue.strip():
        return None
    inc, body = tufile.split_includes(work.read_text())
    have = {ln.strip() for ln in tf.prologue.splitlines()}
    extra = [ln for ln in inc if ln.strip() not in have]
    probe = work.with_suffix(".prologue.c")
    probe.write_text(tf.prologue + "\n" + ("\n".join(extra) + "\n\n" if extra else "") + body)
    unit = p.objdiff_unit_name(u["module"], unit_src)
    obj = oracle._base_object(p, unit)
    cp = oracle.compile_unit(p, unit, unit_src, probe)
    probe.unlink(missing_ok=True)
    if cp.returncode == 0:
        return None
    err = [l for l in (cp.stdout + cp.stderr).splitlines() if l.startswith("#") and "File" not in l and "---" not in l]
    return "\n".join(err[:6])[:900]


# ------------------------------------------------------------------ inventory
def sync(p: Project) -> Dict[str, int]:
    l = Ledger()
    rows = []
    for module in p.modules:
        for s in p.functions(module):
            rows.append({"symbol": p.key(s), "module": module, "unit": p.unit_of(s), "addr": s.addr, "size": s.size})
    n = l.sync_functions(rows)
    matched = 0
    for u in p.load_units():
        if u["status"] == "matching":
            for s in u.get("symbols", []):
                row = l.get(s)
                if row and row["status"] != "matched":
                    l.db.execute("UPDATE functions SET status='matched', best_percent=100, link_state='verified' WHERE symbol=?", (s,))
                    matched += 1
    return {"functions": len(rows), "inserted": n, "marked_matched": matched}


def inventory(p: Project, module: Optional[str] = None, status: Optional[str] = None,
              limit: Optional[int] = None, max_size: Optional[int] = None) -> List[Dict[str, Any]]:
    l = Ledger()
    l.expire_claims()
    rows = l.list(module=module, status=status, limit=limit)
    if max_size:
        rows = [r for r in rows if r["size"] <= max_size]
    return [{"symbol": r["symbol"], "module": r["module"], "size": r["size"], "status": r["status"],
             "attempts": r["attempts"], "best": r["best_percent"], "unit": r["unit"],
             "claimed_by": r["claimed_by"]} for r in rows]


# ---------------------------------------------------------------------- claim
def claim(p: Project, symbol: str, agent: str, ttl: int = DEFAULT_TTL,
          max_attempts: int = MAX_ATTEMPTS, no_carve: bool = False) -> Dict[str, Any]:
    l = Ledger()
    if p.resolve(symbol) is None:
        return {"ok": False, "error": f"unknown or ambiguous symbol {symbol!r} (use module:name for _prolog/_epilog)"}
    key = _key(p, symbol)
    shadow = _is_shadow(agent)
    try:
        row = l.claim(key, agent, ttl, max_attempts, shadow=shadow)
    except (LookupError, PermissionError) as e:
        return {"ok": False, "error": str(e)}
    # nothing is carved before it matches: a unit (split range, object in the link) is
    # created at submit. Until then checks diff the work copy against the retail object.
    res = None
    if _is_revise(agent) and not _unit_source(p, symbol):
        l.finish(key, "carve-failed", "unmatched", notes="revise claim on an unmatched function", shadow=True)
        return {"ok": False, "error": "revise needs a matched function"}
    unit = _unit_source(p, symbol)
    # the agent's private copy: the current source for a rewrite, a stub otherwise
    work = p.work_path(key)
    work.parent.mkdir(parents=True, exist_ok=True)
    name = p.resolve(symbol).name
    if _is_revise(agent) and unit:
        work.write_text(_canonical_text(p, unit) or STUB.format(symbol=name, note="nothing to revise"))
    else:
        work.write_text(STUB.format(symbol=name, note="write the complete unit with write_unit"))
    tu_src = tufile.tu_source_for(p, p.resolve(symbol))
    out = {"ok": True, "symbol": symbol, "unit": unit,
           "path": _unit_label(p, unit) if unit else (f"src/{tu_src}#{name} (block created at submit)" if tu_src else f"src/{p.module_src_prefix(p.resolve(symbol).module)}/{name}.c (created at submit)"),
           "attempt": row["attempts"] + 1, "max_attempts": max_attempts, "ttl": ttl,
           "budget": f"{MAX_CHECKS} checks per attempt; stop after {MAX_STALE} checks without improvement"}
    try:
        out["context"] = build_context(p, l, symbol)
    except LookupError as e:
        out["context"] = f"(no context: {e})"
    return out


def carve_many(p: Project, symbols: List[str], dry_run: bool = False) -> List[Dict[str, Any]]:
    results, created = [], False
    l = Ledger()
    for s in symbols:
        try:
            r = carve(p, s, dry_run=dry_run)
            created |= r.created
            if not dry_run:
                l.db.execute("UPDATE functions SET unit=? WHERE symbol=?", (r.source, _key(p, s)))
            results.append(r.__dict__)
        except LookupError as e:
            results.append({"symbol": s, "error": str(e)})
    if created and not dry_run:
        _reconfigure_and_split(p)
    return results


# -------------------------------------------------------------------- context
def context(p: Project, symbol: str, budget_tokens: int = 6000) -> str:
    return build_context(p, Ledger(), symbol, budget_tokens)


def read_unit(p: Project, symbol: str) -> Dict[str, Any]:
    unit = _unit_source(p, symbol)
    work = p.work_path(_key(p, symbol))
    text = work.read_text() if work.exists() else (_canonical_text(p, unit) if unit else "")
    return {"ok": True, "path": _unit_label(p, unit) if unit else "(work copy)", "source": text}


def write_unit(p: Project, symbol: str, agent: str, source: str) -> Dict[str, Any]:
    """Replace the claimed unit's work copy. The only write path a matcher has."""
    l = Ledger()
    key = _key(p, symbol)
    row = l.get(key)
    if row is None:
        return {"ok": False, "error": "unknown symbol"}
    if row["status"] != "claimed" or row["claimed_by"] != agent:
        return {"ok": False, "error": f"{symbol} is not claimed by {agent} (status {row['status']}, by {row['claimed_by']})"}
    unit = _unit_source(p, symbol)
    if "asm" in source and ("asm {" in source or "asm(" in source or "asm void" in source):
        return {"ok": False, "error": "inline asm is not allowed"}
    att = l.current_attempt(key)
    stop = _budget_stop(att)
    if stop:
        return {"ok": False, "error": stop + "; call release(symbol, agent, reason) now"}
    work = p.work_path(key)
    work.parent.mkdir(parents=True, exist_ok=True)
    work.write_text(source if source.endswith("\n") else source + "\n")
    findings = lint_paths([work])
    result = check(p, symbol)
    return {"ok": True, "path": _unit_label(p, unit) if unit else "(work copy)", "bytes": len(source),
            "lint": [{"rule": r, "line": ln, "msg": m} for _, r, ln, m in findings],
            "check": format_check(result)}


def patch_unit(p: Project, symbol: str, agent: str, old: str, new: str) -> Dict[str, Any]:
    """Edit the claimed work copy in place: `old` must occur exactly once and is replaced by `new`;
    then the same compile-and-diff as write_unit. An agent that changes one declaration or one
    statement sends a few lines instead of the whole unit."""
    key = _key(p, symbol)
    unit = _unit_source(p, symbol)
    src = _work_source(p, key, unit)
    if src is None:
        return {"ok": False, "error": "no work copy to patch: write_unit first"}
    text = Path(src).read_text()
    n = text.count(old)
    if n != 1:
        return {"ok": False, "error": f"`old` occurs {n} times in the unit; it must occur exactly once (include more context)"}
    return write_unit(p, symbol, agent, text.replace(old, new, 1))


def _budget_stop(att) -> Optional[str]:
    if att is None:
        return None
    if (att["checks"] or 0) >= MAX_CHECKS:
        return f"budget exhausted: {MAX_CHECKS} checks used"
    if (att["stale_checks"] or 0) >= MAX_STALE and (att["best_in_attempt"] or 0) < 100.0:
        return f"plateau: {MAX_STALE} consecutive checks without improvement (best {att['best_in_attempt']:.1f}%)"
    return None


# --------------------------------------------------------------------- oracle
def check(p: Project, symbol: str, max_diff_lines: int = 80, versions: Optional[str] = None) -> Dict[str, Any]:
    """Compile and diff the work copy if one exists, else the canonical unit."""
    if versions:
        vers = oracle.CANDIDATE_VERSIONS if versions == "all" else versions.split(",")
        out = oracle.check_versions(p, symbol, vers)
        return {"ok": True, "symbol": symbol, "versions": out,
                "note": "-1 compiler missing, -2 compile error, -3 diff error"}
    key = _key(p, symbol)
    unit = _unit_source(p, symbol)
    src = _work_source(p, key, unit)
    res = oracle.check(p, symbol, max_diff_lines, source=src)
    out = res.to_json()
    if src is not None:
        # every checked body is kept with its score: the (before, after) pairs of a function that
        # went on to match are the exemplars a prompt with examples needs
        try:
            hdir = STATE_DIR / "checks" / key.replace(":", "__")
            hdir.mkdir(parents=True, exist_ok=True)
            n = len(list(hdir.glob("*.c")))
            body = Path(src).read_text()
            (hdir / f"{n:03d}.c").write_text(body)
            with (hdir / "index.jsonl").open("a") as f:
                f.write(json.dumps({"n": n, "t": int(time.time()), "ok": res.ok, "percent": res.percent if res.ok else None,
                                    "adjusted": res.percent_adjusted if res.ok else None, "matched": bool(res.ok and (res.matched or res.matched_pool)),
                                    "rows": res.pool_rows if res.ok else None}) + "\n")
        except OSError:
            pass
    if res.ok and src is not None:
        conflict = _prologue_conflict(p, key, unit) if unit else None
        if conflict:
            out["prologue_conflict"] = conflict
            oracle.compile_unit(p, res.unit, unit, src)  # the probe overwrote the object; restore ours
        stats = Ledger().bump_checks(key, res.percent_adjusted if res.pool_rows else res.percent)
        out["budget"] = stats
        if stats.get("improved"):
            best = STATE_DIR / "attempts" / f"{key}.best.c"
            best.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(p.work_path(key), best)
        att = Ledger().current_attempt(key)
        stop = _budget_stop(att)
        if stop and not res.matched:
            out["stop"] = stop
    return out


def format_check(res: Dict[str, Any]) -> str:
    if "versions" in res:
        return "\n".join(f"{v:10s} {'n/a' if pct < 0 else f'{pct:.1f}%'}" for v, pct in res["versions"].items())
    if not res["ok"]:
        return f"CHECK FAILED: {res['error']}"
    verdict = "MATCH" if res["matched"] else ("MATCH (pool)" if res.get("matched_pool") else "no match")
    lines = [f"{res['symbol']}: {res['percent']:.1f}%  unit={res['unit']}  {verdict}"]
    if res["matched"] and res.get("pool_map"):
        lines.append("literal pool: private constants retargeted to the shared retail symbols (" + ", ".join(res["pool"]) + ")")
    if not res["matched"] and res.get("pool_rows"):
        lines.append(f"{res['pool_rows']} row(s) marked `p` are literal-pool relocations ({', '.join(res['pool'])}); the tooling "
                     f"retargets them at submit, so they already count as matching: {res['percent_adjusted']:.1f}% "
                     "is your real score. Fix only the other marked rows.")
    if res.get("matched_pool"):
        lines.append("pool: the only differences are relocations to shared literal-pool constants whose value "
                     "you reproduce (" + ", ".join(res["pool"]) + "); this counts as a match: call submit.")
    others = {k: v for k, v in res["symbols"].items() if k != res["symbol"]}
    if others:
        lines.append("other functions in unit: " + ", ".join(f"{k}={v:.0f}%" for k, v in others.items()))
    if res["data_sections"]:
        lines.append("data: " + ", ".join(f"{k}={v:.0f}%" for k, v in res["data_sections"].items()))
    if res["missing_in_base"]:
        lines.append("missing in our object: " + ", ".join(res["missing_in_base"]))
    if res["extra_in_base"]:
        lines.append("extra in our object: " + ", ".join(res["extra_in_base"]))
    if res["diff"] and not res.get("matched_pool"):
        lines.append("diff (target | ours):")
        lines.extend(res["diff"])
    if res.get("prologue_conflict"):
        lines.append("PROLOGUE CONFLICT: your unit matches on its own but does not compile under the file's prologue "
                     "(shown in the context as 'already in scope'), so it would be queued for revision. "
                     "Drop or align the declaration named below:\n" + res["prologue_conflict"])
    b = res.get("budget")
    if b:
        lines.append(f"budget: check {b['checks']}/{MAX_CHECKS}, {b['stale']}/{MAX_STALE} without improvement, best this attempt {b['best_in_attempt']:.1f}%")
    if res.get("stop"):
        lines.append(f"STOP: {res['stop']}. Do not write again; call release(symbol, agent, reason).")
    return "\n".join(lines)


def _promote_referenced_locals(p: Project, key: str, unit_src: Optional[str], unit: str) -> List[str]:
    """Symbols our compiled object references that the config marks scope:local get scope:global."""
    obj = oracle._base_object(p, unit) if unit_src else STATE_DIR / "work" / (key.replace(":", "__") + ".o")
    if not obj.exists():
        return []
    from .poolfix import Elf  # scoped: tiny ELF reader, only here
    try:
        und = [e["name"] for e in Elf(obj.read_bytes()).symbols() if e["shndx"] == 0 and e["name"]]
    except (ValueError, IndexError):
        return []
    by_module: Dict[str, List[str]] = {}
    for n in und:
        sd = p.find_symbol(n)
        if sd and sd.scope == "local":
            by_module.setdefault(sd.module, []).append(n)
    out: List[str] = []
    for module, names in by_module.items():
        out += p.promote_to_global(module, names)
    return out


def _install(p: Project, unit_src: str, text: str, pool: bool = False) -> None:
    """Make `text` the canonical source of the unit: a block of its TU file, or its own file.

    A block's generated unit must compile: if it does not under the TU prologue (a private
    declaration that disagrees with a header), the block keeps its own includes instead."""
    u = p.unit_record(unit_src)
    if u and u.get("tu"):
        flags = ["pool"] if pool else None
        tufile.splice(p, u, text, extra_flags=flags)
        unit = p.objdiff_unit_name(u["module"], unit_src)
        if oracle.compile_unit(p, unit, unit_src).returncode != 0:
            tufile.splice(p, u, text, noprologue=True, extra_flags=flags)
    else:
        path = ROOT / "src" / unit_src
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)


def _discard_work(p: Project, key: str) -> None:
    p.work_path(key).unlink(missing_ok=True)


def submit(p: Project, symbol: str, agent: str = "unknown", message: str = "",
           harness: Optional[str] = None, model: Optional[str] = None,
           mw_version: Optional[str] = None, extra_cflags: Optional[str] = None,
           names: Optional[List[Dict[str, str]]] = None, tokens_in: int = 0,
           tokens_out: int = 0, cost_usd: float = 0.0, max_diff_lines: int = 40) -> Dict[str, Any]:
    l = Ledger()
    sym = p.resolve(symbol)
    if sym is None:
        return {"ok": False, "error": "unknown or ambiguous symbol"}
    key = p.key(sym)
    unit_src = p.unit_of(sym)
    row = l.get(key)
    if row and row["status"] == "claimed" and row["claimed_by"] not in (agent, None):
        return {"ok": False, "error": f"claimed by {row['claimed_by']}, not {agent}"}
    work = p.work_path(key)
    src = _work_source(p, key, unit_src or "")
    if not unit_src and src is None:
        return {"ok": False, "error": "nothing to submit: no work copy"}
    findings = lint_paths([src or oracle.unit_source_path(p, unit_src)])
    if findings:
        return {"ok": False, "error": "lint", "findings": findings}
    if unit_src and (mw_version or extra_cflags):
        _set_unit_opts(p, unit_src, mw_version, extra_cflags)
        _reconfigure_and_split(p)
    res = oracle.check(p, symbol, max_diff_lines, source=src, mw_version=mw_version, extra_cflags=extra_cflags)
    if res.ok and not _is_shadow(agent):
        # a symbol our object references that retail kept local to its TU must become global:
        # our unit is a different object now. dtk exports such a local under a suffixed name
        # (`__init_cpp_800118A8`), so a carved unit only diffs clean after the next split.
        promoted = _promote_referenced_locals(p, key, unit_src, res.unit)
        if promoted and unit_src:
            _reconfigure_and_split(p)
            res = oracle.check(p, symbol, max_diff_lines, source=src)
    reason = oracle.unit_fully_matches(res)
    if not reason and not unit_src and not _is_shadow(agent):
        # accepted: now it gets a unit (split range + entry); the batch verify does the one split+relink
        try:
            cr = carve(p, symbol)
            unit_src = cr.source
            l.db.execute("UPDATE functions SET unit=? WHERE symbol=?", (unit_src, key))
            # a version the oracle chose among the module's candidates is the unit's version
            if not mw_version and res.mw_version and res.mw_version != oracle.module_flags(p, sym.module)[1]:
                mw_version = res.mw_version
            if not extra_cflags and getattr(res, "extra_cflags", None):
                extra_cflags = res.extra_cflags
            if mw_version or extra_cflags:
                _set_unit_opts(p, unit_src, mw_version, extra_cflags)
        except Exception as e:
            return {"ok": False, "error": f"carve failed: {e}"}
    if _is_revise(agent):
        # a rewrite is only worth keeping if it also compiles under the file's prologue:
        # that is what the revise pass exists to achieve
        if not reason and src is not None and unit_src:
            conflict = _prologue_conflict(p, key, unit_src)
            if conflict:
                oracle.compile_unit(p, res.unit, unit_src, src)
                reason = "PROLOGUE CONFLICT (fix the declaration, then submit again):\n" + conflict
        if reason:
            _discard_work(p, key)
            l.finish(key, "released", "unmatched", notes=f"revise rejected: {reason}", model=model,
                     harness=harness, tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=True)
            return {"ok": False, "error": reason, "percent": res.percent, "revise": True}
        if work.exists():
            _install(p, unit_src, work.read_text(), pool=res.matched_pool)
        _discard_work(p, key)
        link = "pool" if res.matched_pool else "pending"
        l.db.execute("UPDATE functions SET link_state=? WHERE symbol=?", (link, key))
        l.finish(key, "matched", "matched", notes=f"revised: {message}", model=model, harness=harness,
                 tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=True)
        return {"ok": True, "symbol": symbol, "unit": unit_src, "revise": True, "link": link}
    if _is_shadow(agent):
        _discard_work(p, key)
        if reason:
            l.finish(key, "released", "unmatched", notes=f"shadow submit rejected: {reason}", model=model,
                     harness=harness, tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=True)
            return {"ok": False, "error": reason, "percent": res.percent, "shadow": True}
        l.finish(key, "matched", "matched", notes=message or "", model=model, harness=harness,
                 tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=True)
        return {"ok": True, "symbol": symbol, "commit": None, "unit": unit_src, "shadow": True,
                "note": "shadow trial: match recorded, nothing installed, relinked or committed"}
    if reason:
        return {"ok": False, "error": reason, "percent": res.percent, "diff": res.diff}

    # Accept on the per-object oracle; the batch relink (`fzgx verify`) checks every hash
    # once for all accepted units and bisects the rare object that matches but does not link.
    # A pool match is accepted but keeps linking the retail object: its private literal can
    # only become the TU's shared one when the whole TU is compiled as one unit.
    if work.exists():
        _install(p, unit_src, work.read_text(), pool=res.matched_pool)
    _discard_work(p, key)
    with oracle.build_lock("units.lock"):
        units = p.load_units()
        for u in units:
            if u["source"] == unit_src:
                if res.matched_pool:
                    u["pool"] = True          # accepted, retail object linked (see CLAUDE.md)
                else:
                    u["status"] = "matching"
                    if res.pool_map:
                        u["pool"] = dict(res.pool_map)  # ninja retargets the literals after compiling
                    else:
                        u.pop("pool", None)
        p.save_units(units)
    if res.pool_map:
        _reconfigure_and_split(p)  # build.ninja gains the mwcc_pool statement for this unit
    commit = None
    l.db.execute("UPDATE functions SET link_state=? WHERE symbol=?", ("pool" if res.matched_pool else "pending", key))
    if names:
        l.propose_names(key, agent, names)
    if row and row["status"] != "claimed":
        # submitted without a live claim (e.g. after a ledger reset): open an attempt so accounting is complete
        l.db.execute("INSERT INTO attempts(symbol, agent, started) VALUES(?,?,?)", (key, agent, int(time.time())))
    l.finish(key, "matched-pool" if res.matched_pool else "matched", "matched", commit=commit,
             notes=(message or "") + (f" [pool: {', '.join(res.pool)}]" if res.matched_pool else ""),
             model=model, harness=harness, tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd)
    return {"ok": True, "symbol": symbol, "commit": commit, "unit": unit_src,
            "link": "pool" if res.matched_pool else "pending", "pool": res.pool, "pool_map": res.pool_map}


def verify_links(p: Project, message: Optional[str] = None) -> Dict[str, Any]:
    """Relink once for every accepted-but-unverified unit; commit; bisect on failure."""
    return verify.verify(p, message)


def _set_unit_opts(p: Project, unit_src: str, mw_version: Optional[str], extra_cflags: Optional[str]) -> None:
    units = p.load_units()
    for u in units:
        if u["source"] == unit_src:
            if mw_version:
                u["mw_version"] = mw_version
            if extra_cflags:
                u["extra_cflags"] = extra_cflags.split()
    p.save_units(units)


def release(p: Project, symbol: str, reason: str, harness: Optional[str] = None,
            model: Optional[str] = None, tokens_in: int = 0, tokens_out: int = 0,
            cost_usd: float = 0.0, agent: Optional[str] = None) -> Dict[str, Any]:
    """Give the function up: keep the best work copy under .fzgx/attempts/, touch nothing in the tree."""
    l = Ledger()
    key = _key(p, symbol)
    row = l.get(key)
    if row is None or row["status"] != "claimed":
        return {"ok": False, "error": "not claimed"}
    if agent and row["claimed_by"] != agent:
        return {"ok": False, "error": f"claimed by {row['claimed_by']}, not {agent}"}
    shadow = _is_shadow(row["claimed_by"])
    body_path = None
    work = p.work_path(key)
    best = STATE_DIR / "attempts" / f"{key}.best.c"
    src = best if best.exists() else (work if work.exists() else None)
    if src is not None and src.read_text().strip() != STUB.format(symbol=p.resolve(symbol).name, note="write the complete unit with write_unit").strip():
        # last resort, a few seconds: the deterministic repairs on the best body (type flips for
        # compare/sign-extension diffs); a match is submitted in the agent's name instead of released
        from . import fixup
        fx = fixup.try_fix(p, symbol, src.read_text(), budget_s=6.0)
        if fx.get("matched") and fx.get("body"):
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(fx["body"])
            best.unlink(missing_ok=True)
            r = submit(p, symbol, agent=agent or row["claimed_by"], message=f"fixup: {fx.get('label')}; agent released: {reason}",
                       harness=harness, model=model)
            if r.get("ok"):
                r["fixup"] = fx.get("label")
                r["fixup_secs"] = fx["secs"]
                return r
        dest = STATE_DIR / "attempts" / f"{key}.{'shadow.' if shadow else ''}{int(time.time())}.c"
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(src, dest)  # the best-scoring body, not necessarily the last one written
        body_path = str(dest)
    best.unlink(missing_ok=True)
    _discard_work(p, key)
    l.finish(key, "released", "unmatched", notes=reason, body_path=body_path, model=model,
             harness=harness, tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=shadow)
    out = {"ok": True, "symbol": symbol, "saved": body_path}
    if shadow:
        out["shadow"] = True
    else:
        out["attempts"] = row["attempts"] + 1
    return out


def abort_attempt(p: Project, symbol: str, reason: str) -> Dict[str, Any]:
    """The agent died (rate limit, timeout) before doing anything: the claim is released and
    the attempt is not counted, so the next batch picks the function up again."""
    l = Ledger()
    key = _key(p, symbol)
    row = l.get(key)
    if row is None or row["status"] != "claimed":
        return {"ok": False, "error": "not claimed"}
    _discard_work(p, key)
    with l.db:
        l.db.execute("UPDATE attempts SET ended=?, outcome='crash', notes=? WHERE symbol=? AND ended IS NULL",
                     (int(time.time()), reason[:200], key))
        l.db.execute("UPDATE functions SET status='unmatched', claimed_by=NULL, claimed_at=NULL, "
                     "attempts=MAX(attempts-1, 0) WHERE symbol=?", (key,))
    return {"ok": True, "symbol": symbol}


# ---------------------------------------------------------------- bookkeeping
def block(p: Project, symbol: str, reason: str, open_issue: bool = False) -> Dict[str, Any]:
    l = Ledger()
    issue = None
    symbol = _key(p, symbol)
    if open_issue:
        row = l.get(symbol)
        body = f"Function `{symbol}` exhausted {row['attempts'] if row else '?'} cheap-tier attempts.\n\n"
        body += f"Best: {row['best_percent']:.1f}%\n\nReason: {reason}\n" if row else reason
        cp = subprocess.run(["gh", "issue", "create", "--title", f"blocked: {symbol}", "--body", body,
                             "--label", "blocked"], cwd=ROOT, text=True, capture_output=True)
        tail = cp.stdout.strip().rsplit("/", 1)[-1]
        if cp.returncode == 0 and tail.isdigit():
            issue = int(tail)
    l.block(symbol, reason, issue)
    return {"ok": True, "symbol": symbol, "issue": issue}


def unblock(p: Project, symbol: str) -> Dict[str, Any]:
    Ledger().unblock(_key(p, symbol))
    return {"ok": True}


def report(p: Project) -> Dict[str, Any]:
    l = Ledger()
    objdiff = None
    rp = p.build_dir / "report.json"
    if rp.exists():
        m = json.loads(rp.read_text()).get("measures", {})
        objdiff = {k: m.get(k) for k in ("matched_code_percent", "matched_functions", "total_functions",
                                          "complete_units", "total_units")}
    pending = l.db.execute("SELECT COUNT(*) FROM functions WHERE link_state='pending'").fetchone()[0]
    pool = l.db.execute("SELECT COUNT(*) FROM functions WHERE link_state='pool'").fetchone()[0]
    return {"ledger": l.summary(), "costs": dict(l.costs()), "objdiff": objdiff, "pending_link": pending,
            "pool_matched": pool}


def snapshot(p: Project) -> Dict[str, Any]:
    return {"ok": True, "path": p.rel(Ledger().snapshot())}


def restore(p: Project) -> Dict[str, Any]:
    return {"ok": True, "rows": Ledger().restore()}


def lint(p: Project, paths: Optional[List[str]] = None) -> List[Any]:
    ps = [Path(x) if Path(x).is_absolute() else ROOT / x for x in (paths or ["src"])]
    return [list(f) for f in lint_paths(ps)]


def names(p: Project) -> List[Dict[str, Any]]:
    return [dict(r) for r in Ledger().pending_names()]


def _env_digest(p: Project) -> str:
    """Everything besides the body that can change a check's verdict: headers, tooling."""
    import hashlib
    h = hashlib.sha256()
    for f in sorted((ROOT / "include").rglob("*.h")):
        h.update(f.read_bytes())
    for f in ("oracle.py", "poolfix.py", "fixup.py", "stuck.py", "regalloc.py", "project.py"):
        h.update((ROOT / "tools" / "fzgx" / f).read_bytes())
    cfg = p.build_dir / "config.json"  # the split: which retail object holds each function
    if cfg.exists():
        st = cfg.stat()
        h.update(f"{st.st_mtime_ns}:{st.st_size}".encode())
    return h.hexdigest()[:16]


def lint_repair(text: str, findings) -> str:
    """Add the lint's allow comment to the lines of A1/A2 (unnamed OS/hardware memory) and S2
    (volatile) findings; other rules are left to fail. Findings: (file, rule, line, msg)."""
    lines = text.split("\n")
    per_line: Dict[int, set] = {}
    for f in findings:
        rule, ln = (f[1], f[2]) if isinstance(f, (tuple, list)) else (f.get("rule"), f.get("line"))
        if rule in ("A1", "A2", "S2") and isinstance(ln, int) and 1 <= ln <= len(lines):
            per_line.setdefault(ln, set()).add(rule)
    for ln, rules in per_line.items():
        cur = lines[ln - 1]
        m = re.search(r"/\* fzgx-allow:\s*([\w,]+)([^*]*)\*/\s*$", cur)
        have = set(m.group(1).split(",")) if m else set()
        allow = ",".join(sorted(have | rules))
        why = "unnamed OS/hardware memory" if rules - {"S2"} else "memory-mapped register"
        lines[ln - 1] = (cur[:m.start()].rstrip() if m else cur.rstrip()) + f"  /* fzgx-allow: {allow} {why} */"
    return "\n".join(lines)


def sweep_attempts(p: Project, module: Optional[str] = None, min_percent: float = 90.0,
                   limit: int = 200, workers: int = 12) -> Dict[str, Any]:
    """Re-check the best saved attempt of every plateaued function against today's oracle
    and headers; submit the ones that now match (outright, as a pool match, or after the
    deterministic fixup). Checks run `workers` wide and are memoised by body and environment
    (.fzgx/sweep_cache.json): a body already checked under the same headers is skipped."""
    import hashlib
    from concurrent.futures import ThreadPoolExecutor
    from . import fixup
    from .permute import _attempt_text  # scoped: permute imports api; avoid the cycle at import time
    l = Ledger()
    q = ("SELECT symbol FROM functions WHERE status='unmatched' AND best_percent>=? "
         + ("AND module=? " if module else "") + "ORDER BY best_percent DESC LIMIT ?")
    rows = l.db.execute(q, [min_percent] + ([module] if module else []) + [limit]).fetchall()
    env = _env_digest(p)
    cache_path = STATE_DIR / "sweep_cache.json"
    try:
        cache: Dict[str, Any] = json.loads(cache_path.read_text()) if cache_path.exists() else {}
    except ValueError:
        cache = {}
    todo = []
    out: Dict[str, Any] = {"candidates": len(rows), "checked": 0, "cached": 0, "submitted": [], "pool": [], "fixed": [], "still": []}
    for (key,) in rows:
        sym = p.resolve(key)
        if sym is None:
            continue
        text = _attempt_text(p, key)
        if not text or sym.name not in text:
            continue
        last = l.db.execute("SELECT outcome FROM attempts WHERE symbol=? ORDER BY id DESC LIMIT 1", (key,)).fetchone()
        if last and last["outcome"] == "link-mismatch":
            continue  # matched the object and failed the link before: a resubmit fails the same way
        ck = f"{env}:{hashlib.sha256(text.encode()).hexdigest()[:24]}"
        if ck in cache and not cache[ck].get("match"):
            out["cached"] += 1
            out["still"].append((key, cache[ck].get("percent")))
            continue
        todo.append((key, text, ck))
    scratch = STATE_DIR / "sweep"
    scratch.mkdir(parents=True, exist_ok=True)

    # one batched compile for every body, then the repairs in threads
    srcs = {}
    for key, text, ck in todo:
        src = scratch / (key.replace(":", "__") + ".c")
        src.write_text(text)
        srcs[key] = src
    first = oracle.check_many(p, [(key, srcs[key]) for key, _, _ in todo], 20)

    def one(item):
        key, text, ck = item
        res = first.get(key) or oracle.check(p, key, 20, source=srcs[key])
        if res.ok and oracle.unit_fully_matches(res) is None:
            return key, ck, {"match": True, "body": text, "percent": 100.0}
        if res.ok:
            fx = fixup.try_fix(p, key, text, budget_s=8.0, base=res)
            if fx.get("matched") and fx.get("body"):
                return key, ck, {"match": True, "body": fx["body"], "label": fx.get("label"), "percent": 100.0}
            return key, ck, {"match": False, "percent": round(max(res.percent, fx.get("best") or 0.0), 1)}
        return key, ck, {"match": False, "percent": None, "error": res.error[:80]}

    with ThreadPoolExecutor(max_workers=workers) as ex:
        results = list(ex.map(one, todo))
    out["checked"] = len(results)
    for key, ck, r in results:
        if r["match"]:
            work = p.work_path(key)
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(r["body"])
            sub = submit(p, key, agent="sweep", message=("saved attempt repaired: " + r["label"]) if r.get("label") else "saved attempt re-checked")
            if not sub.get("ok") and sub.get("error") == "lint":
                # a matching body the lint refuses for an unnamed OS/hardware address or an
                # unjustified volatile: the same allow comment the lifter writes, per finding line
                repaired = lint_repair(r["body"], sub.get("findings") or [])
                if repaired != r["body"]:
                    work.write_text(repaired)
                    sub = submit(p, key, agent="sweep", message="saved attempt re-checked (lint allow comments added)")
            if sub.get("ok"):
                (out["fixed"] if r.get("label") else out["pool"] if sub.get("pool") else out["submitted"]).append(key if not r.get("label") else (key, r["label"]))
                continue
            work.unlink(missing_ok=True)
            out["still"].append((key, sub.get("error", "submit failed")[:80]))
            continue
        cache[ck] = {"match": False, "percent": r["percent"]}
        out["still"].append((key, r["percent"] if r["percent"] is not None else r.get("error")))
    cache_path.write_text(json.dumps(cache))
    return out
