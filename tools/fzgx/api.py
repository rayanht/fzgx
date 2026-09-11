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
import hashlib
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

DEFAULT_TTL = int(os.environ.get('FZGX_CLAIM_TTL', 1800))
MAX_ATTEMPTS = int(os.environ.get("FZGX_MAX_ATTEMPTS", 3))  # a stronger-tier round raises it for its agents
MAX_CHECKS = int(os.environ.get("FZGX_MAX_CHECKS", 16))   # per attempt
MAX_STALE = int(os.environ.get("FZGX_MAX_STALE", 5))     # consecutive checks without improving the attempt's best %
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
        # A pool-backed submit can split an auto object containing the next
        # candidate. Its old path may still exist but no longer define that symbol.
        p.__dict__.pop("_obj_index", None)
        p.__dict__.pop("_obj_suffixed", None)


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
    obj = probe.with_suffix(".o")
    try:
        cp = oracle.compile_unit(p, unit, unit_src, probe, output=obj)
    finally:
        probe.unlink(missing_ok=True)
        obj.unlink(missing_ok=True)
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
    rows = l.list(module=module, status=status)
    current = {p.key(s) for mod in ([module] if module else p.modules) for s in p.functions(mod)}
    rows = [r for r in rows if r['symbol'] in current]
    if max_size:
        rows = [r for r in rows if r["size"] <= max_size]
    if limit is not None:
        rows = rows[:limit]
    return [{"symbol": r["symbol"], "module": r["module"], "size": r["size"], "status": r["status"],
             "attempts": r["attempts"], "best": r["best_percent"], "unit": r["unit"],
             "claimed_by": r["claimed_by"]} for r in rows]


# ---------------------------------------------------------------------- claim
def _seed_record(key: str) -> dict:
    manifest = os.environ.get('FZGX_SEEDS')
    return json.loads(Path(manifest).read_text()).get(key, {}) if manifest else {}


def _compiler_options(p: Project, key: str) -> dict:
    options = _seed_record(key)
    path = p.work_path(key).with_suffix('.compiler.json')
    attempt = Ledger().current_attempt(key)
    if path.exists() and attempt:
        saved = json.loads(path.read_text())
        if saved.get('attempt_id') == attempt['id']:
            options = {**options, **saved}
    return options


