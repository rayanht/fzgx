"""`fzgx` command line: thin wrapper over tools/fzgx/api.py."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import List, Optional

from . import api, naming, structs, trivial, tu
from .project import Project


def _print(obj, as_json: bool) -> None:
    if as_json:
        print(json.dumps(obj, indent=None, default=str))
    elif isinstance(obj, str):
        print(obj)
    else:
        print(json.dumps(obj, indent=2, default=str))


def cmd_sync(a, p):
    _print(api.sync(p), a.json); return 0


def cmd_inventory(a, p):
    rows = api.inventory(p, a.module, a.status, a.limit, a.max_size)
    if a.json:
        _print(rows, True)
    else:
        for r in rows:
            print(f"{r['status']:9s} {r['module']:13s} {r['symbol']:28s} {r['size']:6d}B  att={r['attempts']} best={r['best']:.0f}%")
        print(f"({len(rows)} functions)")
    return 0


def cmd_claim(a, p):
    r = api.claim(p, a.symbol, a.agent, a.ttl, a.max_attempts, a.no_carve)
    _print(r, a.json); return 0 if r["ok"] else 2


def cmd_carve(a, p):
    _print(api.carve_many(p, a.symbols, a.dry_run), a.json); return 0


def cmd_context(a, p):
    print(api.context(p, a.symbol, a.budget_tokens)); return 0


def cmd_stuck(a, p):
    from . import stuck
    out = stuck.run(p, a.min_percent, a.module, a.workers)
    if a.json:
        print(json.dumps(out, indent=1))
    else:
        print(stuck.summary(out))


def cmd_uncarve(a, p):
    from . import uncarve
    if a.stubs:
        srcs = [u["source"] for u in uncarve.stubs(p)]
    else:
        srcs = a.sources
    print(json.dumps(uncarve.uncarve(p, srcs)))


def cmd_check(a, p):
    r = api.check(p, a.symbol, a.max_diff_lines, a.versions)
    _print(r if a.json else api.format_check(r), a.json)
    if "versions" in r:
        return 0 if any(v >= 100.0 for v in r["versions"].values()) else 1
    return 0 if r["ok"] and r["matched"] else 1


def cmd_submit(a, p):
    names = json.loads(Path(a.names).read_text()) if a.names else None
    r = api.submit(p, a.symbol, a.agent, a.message or "", a.harness, a.model, a.mw_version, a.extra_cflags,
                   names, a.tokens_in, a.tokens_out, a.cost_usd, a.max_diff_lines)
    _print(r, a.json); return 0 if r["ok"] else 1


def cmd_release(a, p):
    r = api.release(p, a.symbol, a.reason, a.harness, a.model, a.tokens_in, a.tokens_out, a.cost_usd)
    _print(r, a.json); return 0 if r["ok"] else 2


def cmd_block(a, p):
    _print(api.block(p, a.symbol, a.reason, a.issue), a.json); return 0


def cmd_unblock(a, p):
    _print(api.unblock(p, a.symbol), a.json); return 0


def cmd_report(a, p):
    r = api.report(p)
    if a.json:
        _print(r, True)
    else:
        tot = {}
        for st in r["ledger"].values():
            for k, v in st.items():
                if not k.endswith("_bytes"):
                    tot[k] = tot.get(k, 0) + v
        print("status totals:", ", ".join(f"{k}={v}" for k, v in sorted(tot.items())))
        print("costs:", r["costs"])
        if r["objdiff"]:
            print("objdiff:", r["objdiff"])
    return 0


def cmd_snapshot(a, p):
    _print(api.snapshot(p), a.json); return 0


def cmd_restore(a, p):
    _print(api.restore(p), a.json); return 0


def cmd_lint(a, p):
    findings = api.lint(p, a.paths)
    if a.json:
        _print(findings, True)
    else:
        for f, rule, line, msg in findings:
            print(f"{f}:{line}: {rule}: {msg}")
        print(f"{len(findings)} finding(s)")
    return 1 if findings else 0


def cmd_trivial(a, p):
    r = trivial.apply(p, a.module.split(",") if a.module else None, a.limit, a.dry_run)
    if not a.dry_run and not a.no_lift:
        from . import lift
        r["lift"] = lift.apply(p, a.module.split(",") if a.module else None, a.max_size, a.limit)
    _print(r, a.json); return 0


def cmd_compare(a, p):
    """A/B: per-function outcome, checks, tokens and cost for two agent-id prefixes."""
    from .ledger import Ledger
    l = Ledger()
    def rows(prefix):
        out = {}
        for r in l.db.execute("SELECT symbol, outcome, checks, final_percent, tokens_in, tokens_out, cost_usd, model "
                              "FROM attempts WHERE agent LIKE ? ORDER BY id", (prefix + "%",)):
            out[r["symbol"]] = dict(r)
        return out
    A, B = rows(a.a), rows(a.b)
    syms = sorted(set(A) | set(B))
    def fmt(r):
        if not r: return "-"
        o = (r["outcome"] or "?").replace("shadow-", "")
        return f"{o[:8]:8s} {r['final_percent'] or 0:5.1f}% c={r['checks'] or 0} in={r['tokens_in'] or 0:>7} out={r['tokens_out'] or 0:>5} ${r['cost_usd'] or 0:.3f}"
    print(f"{'symbol':14s} | A: {a.a:20s} | B: {a.b}")
    for s in syms:
        print(f"{s:14s} | {fmt(A.get(s))} | {fmt(B.get(s))}")
    def tot(R):
        m = sum(1 for r in R.values() if (r["outcome"] or "").endswith("matched"))
        return f"matched {m}/{len(R)}, checks {sum(r['checks'] or 0 for r in R.values())}, tokens in {sum(r['tokens_in'] or 0 for r in R.values())} out {sum(r['tokens_out'] or 0 for r in R.values())}, ${sum(r['cost_usd'] or 0 for r in R.values()):.2f}"
    print(f"A total: {tot(A)}"); print(f"B total: {tot(B)}")
    return 0


def cmd_verify(a, p):
    r = api.verify_links(p, a.message)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_tu_organize(a, p):
    _print(tu.organize(p, a.module), a.json); return 0


def cmd_rename(a, p):
    if a.map:
        r = tu.rename_many(p, json.loads(Path(a.map).read_text()))
    else:
        r = tu.rename(p, a.old, a.new)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_naming_bundle(a, p):
    print(naming.bundle(p, a.module, a.tu, only_matched=not a.all)); return 0


def cmd_naming_apply(a, p):
    _print(naming.apply(p, json.loads(Path(a.file).read_text()), a.by), a.json); return 0


def cmd_structs(a, p):
    info = structs.analyze(p, a.module, a.symbol)
    if a.json:
        _print(info, True)
    else:
        print(f"{a.symbol}: kind={info['kind']} users={len(info['users'])} shapes={info['shapes']}")
        print(structs.typedef(info))
        for poff, fl in sorted(info.get("pointees", {}).items()):
            print(f"// pointee at +0x{poff:X}:"); print(structs.typedef(info, f"At{poff:X}", fl))
    return 0


def cmd_oversize(a, p):
    rows = structs.oversize(p, a.module, a.min_refs)
    if a.json:
        _print(rows, True)
    else:
        for r in rows:
            print(f"{r['symbol']:22s} {r['section']:8s} size 0x{r['size']:<6X} furthest 0x{r['furthest_access']:<6X} refs={r['refs']:3d} swallows {r['n_swallowed']}: {', '.join(r['swallows'][:6])}")
        print(f"({len(rows)} under-sized globals)")
    return 0


def cmd_headers(a, p):
    if a.write:
        err = structs.write_header(p, a.module, a.tu, a.min_refs)
        if err:
            print("SELF-CHECK FAILED:\n" + err); return 1
        print("self-check: every field offset verified under MWCC"); return 0
    print(structs.tu_header(p, a.module, a.tu) if a.tu else structs.header(p, a.module, a.min_refs))
    return 0


def cmd_tu_migrate(a, p):
    r = tu.migrate(p, a.module, verify=not a.no_verify)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_tu_check(a, p):
    from . import tufile  # scoped: keeps the CLI import graph light; tufile pulls the project only
    ok, text = tufile.tu_check(p, a.tu)
    print(("OK" if ok else "FAILED") + f": {a.tu}")
    if text and (not ok or a.verbose):
        print(text)
    return 0 if ok else 1


def cmd_tu_hoist(a, p):
    from . import oracle, tufile  # scoped: keeps the CLI import graph light
    ok_fn = lambda u: oracle.compile_unit(p, p.objdiff_unit_name(u["module"], u["source"]), u["source"]).returncode == 0
    r = tufile.hoist(p, a.tu, ok_fn)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_tu_trial(a, p):
    from . import tutrial  # scoped: trial compile only when asked
    r = tutrial.trial(p, a.tu)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_tu_tidy(a, p):
    from . import tutidy  # scoped: librarian pass only when asked
    r = tutidy.tidy(p, a.tu, dry_run=a.dry_run)
    _print(r, a.json); return 0


def cmd_tu_include(a, p):
    from . import oracle, tufile  # scoped: keeps the CLI import graph light
    ok_fn = lambda u: oracle.compile_unit(p, p.objdiff_unit_name(u["module"], u["source"]), u["source"]).returncode == 0
    r = tufile.add_include(p, a.tu, a.include, ok_fn)
    _print(r, a.json); return 0


def cmd_tu_hoist_decls(a, p):
    from . import tutidy  # scoped: librarian pass only when asked
    r = tutidy.hoist_decls(p, a.tu)
    _print(r, a.json); return 0


def cmd_tu_collapse(a, p):
    from . import collapse  # scoped: collapse pulls the trial compiler; only when asked
    r = collapse.plan(p, a.tu) if a.plan else collapse.collapse(p, a.tu, keep_on_failure=a.keep)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_tu_reflag(a, p):
    from . import oracle, tufile  # scoped: keeps the CLI import graph light
    ok_fn = lambda u: oracle.compile_unit(p, p.objdiff_unit_name(u["module"], u["source"]), u["source"]).returncode == 0
    tus = [a.tu] if a.tu else sorted({u["tu"] for u in p.load_units() if u.get("tu")})
    tot_f, tot_u = [], []
    for tu in tus:
        r = tufile.reflag(p, tu, ok_fn)
        tot_f += r["flagged"]; tot_u += r["unflagged"]
    _print({"tus": len(tus), "flagged": tot_f, "unflagged": tot_u}, a.json); return 0


def cmd_tu_finish(a, p):
    from . import finish  # scoped: the whole pass only when asked
    r = finish.finish(p, a.module)
    r.pop("results", None) if not a.verbose else None
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_sdkmatch(a, p):
    from . import sdkmatch  # scoped: compiles a whole SDK tree; only when asked
    if a.apply:
        r = sdkmatch.apply_names(p)
        print(json.dumps(r, indent=1)); return 0 if r.get("ok") else 1
    roots = [tuple(x.split(":", 1)) for x in a.roots] if a.roots else None
    r = sdkmatch.run(p, a.sdk, a.mw, a.min_size, roots)
    print(json.dumps({k: r[k] for k in ("compiled", "sdk_functions", "dol_functions", "summary")}, indent=1))
    print(f"failed to compile: {len(r['failed'])}", r["failed"][:8])
    return 0


def cmd_why_link(a, p):
    from . import oracle  # scoped
    _print(oracle.why_link(p, a.symbol), a.json); return 0


def cmd_gen(a, p):
    from . import tufile  # scoped: same
    print(f"{tufile.regenerate(p)} generated units")
    return 0


def cmd_permute(a, p):
    from . import permute  # scoped: pulls the permuter glue only when asked
    if a.plateau is not None:
        rows = permute.plateau(p, a.module, a.plateau, a.max_size, a.limit)
        out = []
        for r in rows:
            res = permute.run(p, r["symbol"], a.threads, a.seconds, submit=not a.no_submit)
            print(f"{r['symbol']:24s} base={res.get('base_score')} best={res.get('best_score')} "
                  f"check={res.get('check')} {'SUBMITTED' if res.get('submit', {}).get('ok') else ''} {res.get('secs')}s", flush=True)
            out.append(res)
        n = sum(1 for r in out if r.get("submit", {}).get("ok"))
        print(f"{n}/{len(out)} matched by permutation")
        return 0
    r = permute.run(p, a.symbol, a.threads, a.seconds, submit=not a.no_submit)
    _print(r, a.json); return 0 if r.get("ok") else 1


def cmd_sweep(a, p):
    r = api.sweep_attempts(p, a.module, a.min_percent, a.limit, a.workers)
    _print(r, a.json); return 0


def cmd_names(a, p):
    _print(api.names(p), a.json); return 0


def cmd_read_unit(a, p):
    r = api.read_unit(p, a.symbol)
    _print(r if a.json else (r.get("source") or r.get("error")), a.json); return 0 if r["ok"] else 2


def cmd_write_unit(a, p):
    r = api.write_unit(p, a.symbol, a.agent, Path(a.file).read_text())
    _print(r, a.json); return 0 if r["ok"] else 2


def cmd_lab(a, p):
    from . import lab
    out = lab.run(p, a.min_percent, a.limit, submit=not a.no_submit)
    print(lab.summary(out))
    return 0


def cmd_regalloc(a, p):
    from . import regalloc
    if a.corpus is not None:
        out = regalloc.run(p, a.corpus, a.limit, submit=not a.no_submit)
        print(f"{out['bodies']} bodies, {len(out['matched'])} matched, {out['improved']} improved, {out['candidates']} candidates, {out['secs']} s")
        for s_, label in out["matched"]:
            print(f"  {s_:24s} {label}")
        return 0
    body = None
    if a.body:
        body = Path(a.body).read_text()
    else:
        import sqlite3
        from .project import STATE_DIR
        db = sqlite3.connect(str(STATE_DIR / "ledger.db"))
        row = db.execute("select best_body_path from attempts where symbol=? and best_body_path is not null order by best_in_attempt desc limit 1",
                         (a.symbol.split(":")[-1],)).fetchone()
        if row and Path(row[0]).exists():
            body = Path(row[0]).read_text()
    if body is None:
        print("no body: pass --body or have a saved attempt"); return 2
    r = regalloc.search(p, a.symbol, body, budget_s=a.budget)
    print(json.dumps({k: v for k, v in r.items() if k != "body"}, indent=1))
    if r.get("body") and a.out:
        Path(a.out).write_text(r["body"]); print(f"wrote {a.out}")
    return 0 if r.get("matched") else 1


def cmd_spell(a, p):
    from . import spell
    if a.symbol:
        body = Path(a.body).read_text() if a.body else None
        if body is None:
            from .project import STATE_DIR
            import sqlite3
            db = sqlite3.connect(str(STATE_DIR / "ledger.db"))
            row = db.execute("select best_body_path from attempts where symbol=? and best_body_path is not null order by best_in_attempt desc limit 1",
                             (a.symbol.split(":")[-1],)).fetchone()
            body = Path(row[0]).read_text() if row and Path(row[0]).exists() else None
        if body is None:
            print("no body: pass --body or have a saved attempt"); return 2
        r = spell.search(p, a.symbol, body, budget_s=a.budget)
        print(json.dumps({k: v for k, v in r.items() if k != "body"}, indent=1))
        if r.get("body") and a.out:
            Path(a.out).write_text(r["body"]); print(f"wrote {a.out}")
        return 0 if r.get("matched") else 1
    if a.attempts:
        out = spell.run_attempts(p, a.min_percent, a.limit, a.workers, a.budget, submit=not a.no_submit, module=a.module)
    else:
        out = spell.run_drafts(p, a.min_percent, a.max_percent, a.limit, a.workers, a.budget, submit=not a.no_submit)
    print(f"{out['drafts']} drafts, {len(out['matched'])} matched, {out['improved']} improved, {out['candidates']} candidates, {out['secs']} s; families: {out['families']}")
    for s_, pct, path in out["matched"]:
        print(f"  {s_:20s} {pct:5.1f} {' + '.join(path)[:100]}")
    return 0


def cmd_asm_unit(a, p):
    from . import asmunit
    from .ledger import Ledger
    syms = list(a.symbols)
    if a.blocked:
        syms += [r[0] for r in Ledger().db.execute("select symbol from functions where status='blocked'").fetchall()]
    r = asmunit.make(p, syms)
    print(json.dumps(r, indent=1)); return 0 if r.get("ok") else 2


def cmd_exemplars(a, p):
    from . import exemplars
    ex = exemplars.mine(p)
    print(f"{len(ex)} exemplars -> .fzgx/exemplars.json")
    for e in ex[:10]:
        print(f"  {e['symbol']:24s} {e.get('from') or 0:5.1f}% -> match  mode={e.get('mode')} lines={e['lines']}")
    return 0


def cmd_patch_unit(a, p):
    r = api.patch_unit(p, a.symbol, a.agent, Path(a.old_file).read_text(), Path(a.new_file).read_text())
    _print(r, a.json); return 0 if r["ok"] else 2


def build_parser() -> argparse.ArgumentParser:
    ap = argparse.ArgumentParser(prog="fzgx", description="F-Zero GX decomp agent CLI")
    ap.add_argument("--version", default="GFZE01")
    ap.add_argument("--json", action="store_true", help="machine-readable output")
    sub = ap.add_subparsers(dest="cmd", required=True)

    s = sub.add_parser("sync", help="load functions from dtk config into the ledger"); s.set_defaults(fn=cmd_sync)
    s = sub.add_parser("inventory", help="list functions"); s.set_defaults(fn=cmd_inventory)
    s.add_argument("--module"); s.add_argument("--status"); s.add_argument("--limit", type=int)
    s.add_argument("--max-size", type=int, help="only functions up to N bytes")
    s = sub.add_parser("claim", help="claim a function and carve its unit"); s.set_defaults(fn=cmd_claim)
    s.add_argument("symbol"); s.add_argument("--agent", required=True)
    s.add_argument("--ttl", type=int, default=api.DEFAULT_TTL); s.add_argument("--max-attempts", type=int, default=api.MAX_ATTEMPTS)
    s.add_argument("--no-carve", action="store_true")
    s = sub.add_parser("carve", help="carve functions into units without claiming"); s.set_defaults(fn=cmd_carve)
    s.add_argument("symbols", nargs="+"); s.add_argument("--dry-run", action="store_true")
    s = sub.add_parser("context", help="print the context bundle"); s.set_defaults(fn=cmd_context)
    s.add_argument("symbol"); s.add_argument("--budget-tokens", type=int, default=6000)
    s = sub.add_parser("read-unit", help="print a carved unit's source"); s.set_defaults(fn=cmd_read_unit); s.add_argument("symbol")
    s = sub.add_parser("write-unit", help="replace a claimed unit's source from a file"); s.set_defaults(fn=cmd_write_unit)
    s.add_argument("symbol"); s.add_argument("--agent", required=True); s.add_argument("--file", required=True)
    s = sub.add_parser("patch-unit", help="replace one unique span of a claimed unit's work copy, then check"); s.set_defaults(fn=cmd_patch_unit)
    s.add_argument("symbol"); s.add_argument("--agent", required=True); s.add_argument("--old-file", required=True); s.add_argument("--new-file", required=True)
    s = sub.add_parser("lab", help="perturbation lab: which source rewrite closes a 97%+ body; submits matches"); s.set_defaults(fn=cmd_lab)
    s.add_argument("--min-percent", type=float, default=97.0); s.add_argument("--limit", type=int, default=400); s.add_argument("--no-submit", action="store_true")
    s = sub.add_parser("regalloc", help="register-allocation search on a near-match body (declaration order, scope, initializer splits); --corpus runs every 90%+ attempt and submits matches"); s.set_defaults(fn=cmd_regalloc)
    s.add_argument("symbol", nargs="?"); s.add_argument("--body"); s.add_argument("--out"); s.add_argument("--budget", type=float, default=8.0)
    s.add_argument("--corpus", type=float, help="minimum best percent of the attempts to search"); s.add_argument("--limit", type=int, default=2000); s.add_argument("--no-submit", action="store_true")
    s = sub.add_parser("spell", help="spelling search (beam over every rewrite family, masked-word fitness): one body, or every lifter draft in a score band"); s.set_defaults(fn=cmd_spell)
    s.add_argument("symbol", nargs="?"); s.add_argument("--body"); s.add_argument("--out"); s.add_argument("--budget", type=float, default=10.0)
    s.add_argument("--min-percent", type=float, default=0.0); s.add_argument("--max-percent", type=float, default=100.0)
    s.add_argument("--limit", type=int, default=5000); s.add_argument("--workers", type=int, default=3); s.add_argument("--no-submit", action="store_true")
    s.add_argument("--attempts", action="store_true", help="search the agents' saved plateau bodies instead of the lifter drafts"); s.add_argument("--module")
    s = sub.add_parser("asm-unit", help="link assembly-only functions from their own split assembly (units the build assembles); --blocked takes every blocked function"); s.set_defaults(fn=cmd_asm_unit)
    s.add_argument("symbols", nargs="*"); s.add_argument("--blocked", action="store_true")
    s = sub.add_parser("exemplars", help="mine (plateau -> match) edit pairs from the check history"); s.set_defaults(fn=cmd_exemplars)
    s = sub.add_parser("check", help="compile + objdiff one function"); s.set_defaults(fn=cmd_check)
    s.add_argument("symbol"); s.add_argument("--max-diff-lines", type=int, default=80)
    s.add_argument("--versions", help="'all' or comma list, e.g. GC/1.2.5n,GC/1.3.2: compile under each compiler and report %")
    s = sub.add_parser("submit", help="accept a 100% match: relink, hash, lint, commit"); s.set_defaults(fn=cmd_submit)
    s.add_argument("symbol"); s.add_argument("--agent", default="unknown"); s.add_argument("--names", help="JSON sidecar of name proposals")
    s.add_argument("--message"); s.add_argument("--max-diff-lines", type=int, default=40)
    s.add_argument("--mw-version", help="record a compiler version for this unit (e.g. GC/1.3) before relinking")
    s.add_argument("--extra-cflags", help="extra compiler flags for this unit, space separated")
    s = sub.add_parser("release", help="give up on a claim, keeping the best attempt"); s.set_defaults(fn=cmd_release)
    s.add_argument("symbol"); s.add_argument("--reason", required=True)
    for name in ("submit", "release"):
        sp = sub.choices[name]
        sp.add_argument("--model"); sp.add_argument("--harness")
        sp.add_argument("--tokens-in", type=int, default=0); sp.add_argument("--tokens-out", type=int, default=0)
        sp.add_argument("--cost-usd", type=float, default=0.0)
    s = sub.add_parser("block", help="mark blocked (optionally open a GitHub issue)"); s.set_defaults(fn=cmd_block)
    s.add_argument("symbol"); s.add_argument("--reason", required=True); s.add_argument("--issue", action="store_true")
    s = sub.add_parser("unblock"); s.set_defaults(fn=cmd_unblock); s.add_argument("symbol")
    s = sub.add_parser("report", help="progress and cost summary"); s.set_defaults(fn=cmd_report)
    s = sub.add_parser("snapshot", help="write state/ledger.json"); s.set_defaults(fn=cmd_snapshot)
    s = sub.add_parser("restore", help="load state/ledger.json into the local ledger"); s.set_defaults(fn=cmd_restore)
    s = sub.add_parser("lint", help="shiftability/style lint"); s.set_defaults(fn=cmd_lint); s.add_argument("paths", nargs="*")
    s = sub.add_parser("names", help="pending name proposals for the librarian"); s.set_defaults(fn=cmd_names)
    s = sub.add_parser("tu-organize", help="move carved units into TU directories from tus.json; relink-verify"); s.set_defaults(fn=cmd_tu_organize)
    s.add_argument("--module", default="main_rel")
    s = sub.add_parser("rename", help="rename a symbol everywhere (symbols.txt, src, units.json, ledger, file); relink-verify"); s.set_defaults(fn=cmd_rename)
    s.add_argument("old", nargs="?"); s.add_argument("new", nargs="?"); s.add_argument("--map", help="JSON {old: new} applied with one relink")
    s = sub.add_parser("naming-bundle", help="librarian bundle for one TU"); s.set_defaults(fn=cmd_naming_bundle)
    s.add_argument("tu"); s.add_argument("--module", default="main_rel"); s.add_argument("--all", action="store_true")
    s = sub.add_parser("naming-apply", help="apply a librarian proposal JSON (renames + structs)"); s.set_defaults(fn=cmd_naming_apply)
    s.add_argument("--file", required=True); s.add_argument("--by", default="librarian")
    s = sub.add_parser("structs", help="recover a global's struct layout from all accesses in the module"); s.set_defaults(fn=cmd_structs)
    s.add_argument("symbol"); s.add_argument("--module", default="main_rel")
    s = sub.add_parser("oversize", help="globals whose accesses exceed the symbol size (symbols.txt size corrections)"); s.set_defaults(fn=cmd_oversize)
    s.add_argument("--module", default="main_rel"); s.add_argument("--min-refs", type=int, default=5)
    s = sub.add_parser("headers", help="generate include/rel/<module>/globals.h for the most-referenced globals"); s.set_defaults(fn=cmd_headers)
    s.add_argument("--module", default="main_rel"); s.add_argument("--min-refs", type=int, default=20); s.add_argument("--write", action="store_true")
    s.add_argument("--tu", help="per-file header for this TU (e.g. camera.c) instead of globals.h")
    s = sub.add_parser("tu-migrate", help="stitch a module's per-function units into TU files (blocks; objects generated)"); s.set_defaults(fn=cmd_tu_migrate)
    s.add_argument("--module", default="main_rel"); s.add_argument("--no-verify", action="store_true")
    s = sub.add_parser("tu-check", help="compile a whole TU file as one unit (the goal state)"); s.set_defaults(fn=cmd_tu_check)
    s.add_argument("tu", help="e.g. rel/main_rel/camera.c"); s.add_argument("-v", "--verbose", action="store_true")
    s = sub.add_parser("tu-hoist", help="move block-private includes into the TU prologue if every block still compiles"); s.set_defaults(fn=cmd_tu_hoist)
    s.add_argument("tu", help="e.g. rel/main_rel/camera.c")
    s = sub.add_parser("tu-trial", help="compile a TU file as one unit and score every function against retail"); s.set_defaults(fn=cmd_tu_trial)
    s.add_argument("tu", help="e.g. rel/main_rel/alloc.c")
    s = sub.add_parser("tu-tidy", help="drop block-private declarations the headers cover (kept only if the block still matches)"); s.set_defaults(fn=cmd_tu_tidy)
    s.add_argument("tu"); s.add_argument("--dry-run", action="store_true")
    s = sub.add_parser("tu-include", help="add a header to a TU prologue; blocks that stop compiling are flagged noprologue"); s.set_defaults(fn=cmd_tu_include)
    s.add_argument("tu"); s.add_argument("include", help='e.g. rel/main_rel/alloc.h')
    s = sub.add_parser("tu-hoist-decls", help="move block extern declarations into the TU prologue (canonical per symbol); disagreeing blocks flagged"); s.set_defaults(fn=cmd_tu_hoist_decls)
    s.add_argument("tu")
    s = sub.add_parser("tu-collapse", help="replace a complete TU's per-function units by one unit (hash-verified; reverts on failure)"); s.set_defaults(fn=cmd_tu_collapse)
    s.add_argument("tu"); s.add_argument("--plan", action="store_true", help="compute the ranges only"); s.add_argument("--keep", action="store_true", help="keep the collapsed config even if the hash fails")
    s = sub.add_parser("tu-reflag", help="after a header change: flag blocks that stopped compiling under the prologue, unflag those that compile again"); s.set_defaults(fn=cmd_tu_reflag)
    s.add_argument("tu", nargs="?")
    s = sub.add_parser("tu-finish", help="one pass over every TU of a module: include, tidy, hoist, reflag, collapse complete TUs; prints the revise queue"); s.set_defaults(fn=cmd_tu_finish)
    s.add_argument("--module", default="main_rel"); s.add_argument("-v", "--verbose", action="store_true")
    s = sub.add_parser("sdkmatch", help="identify SDK/runtime functions in the DOL by masked-byte signatures of a compiled public SDK decomp"); s.set_defaults(fn=cmd_sdkmatch)
    s.add_argument("--sdk", default="build/tools/mkdd"); s.add_argument("--mw", default="GC/1.2.5n"); s.add_argument("--min-size", type=int, default=16)
    s.add_argument("--apply", action="store_true", help="name the identified unnamed DOL functions from the saved runs (link-verified)")
    s.add_argument("--roots", nargs="*", help="dir:flagset pairs to compile instead of the SDK layout, e.g. src:smb")
    s = sub.add_parser("why-link", help="link with one rejected match flipped to Matching and name the bytes that differ"); s.set_defaults(fn=cmd_why_link)
    s.add_argument("symbol")
    s = sub.add_parser("gen", help="regenerate every per-function unit from the TU files"); s.set_defaults(fn=cmd_gen)
    s = sub.add_parser("permute", help="decomp-permuter on a plateaued attempt; submits on a byte-identical result"); s.set_defaults(fn=cmd_permute)
    s.add_argument("symbol", nargs="?"); s.add_argument("--threads", type=int, default=8); s.add_argument("--seconds", type=int, default=600)
    s.add_argument("--no-submit", action="store_true")
    s.add_argument("--plateau", type=float, help="batch: every unmatched function with best %% >= this")
    s.add_argument("--module"); s.add_argument("--max-size", type=int, default=1024); s.add_argument("--limit", type=int, default=20)
    s = sub.add_parser("sweep", help="re-check saved attempts of plateaued functions; submit matches and pool matches"); s.set_defaults(fn=cmd_sweep)
    s.add_argument("--module"); s.add_argument("--min-percent", type=float, default=90.0); s.add_argument("--limit", type=int, default=200); s.add_argument("--workers", type=int, default=12)
    s = sub.add_parser("stuck", help="classify plateaued attempts (>= N%) by failure mode from the object diff"); s.set_defaults(fn=cmd_stuck)
    s.add_argument("--min-percent", type=float, default=80.0); s.add_argument("--module"); s.add_argument("--workers", type=int, default=12)
    s.add_argument("--json", action="store_true")
    s = sub.add_parser("uncarve", help="drop units that have no matched code (rejected, or every stub with --stubs); re-splits"); s.set_defaults(fn=cmd_uncarve)
    s.add_argument("sources", nargs="*"); s.add_argument("--stubs", action="store_true")
    s = sub.add_parser("verify", help="relink once for all accepted units, verify hashes, commit; bisect on failure"); s.set_defaults(fn=cmd_verify)
    s.add_argument("--message")
    s = sub.add_parser("compare", help="A/B table for two agent-id prefixes (e.g. b3c-claude vs shadow-b3c-codex)"); s.set_defaults(fn=cmd_compare)
    s.add_argument("--a", required=True); s.add_argument("--b", required=True)
    s = sub.add_parser("trivial", help="mechanically match single-blr and `li r3,N; blr` functions"); s.set_defaults(fn=cmd_trivial)
    s.add_argument("--module", help="comma list; default all"); s.add_argument("--limit", type=int); s.add_argument("--dry-run", action="store_true"); s.add_argument("--no-lift", action="store_true"); s.add_argument("--max-size", type=int, default=160)
    return ap


def main(argv: Optional[List[str]] = None) -> int:
    a = build_parser().parse_args(argv)
    return a.fn(a, Project(a.version))
