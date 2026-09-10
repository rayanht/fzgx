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
    out = stuck.run(p, a.min_percent, a.module, a.workers, a.max_size, a.seeds)
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


def cmd_reuse(a, p):
    from . import reuse
    _print(reuse.run(p, a.max_size, a.module, not a.no_submit), a.json)
    return 0


def cmd_lift(a, p):
    from . import lift
    _print(lift.apply(p, tu=a.tu, callees=a.callee, symbols=a.symbol, submit=not a.no_submit, engine=a.engine, resume=a.resume,
                      max_size=0xFFFFFFFF if a.all else 160, limit=0 if a.all else 2000), a.json)
    return 0


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




def cmd_headers(a, p):
    if a.merge_u64:
        r = structs.merge_u64(p, a.module, dry_run=a.dry_run)
        if a.json:
            _print(r, True); return 0 if r["ok"] else 1
        for lo, hi, n, users in r["pairs"]:
            print(f"{lo:22s} + {hi:22s} pair sightings {n:2d}, refs to the high half {users:2d}")
        print(f"merged {len(r['merged'])}, skipped {len(r['skipped'])}{' (dry run)' if a.dry_run else ''}", r.get("error", ""))
        for a_, b_, why in r["skipped"]:
            print(f"  skipped {a_}+{b_}: {why}")
        return 0 if r["ok"] else 1
    if a.symbol:
        info = structs.analyze(p, a.module, a.symbol)
        if a.json:
            _print(info, True); return 0
        print(f"{a.symbol}: kind={info['kind']} users={len(info['users'])} shapes={info['shapes']}")
        print(structs.typedef(info))
        for poff, fl in sorted(info.get("pointees", {}).items()):
            print(f"// pointee at +0x{poff:X}:"); print(structs.typedef(info, f"At{poff:X}", fl))
        return 0
    if a.oversize:
        rows = structs.oversize(p, a.module, a.min_refs)
        if a.json:
            _print(rows, True); return 0
        for r in rows:
            print(f"{r['symbol']:22s} {r['section']:8s} size 0x{r['size']:<6X} furthest 0x{r['furthest_access']:<6X} refs={r['refs']:3d} swallows {r['n_swallowed']}: {', '.join(r['swallows'][:6])}")
        print(f"({len(rows)} under-sized globals)")
        return 0
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


def cmd_sdkimport(a, p):
    from . import sdkimport
    r = sdkimport.consolidate(p, a.library) if a.consolidate else sdkimport.run(p, a.library, do_submit=not a.no_submit)
    _print(r, a.json)
    return 0 if not r.get('still') and not r.get('errors') and not r.get('failed') else 1


def cmd_sourcealign(a, p):
    from . import sourcealign
    if a.fuzzy:
        from . import fuzzy
        _print(fuzzy.run(p, a.min_size, a.root, a.rel_only), a.json)
        return 0
    if a.apply_names:
        result = sourcealign.apply_names(p)
        _print(result, a.json)
        return 0 if result['ok'] else 1
    if a.recheck_saved:
        _print(sourcealign.recheck_saved(p, a.symbol, not a.no_submit), a.json)
        return 0
    if a.compile_sdk:
        _print(sourcealign.compile_library(p, a.compile_sdk, a.root, a.functions), a.json)
        return 0
    result = sourcealign.submit_saved(p, a.symbol) if a.submit_saved else sourcealign.run(
        p, a.min_size, a.symbol, a.saved, not a.no_submit, a.discover, roots=a.root, rel_only=a.rel_only)
    _print(result, a.json)
    return 0


def cmd_why_link(a, p):
    from . import oracle  # scoped
    _print(oracle.why_link(p, a.symbol), a.json); return 0