def claim(p: Project, symbol: str, agent: str, ttl: int = DEFAULT_TTL,
          max_attempts: int = MAX_ATTEMPTS, no_carve: bool = False) -> Dict[str, Any]:
    l = Ledger()
    if os.environ.get("FZGX_AGENT_ID", agent) != agent or os.environ.get("FZGX_SYMBOL", symbol) != symbol:
        return {"ok": False, "error": "use the function and agent identity assigned to this worker"}
    if p.resolve(symbol) is None:
        return {"ok": False, "error": f"unknown or ambiguous symbol {symbol!r} (use module:name for _prolog/_epilog)"}
    key = _key(p, symbol)
    worker = re.sub(r"(-(codex|claude)-\d+)-.*$", r"\1", agent)
    prefix = worker + "-"
    prior = l.db.execute(
        "SELECT outcome,checks,best_in_attempt FROM attempts WHERE symbol=? AND ended IS NOT NULL "
        "AND (agent=? OR substr(agent,1,?)=?) ORDER BY id DESC LIMIT 1",
        (key, worker, len(prefix), prefix)).fetchone() if (
            os.environ.get("FZGX_AGENT_ID") or re.search(r"-(codex|claude)-\d+$", worker)) else None
    if prior:
        return {"ok": False, "error": "this worker already finished; it cannot reclaim the function",
                "outcome": prior["outcome"], "checks": prior["checks"], "percent": prior["best_in_attempt"]}
    seed = _seed_record(key)
    seed_body = None
    if os.environ.get('FZGX_SEEDS') and not seed:
        return {'ok': False, 'error': 'seeded batch has no candidate for this function'}
    if seed:
        seed_body = Path(seed['path']).read_text()
        if hashlib.sha256(seed_body.encode()).hexdigest() != seed['sha256']:
            return {'ok': False, 'error': 'seed source changed since batch preparation'}
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
    _discard_work(p, key)
    work = p.work_path(key)
    work.parent.mkdir(parents=True, exist_ok=True)
    name = p.resolve(symbol).name
    if seed_body is not None:
        work.write_text(seed_body)
        best = STATE_DIR / "attempts" / f"{key}.best.c"
        best.parent.mkdir(parents=True, exist_ok=True)
        best.write_text(seed_body)
        best.with_suffix('.json').write_text(json.dumps(dict(
            sha256=seed['sha256'], mw=seed.get('mw'), flags=seed.get('flags'))) + '\n')
    elif _is_revise(agent) and unit:
        work.write_text(_canonical_text(p, unit) or STUB.format(symbol=name, note="nothing to revise"))
    else:
        work.write_text(STUB.format(symbol=name, note="write the complete unit with write_unit"))
    tu_src = tufile.tu_source_for(p, p.resolve(symbol))
    out = {"ok": True, "symbol": symbol, "unit": unit,
           "path": _unit_label(p, unit) if unit else (f"src/{tu_src}#{name} (block created at submit)" if tu_src else f"src/{p.module_src_prefix(p.resolve(symbol).module)}/{name}.c (created at submit)"),
           "attempt": row["attempts"] + 1}
    if seed:
        out['seed'] = {**seed, 'source': seed_body,
                       'instruction': ('Your work copy contains a never-give-up lifter draft. Complete unresolved ??? markers '
                                       'and repair inferred declarations or lowering using the retail assembly, retaining the '
                                       'recovered structure. Compile your completed candidate with write_unit; do not restart from a stub.'
                                       if seed.get('kind') == 'lift_total' else
                                       'Your work copy already contains this C. Start with check, then patch it; do not restart from a stub.')}
    try:
        out["context"] = build_context(p, l, symbol, compiler_options=_compiler_options(p, key))
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
    return build_context(p, Ledger(), symbol, budget_tokens,
                         compiler_options=_compiler_options(p, _key(p, symbol)))


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
        return _finish_check(p, symbol, {"ok": False, "error": stop, "stop": stop})
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
    row = Ledger().get(key)
    if row is None or row['status'] != 'claimed' or row['claimed_by'] != agent:
        return dict(ok=False, error=f'{symbol} is not claimed by {agent}')
    unit = _unit_source(p, symbol)
    src = _work_source(p, key, unit)
    if src is None:
        return {"ok": False, "error": "no work copy to patch: write_unit first"}
    text = Path(src).read_text()
    n = text.count(old)
    if n != 1:
        return {"ok": False, "error": f"`old` occurs {n} times; retry using one unique span of the current source below",
                'source': text}
    return write_unit(p, symbol, agent, text.replace(old, new, 1))


def _budget_stop(att) -> Optional[str]:
    if att is None:
        return None
    if (att["checks"] or 0) >= MAX_CHECKS:
        return f"budget exhausted: {MAX_CHECKS} checks used"
    if (att["stale_checks"] or 0) >= MAX_STALE:
        return f"plateau: {MAX_STALE} consecutive checks without improvement (best {att['best_in_attempt']:.1f}%)"
    return None


def _finish_check(p: Project, symbol: str, result: dict, checked: Optional[oracle.CheckResult] = None) -> dict:
    """A bound headless worker needs no model decision to accept a match or stop."""
    agent = os.environ.get('FZGX_AGENT_ID')
    if not agent:
        return result
    row = Ledger().get(_key(p, symbol))
    if not row or row['status'] != 'claimed' or row['claimed_by'] != agent:
        return result
    automatic = None
    if checked and checked.ok and oracle.unit_fully_matches(checked) is None:
        automatic = submit(p, symbol, agent=agent, message='oracle match accepted automatically',
                           harness=os.environ.get('FZGX_HARNESS'), model=os.environ.get('FZGX_MODEL'),
                           mw_version=checked.mw_version, extra_cflags=checked.extra_cflags)
    if not (automatic and automatic.get('ok')) and result.get('stop'):
        automatic = release(p, symbol, reason=result['stop'], agent=agent,
                            harness=os.environ.get('FZGX_HARNESS'), model=os.environ.get('FZGX_MODEL'))
    if automatic:
        result['automatic'] = automatic
        result['terminal'] = Ledger().current_attempt(_key(p, symbol)) is None
        if result['terminal']:
            result.pop('stop', None)
    return result


