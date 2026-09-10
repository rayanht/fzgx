#!/usr/bin/env python3
"""Headless batch runner: one harness process per function, N in parallel, one summary.

    uv run tools/orchestrate.py --harness claude --parallel 16 --select main_rel:8:96:48
    uv run tools/orchestrate.py --harness codex  --parallel 16 --symbols fn_1_A fn_1_B ...

Each worker spawns `claude -p --agent matcher` (or `codex exec`) with only the
project MCP server, no skills, no other MCPs, and the matcher's tool list. The
RESULT line is parsed from the harness output, real token usage and cost are
written to the ledger, crashed or timed-out workers have their claim released,
and a batch report lands in .fzgx/reports/ (local, not committed). The orchestrating model calls this
once per batch and acts on the summary.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import signal
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from typing import Dict, List, Optional

from fzgx import api, reuse, trivial
from fzgx.ledger import Ledger
from fzgx.project import ROOT, STATE_DIR, Project

RESULT_RE = re.compile(r"RESULT:\s*(matched|released)\s+(\S+)\s+([\d.]+)%(?:\s+checks=(\d+))?")
MATCHER_TOOLS = ["Read", "mcp__fzgx__claim", "mcp__fzgx__write_unit", "mcp__fzgx__patch_unit", "mcp__fzgx__check",
                 "mcp__fzgx__submit", "mcp__fzgx__release"]
# The user's defaults are Fable 5.1 (claude) and GPT-6 Astra (codex); matchers must never run on those.
EXPECTED_MODEL = {"claude": "claude-haiku-4-5", "codex": "gpt-5.6-luna"}
CLAUDE_MODELS = {"haiku": "claude-haiku-4-5", "sonnet": "claude-sonnet-5", "opus": "claude-opus-5"}
# $/M tokens from platform.openai.com/docs/pricing (2026-09-08): input, cached input, cache write, output.
# Codex reports usage but no cost; Claude Code reports total_cost_usd itself.
CODEX_PRICES = {"gpt-5.6-luna": (0.20, 0.02, 0.25, 1.20), "gpt-5.6-terra": (2.00, 0.20, 2.50, 12.00),
                "gpt-5.6-sol": (4.00, 0.40, 5.00, 20.00), "gpt-6-astra": (10.00, 1.00, 12.50, 50.00)}
FAST_MULTIPLIER = 2.0  # "Fast mode" (formerly priority processing) is 2x standard on every line
CODEX_INSTRUCTIONS = ROOT / "tools" / "codex_matcher.md"  # replaces Codex's 17.7k-char default persona prompt
CODEX_REVISE_INSTRUCTIONS = ROOT / "tools" / "codex_revise.md"
CODEX_DISABLE = ["plugins", "recommended_plugins", "plugin_sharing", "remote_plugin", "apps", "browser_use",
                 "browser_use_external", "in_app_browser", "computer_use", "skill_search", "skill_mcp_dependency_install"]


def select(p: Project, spec: str) -> List[str]:
    """module:min:max:count — untouched, uncarved functions spread across sizes."""
    module, lo, hi, n = spec.split(":")
    rows = [r for r in api.inventory(p, module=module, status="unmatched")
            if r["attempts"] == 0 and not r["unit"] and int(lo) <= r["size"] <= int(hi)]
    rows.sort(key=lambda r: (r["size"], r["symbol"]))
    step = max(1, len(rows) // int(n))
    return [r["symbol"] for r in rows[::step][: int(n)]]


def select_tu(p: Project, module: str, tu_files: List[str], max_size: int = 0, revise: bool = False,
              retry: int = 0) -> List[str]:
    """Every unmatched, unattempted function of the given TUs (whole-file matching); with
    retry=N also those with fewer than N attempts; with revise=True every matched one instead."""
    import json as _json
    d = _json.loads((p.module_config_dir(module) / "tus.json").read_text())
    want = {t["file"]: t["functions"] for t in d["tus"] if t["file"] in tu_files}
    inv = {r["symbol"]: r for r in api.inventory(p, module=module, status="matched" if revise else "unmatched")}
    units = {u["symbols"][0] for u in p.load_units() if u["module"] == module}
    out = []
    for f in tu_files:
        for fn in want.get(f, []):
            r = inv.get(fn)
            if not r or (max_size and r["size"] > max_size):
                continue
            if (fn in units) if revise else (r["attempts"] == 0 or 0 < r["attempts"] < retry):
                out.append(fn)
    return out


def claude_cmd(symbol: str, agent_id: str, model: str) -> List[str]:
    prompt = f"SYMBOL={symbol}  AGENT_ID={agent_id}. Match this function following your loop."
    return ["claude", "-p", prompt, "--agent", "matcher", "--model", model,
            "--output-format", "json", "--no-session-persistence",
            "--mcp-config", ".mcp.json", "--strict-mcp-config", "--disable-slash-commands",
            "--allowedTools", ",".join(MATCHER_TOOLS)]


def codex_cmd(symbol: str, agent_id: str, model: str, fast: bool = False, revise: bool = False,
              effort: Optional[str] = None) -> List[str]:
    prompt = (f"SYMBOL={symbol}  AGENT_ID={agent_id}. Rewrite this matched function for readability following your loop."
              if revise else f"SYMBOL={symbol}  AGENT_ID={agent_id}. Match this function following your loop.")
    if os.environ.get('FZGX_SEEDS'):
        prompt += (' This is a seeded SDK repair: claim returns your existing high-scoring C in seed.source '
                   'and installs it as your work copy. Keep that implementation and repair its remaining differences. '
                   'Start with check, then patch_unit.')
    # --ignore-user-config: no user MCP servers/skills (480k -> 125k input tokens on a smoke test)
    cmd = ["codex", "exec", "--json", "--skip-git-repo-check", "--ignore-user-config", "-s", "read-only",
           "-m", model]
    # none of these belong in a matcher's context (each adds tool schemas or injected text every call)
    for feat in CODEX_DISABLE:
        cmd += ["--disable", feat]
    if fast:
        cmd += ["-c", 'service_tier="fast"']
    if effort:
        cmd += ["-c", f'model_reasoning_effort="{effort}"']
    # context trims measured on a smoke run: 13.3k -> ~8k tokens on the first call
    cmd += ["-c", f'model_instructions_file="{CODEX_REVISE_INSTRUCTIONS if revise else CODEX_INSTRUCTIONS}"',
            "-c", "skills.include_instructions=false",                 # no <skills_instructions> block
            "-c", "project_doc_max_bytes=0",                            # no AGENTS.md concatenation (global + repo)
            "-c", 'mcp_servers.fzgx.enabled_tools=["claim","write_unit","patch_unit","check","submit","release"]',
            "-c", "tools.web_search=false",
            "--disable", "shell_tool", "--disable", "unified_exec", "--disable", "view_image"]
    return cmd + [
            "-c", 'mcp_servers.fzgx.command="uv"',
            "-c", 'mcp_servers.fzgx.args=["run","tools/fzgx_mcp.py"]',
            "-c", f'mcp_servers.fzgx.cwd="{ROOT}"',
            # the server inherits nothing from us: the attempt cap of this round travels explicitly
            "-c", 'mcp_servers.fzgx.env={' + ','.join(
                name + '=' + json.dumps(os.environ.get(name, default)) for name, default in (
                    ('FZGX_MAX_ATTEMPTS', '3'), ('FZGX_MAX_CHECKS', '16'), ('FZGX_MAX_STALE', '5'),
                    ('FZGX_CLAIM_TTL', '1800'), ('FZGX_SEEDS', ''))) + '}',
            # codex exec runs with approval_policy=never; without this every mutating MCP call is refused
            "-c", 'mcp_servers.fzgx.default_tools_approval_mode="approve"',
            prompt]


def parse_claude(out: str) -> Dict:
    for line in out.splitlines():
        if line.startswith("{"):
            try:
                d = json.loads(line)
            except json.JSONDecodeError:
                continue
            u = d.get("usage", {})
            return {"text": d.get("result", ""), "cost": d.get("total_cost_usd", 0.0) or 0.0,
                    "turns": d.get("num_turns"), "tokens_in": u.get("input_tokens", 0) + u.get("cache_read_input_tokens", 0)
                    + u.get("cache_creation_input_tokens", 0), "tokens_out": u.get("output_tokens", 0),
                    "model": next(iter(d.get("modelUsage", {}) or {"": None}), "")}
    return {"text": out, "cost": 0.0, "turns": None, "tokens_in": 0, "tokens_out": 0, "model": ""}


def codex_session_model(thread_id: str) -> str:
    """Codex's --json events omit the model; its session rollout records it."""
    if not thread_id:
        return ""
    root = Path.home() / ".codex" / "sessions"
    for f in sorted(root.rglob(f"*{thread_id}*"), key=lambda f: f.stat().st_mtime, reverse=True):
        m = re.search(r'"model":"([^"]+)"', f.read_text(errors="replace"))
        if m:
            return m.group(1)
    return ""


