"""Source transformations and compiler-response algebra for the single fixup engine.

No compilation, search runners, caches, or submission live in this module.
"""
from __future__ import annotations
import difflib
import itertools
import math
import re
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
from . import oracle, mwgraph, mwconstraints

TYPE = (r'(?:(?:register|const|volatile)\s+){0,3}'
        r'(?:(?:unsigned|signed)\s+)?'
        r'(?:(?:long\s+long|long|short)(?:\s+int)?|(?:struct|union|enum)\s+\w+|[A-Za-z_]\w*)'
        r'(?:\s*\*+)?')
DECL_RE = re.compile(r'^\s*(' + TYPE + r')(?:(?<=\*)\s*|\s+)([A-Za-z_]\w*)'
                     r'((?:\[[^\]]*\])*)\s*(?:=\s*([^;]+))?;\s*(?:(?:/\*.*?\*/|//[^\n]*)\s*)?$')


def _function_body_span(body: str, name: str) -> Optional[Tuple[int, int, int]]:
    m = re.search(rf"\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{", body)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    while i < len(body):
        if body[i] == "{":
            depth += 1
        elif body[i] == "}":
            depth -= 1
            if depth == 0:
                return m.start(), m.end(), i
        i += 1
    return None


def _locals(body: str, span) -> List[Tuple[int, int, str, str, str]]:
    """Leading local declarations, one per line: (start, end, type, name, dims). Declarations
    with initializers count (their text keeps the initializer)."""
    out = []
    for m in re.finditer(r"[^\n]*\n", body[span[1]:span[2]]):
        line = m.group(0)
        s0 = span[1] + m.start()
        if not line.strip():
            continue
        dm = DECL_RE.match(line.rstrip("\n"))
        if not dm:
            break
        out.append((s0, s0 + len(line), dm.group(1), dm.group(2), dm.group(3)))
    return out


def _init_of(line: str) -> Optional[str]:
    dm = DECL_RE.match(line.rstrip("\n"))
    return dm.group(4).strip() if dm and dm.group(4) else None


def _order_ok(locs, lines: List[str], order: Tuple[int, ...]) -> bool:
    """An initializer may only name locals declared before it."""
    placed = set()
    for i in order:
        init = _init_of(lines[i])
        if init and any(re.search(rf"\b{re.escape(locs[j][3])}\b", init) for j in range(len(locs)) if j not in placed and j != i):
            return False
        placed.add(i)
    return True


def split_inits(body: str, name: str) -> List[Tuple[str, str]]:
    """`T x = e;` -> `T x;` ... `x = e;` as the first statement (all at once, and one at a
    time); the reverse for a local whose first statement is a plain assignment."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    if not locs:
        return out
    lines = [body[s:e] for s, e, *_ in locs]
    inits = [(i, _init_of(l)) for i, l in enumerate(lines)]
    with_init = [i for i, e in inits if e]
    indent = re.match(r"\s*", lines[0]).group(0)

    def rebuild(split_idx: List[int]) -> str:
        decls, assigns = [], []
        for i, l in enumerate(lines):
            if i in split_idx:
                dm = DECL_RE.match(l.rstrip("\n"))
                decls.append(f"{indent}{dm.group(1)} {dm.group(2)}{dm.group(3)};\n")
                assigns.append(f"{indent}{dm.group(2)} = {dm.group(4).strip()};\n")
            else:
                decls.append(l)
        return body[:locs[0][0]] + "".join(decls) + "".join(assigns) + body[locs[-1][1]:]

    if with_init:
        out.append(("split all inits", rebuild(with_init)))
        if len(with_init) > 1:
            for i in with_init:
                out.append((f"split init {locs[i][3]}", rebuild([i])))
    # the reverse: the first statements `x = e;` for locals without initializers, folded in
    rest = body[locs[-1][1]:span[2]]
    text = body
    folded = 0
    for i, l in enumerate(lines):
        if _init_of(l):
            continue
        m = re.match(r"\s*\n?(\s*)" + re.escape(locs[i][3]) + r" = ([^;]+);\n", rest)
        if not m:
            break
        dm = DECL_RE.match(l.rstrip("\n"))
        new_line = f"{indent}{dm.group(1)} {dm.group(2)}{dm.group(3)} = {m.group(2)};\n"
        text = text.replace(l, new_line, 1)
        text = text.replace(m.group(0), "\n" if m.group(0).startswith("\n") else "", 1)
        rest = rest[m.end():]
        folded += 1
        out.append((f"fold {folded} inits", text))
    return out


def hoists(body: str, name: str) -> List[Tuple[str, str]]:
    """A local declared in an inner block moved to the top of the function."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    top = locs[-1][1] if locs else span[1] + (1 if body[span[1]] == "\n" else 0)
    names = {l[3] for l in locs}
    for m in re.finditer(r"^([ \t]+)(?:register\s+)?(?:const\s+)?((?:struct\s+\w+\s*\*?|[A-Za-z_]\w*(?:\s*\*)?)\s+([A-Za-z_]\w*)((?:\[[^\]]*\])*))\s*(?:=\s*([^;]+))?;[ \t]*\n", body[top:span[2]], re.M):
        nm = m.group(3)
        if nm in names or nm == name:
            continue
        indent = re.match(r"\s*", body[locs[0][0]:locs[0][1]]).group(0) if locs else "    "
        s0, e0 = top + m.start(), top + m.end()
        decl = f"{indent}{m.group(2)};\n"
        repl = f"{m.group(1)}{nm} = {m.group(5).strip()};\n" if m.group(5) else ""
        text = body[:s0] + repl + body[e0:]
        text = text[:top] + decl + text[top:]
        out.append((f"hoist {nm}", text))
    return out