# --------------------------------------------------------------------- oracle
def check(p: Project, symbol: str, max_diff_lines: int = 80, versions: Optional[str] = None) -> Dict[str, Any]:
    """Compile and diff the work copy if one exists, else the canonical unit."""
    key = _key(p, symbol)
    from . import checkview
    # Already-running app-server threads retain their original tool schema.
    # Their existing check argument can address the new read-only surface too.
    if versions and re.fullmatch(r'(diff|data):\d+', versions):
        section, cursor = versions.split(':')
        return read_evidence(p, symbol, section, int(cursor))
    l = Ledger()
    row = l.get(key)
    if row and row["status"] == "claimed":
        stop = _budget_stop(l.current_attempt(key))
        if stop:
            return _finish_check(p, symbol, {"ok": False, "error": stop, "stop": stop})
    unit = _unit_source(p, symbol)
    src = _work_source(p, key, unit)
    options = _compiler_options(p, key)
    if versions:
        if src is None and unit:
            src = oracle.unit_source_path(p, unit)
        vers = list(oracle.CANDIDATE_VERSIONS) if versions == "all" else versions.split(",")
        if versions == 'all' and options.get('mw') in vers:
            vers.remove(options['mw'])
            vers.insert(0, options['mw'])
        out, best = {}, None
        for ver in vers:
            if row and row["status"] == "claimed" and _budget_stop(l.current_attempt(key)):
                break
            if not (ROOT / 'build' / 'compilers' / ver / 'mwcceppc.exe').exists():
                out[ver] = -1.0
                continue
            result = oracle.check(p, symbol, max_diff_lines, source=src,
                                  mw_version=ver, extra_cflags=options.get('flags'))
            _record_check(p, key, src, result)
            score = (result.percent_adjusted if result.pool_rows else result.percent) if result.ok else -2.0
            out[ver] = score
            fully_matches = result.ok and oracle.unit_fully_matches(result) is None
            if result.ok and (best is None or score > best[0] or fully_matches):
                best = score, result
            if fully_matches:
                break
        selected = None
        if best:
            selected = dict(mw=best[1].mw_version, flags=best[1].extra_cflags)
            attempt = l.current_attempt(key)
            if attempt:
                p.work_path(key).with_suffix('.compiler.json').write_text(
                    json.dumps(dict(attempt_id=attempt['id'], **selected)) + '\n')
            checkview.save(p, key, best[1])
        else:
            p.work_path(key).with_suffix('.diff.json').unlink(missing_ok=True)
        response = {"ok": True, "symbol": symbol, "versions": out,
                "selected": selected, "selected_check": best[1].to_json() if best else None,
                "stop": _budget_stop(l.current_attempt(key)),
                "note": "The best tested compiler is retained for subsequent edits and submit. "
                        "-1 compiler missing, -2 check failed; each compiler probe counts toward the attempt"}
        return _finish_check(p, symbol, response, best[1] if best else None)
    res = oracle.check(p, symbol, max_diff_lines, source=src,
                       mw_version=options.get('mw'), extra_cflags=options.get('flags'))
    checkview.save(p, key, res)
    out = res.to_json()
    stats = _record_check(p, key, src, res)
    if src is not None:
        conflict = _prologue_conflict(p, key, unit) if res.ok and unit else None
        if conflict:
            out["prologue_conflict"] = conflict
        out['budget'] = stats
        stop = _budget_stop(l.current_attempt(key))
        if stop:
            out['stop'] = stop
    return _finish_check(p, symbol, out, res)


def read_evidence(p: Project, symbol: str, section: str = 'diff', cursor: int = 0) -> dict:
    from . import checkview
    if p.resolve(symbol) is None:
        return dict(ok=False, error='unknown or ambiguous symbol (use module:name)')
    return checkview.read(p, _key(p, symbol), section, cursor)


def _record_check(p: Project, key: str, src: Optional[Path], res: oracle.CheckResult) -> dict:
    """Archive the body and compiler settings together, including version probes."""
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
                                    "rows": res.pool_rows if res.ok else None,
                                    "mw": res.mw_version, "flags": res.extra_cflags}) + "\n")
        except OSError:
            pass
    if src is not None:
        stats = Ledger().bump_checks(key, (res.percent_adjusted if res.pool_rows else res.percent) if res.ok else 0.0)
        if stats.get("improved"):
            best = STATE_DIR / "attempts" / f"{key}.best.c"
            best.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(src, best)
            best.with_suffix('.json').write_text(json.dumps(dict(
                sha256=hashlib.sha256(best.read_bytes()).hexdigest(),
                mw=res.mw_version, flags=res.extra_cflags, percent=stats['best_in_attempt'])) + '\n')
        return stats
    return {}