def cmd_sweep(a, p):
    if a.symbol:
        body = Path(a.body).read_text() if a.body else api._attempt_text(p, a.symbol)
        if body is None:
            print("no body: pass --body or have a saved attempt"); return 2
        r = api.sweep_one(p, a.symbol, body, a.budget)
        print(json.dumps({k: v for k, v in r.items() if k not in ("body", "best_body")}, indent=1))
        if r.get("body") and a.out:
            Path(a.out).write_text(r["body"]); print(f"wrote {a.out}")
        return 0 if r.get("matched") else 1
    out = api.sweep(p, a.module, a.min_percent, a.limit, a.workers, a.drafts, a.max_percent, a.budget, not a.no_submit, a.max_size, not a.fixup_only)
    if a.json:
        _print(out, True); return 0
    print(f"{out['candidates']} bodies: {out['checked']} checked, {out['cached']} memoised; "
          f"{len(out['submitted'])} matched as saved, {len(out['pool'])} pool, {len(out['fixed'])} fixed, {len(out['spelled'])} spelled")
    for key, label in out["fixed"]:
        print(f"  fixup  {key:24s} {label}")
    for key, pct, path in out["spelled"]:
        print(f"  spell  {key:24s} {' + '.join(path)[:100]}")
    sp = out.get("spell") or {}
    if sp:
        print(f"spell: {sp.get('searched')} searched, {sp.get('skipped')} memoised, {sp.get('improved')} improved, {sp.get('candidates')} candidates, {sp.get('secs')} s; families {sp.get('families')}")
    lint = [k for k, v in out["still"] if v == "lint"]
    if lint:
        print(f"still refused by the lint: {lint}")
    return 0


def cmd_read_unit(a, p):
    r = api.read_unit(p, a.symbol)
    _print(r if a.json else (r.get("source") or r.get("error")), a.json); return 0 if r["ok"] else 2


def cmd_write_unit(a, p):
    r = api.write_unit(p, a.symbol, a.agent, Path(a.file).read_text())
    _print(r, a.json); return 0 if r["ok"] else 2