def parse_codex(out: str, fast: bool = False) -> Dict:
    text, tin, tout, model, thread = "", 0, 0, "", ""
    cached = cache_w = 0
    for line in out.splitlines():
        if not line.startswith("{"):
            continue
        try:
            ev = json.loads(line)
        except json.JSONDecodeError:
            continue
        t = ev.get("type", "")
        if t == "thread.started":
            thread = ev.get("thread_id", "")
        if t == "item.completed" and ev.get("item", {}).get("type") == "agent_message":
            text = ev["item"].get("text", text)
        if t == "turn.completed":
            u = ev.get("usage", {})
            # OpenAI usage: input_tokens already includes cached_input_tokens; output includes reasoning
            tin += u.get("input_tokens", 0)
            cached += u.get("cached_input_tokens", 0)
            cache_w += u.get("cache_write_input_tokens", 0)
            tout += u.get("output_tokens", 0)
        model = ev.get("model", model) or model
    model = model or codex_session_model(thread)
    pi, pc, pw, po = CODEX_PRICES.get(model, (0.0, 0.0, 0.0, 0.0))
    cost = ((tin - cached) * pi + cached * pc + cache_w * pw + tout * po) / 1e6 * (FAST_MULTIPLIER if fast else 1.0)
    return {"text": text or out[-2000:], "cost": round(cost, 6), "turns": None, "tokens_in": tin,
            "tokens_out": tout, "model": model}


