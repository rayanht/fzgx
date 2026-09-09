"""Context bundle for a matcher: everything it needs, ordered by value per token."""

from __future__ import annotations

import json
import re
import struct
from pathlib import Path
from typing import List, Optional

from .ledger import Ledger
from . import tufile
from .project import STATE_DIR, ROOT, Function, Project, Symbol

RULES = ROOT / "docs" / "CODING_RULES.md"
IDIOMS = ROOT / "docs" / "MWCC_IDIOMS.md"


def _sig_hint(fn: Function) -> str:
    """Cheap hints from the prologue/epilogue: stack frame, saved regs, float use."""
    body = " ".join(fn.asm)
    hints = []
    if "stwu r1" in body:
        hints.append("has stack frame")
    else:
        hints.append("leaf, no stack frame")
    if any(m in body for m in ("fadds", "fmuls", "fdivs", "lfs ", "stfs", "fcmpu", "frsp", "fmr")):
        hints.append("uses float")
    if "mtctr" in body and "bctr" in body:
        hints.append("has switch/jump table or indirect call")
    if "_savegpr" in body or "stmw" in body:
        hints.append("saves many GPRs (many locals or calls)")
    return "; ".join(hints)


def _decl_for(sym: Symbol) -> str:
    if sym.kind == "function":
        return f"extern void {sym.name}(void);  // {sym.section}:0x{sym.addr:08X} size 0x{sym.size:X} (signature unknown)"
    dt = sym.attrs.get("data", "")
    ctype = {"byte": "u8", "2byte": "u16", "4byte": "u32", "8byte": "u64", "float": "f32",
             "double": "f64", "string": "char"}.get(dt, "u8")
    n = max(sym.size, 1)
    unit = {"u16": 2, "u32": 4, "u64": 8, "f32": 4, "f64": 8}.get(ctype, 1)
    arr = f"[{n // unit}]" if n // unit > 1 else ""
    return f"extern {ctype} {sym.name}{arr};  // {sym.section}:0x{sym.addr:08X} size 0x{sym.size:X} scope {sym.scope}"


def _header_decl(hdr: str, name: str) -> str:
    """The typedef (if any) and extern line for `name` from a generated globals header."""
    m = re.search(rf"^extern (\w+) \*?{re.escape(name)};", hdr, re.M)
    if not m:
        return ""
    tname = m.group(1)

    def td_of(t: str) -> str:
        td = re.search(rf"^typedef struct \{{\n(?:(?!typedef).*\n)*?\}} {re.escape(t)};", hdr, re.M)
        body = td.group(0) if td else ""
        if body.count("\n") > 40:  # keep bundles small: show the first fields and a count
            lines = body.splitlines()
            body = "\n".join(lines[:30]) + f"\n    /* ... {len(lines) - 31} more fields ... */\n" + lines[-1]
        return body

    body = td_of(tname)
    # pointee typedefs referenced by pointer fields come first, as in the header
    pointees = [td_of(t) for t in re.findall(r"^\s+(\w+) \*unk_", body, re.M)]
    return "\n".join(x for x in pointees + [body] if x) + ("\n" if body else "") + m.group(0)