def through_local(body: str, name: str) -> List[Tuple[str, str]]:
    """`x = A op B;` where A is a load -> `x = A; x = x op B;` (the loaded value is the local's
    own register), and `if (p->f OP k)` -> `t = p->f; if (t OP k)` with a fresh local."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    inner = body[span[1]:span[2]]
    for m in re.finditer(r"^(\s*)([A-Za-z_]\w*) = ([A-Za-z_][\w>.\-\[\]\(\)\* ]*?) (>>|<<|\+|-|&|\||\*) ([^;]+);\n", inner, re.M):
        ind, x, a, op, b = m.groups()
        if x in a or "(" in a and not a.startswith("*("):
            continue
        s0, e0 = span[1] + m.start(), span[1] + m.end()
        out.append((f"through {x}", body[:s0] + f"{ind}{x} = {a};\n{ind}{x} = {x} {op} {b};\n" + body[e0:]))
    if locs:
        top = locs[-1][1]
        indent = re.match(r"\s*", body[locs[0][0]:locs[0][1]]).group(0)
        k = 0
        for m in re.finditer(r"^(\s*)(if|while) \(\(?([A-Za-z_]\w*(?:->|\.)\w+) (==|!=|<|>|<=|>=|&)", inner, re.M):
            if span[1] + m.start() < top:
                continue
            k += 1
            t = f"tmp_ra{k}"
            s0 = span[1] + m.start()
            expr = m.group(3)
            text = body[:s0] + f"{m.group(1)}{t} = {expr};\n" + body[s0:s0 + m.start(3) - m.start()] + t + body[s0 + m.end(3) - m.start():]
            text = text[:top] + f"{indent}s32 {t};\n" + text[top:]
            out.append((f"temp for {expr}", text))
    return out


def rewrites(body: str, name: str) -> List[Tuple[str, str]]:
    """Every single second-stage rewrite of a body."""
    out: List[Tuple[str, str]] = []
    for fn in (scope_moves, split_inits, hoists, through_local, return_values):
        try:
            out += fn(body, name)
        except Exception:
            continue
    return out


def return_values(body: str, name: str) -> List[Tuple[str, str]]:
    """Recover an omitted result when a void draft leaves the value outside r3.

    Tail calls forward their own result; preserving a local across the call would
    create a different live range and hide the actual return convention.
    """
    signature = re.search(rf'\bvoid\s+{re.escape(name)}\s*\(', body)
    span = _function_body_span(body, name)
    if not signature or not span:
        return []
    locals_ = _locals(body, span)
    values = [nm for _, _, ty, nm, dims in locals_ if not dims and
              (ty.strip() in ('u32', 's32', 'int', 'unsigned', 'u16', 's16', 'u8', 's8') or '*' in ty)]
    out = []
    for value in values:
        inner = body[span[1]:span[2]]
        inner = re.sub(r'\breturn\s*;', f'return (u32){value};', inner)
        inner += f'    return (u32){value};\n'
        text = body[:span[1]] + inner + body[span[2]:]
        text = text[:signature.start()] + 'u32' + text[signature.start() + 4:]
        out.append((f'return {value}', text))
        calls = set()
        def forward(match):
            callee = match[2]
            if not re.search(rf'\bextern\s+void\s+{re.escape(callee)}\s*\(', text):
                return match[0]
            calls.add(callee)
            return f'{match[1]}return {callee}({match[3]});'
        inner = re.sub(r'(?m)^([ \t]*)(\w+)\(([^;\n]*)\);(?=\s*})', forward, inner)
        if calls:
            text = body[:span[1]] + inner + body[span[2]:]
            text = text[:signature.start()] + 'u32' + text[signature.start() + 4:]
            for callee in calls:
                text = re.sub(rf'\bextern\s+void(?=\s+{re.escape(callee)}\s*\()', 'extern u32', text)
            out.append((f'return {value}, forward tail calls', text))
    return out


def reorder(body: str, locs, order: Tuple[int, ...]) -> str:
    lines = [body[s:e] for s, e, *_ in locs]
    return body[:locs[0][0]] + "".join(lines[i] for i in order) + body[locs[-1][1]:]


def scope_moves(body: str, name: str) -> List[Tuple[str, str]]:
    """Each local re-declared in an inner block around its uses; each local split off
    into its own declaration block after a blank line (a second declaration group)."""
    out: List[Tuple[str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    if not locs:
        return out
    inner = body[span[1]:span[2]]
    for s, e, typ, nm, dims in locs:
        uses = [span[1] + m.start() for m in re.finditer(rf"\b{re.escape(nm)}\b", inner)]
        uses = [u for u in uses if u >= locs[-1][1]]
        if not uses:
            continue
        line_start = body.rfind("\n", 0, uses[0]) + 1
        line_end = body.find("\n", uses[-1]) + 1
        # only when the use range is a run of whole statements at one nesting depth
        seg = body[line_start:line_end]
        if seg.count("{") != seg.count("}"):
            continue
        decl = body[s:e]
        text = body[:s] + body[e:]
        a, b = line_start - (e - s), line_end - (e - s)
        out.append((f"scope {nm}", text[:a] + "{\n" + decl + text[a:b] + "}\n" + text[b:]))
    return out


def normalise(body: str) -> str:
    """One declarator per line (`u32 a, b;` -> `u32 a;\n u32 b;`), so every family sees every local."""
    lines = []
    for line in body.splitlines(keepends=True):
        # Match only a declaration prefix before splitting declarators. A repeated
        # declaration regex backtracks exponentially on long generated call lines.
        match = re.fullmatch(r'([ \t]+)(struct[ \t]+\w+|[A-Za-z_]\w*)[ \t]+([^;]+);[ \t]*(\n?)', line)
        if match and ',' in match[3]:
            decls = match[3].split(',')
            if all(re.fullmatch(r'\*?\s*[A-Za-z_]\w*(?:\[[^\]]*\])*\s*', decl) for decl in decls):
                lines.append('\n'.join(f'{match[1]}{match[2]} {decl.strip()};' for decl in decls) + match[4])
                continue
        lines.append(line)
    return ''.join(lines)




FLIP = {"s32": "u32", "u32": "s32", "s16": "u16", "u16": "s16", "s8": "u8", "u8": "s8", "f32": "f64", "f64": "f32", "int": "u32"}

def perturbations(body: str, name: str) -> List[Tuple[str, str, str]]:
    """(family, label, text) for every single rewrite."""
    out: List[Tuple[str, str, str]] = []
    span = _function_body_span(body, name)
    if not span:
        return out
    locs = _locals(body, span)
    # 1. declaration order: every permutation of up to 5 locals, else reverse and adjacent swaps
    if len(locs) >= 2:
        lines = [body[s:e] for s, e, *_ in locs]
        blk_s, blk_e = locs[0][0], locs[-1][1]
        perms = list(itertools.permutations(range(len(lines)))) if len(lines) <= 5 else \
            [tuple(reversed(range(len(lines))))] + [tuple(list(range(i)) + [i + 1, i] + list(range(i + 2, len(lines)))) for i in range(len(lines) - 1)]
        for perm in perms:
            if list(perm) == list(range(len(lines))):
                continue
            out.append(("decl-order", "order " + ",".join(locs[i][3] for i in perm), body[:blk_s] + "".join(lines[i] for i in perm) + body[blk_e:]))
    # 2. local types
    for s, e, typ, nm, dims in locs:
        t0 = typ.strip()
        if t0 in FLIP:
            out.append(("local-type", f"{nm}: {t0}->{FLIP[t0]}", body[:s] + body[s:e].replace(t0, FLIP[t0], 1) + body[e:]))
    # 3. inner block scope for a local: declare it where it is first used
    inner = body[span[1]:span[2]]
    for s, e, typ, nm, dims in locs:
        uses = [m.start() for m in re.finditer(rf"\b{re.escape(nm)}\b", inner)]
        uses = [u for u in uses if span[1] + u >= locs[-1][1]]
        if not uses:
            continue
        first = span[1] + uses[0]
        line_start = body.rfind("\n", 0, first) + 1
        last = span[1] + uses[-1]
        line_end = body.find("\n", last) + 1
        decl = body[s:e]
        text = body[:s] + body[e:]
        shift = e - s
        a, b = line_start - shift, line_end - shift
        text = text[:a] + "{\n" + decl + text[a:b] + "}\n" + text[b:]
        out.append(("inner-scope", f"scope {nm}", text))
    # 4. temp inlining: `v = expr;` used once afterwards -> substitute
    for m in re.finditer(r"^(\s*)([A-Za-z_]\w*) = ([^;]+);\n", body[span[1]:span[2]], re.M):
        v, expr = m.group(2), m.group(3)
        rest = body[span[1] + m.end():span[2]]
        uses = list(re.finditer(rf"\b{re.escape(v)}\b", rest))
        if len(uses) == 1 and not re.search(rf"\b{re.escape(v)}\s*=", rest):
            new_rest = rest[:uses[0].start()] + f"({expr})" + rest[uses[0].end():]
            out.append(("inline-temp", f"inline {v}", body[:span[1] + m.start()] + body[span[1] + m.end():span[1] + m.end()] + new_rest.join(["", ""]) if False else body[:span[1] + m.start()] + new_rest + body[span[2]:]))
    # 5. hoist a call argument into a temp right before the call
    for m in re.finditer(r"^(\s*)((?:[A-Za-z_][\w>.\-\[\]]* = )?)([A-Za-z_]\w*)\(([^;]*)\);\n", body[span[1]:span[2]], re.M):
        indent, lhs, callee, args = m.groups()
        parts = [a.strip() for a in re.split(r",(?![^()]*\))", args)] if args.strip() else []
        prototype = re.search(r'\b'+re.escape(callee)+r'\s*\(([^;{}]*)\)\s*;', body[:span[0]])
        parameter_types = []
        if prototype:
            for parameter in prototype[1].split(','):
                parameter = parameter.strip()
                typed = re.fullmatch('('+TYPE+r')(?:\s+\w+)?', parameter)
                parameter_types.append(typed[1] if typed else None)
        for k, a in enumerate(parts):
            known_type = parameter_types[k] if k < len(parameter_types) else None
            if not known_type and re.fullmatch(r"[A-Za-z_]\w*|-?\d+|0x[0-9A-Fa-f]+|&[A-Za-z_]\w*|\d+\.\d*f?", a):
                continue
            tname = f"lab_t{k}"
            while re.search(r'\b'+tname+r'\b',body):
                tname += '_'
            newparts = list(parts); newparts[k] = tname
            stmt = f"{indent}u32 {tname};\n" if False else ""
            text = body[:span[1] + m.start()] + f"{indent}{tname} = {a};\n{indent}{lhs}{callee}({', '.join(newparts)});\n" + body[span[1] + m.end():]
            # The call's conversion belongs in the temporary too. In particular,
            # pointer arguments are not integers and narrow counts truncate here.
            cast = re.match(r'\(('+TYPE+r')\)',a)
            ty = known_type or (cast[1] if cast else None) or ("f32" if re.search(r"\d\.\d|f32|unk_\w*f\b", a) else "u32")
            ins_at = locs[-1][1] if locs else span[1] + 1
            text = text[:ins_at] + f"    {ty} {tname};\n" + text[ins_at:]
            out.append(("hoist-arg", f"hoist arg {k} of {callee}", text))
    # 6. increment forms
    for m in re.finditer(r"^(\s*)(\S[^=\n]*?) = \2 \+ 1;\n", body, re.M):
        out.append(("increment", "x = x + 1 -> x++", body[:m.start()] + f"{m.group(1)}{m.group(2)}++;\n" + body[m.end():]))
    for m in re.finditer(r"^(\s*)(\S[^\n]*?)\+\+;\n", body, re.M):
        out.append(("increment", "x++ -> x = x + 1", body[:m.start()] + f"{m.group(1)}{m.group(2)} = {m.group(2)} + 1;\n" + body[m.end():]))
    # 7. return forms
    for m in re.finditer(r"^(\s*)return ([A-Za-z_]\w*\([^;]*\));\n", body, re.M):
        out.append(("return-form", "return f() -> f(); return", body[:m.start()] + f"{m.group(1)}{m.group(2)};\n{m.group(1)}return;\n" + body[m.end():]))
    # 8. address forms
    for m in re.finditer(r"\(struct (\w+) \*\)&([A-Za-z_]\w*)", body):
        out.append(("address-form", f"drop cast on &{m.group(2)}", body[:m.start()] + f"&{m.group(2)}" + body[m.end():]))
    # 9. compare forms
    for m in re.finditer(r"\(([^()]+?) != 0\)", body):
        out.append(("compare-form", "x != 0 -> x", body[:m.start()] + f"({m.group(1)})" + body[m.end():]))
    for m in re.finditer(r"\(([^()]+?) == 0\)", body):
        out.append(("compare-form", "x == 0 -> !x", body[:m.start()] + f"(!({m.group(1)}))" + body[m.end():]))
    # 11. commute the operands of a commutative binary operator (register assignment follows
    #     operand order)
    for m in re.finditer(r"\(([A-Za-z_][\w>.\-\[\]]*) ([+*&|^]|==|!=) ([A-Za-z_][\w>.\-\[\]]*|-?\d+|0x[0-9A-Fa-f]+)\)", body[span[1]:span[2]]):
        a_, op, b_ = m.groups()
        if a_ == b_:
            continue
        s0 = span[1] + m.start(); e0 = span[1] + m.end()
        out.append(("commute", f"{a_} {op} {b_} -> {b_} {op} {a_}", body[:s0] + f"({b_} {op} {a_})" + body[e0:]))
    # 12. swap two adjacent statements that share no identifier (independent: order is free)
    stmts_ = [(m.start() + span[1], m.end() + span[1], m.group(0)) for m in re.finditer(r"^[ \t]*[^\n{}]+;\n", body[span[1]:span[2]], re.M)]
    for (s1, e1, t1), (s2, e2, t2) in zip(stmts_, stmts_[1:]):
        if e1 != s2:
            continue
        ids1 = set(re.findall(r"[A-Za-z_]\w*", t1)); ids2 = set(re.findall(r"[A-Za-z_]\w*", t2))
        if ids1 & ids2 or "(" in t1 and "(" in t2:  # shared names or two calls: order carries meaning
            continue
        out.append(("stmt-swap", f"swap `{t1.strip()[:30]}` / `{t2.strip()[:30]}`", body[:s1] + t2 + t1 + body[e2:]))
    # 13. struct layout: shift every field of a block-private struct by a small delta (front padding)
    for m in re.finditer(r"(?:typedef\s+)?struct\s+\w*\s*\{([^}]*)\}", body):
        inner = m.group(1)
        for delta in (4, 8, -4, -8):
            if delta > 0:
                out.append(("struct-pad", f"+{delta} front padding", body[:m.start(1)] + f"\n    u8 lab_pad[{delta}];" + inner + body[m.end(1):]))
            else:
                pm = re.match(r"\s*u8\s+(\w+)\[(0x[0-9A-Fa-f]+|\d+)\];", inner)
                if pm and int(pm.group(2), 0) + delta > 0:
                    out.append(("struct-pad", f"{delta} front padding", body[:m.start(1)] + re.sub(r"^\s*u8\s+\w+\[[^\]]+\];", f"\n    u8 {pm.group(1)}[{int(pm.group(2), 0) + delta}];", inner, count=1) + body[m.end(1):]))
    # 14. a repeated non-trivial expression becomes a local computed once
    exprs = {}
    for m in re.finditer(r"[A-Za-z_]\w*(?:->|\.)\w+(?:(?:->|\.)\w+)*|[A-Za-z_]\w*\[[^\]]+\]", body[span[1]:span[2]]):
        exprs[m.group(0)] = exprs.get(m.group(0), 0) + 1
    for ex, n in exprs.items():
        if n < 2 or re.search(rf"{re.escape(ex)}\s*=[^=]", body[span[1]:span[2]]):
            continue
        first = body.find(ex, span[1])
        line_start = body.rfind("\n", 0, first) + 1
        ins_at = locs[-1][1] if locs else span[1] + 1
        ty = "f32" if re.search(r"f32|\bf\w*\b", ex) and False else "u32"
        text = body[:line_start] + f"    lab_v = {ex};\n" + body[line_start:]
        text = text.replace(ex, "lab_v")
        text = text.replace("    lab_v = lab_v;\n", f"    lab_v = {ex};\n", 1)
        text = text[:ins_at] + f"    {ty} lab_v;\n" + text[ins_at:]
        out.append(("repeat-to-local", f"local for {ex}", text))
    # 10. parameters: signedness flips and unused trailing parameters
    pm = re.search(rf"\b{re.escape(name)}\s*\(([^)]*)\)\s*\{{", body)
    if pm:
        params = [x.strip() for x in pm.group(1).split(",")] if pm.group(1).strip() not in ("", "void") else []
        for k, prm in enumerate(params):
            t0 = prm.split()[0]
            if t0 in FLIP:
                np = list(params); np[k] = prm.replace(t0, FLIP[t0], 1)
                out.append(("param-type", f"param {k}: {t0}->{FLIP[t0]}", body[:pm.start(1)] + ", ".join(np) + body[pm.end(1):]))
        for extra in (1, 2, 3):
            np = params + [f"u32 lab_unused{i}" for i in range(extra)]
            out.append(("param-count", f"+{extra} unused params", body[:pm.start(1)] + ", ".join(np) + body[pm.end(1):]))
    return out




FIELD_FLIP = {"u16": "s16", "s16": "u16", "u8": "s8", "s8": "u8", "u32": "s32", "s32": "u32"}


def _fn_span(body: str, name: str):
    return _function_body_span(body, name)


def extra_families(body: str, name: str) -> List[Tuple[str, str, str]]:
    """(family, label, text): near/far externs, pointer locals for globals, field signedness,
    loop direction, compare casts, call-result temps."""
    out: List[Tuple[str, str, str]] = []
    span = _fn_span(body, name)
    if not span:
        return out
    # 1. near <-> far: a scalar extern becomes an unknown-size array (far) or back
    for m in re.finditer(r"^extern ((?:struct \w+|[us](?:8|16|32)|f32|f64)) ([A-Za-z_]\w*);$", body, re.M):
        t, g = m.groups()
        text = body[:m.start()] + f"extern {t} {g}[];" + body[m.end():]
        if t.startswith("struct"):
            text = re.sub(rf"(?<![\w>.]){re.escape(g)}\.unk_", f"{g}[0].unk_", text)
        else:
            text = re.sub(rf"(?<![\w>.&]){re.escape(g)}\b(?!\s*\[|\s*=\s*\()", f"{g}[0]", text)
        out.append(("near-far", f"{g} far", text))
    for m in re.finditer(r"^extern ((?:struct \w+|[us](?:8|16|32)|f32|f64)) ([A-Za-z_]\w*)\[\];$", body, re.M):
        t, g = m.groups()
        text = body[:m.start()] + f"extern {t} {g};" + body[m.end():]
        text = text.replace(f"{g}[0]", g)
        out.append(("near-far", f"{g} near", text))
    # 2. a global struct accessed several times through a pointer local
    inner = body[span[1]:span[2]]
    for m in re.finditer(r"^extern struct (\w+) ([A-Za-z_]\w*)(\[\])?;$", body, re.M):
        st, g, arr = m.groups()
        uses = re.findall(rf"(?<![\w>.]){re.escape(g)}(?:\[0\])?\.unk_", inner)
        if len(uses) < 2 or f"p_{g}" in body:
            continue
        acc = f"{g}[0].unk_" if arr else f"{g}.unk_"
        new_inner = inner.replace(acc, f"p_{g}->unk_")
        # the assignment goes before the first statement; the declaration with the locals
        first_stmt = re.search(r"\n(\s*)(?![A-Za-z_][\w ]*\*?\s*[A-Za-z_]\w*(\[[^\]]*\])*;\n)([^\n]*;)", new_inner)
        if not first_stmt:
            continue
        at = first_stmt.start(3)
        new_inner = new_inner[:at] + f"p_{g} = (struct {st} *)&{g};\n    " + new_inner[at:]
        new_inner = f"\n    struct {st} *p_{g};" + new_inner
        out.append(("ptr-local", f"pointer local for {g}", body[:span[1]] + new_inner + body[span[2]:]))
    # 3. field signedness in block-private structs
    for m in re.finditer(r"^(    )([us](?:8|16|32)) (unk_[0-9A-F]+)(\[[^\]]*\])?;$", body, re.M):
        t = m.group(2)
        out.append(("field-type", f"{m.group(3)}: {t}->{FIELD_FLIP[t]}", body[:m.start(2)] + FIELD_FLIP[t] + body[m.end(2):]))
    # 4. counted loop direction
    for m in re.finditer(r"for \((\w+) = ([^;]+); \1 != 0; \1--\)", body):
        v, n = m.groups()
        out.append(("loop-form", "count down -> up", body[:m.start()] + f"for ({v} = 0; {v} < {n}; {v}++)" + body[m.end():]))
    for m in re.finditer(r"for \((\w+) = 0; \1 < ([^;]+); \1\+\+\)", body):
        v, n = m.groups()
        out.append(("loop-form", "count up -> down", body[:m.start()] + f"for ({v} = {n}; {v} != 0; {v}--)" + body[m.end():]))
    # 5. compare casts: drop or flip the cast on a compare operand
    for m in re.finditer(r"\((s32|u32)\)([A-Za-z_][\w>.\-\[\]]*) (==|!=|<|>|<=|>=)", inner):
        s0 = span[1] + m.start(); e0 = span[1] + m.end()
        other = "u32" if m.group(1) == "s32" else "s32"
        out.append(("compare-cast", f"drop ({m.group(1)}) on {m.group(2)}", body[:s0] + f"{m.group(2)} {m.group(3)}" + body[e0:]))
        out.append(("compare-cast", f"({m.group(1)})->({other}) on {m.group(2)}", body[:s0] + f"({other}){m.group(2)} {m.group(3)}" + body[e0:]))
    # 6. a returned parameter or constant on a function whose r3 is scratch: a void function
    ret = re.search(r"^(\s*)return ((?:arg\d+|v\d+|-?\d+|0x[0-9A-Fa-f]+));\n\}\s*$", body, re.M)
    if ret:
        sig = re.search(rf"^(u32|s32|s16|u16|s8|u8)( {re.escape(name)}\()", body, re.M)
        if sig:
            text = body[:sig.start(1)] + "void" + body[sig.end(1):]
            text = text.replace(ret.group(0), "}\n", 1)
            out.append(("void-return", "drop the returned value", text))
    # 7. an early return is the source's if-block around the tail: `if (c) { return; } S` -> `if (!c) { S }`
    for m in re.finditer(r"^(\s*)if \((.+?)\) \{ return; \}[^\n]*\n", inner, re.M):
        cond = m.group(2)
        tail = inner[m.end():]
        close = tail.rfind("\n")
        stmts_tail = tail[:close] if close >= 0 else tail
        if "{" in stmts_tail or "}" in stmts_tail or "return" in stmts_tail or not stmts_tail.strip():
            continue
        inv = {"==": "!=", "!=": "==", "<": ">=", ">": "<=", "<=": ">", ">=": "<"}
        mm = re.fullmatch(r"(.+?) (==|!=|<|>|<=|>=) (.+)", cond)
        ncond = f"{mm.group(1)} {inv[mm.group(2)]} {mm.group(3)}" if mm else f"!({cond})"
        new_inner = inner[:m.start()] + f"{m.group(1)}if ({ncond}) {{\n" + stmts_tail + f"\n{m.group(1)}}}" + tail[close:]
        out.append(("return-to-block", "early return -> if block", body[:span[1]] + new_inner + body[span[2]:]))
    # 8a. a call assigned to a field or global goes through a local first (the scheduler places
    #     the store differently when the value has a home)
    for m in re.finditer(r"^(\s*)([A-Za-z_][\w>.\-\[\]]*) = ([A-Za-z_]\w*\([^;]*\));\n", inner, re.M):
        ind, lhs, call = m.groups()
        if re.fullmatch(r"[A-Za-z_]\w*", lhs) and not re.search(rf"(?:->|\.)", lhs):
            continue  # already a plain local
        decl_at = _locals(body, span)
        ins_at = decl_at[-1][1] if decl_at else span[1] + 1
        new_inner = inner[:m.start()] + f"{ind}spell_call = {call};\n{ind}{lhs} = spell_call;\n" + inner[m.end():]
        text = body[:span[1]] + new_inner + body[span[2]:]
        text = text[:ins_at] + "    u32 spell_call;\n" + text[ins_at:]
        out.append(("call-to-local", f"local for {call[:30]}", text))
    # 9. 64-bit values the body split into two u32 halves (OSTime everywhere in the OS SDK): the
    #    halves travel as an adjacent register pair, so the split is invisible in the diff except
    #    as register order. Pairs are rejoined in the signature, at call sites, in stores, and in
    #    the callee's prototype.
    u64_1 = _u64_family(body, name, span, inner)
    out += u64_1
    seen_u64 = {t for _, _, t in u64_1}
    for _, label1, t1 in u64_1[:12]:
        sp1 = _fn_span(t1, name)
        if not sp1:
            continue
        for _, label2, t2 in _u64_family(t1, name, sp1, t1[sp1[1]:sp1[2]])[:12]:
            if t2 not in seen_u64 and t2 != body:
                seen_u64.add(t2); out.append(("u64", f"{label1} + {label2}", t2))
    # 8. a temporary for a call result used once: inline it
    for m in re.finditer(r"^(\s*)(t\d+) = ([A-Za-z_]\w*\([^;]*\));\n", inner, re.M):
        tn, call = m.group(2), m.group(3)
        rest = inner[m.end():]
        if len(re.findall(rf"\b{tn}\b", rest)) == 1:
            new_inner = inner[:m.start()] + re.sub(rf"\b{tn}\b", call, rest, count=1)
            out.append(("inline-call", f"inline {tn}", body[:span[1]] + new_inner + body[span[2]:]))
    return out


# a call with its argument list; casts inside the arguments are one level of parentheses
CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\(((?:[^()]|\([^()]*\))*)\)")


def _pair_proto(text: str, callee: str, idx: int) -> Optional[str]:
    """The callee's extern prototype with parameters idx and idx+1 (both 32-bit ints) as one u64."""
    m = re.search(rf"^extern ([\w ]+?\*?) {re.escape(callee)}\(([^)]*)\);$", text, re.M)
    if not m:
        return None
    ps = [x.strip() for x in m.group(2).split(",")]
    if len(ps) <= idx + 1 or not all(re.fullmatch(r"(u32|s32|int|unsigned int|unsigned|long|unsigned long)", ps[k]) for k in (idx, idx + 1)):
        return None
    ps[idx:idx + 2] = ["u64"]
    return text[:m.start(2)] + ", ".join(ps) + text[m.end(2):]