def format_check(res: Dict[str, Any]) -> str:
    if res.get('terminal'):
        return 'Attempt completed automatically: ' + json.dumps(res['automatic'])
    if "versions" in res:
        text = "\n".join(f"{v:10s} {'n/a' if pct < 0 else f'{pct:.1f}%'}" for v, pct in res["versions"].items())
        if res.get('selected_check'):
            text += '\nSelected for subsequent edits and submit:\n' + format_check(res['selected_check'])
        return text + (f"\nSTOP: {res['stop']}." if res.get("stop") else "")
    if not res["ok"]:
        return f"CHECK FAILED: {res['error']}" + (f"\nSTOP: {res['stop']}." if res.get("stop") else "")
    verdict = "MATCH" if res["matched"] else ("MATCH (pool)" if res.get("matched_pool") else "no match")
    lines = [f"{res['symbol']}: {res['percent']:.1f}%  unit={res['unit']}  {verdict}"]
    if res.get('automatic'):
        lines.append('Automatic submission rejected: ' + json.dumps(res['automatic']))
    if res.get('mw_version'):
        lines.append(f"compiler: {res['mw_version']}" + (f" extra: {res['extra_cflags']}" if res.get('extra_cflags') else ''))
    if res.get('instruction_rows') and not res['matched']:
        lines.append(f"{res['differing_rows']} of {res['instruction_rows']} aligned instruction rows still differ "
                     "after accepted relocation equivalences; the displayed % is objdiff's similarity score.")
    if res["matched"] and res.get("pool_map"):
        lines.append("literal pool: private constants retargeted to the shared retail symbols (" + ", ".join(res["pool"]) + ")")
    if not res["matched"] and res.get("pool_rows"):
        lines.append(f"{res['pool_rows']} row(s) marked `p` are literal-pool relocations ({', '.join(res['pool'])}); the tooling "
                     f"retargets them at submit, so they already count as matching: {res['percent_adjusted']:.1f}% "
                     "is the adjusted instruction-row score. Fix only the other marked rows.")
    if res.get("matched_pool"):
        lines.append("pool: the only differences are relocations to shared literal-pool constants whose value "
                     "you reproduce (" + ", ".join(res["pool"]) + "); this counts as a match.")
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
        lines.append(f"check {b['checks']}: best this attempt {b['best_in_attempt']:.1f}%")
    if res.get("stop"):
        lines.append(f"STOP: {res['stop']}. Do not write again.")
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
    p.work_path(key).with_suffix('.compiler.json').unlink(missing_ok=True)
    p.work_path(key).with_suffix('.diff.json').unlink(missing_ok=True)
    best = STATE_DIR / 'attempts' / f'{key}.best.c'
    best.unlink(missing_ok=True)
    best.with_suffix('.json').unlink(missing_ok=True)