# failure mode (from stuck.classify_rows / _pure) -> what changed in bodies that then matched
MODE_TIPS = {
    "schedule": "same instructions, different order: MWCC emits argument materialisation and loads in source order; "
                "reorder the statements or the argument expressions, or load a value into a local once and reuse it "
                "(a value used across a call lives in a non-volatile register: `x = g->f; call(); use(x)`).",
    "regalloc": "register numbers only: allocation follows declaration order of locals and the order values are first "
                "used; reorder local declarations, merge two temporaries into one, or split one variable into two.",
    "frame": "stack frame or local offsets differ: a local array/struct is missing or sized differently, or a scalar is "
             "spilled because it lives across a call; compare `stwu` sizes and add/remove/resize locals.",
    "ext": "missing or extra extsh/extsb/clrlwi: a parameter, local or field has the wrong width or signedness "
           "(s16 vs u16 vs s32); the extension appears where a narrow value is used as an int.",
    "signedness": "cmpw vs cmplw / cmpwi vs cmplwi: the compared operand's type (signed vs unsigned) decides it; "
                  "check the variable, the field and the literal (`0x80` vs `0x80u`).",
    "imm": "an immediate differs: a struct field offset (fix the struct layout), a stride (array element size), a "
           "mask (`& 0xFF` vs `& 0x7F`), or a constant folded from an expression.",
    "reloc": "a relocation names another symbol: the wrong global or callee, or a private literal where retail "
             "pools a shared constant (declare the pooled `lbl_*_rodata_*` symbol and use it).",
    "ins:float": "float rows differ: f32 vs f64 arithmetic; a double literal (`1.0`) promotes the expression, `1.0f` "
                 "does not; `frsp` means a double was narrowed.",
    "ins:branch": "branch rows differ: the condition sense or block order; `if (a) X else Y` vs `if (!a) Y else X`, "
                  "`==` vs `!=`, early `return` vs `else`, `&&` chains vs nested ifs.",
    "op:li/addi": "li vs addi: a constant written directly vs derived from another value (`x = 0` vs `x = y - y`, "
                  "or `n = 5` vs `n = m + 1`); also a zero-init reused from another variable.",
    "op:addi/mr": "addi vs mr: the compiler copied a register instead of adding 0; an expression like `p + 0` or a "
                  "different pointer base (`&s->f` vs `s`).",
    "mixed": "several kinds at once: fix the structural ones first (frame, ext, imm, reloc), then scheduling and "
             "registers usually follow.",
}


def _pooled_constant(project: Project, s: Symbol) -> Optional[str]:
    """A float/double literal in .rodata/.sdata2 with its retail value, as a declaration."""
    if s.kind != "object" or s.section not in (".rodata", ".sdata2") or s.size not in (4, 8):
        return None
    raw = project.bytes_at(s.module, s.name)
    if raw is None:
        return None
    if s.size == 4:
        v = struct.unpack(">f", raw)[0]
        return f"extern const f32 {s.name};  // = {v!r}f (retail literal pool)"
    v = struct.unpack(">d", raw)[0]
    return f"extern const f64 {s.name};  // = {v!r} (retail literal pool)"


def _spell_fitness(tw, ow) -> float:
    import difflib  # scoped: one alignment
    sm = difflib.SequenceMatcher(None, tw, ow, autojunk=False)
    return 100.0 * sum(b.size for b in sm.get_matching_blocks()) / max(len(tw), len(ow))