def _u64_family(body: str, name: str, span, inner: str) -> List[Tuple[str, str, str]]:
    out: List[Tuple[str, str, str]] = []
    protos = set(re.findall(r"^extern [\w ]+?\*? ([A-Za-z_]\w*)\([^)]*\);$", body, re.M))
    # `#define InsertAlarm InsertAlarm_8000AC44`: the call names the alias, the prototype the symbol
    aliases = dict(re.findall(r"^#define (\w+) (\w+)$", body, re.M))
    protos |= {a for a, t in aliases.items() if t in protos}
    def proto_name(c):
        return aliases.get(c, c)
    # (a) two adjacent zero arguments: one u64 zero (materialised low word first, as retail does)
    declared = {m.group(1) for m in re.finditer(r"^extern [\w ]+?\*? ([A-Za-z_]\w*)\(", body, re.M)} | set(aliases)
    keywords = {"if", "while", "for", "switch", "return", "sizeof"}
    for cm in re.finditer(CALL_RE, inner):
        callee, args = cm.group(1), cm.group(2)
        if callee == name or callee in keywords or not args.strip():
            continue
        al = [a.strip() for a in args.split(",")]
        for k in range(len(al) - 1):
            if al[k] == "0" and al[k + 1] == "0":
                new_inner = inner[:cm.start(2)] + ", ".join(al[:k] + ["(u64)0"] + al[k + 2:]) + inner[cm.end(2):]
                text = body[:span[1]] + new_inner + body[span[2]:]
                text = _pair_proto(text, proto_name(callee), k) if callee in declared else text
                if text:
                    out.append(("u64", f"{callee}: zero pair at {k} -> (u64)0", text))
    # (b) two adjacent 32-bit parameters that only ever travel together: one u64 parameter
    sig = re.search(rf"\b{re.escape(name)}\s*\(([^)]*)\)\s*\{{", body)
    if sig and sig.group(1).strip() not in ("", "void"):
        ps = [x.strip() for x in sig.group(1).split(",")]
        for k in range(len(ps) - 1):
            ma = re.fullmatch(r"(u32|s32) (\w+)", ps[k]); mb = re.fullmatch(r"(u32|s32) (\w+)", ps[k + 1])
            if not (ma and mb):
                continue
            A, B = ma.group(2), mb.group(2)
            pair_re = rf"\b{A}, {B}\b"
            # a store of both halves to fields 4 bytes apart, in either order
            store_re = (rf"^(\s*)([A-Za-z_][\w>.\-\[\]]*?)unk_([0-9A-Fa-f]+) = ({A}|{B});\n\s*\2unk_([0-9A-Fa-f]+) = ({A}|{B});\n")
            stores = [m for m in re.finditer(store_re, inner, re.M) if {m.group(4), m.group(6)} == {A, B}
                      and abs(int(m.group(3), 16) - int(m.group(5), 16)) == 4]
            n_pair = len(re.findall(pair_re, inner))
            if n_pair + len(stores) == 0:
                continue
            if len(re.findall(rf"\b{A}\b", inner)) != n_pair + len(stores) or len(re.findall(rf"\b{B}\b", inner)) != n_pair + len(stores):
                continue
            P = f"{A}_{B}"
            new_inner = inner
            for m in reversed(stores):
                lo = min(int(m.group(3), 16), int(m.group(5), 16))
                # the high half is the first parameter (the lower register); the u64 store covers both
                new_inner = new_inner[:m.start()] + f"{m.group(1)}*(u64 *)&{m.group(2)}unk_{lo:X} = {P};\n" + new_inner[m.end():]
            # call sites: the pair becomes one argument; the callee's prototype pairs the same slot
            text = body[:span[1]] + new_inner + body[span[2]:]
            ok = True
            for cm in list(re.finditer(CALL_RE, new_inner)):
                al = [a.strip() for a in cm.group(2).split(",")]
                for j in range(len(al) - 1):
                    if al[j] == A and al[j + 1] == B:
                        t2 = _pair_proto(text, proto_name(cm.group(1)), j)
                        if t2 is None:
                            ok = False
                        else:
                            text = t2
            if not ok:
                continue
            text = re.sub(pair_re, P, text)
            text = text.replace(sig.group(1), ", ".join(ps[:k] + [f"u64 {P}"] + ps[k + 2:]), 1)
            out.append(("u64", f"parameters {A}, {B} -> u64 {P}", text))
    # (d) a call argument that is a cast local or a plain local: dropped, with the prototype
    #     shortened (retail's register there was scratch; the body invented the argument)
    for cm in re.finditer(CALL_RE, inner):
        callee, args = cm.group(1), cm.group(2)
        if callee == name or callee in keywords or not args.strip():
            continue
        al = [a.strip() for a in args.split(",")]
        for k, arg in enumerate(al):
            if not re.fullmatch(r"\((?:u32|s32)\)\w+|[a-z]\w*", arg) or len(al) < 2:
                continue
            new_inner = inner[:cm.start(2)] + ", ".join(al[:k] + al[k + 1:]) + inner[cm.end(2):]
            text = body[:span[1]] + new_inner + body[span[2]:]
            if callee in declared:
                pm = re.search(rf"^extern ([\w ]+?\*?) {re.escape(proto_name(callee))}\(([^)]*)\);$", text, re.M)
                if not pm:
                    continue
                ps = [x.strip() for x in pm.group(2).split(",")]
                if len(ps) != len(al):
                    continue
                del ps[k]
                text = text[:pm.start(2)] + ", ".join(ps) + text[pm.end(2):]
            out.append(("u64", f"{callee}: drop argument {k} ({arg})", text))
    # (c) a u64 value stored as two halves: one store
    for m in re.finditer(r"^(\s*)([A-Za-z_][\w>.\-\[\]]*?)unk_([0-9A-Fa-f]+) = \(u32\)\((\w+) >> 32\);\n\s*\2unk_([0-9A-Fa-f]+) = \(u32\)\4;\n", inner, re.M):
        if int(m.group(5), 16) - int(m.group(3), 16) != 4:
            continue
        new_inner = inner[:m.start()] + f"{m.group(1)}*(u64 *)&{m.group(2)}unk_{m.group(3)} = {m.group(4)};\n" + inner[m.end():]
        out.append(("u64", f"{m.group(4)}: halves -> one u64 store", body[:span[1]] + new_inner + body[span[2]:]))
    return out