# Different functions can share splits, symbol tables and TU files. Their work
# copies compile independently, but installing accepted C must be serial.
@oracle.build_lock("submit.lock")
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
    seed = _compiler_options(p, key)
    mw_version = mw_version or seed.get('mw')
    extra_cflags = extra_cflags if extra_cflags is not None else seed.get('flags')
    row = l.get(key)
    if _is_shadow(agent) and (row is None or row["status"] != "claimed"):
        return {"ok": False, "error": "this trial has no active claim; its result is already final"}
    if row and row["status"] == "claimed" and row["claimed_by"] not in (agent, None):
        return {"ok": False, "error": f"claimed by {row['claimed_by']}, not {agent}"}
    work = p.work_path(key)
    src = _work_source(p, key, unit_src or "")
    if not unit_src and src is None:
        return {"ok": False, "error": "nothing to submit: no work copy"}
    findings = lint_paths([src or oracle.unit_source_path(p, unit_src)])
    if findings:
        return {"ok": False, "error": "lint", "findings": findings}
    if unit_src and (mw_version or extra_cflags) and not _is_shadow(agent):
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
            res = oracle.check(p, symbol, max_diff_lines, source=src,
                               mw_version=mw_version, extra_cflags=extra_cflags)
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
        if reason:
            return {"ok": False, "error": reason, "percent": res.percent, "shadow": True}
        dest = STATE_DIR / "attempts" / f"{key}.shadow.{time.time_ns()}.c"
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(src or oracle.unit_source_path(p, unit_src), dest)
        dest.with_suffix(".json").write_text(json.dumps({"sha256": hashlib.sha256(dest.read_bytes()).hexdigest(),
                                                       "percent": res.percent, "mw": res.mw_version,
                                                       "flags": res.extra_cflags}) + "\n")
        _discard_work(p, key)
        l.finish(key, "matched", "matched", notes=message or "", body_path=str(dest), model=model, harness=harness,
                 tokens_in=tokens_in, tokens_out=tokens_out, cost_usd=cost_usd, shadow=True)
        return {"ok": True, "symbol": symbol, "commit": None, "unit": unit_src, "shadow": True, "saved": str(dest),
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
            cost_usd: float = 0.0, agent: Optional[str] = None, save_only: bool = False) -> Dict[str, Any]:
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
        seed = _compiler_options(p, key)
        metadata = best.with_suffix('.json')
        if src == best and metadata.exists():
            saved = json.loads(metadata.read_text())
            if saved.get('sha256') == hashlib.sha256(src.read_bytes()).hexdigest():
                seed = saved
        base = None
        fx = {}
        if not save_only:
            base = oracle.check(p, symbol, 0, source=src,
                                mw_version=seed.get('mw'), extra_cflags=seed.get('flags'))
            fx = fixup.try_fix(p, symbol, src.read_text(), budget_s=6.0, base=base)
        if fx.get("matched") and fx.get("body"):
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(fx["body"])
            r = submit(p, symbol, agent=agent or row["claimed_by"], message=f"fixup: {fx.get('label')}; agent released: {reason}",
                       harness=harness, model=model, mw_version=base.mw_version, extra_cflags=base.extra_cflags)
            if r.get("ok"):
                best.unlink(missing_ok=True)
                best.with_suffix('.json').unlink(missing_ok=True)
                r["fixup"] = fx.get("label")
                r["fixup_secs"] = fx["secs"]
                return r
        dest = STATE_DIR / "attempts" / f"{key}.{'shadow.' if shadow else ''}{int(time.time())}.c"
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(src, dest)  # the best-scoring body, not necessarily the last one written
        dest.with_suffix('.json').write_text(json.dumps(dict(
            sha256=hashlib.sha256(dest.read_bytes()).hexdigest(), mw=base.mw_version if base else seed.get('mw'),
            flags=base.extra_cflags if base else seed.get('flags'),
            percent=(base.percent_adjusted if base.pool_rows else base.percent) if base else seed.get('percent',
                     dict(l.current_attempt(key) or {}).get('best_in_attempt', 0)))) + '\n')
        body_path = str(dest)
    best.unlink(missing_ok=True)
    best.with_suffix('.json').unlink(missing_ok=True)
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
        l.db.execute("UPDATE functions SET status=COALESCE(prev_status, 'unmatched'), claimed_by=NULL, "
                     "claimed_at=NULL, claim_ttl=NULL, prev_status=NULL WHERE symbol=?", (key,))
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


def _attempt_text(p: Project, key: str) -> Optional[str]:
    """The best saved body: the live work copy of a claimed function, else the ledger's
    best-scoring attempt (a stale work copy or .best.c of an unclaimed function is ignored)."""
    l = Ledger()
    row = l.get(key)
    claimed = bool(row and row["status"] == "claimed")
    work = p.work_path(key)
    if claimed and work.exists():
        return work.read_text()
    best = STATE_DIR / "attempts" / f"{key}.best.c"
    if claimed and best.exists():
        return best.read_text()
    row = l.db.execute(
        "SELECT best_body_path FROM attempts WHERE symbol=? AND best_body_path IS NOT NULL "
        "ORDER BY best_in_attempt DESC, final_percent DESC, id DESC LIMIT 1", (key,)).fetchone()
    if row and row[0]:
        path = Path(row[0])
        if not path.exists():  # the repository moved; the store did not
            path = STATE_DIR / "attempts" / path.name
        if path.exists():
            return path.read_text()
    return None