def build_context(project: Project, ledger: Optional[Ledger], symbol: str,
                  budget_tokens: int = 6000) -> str:
    sym0 = project.resolve(symbol)
    fn = project.function_asm(sym0.module).get(sym0.name) if sym0 else None
    if fn is None:
        raise LookupError(f"{symbol}: no disassembly (is it a function? ambiguous? run ninja first)")
    sym = fn.symbol
    module = sym.module
    symbol = sym.name
    row = ledger.get(project.key(sym)) if ledger else None
    unit_src = project.unit_of(sym)
    units = {u["source"]: u for u in project.load_units()}
    unit_cfg = units.get(unit_src or "", {})

    parts: List[str] = []
    parts.append(f"# Match task: `{symbol}`")
    parts.append(
        f"- module: `{module}`  section: `{sym.section}`  address: `0x{sym.addr:08X}`  "
        f"size: {sym.size} bytes ({sym.size // 4} instructions)  scope: {sym.scope}"
    )
    if unit_src and unit_cfg.get("tu"):
        parts.append(f"- unit: block `{symbol}` of `src/{unit_cfg['tu']}` (you write the unit; the tooling splices it in)")
        tf = tufile.load(project, unit_cfg["tu"])
        if tf.prologue.strip():
            parts.append(f"\n## Already in scope: the prologue of `src/{unit_cfg['tu']}`\n"
                         "Every block of the file is compiled after these lines. Do not redeclare what they declare; "
                         "if one of them is wrong for the retail bytes of your function, say so in your release reason.\n"
                         "```c\n" + tf.prologue.strip() + "\n```")
    else:
        parts.append(f"- unit: `src/{unit_src}`" if unit_src else "- unit: created when the function matches (write the complete unit; checks diff it against the retail object)")
    if row and not (row["claimed_by"] or "").startswith("shadow-"):
        parts.append(f"- attempts so far: {row['attempts']}  best: {row['best_percent']:.1f}%")
    parts.append(f"- hints: {_sig_hint(fn)}")
    mw = unit_cfg.get("mw_version") or ("GC/1.2.5n" if module == "main" else "GC/1.3.2")
    parts.append(f"- compiler: `{mw}` `-O4,p -inline auto -fp hardware -enum int`"
                 + (" `-sdata 0 -sdata2 0`" if module != "main" else "")
                 + (f" extra: `{' '.join(unit_cfg.get('extra_cflags', []))}`" if unit_cfg.get("extra_cflags") else ""))

    parts.append("\n## Target assembly (retail)\n```asm")
    parts.extend(fn.asm)
    parts.append("```")

    if fn.refs:
        header = ROOT / "include" / project.module_src_prefix(module) / "globals.h"
        hdr_text = header.read_text() if header.exists() else ""
        tu_stem = None
        tus_path = project.module_config_dir(module) / "tus.json"
        if tus_path.exists():
            for t in json.loads(tus_path.read_text())["tus"]:
                if symbol in t["functions"]:
                    tu_stem = t["file"].rsplit(".", 1)[0]
                    break
        tu_header = ROOT / "include" / project.module_src_prefix(module) / f"{tu_stem}.h" if tu_stem else None
        tu_hdr_text = tu_header.read_text() if tu_header and tu_header.exists() else ""
        hdr_text = hdr_text + "\n" + tu_hdr_text
        shown_from_header = []
        parts.append("\n## Referenced symbols (declare what you use; names are provisional)\n```c")
        pooled = []
        for name in fn.refs:
            s = project.find_symbol(name, module) or project.find_symbol(name)
            if not s:
                continue
            const = _pooled_constant(project, s)
            if const:  # a literal-pool constant beats whatever the header calls it
                parts.append(const)
                pooled.append(name)
                continue
            if hdr_text and re.search(rf"^extern .*\b{re.escape(name)};", hdr_text, re.M):
                shown_from_header.append(name)
                continue
            parts.append(_decl_for(s))
        parts.append("```")
        if pooled:
            parts.append("Constant pool: the target loads these from the module's shared literal pool. "
                         "Declare them `extern const` as shown and use the symbol; writing the literal "
                         "in C emits a private constant with a different relocation and never matches.")
        if shown_from_header:
            inc = f"{project.module_src_prefix(module)}/{tu_stem}.h" if tu_hdr_text else f"{project.module_src_prefix(module)}/globals.h"
            parts.append(f"\nThese are declared in `include/{inc}` with recovered struct layouts; "
                         f"`#include \"{inc}\"` and use the typed fields (`unk_XX` names are offsets) "
                         f"instead of casts or your own extern:")
            parts.append("```c")
            for name in shown_from_header:
                parts.append(_header_decl(hdr_text, name))
            parts.append("```")

    callers = project.callers(symbol)
    if callers:
        parts.append(f"\n## Callers: {', '.join(f'`{c}`' for c in callers)}")

    # Matched C in the same module: first the siblings that share callees and globals with this
    # function (their declaration style is what the compiler wanted), then the nearest by address.
    matched_units = [u for u in project.load_units()
                     if u["module"] == module and u["status"] == "matching" and u["source"] != unit_src]
    asm_index = project.function_asm(module)
    my_refs = set(fn.refs)
    def overlap(u):
        f2 = asm_index.get(u["symbols"][0])
        return len(my_refs & set(f2.refs)) if f2 else 0
    by_overlap = sorted((u for u in matched_units if overlap(u) >= 2), key=lambda u: -overlap(u))[:2]
    by_addr = sorted(matched_units, key=lambda u: abs((project.find_symbol(u["symbols"][0]) or sym).addr - sym.addr))
    chosen, seen_src = [], set()
    for u in by_overlap + by_addr:
        if u["source"] not in seen_src and len(chosen) < 3:
            chosen.append(u); seen_src.add(u["source"])
    neigh: List[str] = []
    for u in chosen:
        body = tufile.unit_text(project, u)
        if body and len(body) < 2500:
            label = f"src/{u['tu']}#{u['symbols'][0]}" if u.get("tu") else f"src/{u['source']}"
            shared = sorted(my_refs & set((asm_index.get(u["symbols"][0]).refs if asm_index.get(u["symbols"][0]) else [])))
            note = f"  (shares {', '.join(f'`{r}`' for r in shared[:6])}: declare and call these the same way)" if len(shared) >= 2 else ""
            neigh.append(f"### {label}{note}\n```c\n{body}\n```")
    if neigh:
        parts.append("\n## Matched code in this module (siblings sharing symbols first; copy their declaration style)")
        parts.extend(neigh)

    if unit_src:
        work = project.work_path(project.key(sym))
        cur = work.read_text() if work.exists() else (tufile.unit_text(project, unit_cfg) if unit_cfg else "")
        if cur.strip():
            parts.append(f"\n## Current unit\n```c\n{cur}\n```")

    if ledger and not (row and (row["claimed_by"] or "").startswith("shadow-")):
        att = ledger.db.execute(
            "SELECT * FROM attempts WHERE symbol=? AND ended IS NOT NULL ORDER BY final_percent DESC, id DESC LIMIT 1",
            (symbol,)).fetchone()
        if att and att["best_body_path"] and Path(att["best_body_path"]).exists():
            body = Path(att["best_body_path"]).read_text()
            parts.append(f"\n## Best prior attempt ({att['final_percent'] or 0:.1f}%, notes: {att['notes'] or '-'})\n```c\n{body}\n```")
            # the plateau itself: which rows still differ and what kind of difference they are, so the
            # next attempt changes their cause instead of resubmitting the same body
            try:
                from . import oracle, stuck
                res = oracle.check(project, symbol, 0, source=Path(att["best_body_path"]))
                if res.ok and not res.matched:
                    lrows, rrows = getattr(res, "_rows", ([], []))
                    counts = stuck.classify_rows(lrows, rrows)
                    mode = stuck._pure(counts, lrows, rrows)
                    diffs = [(i, stuck._fmt(a), stuck._fmt(b)) for i, (a, b) in enumerate(zip(lrows, rrows))
                             if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" or (b.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE"]
                    kinds = ", ".join(f"{k} {v}" for k, v in counts.items() if ":" not in k)
                    lines = [f"{i:4d}  {t:38s} | {o}" for i, t, o in diffs[:24]]
                    parts.append(f"\n### Why it plateaued: {mode} ({kinds}); {len(diffs)} rows differ (target | prior attempt)\n```\n"
                                 + "\n".join(lines) + ("\n..." if len(diffs) > 24 else "") + "\n```")
                    tips = [t for k, t in MODE_TIPS.items() if k in mode or k in counts or any(k in x for x in counts)]
                    if tips:
                        parts.append("What usually causes this kind of row, from functions that went on to match:\n- " + "\n- ".join(dict.fromkeys(tips)))
                    try:
                        from . import exemplars as _ex
                        for e in _ex.nearest(mode, {k: v for k, v in counts.items() if ":" not in k}):
                            parts.append(f"\n### Exemplar: `{e['symbol']}` went from {e.get('from') or 0:.0f}% to a match ({e.get('mode')}) with this edit\n```diff\n" + "\n".join(e["diff"]) + "\n```")
                    except Exception:
                        pass
            except Exception:
                pass

    # the lifter's draft: a mechanical translation of the disassembly, structurally right by
    # construction (calls, layouts, loops), shown with the rows it still misses so the agent
    # starts from it instead of from nothing
    if ledger and row and row["status"] != "matched" and not (row["claimed_by"] or "").startswith("shadow-"):
        try:
            from . import lift as _lift, oracle as _oracle
            variants = _lift.lift_variants(project, module, symbol)
            tgt = project.target_object_for(sym)
            best = None
            if variants and tgt:
                ddir = STATE_DIR / "lift" / "ctx"; ddir.mkdir(parents=True, exist_ok=True)
                srcs = []
                for vi, vt in enumerate(variants):
                    f = ddir / f"{project.key(sym).replace(':', '__')}_{vi}.c"; f.write_text(vt); srcs.append(f)
                for ver, ex in _oracle.version_candidates(project, module):
                    objs = _oracle.compile_many(project, module, srcs, ddir / "obj" / (ver.replace("/", "_") + ("_stmw" if ex else "")), ver, ex)
                    for vt, f in zip(variants, srcs):
                        o = objs.get(f)
                        rows = _oracle.function_rows(project, symbol, tgt, o) if o else None
                        if rows and (best is None or rows[2] > best[0]):
                            best = (rows[2], vt, rows)
            if best:
                pct, vt, (lr, rr, _) = best
                diffs = [(i, stuck._fmt(a), stuck._fmt(b)) for i, (a, b) in enumerate(zip(lr, rr)) if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" or (b.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE"]
                lines = [f"{i:4d}  {t:38s} | {o}" for i, t, o in diffs[:20]]
                if pct >= 60:
                    head = (f"\n## Mechanical draft ({pct:.1f}%): lifted from the disassembly, verified to this score\n"
                            "Its calls, struct layouts, locals and loops are taken from the retail code; what it misses is\n"
                            "in the rows below (target | draft). Start from it: rename, restructure, fix those rows.\n")
                else:
                    head = (f"\n## Mechanical draft ({pct:.1f}%, low): lifted from the disassembly; the shape is off but the\n"
                            "declarations, struct layouts, call prototypes and locals are from the retail code. Keep those;\n"
                            "rewrite the control flow and expression shapes from the disassembly (first differing rows below).\n")
                parts.append(head + "```c\n" + vt + "\n```\n"
                             + ("```\n" + "\n".join(lines) + ("\n..." if len(diffs) > 20 else "") + "\n```" if diffs else ""))
            else:
                # no full draft: the never-give-up draft (unknown instructions marked `???`) when it
                # compiles, with the first row where it diverges from retail; else the skeleton
                total = _lift.lift_total(project, module, symbol)
                shown_total = False
                if total and tgt:
                    try:
                        from . import repair as _repair
                        tdir = STATE_DIR / "lift" / "ctx"; tdir.mkdir(parents=True, exist_ok=True)
                        tf = tdir / f"{project.key(sym).replace(':', '__')}_total.c"; tf.write_text(total)
                        mw_, extra_ = _oracle.version_for(project, sym, tf)
                        to = tdir / "obj" / (tf.stem + ".o"); to.parent.mkdir(parents=True, exist_ok=True)
                        cp_ = _oracle.compile_source(project, module, tf, to, mw_, ((extra_ + " ") if extra_ else "") + "-g")
                        if cp_.returncode == 0 and to.exists():
                            tw_ = _oracle.words(tgt, symbol); ow_ = _oracle.words(to, symbol)
                            aligned = _spell_fitness(tw_, ow_) if tw_ and ow_ else 0.0
                            div = _repair.first_divergence(project, sym, tgt, to)
                            where = f"first divergence at row {div[0]} of {div[2]}, produced by line {div[1]} of the draft" if div and div[1] else ("no divergence found" if div is None else f"first divergence at row {div[0]}")
                            markers = total.count("/* ???")
                            parts.append(f"\n## Mechanical draft, complete but unverified ({aligned:.0f}% of retail words align; {markers} instruction(s) marked `???`)\n"
                                         "Every call, struct layout, loop and branch below is taken from the retail code; instructions the\n"
                                         "lifter could not express are left as `/* ??? mnemonic */` with an `unk_N` local for their result.\n"
                                         f"{where} (line numbers count from the first line of the code block). Start from this text and\n"
                                         "repair it with patch_unit: fix the `???` spots and the first divergence first, then re-check.\n```c\n" + total + "\n```")
                            shown_total = True
                    except Exception:
                        shown_total = False
                sk = None if shown_total else _lift.skeleton(project, module, symbol)
                if sk and "NOT LIFTED" in sk:
                    parts.append("\n## Mechanical skeleton (unverified): what the lifter recovered before it gave up\n"
                                 "Declarations, struct layouts, call prototypes with argument shapes, locals and the leading\n"
                                 "statements are taken from the retail code; the `NOT LIFTED` marker says where it stopped.\n"
                                 "Keep its declarations and layouts, write the rest of the body from the disassembly.\n```c\n" + sk + "\n```")
        except Exception:
            pass

    if IDIOMS.exists():
        parts.append("\n## MWCC idioms\n" + IDIOMS.read_text().strip())
    if RULES.exists():
        rules = RULES.read_text()
        parts.append("\n## Rules (excerpt)\n" + rules[: 1800].strip())

    text = "\n".join(parts)
    # crude token cap: ~4 chars per token
    limit = budget_tokens * 4
    if len(text) > limit:
        text = text[:limit] + "\n\n[context truncated to budget]"
    return text
