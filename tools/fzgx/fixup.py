"""Deterministic last-resort repairs of a plateaued body, cheap enough to run inside an
agent's session before it releases (seconds, not minutes).

The object diff says what kind of difference is left (stuck.classify_rows); each kind has a
small, enumerable search over the source that the oracle verifies:

  signedness / sign-extension rows   flip the signedness or width of one integer declaration
  (cmpw/cmplw, extsh, extsb, clrlwi,   at a time (params, locals, block-private struct fields)
   wrong int-to-double constant)

Every candidate is one compile plus one objdiff (~0.4 s). The first body that matches wins;
otherwise the best percentage seen is reported, never applied.
"""

from __future__ import annotations

import re
import time
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from . import oracle, stuck
from .project import STATE_DIR, Project

BRANCH_INV = {("beq", "bne"), ("bne", "beq"), ("blt", "bge"), ("bge", "blt"), ("bgt", "ble"), ("ble", "bgt")}
FLOAT_PAIRS = {"fsubs", "fsub", "fadds", "fadd", "fmuls", "fmul", "fdivs", "fdiv", "fmadds", "fmadd", "fmsubs", "fmsub", "frsp"}

INT_TYPES = ["s8", "u8", "s16", "u16", "s32", "u32", "int", "unsigned int", "unsigned", "char", "unsigned char",
             "short", "unsigned short", "long", "unsigned long", "signed char"]
FLIP = {"s8": "u8", "u8": "s8", "s16": "u16", "u16": "s16", "s32": "u32", "u32": "s32",
        "int": "u32", "unsigned int": "s32", "unsigned": "s32", "char": "u8", "unsigned char": "s8", "signed char": "u8",
        "short": "u16", "unsigned short": "s16", "long": "u32", "unsigned long": "s32"}
WIDEN = {"s8": ["s16", "s32"], "u8": ["u16", "u32"], "s16": ["s8", "s32"], "u16": ["u8", "u32"],
         "s32": ["s16", "s8"], "u32": ["u16", "u8"], "int": ["s16", "s8"], "char": ["s16", "s32"], "short": ["s8", "s32"]}
TYPE_RE = "|".join(re.escape(t) for t in sorted(INT_TYPES, key=len, reverse=True))
# a declaration: type, then one or more declarators (pointers excluded: their signedness never matters)
DECL_RE = re.compile(rf"(?<![\w.>])(?:const\s+)?({TYPE_RE})\s+(?!\*)([A-Za-z_]\w*(?:\s*\[[^\]]*\])?)(?=\s*[;,=)\[])")


def _kinds(res: oracle.CheckResult) -> Dict[str, int]:
    lrows, rrows = getattr(res, "_rows", ([], []))
    return stuck.classify_rows(lrows, rrows)


def _wants_type_flip(counts: Dict[str, int], diffs: List[Tuple[str, str]]) -> bool:
    if any(k.startswith("op:cmp") for k in counts) or counts.get("ins:ext"):
        return True
    text = " ".join(t + " " + o for t, o in diffs)
    return bool(re.search(r"\b(extsh|extsb|clrlwi|cmplw|cmpw|cmplwi|cmpwi|rlwinm)\b", text)) or "@" in text


def _decl_sites(body: str, fn_span: Tuple[int, int]) -> List[Tuple[int, int, str, str]]:
    """(start, end, type, name) of integer declarations in the function and in structs above it."""
    out = []
    for m in DECL_RE.finditer(body):
        if m.start() > fn_span[1]:
            break
        typ, name = m.group(1), m.group(2).split("[")[0].strip()
        # must be used inside the function to matter
        if re.search(rf"\b{re.escape(name)}\b", body[fn_span[0]:fn_span[1]]):
            out.append((m.start(1), m.end(1), typ, name))
    return out


def _function_span(text: str, name: str) -> Optional[Tuple[int, int]]:
    m = re.search(rf"\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{", text)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return m.start(), i + 1
        i += 1
    return None