def _env_digest(p: Project) -> str:
    """Everything besides the body that can change a check's verdict: headers, tooling."""
    import hashlib
    h = hashlib.sha256()
    for f in sorted((ROOT / "include").rglob("*.h")):
        h.update(f.read_bytes())
    for f in ("oracle.py", "poolfix.py", "fixup.py", "stuck.py", "regalloc.py", "project.py", "lint.py", "spell.py", "lab.py"):
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


def sweep(p: Project, module: Optional[str] = None, min_percent: float = 80.0, limit: int = 2000,
          workers: int = 12, drafts: bool = False, max_percent: float = 100.0, budget_s: float = 10.0,
          do_submit: bool = True, max_size: Optional[int] = None, do_spell: bool = True) -> Dict[str, Any]:
    """The search over every saved body, in three stages, one pass:
      1. re-check against today's oracle and headers (a header, oracle or pool change lands
         bodies that were right all along); submit outright and pool matches
      2. the deterministic fixup: edits the diff rows name (type flips, symbol substitutions,
         immediates, layout, branch shape) with a short register-allocation search
      3. the spelling search (spell.run_bodies): a beam over every rewrite family, lockstep
         across the remaining bodies, from the fixup's improved body where it had one
    Bodies: the agents' saved best attempts (default) or the lifter's drafts (`drafts`,
    .fzgx/lift/scores.json from `fzgx trivial`) scoring in [min_percent, max_percent).
    Stages 1-2 are memoised by body + environment (.fzgx/sweep_cache.json), stage 3 by the
    spell memo; a body already searched under the same headers and tooling is skipped."""
    import hashlib
    from concurrent.futures import ThreadPoolExecutor
    from . import fixup, spell
    l = Ledger()
    out: Dict[str, Any] = {"candidates": 0, "checked": 0, "cached": 0, "submitted": [], "pool": [], "fixed": [],
                           "spelled": [], "still": [], "spell": {}}
    bodies: List[tuple] = []  # (key, module, size, percent, text)
    if drafts:
        scores_path = STATE_DIR / "lift" / "scores.json"
        scores = json.loads(scores_path.read_text()) if scores_path.exists() else {}
        for key, rec in scores.items():
            pct = rec.get("percent") or 0.0
            if rec.get("matched") or pct < min_percent or pct >= max_percent:
                continue
            sym = p.resolve(key)
            if sym is None or p.unit_of(sym) or (module and sym.module != module) or (max_size is not None and sym.size > max_size):
                continue
            best = STATE_DIR / "spell" / p.key(sym).replace(":", "__") / "best.c"
            text = best.read_text() if best.exists() else rec.get("text") or ""
            if sym.name in text:
                bodies.append((p.key(sym), sym.module, sym.size, pct, text))
        bodies.sort(key=lambda b: -b[3])
        bodies = bodies[:limit]
    else:
        q = ("SELECT symbol, module, size, best_percent FROM functions WHERE status='unmatched' AND best_percent>=? AND best_percent<? "
             + ("AND module=? " if module else "") + ("AND size<=? " if max_size is not None else "")
             + "ORDER BY best_percent DESC LIMIT ?")
        args = [min_percent, max_percent] + ([module] if module else []) + ([max_size] if max_size is not None else []) + [limit]
        for key, mod, size, pct in l.db.execute(q, args).fetchall():
            sym = p.resolve(key)
            text = _attempt_text(p, key) if sym else None
            if not text or sym.name not in text:
                continue
            last = l.db.execute("SELECT outcome FROM attempts WHERE symbol=? ORDER BY id DESC LIMIT 1", (key,)).fetchone()
            if last and last["outcome"] == "link-mismatch":
                continue  # matched the object and failed the link before: a resubmit fails the same way
            bodies.append((key, mod, size, pct or 0.0, text))
    out["candidates"] = len(bodies)
    env = _env_digest(p)
    cache_path = STATE_DIR / "sweep_cache.json"
    try:
        cache: Dict[str, Any] = json.loads(cache_path.read_text()) if cache_path.exists() else {}
    except ValueError:
        cache = {}
    todo, left = [], []  # left: bodies for the spelling search
    for key, mod, size, pct, text in bodies:
        ck = f"{env}:{hashlib.sha256(text.encode()).hexdigest()[:24]}"
        if ck in cache and not cache[ck].get("match"):
            out["cached"] += 1
            left.append((key, mod, size, pct, cache[ck].get("body") or text))
            continue
        todo.append((key, mod, size, pct, text, ck))
    scratch = STATE_DIR / "sweep"
    scratch.mkdir(parents=True, exist_ok=True)
    srcs = {}
    for key, mod, size, pct, text, ck in todo:
        src = scratch / (key.replace(":", "__") + ".c")
        src.write_text(text)
        srcs[key] = src
    # stage 1: one batched compile for every body; stage 2: the repairs in threads
    first = oracle.check_many(p, [(key, srcs[key]) for key, *_ in todo], 20) if todo else {}

    def one(item):
        key, mod, size, pct, text, ck = item
        res = first.get(key) or oracle.check(p, key, 20, source=srcs[key])
        options = {"mw_version": res.mw_version, "extra_cflags": res.extra_cflags}
        if res.ok and oracle.unit_fully_matches(res) is None:
            return item, {"match": True, "body": text, "percent": 100.0, **options}
        if res.ok:
            fx = fixup.try_fix(p, key, text, budget_s=8.0, base=res)
            if fx.get("matched") and fx.get("body"):
                return item, {"match": True, "body": fx["body"], "label": fx.get("label"), "percent": 100.0, **options}
            return item, {"match": False, "percent": round(max(res.percent, fx.get("best") or 0.0), 1), "body": fx.get("best_body")}
        return item, {"match": False, "percent": None, "error": (res.error or "")[:80]}

    with ThreadPoolExecutor(max_workers=workers) as ex:
        results = list(ex.map(one, todo))
    out["checked"] = len(results)
    for (key, mod, size, pct, text, ck), r in results:
        if r["match"]:
            if not do_submit:
                out["submitted"].append(key); continue
            work = p.work_path(key)
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(r["body"])
            options = {name: r.get(name) for name in ("mw_version", "extra_cflags")}
            sub = submit(p, key, agent="sweep", message=("saved body repaired: " + r["label"]) if r.get("label") else "saved body re-checked",
                         **options)
            if not sub.get("ok") and sub.get("error") == "lint":
                # a matching body the lint refuses for an unnamed OS/hardware address or an
                # unjustified volatile: the same allow comment the lifter writes, per finding line
                repaired = lint_repair(r["body"], sub.get("findings") or [])
                if repaired != r["body"]:
                    work.write_text(repaired)
                    sub = submit(p, key, agent="sweep", message="saved body re-checked (lint allow comments added)", **options)
            if sub.get("ok"):
                (out["fixed"] if r.get("label") else out["pool"] if sub.get("pool") else out["submitted"]).append(key if not r.get("label") else (key, r["label"]))
                continue
            work.unlink(missing_ok=True)
            out["still"].append((key, sub.get("error", "submit failed")[:80]))
            continue
        cache[ck] = {"match": False, "percent": r["percent"], "body": r.get("body")}
        if r["percent"] is None:
            out["still"].append((key, r.get("error")))
        else:
            left.append((key, mod, size, r["percent"], r.get("body") or text))
    cache_path.write_text(json.dumps(cache))
    # stage 3: the spelling search over what is left, lockstep (its own memo skips old bodies)
    if left and do_spell:
        sp = spell.run_bodies(p, left, workers=3, budget_s=budget_s, submit=do_submit, agent="sweep")
        out["spelled"] = [(s_, pct_, path_) for s_, pct_, path_ in sp.get("matched", [])]
        out["spell"] = {k: sp.get(k) for k in ("searched", "skipped", "improved", "candidates", "families", "secs")}
        spelled = {s_ for s_, _, _ in out["spelled"]}
        out["still"] += [(key, pct) for key, _, _, pct, _ in left if key not in spelled]
    elif left:
        out["still"] += [(key, pct) for key, _, _, pct, _ in left]
    return out


def sweep_one(p: Project, symbol: str, body: str, budget_s: float = 10.0) -> Dict[str, Any]:
    """The three stages on one body (no submit): check, fixup, spell. Returns the fixup/spell
    result dict with `body` on a match."""
    from . import fixup, spell
    fx = fixup.try_fix(p, symbol, body, budget_s=min(budget_s, 8.0))
    if fx.get("matched"):
        fx["stage"] = "fixup"; return fx
    sp = spell.search(p, symbol, fx.get("best_body") or body, budget_s=budget_s)
    sp["stage"] = "spell"; sp["fixup_best"] = fx.get("best")
    return sp