def all_rewrites(body: str, name: str, max_per_family: int = 16) -> List[Tuple[str, str, str]]:
    """Every single-step rewrite, at most `max_per_family` of any one family (the declaration
    permutations alone would be a hundred; the engine shares their candidate budget)."""
    out: List[Tuple[str, str, str]] = []
    for fn in (lambda b, n: perturbations(b, n),
               lambda b, n: [("regalloc", l, t) for l, t in rewrites(b, n)],
               extra_families):
        try:
            out += fn(body, name)
        except Exception:
            continue
    counts: Dict[str, int] = {}
    kept = []
    by_fam: Dict[str, List[str]] = {}
    for fam, label, text in out:
        counts[fam] = counts.get(fam, 0) + 1
        by_fam.setdefault(fam, []).append(text)
        if counts[fam] <= max_per_family:
            kept.append((fam, label, text))
    # every edit of a family applied together (the same fix at every site): the composition of
    # the per-site texts when their edits do not overlap
    for fam, texts in by_fam.items():
        if len(texts) < 2 or fam in ("decl-order", "regalloc", "param-count", "struct-pad"):
            continue
        base_lines = body.splitlines(keepends=True)
        merged = list(base_lines); ok = True; touched: set = set()
        for t in texts[:24]:
            sm = difflib.SequenceMatcher(None, base_lines, t.splitlines(keepends=True), autojunk=False)
            ops = [(tag, i1, i2, j1, j2) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal"]
            if any(set(range(i1, max(i2, i1 + 1))) & touched for _, i1, i2, _, _ in ops):
                continue
            tl = t.splitlines(keepends=True)
            for tag, i1, i2, j1, j2 in reversed(ops):
                merged[i1:i2] = tl[j1:j2]
                touched.update(range(i1, max(i2, i1 + 1)))
        text = "".join(merged)
        if text != body and text not in texts:
            kept.append((fam, f"{fam} at every site", text))
    return kept


def fitness(tw: List[int], ow: List[int]) -> Tuple[float, float]:
    """(aligned matched words as a percent, positional percent)."""
    if not tw or not ow:
        return (0.0, 0.0)
    sm = difflib.SequenceMatcher(None, tw, ow, autojunk=False)
    matched = sum(b.size for b in sm.get_matching_blocks())
    n = max(len(tw), len(ow))
    pos, _ = oracle.word_score(tw, ow)
    return (100.0 * matched / n, pos)




TOKEN = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
                   r'[A-Za-z_]\w*|(?:0[xX][0-9a-fA-F]+|\d+(?:\.\d*)?)(?:[eE][+-]?\d+)?[uUlLfF]*|'
                   r'->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||[+*/%&|^!-]=|[^\s]', re.S)