def _tu_of(p: Project, sym) -> Optional[str]:
    """The TU file that holds this function per tus.json, carved or not."""
    try:
        for t in p.tu_map(sym.module).values() if isinstance(p.tu_map(sym.module), dict) else []:
            pass
    except Exception:
        pass
    import json
    path = p.module_config_dir(sym.module) / "tus.json"
    if not path.exists():
        return None
    try:
        d = json.loads(path.read_text())
    except ValueError:
        return None
    for t in d.get("tus", []):
        if sym.name in t.get("functions", []):
            return f"{p.module_src_prefix(sym.module)}/{t['file']}"
    return None


def try_fix(p: Project, symbol: str, body: str, budget_s: float = 30.0, max_candidates: int = 80, _depth: int = 0,
            base: Optional[oracle.CheckResult] = None) -> Dict[str, object]:
    """Search the cheap repairs; returns {"matched": bool, "body": text or None, "tried": n, "best": %, "secs": s}.
    `base`: the body's check result when the caller already has it (saves one compile)."""
    t0 = time.time()
    sym = p.resolve(symbol)
    key = p.key(sym)
    scratch = STATE_DIR / "fixup" / (key.replace(":", "__") + ".c")
    scratch.parent.mkdir(parents=True, exist_ok=True)

    def check(text: str) -> oracle.CheckResult:
        scratch.write_text(text)
        return oracle.check(p, symbol, 0, source=scratch)

    if base is None:
        base = check(body)
    out: Dict[str, object] = {"matched": False, "body": None, "tried": 0, "best": base.percent if base.ok else 0.0,
                              "base": base.percent if base.ok else 0.0, "secs": 0.0, "kinds": {}}
    if not base.ok:
        out["error"] = base.error[-300:]
        return out
    if base.matched or base.matched_pool:
        out.update(matched=True, body=body)
        return out
    counts = _kinds(base)
    out["kinds"] = {k: v for k, v in counts.items()}
    # first, a fraction of a second: the register-allocation search (declaration order, scope,
    # initializer splits) on a body that is already close; the type families come after
    if base.percent >= 85.0 and _depth == 0:
        from . import regalloc
        ra = regalloc.search(p, symbol, body, budget_s=min(budget_s, 8.0), mw_version=base.mw_version)
        out["regalloc"] = {"tried": ra.get("tried"), "best": ra.get("best"), "secs": ra.get("secs")}
        if ra.get("matched") and ra.get("body"):
            out.update(matched=True, body=ra["body"], tried=ra.get("tried", 0), best=100.0,
                       label=f"regalloc {ra.get('stage')}: {ra.get('label')}", secs=round(time.time() - t0, 2))
            return out
    lrows, rrows = base._rows
    diffs = [(stuck._fmt(a), stuck._fmt(b)) for a, b in zip(lrows, rrows) if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE"]
    span = _function_span(body, sym.name)
    candidates: List[Tuple[str, str]] = []
    fam_marks: List[Tuple[int, str]] = []
    fam_marks.append((len(candidates), "type"))
    if span and _wants_type_flip(counts, diffs):
        sites = _decl_sites(body, span)
        for s, e, typ, name in sites:
            alts = [FLIP[typ]] if typ in FLIP else []
            if counts.get("ins:ext") or "@" in " ".join(t + o for t, o in diffs):
                alts += WIDEN.get(typ, [])
            for alt in alts:
                candidates.append((f"{name}:{typ}->{alt}", body[:s] + alt + body[e:]))
    fam_marks.append((len(candidates), "decl"))
    # declaration variants: when a symbol this body declares is declared differently by another
    # block of the same TU (a contested prototype or extern type), each sibling variant is a
    # candidate: a matched neighbour usually already found the spelling the compiler wants
    tu_src = None
    try:
        rec = p.unit_record(p.unit_of(sym)) if p.unit_of(sym) else None
        tu_src = rec.get("tu") if rec else None
        if tu_src is None:
            tu_src = next((t for t in [_tu_of(p, sym)] if t), None)
    except Exception:
        tu_src = None
    if tu_src:
        from . import tufile, tutidy
        try:
            tf = tufile.load(p, tu_src)
        except Exception:
            tf = None
        if tf is not None:
            mine = {}
            for ln in body.splitlines():
                if tutidy.DECL_LINE_RE.match(ln):
                    n = tutidy._decl_name(ln)
                    if n:
                        mine.setdefault(n, ln.strip())
            variants: Dict[str, List[str]] = {}
            for b in tf.blocks:
                if b.name == sym.name:
                    continue
                for ln in b.body.splitlines():
                    if tutidy.DECL_LINE_RE.match(ln):
                        n = tutidy._decl_name(ln)
                        if n in mine and ln.strip() != mine[n] and ln.strip() not in variants.setdefault(n, []):
                            variants[n].append(ln.strip())
            for ln in tf.prologue.splitlines():
                if tutidy.DECL_LINE_RE.match(ln):
                    n = tutidy._decl_name(ln)
                    if n in mine and ln.strip() != mine[n] and ln.strip() not in variants.setdefault(n, []):
                        variants[n].append(ln.strip())
            for n, alts in variants.items():
                for alt in alts[:4]:
                    candidates.append((f"{n}: {mine[n]} -> {alt}", body.replace(mine[n], alt, 1)))
    fam_marks.append((len(candidates), "sym"))
    # wrong callee / wrong data symbol: the same instruction with a different relocation target.
    # The retail name is known; the body names ours verbatim, so the substitution is exact.
    subs: Dict[str, str] = {}
    for t, o in diffs:
        if not t or not o or t.split()[0] != o.split()[0]:
            continue
        mt = re.findall(r"\b([A-Za-z_]\w*)(?=@|$|\b)", re.sub(r"^\S+\s+", "", t))
        mo = re.findall(r"\b([A-Za-z_]\w*)(?=@|$|\b)", re.sub(r"^\S+\s+", "", o))
        tn = [x for x in mt if not re.fullmatch(r"[rf]\d+|cr\d|lt|gt|eq|so|ha|l|sda21", x)]
        on = [x for x in mo if not re.fullmatch(r"[rf]\d+|cr\d|lt|gt|eq|so|ha|l|sda21", x)]
        if len(tn) == 1 and len(on) == 1 and tn[0] != on[0] and not on[0].startswith("@"):
            if re.sub(r"\b" + re.escape(on[0]) + r"\b", tn[0], o) == t:
                subs.setdefault(on[0], tn[0])
    # a hardware register block under an invented name: retail's `lis rX, 0xcc00` / `addi rX, rX,
    # 0xNNNN` literal pair against ours `SYM@ha` / `SYM@l` names the address; the link script's
    # canonical symbol for it (config/<v>/ldscript.tpl) is what the oracle accepts
    abs_by_addr: Dict[int, str] = {}
    for name_, addr_ in oracle.abs_symbols().items():
        abs_by_addr.setdefault(addr_, name_)
    for (t1, o1), (t2, o2) in zip(diffs, diffs[1:]):
        m1 = re.match(r"lis r\d+, (0x[0-9a-f]+)$", t1 or ""); n1 = re.match(r"lis r\d+, (\w+)@ha$", o1 or "")
        m2 = re.match(r"(addi|ori) r\d+, r\d+, (-?0x[0-9a-f]+|-?\d+)$", t2 or ""); n2 = re.match(r"(?:addi|ori) r\d+, r\d+, (\w+)@l$", o2 or "")
        if not (m1 and n1 and m2 and n2 and n1.group(1) == n2.group(1)):
            continue
        hi, lo = int(m1.group(1), 16), int(m2.group(2), 0)
        addr = ((hi << 16) + lo) & 0xFFFFFFFF if m2.group(1) == "addi" else (hi << 16) | lo
        canon = abs_by_addr.get(addr)
        if canon and canon != n1.group(1):
            subs.setdefault(n1.group(1), canon)
    for ours, retail in subs.items():
        if re.search(rf"\b{re.escape(ours)}\b", body) and not re.search(rf"\b{re.escape(retail)}\b", body):
            candidates.append((f"symbol {ours} -> {retail}", re.sub(rf"\b{re.escape(ours)}\b", retail, body)))
    if len(subs) > 1:
        text = body
        for ours, retail in subs.items():
            text = re.sub(rf"\b{re.escape(ours)}\b", retail, text)
        candidates.append(("all symbol substitutions", text))
    fam_marks.append((len(candidates), "float"))
    # float vs double: fsubs/fsub, frsp rows come from f32/f64 declarations and literal suffixes
    if any((t.split()[0] if t else "") in FLOAT_PAIRS or (o.split()[0] if o else "") in FLOAT_PAIRS or "frsp" in (t + o) for t, o in diffs):
        for a, b in (("f64", "f32"), ("f32", "f64"), ("double", "float"), ("float", "double")):
            if re.search(rf"\b{a}\b", body):
                candidates.append((f"all {a}->{b}", re.sub(rf"\b{a}\b", b, body)))
                for m in list(re.finditer(rf"\b{a}\b", body))[:12]:
                    candidates.append((f"{a}->{b} at {m.start()}", body[:m.start()] + b + body[m.end():]))
        lits = list(re.finditer(r"(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?)(?![\w.])", body))
        if lits:
            candidates.append(("float literals get f", re.sub(r"(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?)(?![\w.])", r"\1f", body)))
        litf = list(re.finditer(r"(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?)f\b", body))
        if litf:
            candidates.append(("float literals lose f", re.sub(r"(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?)f\b", r"\1", body)))
    fam_marks.append((len(candidates), "params"))
    # unused leading parameters: retail keeps r3..r5 alive (they were parameters) and uses r6 for a
    # temporary where we used r3; adding parameters the body ignores reproduces that
    if span:
        regs_t = set(re.findall(r"\br(\d+)\b", " ".join(t for t, o in diffs))); regs_o = set(re.findall(r"\br(\d+)\b", " ".join(o for t, o in diffs)))
        hi_t = [int(x) for x in regs_t if 3 <= int(x) <= 10]; lo_o = [int(x) for x in regs_o if 3 <= int(x) <= 10]
        m = re.search(rf"\b{re.escape(sym.name)}\s*\(([^)]*)\)\s*\{{", body)
        if m and hi_t and lo_o and max(hi_t) > max(lo_o):
            cur = m.group(1).strip()
            n_cur = 0 if cur in ("", "void") else cur.count(",") + 1
            for extra in range(1, 4):
                pads = ", ".join(f"u32 unused{n_cur + i}" for i in range(extra))
                newp = pads if cur in ("", "void") else cur + ", " + pads
                candidates.append((f"+{extra} unused parameter(s)", body[:m.start(1)] + newp + body[m.end(1):]))
    fam_marks.append((len(candidates), "struct"))
    # target-driven immediates: a row where only an immediate differs names ours and retail's
    # value; the C literal that produced ours (as decimal, hex, or a struct stride) is replaced
    imm_pairs = []
    for t, o in diffs:
        if not t or not o or t.split()[0] != o.split()[0]:
            continue
        ti = re.findall(r"(?<![\w(])(-?0x[0-9a-f]+|-?\d+)(?![\w(])", t); oi = re.findall(r"(?<![\w(])(-?0x[0-9a-f]+|-?\d+)(?![\w(])", o)
        if len(ti) == len(oi) and re.sub(r"\b[rf]\d+\b", "R", re.sub(r"(-?0x[0-9a-f]+|-?\d+)", "#", t)) == re.sub(r"\b[rf]\d+\b", "R", re.sub(r"(-?0x[0-9a-f]+|-?\d+)", "#", o)):
            for a, b in zip(ti, oi):
                if a != b:
                    imm_pairs.append((int(b, 0), int(a, 0), t.split()[0]))
    seen_imm = set()
    for ours_v, retail_v, mn in imm_pairs:
        if (ours_v, retail_v) in seen_imm:
            continue
        seen_imm.add((ours_v, retail_v))
        forms = {str(ours_v), f"0x{ours_v:X}", f"0x{ours_v:x}"}
        if ours_v < 0:
            forms |= {str(ours_v & 0xFFFF), f"0x{ours_v & 0xFFFF:X}"}
        for form in forms:
            for m in list(re.finditer(rf"(?<![\w.]){re.escape(form)}(?![\w.])", body))[:6]:
                rep = f"0x{retail_v:X}" if form.startswith("0x") else str(retail_v)
                candidates.append((f"imm {form} -> {rep} ({mn})", body[:m.start()] + rep + body[m.end():]))
        if mn.rstrip(".") in ("lis", "addis", "subis", "oris", "xoris", "andis"):
            # a high-half immediate: the C literal is a 32-bit constant whose upper half (with the
            # low half's sign carried for addis/subis) is ours; retail's literal differs by the
            # delta in the upper half, e.g. `== 0x1FFFF` (subis 1) where retail has 0x3FFFF (subis 3)
            delta = (retail_v - ours_v) << 16
            for lm in list(re.finditer(r"(?<![\w.])(0[xX][0-9A-Fa-f]+|\d+)(?![\w.])", body))[:64]:
                L = int(lm.group(1), 0)
                if L < 0x10000 or not ((L >> 16) & 0xFFFF == ours_v & 0xFFFF or ((L + 0x8000) >> 16) & 0xFFFF == ours_v & 0xFFFF):
                    continue
                nv = L + delta
                if nv < 0:
                    continue
                rep = f"0x{nv:X}" if lm.group(1).lower().startswith("0x") else str(nv)
                candidates.append((f"imm high half {lm.group(1)} -> {rep} ({mn})", body[:lm.start()] + rep + body[lm.end():]))
        if mn == "mulli" and retail_v > ours_v:
            # a stride: the struct the loop indexes is smaller than retail's; pad its tail
            for sm in re.finditer(r"((?:typedef\s+)?struct\s+\w*\s*\{)([^}]*)(\})", body):
                candidates.append((f"struct tail padding +{retail_v - ours_v} (stride {ours_v}->{retail_v})",
                                   body[:sm.start(2)] + sm.group(2).rstrip() + f"\n    u8 pad_tail[{retail_v - ours_v}];\n" + body[sm.end(2):]))
    # a compare of the wrong signedness where the operand is a header field: cast at the compare
    if any(t and o and (t.split()[0], o.split()[0]) in (("cmpwi", "cmplwi"), ("cmplwi", "cmpwi"), ("cmpw", "cmplw"), ("cmplw", "cmpw")) for t, o in diffs):
        want_signed = any(t and t.split()[0] in ("cmpwi", "cmpw") for t, o in diffs)
        cast = "(s32)" if want_signed else "(u32)"
        for m in list(re.finditer(r"\bif \(([A-Za-z_][\w>.\-\[\]]*) (==|!=|<|>|<=|>=) ", body))[:12]:
            candidates.append((f"cast {cast} at compare of {m.group(1)}", body[:m.start(1)] + cast + m.group(1) + body[m.end(1):]))
    # struct layout: every field offset off by the same delta means padding is missing or extra
    # at the front of the block-private struct; two deltas mean two fields are in the wrong order
    deltas = set()
    for t, o in diffs:
        if not t or not o or t.split()[0] != o.split()[0]:
            continue
        mt = re.search(r"(-?0x[0-9a-f]+|-?\d+)\((r\d+)\)", t); mo = re.search(r"(-?0x[0-9a-f]+|-?\d+)\((r\d+)\)", o)
        if mt and mo and mt.group(2) == mo.group(2) and mt.group(2) != "r1" and mt.group(1) != mo.group(1):
            deltas.add(int(mt.group(1), 0) - int(mo.group(1), 0))
    struct_spans = [(m.start(), m.end(), m.group(1)) for m in re.finditer(r"(?:typedef\s+)?struct\s+\w*\s*\{([^}]*)\}", body)]
    if len(deltas) == 1 and struct_spans:
        delta = next(iter(deltas))
        for s0, e0, inner in struct_spans:
            if delta > 0:
                new_inner = f"\n    u8 _pad_pre[0x{delta:X}];" + inner
                candidates.append((f"struct +{delta} front padding", body[:s0] + body[s0:e0].replace(inner, new_inner, 1) + body[e0:]))
            else:
                m = re.match(r"\s*u8\s+(\w+)\[(0x[0-9A-Fa-f]+|\d+)\];", inner)
                if m and int(m.group(2), 0) + delta >= 0:
                    n = int(m.group(2), 0) + delta
                    rep = "" if n == 0 else f"\n    u8 {m.group(1)}[0x{n:X}];"
                    candidates.append((f"struct {delta} front padding", body[:s0] + body[s0:e0].replace(inner, re.sub(r"^\s*u8\s+\w+\[[^\]]+\];", rep, inner, count=1), 1) + body[e0:]))
    if len(deltas) >= 2 and struct_spans:
        for s0, e0, inner in struct_spans:
            lines = inner.split("\n")
            fl = [i for i, ln in enumerate(lines) if re.match(r"\s*[A-Za-z_][\w ]*\*?\s*\w+(\[[^\]]*\])?;", ln)]
            for a, b in zip(fl, fl[1:]):
                sw = list(lines); sw[a], sw[b] = sw[b], sw[a]
                candidates.append((f"swap fields {lines[a].strip()} <-> {lines[b].strip()}", body[:s0] + body[s0:e0].replace(inner, "\n".join(sw), 1) + body[e0:]))
                if len(candidates) > max_candidates:
                    break
    fam_marks.append((len(candidates), "branch"))
    # two adjacent independent statements in the other order (the lab closed a function this way)
    if span:
        stmts_ = [(m.start(), m.end(), m.group(0)) for m in re.finditer(r"^[ \t]*[^\n{}]+;\n", body[span[0]:span[1]], re.M)]
        for (s1, e1, t1), (s2, e2, t2) in list(zip(stmts_, stmts_[1:]))[:40]:
            if e1 != s2:
                continue
            ids1 = set(re.findall(r"[A-Za-z_]\w*", t1)); ids2 = set(re.findall(r"[A-Za-z_]\w*", t2))
            if ids1 & ids2 or ("(" in t1 and "(" in t2):
                continue
            candidates.append((f"swap `{t1.strip()[:24]}` / `{t2.strip()[:24]}`", body[:span[0] + s1] + t2 + t1 + body[span[0] + e2:]))
    # inverted branch: negate one `if` condition and swap its then/else blocks
    if any(t and o and (t.split()[0], o.split()[0]) in BRANCH_INV for t, o in diffs):
        for m in list(re.finditer(r"\bif\s*\(", body))[:16]:
            depth, i = 1, m.end()
            while i < len(body) and depth:
                depth += body[i] == "("; depth -= body[i] == ")"; i += 1
            cond = body[m.end():i - 1]
            j = i
            while j < len(body) and body[j] in " \t\r\n": j += 1
            if j >= len(body) or body[j] != "{":
                continue
            d2, k = 1, j + 1
            while k < len(body) and d2:
                d2 += body[k] == "{"; d2 -= body[k] == "}"; k += 1
            then_blk = body[j:k]
            rest = body[k:]
            me = re.match(r"\s*else\s*(\{)", rest)
            if me:
                d3, e = 1, k + me.end()
                while e < len(body) and d3:
                    d3 += body[e] == "{"; d3 -= body[e] == "}"; e += 1
                else_blk = body[k + me.end() - 1:e]
                neg = f"!({cond})" if not re.fullmatch(r"\s*!\((.*)\)\s*", cond) else re.fullmatch(r"\s*!\((.*)\)\s*", cond).group(1)
                text = body[:m.end()] + neg + ") " + else_blk + " else " + then_blk + body[e:]
                candidates.append((f"invert if at {m.start()}", text))
            else:
                # `if (c) { return A; } ... return B;` is equivalent to `if (!c) { rest } return A;` only in
                # simple shapes; the cheap variant that changes codegen: swap == / != in the condition
                if "==" in cond or "!=" in cond:
                    c2 = cond.replace("==", "\0").replace("!=", "==").replace("\0", "!=")
                    candidates.append((f"flip ==/!= at {m.start()}", body[:m.end()] + c2 + body[i - 1:]))
    def family_of(idx: int) -> str:
        f = "misc"
        for k, fam in fam_marks:
            if k <= idx:
                f = fam
        return f
    # the rows each family is meant to repair, by the kind classify_rows gives the base diff
    FAMILY_KINDS = {"type": ("ins:ext", "ins:cmp", "op:cmp", "op:ext", "op:rlwinm", "op:extsh", "op:extsb"),
                    "float": ("ins:float", "op:f"), "sym": ("reloc",), "struct": ("imm",), "branch": ("ins:branch", "op:b"),
                    "params": ("regalloc",), "decl": (), "misc": ()}
    kinds_rows = stuck.row_kinds(lrows, rrows)
    def taddr(row):
        ins_ = row.get("instruction") or {}
        return ins_.get("address")
    # rows are addressed by word index into the retail function (objdiff rows carry the address)
    def _addr(a):
        if a is None:
            return None
        return int(a, 16) if isinstance(a, str) else int(a)
    fn_addr = next((_addr(taddr(l)) for l in lrows if taddr(l) is not None), None)
    def tidx(row):
        a = _addr(taddr(row))
        return None if a is None or fn_addr is None else (a - fn_addr) // 4
    base_diff = {tidx(l) for l, k in zip(lrows, kinds_rows) if k is not None and tidx(l) is not None}
    base_extra = sum(1 for l, k in zip(lrows, kinds_rows) if k is not None and taddr(l) is None)
    def targets(fam: str):
        pats = FAMILY_KINDS.get(fam, ())
        if not pats:
            return set(base_diff)
        return {tidx(l) for l, k in zip(lrows, kinds_rows) if k and tidx(l) is not None and any(k.startswith(pp) for pp in pats)}

    import difflib
    def spans_of(text: str):
        sm = difflib.SequenceMatcher(None, body, text, autojunk=False)
        return [(i1, i2, text[j1:j2]) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal"]
    def compose(edit_lists):
        allspans = sorted((sp for e in edit_lists for sp in e), key=lambda x: x[0])
        for a, b in zip(allspans, allspans[1:]):
            if b[0] < a[1]:
                return None  # overlapping: not composable
        t = body
        for s0, e0, rep in reversed(allspans):
            t = t[:s0] + rep + t[e0:]
        return t

    target = p.target_object_for(sym)
    tw = oracle.words(target, sym.name) if target else None
    bdir = STATE_DIR / "fixup" / "batch" / key.replace(":", "__")
    bdir.mkdir(parents=True, exist_ok=True)

    def evaluate(texts: List[str]):
        """Batch compile, then per candidate: (score %, rows fixed, rows broken, extra rows)."""
        for old in bdir.glob("*.c"):
            old.unlink()
        srcs = []
        for i_, t_ in enumerate(texts):
            f = bdir / f"c{i_}.c"; f.write_text(t_); srcs.append(f)
        objs = oracle.compile_many(p, sym.module, srcs, bdir / "obj", base.mw_version, getattr(base, "extra_cflags", None)) if target and tw else {}
        res = []
        for i_, t_ in enumerate(texts):
            o = objs.get(srcs[i_])
            ow = oracle.words(o, sym.name) if o else None
            if not ow:
                res.append(None); continue
            pct, bad = oracle.word_score(tw, ow)
            now_diff = set(bad)
            extra = max(0, len(ow) - len(tw))
            fixed = base_diff - now_diff
            broken = now_diff - base_diff
            res.append((pct, fixed, broken, extra))
        return res

    best_text, best_pct = None, out["best"]
    cand = candidates[:max_candidates]
    if cand and target and time.time() - t0 < budget_s:
        singles = evaluate([t_ for _, t_ in cand])
        out["tried"] = len(cand)
        keepers = []
        for i_, ((label, text), r_) in enumerate(zip(cand, singles)):
            if r_ is None:
                continue
            pct, fixed, broken, extra = r_
            if pct >= 100.0:
                best_text, best_pct = text, pct; out["label"] = label; break
            if pct > best_pct:
                best_pct, best_text = pct, text; out["best_label"] = label
            own = fixed & targets(family_of(i_))
            # a keeper repairs rows of its own kind without breaking any row that was right
            if own and not broken and extra <= base_extra:
                keepers.append((len(own), i_, label, spans_of(text)))
        if best_pct < 100.0 and keepers:
            keepers.sort(key=lambda x: -x[0])
            # 1. the composition of every keeper (disjoint edits): the fixpoint of the single repairs
            # 2. every pair among the top keepers, for the cases where two edits only pay together
            combos = []
            allk = compose([k[3] for k in keepers])
            if allk is not None and len(keepers) > 1:
                combos.append(("all keepers: " + " + ".join(k[2] for k in keepers[:6]), allk))
            top = keepers[:12]
            for x in range(len(top)):
                for y in range(x + 1, len(top)):
                    t_ = compose([top[x][3], top[y][3]])
                    if t_ is not None:
                        combos.append((f"{top[x][2]} + {top[y][2]}", t_))
            if combos and time.time() - t0 < budget_s:
                res2 = evaluate([t_ for _, t_ in combos])
                out["tried"] += len(combos)
                for (label, text), r_ in zip(combos, res2):
                    if r_ and r_[0] > best_pct:
                        best_pct, best_text = r_[0], text; out["best_label"] = label
                    if r_ and r_[0] >= 100.0:
                        out["label"] = label; break
        if best_text is not None:
            r = check(best_text)  # the full verdict on the winner: pool rows, adjusted percent
            if r.ok:
                pct2 = r.percent_adjusted or r.percent
                out["best"] = max(out["best"], pct2)
                if r.matched or r.matched_pool:
                    out.update(matched=True, body=best_text, label=out.get("label") or out.get("best_label"))
    # a plateau usually has more than one cause: when repairs improved the body without matching,
    # search again from the improved body (bounded by the budget)
    if not out["matched"] and best_text is not None and out["best"] > out["base"] + 0.05 and _depth < 2:
        left = budget_s - (time.time() - t0)
        if left > 2:
            nxt = try_fix(p, symbol, best_text, budget_s=left, max_candidates=max_candidates, _depth=_depth + 1)
            out["tried"] += nxt["tried"]
            if nxt["best"] > out["best"]:
                out["best"] = nxt["best"]; out["best_label"] = f"{out.get('best_label')} + {nxt.get('best_label')}"
            if nxt.get("matched"):
                out.update(matched=True, body=nxt["body"], label=f"{out.get('best_label')} + {nxt.get('label')}")
            out["rounds"] = 1 + nxt.get("rounds", 0)
    out["secs"] = round(time.time() - t0, 1)
    return out