def cmd_asm_unit(a, p):
    from . import asmunit
    from .ledger import Ledger
    syms = list(a.symbols)
    if a.blocked:
        syms += [r[0] for r in Ledger().db.execute("select symbol from functions where status='blocked'").fetchall()]
    r = asmunit.make(p, syms)
    print(json.dumps(r, indent=1)); return 0 if r.get("ok") else 2



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
    s = sub.add_parser("asm-unit", help="link assembly-only functions from their own split assembly (units the build assembles); --blocked takes every blocked function"); s.set_defaults(fn=cmd_asm_unit)
    s.add_argument("symbols", nargs="*"); s.add_argument("--blocked", action="store_true")
    s = sub.add_parser("check", help="compile + objdiff one function"); s.set_defaults(fn=cmd_check)
    s.add_argument("symbol"); s.add_argument("--max-diff-lines", type=int, default=80)
    s.add_argument("--versions", help="'all' or comma list, e.g. GC/1.2.5n,GC/1.3.2: compile under each compiler and report %%")
    s = sub.add_parser("submit", help="accept a 100%% match: relink, hash, lint, commit"); s.set_defaults(fn=cmd_submit)
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
    s = sub.add_parser("tu-organize", help="move carved units into TU directories from tus.json; relink-verify"); s.set_defaults(fn=cmd_tu_organize)
    s.add_argument("--module", default="main_rel")
    s = sub.add_parser("rename", help="rename a symbol everywhere (symbols.txt, src, units.json, ledger, file); relink-verify"); s.set_defaults(fn=cmd_rename)
    s.add_argument("old", nargs="?"); s.add_argument("new", nargs="?"); s.add_argument("--map", help="JSON {old: new} applied with one relink")
    s = sub.add_parser("naming-bundle", help="librarian bundle for one TU"); s.set_defaults(fn=cmd_naming_bundle)
    s.add_argument("tu"); s.add_argument("--module", default="main_rel"); s.add_argument("--all", action="store_true")
    s = sub.add_parser("naming-apply", help="apply a librarian proposal JSON (renames + structs)"); s.set_defaults(fn=cmd_naming_apply)
    s.add_argument("--file", required=True); s.add_argument("--by", default="librarian")
    s = sub.add_parser("headers", help="generate include/rel/<module>/globals.h for the most-referenced globals (--symbol: one global's recovered layout; --oversize: globals whose accesses exceed the symbol size)"); s.set_defaults(fn=cmd_headers)
    s.add_argument("--module", default="main_rel"); s.add_argument("--min-refs", type=int, default=20); s.add_argument("--write", action="store_true")
    s.add_argument("--tu", help="per-file header for this TU (e.g. camera.c) instead of globals.h")
    s.add_argument("--symbol", help="print the recovered struct layout of one global"); s.add_argument("--oversize", action="store_true")
    s.add_argument("--merge-u64", action="store_true", help="merge adjacent 4-byte symbols retail moves as a register pair into one u64 (relink-verified)"); s.add_argument("--dry-run", action="store_true")
    s = sub.add_parser("tu-migrate", help="stitch a module's per-function units into TU files (blocks; objects generated)"); s.set_defaults(fn=cmd_tu_migrate)
    s.add_argument("--module", default="main_rel"); s.add_argument("--no-verify", action="store_true")
    s = sub.add_parser("tu-check", help="compile a whole TU file as one unit (the goal state)"); s.set_defaults(fn=cmd_tu_check)
    s.add_argument("tu", help="e.g. rel/main_rel/camera.c"); s.add_argument("-v", "--verbose", action="store_true")
    s = sub.add_parser("tu-finish", help="one pass over every TU of a module: include, tidy, hoist, reflag, collapse complete TUs; prints the revise queue"); s.set_defaults(fn=cmd_tu_finish)
    s.add_argument("--module", default="main_rel"); s.add_argument("-v", "--verbose", action="store_true")
    s = sub.add_parser("sdkimport", help="import saved SDK C signatures with shared declarations and verified relocation bindings"); s.set_defaults(fn=cmd_sdkimport)
    s.add_argument("--library", choices=["card", "os", "exi", "si", "ar", "vi", "dvd", "gx", "dsp", "pad", "ai", "Runtime", "MSL"], default="card")
    s.add_argument("--no-submit", action="store_true", help="adapt and check C without submitting units")
    s.add_argument("--consolidate", action="store_true", help="combine complete, identified SDK source files and verify the link")
    s = sub.add_parser("sourcealign", help="recover SDK relatives and C layouts from instruction alignment and compiler probes"); s.set_defaults(fn=cmd_sourcealign)
    s.add_argument("--min-size", type=int, default=256)
    s.add_argument("--symbol", action="append", default=[])
    s.add_argument("--saved", action="store_true", help="use the saved source discovery")
    s.add_argument("--discover", action="store_true", help="only identify source relatives")
    s.add_argument("--no-submit", action="store_true")
    s.add_argument("--submit-saved", action="store_true", help="recheck and submit saved exact candidates without repeating probes")
    s.add_argument("--recheck-saved", action="store_true", help="recheck bound imports after oracle repairs without repeating layout probes")
    s.add_argument("--compile-sdk", help="compile another local SDK donor tree under build/tools")
    s.add_argument("--functions", action="store_true", help="compile donor functions independently, excluding unresolved dependencies")
    s.add_argument("--apply-names", action="store_true", help="apply unambiguous function names from verified licensed imports")
    s.add_argument("--root", action="append", default=[], help="source root relative to the SDK; filters compilation or discovery, repeatable")
    s.add_argument("--rel-only", action="store_true", help="discover matches in REL modules only")
    s.add_argument("--fuzzy", action="store_true", help="rank whole-function and partial overlap below import cutoffs")
    s = sub.add_parser("sdkmatch", help="identify SDK/runtime functions in the DOL by masked-byte signatures of a compiled public SDK decomp"); s.set_defaults(fn=cmd_sdkmatch)
    s.add_argument("--sdk", default="build/tools/mkdd"); s.add_argument("--mw", default="GC/1.2.5n"); s.add_argument("--min-size", type=int, default=16)
    s.add_argument("--apply", action="store_true", help="name the identified unnamed DOL functions from the saved runs (link-verified)")
    s.add_argument("--roots", nargs="*", help="dir:flagset pairs to compile instead of the SDK layout, e.g. src:smb")
    s = sub.add_parser("why-link", help="link with one rejected match flipped to Matching and name the bytes that differ"); s.set_defaults(fn=cmd_why_link)
    s.add_argument("symbol")
    s = sub.add_parser("sweep", help="the search over every saved body: re-check, fixup, spelling search; submits matches. One symbol: the same stages on one body"); s.set_defaults(fn=cmd_sweep)
    s.add_argument("symbol", nargs="?"); s.add_argument("--body"); s.add_argument("--out")
    s.add_argument("--module"); s.add_argument("--min-percent", type=float, default=80.0); s.add_argument("--max-percent", type=float, default=100.0)
    s.add_argument("--limit", type=int, default=2000); s.add_argument("--workers", type=int, default=12); s.add_argument("--budget", type=float, default=10.0)
    s.add_argument("--drafts", action="store_true", help="the lifter's drafts (fzgx trivial) instead of the agents' saved bodies")
    s.add_argument("--no-submit", action="store_true")
    s.add_argument("--fixup-only", action="store_true", help="recheck and repair saved bodies without the spelling beam")
    s.add_argument("--max-size", type=int, help="only functions up to N bytes")
    s = sub.add_parser("stuck", help="classify plateaued attempts (>= N%%) by failure mode from the object diff"); s.set_defaults(fn=cmd_stuck)
    s.add_argument('--seeds', type=Path, help='analyse saved candidates with their recorded compiler settings')
    s.add_argument("--min-percent", type=float, default=80.0); s.add_argument("--module"); s.add_argument("--workers", type=int, default=12)
    s.add_argument("--max-size", type=int, help="only functions up to N bytes")
    s.add_argument("--json", action="store_true")
    s = sub.add_parser("uncarve", help="drop units that have no matched code (rejected, or every stub with --stubs); re-splits"); s.set_defaults(fn=cmd_uncarve)
    s.add_argument("sources", nargs="*"); s.add_argument("--stubs", action="store_true")
    s = sub.add_parser("verify", help="relink once for all accepted units, verify hashes, commit; bisect on failure"); s.set_defaults(fn=cmd_verify)
    s.add_argument("--message")
    s = sub.add_parser("compare", help="A/B table for two agent-id prefixes (e.g. b3c-claude vs shadow-b3c-codex)"); s.set_defaults(fn=cmd_compare)
    s.add_argument("--a", required=True); s.add_argument("--b", required=True)
    s = sub.add_parser("trivial", help="mechanically match single-blr and `li r3,N; blr` functions"); s.set_defaults(fn=cmd_trivial)
    s.add_argument("--module", help="comma list; default all"); s.add_argument("--limit", type=int); s.add_argument("--dry-run", action="store_true"); s.add_argument("--no-lift", action="store_true"); s.add_argument("--max-size", type=int, default=160)
    s = sub.add_parser("reuse", help="reuse verified C for identical retail instruction shapes"); s.set_defaults(fn=cmd_reuse)
    s.add_argument("--module"); s.add_argument("--max-size", type=int, default=255)
    s.add_argument("--no-submit", action="store_true")
    s = sub.add_parser('lift', help='lift unmatched functions in a TU or callers of a shared interface'); s.set_defaults(fn=cmd_lift)
    scope = s.add_mutually_exclusive_group(required=True)
    scope.add_argument('--tu', help='TU path relative to src/, e.g. rel/main_rel/accessory.c')
    scope.add_argument('--callee', action='append', help='direct callee to select callers of; repeat for a shared interface')
    scope.add_argument('--symbol', action='append', help='regenerate selected functions without a size cap; repeatable')
    scope.add_argument('--all', action='store_true', help='all unmatched functions, without a size or count cap')
    s.add_argument('--engine', choices=('lift', 'm2c'), default='lift')
    s.add_argument('--resume', action='store_true', help='reuse saved m2c candidates and retry generation or compilation failures')
    s.add_argument('--no-submit', action='store_true')
    return ap


def main(argv: Optional[List[str]] = None) -> int:
    a = build_parser().parse_args(argv)
    return a.fn(a, Project(a.version))