PREC = {'=': 1, '+=': 1, '-=': 1, '*=': 1, '/=': 1, '|=': 1, '&=': 1,
        '||': 2, '&&': 3, '|': 4, '^': 5, '&': 6, '==': 7, '!=': 7,
        '<': 8, '>': 8, '<=': 8, '>=': 8, '<<': 9, '>>': 9,
        '+': 10, '-': 10, '*': 11, '/': 11, '%': 11}
COMMUTE = {'+', '*', '&', '|', '^', '==', '!='}


def commutations(body, name, operations=None):
    """Parse expression precedence, retaining source spans and parenthesization.

    Calls, updates and assignments make an expression ineligible to commute,
    though pure subexpressions within it remain eligible. Casts and unsupported
    syntax end a parse; compilation checks all proposals against retail.
    """
    span = _function_body_span(body, name)
    if not span:
        return []
    tokens = [(m[0], m.start() + span[1], m.end() + span[1])
              for m in TOKEN.finditer(body[span[1]:span[2]])
              if not m[0].startswith(('/*', '//'))]
    proposals, sites = [], defaultdict(list)
    types = {'void', 'char', 'short', 'int', 'long', 'signed', 'unsigned', 'float', 'double',
             'u8', 's8', 'u16', 's16', 'u32', 's32', 'u64', 's64', 'f32', 'f64'}
    types.update(re.findall(r'\btypedef\s+[^;{}]+\s+(\w+)\s*;', body))

    def parse(i, minimum=1):
        if i >= len(tokens):
            raise ValueError
        tok, start, end = tokens[i]
        i += 1
        pure = True
        if tok == '(':
            close = i
            while close < len(tokens) and (re.fullmatch(r'\w+', tokens[close][0]) or tokens[close][0] == '*'):
                close += 1
            cast = (i < close < len(tokens) and tokens[close][0] == ')' and
                    (tokens[i][0] in types or tokens[i][0] in ('struct', 'union', 'enum', 'const', 'volatile')))
            if cast:
                i, (_, end, pure) = parse(close + 1, 12)
            else:
                i, (_, end, pure) = parse(i)
                if i >= len(tokens) or tokens[i][0] != ')':
                    raise ValueError
                end = tokens[i][2]
                i += 1
        elif tok in ('-', '+', '!', '~', '*', '&', '++', '--'):
            i, (_, end, pure) = parse(i, 12)
            pure &= tok not in ('++', '--')
        elif not re.match(r'[\w"\']', tok):
            raise ValueError
        while i < len(tokens):
            op = tokens[i][0]
            if op in ('->', '.') and i + 1 < len(tokens):
                end = tokens[i + 1][2]
                i += 2
                continue
            if op == '[':
                j, _ = parse(i + 1)
                if j >= len(tokens) or tokens[j][0] != ']':
                    raise ValueError
                # Index expressions can have side effects too.
                pure &= not any(t[0] in ('(', '++', '--', '=') for t in tokens[i + 1:j])
                end, i = tokens[j][2], j + 1
                continue
            if op == '(':
                # Parse arguments to discover commutations inside calls.
                j = i + 1
                while j < len(tokens) and tokens[j][0] != ')':
                    j, _ = parse(j)
                    if j < len(tokens) and tokens[j][0] == ',':
                        j += 1
                    else:
                        break
                if j >= len(tokens) or tokens[j][0] != ')':
                    raise ValueError
                end, i, pure = tokens[j][2], j + 1, False
                continue
            if op in ('++', '--'):
                end, i, pure = tokens[i][2], i + 1, False
                continue
            precedence = PREC.get(op, 0)
            if precedence < minimum:
                break
            j, (rs, re_, rp) = parse(i + 1, precedence + (precedence != 1))
            if operations is not None and pure and rp and precedence > 1:
                operations.append({'start': start, 'end': re_, 'left': (start, end),
                                   'right': (rs, re_), 'op': op})
            if op in COMMUTE and pure and rp and body[start:end] != body[rs:re_]:
                replacement = f'(({body[rs:re_]}) {op} ({body[start:end]}))'
                proposals.append((f'operand {op} at {start}', body[:start] + replacement + body[re_:]))
                sites[(body[start:re_], replacement, op)].append((start, re_))
            end, i, pure = re_, j, pure and rp and precedence != 1
        return i, (start, end, pure)

    i = 0
    while i < len(tokens):
        try:
            j, _ = parse(i)
            i = max(i + 1, j)
        except (ValueError, RecursionError):
            i += 1
    # CSE couples identical occurrences: changing one may leave the shared
    # expression's operand order determined by the unchanged occurrence.
    grouped = []
    for (old, replacement, op), ranges in sites.items():
        ranges = sorted(set(ranges))
        if len(ranges) > 1 and all(b <= c for (_, b), (c, _) in zip(ranges, ranges[1:])):
            text = body
            for a, b in reversed(ranges):
                text = text[:a] + replacement + text[b:]
            grouped.append((f'shared operands {old}', text))
    # Repeated blocks often use different temporary names. Exact text grouping
    # misses their coupled operand choices; group disjoint scalar expressions by
    # operator as well. Exclude pointer arithmetic and nested overlapping trees.
    by_operator = defaultdict(list)
    for (old, replacement, op), ranges in sites.items():
        if re.search(r'\*\s*\)|\b(?:u8|s8|void|char)\b|\[', old):
            continue
        for a,b in ranges:
            by_operator[op].append((a,b,replacement))
    for op, ranges in by_operator.items():
        ranges=sorted(set(ranges))
        if len(ranges)>1 and all(b<=c for (_,b,_),(c,_,_) in zip(ranges,ranges[1:])):
            text=body
            for a,b,replacement in reversed(ranges):
                text=text[:a]+replacement+text[b:]
            grouped.append((f'coupled scalar operands {op}',text))
    return list(dict.fromkeys(grouped + proposals))