def run_one(p: Project, harness: str, model: str, symbol: str, idx: int, timeout: int, batch: str,
            shadow: bool = False, fast: bool = False, revise: bool = False) -> Dict:
    prefix = "revise-" if revise else ("shadow-" if shadow else "")
    agent_id = f"{prefix}{batch}-{harness}-{idx}"
    if harness == "claude" and revise:
        raise SystemExit("--revise is implemented for the codex harness only")
    cmd = claude_cmd(symbol, agent_id, model) if harness == "claude" else codex_cmd(symbol, agent_id, model, fast, revise, EFFORT.get("level"))
    t0 = time.time()
    # own process group: on timeout the agent AND its MCP server die (they leaked before)
    proc = subprocess.Popen(cmd, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                            stdin=subprocess.DEVNULL, start_new_session=True,
                            env={**os.environ, "CLAUDE_CODE_DISABLE_TERMINAL_TITLE": "1"})
    try:
        so, se = proc.communicate(timeout=timeout)
        out, rc = (so or "") + "\n" + (se or ""), proc.returncode
    except subprocess.TimeoutExpired:
        try:
            os.killpg(proc.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
        so, se = proc.communicate()
        def _s(x):
            return x.decode(errors="replace") if isinstance(x, bytes) else (x or "")
        out, rc = _s(so) + "\n" + _s(se), -9
    info = parse_claude(out) if harness == "claude" else parse_codex(out, fast)
    m = RESULT_RE.search(info["text"] or "") or RESULT_RE.search(out)
    outcome = m.group(1) if m else ("timeout" if rc == -9 else "crash")
    if not m:  # no RESULT line: the agent never finished its loop; do not charge an attempt
        try:
            api.abort_attempt(p, symbol, f"{outcome}: agent exited without a result (rc={rc})")
        except Exception:
            pass
    if info["model"] and not info["model"].startswith(EXPECTED_MODEL[harness]):
        outcome = f"WRONG-MODEL({info['model']})"
    pct = float(m.group(3)) if m else None
    checks = int(m.group(4)) if m and m.group(4) else None
    key = api._key(p, symbol)
    l = Ledger()
    # cost accounting onto the attempt this agent opened
    l.db.execute("UPDATE attempts SET tokens_in=?, tokens_out=?, cost_usd=?, harness=?, model=COALESCE(NULLIF(?, ''), model) "
                 "WHERE id=(SELECT id FROM attempts WHERE symbol=? AND agent=? ORDER BY id DESC LIMIT 1)",
                 (info["tokens_in"], info["tokens_out"], info["cost"], harness, info["model"], key, agent_id))
    row = l.get(key)
    if row and row["status"] == "claimed" and row["claimed_by"] == agent_id:
        api.release(p, symbol, f"harness {outcome} (rc={rc}); no RESULT line", harness=harness, model=info["model"], agent=agent_id)
        outcome = f"{outcome}+released"
    log = STATE_DIR / "runs" / batch / f"{symbol}.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text(out)
    return {"symbol": symbol, "outcome": outcome, "percent": pct, "checks": checks, "cost": info["cost"], "model": info["model"],
            "tokens_in": info["tokens_in"], "tokens_out": info["tokens_out"], "turns": info["turns"],
            "secs": round(time.time() - t0, 1), "rc": rc}


EFFORT: Dict[str, Optional[str]] = {"level": None}


def fan_out(p: Project, a, model: str, symbols: List[str], batch: str, revise: bool) -> tuple:
    """Run one agent per symbol, `a.parallel` at a time, within `a.budget_usd`."""
    results: List[Dict] = []
    spent = 0.0
    with ThreadPoolExecutor(max_workers=a.parallel) as ex:
        futs = {}
        queue = list(enumerate(symbols, 1))
        while queue or futs:
            while queue and len(futs) < a.parallel and (a.budget_usd is None or spent < a.budget_usd):
                i, s = queue.pop(0)
                futs[ex.submit(run_one, p, a.harness, model, s, i, a.timeout, batch, a.shadow, a.fast, revise)] = s
            if not futs:
                break
            done = next(as_completed(list(futs)))
            futs.pop(done)
            r = done.result()
            results.append(r)
            spent += r["cost"] or 0.0
            if r["outcome"].startswith("WRONG-MODEL"):
                print(f"ABORT: {r['symbol']} ran on {r['outcome']}; expected {EXPECTED_MODEL[a.harness]}", flush=True)
                queue.clear()
            print(f"  {r['outcome']:16s} {r['symbol']:14s} {'' if r['percent'] is None else f'{r['percent']:.1f}%':7s} "
                  f"checks={r['checks'] if r['checks'] is not None else '-'} turns={r['turns'] or '-'} "
                  f"${r['cost']:.3f} {r['secs']}s", flush=True)
    return results, spent


def finish_round(p: Project, a, model: str, module: str) -> Dict:
    """The TU-finish pass, a revise round on its queue, the pass again. No hands."""
    from fzgx import finish  # scoped: only when --finish is used
    # the deterministic pass first: re-check, fixup and spelling search over the module's saved bodies
    sw = api.sweep(p, module, 60.0, 2000)
    print(f"sweep {module}: {len(sw.get('submitted', []))} matched as saved, {len(sw.get('pool', []))} pool, "
          f"{len(sw.get('fixed', []))} fixed, {len(sw.get('spelled', []))} spelled of {sw.get('candidates')} bodies", flush=True)
    from fzgx.ledger import Ledger  # scoped: same
    out = {"passes": [], "revise": None}
    r = finish.finish(p, module)
    out["passes"].append({k: r[k] for k in ("ok", "tus", "hoisted", "renamed", "contested", "collapsed", "queue")})
    print(f"tu-finish {module}: ok={r['ok']} hoisted={r['hoisted']} renamed={r['renamed']} contested={r['contested']} "
          f"collapsed={r['collapsed']} unresolved={len(r['queue'])} ({r.get('secs')}s)", flush=True)
    queue = r["queue"]
    if queue and a.harness == "codex":
        l = Ledger()  # blocks released twice by revise agents are the librarian's, not the loop's
        capped = {row[0] for row in l.db.execute("SELECT symbol FROM attempts WHERE agent LIKE 'revise-%' AND outcome='released' "
                                                  "GROUP BY symbol HAVING COUNT(*) >= 2")}
        todo = [s for s in queue if s not in capped]
        print(f"revise round: {len(todo)} blocks ({len(queue) - len(todo)} at the revise cap)", flush=True)
        if todo:
            results, spent = fan_out(p, a, model, todo, f"{a.batch}-revise", True)
            api.verify_links(p, f"batch {a.batch}: revise round link-verified")
            out["revise"] = {"n": len(results), "kept": sum(1 for x in results if x["outcome"] == "matched"), "cost_usd": round(spent, 3)}
            print(f"revise round: {out['revise']['kept']}/{len(results)} kept, ${spent:.2f}", flush=True)
            r = finish.finish(p, module)
            out["passes"].append({k: r[k] for k in ("ok", "tus", "hoisted", "renamed", "contested", "collapsed", "queue")})
            print(f"tu-finish {module}: ok={r['ok']} collapsed={r['collapsed']} unresolved={len(r['queue'])}", flush=True)
    return out


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--harness", choices=["claude", "codex"], default="claude")
    ap.add_argument("--model", help="claude: haiku|sonnet|opus (default haiku); codex: model name (default gpt-5.6-luna)")
    ap.add_argument("--parallel", type=int, default=48)
    ap.add_argument("--timeout", type=int, default=900, help="seconds per agent")
    ap.add_argument('--seeds', type=Path, help='JSON manifest of saved C, compiler options and scores; selects its functions by default')
    ap.add_argument('--max-checks', type=int, help='checks allowed per worker attempt')
    ap.add_argument('--max-stale', type=int, help='consecutive non-improving checks allowed per worker')
    ap.add_argument('--max-attempts', type=int, help='claim attempt cap for this batch')
    ap.add_argument("--symbols", nargs="*", default=[])
    ap.add_argument("--select", help="module:min_size:max_size:count, e.g. main_rel:8:96:48")
    ap.add_argument("--select-tu", nargs="*", help="whole-file batches: TU names from tus.json, e.g. camera.c coli.c")
    ap.add_argument("--module", default="main_rel", help="module for --select-tu")
    ap.add_argument("--max-size", type=int, default=0, help="size cap for --select-tu")
    ap.add_argument("--retry", type=int, default=0, help="--select-tu: also functions with fewer than N attempts")
    ap.add_argument("--budget-usd", type=float, help="stop launching new agents past this spend (claude only reports cost)")
    ap.add_argument("--batch", default=time.strftime("b%Y%m%d-%H%M"))
    ap.add_argument("--no-trivial", action="store_true", help="skip the mechanical blr/li pass first")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--fast", action="store_true", help="codex: service_tier=fast (2x price, faster generation)")
    ap.add_argument("--effort", choices=["minimal", "low", "medium", "high", "xhigh"], help="codex: model_reasoning_effort")
    ap.add_argument("--shadow", action="store_true",
                    help="A/B trial: run on already-matched functions without relinking or committing")
    ap.add_argument("--finish", action="store_true", help="after the batch: TU-finish pass, revise round on its queue, pass again")
    ap.add_argument("--finish-only", action="store_true", help="no matching batch: just the TU-finish round for --module")
    ap.add_argument("--revise", action="store_true",
                    help="rewrite already-matched functions for readability; kept only if still 100%%")
    a = ap.parse_args(argv)
    for option, name in ((a.max_checks, 'FZGX_MAX_CHECKS'), (a.max_stale, 'FZGX_MAX_STALE'),
                         (a.max_attempts, 'FZGX_MAX_ATTEMPTS')):
        if option is not None:
            if option < 1:
                ap.error(name + ' must be positive')
            os.environ[name] = str(option)
    os.environ['FZGX_CLAIM_TTL'] = str(max(api.DEFAULT_TTL, a.timeout + 300))
    if a.seeds:
        os.environ['FZGX_SEEDS'] = str(a.seeds.resolve())
    model = a.model or ("haiku" if a.harness == "claude" else "gpt-5.6-luna")
    if a.harness == "claude":
        EXPECTED_MODEL["claude"] = CLAUDE_MODELS.get(model, model)  # the guard checks the tier that was asked for
    elif a.model:
        EXPECTED_MODEL["codex"] = a.model
    EFFORT["level"] = a.effort
    p = Project()

    if a.finish_only:
        fr = finish_round(p, a, model, a.module)
        print(json.dumps(fr, indent=1))
        return 0 if all(x["ok"] for x in fr["passes"]) else 1
    symbols = list(a.symbols)
    if a.seeds and not symbols:
        symbols = list(json.loads(a.seeds.read_text()))
    if a.select:
        symbols += select(p, a.select)
    if a.select_tu:
        symbols += select_tu(p, a.module, a.select_tu, a.max_size, a.revise, a.retry)
    if not symbols:
        print("nothing selected", file=sys.stderr)
        return 2
    print(f"batch {a.batch}: {len(symbols)} functions, harness={a.harness} model={model} parallel={a.parallel}")
    if a.dry_run:
        print(" ".join(symbols))
        return 0
    if not a.no_trivial and not a.shadow and not a.revise:
        triv = trivial.apply(p)
        reused = reuse.run(p, max_size=a.max_size or 255, module=a.module)
        from fzgx import lift  # scoped: the lifter needs the build tree, not the harness
        lifted = lift.apply(p, [a.module] if a.module else None, a.max_size or 400)
        print(f"trivial pass: {triv.get('applied', 0)} matched mechanically; reuse: {len(reused['matched'])}; "
              f"lifter: {lifted.get('submitted', 0)} submitted of {lifted.get('lifted', 0)} lifted", flush=True)
        ledger = Ledger()
        symbols = [s for s in symbols if (row := ledger.get(api._key(p, s))) is not None and row['status'] == 'unmatched']
    # nothing is carved up front: a unit exists only once a function matches (submit carves it)

    t0 = time.time()
    results, spent = fan_out(p, a, model, symbols, a.batch, a.revise)
    ver = {"verified": [], "rejected": []}
    if not a.shadow:
        ver = api.verify_links(p, f"batch {a.batch}: link-verified matches")
        print(f"verify: {len(ver.get('verified', []))} verified, {len(ver.get('rejected', []))} rejected"
              + (f" ({ver.get('error')})" if ver.get("error") else ""), flush=True)
        for r in results:
            if r["outcome"] == "matched" and r["symbol"] in ver.get("rejected", []):
                r["outcome"] = "link-mismatch"
    finish_result = None
    if a.finish and not a.shadow:
        finish_result = finish_round(p, a, model, a.module)
    matched = [r for r in results if r["outcome"] == "matched"]
    released = [r for r in results if r["outcome"].startswith("released")]
    other = [r for r in results if r not in matched and r not in released]
    models = sorted({r.get("model") for r in results if r.get("model")})
    summary = {"batch": a.batch, "harness": a.harness, "model": model + (" (fast)" if a.fast else ""), "models_seen": models, "n": len(results), "matched": len(matched),
               "link_rejected": len(ver.get("rejected", [])),
               "released": len(released), "failed": len(other), "cost_usd": round(spent, 3),
               "wall_s": round(time.time() - t0, 1), "finish": finish_result, "results": results}
    # report + snapshot
    rep = STATE_DIR / "reports" / f"{a.batch}{'-shadow' if a.shadow else ''}{'-revise' if a.revise else ''}{'-' + a.effort if a.effort else ''}.md"
    lines = [f"# Batch {a.batch}{' (shadow A/B trial)' if a.shadow else ''} — {a.harness}/{model}, {a.parallel} parallel",
             "", f"{len(results)} functions: {len(matched)} matched, {len(released)} released, {len(other)} failed; "
             f"${spent:.2f}; {summary['wall_s']} s wall.", "",
             "| Function | Outcome | % | Checks | Turns | $ | s |", "|---|---|---|---|---|---|---|"]
    for r in sorted(results, key=lambda r: r["symbol"]):
        lines.append(f"| {r['symbol']} | {r['outcome']} | {'' if r['percent'] is None else r['percent']} | "
                     f"{r['checks'] if r['checks'] is not None else ''} | {r['turns'] or ''} | {r['cost']:.3f} | {r['secs']} |")
    rep.parent.mkdir(parents=True, exist_ok=True)
    rep.write_text("\n".join(lines) + "\n")
    api.snapshot(p)
    subprocess.run(["git", "add", str(ROOT / "state" / "ledger.json")], cwd=ROOT, capture_output=True)
    subprocess.run(["git", "commit", "-q", "-m", f"batch {a.batch}: {len(matched)}/{len(results)} matched ({a.harness}/{model})"],
                   cwd=ROOT, capture_output=True)
    print(json.dumps({k: v for k, v in summary.items() if k != "results"}))
    return 0


if __name__ == "__main__":
    sys.exit(main())