def probes(body, name, limit=32):
    """Linear probes, not permutations; each observed response is reusable."""
    choices = commutations(body, name)
    normalized = normalise(body)
    span = _function_body_span(normalized, name)
    if span:
        locs = _locals(normalized, span)
        lines = [normalized[s:e] for s, e, *_ in locs]
        for i in range(len(locs) - 1):
            order = list(range(len(locs)))
            order[i:i + 2] = reversed(order[i:i + 2])
            if _order_ok(locs, lines, order):
                choices.append((f'adjacent declarations {i}', reorder(normalized, locs, order)))
    # Scope and materialization change live ranges; they are not register renames.
    nested = []
    if span:
        declarations = [(m.start() + span[1], m.end() + span[1], m[0])
                        for m in re.finditer(r'[^\n]*\n', normalized[span[1]:span[2]])
                        if (match := DECL_RE.match(m[0].rstrip('\n')))
                        and match[1].strip() not in ('return', 'goto', 'break', 'continue')]
        for (a, b, first), (c, d, second) in zip(declarations, declarations[1:]):
            if b != c:
                continue
            fm, sm = (DECL_RE.match(line.rstrip('\n')) for line in (first, second))
            if re.search(r'\b' + re.escape(fm[2]) + r'\b', sm[4] or ''):
                continue
            nested.append((f'block declarations {fm[2]}, {sm[2]}', normalized[:a] + second + first + normalized[d:]))
    from .fixup_evidence import optimizer_pragmas
    families = [choices, nested, scope_moves(normalized, name),
                optimizer_pragmas(body, name),
                through_local(normalized, name), split_inits(normalized, name)]
    out, seen = [], {body}
    for i in range(max(map(len, families), default=0)):
        for family in families:
            if i < len(family) and family[i][1] not in seen:
                seen.add(family[i][1])
                out.append(family[i])
                if len(out) == limit:
                    return out
    return out


def edits(before, after):
    """Align lines, then trim changed spans; never quadratic whole-body character LCS."""
    left, right = before.splitlines(keepends=True), after.splitlines(keepends=True)
    offsets = [0]
    for line in left:
        offsets.append(offsets[-1] + len(line))
    changes = []
    for tag, a, b, c, d in difflib.SequenceMatcher(None, left, right, autojunk=False).get_opcodes():
        if tag == 'equal':
            continue
        old, new = ''.join(left[a:b]), ''.join(right[c:d])
        first, last = 0, 0
        while first < min(len(old), len(new)) and old[first] == new[first]:
            first += 1
        while last < min(len(old), len(new)) - first and old[-last-1] == new[-last-1]:
            last += 1
        changes.append((offsets[a] + first, offsets[b] - last, new[first:len(new)-last]))
    return changes


def compose(body, target, baseline, responses):
    """Set cover over exact repaired bits, constrained by source-span conflicts.

    Responses that change any correct bit are excluded. A combined compile is
    essential: register allocation can couple otherwise disjoint source edits.
    """
    remaining = {(i, bit) for i, (a, b) in enumerate(zip(target, baseline))
                 for bit in range(32) if (a ^ b) & (1 << bit)}
    eligible = []
    for label, source, words in responses:
        if words is None or len(words) != len(target):
            continue
        if any((old ^ new) & (wanted ^ new) for wanted, old, new in zip(target, baseline, words)):
            continue
        fixed = {(i, bit) for i, (old, new) in enumerate(zip(baseline, words))
                 for bit in range(32) if (old ^ new) & (1 << bit)}
        if fixed:
            eligible.append((fixed, label, edits(body, source)))
    chosen, patches = [], []
    while eligible:
        eligible.sort(key=lambda r: -len(r[0] & remaining))
        fixed, label, changes = eligible.pop(0)
        if not fixed & remaining:
            break
        if any(max(a, c) <= min(b, d) for a, b, _ in changes for c, d, _ in patches):
            continue
        chosen.append(label)
        patches.extend(changes)
        remaining -= fixed
    if len(chosen) < 2:
        return None
    for a, b, text in sorted(patches, reverse=True):
        body = body[:a] + text + body[b:]
    return ' + '.join(chosen), body


def linear_compositions(body, target, baseline, responses):
    """Solve the measured bit responses over GF(2), including cancelling effects.

    This is a shortlist, never an assertion that the allocator is linear. Rotating
    pivot order exposes bounded alternative solutions without subset enumeration.
    """
    def vector(words):
        return int.from_bytes(b''.join((a ^ b).to_bytes(4, 'big') for a, b in zip(baseline, words)), 'big')
    wanted = vector(target)
    choices = [(label, source, vector(words)) for label, source, words in responses
               if words and len(words) == len(target)]
    choices = [c for c in choices if c[2]]
    proposals, seen = [], set()
    for offset in range(min(len(choices), 8)):
        ordered = choices[offset:] + choices[:offset]
        basis = {}
        for i, (_, _, value) in enumerate(ordered):
            mask = 1 << i
            while value:
                pivot = value.bit_length()
                if pivot not in basis:
                    basis[pivot] = value, mask
                    break
                other, selected = basis[pivot]
                value ^= other
                mask ^= selected
        value, mask = wanted, 0
        while value and value.bit_length() in basis:
            other, selected = basis[value.bit_length()]
            value ^= other
            mask ^= selected
        if value or mask.bit_count() < 2:
            continue
        patches, labels = [], []
        for i, (label, source, _) in enumerate(ordered):
            if not mask & (1 << i):
                continue
            changes = edits(body, source)
            if any(max(a, c) <= min(b, d) for a, b, _ in changes for c, d, _ in patches):
                break
            patches.extend(changes)
            labels.append(label)
        else:
            text = body
            for a, b, replacement in sorted(patches, reverse=True):
                text = text[:a] + replacement + text[b:]
            if text not in seen:
                seen.add(text)
                proposals.append(('response equations: ' + ' + '.join(labels), text))
    return proposals




ALIASES = {'li': 'addi', 'lis': 'addis', 'subi': 'addi', 'subis': 'addis',
           'slwi': 'rlwinm', 'srwi': 'rlwinm', 'clrlwi': 'rlwinm', 'clrrwi': 'rlwinm',
           'rotlwi': 'rlwinm', 'clrlslwi': 'rlwinm', 'mtlr': 'mtspr', 'mflr': 'mfspr',
           'mtctr': 'mtspr', 'mfctr': 'mfspr', 'cmpwi': 'cmpi', 'cmplwi': 'cmpli',
           'cmpw': 'cmp', 'cmplw': 'cmpl'}


def mnemonic(name):
    return ALIASES.get(name, name)


def decode(words):
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True
    return [(mnemonic(i.mnemonic), tuple(mwconstraints.REG.findall(i.op_str)), i.op_str)
            for i in md.disasm(b''.join(w.to_bytes(4, 'big') for w in words), 0)]


def web_constraints(captures, target, ours):
    original, retail = decode(ours), decode(target)
    if len(original) != len(ours) or len(retail) != len(target):
        return {'status': 'instruction-shape'}
    shape = lambda row: (row[0], mwconstraints.REG.sub('R', row[2]))
    retail_alignment = difflib.SequenceMatcher(a=[shape(r) for r in original],
                                              b=[shape(r) for r in retail], autojunk=False)
    retail_rows = {block.a + i: block.b + i for block in retail_alignment.get_matching_blocks()
                   for i in range(block.size)}
    nodes = {c['before']['register_class']: {n['virtual_register']: n for n in c['after']['nodes']}
             for c in captures}
    def root(cls, register):
        seen = set()
        while register >= 32 and nodes[cls][register]['flags'] & 4:
            if register in seen:
                raise ValueError('coalescing cycle')
            seen.add(register)
            register = nodes[cls][register]['physical_register']
        return register
    def physical(cls, register):
        register = root(cls, register)
        return register if register < 32 else nodes[cls][register]['physical_register']
    pcode = max((c.get('pcode', []) for c in captures), key=len)
    keys, origins = [], []
    for instruction in pcode:
        operands, regs = [], []
        for a in instruction['operands']:
            cls, r = a['class'], a['reg']
            if cls not in nodes or a['flags'] == 0:
                continue
            prefix = 'r' if cls == 'gpr' else 'f'
            operands.append((cls, root(cls, r)))
            regs.append(prefix + str(physical(cls, r)))
        name = mnemonic(instruction['mnemonic'])
        if name in ('mr', 'fmr') and len(regs) == 2 and regs[0] == regs[1]:
            continue
        keys.append((name, tuple(regs)))
        origins.append(operands)
    matching = difflib.SequenceMatcher(a=keys, b=[r[:2] for r in original], autojunk=False)
    domains, alternatives, anchors = defaultdict(set), [], []
    for block in matching.get_matching_blocks():
        for offset in range(block.size):
            row, index = block.b + offset, block.a + offset
            if row not in retail_rows:
                continue
            name, registers, operand_text = retail[retail_rows[row]]
            if name != original[row][0] or len(registers) != len(origins[index]):
                continue
            if mwconstraints.REG.sub('R', operand_text) != mwconstraints.REG.sub('R', original[row][2]):
                continue
            pairs = list(zip(origins[index], (int(r[1:]) for r in registers)))
            anchors.append(row)
            if name in mwconstraints.COMMUTE and len(pairs) == 3:
                domains[pairs[0][0]].add(pairs[0][1])
                alternatives.append((row, pairs[1:]))
            else:
                for web, color in pairs:
                    domains[web].add(color)
    conflicts = {str(k): sorted(v) for k, v in domains.items() if len(v) > 1}
    desired = {web: next(iter(colors)) for web, colors in domains.items() if len(colors) == 1}
    swapped, unresolved = [], []
    for row, pairs in alternatives:
        (a, x), (b, y) = pairs
        valid = [(swap, u, v) for swap, u, v in [(False, x, y), (True, y, x)]
                 if desired.get(a, u) == u and desired.get(b, v) == v and (a != b or u == v)]
        if not valid:
            unresolved.append(row)
            continue
        if len(valid) > 1 and x != y:
            unresolved.append(row)
            continue
        swap, x, y = valid[0]
        desired[a], desired[b] = x, y
        if swap:
            swapped.append(row)
    return {'status': 'web-hypothesis', 'anchors': anchors,
            'conflicts': conflicts, 'desired': {cls: {r: c for (bank, r), c in desired.items() if cls == bank and r >= 32}
                        for cls in nodes}, 'operand_order_rows': swapped, 'unresolved_rows': unresolved}


def scalar_locals(body, span):
    # Carriers from a previous repair are fixed aggregate declarations; keep
    # scanning so remaining scalars can be repaired in the next captured graph.
    result = []
    for match in re.finditer(r'[^\n]*\n', body[span[1]:span[2]]):
        line = match[0]
        if not line.strip() or re.fullmatch(r'\s*struct \{ [^{};]+ value; \} \w+(?: = \{ .* \})?;\s*', line):
            continue
        decl = DECL_RE.match(line.rstrip('\n'))
        if not decl:
            break
        start = span[1] + match.start()
        result.append((start, start + len(line), decl[1], decl[2], decl[3]))
    return result


def annotate_verified_branches(body, findings):
    """Document branch preservation only after a full stock-object match."""
    lines = body.splitlines(keepends=True)
    changed = False
    for rule, line, _ in findings:
        if rule != 'S1':
            continue
        match = re.search(r'\bgoto\s+(\w+)\s*;', lines[line - 1])
        if match:
            pos = match.end()
            lines[line - 1] = (lines[line - 1][:pos] + f' /* Keep the verified branch to {match[1]}. */'
                               + lines[line - 1][pos:])
            changed = True
    return [('document verified control flow', ''.join(lines))] if changed else []


def declaration_candidates(body, name, captures, constraints, max_orders=50000):
    """Evaluate declaration orders in the actual graph, with no compile loop."""
    if constraints['status'] != 'web-hypothesis' or constraints['operand_order_rows']:
        return [], {'status': constraints['status'], 'orders': 0}
    span = _function_body_span(body, name)
    if span is None:
        return [], {'status': 'no-body', 'orders': 0}
    locals_ = scalar_locals(body, span)
    if any(_init_of(body[a:b]) for a, b, *_ in locals_):
        return [], {'status': 'initialized-declarations', 'orders': 0}
    by_name = defaultdict(list)
    for capture in captures:
        cls = capture['before']['register_class']
        for n in capture['before']['nodes']:
            if n.get('name'):
                by_name[n['name']].append((cls, n['virtual_register']))
    if all(all(next(n['physical_register'] for n in c['after']['nodes'] if n['virtual_register'] == r) == color
                   for r, color in constraints['desired'][c['before']['register_class']].items()) for c in captures):
        return [], {'status': 'no-allocation-difference', 'orders': 0}
    movable = [(i, by_name[n][0]) for i, (_, _, _, n, dims) in enumerate(locals_)
               if not dims and len(by_name.get(n, [])) == 1]
    if len(movable) < 2:
        return [], {'status': 'no-movable-stratum', 'orders': 0}
    slots = {cls: sorted((r for _, (bank, r) in movable if bank == cls), reverse=True)
             for cls in constraints['desired']}
    if any([r for _, (bank, r) in movable if bank == cls] != order for cls, order in slots.items()):
        return [], {'status': 'unknown-creation-order', 'orders': 0}
    witnesses = []
    positions = {}
    for capture in captures:
        before=capture['before']; cls=before['register_class']
        desired={n['virtual_register']:n['physical_register'] for n in capture['after']['nodes']
                 if n['virtual_register'] in before['simplify_order']}
        desired.update({r:color for r,color in constraints['desired'][cls].items() if r in desired})
        if any(not 0<=color<32 for color in desired.values()):
            continue
        witness=mwgraph.selection_order(before,desired)
        if witness:
            positions[cls]={r:i for i,r in enumerate(witness)}
    if positions:
        ordered=list(movable)
        for cls,rank in positions.items():
            indices=[i for i,(_, (bank,r)) in enumerate(movable) if bank==cls]
            values=sorted((movable[i] for i in indices),key=lambda x:rank.get(x[1][1],10**9))
            for i,value in zip(indices,values):
                ordered[i]=value
        witnesses.append(ordered)
    candidates, checked, best = [], 0, None
    # Source ranks still have to reproduce simplify and coloring, not merely
    # the abstract selection witness. Keep a bounded small-stratum fallback.
    orders=itertools.chain(witnesses,itertools.islice(itertools.permutations(movable),min(max_orders,720)))
    for order in orders:
        ranks = {cls: dict(zip((r for _, (bank, r) in order if bank == cls), slots[cls])) for cls in slots}
        score = 0
        for capture in captures:
            before = capture['before']; cls = before['register_class']
            select = mwgraph.simplify(before, ranks[cls])
            if select is None:
                score += 100000
                continue
            colors = mwgraph.replay(before, select)
            score += sum(colors[r] != c for r, c in constraints['desired'][cls].items())
        checked += 1
        best = score if best is None else min(best, score)
        if score:
            continue
        replacements = {i: locals_[j] for (i, _), (j, _) in zip(movable, order)}
        text, cursor = [], 0
        for i, (a, b, *_) in enumerate(locals_):
            text.append(body[cursor:a])
            x, y, *_ = replacements.get(i, locals_[i])
            text.append(body[x:y]); cursor = b
        candidate = ''.join(text) + body[cursor:]
        if candidate != body:
            candidates.append(candidate)
        # Equivalent orders of unused locals do not justify more compiler calls.
        if candidates:
            break
    return candidates, {'status': 'predicted' if candidates else 'no-predicted-declaration-repair',
                        'orders': checked, 'exhaustive': checked >= len(witnesses) + math.factorial(len(movable)),
                        'best_conflicts': best}


def carrier_candidates(body, name, captures, constraints):
    """Move implicated scalar homes into MWCC's aggregate-scalarization stratum.

    A one-field aggregate preserves the scalar's declared type. Only identifier
    uses in the function body are changed; field names, strings and comments
    retain their spelling. Every result still requires a stock compile.
    """
    span = _function_body_span(body, name)
    if span is None or constraints['status'] != 'web-hypothesis':
        return []
    locals_ = scalar_locals(body, span)
    implicated = set()
    for capture in captures:
        cls = capture['before']['register_class']
        desired = {int(r): c for r, c in constraints['desired'][cls].items()}
        nodes = {n['virtual_register']: n for n in capture['after']['nodes']}
        for n in nodes.values():
            r, seen = n['virtual_register'], set()
            while r >= 32 and nodes[r]['flags'] & 4 and r not in seen:
                seen.add(r); r = nodes[r]['physical_register']
            if r >= 32 and r in desired and nodes[r]['physical_register'] != desired[r] and n.get('name'):
                implicated.add(n['name'])
    # Saved compiler temporaries can carry a source scalar whose original home
    # was coalesced into an ABI register. PCode line provenance recovers those
    # assignments instead of mistaking the temporary's @name for a C local.
    assignments = []
    local_names = {l[3] for l in locals_}
    for match in re.finditer(r'^\s*(\w+)\s*=(?!=)[^;{}]+;', body[span[1]:span[2]], re.M):
        if match[1] not in local_names:
            continue
        start = span[1] + match.start(); end = span[1] + match.end()
        assignments.append((body.count('\n', 0, start) + 1, body.count('\n', 0, end) + 2, match[1]))
    for capture in captures:
        cls = capture['before']['register_class']
        desired = {int(r): c for r, c in constraints['desired'][cls].items()}
        nodes = {n['virtual_register']: n for n in capture['after']['nodes']}
        wrong = {r for r, color in desired.items() if nodes[r]['physical_register'] != color}
        for instruction in capture['pcode']:
            line = instruction['line']
            if line is None or line < 1:
                continue
            if any(a['class'] == cls and a['reg'] in wrong and a['flags'] & 2 for a in instruction['operands']):
                implicated.update(var for first, last, var in assignments if first <= line <= last)
    selected = [l for l in locals_ if l[3] in implicated and not l[4]]
    proposals = []
    groups = [(local,) for local in selected]
    groups.extend(itertools.combinations(selected, 2))
    if len(selected) > 2:
        groups.append(tuple(selected))
    for group in groups:
        if any('volatile' in l[2] or 'register' in l[2] for l in group):
            continue
        names = {l[3] for l in group}
        def uses(text):
            changes, previous = [], None
            for match in TOKEN.finditer(text):
                token = match[0]
                if token.startswith(('/*', '//')):
                    continue
                if token in names and previous not in ('.', '->', 'struct', 'union', 'enum'):
                    changes.append((match.start(), match.end(), token + '.value'))
                previous = token
            for a, b, value in reversed(changes):
                text = text[:a] + value + text[b:]
            return text
        changes = []
        for a, b, type_, var, _ in group:
            init = _init_of(body[a:b])
            initializer = ' = { ' + uses(init) + ' }' if init is not None else ''
            changes.append((a, b, f'    struct {{ {type_} value; }} {var}{initializer};\n'))
        # Rewrite uses between converted declarations too, including scalar
        # initializers depending on an earlier converted local.
        pieces, cursor = [], group[0][0]
        for a, b, declaration in sorted(changes):
            pieces.extend((uses(body[cursor:a]), declaration))
            cursor = b
        pieces.append(uses(body[cursor:span[2]]))
        source = body[:group[0][0]] + ''.join(pieces) + body[span[2]:]
        label = 'carrier:' + ','.join(l[3] for l in group)
        proposals.append((label, source))
        # A block-local value can survive scalarization as a separate web where
        # assigning the aggregate member directly collapses back to a scalar.
        split = source
        changed = False
        for _, _, type_, var, _ in group:
            temp = '__reg_value_' + var
            while re.search(r'\b' + temp + r'\b', split):
                temp += '_'
            pattern = re.compile(r'^(\s*)' + re.escape(var) + r'\.value\s*=\s*([^;{}]+);', re.M)
            def replace_assignment(match):
                nonlocal changed
                changed = True
                return (match[1] + '{ ' + type_ + ' ' + temp + ' = ' + match[2] + '; ' +
                        var + '.value = ' + temp + '; }')
            split = pattern.sub(replace_assignment, split)
        if changed:
            proposals.append((label + ':block-copy', split))
    return proposals


def expression_trees(body, name):
    operations = []
    commutations(body, name, operations)
    out = []
    for outer in operations:
        op = outer['op']
        if op not in ('+', '*', '&', '|', '^'):
            continue
        for side in ('left', 'right'):
            lo, hi = outer[side]
            children = [r for r in operations if r['op'] == op and lo <= r['start'] and r['end'] <= hi
                        and (r['start'], r['end']) != (outer['start'], outer['end'])
                        and not body[lo:r['start']].strip(' (\t\n') and not body[r['end']:hi].strip(' )\t\n')]
            if not children:
                continue
            child = max(children, key=lambda r:r['end']-r['start'])
            other = outer['right' if side == 'left' else 'left']
            terms = [body[a:b] for a,b in (child['left'], child['right'], other)]
            # Constants and load order affect CSE and FMA selection. Enumerate the
            # two three-leaf trees together instead of commuting just one node.
            for a,b,c in dict.fromkeys(itertools.permutations(terms)):
                for text in (f'((({a}) {op} ({b})) {op} ({c}))', f'(({a}) {op} (({b}) {op} ({c})))'):
                    out.append((f'expression-tree {op} at {outer["start"]}',
                                body[:outer['start']]+text+body[outer['end']:]))
    return list(dict.fromkeys(out))


def missing_values(body, name):
    """Bind a used but never-defined scalar to an already-read source lvalue.

    Preserve the existing load's evaluation point through an assignment expression.
    This repairs missing def/use edges without inserting an arbitrary entry load.
    """
    span = _function_body_span(body, name)
    if not span:
        return []
    locals_ = _locals(body, span)
    if not locals_:
        return []
    start = locals_[-1][1]
    tokens = [(m[0], m.start()+start, m.end()+start) for m in TOKEN.finditer(body[start:span[2]])
              if not m[0].startswith(('/*','//'))]
    out=[]
    for a,b,type_,var,dims in locals_:
        if dims or _init_of(body[a:b]):
            continue
        uses=[i for i,t in enumerate(tokens) if t[0]==var and (i==0 or tokens[i-1][0] not in ('.','->'))]
        if not uses:
            continue
        if any((i+1<len(tokens) and tokens[i+1][0] in ('=','+=','-=','*=','/=','++','--','|=','&=','^='))
               or (i and tokens[i-1][0] in ('++','--','&')) for i in uses):
            continue
        first=tokens[uses[0]][1]
        pattern=r'\b(?:lbl_\w+|[A-Za-z_]\w*(?:->|\.)[A-Za-z_]\w*)(?:(?:->|\.)[A-Za-z_]\w*|\[\d+\])*'
        for m in re.finditer(pattern,body[start:first]):
            lo,hi=start+m.start(),start+m.end()
            # Only reads, never assignment destinations or address-taking.
            if re.match(r'\s*(?:=(?!=)|[+*/&|^-]=|\+\+|--)',body[hi:]) or body[max(start,lo-1):lo]=='&':
                continue
            replacement=f'({var} = {m[0]})'
            out.append((f'missing-value {var} from {m[0]} at {lo}',body[:lo]+replacement+body[hi:]))
    return out


def external_helper(body, name):
    """Use an already-owned helper instead of emitting a duplicate local copy."""
    span=_function_body_span(body,name)
    if not span:
        return
    start=body.rfind('\n',0,span[0])+1
    header=body[start:span[1]-1].strip()
    header=re.sub(r'\b(?:static|inline)\s+', '', header)
    yield 'reuse owned helper '+name,body[:start]+'extern '+header+';\n'+body[span[2]+1:]


def split_helper_calls(body, name):
    """Separate inlined uses from calls to an already-owned out-of-line helper."""
    span=_function_body_span(body,name)
    if not span:
        return
    alias=name+'_inline'
    if re.search(r'\b'+re.escape(alias)+r'\b',body):
        return
    uses=list(re.finditer(r'\b'+re.escape(name)+r'(?=\s*\()',body[span[2]+1:]))
    if not 1<=len(uses)<=8:
        return
    start=body.rfind('\n',0,span[0])+1
    signature=body[start:span[1]-1].strip()
    signature=re.sub(r'\b(?:static|inline|extern)\s+','',signature)
    # Keep the original signature for external calls; the private copy is only
    # allowed to survive if the compiler inlines every selected use.
    for mask in range(1,1<<len(uses)):
        text=body
        for i,use in reversed(list(enumerate(uses))):
            if mask & (1<<i):
                a,b=span[2]+1+use.start(),span[2]+1+use.end()
                text=text[:a]+alias+text[b:]
        text=text[:span[0]]+alias+text[span[0]+len(name):]
        text=text[:start]+'extern '+signature+';\n'+text[start:]
        yield f'split inline/external helper {name} uses {mask:x}',text


def inline_helpers(body, name):
    """Do not emit unused out-of-line copies of reconstructed static helpers.

    A REL retains these copies even when the target function inlined every call.
    They shift its text and every dependent relocation despite an exact function diff.
    """
    pattern = re.compile(r'\bstatic\s+(?!inline\b)(?:'+TYPE+r')\s+(\w+)\s*\([^;{}]*\)\s*\{')
    sites = [m.start()+len('static ') for m in pattern.finditer(body) if m[1] != name]
    if len(sites)>1:
        text=body
        for at in reversed(sites):
            text=text[:at]+'inline '+text[at:]
        yield 'inline all static helpers',text
    for at in sites:
        yield 'inline helper at '+str(at), body[:at]+'inline '+body[at:]
    for definition in re.finditer(r'\bstatic\s+inline\s+(?:'+TYPE+r')\s+(\w+)\s*\([^;{}]*\)\s*\{',body):
        helper=definition[1]
        if helper==name:
            continue
        prototypes=list(re.finditer(r'(?m)^(?!static\b)(?:extern\s+)?(?:'+TYPE+r')\s+'+re.escape(helper)+r'\s*\([^;{}]*\);',body[:definition.start()]))
        if prototypes:
            text=body
            for m in reversed(prototypes):
                text=text[:m.start()]+'static inline '+re.sub(r'^extern\s+','',m[0])+text[m.end():]
            yield 'localize inline helper declaration '+helper,text
    # A recovered helper can also be a public definition already owned by
    # another TU. Keep its body available to the inliner without exporting it.
    pattern = re.compile(r'(?m)^(?!static\b|extern\b)(?:'+TYPE+r')\s+(\w+)\s*\([^;{}]*\)\s*\{')
    for match in pattern.finditer(body):
        if match[1] != name:
            yield 'internal inline helper '+match[1], body[:match.start()]+'static inline '+body[match.start():]
