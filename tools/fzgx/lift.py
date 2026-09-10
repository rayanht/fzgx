"""Mechanical C for straight-line functions: getters, setters, wrappers and short call-free
bodies, lifted from the retail disassembly. No model involved; the oracle verifies every
candidate and `fzgx trivial` submits the ones that match.

The lifter is a register-level symbolic evaluator over one basic block: constants, address
materialisation (lis/addi, @ha/@l), loads and stores by symbol or by base+offset (a struct
parameter), the common integer arithmetic, one call. Anything else makes it give up.
"""

from __future__ import annotations

import json
import re
from typing import Dict, List, Optional, Tuple

from .project import ROOT, Project

WIDTH = {"lwz": 4, "lhz": 2, "lha": 2, "lbz": 1, "lfs": 4, "lfd": 8, "stw": 4, "sth": 2, "stb": 1, "stfs": 4, "stfd": 8}
LOAD_T = {"lwz": "u32", "lhz": "u16", "lha": "s16", "lbz": "u8", "lfs": "f32", "lfd": "f64",
          "lwzu": "u32", "lhzu": "u16", "lbzu": "u8", "lfsu": "f32", "lfdu": "f64"}
STORE_T = {"stw": "u32", "sth": "u16", "stb": "u8", "stfs": "f32", "stfd": "f64"}
LABELS: List[Dict[str, int]] = [{}]
ARITY_HINT: List[Dict[str, int]] = [{}]        # callee -> widest integer-argument count (second run)
ARITY_SEEN: List[Dict[str, List[int]]] = [{}]  # filled by a run: what each site passed
FLOAT_CALLEES: List[set] = [set()]              # callees that took a float argument at some site
LINE_RE = re.compile(r"^[0-9A-Fa-f]+:\s*(\S+)\s*(.*)$")
MEM_RE = re.compile(r"^(-?0x[0-9a-f]+|-?\d+|[\w.]+@l|[\w.]+@sda21)\((r\d+)\)$")
COND = {"eq": "==", "ne": "!=", "lt": "<", "gt": ">", "le": "<=", "ge": ">="}
SAVE_RE = re.compile(r"^r(1[4-9]|2\d|3[01])$")  # callee-saved: their save/restore is frame noise


class Give(Exception):
    pass


def _imm(s: str) -> int:
    try:
        return int(s, 0)
    except ValueError:
        raise Give()  # a symbol where a number was expected: not this lifter's shape



def _hw_blocks():
    """Hardware register blocks by base address -> the link script's canonical absolute symbol
    (first name listed per address in config/<v>/ldscript.tpl)."""
    from . import oracle  # scoped: the template reader lives with the oracle
    out = {}
    for name, addr in oracle.abs_symbols().items():
        out.setdefault(addr, name)
    return out


HW_BLOCKS = _hw_blocks()

def integer_float_pairs(ins, labels):
    """Find conversion scratch stores by their reaching definitions, in either store order."""
    constants, stores, pairs, raw_reads = {}, {}, {}, set()
    boundaries = set(labels.values())
    for i, (mn, args) in enumerate(ins):
        if i in boundaries:
            constants.clear(); stores.clear()
        if mn.startswith('b'):
            constants.clear(); stores.clear()
            continue
        if not args:
            continue
        mem = MEM_RE.fullmatch(args[1]) if len(args) > 1 else None
        if mem and mem[2] == 'r1' and re.fullmatch(r'-?(?:0x[0-9a-f]+|\d+)', mem[1]):
            off = _imm(mem[1])
            if mn in STORE_T:
                width = WIDTH[mn]
                for byte in range(off, off + width):
                    stores.pop(byte, None)
                if mn == 'stw':
                    for byte in range(off, off + 4):
                        stores[byte] = (i, constants.get(args[0]) == 0x43300000, off)
            elif mn in LOAD_T:
                width = WIDTH.get(mn, WIDTH.get(mn[:-1]))
                if width is None:
                    continue
                high, low = stores.get(off), stores.get(off + 4)
                if mn == 'lfd' and high and low and high[1] and high[2] == off and low[2] == off + 4:
                    pairs[i] = (high[0], low[0])
                else:
                    raw_reads.update(stores[byte][0] for byte in range(off, off + width) if byte in stores)
        if mn == 'lis' and re.fullmatch(r'-?(?:0x[0-9a-f]+|\d+)', args[1]):
            constants[args[0]] = (_imm(args[1]) & 0xffff) << 16
        elif mn == 'mr' and args[1] in constants:
            constants[args[0]] = constants[args[1]]
        elif mn not in STORE_T and not mn.startswith(('st', 'cmp', 'mt')):
            constants.pop(args[0], None)
    return {load: pair for load, pair in pairs.items() if not raw_reads.intersection(pair)}


def lift(p: Project, module: str, name: str) -> Optional[str]:
    fa = p.function_asm(module).get(name)
    if fa is None:
        return None
    ins: List[Tuple[str, List[str]]] = []
    labels: Dict[str, int] = {}
    for ln in fa.asm:
        t = ln.strip()
        if t.startswith(".L_") and t.endswith(":"):
            labels[t[:-1]] = len(ins)  # index of the next instruction
            continue
        m = LINE_RE.match(t)
        if not m:
            continue
        mn, args = m.group(1), [a.strip() for a in m.group(2).split(",")] if m.group(2) else []
        ins.append((mn, args))
    LABELS[0] = labels
    if not ins or ins[-1][0] != "blr":
        return None
    # Calls return to the next instruction, including indirect calls through CTR. The inner
    # lifter validates their pointer and arguments, and the loop/branch shapes below.
    branches = [(i, mn, a) for i, (mn, a) in enumerate(ins) if mn.startswith("b") and mn not in ("bl", "bctrl", "blrl", "blr")]
    for i, mn, a in branches:
        if mn.endswith("lr") and mn[1:-2] in COND:
            continue
        if mn == "b" and a and a[-1].startswith(".L_") and labels.get(a[-1], -1) > i:
            continue  # a forward jump: the end of a then-block or a loop entry (checked when lifted)
        if mn == "bdnz":
            continue  # a counted loop: the struct-copy idiom explains it, or _lift gives up
        m = re.fullmatch(r"b(\w+)", mn)
        if not (m and m.group(1) in COND and a and a[-1].startswith(".L_")):
            return None
    if len(ins) > 160:
        return None
    try:
        ARITY_HINT[0] = {}; ARITY_SEEN[0] = {}; FLOAT_CALLEES[0] = set()
        try:
            text = _lift(p, module, name, ins)
        except (KeyError, IndexError, ValueError):
            return None  # the lifter lost track: no verified draft (the total draft still exists)
        # a callee whose sites disagree on the argument count gets the widest prototype, and
        # every narrower site passes what its argument register held (the source did)
        hint = {c: max(v) for c, v in ARITY_SEEN[0].items() if len(set(v)) > 1}
        if hint:
            ARITY_HINT[0] = hint
            try:
                ARITY_SEEN[0] = {}
                text = _lift(p, module, name, ins)
            except (KeyError, IndexError, ValueError):
                pass  # the first run's text stands
            finally:
                ARITY_HINT[0] = {}
            # sites that still disagree (no value to pad with): the callee is declared without
            # a prototype, which takes any count; only when no site passed a float (promotion)
            for c, v in ARITY_SEEN[0].items():
                if len(set(v)) > 1 and c not in FLOAT_CALLEES[0]:
                    text = re.sub(rf"^extern (\w[\w ]*?) {re.escape(c)}\([^)]*\);$", rf"extern \1 {c}();", text, flags=re.M)
        return text
    except Give:
        return None



def explain(p: Project, module: str, name: str) -> str:
    """Why `lift` declines a function: the control-flow filter, the size cap, a Give (with its
    message) or the exception the inner lifter raised (with its line)."""
    import traceback  # scoped: diagnostics only
    fa = p.function_asm(module).get(name)
    if fa is None:
        return "no disassembly"
    ins, labels = [], {}
    for ln in fa.asm:
        t = ln.strip()
        if t.startswith(".L_") and t.endswith(":"):
            labels[t[:-1]] = len(ins); continue
        m = LINE_RE.match(t)
        if m:
            ins.append((m.group(1), [a.strip() for a in m.group(2).split(",")] if m.group(2) else []))
    LABELS[0] = labels
    if not ins or ins[-1][0] != "blr":
        return "filter: no final blr" if ins else "filter: empty"
    for i, (mn, a) in enumerate(ins):
        if not mn.startswith("b") or mn in ("bl", "bctrl", "blrl", "blr"):
            continue
        if (mn.endswith("lr") and mn[1:-2] in COND) or mn == "bdnz":
            continue
        if mn == "b" and a and a[-1].startswith(".L_") and labels.get(a[-1], -1) > i:
            continue
        m = re.fullmatch(r"b(\w+)", mn)
        if not (m and m.group(1) in COND and a and a[-1].startswith(".L_")):
            return f"filter: control flow `{mn} {' '.join(a)}`"
    if len(ins) > 160:
        return "filter: over 160 instructions"
    ARITY_HINT[0] = {}; ARITY_SEEN[0] = {}; FLOAT_CALLEES[0] = set()
    try:
        _lift(p, module, name, ins)
        return "lifted"
    except Give as e:
        return f"give: {e}" if str(e) else "give: (no reason)"
    except Exception as e:
        tb = traceback.extract_tb(e.__traceback__)[-1]
        return f"{type(e).__name__} at lift.py:{tb.lineno}: {str(e)[:60]}"


def known_protos(p: Project, module: str = "main_rel") -> Dict[str, tuple]:
    """Signatures with transportable header/private type dependencies; unspecified lists stay unknown."""
    from .signatures import recovered
    index = recovered(p)
    out = {}
    for key, sig in index.signatures.items():
        sym = p.resolve(key)
        if sym and (sym.module == module or sym.name not in p.ambiguous_names()) and sig.args is not None:
            out[sym.name] = (sig.result, list(sig.args), sig.defined)
    return out


def lift_total(p: Project, module: str, name: str, max_ins: int = 1200) -> Optional[str]:
    """The draft that never gives up: every instruction the lifter cannot explain is a `???`
    marker and an unknown local. For large functions, where an agent edits rather than writes."""
    fa = p.function_asm(module).get(name)
    if fa is None:
        return None
    ins: List[Tuple[str, List[str]]] = []
    labels: Dict[str, int] = {}
    for ln in fa.asm:
        t = ln.strip()
        if t.startswith(".L_") and t.endswith(":"):
            labels[t[:-1]] = len(ins); continue
        m = LINE_RE.match(t)
        if m:
            ins.append((m.group(1), [a.strip() for a in m.group(2).split(",")] if m.group(2) else []))
    if not ins or len(ins) > max_ins:
        return None
    LABELS[0] = labels
    ARITY_HINT[0] = {}; ARITY_SEEN[0] = {}; FLOAT_CALLEES[0] = set()
    try:
        return _lift(p, module, name, ins, total=True)
    except Exception:
        return None


def skeleton(p: Project, module: str, name: str) -> Optional[str]:
    """What the lifter recovers before it gives up: declarations, layouts, locals, the leading
    statements, and a marker for what is left. For the agent's context when no full draft exists."""
    fa = p.function_asm(module).get(name)
    if fa is None:
        return None
    ins: List[Tuple[str, List[str]]] = []
    labels: Dict[str, int] = {}
    for ln in fa.asm:
        t = ln.strip()
        if t.startswith(".L_") and t.endswith(":"):
            labels[t[:-1]] = len(ins); continue
        m = LINE_RE.match(t)
        if m:
            ins.append((m.group(1), [a.strip() for a in m.group(2).split(",")] if m.group(2) else []))
    if not ins:
        return None
    LABELS[0] = labels
    try:
        text = _lift(p, module, name, ins, partial=True)
    except Give:
        return None
    except Exception:
        return None
    return text


def lift_variants(p: Project, module: str, name: str) -> List[str]:
    """Every spelling worth checking: with stack locals, MWCC's frame layout depends on the
    declaration order, so both plausible orders are candidates (the oracle picks)."""
    first = lift(p, module, name)
    if first is None:
        return []
    out = [first]
    fa = p.function_asm(module).get(name)
    ins: List[Tuple[str, List[str]]] = []
    for ln in fa.asm:
        t = ln.strip()
        if t.startswith(".L_"):
            continue
        m = LINE_RE.match(t)
        if m:
            ins.append((m.group(1), [a.strip() for a in m.group(2).split(",")] if m.group(2) else []))
    # the spellings the oracle must choose between: frame layout order, and whether a value
    # passed several times to one call goes through a temporary
    options = [("grouped", True), ("reverse", False), ("grouped", False)] if "/* frame */" in first else [("reverse", False)]
    for layout, site_temps in options:
        try:
            alt = _lift(p, module, name, ins, layout=layout, site_temps=site_temps)
        except Give:
            continue
        if alt and alt not in out:
            out.append(alt)
    return out


def _lift(p: Project, module: str, name: str, ins, layout: str = "reverse", site_temps: bool = True, partial: bool = False,
          total: bool = False) -> Optional[str]:
    syms = p.symbols(module)
    regs: Dict[str, str] = {}          # register -> C expression
    rtype: Dict[str, str] = {}         # register -> C type of the expression
    params: List[str] = []             # r3.. read before written
    def_idx: Dict[str, int] = {}       # register -> index of the instruction that last wrote it
    ptypes: Dict[str, str] = {}        # param register -> type
    fields: Dict[str, Dict[int, str]] = {}   # param register -> {offset: type} (struct parameter)
    stmts: List[str] = []
    externs: Dict[str, str] = {}
    calls: List[str] = []
    frame = False
    ret = None
    r3_set = [False]  # r3 written by this function (a returned parameter counts once a call intervened)

    def clobbered(r: str) -> bool:
        # written by an instruction before the current one (def_idx is set when an instruction
        # is entered, so the instruction's own write does not count against its reads)
        try:
            cur = i
        except NameError:
            cur = len(ins)
        return r in def_idx and def_idx[r] < cur

    def use(r: str) -> str:
        if r in regs:
            return regs[r]
        if re.fullmatch(r"r([3-9]|10)", r) or re.fullmatch(r"f[1-8]", r):
            # parameters are contiguous from r3 (or f1): reading r5 implies r3 and r4 exist
            n = int(r[1:])
            base = 3 if r.startswith("r") else 1
            for k in range(base, n + 1):
                rk = f"{r[0]}{k}"
                if rk not in params:
                    params.append(rk)
                    ptypes[rk] = "f32" if rk.startswith("f") else "u32"
                    if rk not in regs and not clobbered(rk):  # not already overwritten by this function
                        regs[rk] = f"arg{params.index(rk)}"
                        rtype[rk] = ptypes[rk]
            if r not in regs:
                if not clobbered(r):
                    # a parameter read again after a call cleared the caller-saved registers, or
                    # one first seen as a load base: the incoming argument, unchanged
                    regs[r] = f"arg{params.index(r)}"; rtype[r] = ptypes.get(r, "u32")
                else:
                    raise Give(f"{r} read after it was clobbered")
            return regs[r]
        if r == "r0":
            raise Give("r0 read before it was written")
        raise Give(f"{r} read before it was written")

    def sym_of(a: str) -> Optional[str]:
        m = re.match(r"^([\w.]+)(?:[+-]0x[0-9a-fA-F]+)?@(ha|h|l|sda21)$", a)
        return m.group(1) if m else None

    def sym_off(a: str) -> int:
        m = re.match(r"^[\w.]+([+-]0x[0-9a-fA-F]+)?@", a)
        return int(m.group(1), 16) if m and m.group(1) else 0

    gfields: Dict[str, Dict[int, str]] = {}   # global symbol -> {offset: type} accessed as a struct
    pfields: Dict[str, Dict[int, str]] = {}   # pointer global -> {offset: type} accessed through it
    ptr_globals: set = set()

    far: set = set()  # data symbols retail addresses with lis/addi: declared with unknown size so
                      # MWCC's -sdata threshold (DOL) cannot move them into small data

    def lookup(s: str):
        sd = syms.get(s)
        if sd is None:
            # dtk exports a TU-local symbol under its address-suffixed name; that is the name
            # the retail object relocates against, so it is the name the C must use
            m = re.match(r"^(.*)_[0-9A-F]{8}$", s)
            sd = syms.get(m.group(1)) if m else None
        if sd is None:
            sd = p.find_symbol(s)  # another module: a REL imports from main.rel and the DOL
        return sd

    def declare(s: str, t: str, far_ref: bool = False) -> None:
        sd = lookup(s)
        if sd is None:
            raise Give()
        if sd.kind == "function":
            signature = signature_index.get(sd.module, sd.name, signature_source)
            if signature:
                signatures_used[s] = signature
            externs.setdefault(s, signature.declaration(s) if signature else f"extern u32 {s}();")
        elif far_ref and module == "main":
            far.add(s)
            externs[s] = f"extern {t} {s}[];"
        else:
            externs.setdefault(s, f"extern {t} {s};")

    def ref(s: str) -> str:
        return f"{s}[0]" if s in far else s


    locals_: Dict[str, str] = {}  # local pointer name -> global symbol it points at
    by_addr = sorted((sd.addr, sd) for sd in syms.values() if sd.kind == "object" and sd.size) if module == "main" else []

    def symbol_at(addr: int):
        """(symbol, offset) of the data object containing an absolute address, or None."""
        import bisect
        i = bisect.bisect_right([a for a, _ in by_addr], addr) - 1
        if i >= 0:
            sd = by_addr[i][1]
            if sd.addr <= addr < sd.addr + sd.size:
                return sd, addr - sd.addr
        return None

    def rlwinm_expr(x: str, sh: int, mb: int, me: int) -> Optional[str]:
        """rotate-left-and-mask as C, when the rotate does not wrap through the mask."""
        if mb <= me:
            mask = ((0xFFFFFFFF >> mb) & (0xFFFFFFFF << (31 - me))) & 0xFFFFFFFF
        else:
            mask = ((0xFFFFFFFF >> mb) | (0xFFFFFFFF << (31 - me))) & 0xFFFFFFFF
        if sh == 0:
            return f"({x} & 0x{mask:X})"
        if mask & ((1 << sh) - 1) == 0:
            if mask == (0xFFFFFFFF << sh) & 0xFFFFFFFF:
                return f"({x} << {sh})"
            return f"(({x} << {sh}) & 0x{mask:X})"
        if mask < (1 << sh):
            if mask == (1 << sh) - 1:
                return f"((u32){x} >> {32 - sh})"
            return f"(((u32){x} >> {32 - sh}) & 0x{mask:X})"
        return None

    def raw_ok(addr: int) -> bool:
        """Memory no symbol names that the source addressed by number: the OS globals below the
        first DOL section, and the hardware registers (the lint allows both with a comment)."""
        return 0x80000000 <= addr < 0x80003100 or 0xCC000000 <= addr <= 0xCC00FFFF

    def const_of(b: str) -> Optional[int]:
        m = re.fullmatch(r"0x([0-9A-Fa-f]+)", b) or re.fullmatch(r"\((0x[0-9A-Fa-f]+) \+ (-?\d+)\)", b)
        if not m:
            return None
        return int(m.group(1), 16) + (int(m.group(2)) if m.lastindex and m.lastindex >= 2 else 0)

    def field_base(b: str, base_reg: str):
        """Where a base+offset access lands: ("param", reg) / ("global", sym, k) / ("ptr", name) / None."""
        if base_reg in params and re.fullmatch(r"arg\d+", b):
            return ("param", base_reg, 0)
        if b in locals_:
            return ("global", locals_[b], 0)
        m = re.fullmatch(r"&([A-Za-z_]\w*)", b)
        if m:
            return ("global", m.group(1), 0)
        m = re.fullmatch(r"\(\(u8 \*\)&([A-Za-z_]\w*) \+ (\d+)\)", b)
        if m:
            return ("global", m.group(1), int(m.group(2)))
        if re.fullmatch(r"[A-Za-z_]\w*", b) and b in externs:
            return ("ptr", b, 0)
        c = const_of(b)
        if c is not None:
            return ("abs", c, 0)
        return None

    def indexed_field(b: str, o: int, t: str) -> Optional[str]:
        """`(base + (idx << k))` / `(base + (idx * n))` with a displacement is an array field of the
        struct the base points to: `base->unk_K[idx]` (elements of the access width), or, when the
        stride is wider, an array of element structs `base->unk_K[idx].unk_o` whose fields collect
        across accesses. MWCC then emits the retail `add; load disp(r)` instead of an indexed load."""
        BASE = r"(arg\d+|p_[A-Za-z_]\w*|&[A-Za-z_]\w*|\(\(u8 \*\)&[A-Za-z_]\w* \+ \d+\)|\(\(u8 \*\)arg\d+ \+ \d+\)|\(\(u8 \*\)p_[A-Za-z_]\w* \+ \d+\))"
        IDX = r"\((.+?) (<<|\*) (\d+)\)"
        m = re.fullmatch(rf"\({BASE} \+ {IDX}\)", b) or re.fullmatch(rf"\(\(u8 \*\){BASE} \+ {IDX}\)", b)
        if m:
            bexpr, idx, op, n = m.groups()
        else:
            m = re.fullmatch(rf"\({IDX} \+ {BASE}\)", b)
            if not m:
                return None
            idx, op, n, bexpr = m.groups()
        stride = (1 << int(n)) if op == "<<" else int(n)
        w = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "f32": 4, "f64": 8}[t]
        if stride < w or o < 0:
            return None
        # a displacement beyond the stride puts the array further in: the element field is o mod
        # stride and the array starts stride*(o div stride) later (the address is the same)
        shift = (o // stride) * stride if o >= stride else 0
        o -= shift
        if o + w > stride:
            return None
        # the base: a global (with a constant offset K), a parameter, or a local pointer
        K = 0; tag = None
        mg = re.fullmatch(r"&([A-Za-z_]\w*)", bexpr) or re.fullmatch(r"\(\(u8 \*\)&([A-Za-z_]\w*) \+ (\d+)\)", bexpr)
        mp = re.fullmatch(r"(arg\d+|p_[A-Za-z_]\w*)", bexpr) or re.fullmatch(r"\(\(u8 \*\)(arg\d+|p_[A-Za-z_]\w*) \+ (\d+)\)", bexpr)
        if mg:
            gsym = mg.group(1); K = (int(mg.group(2)) if mg.lastindex and mg.lastindex >= 2 else 0) + shift
            declare(gsym, "struct", far_ref=True)
            tab = gfields.setdefault(gsym, {}); acc = f"{gsym}.unk_{K:X}"; tag = gsym
        elif mp:
            pname = mp.group(1); K = (int(mp.group(2)) if mp.lastindex and mp.lastindex >= 2 else 0) + shift
            if pname.startswith("arg"):
                k = int(pname[3:])
                if k >= len(params):
                    return None
                tab = fields.setdefault(params[k], {})
            elif pname in locals_:
                tab = gfields.setdefault(locals_[pname], {})
            else:
                return None
            acc = f"{pname}->unk_{K:X}"; tag = pname
        else:
            return None
        existing = tab.get(K)
        if existing is not None and not (str(existing).startswith("arr:") and str(existing).endswith(f":{stride}")):
            return None  # the offset is already a scalar field, or an array of another stride
        if stride == w and o == 0 and (existing is None or existing == f"arr:{t}:{stride}"):
            tab[K] = f"arr:{t}:{stride}"
            return f"{acc}[{idx}]"
        ename = f"{name}_{tag}_{K:X}_E{stride}"
        if existing is not None and existing != f"arr:struct {ename}:{stride}":
            return None
        elem = elem_fields.setdefault(ename, {"stride": stride, "fields": {}})
        if elem["fields"].get(o, t) != t:
            return None
        elem["fields"][o] = t
        tab[K] = f"arr:struct {ename}:{stride}"
        return f"{acc}[{idx}].unk_{o:X}"

    def elem_struct_texts() -> List[str]:
        out = []
        for ename, e in elem_fields.items():
            lines = [f"struct {ename} {{"]
            cur = 0
            for o in sorted(e["fields"]):
                if o > cur:
                    lines.append(f"    u8 pad_{cur:X}[0x{o - cur:X}];")
                t_ = e["fields"][o]
                lines.append(f"    {t_} unk_{o:X};")
                cur = o + {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "f32": 4, "f64": 8}[t_]
            if cur < e["stride"]:
                lines.append(f"    u8 pad_{cur:X}[0x{e['stride'] - cur:X}];")
            lines.append("};")
            out.append("\n".join(lines))
        return out

    elem_fields: Dict[str, dict] = {}

    hi: Dict[str, str] = {}  # register holding sym@ha
    labels = LABELS[0]
    frame_size = 0
    stwu_index = -1
    for j_, (mn_, a_) in enumerate(ins):
        if mn_ == "stwu" and a_ and a_[0] == "r1":
            m_ = re.match(r"^(-?0x[0-9a-f]+|-?\d+)\(r1\)$", a_[1])
            if m_:
                frame_size = -int(m_.group(1), 0); stwu_index = j_
            break
    saved_slots: set = set()
    seen_written: set = set()
    for mn_, a_ in ins:
        if mn_ == "stmw" and a_ and len(a_) >= 2:  # rN..r31 saved at consecutive slots
            m_ = re.match(r"^(-?0x[0-9a-f]+|-?\d+)\(r1\)$", a_[1])
            if m_:
                first = int(a_[0][1:]); base_ = int(m_.group(1), 0)
                for k_ in range(32 - first):
                    saved_slots.add(base_ + 4 * k_)
        # a callee-saved register's prologue save: stored before the function writes it
        if mn_ in ("stw", "stfd", "psq_st") and a_ and (SAVE_RE.match(a_[0]) or re.fullmatch(r"f(1[4-9]|2\d|3[01])", a_[0])) and "(r1)" in a_[1] and a_[0] not in seen_written:
            m_ = re.match(r"^(-?0x[0-9a-f]+|-?\d+)\(r1\)$", a_[1])
            if m_:
                saved_slots.add(int(m_.group(1), 0))
        if a_ and mn_ not in STORE_T and not mn_.startswith(("st", "cmp", "b")) and mn_ not in ("mtlr", "mtspr", "mtctr"):
            seen_written.add(a_[0])
    slocals: Dict[int, Dict[str, object]] = {}  # frame offset -> {"w": width or 0 (address only), "t": type}
    # struct copies through the count register: recognised up front so their address setup
    # (dst-4 / src-4) is not mistaken for locals or pointer arithmetic
    copies: Dict[int, Tuple[int, str, str, int]] = {}  # mtctr index -> (K, rD, rS, bdnz index)
    copy_addresses = {}  # address setup index -> (destination register, base register, byte offset)
    for j_, (mn_, a_) in enumerate(ins):
        if mn_ == "mtctr" and a_:
            li_ = next((x for x in range(j_ - 1, max(-1, j_ - 6), -1) if ins[x][0] == "li" and ins[x][1][0] == a_[0]), None)
            body_ = ins[j_ + 1:j_ + 6]
            if li_ is not None and len(body_) == 5 and [m for m, _ in body_] == ["lwz", "lwzu", "stw", "stwu", "bdnz"]:
                (l1, l2, s1, s2, _) = body_
                rS = re.search(r"\((r\d+)\)$", l1[1][1]).group(1); rD = re.search(r"\((r\d+)\)$", s1[1][1]).group(1)
                if l1[1][1].startswith("0x4(") and l2[1][1].startswith("0x8(") and s1[1][1].startswith("0x4(") and s2[1][1].startswith("0x8("):
                    setups = []
                    for reg in (rD, rS):
                        setup = next((x for x in range(j_ - 1, max(-1, j_ - 12), -1)
                                      if ins[x][1] and ins[x][1][0] == reg
                                      and ins[x][0] not in STORE_T), None)
                        if setup is None:
                            break
                        sm, sa = ins[setup]
                        if sm not in ('addi', 'subi') or not re.fullmatch(r'-?(?:0x[0-9a-f]+|\d+)', sa[2]):
                            break
                        setups.append((setup, (reg, sa[1], _imm(sa[2]) * (-1 if sm == 'subi' else 1) + 4)))
                    if len(setups) == 2:
                        copies[j_] = (_imm(ins[li_][1][1]), rD, rS, j_ + 5)
                        copy_addresses.update(setups)
    struct_syms = {sym_of(a_[2]) for mn_, a_ in ins if mn_ == "addi" and len(a_) == 3 and sym_of(a_[2]) and not a_[1] == "r1"}
    copy_dst_locals: Dict[int, int] = {}  # frame offset of a copied-into local -> size
    for ctr, (K, rD, rS, end_) in copies.items():
        setup = max((i for i, (reg, _, _) in copy_addresses.items() if i < ctr and reg == rD), default=None)
        if setup is not None:
            _, base, offset = copy_addresses[setup]
            if base == 'r1':
                copy_dst_locals[offset] = 8 * K
    taken = sorted({_imm(a_[2]) for j_, (mn_, a_) in enumerate(ins)
                    if mn_ == "addi" and len(a_) == 3 and a_[1] == "r1"
                    and a_[0] != 'r11' and j_ not in copy_addresses} | set(copy_dst_locals))
    top_of_locals = min(saved_slots) if saved_slots else frame_size

    def owner(off: int):
        """The address-taken local whose extent covers `off`, and the offset inside it."""
        for i_, t_ in enumerate(taken):
            end = taken[i_ + 1] if i_ + 1 < len(taken) else top_of_locals
            if t_ <= off < end:
                return t_, off - t_
        return None

    local_accesses = {}

    def local_at(off: int, w: int, t: str) -> str:
        own = owner(off)
        if own is not None:
            base_off, inner = own
            ent = slocals.setdefault(base_off, {"w": 0, "t": "u8", "addr": True, "elems": {}})
            if w and not ent["w"]:
                ent["w"] = w; ent["t"] = t
            ent.setdefault("elems", {})[inner] = (w, t)
            ew = ent["w"] or w or 1
            i_ = taken.index(base_off)
            extent = (taken[i_ + 1] if i_ + 1 < len(taken) else top_of_locals) - base_off
            if extent <= ew:
                expression = f"loc_{base_off:X}"
            elif extent >= 16:
                ent["wrapped"] = max(extent // ew, 1)
                expression = f"loc_{base_off:X}.a[{inner // ew}]" if inner % ew == 0 else f"*({t} *)((u8 *)&loc_{base_off:X} + {inner})"
            else:
                ent["array"] = max(extent // ew, 1)
                expression = f"loc_{base_off:X}[{inner // ew}]" if inner % ew == 0 else f"*({t} *)((u8 *)loc_{base_off:X} + {inner})"
            if w:
                token = f"__FRAME_{base_off:X}_{inner:X}_{t}__"
                if t != ent["t"]:
                    expression = f"*({t} *)((u8 *)&loc_{base_off:X} + {inner})"
                local_accesses[token] = (base_off, inner, t, expression)
                return token
            return expression
        ent = slocals.setdefault(off, {"w": 0, "t": "u8", "addr": False, "elems": {}})
        if w and not ent["w"]:
            ent["w"] = w; ent["t"] = t
        if w and ent["w"] == w and t != ent["t"] and (t.startswith("f") != ent["t"].startswith("f")):
            return f"(*({t} *)&loc_{off:X})"  # the bits of a float read as an integer, or the reverse
        return f"loc_{off:X}"
    temps: List[str] = []
    written_since_call: set = set()
    variadic_next = [False]
    copy_types: set = set()

    def inline_copy_at(i0: int):
        """A run of `lwz rX, k+4j(rS)` / `stw rX, k'+4j(rD)` over consecutive words, in ordinal
        order (MWCC's small struct assignment): (end index exclusive, words, rS, k, rD, k')."""
        mn0, a0 = ins[i0]
        if mn0 != "lwz" or not a0 or len(a0) < 2:
            return None
        m0 = MEM_RE.match(a0[1])
        if not m0 or m0.group(1).endswith(("@l", "@sda21", "@ha")):
            return None
        rS = m0.group(2); k = _imm(m0.group(1))
        loads: List[Tuple[str, int]] = []   # (reg, ordinal)
        stores = 0; rD = None; kD = None
        x = i0
        while x < len(ins):
            mn_, a_ = ins[x]
            if mn_ == "lwz" and a_ and len(a_) >= 2:
                m_ = MEM_RE.match(a_[1])
                if not m_ or m_.group(2) != rS or m_.group(1).endswith(("@l", "@sda21", "@ha")):
                    break
                if _imm(m_.group(1)) != k + 4 * len(loads):
                    break
                loads.append((a_[0], len(loads))); x += 1; continue
            if mn_ == "stw" and a_ and len(a_) >= 2:
                m_ = MEM_RE.match(a_[1])
                if not m_ or m_.group(1).endswith(("@l", "@sda21", "@ha")):
                    break
                if rD is None:
                    rD = m_.group(2); kD = _imm(m_.group(1))
                    if rD == rS:
                        break
                if m_.group(2) != rD or _imm(m_.group(1)) != kD + 4 * stores:
                    break
                if stores >= len(loads) or loads[stores][0] != a_[0]:
                    break
                stores += 1; x += 1
                if stores == len(loads) and (x >= len(ins) or ins[x][0] != "lwz"):
                    break
                continue
            break
        if rD is None or stores < 2 or stores != len(loads):
            return None
        # the loaded registers are dead after the run
        for r_, _ in loads:
            if x < len(ins) and reads(x, r_):
                return None
        return x, stores, rS, k, rD, kD

    inline_copies: Dict[int, tuple] = {}

    def scan_inline_copies() -> None:  # after `reads` exists (it is defined further down)
        _x = 0
        while _x < len(ins):
            _c = inline_copy_at(_x)
            if _c:
                inline_copies[_x] = _c; _x = _c[0]
            else:
                _x += 1
        inline_copies.setdefault(-1, ())
    magic_div: Dict[str, Tuple[str, int]] = {}  # register holding mulhwu(x, magic) -> (x, magic)
    pending_div: Dict[int, Tuple[str, str]] = {}  # index of the idiom's last instruction -> (register, quotient expression)
    int_float_loads = integer_float_pairs(ins, LABELS[0])
    int_float_stores = {store for pair in int_float_loads.values() for store in pair}
    int_float_values = {}
    conv_slots: Dict[int, Tuple[str, Optional[str]]] = {}  # stack slot -> int/float conversion in progress

    def divisor_of(magic: int, post_shift: int, add: bool) -> Optional[int]:
        """The d for which MWCC's magicu(d) is (magic, add, post_shift): search small divisors."""
        for d in range(2, 1 << 20):
            # Hacker's Delight magicu
            nc = (1 << 32) - 1 - (((1 << 32) - d) % d)
            p_ = 31; q1 = (1 << 31) // nc; r1 = (1 << 31) - q1 * nc; q2 = ((1 << 31) - 1) // d; r2 = ((1 << 31) - 1) - q2 * d
            a_ = False
            while True:
                p_ += 1
                if r1 >= nc - r1:
                    q1 = 2 * q1 + 1; r1 = 2 * r1 - nc
                else:
                    q1 = 2 * q1; r1 = 2 * r1
                if r2 + 1 >= d - r2:
                    if q2 >= (1 << 31) - 1: a_ = True
                    q2 = 2 * q2 + 1; r2 = 2 * r2 + 1 - d
                else:
                    if q2 >= (1 << 31): a_ = True
                    q2 = 2 * q2; r2 = 2 * r2 + 1
                delta = d - 1 - r2
                if not (p_ < 64 and (q1 < delta or (q1 == delta and r1 == 0))):
                    break
            M = (q2 + 1) & 0xFFFFFFFF; sh = p_ - 32
            if M == magic and a_ == add and sh == post_shift:
                return d
            if d > 4096 and d % 1000 != 0:
                continue
        return None
    pending_ptr: Dict[str, str] = {}

    class _Stmts(list):
        def append(self, st):
            for ln_, asg in list(pending_ptr.items()):
                if re.search(rf"\b{re.escape(ln_)}\b", st) and st != asg:
                    del pending_ptr[ln_]; super().append(asg)
            # an address assigned to an integer temporary is cast (temporaries are integers unless
            # they hold a struct pointer, see the declarations)
            m_ = re.fullmatch(r"(v\d+) = (\(\(u8 \*\).*|\(u8 \*\).*|&[A-Za-z_]\w*.*);", st)
            if m_:
                st = f"{m_.group(1)} = (u32){m_.group(2)};"
            super().append(st)
    stmts = _Stmts(stmts)
    fnames_seen: set = set()
    array_locals: set = set()

    def reads(idx: int, r: str) -> bool:
        """Is register r read at instruction idx (before being written there)?"""
        mn_, a_ = ins[idx]
        if not a_:
            return False
        srcs = a_[1:] if mn_ not in STORE_T and mn_ not in ("mtlr", "mtctr") and not mn_.startswith(("st", "cmp")) else a_
        return any(re.search(rf"\b{r}\b", x) for x in srcs)

    def read_later(idx: int, r: str) -> bool:
        """Is r read after instruction idx before being written again (a call reads r3..r10)?"""
        for j in range(idx + 1, len(ins)):
            mn_, a_ = ins[j]
            if reads(j, r):
                return True
            if mn_ in ("bl", "bctrl", "blrl"):
                sig = signature_index.get(module, a_[0], signature_source) if mn_ == 'bl' and a_ else None
                slots = signature_index.registers(sig) if sig else None
                if slots is not None and re.fullmatch(r"r([0-9]|1[0-2])|f(\d|1[0-3])", r):
                    return r in {reg for reg, _ in slots}
                if re.fullmatch(r"r([3-9]|10)|f([1-8])", r):
                    return True
                if re.fullmatch(r"r([0-9]|1[0-2])|f(\d|1[0-3])", r):
                    return False
            if mn_ == "blr":
                return r in ("r3", "f1")
            if a_ and a_[0] == r and mn_ not in STORE_T and not mn_.startswith(("st", "cmp")):
                return False
        return False

    def reused_after_store(idx: int, r: str, mem: str) -> bool:
        """After instruction idx, is there a store to `mem` followed by a read of r, with no
        write of r in between? Then the source kept the loaded value in a local."""
        stored = False
        for j in range(idx + 1, len(ins)):
            mn_, a_ = ins[j]
            if mn_ in STORE_T and len(a_) > 1 and a_[1] == mem:
                stored = True
                continue
            if stored and reads(j, r):
                return True
            if mn_ in ("bl", "bctrl", "blrl"):
                if stored and re.fullmatch(r"r([3-9]|10)", r):
                    return True  # an argument register at a call is read by the callee
                if re.fullmatch(r"r([0-9]|1[0-2])", r):
                    return False
            if a_ and a_[0] == r and mn_ not in STORE_T and not mn_.startswith(("st", "cmp")):
                return False  # r written again
        return False
    cond: Optional[Tuple[str, str, bool]] = None  # (lhs, rhs, unsigned) of the last compare
    open_ifs: List[Tuple[int, str]] = []          # (instruction index where a block closes, text to emit)
    skip: set = set()                             # instruction indices consumed by the structure (the `b` of a then-block)
    i = -1
    gave_at: Optional[int] = None
    gave_why = ""
    unknown_count = [0]
    from .signatures import recovered
    signature_index = recovered(p)
    signature_source = None
    from .signatures import propagate
    tus = p.module_config_dir(module) / "tus.json"
    if tus.exists():
        tu = next((tu for tu in json.loads(tus.read_text())["tus"] if name in tu["functions"]), None)
        if tu:
            signature_source = p.module_src_prefix(module) + '/' + tu['file']
            signature_index = propagate(signature_index, module, tu["functions"])
    signatures_used = {}
    own_signature = signature_index.get(module, name)
    own_slots = signature_index.registers(own_signature) if own_signature else None
    if own_slots:
        signatures_used[name] = own_signature
        for reg, typ in own_slots:
            params.append(reg); ptypes[reg] = typ
            regs[reg] = f"arg{len(params) - 1}"; rtype[reg] = typ
    call_types = []

    def typed_access(base, offset, access):
        typ = rtype.get(base, "")
        member = signature_index.member(typ, offset, access)
        if member:
            field, field_type = member
            return f"({use(base)})->{field}", field_type
        if signature_index.category(typ) == "pointer" and typ != "void *":
            return f"*({access} *)((u8 *){use(base)} + {offset})", access
        return None
    void_calls: set = set()
    temps_written: List[Tuple[str, int]] = []
    carried: Dict[str, str] = {}     # register -> local name while inside a loop region
    loop_regions: List[Tuple[int, int, int]] = []  # (body_start, test_start, backbranch_index)
    for j_, (mn_, a_) in enumerate(ins):
        if mn_ == "b" and a_ and a_[-1].startswith(".L_"):
            tst = labels.get(a_[-1], -1)
            if tst > j_:
                # the back branch: the first conditional branch at/after the test that targets j_+1
                for k_ in range(tst, len(ins)):
                    m_ = re.fullmatch(r"b(\w+)", ins[k_][0])
                    if m_ and m_.group(1) in COND and ins[k_][1] and labels.get(ins[k_][1][-1]) == j_ + 1:
                        loop_regions.append((j_ + 1, tst, k_)); break
    loop_by_entry = {b - 1: (b, t, k) for b, t, k in loop_regions}
    loop_end_by_index = {k: (b, t, k) for b, t, k in loop_regions}
    in_loop: List[Tuple[int, int, int]] = []
    # do-while: a backward conditional branch no entry jump explained; the test is the run of
    # compares (and sign extensions) just before it
    dowhile_by_entry: Dict[int, Tuple[int, int, int]] = {}
    dowhile_test: Dict[int, Tuple[int, int, int]] = {}
    ctr_loops: Dict[int, Tuple[int, int]] = {}  # mtctr index -> (body start, bdnz index)
    ctr_guarded: set = set()
    else_state: Dict[int, Tuple[dict, dict]] = {}
    for k_, (mn_, a_) in enumerate(ins):
        m_ = re.fullmatch(r"b(\w+)", mn_)
        if mn_ == "bdnz" and a_ and a_[-1].startswith(".L_"):
            t_ = labels.get(a_[-1])
            if t_ is not None and t_ <= k_:
                mt = next((x for x in range(t_ - 1, max(-1, t_ - 4), -1) if ins[x][0] == "mtctr"), None)
                if mt is not None and mt not in copies and not any(mt == li for li in copies):
                    ctr_loops[mt] = (t_, k_)
                    # `cmplwi n, 0; beq end` just before or just after the mtctr: the guard of an
                    # up-counting for loop
                    for x in list(range(max(0, mt - 3), mt)) + list(range(mt + 1, min(t_, mt + 3))):
                        if ins[x][0] in ("cmplwi", "cmpwi") and ins[x][1][0] == ins[mt][1][0] and _imm(ins[x][1][1]) == 0 \
                                and x + 1 < len(ins) and ins[x + 1][0] == "beq" and labels.get(ins[x + 1][1][-1], -1) > k_:
                            skip.add(x); skip.add(x + 1); ctr_guarded.add(mt)
            continue
        if not (m_ and m_.group(1) in COND and a_ and a_[-1].startswith(".L_")):
            continue
        t_ = labels.get(a_[-1])
        if t_ is None or t_ > k_ or k_ in loop_end_by_index:
            continue
        ts = k_
        while ts - 1 > t_ and ins[ts - 1][0] in ("cmpwi", "cmpw", "cmplwi", "cmplw", "extsb", "extsh", "andi.", "subi", "addi", "srwi", "srawi", "clrlwi") \
                and not (ins[ts - 1][0] in ("subi", "addi", "srwi", "srawi", "clrlwi") and ts - 2 > t_ and ins[ts - 2][0] not in ("cmpwi", "cmpw", "cmplwi", "cmplw", "andi.", "subi", "addi", "srwi", "srawi", "clrlwi", "extsb", "extsh")):
            ts -= 1
        if ts == k_:
            continue  # no compare feeds the branch: a record-form test, not lifted here
        dowhile_by_entry[t_] = (t_, ts, k_)
        dowhile_test[ts] = (t_, ts, k_)
    ctr_expr: List[Optional[str]] = [None]
    lr_expr: List[Optional[str]] = [None]
    fn_typedefs: List[str] = []

    # ---- structured control flow, discovered up front ---------------------------------------
    loop_branches = {k for _, _, k in loop_regions} | {k for _, _, k in dowhile_by_entry.values()} | {k for _, k in ctr_loops.values()}
    BCOND_RE = re.compile(r"b(eq|ne|lt|gt|le|ge)$")

    def _ranges_op(ranges, op, K, uns):
        """Split value ranges by a compare with K: (taken, rest); None bounds are unbounded."""
        def inter(r, lo, hi):
            a_, b_ = r
            lo2 = a_ if lo is None else (lo if a_ is None else max(a_, lo))
            hi2 = b_ if hi is None else (hi if b_ is None else min(b_, hi))
            if lo2 is not None and hi2 is not None and lo2 > hi2:
                return None
            return (lo2, hi2)
        def cut(rs, lo, hi):
            return [x for x in (inter(r, lo, hi) for r in rs) if x is not None]
        if op == "eq":
            taken = cut(ranges, K, K); rest = cut(ranges, None, K - 1) + cut(ranges, K + 1, None)
        elif op == "ne":
            rest = cut(ranges, K, K); taken = cut(ranges, None, K - 1) + cut(ranges, K + 1, None)
        elif op == "lt":
            taken = cut(ranges, None, K - 1); rest = cut(ranges, K, None)
        elif op == "le":
            taken = cut(ranges, None, K); rest = cut(ranges, K + 1, None)
        elif op == "gt":
            taken = cut(ranges, K + 1, None); rest = cut(ranges, None, K)
        else:  # ge
            taken = cut(ranges, K, None); rest = cut(ranges, None, K - 1)
        if uns:
            taken = cut(taken, 0, None); rest = cut(rest, 0, None)
        return taken, rest

    def switch_tree(j: int):
        """A compare tree on one register with constant cases (MWCC's small switch): the tree's
        instruction indices, {leaf index: ranges}, and whether the compares are unsigned."""
        mn0, a0 = ins[j]
        if mn0 not in ("cmpwi", "cmplwi") or not a0 or j + 1 >= len(ins) or not BCOND_RE.match(ins[j + 1][0]):
            return None
        reg = a0[0]; uns = mn0 == "cmplwi"
        tree: set = set(); leaves: Dict[int, list] = {}
        def walk(idx: int, ranges) -> bool:
            guard = 0
            while ranges and guard < 64:
                guard += 1
                if idx >= len(ins) or idx in tree and idx != j:
                    return False
                mn_, a_ = ins[idx]
                if mn_ in ("cmpwi", "cmplwi") and a_ and a_[0] == reg and idx + 1 < len(ins) and BCOND_RE.match(ins[idx + 1][0]):
                    if (mn_ == "cmplwi") != uns:
                        return False
                    K = _imm(a_[1]); tree.add(idx); idx += 1
                    while idx < len(ins) and BCOND_RE.match(ins[idx][0]) and ins[idx][1] and ins[idx][1][-1].startswith(".L_"):
                        op = ins[idx][0][1:]; tgt = labels.get(ins[idx][1][-1])
                        if tgt is None or tgt <= idx:
                            return False
                        tree.add(idx); idx += 1
                        taken, rest = _ranges_op(ranges, op, K, uns)
                        if taken and not walk(tgt, taken):
                            return False
                        ranges = rest
                        if not ranges:
                            return True
                    continue
                if mn_ == "b" and a_ and a_[-1].startswith(".L_"):
                    tgt = labels.get(a_[-1])
                    if tgt is None or tgt <= idx:
                        return False
                    tree.add(idx); idx = tgt; continue
                leaves.setdefault(idx, []).extend(ranges); return True
            return not ranges
        if not walk(j, [(None, None)]):
            return None
        if len(leaves) < 3 or len(tree) < 3:
            return None
        return tree, leaves, uns, reg

    switch_at: Dict[int, dict] = {}
    switch_tree_idx: set = set()
    for j in range(len(ins)):
        if j in switch_tree_idx or j in loop_branches:
            continue
        st = switch_tree(j)
        if st is None:
            continue
        tree, leaves, uns, reg = st
        tree_end = max(tree) + 1
        labels_sorted = sorted(leaves)
        if labels_sorted[0] < tree_end or any(x >= labels_sorted[0] for x in tree):
            continue
        # bodies are laid out one after another; the join is where the first `b` out of a body goes
        join = None
        bodies_ok = True
        for bi, L in enumerate(labels_sorted):
            end = labels_sorted[bi + 1] if bi + 1 < len(labels_sorted) else None
            if end is None:
                continue
            last = ins[end - 1]
            if last[0] == "b" and last[1] and last[1][-1].startswith(".L_"):
                t_ = labels.get(last[1][-1], -1)
                if join is None:
                    join = t_
                elif t_ != join:
                    bodies_ok = False; break
            elif last[0] not in ("blr",):
                pass  # falls through into the next case (C allows it)
        if not bodies_ok:
            continue
        last_label = labels_sorted[-1]
        if join is None:
            # every body returns or falls through: the join is the end of the last body
            continue
        if join <= last_label:
            # the last leaf is the join itself: an empty default
            if last_label != join:
                continue
        cases: Dict[int, List[int]] = {}
        default = None
        bad = False
        for L, rs in leaves.items():
            vals = []
            for lo_, hi_ in rs:
                if lo_ is None or hi_ is None or hi_ - lo_ > 8:
                    vals = None; break
                vals += list(range(lo_, hi_ + 1))
            if vals is None:
                if default is not None and default != L:
                    bad = True; break
                default = L
            else:
                cases[L] = sorted(set(cases.get(L, []) + vals))
        if bad or not cases:
            continue
        if default is not None and default == join:
            default = None
        switch_at[j] = {"tree": tree, "cases": cases, "default": default, "join": join, "reg": reg, "uns": uns,
                        "labels": labels_sorted}
        switch_tree_idx |= tree

    # short-circuit chains: consecutive conditional branches whose targets are one else label E
    # or the then-block right after the run; `a && (b || c)` in the source
    CHAIN_OK = ("cmpwi", "cmpw", "cmplwi", "cmplw", "extsb", "extsh", "lwz", "lhz", "lha", "lbz", "lfs", "lfd", "rlwinm", "rlwinm.",
                "andi.", "clrlwi", "clrlwi.", "srwi", "srawi", "slwi", "mr", "mr.", "li", "lis", "addi", "and", "or", "xor", "not", "neg",
                "extrwi", "extrwi.", "fcmpo", "fcmpu", "cntlzw", "subf", "add")
    chain_mid: Dict[int, int] = {}    # branch index -> chain id
    chain_last: Dict[int, dict] = {}  # last branch index -> {"id", "E", "then", "fall_b"}
    bconds = [x for x in range(len(ins)) if BCOND_RE.match(ins[x][0]) and ins[x][1] and ins[x][1][-1].startswith(".L_")
              and x not in switch_tree_idx and x not in loop_branches and labels.get(ins[x][1][-1], -1) > x]
    used_in_chain: set = set()
    cid = 0
    for start in bconds:
        if start in used_in_chain:
            continue
        run = [start]
        x = start + 1
        while x < len(ins):
            if x in bconds and x not in used_in_chain:
                run.append(x); x += 1; continue
            if ins[x][0] in CHAIN_OK and ins[x][1] and not ins[x][1][-1].startswith(".L_"):
                x += 1; continue
            if ins[x][0] == "bl" and ins[x][1] and not re.fullmatch(r"_(save|rest)(gpr|fpr)_\d+", ins[x][1][0]):
                # a call in a condition: its result must be what the next compare tests
                y = x + 1
                while y < len(ins) and ins[y][0] in ("extsb", "extsh", "clrlwi", "rlwinm", "srwi"):
                    y += 1
                if y < len(ins) and ins[y][0] in ("cmpwi", "cmpw", "cmplwi", "cmplw", "andi.", "clrlwi.", "rlwinm.", "extsb.", "mr.") and ins[y][1] and ins[y][1][-1 if ins[y][0] == "mr." else 0] == "r3" or (y < len(ins) and ins[y][0] == "mr." and ins[y][1][1] == "r3"):
                    x += 1; continue
                if y < len(ins) and ins[y][0] in ("cmpwi", "cmplwi", "cmpw", "cmplw") and ins[y][1][0] == "r3":
                    x += 1; continue
            break
        # the longest prefix of at least two branches that reads as one condition
        best = None
        for n in range(len(run), 1, -1):
            br = run[:n]
            after = br[-1] + 1
            fall_b = None
            then_idx = after
            if after < len(ins) and ins[after][0] == "b" and ins[after][1] and ins[after][1][-1].startswith(".L_") and labels.get(ins[after][1][-1], -1) > after:
                fall_b = after; then_idx = after + 1
            targets = [labels[ins[b][1][-1]] for b in br]
            E_cands = {t for t in targets if t != then_idx}
            if fall_b is not None:
                E_cands.add(labels[ins[fall_b][1][-1]])
            if len(E_cands) != 1:
                continue
            E = next(iter(E_cands))
            if E <= then_idx:
                continue
            if any(ins[j][0] in LOAD_T and read_later(after - 1, ins[j][1][0])
                   for j in range(br[0] + 1, br[-1])):
                continue  # A loaded value reused by the body must stay behind its guard.
            if all(t == E for t in targets) and fall_b is None and n < 2:
                continue
            # the then block must not be jumped into from inside the run except at its start
            best = (br, E, then_idx, fall_b); break
        if best is None:
            continue
        br, E, then_idx, fall_b = best
        cid += 1
        for b in br[:-1]:
            chain_mid[b] = cid
        chain_last[br[-1]] = {"id": cid, "E": E, "then": then_idx, "fall_b": fall_b}
        used_in_chain.update(br)
        if fall_b is not None:
            skip.add(fall_b)
    chain_cmp_idx: set = set()
    for b_last, ch in chain_last.items():
        b_first = min([b for b, c in chain_mid.items() if c == ch["id"]] + [b_last])
        chain_cmp_idx.update(range(b_first, b_last + 1))
    chain_terms: Dict[int, list] = {}
    case_labels: Dict[int, str] = {}
    switch_breaks: set = set()
    switch_state: Dict[int, Tuple[dict, dict]] = {}

    UNKNOWN = ("?", "?")

    def test_step(mn_x: str, a_x: List[str], cur_cond):
        """One instruction of a loop test: compares set the condition, the rest update regs.
        Returns the condition (lhs, rhs) or the previous one; UNKNOWN when the shape is unknown."""
        if mn_x in ("cmpwi", "cmpw", "cmplwi", "cmplw"):
            lhs = use(a_x[0]); rhs = str(_imm(a_x[1])) if mn_x.endswith("i") else use(a_x[1])
            uns = mn_x.startswith("cmpl")
            tt = rtype.get(a_x[0], "u32")
            if uns and tt not in ("u32", "u16", "u8"):
                lhs = f"(u32){lhs}"
            elif not uns and tt not in ("s32", "s16", "s8"):
                lhs = f"(s32){lhs}"
            if not mn_x.endswith("i"):
                tr = rtype.get(a_x[1], "u32")
                if uns and tr not in ("u32", "u16", "u8"):
                    rhs = f"(u32){rhs}"
                elif not uns and tr not in ("s32", "s16", "s8"):
                    rhs = f"(s32){rhs}"
            return (lhs, rhs)
        if mn_x == "extsb":
            regs[a_x[0]] = f"(s8){use(a_x[1])}"; rtype[a_x[0]] = "s8"; return cur_cond
        if mn_x == "extsh":
            regs[a_x[0]] = f"(s16){use(a_x[1])}"; rtype[a_x[0]] = "s16"; return cur_cond
        if mn_x == "andi.":
            regs[a_x[0]] = f"({use(a_x[1])} & {_imm(a_x[2])})"; rtype[a_x[0]] = "u32"; return (regs[a_x[0]], "0")
        if mn_x in ("subi", "addi"):
            base = use(a_x[1])
            typ = rtype.get(a_x[1], 'u32')
            if signature_index.category(typ) == 'pointer':
                base = f'(u8 *){base}'; typ = 'void *'
            regs[a_x[0]] = f"({base} {'-' if mn_x == 'subi' else '+'} {_imm(a_x[2])})"; rtype[a_x[0]] = typ; return cur_cond
        if mn_x == "mr":
            regs[a_x[0]] = use(a_x[1]); rtype[a_x[0]] = rtype.get(a_x[1], "u32"); return cur_cond
        if mn_x == "srwi":
            regs[a_x[0]] = f"((u32){use(a_x[1])} >> {_imm(a_x[2])})"; rtype[a_x[0]] = "u32"; return cur_cond
        if mn_x == "srawi":
            regs[a_x[0]] = f"((s32){use(a_x[1])} >> {_imm(a_x[2])})"; rtype[a_x[0]] = "s32"; return cur_cond
        if mn_x == "clrlwi":
            n_ = 32 - _imm(a_x[2]); regs[a_x[0]] = f"({use(a_x[1])} & 0x{(1 << n_) - 1:X})"; rtype[a_x[0]] = "u32"; return cur_cond
        if mn_x in LOAD_T and a_x and not a_x[1].endswith("(r1)") and not mn_x.endswith("u"):
            e_ = load_expr(mn_x, a_x)
            if e_ is None:
                return UNKNOWN
            regs[a_x[0]] = e_; rtype[a_x[0]] = LOAD_T[mn_x]; return cur_cond
        return UNKNOWN

    def load_expr(mn_x: str, a_x: List[str]) -> Optional[str]:
        """The value of a plain load as an expression (fields registered), for loop tests."""
        m_ = MEM_RE.match(a_x[1])
        if not m_:
            return None
        off, base = m_.group(1), m_.group(2)
        t = LOAD_T[mn_x]
        if off.endswith("@sda21"):
            s_ = sym_of(off); so = sym_off(off)
            if so:
                declare(s_, "struct"); gfields.setdefault(s_, {})[so] = t; return f"{s_}.unk_{so:X}"
            declare(s_, t); return s_
        if off.endswith("@l") and base in hi:
            s_ = hi[base]; so = sym_off(off)
            declare(s_, "struct", far_ref=True); gfields.setdefault(s_, {})[so] = t; return f"{s_}.unk_{so:X}"
        o = _imm(off); b = use(base)
        typed = typed_access(base, o, t)
        if typed:
            return typed[0]
        fb = field_base(b, base) if o >= 0 else None
        if fb is None:
            return f"*({t} *)((u8 *){b} + {o})"
        kind, key, k = fb
        if kind == "param":
            fields.setdefault(key, {})[o] = t; return f"{b}->unk_{o:X}"
        if kind == "global" and b in locals_:
            gfields.setdefault(key, {})[o] = t; return f"{b}->unk_{o:X}"
        if kind == "global":
            declare(key, "struct", far_ref=True); gfields.setdefault(key, {})[o + k] = t; return f"{key}.unk_{o + k:X}"
        if kind == "ptr":
            ptr_globals.add(key); pfields.setdefault(key, {})[o] = t; return f"{key}->unk_{o:X}"
        return None

    carried_until: Dict[str, int] = {}

    def promote_written(i0: int, region_end: int) -> None:
        """Every register the region (i0, region_end) writes and code after it may read is a
        local: its writes become statements inside the branches, reads after use the local."""
        written = []
        for x in range(i0 + 1, region_end):
            mn_x, a_x = ins[x]
            if a_x and mn_x not in STORE_T and not mn_x.startswith(("st", "cmp", "b")) and mn_x not in ("mtlr", "mtspr", "mtctr"):
                if a_x[0] not in written:
                    written.append(a_x[0])
        for rw in written:
            if rw in ("r0", "r1") or rw in carried or not re.fullmatch(r"r([3-9]|1\d|2\d|3[01])|f([1-9]|1\d|2\d|3[01])", rw):
                continue
            read_after = read_later(region_end - 1, rw)
            if not read_after:
                continue
            init0 = regs.get(rw)
            if init0 is not None and (re.fullmatch(r"&[A-Za-z_]\w*", init0) or init0.startswith("((u8 *)&") or init0.startswith("(struct ")):
                continue  # MWCC rematerialises addresses: no local
            tn = f"v{len(temps)}"
            init = regs.get(rw)
            if init is None and re.fullmatch(r"r([3-9]|10)|f[1-8]", rw) and rw not in params and rw not in def_idx:
                init = use(rw)  # a parameter not seen before: its value is the argument
            temps.append(f"{rtype.get(rw, 'u32')} {tn};")
            if init is not None:
                stmts.append(f"{tn} = {init};")
            regs[rw] = tn; carried[rw] = tn
            carried_until[rw] = max(carried_until.get(rw, 0), region_end)

    def loop_locals(b_: int, t_: int, k_: int) -> None:
        """Registers written inside the loop and read inside before written, or read by its
        test, are loop-carried: locals initialised from their pre-loop value."""
        def writes(x):
            mn_x, a_x = ins[x]
            return a_x[0] if a_x and mn_x not in STORE_T and not mn_x.startswith(("st", "cmp", "b")) and mn_x not in ("mtlr", "mtspr", "mtctr") else None
        def reads_of(x):
            mn_x, a_x = ins[x]
            srcs = a_x[1:] if mn_x not in STORE_T and not mn_x.startswith(("st", "cmp", "b")) else a_x
            return set(re.findall(r"\b([rf]\d+)\b", " ".join(srcs)))
        written_in = {writes(x) for x in range(b_, k_ + 1) if writes(x)}
        live_in, seen_w = set(), set()
        for x in range(b_, t_):
            live_in |= (reads_of(x) - seen_w)
            w_ = writes(x)
            if w_:
                seen_w.add(w_)
        test_reads = set()
        for x in range(t_, k_ + 1):
            test_reads |= reads_of(x)
        for r_ in sorted((live_in | test_reads) & written_in):
            if r_ in ("r1", "r0") or r_ in carried:
                continue
            tn = f"v{len(temps)}"
            init = regs.get(r_)
            if init is None:
                init = use(r_) if re.fullmatch(r"r([3-9]|10)|f[1-8]", r_) else "0"
            temps.append(f"{rtype.get(r_, 'u32')} {tn};")
            stmts.append(f"{tn} = {init};")
            regs[r_] = tn; carried[r_] = tn
            carried_until[r_] = max(carried_until.get(r_, 0), k_ + 1)
    for i, (mn, a) in enumerate(ins):
        n_open, n_stmts = len(open_ifs), len(stmts)
        try:
            # a value used more than once (before its register is redefined) lives in a local: the
            # compiler would otherwise recompute or reschedule the expression at each use
            if i > 0:
                pm, pa = ins[i - 1]
                pd = pa[0] if pa and pm not in STORE_T and not pm.startswith(("st", "cmp", "b")) and pm not in ("mtlr", "mtspr", "bl") else None
                if pd and pd in regs and pd not in carried and not re.fullmatch(r"[A-Za-z_]\w*|-?\d+|0x[0-9A-Fa-f]+|&[A-Za-z_]\w*", regs[pd]) and not regs[pd].startswith(("(struct ", "__CALLRET__", "__XORIS__", "__I2D__", "__FCTIWZ__", "((u8 *)&", "&")):
                    uses = 0
                    for x in range(i, len(ins)):
                        if reads(x, pd) or (ins[x][0] in ("bl", "bctrl", "blrl") and re.fullmatch(r"r([3-9]|10)|f[1-8]", pd)):
                            if x in chain_cmp_idx and reads(x, pd) and ins[x][0].startswith("cmp"):
                                uses += 0.5  # compares of one short-circuit condition share the value
                            else:
                                uses += 1
                        if ins[x][0] == "blr" and pd in ("r3", "f1"):
                            uses += 1  # returned
                        if ins[x][0] in ("bl", "bctrl", "blrl") and re.fullmatch(r"r([0-9]|1[0-2])|f([0-9]|1[0-3])", pd):
                            break
                        if ins[x][1] and ins[x][1][0] == pd and ins[x][0] not in STORE_T and not ins[x][0].startswith(("st", "cmp")):
                            break
                    if uses >= 2:
                        tn = f"v{len(temps)}"; temps.append(f"{rtype.get(pd, 'u32')} {tn};")
                        stmts.append(f"{tn} = {regs[pd]};"); regs[pd] = tn
            # a carried register that now holds a new expression: materialise the assignment
            for r_, tn in list(carried.items()):
                if regs.get(r_) is None:
                    regs[r_] = tn  # cleared by a call: the local still holds the value
                elif regs.get(r_) != tn:
                    e_ = regs.get(r_)
                    if e_.startswith(("__I2D__", "__XORIS__", "__FCTIWZ__")):
                        continue  # Publish the converted value, not the compiler's scratch encoding.
                    if e_.startswith(("((u8 *)", "(u8 *)", "&", "(struct ")):
                        e_ = f"(u32){e_}"  # a register reused for an address: the local is an integer
                    # another register still holds an expression over the old value: that value
                    # is a temporary of its own before the local changes
                    for r2, e2 in list(regs.items()):
                        if r2 != r_ and e2 and e2 != tn and re.search(rf"\b{re.escape(tn)}\b", e2) and read_later(i - 1, r2):
                            t2 = f"v{len(temps)}"; temps.append(f"{rtype.get(r2, 'u32')} {t2};")
                            stmts.append(f"{t2} = {e2};"); regs[r2] = t2
                    stmts.append(f"{tn} = {e_};"); regs[r_] = tn
            # a register an if-region carried is its own again after the region: a later reuse
            # of the register is not an assignment to the local (the region's last write was
            # materialised just above)
            for rw_ in [r_ for r_, u_ in carried_until.items() if u_ <= i]:
                carried_until.pop(rw_, None)
                carried.pop(rw_, None)
            in_loop[:] = [region for region in in_loop if region[2] >= i]
            if a and mn not in STORE_T and not mn.startswith(("st", "cmp", "b")) and mn not in ("mtlr", "mtspr", "mtctr"):
                temps_written.append((a[0], i)); written_since_call.add(a[0]); def_idx[a[0]] = i
            if mn == "bl":
                pass  # cleared after the call is processed (see the bl branch)
            # the previous instruction wrote a callee-saved register with a computed value that a
            # call will intervene before its use: the source kept it in a local
            if i > 0:
                pm, pa = ins[i - 1]
                pd = pa[0] if pa and pm not in STORE_T and not pm.startswith(("st", "cmp", "b")) and pm not in ("mtlr", "mtspr", "mtctr") else None
                if pd and SAVE_RE.match(pd) and pd not in carried and pd in regs and not re.fullmatch(r"[A-Za-z_]\w*|-?\d+|0x[0-9A-Fa-f]+|&[A-Za-z_]\w*", regs[pd]) and not regs[pd].startswith("(struct "):
                    call_before_use = False
                    for x in range(i, len(ins)):
                        if ins[x][0] in ("bl", "bctrl", "blrl"):
                            call_before_use = True; break
                        if reads(x, pd) or (ins[x][1] and ins[x][1][0] == pd and ins[x][0] not in STORE_T):
                            break
                    if call_before_use:
                        tn = f"v{len(temps)}"; temps.append(f"{rtype.get(pd, 'u32')} {tn};")
                        stmts.append(f"{tn} = {regs[pd]};"); regs[pd] = tn
            while open_ifs and open_ifs[-1][0] == i:
                text_ = open_ifs.pop()[1]
                if text_ == "} else {" and open_ifs and open_ifs[-1][0] == i and open_ifs[-1][1] == "} else {":
                    text_ = "}"  # an inner region whose else is the enclosing region's: a plain if
                stmts.append(text_)
                if text_ == "} else {" and i in else_state:
                    snap_r, snap_t = else_state.pop(i)
                    for r_ in list(regs):
                        if r_ not in snap_r:
                            regs.pop(r_)
                    regs.update(snap_r); rtype.update(snap_t)
            if i in pending_div:
                d_, e_ = pending_div.pop(i)
                regs[d_] = e_; rtype[d_] = "u32"
            if -1 not in inline_copies:
                scan_inline_copies()
            if i in inline_copies:
                end_, nw, rS, k, rD, kD = inline_copies[i]
                size = 4 * nw
                def copy_ref(reg: str, off: int) -> str:
                    b_ = use(reg)
                    fb_ = field_base(b_, reg)
                    if fb_ and fb_[0] == "param":
                        return f"*(struct {name}_Copy{size} *)((u8 *){b_} + {off})" if off else f"*(struct {name}_Copy{size} *){b_}"
                    return f"*(struct {name}_Copy{size} *)((u8 *){b_} + {off})" if off else f"*(struct {name}_Copy{size} *){b_}"
                src_e = copy_ref(rS, k); dst_e = copy_ref(rD, kD)
                copy_types.add(size)
                stmts.append(f"{dst_e} = {src_e};")
                for x in range(i, end_):
                    skip.add(x)
                for r_, _ in ((a_[0], 0) for mn_, a_ in ins[i:end_] if mn_ == "lwz"):
                    regs.pop(r_, None)
                continue
            if i in copy_addresses:
                reg, base, offset = copy_addresses[i]
                if base == 'r1':
                    slocals.setdefault(offset, {"w": 4, "t": "u32", "addr": True, "elems": {}})
                    regs[reg] = f"&loc_{offset:X}"
                else:
                    expression = use(base)
                    regs[reg] = f"((u8 *){expression} + {offset})" if offset else expression
                rtype[reg] = "void *"
                continue
            if i in copies:
                K, rD, rS, end_ = copies[i]
                size = 8 * K
                dest, source = use(rD), use(rS)
                dst = dest[1:] if re.fullmatch(r'&loc_[0-9A-F]+', dest) else f"*(struct {name}_Copy{size} *){dest}"
                stmts.append(f"{dst} = *(struct {name}_Copy{size} *){source};")
                copy_types.add(size)
                skip.update(range(i + 1, end_ + 1))
                for r_ in (rD, rS, "r0", "r3"):
                    regs.pop(r_, None)
                continue
            if i in case_labels:
                stmts.append(case_labels[i])
                snap = switch_state.get(case_labels[i])
                if snap:
                    for r_ in list(regs):
                        if r_ not in snap[0]:
                            regs.pop(r_)
                    regs.update(snap[0]); rtype.update(snap[1])
            if i in switch_breaks:
                stmts.append("break;"); continue
            if i in switch_at:
                sw = switch_at[i]
                x_ = use(sw["reg"])
                tt = rtype.get(sw["reg"], "u32")
                if sw["uns"] and tt not in ("u32", "u16", "u8"):
                    x_ = f"(u32){x_}"
                elif not sw["uns"] and tt not in ("s32", "s16", "s8"):
                    x_ = f"(s32){x_}"
                promote_written(i, sw["join"])
                stmts.append(f"switch ({x_}) {{")
                for x in sw["tree"]:
                    skip.add(x)
                snap = (dict(regs), dict(rtype))
                for L, vals in sw["cases"].items():
                    case_labels[L] = "\n".join(f"case {v}:" for v in vals)
                    switch_state[case_labels[L]] = snap
                if sw["default"] is not None:
                    case_labels[sw["default"]] = "default:"
                    switch_state["default:"] = snap
                for bi, L in enumerate(sw["labels"]):
                    end = sw["labels"][bi + 1] if bi + 1 < len(sw["labels"]) else sw["join"]
                    if end - 1 > L and ins[end - 1][0] == "b" and labels.get(ins[end - 1][1][-1], -1) == sw["join"]:
                        switch_breaks.add(end - 1)
                open_ifs.append((sw["join"], "}"))
                open_ifs.sort(key=lambda x: -x[0])
                continue
            if i in skip:
                continue
            if i in dowhile_by_entry or i in ctr_loops:
                if i in ctr_loops:
                    b_, k_ = ctr_loops[i]; t_ = k_
                    count = use(a[0])
                    tn = f"v{len(temps)}"; temps.append(f"u32 {tn};")
                    loop_locals(b_, t_, k_)
                    guarded = i in ctr_guarded
                    if guarded:
                        stmts.append(f"for ({tn} = 0; {tn} < {count}; {tn}++) {{")
                    else:
                        stmts.append(f"for ({tn} = {count}; {tn} != 0; {tn}--) {{")
                    skip.add(k_)
                    open_ifs.append((k_, "}"))
                    open_ifs.sort(key=lambda x: -x[0])
                    in_loop.append((b_, t_, k_))
                    continue
                b_, t_, k_ = dowhile_by_entry[i]
                loop_locals(b_, t_, k_)
                stmts.append("do {")
                in_loop.append((b_, t_, k_))
            if i in dowhile_test:
                b_, t_, k_ = dowhile_test[i]
                cond_expr = None
                for x in range(t_, k_):
                    mn_x, a_x = ins[x]
                    cond_expr = test_step(mn_x, a_x, cond_expr)
                    if cond_expr is UNKNOWN:
                        raise Give("do-while test shape")
                if cond_expr is None:
                    raise Give("do-while test")
                op = COND[re.fullmatch(r"b(\w+)", ins[k_][0]).group(1)]
                for reg, local in carried.items():
                    if regs.get(reg) is not None and regs[reg] != local:
                        stmts.append(f'{local} = {regs[reg]};')
                        regs[reg] = local
                stmts.append(f"}} while ({cond_expr[0]} {op} {cond_expr[1]});")
                for x in range(t_, k_ + 1):
                    skip.add(x)
                if in_loop:
                    in_loop.pop()
                continue
            if i in loop_by_entry:
                b_, t_, k_ = loop_by_entry[i]
                # loop-carried registers: written inside [b_, k_] and read inside before written, or read by the test
                def writes(x):
                    mn_x, a_x = ins[x]
                    return a_x[0] if a_x and mn_x not in STORE_T and not mn_x.startswith(("st", "cmp", "b")) and mn_x not in ("mtlr", "mtspr") else None
                def reads_of(x):
                    mn_x, a_x = ins[x]
                    srcs = a_x[1:] if mn_x not in STORE_T and not mn_x.startswith(("st", "cmp", "b")) else a_x
                    return set(re.findall(r"\b([rf]\d+)\b", " ".join(srcs)))
                written_in = {writes(x) for x in range(b_, k_ + 1) if writes(x)}
                live_in, seen_w = set(), set()
                for x in range(b_, t_):
                    live_in |= (reads_of(x) - seen_w)
                    w_ = writes(x)
                    if w_:
                        seen_w.add(w_)
                test_reads = set()
                for x in range(t_, k_ + 1):
                    test_reads |= reads_of(x)
                for r_ in sorted((live_in | test_reads) & written_in):
                    if r_ in ("r1", "r0") or r_ in carried:
                        continue
                    tn = f"v{len(temps)}"
                    init = regs.get(r_)
                    if init is None:
                        init = use(r_) if re.fullmatch(r"r([3-9]|10)|f[1-8]", r_) else "0"
                    temps.append(f"{rtype.get(r_, 'u32')} {tn};")
                    stmts.append(f"{tn} = {init};")
                    regs[r_] = tn; carried[r_] = tn
                    carried_until[r_] = max(carried_until.get(r_, 0), k_ + 1)
                # the test, evaluated on the pre-loop state, gives the condition
                saved_regs, saved_rtype, saved_len = dict(regs), dict(rtype), len(stmts)
                cond_expr = None
                for x in range(t_, k_):
                    mn_x, a_x = ins[x]
                    nxt_ = test_step(mn_x, a_x, cond_expr)
                    if nxt_ is UNKNOWN:
                        raise Give("loop test shape")
                    cond_expr = nxt_
                if cond_expr is None:
                    raise Give()
                m_ = re.fullmatch(r"b(\w+)", ins[k_][0])
                op = COND[m_.group(1)]
                stmts.append(f"while ({cond_expr[0]} {op} {cond_expr[1]}) {{")
                regs, rtype = saved_regs, saved_rtype
                # the body runs next; the test instructions and the back branch are consumed
                for x in range(t_, k_ + 1):
                    skip.add(x)
                open_ifs.append((k_ + 1, "}"))
                open_ifs.sort(key=lambda x: -x[0])
                in_loop.append((b_, t_, k_))
                continue
            if mn == "b":
                tgt_ = labels.get(a[-1]) if a and a[-1].startswith(".L_") else None
                if tgt_ is not None and tgt_ > i and all(ins[x][0] in ("lwz", "lmw", "mtlr", "addi", "blr", "lfd", "psq_l") or (ins[x][0] == "bl" and re.fullmatch(r"_rest(gpr|fpr)_\d+", ins[x][1][0])) for x in range(tgt_, len(ins))):
                    # the epilogue: an early return with what r3 (or f1) holds
                    if "r3" in regs and any(a_ and a_[0] == "r3" for mn_, a_ in ins[:i] if mn_ not in ("stw", "sth", "stb", "stfs", "stfd", "cmpwi", "cmpw", "cmplwi", "cmplw")):
                        stmts.append(f"return {regs['r3']};"); regs.pop("r3", None)
                    elif "f1" in regs and any(a_ and a_[0] == "f1" for mn_, a_ in ins[:i]):
                        stmts.append(f"return {regs['f1']};"); regs.pop("f1", None)
                    else:
                        stmts.append("return __RET__;")
                    continue
                raise Give("unexplained b")  # an unconditional jump that no if/else or loop explained
            if mn == "blr":
                if i == len(ins) - 1 or not any(True for _ in ins[i + 1:]):
                    break
                # an early return: the value r3 holds here, then the lift goes on at the label
                # that follows (the fallthrough code the branch skipped over)
                if "r3" in regs and any(a_ and a_[0] == "r3" for mn_, a_ in ins[:i] if mn_ not in ("stw", "sth", "stb", "stfs", "stfd", "cmpwi", "cmpw", "cmplwi", "cmplw")):
                    stmts.append(f"return {regs['r3']};")
                    regs.pop("r3", None)
                elif "f1" in regs and any(a_ and a_[0] == "f1" for mn_, a_ in ins[:i]):
                    stmts.append(f"return {regs['f1']};")
                    regs.pop("f1", None)
                else:
                    stmts.append("return __RET__;")
                continue
            if mn in ("cmpwi", "cmpw", "cmplwi", "cmplw"):
                lhs = use(a[0]); rhs = str(_imm(a[1])) if mn.endswith("i") else use(a[1])
                uns = mn.startswith("cmpl")
                # the compare's signedness is the operands' type: cmpwi wants signed operands
                def typed(e: str, reg: str) -> str:
                    t = rtype.get(reg, "u32")
                    if uns:
                        return e if t in ("u32", "u16", "u8") else f"(u32){e}"
                    return e if t in ("s32", "s16", "s8") else f"(s32){e}"
                lhs = typed(lhs, a[0])
                if not mn.endswith("i"):
                    rhs = typed(rhs, a[1])
                cond = (lhs, rhs, uns); continue
            if mn.endswith("lr") and mn[1:-2] in COND and cond is not None:
                op = COND[mn[1:-2]]
                l, r_, uns = cond
                stmts.append(f"if ({l} {op} {r_}) {{ return __RET__; }}"); continue
            m = re.fullmatch(r"b(\w+)", mn)
            if m and m.group(1) in COND and a and a[-1].startswith(".L_") and cond is not None:
                tgt = labels.get(a[-1])
                if tgt is None or tgt <= i:
                    raise Give()  # a back edge no loop region explained
                op = COND[m.group(1)]
                inv = {"==": "!=", "!=": "==", "<": ">=", ">": "<=", "<=": ">", ">=": "<"}[op]  # branch taken = skip
                l, r_, uns = cond
                enter_text = f"{l} {inv} {r_}"   # the then block runs when the branch is not taken
                skip_text = f"{l} {op} {r_}"
                if i in chain_mid:
                    ch = chain_last[next(b for b in chain_last if chain_last[b]["id"] == chain_mid[i])]
                    chain_terms.setdefault(chain_mid[i], []).append(("E" if tgt == ch["E"] else "T", l, op, inv, r_))
                    continue
                if i in chain_last:
                    ch = chain_last[i]
                    terms = chain_terms.get(ch["id"], []) + [("E" if tgt == ch["E"] else "T", l, op, inv, r_)]
                    # reaching the then block: R(k) = !e_k && R(k+1) for an else-branch, t_k || R(k+1) for a then-branch
                    R = "0" if ch["fall_b"] is not None else None
                    for kind, tl, top_, tinv, tr in reversed(terms):
                        if kind == "E":
                            term = f"{tl} {tinv} {tr}"
                            if R is None or R == "0":
                                R = term
                            else:
                                R = f"{term} && ({R})" if "||" in R else f"{term} && {R}"
                        else:
                            term = f"{tl} {top_} {tr}"
                            if R is None or R == "0":
                                R = term
                            else:
                                R = f"{term} || ({R})" if "&&" in R else f"{term} || {R}"
                    # calls whose results the condition tests are evaluated inside it
                    for m_c in re.finditer(r"__CALLRET__(\d+)", R):
                        n_c = int(m_c.group(1))
                        for si in range(len(stmts) - 1, -1, -1):
                            m_s = re.match(rf"__CALL__{n_c}\((.*)\);$", stmts[si])
                            if m_s:
                                R = R.replace(f"__CALLRET__{n_c}", f"__INLINECALL__{n_c}({m_s.group(1)})")
                                stmts.pop(si)
                                # a local initialised from that result has no value before the condition
                                stmts[:] = [st for st in stmts if not re.fullmatch(rf"\w+ = __CALLRET__{n_c};", st)]
                                for r_ in list(regs):
                                    if regs[r_] == f"__CALLRET__{n_c}":
                                        regs.pop(r_)
                                break
                    enter_text = R
                    skip_text = f"!({R})"
                    tgt = ch["E"]
                if ins[tgt][0] == "blr" or tgt == len(ins) - 1:
                    stmts.append(f"if ({skip_text}) {{ return __RET__; }}")
                else:
                    # every register the region writes and code after it may read is a local: its
                    # writes become statements inside the branches, reads after use the local
                    region_end = tgt
                    pm0, pa0 = ins[tgt - 1]
                    if pm0 == "b" and pa0 and pa0[-1].startswith(".L_") and labels.get(pa0[-1], -1) > tgt:
                        region_end = labels[pa0[-1]]
                    promote_written(i, region_end)
                    # `if (c) { then } else { else }` when the then-block ends with a forward jump
                    # over the else-block; otherwise a plain if
                    pm, pa = ins[tgt - 1]
                    if pm == "b" and pa and pa[-1].startswith(".L_") and labels.get(pa[-1], -1) > tgt:
                        end = labels[pa[-1]]
                        # the then-block's jump may leave an enclosing region too: this region
                        # still closes where the enclosing one continues
                        enclosing = min((idx for idx, _ in open_ifs if idx > i), default=None)
                        if enclosing is not None and end > enclosing:
                            end = enclosing
                        skip.add(tgt - 1)
                        stmts.append(f"if ({enter_text}) {{")
                        # closers are pushed innermost-last: the stack pops the else first, then the end
                        open_ifs.append((end, "}")); open_ifs.append((tgt - 1, "} else {"))
                        # the else branch runs from the state at the branch (a call in the then
                        # branch clears argument registers the else branch still holds)
                        else_state[tgt - 1] = (dict(regs), dict(rtype))
                    else:
                        stmts.append(f"if ({enter_text}) {{"); open_ifs.append((tgt, "}"))
                open_ifs.sort(key=lambda x: -x[0])  # smallest index on top: every closer pops at its index
                continue
            lr_slot = f"0x{frame_size + 4:x}(r1)" if frame_size else None
            slot_ = None
            if a and len(a) > 1 and a[1].endswith("(r1)"):
                m_s = re.match(r"^(-?0x[0-9a-f]+|-?\d+)", a[1])
                slot_ = int(m_s.group(1), 0) if m_s else None
            if mn == "mtlr":
                # An indirect call consumes LR as a function pointer; the final mtlr
                # restores the caller's return address and remains frame bookkeeping.
                next_lr_use = next((m for m, _ in ins[i + 1:] if m in ("mtlr", "bl", "bctrl", "blrl", "blr")), None)
                if next_lr_use == "blrl":
                    lr_expr[0] = use(a[0])
                    continue
            if mn in ("stwu", "mflr", "mtlr") or (mn in ("stw", "lwz") and a and ((a[0] == "r0" and a[1] == lr_slot) or (SAVE_RE.match(a[0]) and slot_ in saved_slots))) or (mn == "addi" and a and a[0] == "r1"):
                frame = True
                continue
            if mn == "addi" and len(a) == 3 and a[1] == "r1":
                off_ = _imm(a[2])
                local_at(off_, 0, "u8"); slocals[off_]["addr"] = True
                regs[a[0]] = f"&loc_{off_:X}"; rtype[a[0]] = "void *"; frame = True
                continue
            if i in int_float_stores:
                int_float_values[i] = use(a[0])
                frame = True
                continue
            if i in int_float_loads:
                _, low_store = int_float_loads[i]
                value = int_float_values[low_store]
                signed = re.fullmatch(r"__XORIS__\((.+), 32768\)", value)
                regs[a[0]] = f"__I2D__({signed[1]}, signed)" if signed else f"__I2D__({value}, unsigned)"
                rtype[a[0]] = "f64"; frame = True
                continue
            if mn == "stfd" and a and a[1].endswith("(r1)"):
                expression = regs.get(a[0], "")
                if expression.startswith("__FCTIWZ__("):
                    conv_slots[_imm(a[1][:-4])] = ("fctiwz", expression[len("__FCTIWZ__("):-1])
                    frame = True
                    continue
            if mn == "lwz" and a and a[1].endswith("(r1)") and _imm(a[1][:-4]) - 4 in conv_slots and conv_slots[_imm(a[1][:-4]) - 4][0] == "fctiwz":
                regs[a[0]] = f"(s32){conv_slots[_imm(a[1][:-4]) - 4][1]}"; rtype[a[0]] = "s32"; frame = True; continue
            if mn in LOAD_T and a and a[1].endswith("(r1)"):
                off_ = _imm(a[1][:-4]); t = LOAD_T[mn]
                if off_ in saved_slots or off_ >= frame_size:
                    frame = True; continue
                regs[a[0]] = local_at(off_, WIDTH[mn], t); rtype[a[0]] = t; frame = True
                continue
            if mn == "stw" and a and a[0] == "r0" and a[1] == "0x4(r1)" and i < stwu_index and any(ins[x][0] == "mflr" for x in range(0, i)):
                frame = True; continue  # the 1.2.5n prologue saves LR before it moves the stack pointer
            if mn in STORE_T and a and a[1].endswith("(r1)"):
                off_ = _imm(a[1][:-4]); t = STORE_T[mn]
                if off_ in saved_slots or off_ >= frame_size or a[0] == "r0" and off_ > frame_size:
                    frame = True; continue
                stmts.append(f"{local_at(off_, WIDTH[mn], t)} = {use(a[0])};"); frame = True
                continue
            if mn in ("stfd", "lfd", "psq_st", "psq_l") and a and re.fullmatch(r"f(1[4-9]|2\d|3[01])", a[0]) and slot_ in saved_slots:
                frame = True
                continue  # callee-saved float registers
            if mn in ("stmw", "lmw"):
                frame = True; continue  # the callee-saved block save/restore
            if mn in ("crclr", "crset") or mn == "nop":
                if mn == "crclr":
                    variadic_next[0] = True  # `crclr cr1eq`: the callee is variadic (no float varargs)
                continue
            if mn == "lis" and sym_of(a[1]):
                hi[a[0]] = sym_of(a[1]); regs.pop(a[0], None); continue
            if mn == "lis":
                regs[a[0]] = f"0x{(_imm(a[1]) & 0xFFFF) << 16:X}"; rtype[a[0]] = "u32"; continue
            if mn == "addi" and sym_of(a[2]) and a[1] in hi:
                s = sym_of(a[2]); declare(s, "u32", far_ref=True)  # lis/addi: the retail addressed it far
                sd = lookup(s)
                so = sym_off(a[2])
                if sd is not None and sd.kind == "function":
                    regs[a[0]] = s; fnames_seen.add(s)
                elif so:
                    regs[a[0]] = f"((u8 *)&{s} + {so})"
                elif SAVE_RE.match(a[0]):
                    # kept in a callee-saved register: the source held it in a local pointer
                    ln = f"p_{s}"
                    locals_[ln] = s
                    declare(s, "struct", far_ref=True); gfields.setdefault(s, {})
                    # the cast is what keeps the address in the register across calls: MWCC
                    # rematerialises a plain `&sym` after each call, but not a cast of it.
                    # The assignment is emitted right before the first statement that uses it.
                    stmts.append(f"{ln} = (struct {name}_{s} *)&{s};")  # eager: retail places it early
                    regs[a[0]] = ln
                else:
                    regs[a[0]] = f"&{s}"
                rtype[a[0]] = "void *"; continue
            if mn == "li" and a[1].endswith("@sda21") and sym_of(a[1]):
                s_ = sym_of(a[1]); so = sym_off(a[1]); declare(s_, "u32")
                regs[a[0]] = f"((u8 *)&{s_} + {so})" if so else f"&{s_}"; rtype[a[0]] = "void *"; continue
            if mn in ("li",):
                regs[a[0]] = str(_imm(a[1])); rtype[a[0]] = "s32"; continue
            if mn == "mr":
                regs[a[0]] = use(a[1]); rtype[a[0]] = rtype.get(a[1], "u32"); continue
            if mn == "mr.":
                regs[a[0]] = use(a[1]); rtype[a[0]] = rtype.get(a[1], "u32")
                cond = (regs[a[0]], "0", rtype[a[0]] in ("u32", "u16", "u8", "void *")); continue
            if mn == "addis" and not sym_of(a[2]) and a[1] != "r0":
                imm_ = (_imm(a[2]) << 16) & 0xFFFFFFFF
                regs[a[0]] = f"({use(a[1])} + 0x{imm_:X})"; rtype[a[0]] = "u32"; continue
            if mn in ("fcmpo", "fcmpu") and len(a) >= 3:
                cond = (use(a[1]), use(a[2]), False); continue
            if mn in LOAD_T:
                m = MEM_RE.match(a[1])
                if not m:
                    raise Give()
                off, base = m.group(1), m.group(2)
                t = LOAD_T[mn]
                if off.endswith("@l") and base in hi:
                    s = hi[base]; so = sym_off(off)
                    if so or s in struct_syms:
                        declare(s, "struct", far_ref=True); gfields.setdefault(s, {})[so] = t; regs[a[0]] = f"{s}.unk_{so:X}"
                    else:
                        declare(s, t, far_ref=True); regs[a[0]] = ref(s)
                    rtype[a[0]] = t
                    if mn.endswith("u"):
                        regs[base] = f"&{s}" if not so else f"((u8 *)&{s} + {so})"; hi.pop(base, None)
                    continue
                elif off.endswith("@sda21"):
                    s = sym_of(off); so = sym_off(off)
                    if so:
                        declare(s, "struct"); gfields.setdefault(s, {})[so] = t; regs[a[0]] = f"{s}.unk_{so:X}"
                    else:
                        declare(s, t); regs[a[0]] = s
                    rtype[a[0]] = t
                else:
                    o = _imm(off)
                    b = use(base)
                    typed = typed_access(base, o, t)
                    if typed:
                        regs[a[0]], rtype[a[0]] = typed
                        if mn.endswith("u"):
                            regs[base] = f"((u8 *){b} + {o})"
                        if reused_after_store(i, a[0], a[1]):
                            tn = f"v{len(temps)}"; temps.append(f"{rtype[a[0]]} {tn};")
                            stmts.append(f"{tn} = {regs[a[0]]};"); regs[a[0]] = tn
                        continue
                    fb = field_base(b, base) if o >= 0 else None
                    if fb is None:
                        ax = indexed_field(b, o, t)
                        if ax is not None and not mn.endswith("u"):
                            regs[a[0]] = ax; rtype[a[0]] = t
                            if reused_after_store(i, a[0], a[1]):
                                tn = f"v{len(temps)}"; temps.append(f"{t} {tn};")
                                stmts.append(f"{tn} = {regs[a[0]]};"); regs[a[0]] = tn
                            continue
                        # a computed address (array element, pointer arithmetic): a plain typed access
                        regs[a[0]] = f"*({t} *)((u8 *){b} + {o})"; rtype[a[0]] = t
                        if mn.endswith("u"):
                            regs[base] = f"((u8 *){b} + {o})"
                        continue
                    kind, key, k = fb
                    if kind == "param":
                        fields.setdefault(key, {})[o] = t; regs[a[0]] = f"{b}->unk_{o:X}"
                    elif kind == "global" and b in locals_:
                        gfields.setdefault(key, {})[o] = t; regs[a[0]] = f"{b}->unk_{o:X}"
                    elif kind == "global" and key in ptr_globals and o + k == 0 and t == "u32":
                        regs[a[0]] = key  # the pointer variable itself, read through its address
                    elif kind == "global":
                        declare(key, "struct", far_ref=True); gfields.setdefault(key, {})[o + k] = t; regs[a[0]] = f"{key}.unk_{o + k:X}"
                    elif kind == "abs" and (key + o in HW_BLOCKS or (key in HW_BLOCKS and 0 <= o < 0x1000)):
                        # the register block's base materialised (lis/addi) then indexed: retail
                        # went through a linker-defined absolute symbol (config/<v>/ldscript.tpl)
                        # lis + load/store offset may form the block address
                        # directly, without an intervening addi.
                        hw = HW_BLOCKS[key + o] if key + o in HW_BLOCKS else HW_BLOCKS[key]
                        o = 0 if key + o in HW_BLOCKS else o
                        externs[hw] = f"extern vu32 {hw}[];"
                        regs[a[0]] = f"{hw}[{o // 4}]" if t == "u32" and o % 4 == 0 else f"*({t} *)((u8 *){hw} + 0x{o:X})"; rtype[a[0]] = t
                        if reused_after_store(i, a[0], a[1]):
                            tn = f"v{len(temps)}"; temps.append(f"{t} {tn};")
                            stmts.append(f"{tn} = {regs[a[0]]};"); regs[a[0]] = tn
                        continue
                    elif kind == "abs":
                        hit = symbol_at(key + o)
                        if hit is None:
                            if not raw_ok(key + o):
                                raise Give(f"unnamed memory 0x{key + o:X}")
                            regs[a[0]] = f"*({t} *)0x{key + o:08X}"; rtype[a[0]] = t
                            if mn.endswith("u"):
                                regs[base] = f"0x{key + o:08X}"
                            if reused_after_store(i, a[0], a[1]):
                                tn = f"v{len(temps)}"; temps.append(f"{t} {tn};")
                                stmts.append(f"{tn} = {regs[a[0]]};"); regs[a[0]] = tn
                            continue
                        sd, so = hit
                        if so == 0 and sd.size <= 8:
                            declare(sd.name, t, far_ref=True); regs[a[0]] = ref(sd.name)
                        else:
                            declare(sd.name, "struct", far_ref=True); gfields.setdefault(sd.name, {})[so] = t; regs[a[0]] = f"{sd.name}.unk_{so:X}"
                    else:
                        ptr_globals.add(key); pfields.setdefault(key, {})[o] = t; regs[a[0]] = f"{key}->unk_{o:X}"
                    rtype[a[0]] = t
                if mn.endswith("u"):  # update form: the base register advances
                    regs[base] = f"((u8 *){use(base)} + {_imm(off) if not off.endswith(('@l', '@sda21')) else 0})"
                if reused_after_store(i, a[0], a[1]):
                    tn = f"v{len(temps)}"; temps.append(f"{rtype.get(a[0], 'u32')} {tn};")
                    stmts.append(f"{tn} = {regs[a[0]]};"); regs[a[0]] = tn
                continue
            if mn in STORE_T:
                m = MEM_RE.match(a[1])
                if not m:
                    raise Give()
                off, base = m.group(1), m.group(2)
                t = STORE_T[mn]
                def as_int(v: str) -> str:
                    return f"(u32){v}" if v.startswith(("&", "((u8 *)", "(u8 *)", "(struct ")) else v
                # a value loaded before this store and read after it was a local in the source
                # (the swap idiom: `old = p->x; p->x = v; return old;`); left pending, the read
                # would be emitted after the store and see the new value
                for r_ in list(regs):
                    e_ = regs[r_]
                    if r_ == a[0] or not e_ or not re.search(r"\*\(|->|\.unk_|(?<![\w])[A-Za-z_]\w*\[", e_) or re.fullmatch(r"[A-Za-z_]\w*", e_):
                        continue
                    if not read_later(i, r_):
                        continue
                    tn = f"v{len(temps)}"; temps.append(f"{rtype.get(r_, 'u32')} {tn};")
                    stmts.append(f"{tn} = {e_};"); regs[r_] = tn
                val = as_int(use(a[0]))
                if signature_index.category(rtype.get(a[0], 'u32')) == 'pointer':
                    val = f'({t})({use(a[0])})'
                if off.endswith("@l") and base in hi:
                    s = hi[base]; so = sym_off(off)
                    if so or s in struct_syms:
                        declare(s, "struct", far_ref=True); gfields.setdefault(s, {})[so] = t; stmts.append(f"{s}.unk_{so:X} = {val};")
                    else:
                        declare(s, t, far_ref=True); stmts.append(f"{ref(s)} = {val};")
                elif off.endswith("@sda21"):
                    s = sym_of(off); so = sym_off(off)
                    if so:
                        declare(s, "struct"); gfields.setdefault(s, {})[so] = t; stmts.append(f"{s}.unk_{so:X} = {val};")
                    else:
                        declare(s, t); stmts.append(f"{s} = {val};")
                else:
                    o = _imm(off); b = use(base)
                    typed = typed_access(base, o, t)
                    if typed is not None:
                        if signature_index.category(typed[1]) == 'pointer':
                            val = f'({typed[1]})({use(a[0])})'
                        stmts.append(f"{typed[0]} = {val};")
                        continue
                    fb = field_base(b, base) if o >= 0 else None
                    if fb is None:
                        ax = indexed_field(b, o, t)
                        if ax is not None:
                            stmts.append(f"{ax} = {val};"); continue
                        stmts.append(f"*({t} *)((u8 *){b} + {o}) = {val};"); continue
                    kind, key, k = fb
                    if kind == "param":
                        fields.setdefault(key, {})[o] = t; stmts.append(f"{b}->unk_{o:X} = {val};")
                    elif kind == "global" and b in locals_:
                        gfields.setdefault(key, {})[o] = t; stmts.append(f"{b}->unk_{o:X} = {val};")
                    elif kind == "global" and key in ptr_globals and o + k == 0 and t == "u32":
                        stmts.append(f"{key} = (struct {name}_{key}_T *){val};")
                    elif kind == "global":
                        declare(key, "struct", far_ref=True); gfields.setdefault(key, {})[o + k] = t; stmts.append(f"{key}.unk_{o + k:X} = {val};")
                    elif kind == "abs" and (key + o in HW_BLOCKS or (key in HW_BLOCKS and 0 <= o < 0x1000)):
                        hw = HW_BLOCKS[key + o] if key + o in HW_BLOCKS else HW_BLOCKS[key]
                        o = 0 if key + o in HW_BLOCKS else o
                        externs[hw] = f"extern vu32 {hw}[];"
                        stmts.append((f"{hw}[{o // 4}]" if t == "u32" and o % 4 == 0 else f"*({t} *)((u8 *){hw} + 0x{o:X})") + f" = {val};"); continue
                    elif kind == "abs":
                        hit = symbol_at(key + o)
                        if hit is None:
                            if not raw_ok(key + o):
                                raise Give(f"unnamed memory 0x{key + o:X}")
                            stmts.append(f"*({t} *)0x{key + o:08X} = {val};"); continue
                        sd, so = hit
                        if so == 0 and sd.size <= 8:
                            declare(sd.name, t, far_ref=True); stmts.append(f"{ref(sd.name)} = {val};")
                        else:
                            declare(sd.name, "struct", far_ref=True); gfields.setdefault(sd.name, {})[so] = t; stmts.append(f"{sd.name}.unk_{so:X} = {val};")
                    else:
                        ptr_globals.add(key); pfields.setdefault(key, {})[o] = t; stmts.append(f"{key}->unk_{o:X} = {val};")
                continue
            if mn in ("extsh", "extsb", "clrlwi", "rlwinm", "slwi", "srwi", "srawi", "add", "subf", "sub", "mulli", "mullw", "neg", "or", "and", "xor", "ori", "andi.", "addis", "subi", "not", "extrwi", "extlwi"):
                d = a[0]
                if mn == "extrwi":
                    n, b = _imm(a[2]), _imm(a[3]); regs[d] = f"(({use(a[1])} >> {32 - b - n}) & 0x{(1 << n) - 1:X})"; rtype[d] = "u32"; continue
                if mn == "extlwi":
                    n, b = _imm(a[2]), _imm(a[3]); regs[d] = f"(({use(a[1])} << {b}) & 0x{((1 << n) - 1) << (32 - n):X})"; rtype[d] = "u32"; continue
                if mn == "extsh": regs[d] = f"(s16){use(a[1])}"; rtype[d] = "s16"
                elif mn == "extsb": regs[d] = f"(s8){use(a[1])}"; rtype[d] = "s8"
                elif mn == "clrlwi":
                    n = 32 - _imm(a[2]); regs[d] = f"({use(a[1])} & 0x{(1 << n) - 1:X})" if n < 32 else use(a[1]); rtype[d] = "u32"
                elif mn == "slwi": regs[d] = f"({use(a[1])} << {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "srwi":
                    src_e = regs.get(a[1], "")
                    m_ = re.fullmatch(r"\(\(\((.+) - __MULHU__\((.+), (\d+)\)\) >> 1\) \+ __MULHU__\(\2, \3\)\)", src_e) if src_e else None
                    if m_ and m_.group(1) == m_.group(2):  # the add form: x - q >> 1 + q, then >> (s-1)
                        dv = divisor_of(int(m_.group(3)), _imm(a[2]) + 1, True)
                        if dv is None:
                            raise Give()
                        regs[d] = f"({m_.group(1)} / {dv})"; rtype[d] = "u32"
                    else:
                        m2 = re.fullmatch(r"__MULHU__\((.+), (\d+)\)", src_e) if src_e else None
                        if m2:
                            dv = divisor_of(int(m2.group(2)), _imm(a[2]), False)
                            if dv is None:
                                raise Give()
                            regs[d] = f"({m2.group(1)} / {dv})"; rtype[d] = "u32"
                        else:
                            regs[d] = f"((u32){use(a[1])} >> {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "srawi": regs[d] = f"((s32){use(a[1])} >> {_imm(a[2])})"; rtype[d] = "s32"
                elif mn == "add":
                    x, y = use(a[1]), use(a[2])
                    # address + integer: byte arithmetic, or the pointee size scales the sum
                    if signature_index.category(rtype.get(a[1], 'u32')) == "pointer" and signature_index.category(rtype.get(a[2], 'u32')) != "pointer":
                        regs[d] = f"((u8 *){x} + {y})"; rtype[d] = "void *"
                    elif signature_index.category(rtype.get(a[2], 'u32')) == "pointer" and signature_index.category(rtype.get(a[1], 'u32')) != "pointer":
                        regs[d] = f"((u8 *){y} + {x})"; rtype[d] = "void *"
                    else:
                        regs[d] = f"({x} + {y})"; rtype[d] = "u32"
                elif mn in ("subf",): regs[d] = f"({use(a[2])} - {use(a[1])})"; rtype[d] = "u32"
                elif mn == "sub": regs[d] = f"({use(a[1])} - {use(a[2])})"; rtype[d] = "u32"
                elif mn == "subi": regs[d] = f"({use(a[1])} - {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "addi": regs[d] = f"({use(a[1])} + {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "mulli": regs[d] = f"({use(a[1])} * {_imm(a[2])})"; rtype[d] = "s32"
                elif mn == "mullw": regs[d] = f"({use(a[1])} * {use(a[2])})"; rtype[d] = "s32"
                elif mn == "neg": regs[d] = f"(-{use(a[1])})"; rtype[d] = "s32"
                elif mn == "or":
                    x_, y_ = use(a[1]), use(a[2])
                    if def_idx.get(a[2], -1) < def_idx.get(a[1], -1):
                        x_, y_ = y_, x_  # the operand computed first is written first
                    regs[d] = f"({x_} | {y_})"; rtype[d] = "u32"
                elif mn == "and":
                    x_, y_ = use(a[1]), use(a[2])
                    if def_idx.get(a[2], -1) < def_idx.get(a[1], -1):
                        x_, y_ = y_, x_
                    if rtype.get(a[1]) == "void *" or x_.startswith(("((u8 *)", "(u8 *)", "&")): x_ = f"(u32){x_}"
                    if rtype.get(a[2]) == "void *" or y_.startswith(("((u8 *)", "(u8 *)", "&")): y_ = f"(u32){y_}"
                    regs[d] = f"({x_} & {y_})"; rtype[d] = "u32"
                elif mn == "xor":
                    x_, y_ = use(a[1]), use(a[2])
                    if def_idx.get(a[2], -1) < def_idx.get(a[1], -1):
                        x_, y_ = y_, x_
                    regs[d] = f"({x_} ^ {y_})"; rtype[d] = "u32"
                elif mn == "ori": regs[d] = f"({use(a[1])} | {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "andi.":
                    x_ = use(a[1])
                    if rtype.get(a[1]) == "void *" or x_.startswith(("((u8 *)", "(u8 *)", "&")): x_ = f"(u32){x_}"
                    regs[d] = f"({x_} & {_imm(a[2])})"; rtype[d] = "u32"
                elif mn == "not": regs[d] = f"(~{use(a[1])})"; rtype[d] = "u32"
                elif mn == "rlwinm":
                    e_ = rlwinm_expr(use(a[1]), _imm(a[2]), _imm(a[3]), _imm(a[4]))
                    if e_ is None:
                        raise Give("rlwinm rotate")
                    regs[d] = e_; rtype[d] = "u32"
                else:
                    raise Give()
                continue
            if mn == "addi":  # plain addi (not an address)
                try:
                    const_ = (int(use(a[1]), 0) + _imm(a[2])) & 0xFFFFFFFF
                except ValueError:
                    const_ = None
                if const_ in HW_BLOCKS:
                    # lis/addi of a hardware register block's address as a value: the link
                    # script's absolute symbol (retail's lis/addi carry the resolved literal)
                    hw = HW_BLOCKS[const_]
                    externs[hw] = f"extern vu32 {hw}[];"
                    regs[a[0]] = f"(u32){hw}"; rtype[a[0]] = "u32"; continue
                if signature_index.category(rtype.get(a[1], 'u32')) == "pointer":
                    regs[a[0]] = f"((u8 *){use(a[1])} + {_imm(a[2])})"; rtype[a[0]] = "void *"
                else:
                    regs[a[0]] = f"({use(a[1])} + {_imm(a[2])})"; rtype[a[0]] = "u32"
                continue
            if mn == "oris":
                regs[a[0]] = f"({use(a[1])} | 0x{_imm(a[2]) << 16:X})"; rtype[a[0]] = "u32"; continue
            if mn == "rlwimi" and len(a) == 5:
                sh, mb, me = _imm(a[2]), _imm(a[3]), _imm(a[4])
                mask = ((0xFFFFFFFF >> mb) & (0xFFFFFFFF << (31 - me))) & 0xFFFFFFFF if mb <= me else ((0xFFFFFFFF >> mb) | (0xFFFFFFFF << (31 - me))) & 0xFFFFFFFF
                if sh and mask & ((1 << sh) - 1):
                    raise Give("rlwimi rotate")
                rot = f"({use(a[1])} << {sh})" if sh else use(a[1])
                regs[a[0]] = f"(({use(a[0])} & ~0x{mask:X}) | ({rot} & 0x{mask:X}))"; rtype[a[0]] = "u32"; continue
            if mn == "addze":
                m_ = re.fullmatch(r"\(\(s32\)(.+) >> (\d+)\)", regs.get(a[1], ""))
                if m_ and i > 0 and ins[i - 1][0] == "srawi" and ins[i - 1][1][0] == a[1]:
                    regs[a[0]] = f"((s32){m_.group(1)} / {1 << int(m_.group(2))})"; rtype[a[0]] = "s32"; continue
                raise Give("addze")
            if mn == "rotlwi":
                n_ = _imm(a[2]); x_ = use(a[1])
                regs[a[0]] = f"(({x_} << {n_}) | ((u32){x_} >> {32 - n_}))"; rtype[a[0]] = "u32"; continue
            if mn == "xori":
                regs[a[0]] = f"({use(a[1])} ^ {_imm(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "subis" and not sym_of(a[2]):
                regs[a[0]] = f"({use(a[1])} - 0x{(_imm(a[2]) << 16) & 0xFFFFFFFF:X})"; rtype[a[0]] = "u32"; continue
            if mn == "divw":
                regs[a[0]] = f"((s32){use(a[1])} / (s32){use(a[2])})"; rtype[a[0]] = "s32"; continue
            if mn == "divwu":
                regs[a[0]] = f"((u32){use(a[1])} / (u32){use(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "subfic":
                regs[a[0]] = f"({_imm(a[2])} - {use(a[1])})"; rtype[a[0]] = "s32"; continue
            if mn == "clrrwi":
                n = _imm(a[2]); x_ = use(a[1])
                if rtype.get(a[1]) == "void *" or x_.startswith(("((u8 *)", "(u8 *)", "&")): x_ = f"(u32){x_}"
                regs[a[0]] = f"({x_} & ~0x{(1 << n) - 1:X})"; rtype[a[0]] = "u32"; continue
            if mn == "clrlslwi":
                b, n = _imm(a[2]), _imm(a[3]); regs[a[0]] = f"(({use(a[1])} & 0x{(1 << (32 - b)) - 1:X}) << {n})"; rtype[a[0]] = "u32"; continue
            if mn.endswith(".") and mn[:-1] in ("extrwi", "rlwinm", "andi", "extsb", "extsh", "clrlwi", "clrrwi", "subic", "addic", "and", "or", "subf", "add", "neg", "srawi", "cntlzw", "xor", "mulli", "slwi", "srwi"):
                # record form: the result is also compared with zero for the branch that follows
                base_mn = mn[:-1]
                ins_i = (base_mn, a)
                handled = False
                # evaluate through the plain op by recursion on a one-instruction list is awkward:
                # replicate the few cases inline
                if base_mn == "extrwi":
                    n, b = _imm(a[2]), _imm(a[3]); regs[a[0]] = f"(({use(a[1])} >> {32 - b - n}) & 0x{(1 << n) - 1:X})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "andi":
                    regs[a[0]] = f"({use(a[1])} & {_imm(a[2])})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "extsb":
                    regs[a[0]] = f"(s8){use(a[1])}"; rtype[a[0]] = "s8"; handled = True
                elif base_mn == "extsh":
                    regs[a[0]] = f"(s16){use(a[1])}"; rtype[a[0]] = "s16"; handled = True
                elif base_mn == "clrlwi":
                    n = 32 - _imm(a[2]); regs[a[0]] = f"({use(a[1])} & 0x{(1 << n) - 1:X})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "rlwinm":
                    e_ = rlwinm_expr(use(a[1]), _imm(a[2]), _imm(a[3]), _imm(a[4]))
                    if e_ is not None:
                        regs[a[0]] = e_; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "clrrwi":
                    n = _imm(a[2]); regs[a[0]] = f"({use(a[1])} & ~0x{(1 << n) - 1:X})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn in ("subic", "addic"):
                    k = _imm(a[2]); regs[a[0]] = f"({use(a[1])} {'-' if base_mn == 'subic' else '+'} {k})"; rtype[a[0]] = rtype.get(a[1], "s32"); handled = True
                elif base_mn == "and":
                    regs[a[0]] = f"({use(a[1])} & {use(a[2])})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "or":
                    regs[a[0]] = f"({use(a[1])} | {use(a[2])})"; rtype[a[0]] = "u32"; handled = True
                elif base_mn == "subf":
                    regs[a[0]] = f"({use(a[2])} - {use(a[1])})"; rtype[a[0]] = "s32"; handled = True
                elif base_mn == "add":
                    regs[a[0]] = f"({use(a[1])} + {use(a[2])})"; rtype[a[0]] = "s32"; handled = True
                elif base_mn == "neg":
                    regs[a[0]] = f"(-{use(a[1])})"; rtype[a[0]] = "s32"; handled = True
                elif base_mn == "rlwinm":
                    sh, mb, me = _imm(a[2]), _imm(a[3]), _imm(a[4])
                    if sh == 0 and mb == 0: regs[a[0]] = f"({use(a[1])} & 0x{(0xFFFFFFFF << (31 - me)) & 0xFFFFFFFF:X})"
                    elif sh == 0 and me == 31: regs[a[0]] = f"({use(a[1])} & 0x{(1 << (32 - mb)) - 1:X})"
                    else: raise Give()
                    rtype[a[0]] = "u32"; handled = True
                if not handled:
                    raise Give()
                signed = rtype.get(a[0]) in ("s8", "s16", "s32")
                cond = (regs[a[0]], "0", not signed); continue
            if mn in ("lwzx", "lhzx", "lbzx", "lfsx", "lhax"):
                t = {"lwzx": "u32", "lhzx": "u16", "lbzx": "u8", "lfsx": "f32", "lhax": "s16"}[mn]
                b = use(a[1]); i2 = use(a[2])
                ax = indexed_field(f"({b} + {i2})", 0, t) or indexed_field(f"({i2} + {b})", 0, t)
                if ax is None and t == "u8" and re.fullmatch(r"arg\d+|p_[A-Za-z_]\w*|&[A-Za-z_]\w*|\(\(u8 \*\)&[A-Za-z_]\w* \+ \d+\)", b):
                    ax = indexed_field(f"({b} + ({i2} * 1))", 0, t)
                if ax is not None:
                    regs[a[0]] = ax; rtype[a[0]] = t; continue
                regs[a[0]] = f"*({t} *)((u8 *){b} + {i2})"; rtype[a[0]] = t; continue
            if mn in ("stwx", "sthx", "stbx", "stfsx"):
                t = {"stwx": "u32", "sthx": "u16", "stbx": "u8", "stfsx": "f32"}[mn]
                b = use(a[1]); i2 = use(a[2])
                ax = indexed_field(f"({b} + {i2})", 0, t) or indexed_field(f"({i2} + {b})", 0, t)
                if ax is not None:
                    stmts.append(f"{ax} = {use(a[0])};"); continue
                stmts.append(f"*({t} *)((u8 *){b} + {i2}) = {use(a[0])};"); continue
            if mn in ("fmuls", "fadds", "fsubs", "fdivs", "fmul", "fadd", "fsub", "fdiv"):
                op = {"fmuls": "*", "fadds": "+", "fsubs": "-", "fdivs": "/", "fmul": "*", "fadd": "+", "fsub": "-", "fdiv": "/"}[mn]
                t = "f32" if mn.endswith("s") else "f64"
                m_ = re.fullmatch(r"__I2D__\((.+), (signed|unsigned)\)", regs.get(a[1], ""))
                if m_ and op == "-":
                    cast = "(s32)" if m_.group(2) == "signed" else "(u32)"
                    regs[a[0]] = f"({t}){cast}{m_.group(1)}"; rtype[a[0]] = t
                    written_since_call.discard(a[2]); regs.pop(a[2], None)  # the constant, not an argument
                    continue
                regs[a[0]] = f"({use(a[1])} {op} {use(a[2])})"; rtype[a[0]] = t; continue
            if mn in ("fmadds", "fmadd"):
                regs[a[0]] = f"(({use(a[1])} * {use(a[2])}) + {use(a[3])})"; rtype[a[0]] = "f32" if mn.endswith("s") else "f64"; continue
            if mn in ("fmsubs", "fmsub"):
                regs[a[0]] = f"(({use(a[1])} * {use(a[2])}) - {use(a[3])})"; rtype[a[0]] = "f32" if mn.endswith("s") else "f64"; continue
            if mn == "fmr":
                regs[a[0]] = use(a[1]); rtype[a[0]] = rtype.get(a[1], "f32"); continue
            if mn == "fneg":
                regs[a[0]] = f"(-{use(a[1])})"; rtype[a[0]] = rtype.get(a[1], "f32"); continue
            if mn == "frsp":
                regs[a[0]] = f"(f32){use(a[1])}"; rtype[a[0]] = "f32"; continue
            if mn == "andc":
                regs[a[0]] = f"({use(a[1])} & ~{use(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "mulhwu":
                # unsigned division by a constant: q = mulhu(x, m) then the fix-up sequence; the
                # divisor is recovered from the magic number (Hacker's Delight magicu). The whole
                # idiom is matched here by looking ahead, so its steps never leak into expressions.
                m_expr = regs.get(a[1]); x_reg = a[2]; x_expr = use(x_reg)
                if m_expr is None:
                    raise Give()
                try:
                    magic = int(eval(m_expr, {"__builtins__": {}})) & 0xFFFFFFFF if re.fullmatch(r"[0-9x\s()+\-*A-Fa-f]+", m_expr) else None
                except Exception:
                    magic = None
                if magic is None:
                    raise Give()
                q = a[0]
                # the fix-up steps may be interleaved with unrelated instructions: find them in order
                def find(start, pred):
                    for x in range(start, min(len(ins), start + 12)):
                        if pred(ins[x][0], ins[x][1]):
                            return x
                    return None
                j1 = find(i + 1, lambda m_, a_: m_ == "subf" and len(a_) == 3 and a_[1] == q and a_[2] == x_reg)
                if j1 is not None:
                    t1 = ins[j1][1][0]
                    j2 = find(j1 + 1, lambda m_, a_: m_ == "srwi" and a_[1] == t1 and _imm(a_[2]) == 1)
                    if j2 is not None:
                        t2 = ins[j2][1][0]
                        j3 = find(j2 + 1, lambda m_, a_: m_ == "add" and set(a_[1:]) == {t2, q})
                        if j3 is not None:
                            t3 = ins[j3][1][0]
                            j4 = find(j3 + 1, lambda m_, a_: m_ == "srwi" and a_[1] == t3)
                            if j4 is not None:
                                dv = divisor_of(magic, _imm(ins[j4][1][2]) + 1, True)
                                if dv is None:
                                    raise Give()
                                for x in (j1, j2, j3, j4):
                                    skip.add(x)
                                pending_div[j4] = (ins[j4][1][0], f"({x_expr} / {dv})")
                                continue
                j1 = find(i + 1, lambda m_, a_: m_ == "srwi" and a_[1] == q)
                if j1 is not None:
                    dv = divisor_of(magic, _imm(ins[j1][1][2]), False)
                    if dv is None:
                        raise Give()
                    skip.add(j1)
                    pending_div[j1] = (ins[j1][1][0], f"({x_expr} / {dv})")
                    continue
                raise Give()
            if mn == "nor":
                regs[a[0]] = f"(~({use(a[1])} | {use(a[2])}))"; rtype[a[0]] = "u32"; continue
            if mn == "slw":
                regs[a[0]] = f"({use(a[1])} << {use(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "srw":
                regs[a[0]] = f"((u32){use(a[1])} >> {use(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "sraw":
                regs[a[0]] = f"((s32){use(a[1])} >> {use(a[2])})"; rtype[a[0]] = "s32"; continue
            if mn == "mulhw":
                regs[a[0]] = f"(u32)(((s64){use(a[1])} * (s64){use(a[2])}) >> 32)"; rtype[a[0]] = "s32"; continue
            if mn == "xoris":
                regs[a[0]] = f"__XORIS__({use(a[1])}, {_imm(a[2])})"; rtype[a[0]] = "u32"; continue
            if mn == "fctiwz":
                regs[a[0]] = f"__FCTIWZ__({use(a[1])})"; rtype[a[0]] = "f64"; continue
            if mn == "cntlzw":
                regs[a[0]] = f"__cntlzw({use(a[1])})"; rtype[a[0]] = "u32"; continue
            if mn == "bl" and a and re.fullmatch(r"_(save|rest)(gpr|fpr)_\d+", a[0]):
                frame = True; continue  # the callee-saved block save/restore helpers
            if mn == "addi" and len(a) == 3 and a[0] == "r11" and a[1] == "r1":
                frame = True; continue  # the helpers' frame pointer
            if mn == "mtctr" and i not in ctr_loops and i not in copies:
                ctr_expr[0] = use(a[0]); continue
            if mn in ("bl", "bctrl", "blrl"):
                callee = a[0] if mn == "bl" else None
                if callee is not None and lookup(callee) is None:
                    raise Give(f"unknown callee {callee}")
                indirect = lr_expr if mn == "blrl" else ctr_expr
                if callee is None and indirect[0] is None:
                    raise Give(f"{mn} without a pointer")
                # arguments: r3..rN where N is the highest argument register set here; a lower
                # register never written is a parameter of ours passed straight through
                # an argument register counts only if this function wrote it since the last call
                # (a stale value from earlier code is not an argument), or passes a parameter through
                # an argument is a register written since the last call whose value is not consumed
                # by the caller before the call (a register read after its last write was a temporary)
                def is_arg(rk: str) -> bool:
                    if rk not in regs:
                        return False
                    if rk in params and regs[rk] == f"arg{params.index(rk)}":
                        return True
                    if rk not in written_since_call:
                        return False
                    last_w = max((x for x, (m_, a_) in enumerate(ins[:i]) if a_ and a_[0] == rk and m_ not in STORE_T and not m_.startswith(("st", "cmp", "b"))), default=None)
                    if last_w is None:
                        return True
                    return not any(reads(x, rk) for x in range(last_w + 1, i))
                set_regs = [k for k in range(3, 11) if is_arg(f"r{k}")]
                top = max(set_regs) if set_regs else 2
                # registers below the lowest temporary this function used are parameters passed
                # straight through to the callee: a temporary in r6 with r3..r5 untouched means
                # the source wrote callee(a, b, c)
                written = [int(x[1:]) for x, _ in temps_written if re.fullmatch(r"r([3-9]|10)", x)]
                temp_low = min((w for w in written if f"r{w}" not in params), default=None)
                if temp_low is not None and temp_low - 1 > top:
                    top = temp_low - 1
                want = ARITY_HINT[0].get(callee) if callee else None
                signature = signature_index.get(module, callee, signature_source) if callee else None
                known = (signature.result, list(signature.args), signature.defined) if signature and signature.args is not None else None
                slots = signature_index.registers(signature) if signature else None
                if signature:
                    signatures_used[callee] = signature
                no_proto = False
                if known is not None and "..." not in known[1]:
                    n_int = sum(1 for t_ in known[1] if signature_index.category(t_) != "float")
                    if 2 + n_int < top:
                        top = 2 + n_int  # the extra registers were temporaries, not arguments
                    elif 2 + n_int > top:
                        if all(f"r{k}" in regs or (f"r{k}" not in def_idx and k <= 10) for k in range(top + 1, 3 + n_int)):
                            top = 2 + n_int
                        else:
                            no_proto = True  # the site cannot supply the arguments: declared without a prototype
                elif want is not None and 2 + want > top and all(f"r{k}" in regs for k in range(top + 1, 3 + want)):
                    top = 2 + want
                if callee:
                    ARITY_SEEN[0].setdefault(callee, []).append(top - 2)
                    if any(f"f{k}" in regs and f"f{k}" in written_since_call for k in range(1, 9)):
                        FLOAT_CALLEES[0].add(callee)
                if slots is not None:
                    top = max((int(reg[1:]) for reg, _ in slots if reg.startswith('r')), default=2)
                    ftop = sum(reg.startswith('f') for reg, _ in slots)
                else:
                    # Unknown/variadic calls still use consecutive ABI argument registers;
                    # a live f7 temporary does not imply six missing float arguments.
                    ftop = 0
                    while ftop < 8 and is_arg(f'f{ftop + 1}'):
                        ftop += 1
                fargs = [use(f"f{k}") for k in range(1, ftop + 1)]
                ptypes_ = []
                for k in range(3, top + 1):
                    e = regs.get(f"r{k}", "")
                    stack_addr = e.startswith("&loc_") or (e.startswith("loc_") and e[4:].split("[")[0].isalnum() and slocals.get(int(e[4:].split("[")[0], 16), {}).get("addr"))
                    other_addr = rtype.get(f"r{k}") == "void *" or e.startswith(("&", "(u8 *)", "((u8 *)", "(struct ")) or e in fnames_seen or e in ptr_globals
                    if stack_addr:
                        ptypes_.append("void *")  # `&x` with a pointer parameter is recomputed per call
                    else:
                        if slots is None and other_addr and not e.startswith("(u32)"):
                            regs[f"r{k}"] = f"(u32){e}"
                        ptypes_.append("u32")
                for k in range(1, ftop + 1):
                    ptypes_.append(rtype.get(f"f{k}", "f32"))
                while top >= 3 and ((f"r{top}" not in regs and (f"r{top}" in params or f"r{top}" in def_idx)) or regs.get(f"r{top}") == ""):
                    top -= 1  # a register cleared by an earlier call or region: stale, not an argument
                ptypes_ = ptypes_[:max(0, top - 2)] + ptypes_[len(ptypes_) - len(fargs):] if fargs else ptypes_[:max(0, top - 2)]
                args = [use(f"r{k}") for k in range(3, top + 1)] + fargs  # after the casts
                seen_args: Dict[str, int] = {}
                for e in args:
                    seen_args[e] = seen_args.get(e, 0) + 1
                for e, n_ in seen_args.items():
                    if site_temps and n_ >= 2 and not re.fullmatch(r"[A-Za-z_]\w*|-?\d+|0x[0-9A-Fa-f]+", e):
                        tn = f"v{len(temps)}"
                        tt = next((rtype.get(r_) for r_, ex in regs.items() if ex == e), "u32") or "u32"
                        temps.append(f"{tt} {tn};"); stmts.append(f"{tn} = {e};")
                        args = [tn if x == e else x for x in args]
                        for r_ in list(regs):
                            if regs[r_] == e:
                                regs[r_] = tn
                if callee is None:
                    tname = f"{name}_Fn{len(fn_typedefs)}"
                    fn_typedefs.append(f"typedef u32 (*{tname})({', '.join(ptypes_) or 'void'});")
                    callee = f"(({tname}){indirect[0]})"
                    indirect[0] = None
                if known is not None and slots is not None:
                    try:
                        args = [use(reg) for reg, typ in slots]
                    except Give:
                        raise Give(f"cannot supply recovered signature for {callee}")
                    for (reg, typ), expression in zip(slots, args):
                        local = re.fullmatch(r'&loc_([0-9A-F]+)', expression)
                        if local and signature_index.layout(typ):
                            slocals[int(local[1], 16)].setdefault("type_candidates", set()).add(typ)
                    no_proto = False
                elif known is not None and "..." not in known[1]:
                    raise Give(f"unsupported ABI in recovered signature for {callee}")
                calls.append(callee)
                call_types.append(known[0] if known is not None else "u32")
                written_since_call.clear()
                if callee.startswith("(("):
                    pass  # a pointer call: the typedef carries the prototype
                elif known is not None and no_proto:
                    externs[callee] = f"extern {known[0]} {callee}();"
                elif known is not None:
                    externs[callee] = f"extern {known[0]} {callee}({', '.join(known[1]) or 'void'});"
                elif variadic_next[0]:
                    variadic_next[0] = False
                    proto = f"extern u32 {callee}({ptypes_[0] if ptypes_ else 'void *'}, ...);"
                    externs[callee] = proto
                else:
                    proto = f"extern u32 {callee}({', '.join(ptypes_) or 'void'});"
                    prev = externs.get(callee)
                    if prev is None or prev.endswith("(void);") or (prev.count(",") < proto.count(",") and "..." not in prev):
                        externs[callee] = proto
                variadic_next[0] = False
                stmts.append(f"__CALL__{len(calls) - 1}({', '.join(args)});")
                for r in list(regs):
                    if re.fullmatch(r"r([0-9]|1[0-2])|f([0-9]|1[0-3])", r):
                        regs.pop(r, None)
                if known is not None and known[0] == "void":
                    void_calls.add(len(calls) - 1)  # no result: a later read of r3 is the lifter's error
                else:
                    regs["r3"] = f"__CALLRET__{len(calls) - 1}"; rtype["r3"] = known[0] if known is not None else "u32"
                    if known is not None and signature_index.category(known[0]) == "float":
                        regs.pop("r3", None); regs["f1"] = f"__CALLRET__{len(calls) - 1}"; rtype["f1"] = known[0]
                continue
            raise Give(f"unhandled {mn} {' '.join(a)}")

        except (Give, KeyError, IndexError, ValueError) as e:
            why = (str(e)[:60] if isinstance(e, Give) else f"{type(e).__name__}: {str(e)[:60]}") if str(e) else ("" if isinstance(e, Give) else type(e).__name__)
            if total and i >= 0:
                # never give up: the instruction stays as a marker for the reader (and the agent),
                # its destination register becomes an unknown local so the rest still compiles
                del open_ifs[n_open:]
                stmts[n_stmts:] = [st for st in stmts[n_stmts:] if not st.rstrip().endswith("{")]
                unknown_count[0] += 1
                stmts.append(f"/* ??? {mn} {', '.join(a)}" + (f" ({why})" if why else "") + " */")
                if a and mn not in STORE_T and not mn.startswith(("st", "cmp", "b")) and mn not in ("mtlr", "mtspr", "mtctr") and re.fullmatch(r"[rf]\d+", a[0]):
                    un = f"unk_{unknown_count[0]}"
                    temps.append(f"{'f32' if a[0].startswith('f') else 'u32'} {un};")
                    regs[a[0]] = un; rtype[a[0]] = "f32" if a[0].startswith("f") else "u32"; def_idx[a[0]] = i
                    written_since_call.add(a[0])
                continue
            # a KeyError is the lifter losing track of a register: the same give-up, later
            if not partial or (not isinstance(e, Give) and i < 0):
                raise
            gave_at = i
            gave_why = why
            break
    if total:
        while open_ifs:
            stmts.append(open_ifs.pop()[1])
        if unknown_count[0]:
            stmts.insert(0, f"/* {unknown_count[0]} instruction(s) not lifted: see the ??? markers */")
    if partial and gave_at is not None:
        left = len(ins) - gave_at
        nxt = "; ".join(f"{m_} {', '.join(a_)}" for m_, a_ in ins[gave_at:gave_at + 4])
        # what the registers held at that point, for the reader: not code, the values are partial
        held = [f"/* {r_} = {e_} */" for r_, e_ in sorted(regs.items()) if e_ and not re.fullmatch(r"(arg\d+|v\d+|t\d+|\d+|0x[0-9A-Fa-f]+)", e_)]
        stmts.extend(held[:12])
        stmts.append(f"/* NOT LIFTED from here: {left} instructions, starting `{nxt}`" + (f" ({gave_why})" if gave_why else "") + " */")
        regs.clear()
    for ln_, asg in pending_ptr.items():
        if any(re.search(rf"\b{re.escape(ln_)}\b", e) for e in regs.values()):
            stmts.append(asg)
    pending_ptr.clear()
    # return value: whatever r3 holds at blr, when this function wrote r3 (an untouched first
    # parameter is not a return value; a parameter copied back after a call is)
    wrote_r3 = any(a and a[0] == "r3" and mn not in ("stw", "sth", "stb", "stfs", "stfd", "cmpwi", "cmpw", "cmplwi", "cmplw") for mn, a in ins)
    if partial and gave_at is not None:
        wrote_r3 = False  # the return value is beyond the give-up point
    # the last write to r3 decides: an address materialisation (`lis r3, sym@ha`) is scratch,
    # and a value the function consumed afterwards (stored, compared) is not a return value
    last_w = max((x for x, (mn_, a_) in enumerate(ins) if a_ and a_[0] == "r3" and mn_ not in STORE_T and not mn_.startswith(("st", "cmp", "b")) and mn_ not in ("mtlr", "mtspr", "mtctr")), default=None)
    if last_w is not None:
        mn_l, a_l = ins[last_w]
        if mn_l == "lis" and a_l and a_l[1].endswith("@ha"):
            wrote_r3 = False
        elif any(reads(x, "r3") and ins[x][0] not in ("mr",) for x in range(last_w + 1, len(ins)) if ins[x][0] != "blr") and not any(ins[x][0] in ("bl", "bctrl", "blrl") for x in range(last_w + 1, len(ins))):
            wrote_r3 = False
    if "r3" in regs and wrote_r3 and not regs["r3"].startswith("__CALLRET__"):
        ret = regs["r3"]  # a call's result falls through in r3 either way: `void f(void) { g(); }`
    # a call whose result is returned becomes `return f(...)`; one whose result feeds later code
    # becomes a temporary; the rest are statements
    f1_ret = regs.get("f1") if ("f1" in regs and any(a_ and a_[0] == "f1" for mn_, a_ in ins if mn_ != "blr")) else None
    used_ret = {i for i in range(len(calls)) if any(re.search(rf"__CALLRET__{i}\b", st) for st in stmts if not st.startswith(f"__CALL__{i}(")) or (ret is not None and re.search(rf"__CALLRET__{i}\b", ret)) or (f1_ret is not None and re.search(rf"__CALLRET__{i}\b", f1_ret))}
    structs: List[str] = []
    body = []
    for st in stmts:
        m = re.match(r"__CALL__(\d+)\((.*)\);", st)
        if m:
            i = int(m.group(1)); call = f"{calls[i]}({m.group(2)})"
            if ret == f"__CALLRET__{i}" and not any(f"__CALLRET__{i}" in x for x in stmts if x != st):
                body.append(f"return {call};"); ret = None
            elif i in used_ret:
                body.append(f"{call_types[i]} t{i} = {call};")
            else:
                body.append(f"{call};")
        else:
            body.append(st)
    for vi in void_calls:
        body = [re.sub(rf"^u32 t{vi} = ", "", b) for b in body]
        body = [re.sub(rf"__CALLRET__{vi}\b", "0", b) for b in body]  # the lifter misread a void result
    body = [re.sub(r"__INLINECALL__(\d+)\(", lambda m_: f"{calls[int(m_.group(1))]}(", b) for b in body]
    body = [re.sub(r"__CALLRET__(\d+)", r"t\1", b) for b in body]
    if ret is not None:
        ret = re.sub(r"__CALLRET__(\d+)", r"t\1", ret)
    # temporaries must be declared before any statement: hoist them
    call_decls = []
    for ci, ctype in enumerate(call_types):
        prefix = f"{ctype} t{ci} = "
        if any(b.startswith(prefix) for b in body):
            call_decls.append(f"{ctype} t{ci};")
            body = [b.replace(prefix, f"t{ci} = ", 1) if b.startswith(prefix) else b for b in body]
    body = call_decls + body
    # A typed callee constrains the entire address-taken object, including earlier stores.
    for off, ent in slocals.items():
        candidates = ent.get("type_candidates", set())
        if len(candidates) != 1:
            continue
        pointer = next(iter(candidates))
        fields_, size = signature_index.layout(pointer)
        extent = (next((o for o in taken if o > off), top_of_locals) - off)
        if copy_dst_locals.get(off, size) != size or size > extent:
            continue
        if any(inner + width > size for inner, (width, _) in ent.get("elems", {}).items()):
            continue
        ent["ctype"] = re.sub(r'\b(const|volatile)\s*', '', pointer[:-1]).strip()
        for k, line in enumerate(body):
            body[k] = re.sub(rf'^(loc_{off:X} = )\*\(struct {name}_Copy{size} \*\)',
                             rf'\1*({ent["ctype"]} *)', line)
    for token, (off, inner, typ, fallback) in local_accesses.items():
        ctype = slocals[off].get("ctype")
        member = signature_index.member(ctype + ' *', inner, typ) if ctype else None
        expression = f'loc_{off:X}.{member[0]}' if member else (
            f'*({typ} *)((u8 *)&loc_{off:X} + {inner})' if ctype else fallback)
        if member and signature_index.category(member[1]) == 'pointer':
            body = [re.sub(rf'^{token} = (.*);$', rf'{token} = ({member[1]})(\1);', b) for b in body]
        body = [b.replace(token, expression) for b in body]
        if ret:
            ret = ret.replace(token, expression)
    if slocals:
        offs = sorted(slocals)
        top = min(saved_slots) if saved_slots else frame_size
        decls = []
        for i_, off_ in enumerate(offs):
            ent = slocals[off_]
            nxt = offs[i_ + 1] if i_ + 1 < len(offs) else top
            size = max(nxt - off_, ent["w"] or 1)
            w = ent["w"] or 1
            if ent.get("ctype"):
                decls.append((off_, f"{ent['ctype']} loc_{off_:X};", "struct")); continue
            if off_ in copy_dst_locals:
                decls.append((off_, f"struct {name}_Copy{copy_dst_locals[off_]} loc_{off_:X};", "struct")); continue
            if not ent["w"] and size in (1, 2, 4, 8):  # address only: a scalar of that size
                ent["t"] = {1: "u8", 2: "u16", 4: "u32", 8: "f64"}[size]; w = size
            elif not ent["w"] and size % 4 == 0:
                ent["t"] = "u32"; w = 4  # a u8 buffer would be 16-aligned by MWCC; a u32 array is not
            # the element count follows the final element type: an address-only buffer was
            # measured in bytes (width unknown at the use) and is declared as u32 here
            if ent.get("wrapped"):
                decls.append((off_, f"struct {{ {ent['t']} a[{max(size // w, 1)}]; }} loc_{off_:X};", "struct")); continue
            if ent.get("array"):
                decls.append((off_, f"{ent['t']} loc_{off_:X}[{max(size // w, 1)}];", True)); continue
            if size > w and size >= 16:
                decls.append((off_, f"struct {{ {ent['t']} a[{max(size // w, 1)}]; }} loc_{off_:X};", "struct")); continue
            if size > w:
                decls.append((off_, f"{ent['t']} loc_{off_:X}[{max(size // w, 1)}];", True))
            else:
                # a scalar whose address is taken: `&x` at each use, which MWCC does not hoist
                # (an array's decay it does, into a saved register)
                decls.append((off_, f"{ent['t']} loc_{off_:X};", False))
        if layout == "grouped":  # scalars first, arrays after, each group highest offset first
            ordered = [d for d in sorted(decls, key=lambda x: -x[0]) if d[2] is False] + [d for d in sorted(decls, key=lambda x: -x[0]) if d[2] is not False]
        else:  # highest frame offset declared first
            ordered = sorted(decls, key=lambda x: -x[0])
        body = [d[1] for d in ordered] + ["/* frame */"] + body
        # an address-taken array is passed as itself, not &array, and cast like every address
        arrays = {f"loc_{d[0]:X}" for d in decls if d[2] is True}  # struct-wrapped ones keep the &
        for arr in arrays:
            body = [re.sub(rf"(?<![\w.>&]){arr}\b(?!\s*\[|\s*=[^=])", f"(u32){arr}", b) if not re.match(rf"^\s*\w[\w ]*\s+{arr}\[", b) else b for b in body]
        def fix_addr(b: str) -> str:
            return re.sub(r"&(loc_[0-9A-F]+)\b", lambda m: m.group(1) if m.group(1) in arrays else f"&{m.group(1)}", b)
        body = [fix_addr(b) if not b.startswith(("u8 loc", "u32 loc", "f32 loc", "s16 loc", "u16 loc", "s8 loc", "f64 loc", "struct {")) else b for b in body]
    if temps:
        # a temporary's type follows its first assignment: a pointer global's struct pointer,
        # `u8 *` for byte arithmetic and addresses, a struct pointer for the cast form
        ptr_types = {g: f"struct {name}_{g}_T *" for g in pfields}
        fixed_temps = []
        for tdecl in temps:
            m_ = re.fullmatch(r"(\S+) (v\d+);", tdecl)
            if m_:
                init_line = next((b for b in body if re.match(rf"{m_.group(2)} = ", b)), None)
                if init_line:
                    rhs = init_line[len(m_.group(2)) + 3:].rstrip(";")
                    if rhs in ptr_types:
                        tdecl = f"{ptr_types[rhs]}{m_.group(2)};"
                    else:
                        ms = re.match(r"\(struct (\w+) \*\)", rhs)
                        if ms:
                            tdecl = f"struct {ms.group(1)} *{m_.group(2)};"
            fixed_temps.append(tdecl)
        body = fixed_temps + body
    if locals_:
        body = [f"struct {name}_{g} *{ln};" for ln, g in locals_.items()] + body
    # an address stored or passed is a pointer: cast, so u32 fields and parameters accept it
    body = [b if b.startswith("p_") else re.sub(r"= (&[A-Za-z_]\w*(?:\[0\])?);", r"= (u32)\1;", b) for b in body]
    fnames = {s for s, e in externs.items() if e.startswith("extern void ") and e.endswith("(void);")}
    for f in fnames:
        body = [re.sub(rf"(= ){re.escape(f)}(?=;)", rf"\1(u32){f}", b) for b in body]
    if ret is not None:
        if ret.startswith(("&", "((u8 *)", "(u8 *)", "(struct ")) and not rtype.get("r3", "").endswith("*"):
            ret = f"(u32){ret}"  # an address returned as an integer
        body.append(f"return {ret};")
    if not partial and not total and (any(("__MULHU__" in b or "__I2D__" in b or "__XORIS__" in b or "__FCTIWZ__" in b) for b in body) or (ret and any(x in ret for x in ("__MULHU__", "__I2D__", "__XORIS__", "__FCTIWZ__")))):
        raise Give()
    def peephole(b: str) -> str:
        m = re.fullmatch(r"(\S.*?) = \((\S.*?) ([+-]) (\d+)\);", b)
        if m and m.group(1) == m.group(2):
            k = int(m.group(4))
            if k == 1:
                return f"{m.group(1)}{'++' if m.group(3) == '+' else '--'};"
            return f"{m.group(1)} {m.group(3)}= {k};"
        return b
    body = [peephole(b) for b in body]
    body = [re.sub(r"\((\S+) - \(\(\1 / (\d+)\) \* \2\)\)", r"(\1 % \2)", b) for b in body]
    rtype_c = "void"
    if any(b.startswith("return ") for b in body):
        rtype_c = rtype.get("r3", "u32")
    if rtype_c == "void":
        body = [b.replace("return __RET__;", "return;") for b in body]
    else:
        # r3 at an early return holds the first parameter unless something wrote it before
        body = [b.replace("return __RET__;", f"return {'arg0' if params and params[0] == 'r3' else '0'};") for b in body]
    if "f1" in regs and any(a and a[0] == "f1" for mn, a in ins if mn != "blr") and not any(b.startswith("return ") for b in body):
        body.append(f"return {re.sub(r'__CALLRET__(\d+)', r't\1', regs['f1'])};"); rtype_c = rtype.get("f1", "f32")
        if rtype_c in ("s8", "s16"): rtype_c = "s32"
    if own_signature and own_signature.result == 'void':
        body = ['return;' if b.startswith('return ') else b for b in body]
        if body and body[-1] == 'return;':
            body.pop()
        rtype_c = 'void'
    def field_width(t: str) -> int:
        if t.startswith("arr:"):
            return int(t.rsplit(":", 1)[1])  # one element: enough for the padding that follows
        return {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "f32": 4, "f64": 8}[t]

    def field_decl(t: str, o: int) -> str:
        if t.startswith("arr:"):
            _, et, _ = t.split(":", 2) if t.count(":") == 2 else (None, t[4:t.rfind(":")], None)
            et = t[4:t.rfind(":")]
            return f"{et} unk_{o:X}[1];"
        return f"{t} unk_{o:X};"

    # a struct global used as a plain value reads its first field (before the struct texts)
    for g, offs in list(gfields.items()):
        if not offs:
            continue
        pat = re.compile(rf"(?<![\w.>&]){re.escape(g)}\b(?![\w.\[]|\s*=\s*\(struct)")
        if any(pat.search(b) for b in body if not b.startswith("extern")):
            w0 = next((t_ for o_, t_ in sorted(offs.items()) if o_ > 0 and not str(t_).startswith("arr:")), "u32")
            offs.setdefault(0, w0 if w0 in ("u8", "s8", "u16", "s16", "u32", "s32", "f32") else "u32")
            body = [pat.sub(f"{g}.unk_0", b) if not b.startswith("extern") else b for b in body]
    structs.extend(elem_struct_texts())
    structs = fn_typedefs + structs
    # parameters and struct parameters
    decl_params = []
    for i, r in enumerate(params):
        if r in fields:
            sname = f"{name}_Arg{i}"
            offs = fields[r]
            lines = [f"struct {sname} {{"]
            cur = 0
            for o in sorted(offs):
                if o > cur:
                    lines.append(f"    u8 pad_{cur:X}[0x{o - cur:X}];")
                lines.append("    " + field_decl(offs[o], o))
                cur = o + field_width(offs[o])
            lines.append("};")
            structs.append("\n".join(lines))
            decl_params.append(f"struct {sname} *arg{i}")
        else:
            typ = ptypes[r]
            decl_params.append(re.sub(r'\(\s*\*\s*\)', f'(*arg{i})', typ, count=1)
                               if re.search(r'\(\s*\*\s*\)', typ) else f"{typ} arg{i}")
    if calls and not frame and not partial and not total:
        raise Give()
    def struct_text(sname: str, offs: Dict[int, str]) -> str:
        lines = [f"struct {sname} {{"]
        cur = 0
        for o in sorted(offs):
            if o > cur:
                lines.append(f"    u8 pad_{cur:X}[0x{o - cur:X}];")
            lines.append("    " + field_decl(offs[o], o))
            cur = o + field_width(offs[o])
        lines.append("};")
        return "\n".join(lines)
    empty_globals = [g for g, offs in gfields.items() if not offs]
    for size in sorted(copy_types | set(copy_dst_locals.values())):
        structs.append(f"struct {name}_Copy{size} {{ u32 a[{size // 4}]; }};")
    for g, offs in gfields.items():
        sname = f"{name}_{g}"
        if not offs:
            externs[g] = f"extern u8 {g}[];"
            continue
        structs.append(struct_text(sname, offs))
        externs[g] = f"extern struct {sname} {g};"
    far_structs = set()
    for g, offs in pfields.items():
        sname = f"{name}_{g}_T"
        structs.append(struct_text(sname, offs))
        externs[g] = f"extern struct {sname} *{g};"
    for g in empty_globals:
        sname = f"{name}_{g}"
        body = [b.replace(f"struct {sname} *", "u8 *").replace(f"(struct {sname} *)", "(u8 *)") for b in body]
    for g in pfields:
        body = [re.sub(rf"^{re.escape(g)} = (?!\(struct)", f"{g} = (struct {name}_{g}_T *)", b) for b in body]
    value_types = {f'arg{i}': ptypes[r] for i, r in enumerate(params)}
    for line in body:
        decl = re.fullmatch(r'(?!return\b)([\w *]+?)\s+([vt]\d+);', line)
        if decl:
            value_types[decl[2]] = decl[1].strip()
    value_types.update({n: 'void *' for n in ptr_globals | set(locals_)})
    def expression_type(expr):
        if expr in value_types:
            return value_types[expr]
        cast = re.match(r'^\(([\w *]+)\)', expr)
        if cast:
            return cast[1]
        if expr.startswith('&'):
            return 'void *'
        return None
    # Cast only at C type boundaries; register moves themselves preserve pointer types.
    for c, proto in list(externs.items()):
        m_p = re.match(r"extern ([\w *]+?) (\w+)\((.*)\);$", proto)
        if not m_p or m_p.group(3).strip() in ("", "void", "..."):
            continue
        ptl = [x.strip() for x in m_p.group(3).split(",")]
        vpos = [k for k, x in enumerate(ptl) if x.endswith("*") or x in ("u32", "s32", "u16", "s16", "u8", "s8", "int")]
        if not vpos:
            continue
        ptypes_p = {k: ptl[k] for k in vpos}
        def fix_call(b: str) -> str:
            out_b = ""; pos = 0
            while True:
                m_c = re.search(rf"\b{re.escape(c)}\(", b[pos:])
                if not m_c:
                    return out_b + b[pos:]
                start = pos + m_c.end(); depth = 1; j = start
                while j < len(b) and depth:
                    depth += (b[j] == "(") - (b[j] == ")"); j += 1
                inner = b[start:j - 1]
                args = []; cur = ""; dp = 0
                for ch in inner:
                    if ch == "," and dp == 0:
                        args.append(cur.strip()); cur = ""; continue
                    dp += (ch == "(") - (ch == ")"); cur += ch
                if cur.strip() or args:
                    args.append(cur.strip())
                for k in vpos:
                    if k >= len(args) or args[k].startswith("(" + ptypes_p[k] + ")"):
                        continue
                    if ptypes_p[k].endswith("*"):
                        args[k] = f"({ptypes_p[k]}){args[k]}"
                    elif signature_index.category(expression_type(args[k]) or '') == 'pointer' or args[k].startswith(("&", "loc_", "(u8 *)", "((u8 *)", "(struct ")):
                        args[k] = f"(u32){args[k]}"  # an address to an integer parameter
                out_b += b[pos:pos + m_c.start()] + f"{c}({', '.join(args)})"; pos = j
        body = [fix_call(b) for b in body]
    ptr_names = [f"arg{i}" for i, r in enumerate(params) if r in fields] + [ln for ln in locals_ if ln.startswith("p_")] + list(pfields)
    decl_line = re.compile(r"^\s*(?!return\b)(struct\s+\w+\s*\*+|[A-Za-z_]\w*\s*\*+|[A-Za-z_]\w*\s+)\s*[A-Za-z_]\w*(\[[^\]]*\])*;$")
    for pn in ptr_names:
        body = [re.sub(rf"(?<![\w>.*])({re.escape(pn)})\b(?!\s*->|\s*=\s*\(struct)", r"(u32)\1", b)
                if not (b.startswith(f"{pn} = ") or decl_line.match(b)) else b for b in body]
    def assignment_cast(line):
        assignment = re.fullmatch(r'([vt]\d+) = (.*);', line)
        if not assignment:
            return line
        target, expr = assignment.groups()
        typ = value_types.get(target, 'u32')
        source = expression_type(expr)
        if signature_index.category(typ) == 'pointer':
            expr = re.sub(r'^\(u32\)', '', expr)
            if expression_type(expr) != typ:
                return f'{target} = ({typ})({expr});'
            return f'{target} = {expr};'
        elif source and signature_index.category(source) == 'pointer':
            return f'{target} = ({typ})({expr});'
        return line
    body = [assignment_cast(line) for line in body]
    body = [f'return ({rtype_c})({line[7:-1]});'
            if line.startswith('return ') and line.endswith(';')
            and expression_type(line[7:-1])
            and signature_index.category(expression_type(line[7:-1])) != signature_index.category(rtype_c)
            and signature_index.category(rtype_c) in ('integer', 'pointer') else line for line in body]
    body = [b + "  /* fzgx-allow: A1,A2 unnamed OS/hardware memory */" if re.search(r"\(\s*[\w\s]+\*\s*\)\s*0[xX][0-9A-Fa-f]{8}", b) else b for b in body]
    if module == "main":
        small = {".sdata", ".sbss", ".sdata2", ".sbss2"}
        # a global outside the small-data sections is addressed far in retail whatever its size:
        # MWCC assumes an extern of 8 bytes or less is small, so such a global is declared as an
        # array of unknown size and read through [0]
        for g in list(gfields):
            sd = lookup(g)
            if sd is None or sd.section in small or not gfields[g] or g in locals_.values():
                continue
            sname = f"{name}_{g}"
            externs[g] = f"extern struct {sname} {g}[];"
            body = [re.sub(rf"(?<![\w>.]){re.escape(g)}\.unk_", f"{g}[0].unk_", b) for b in body]
        def padded(text_: str, g: str) -> str:
            sd = lookup(g)
            if sd is None or sd.section in small or sd.size <= 8:
                return text_
            # size of the struct as written: from the last field / pad
            m_ = re.search(r"    (\w[\w ]*?) (unk|pad)_([0-9A-F]+)(\[0x([0-9A-F]+)\])?;\n\};$", text_)
            if not m_:
                return text_
            off = int(m_.group(3), 16)
            w = int(m_.group(5), 16) if m_.group(5) else {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "f32": 4, "f64": 8}.get(m_.group(1).strip(), 4)
            end = off + w
            if end <= 8 and sd.size > end:
                return text_[:-3] + f"    u8 pad_{end:X}[0x{sd.size - end:X}];\n}};"
            return text_
        for g in list(gfields):
            sname = f"{name}_{g}"
            structs = [padded(t_, g) if t_.startswith(f"struct {sname} {{") else t_ for t_ in structs]
    externs.pop(name, None)  # never a declaration of the function itself
    types_header = 'dolphin/types.h' if any(hw in externs for hw in HW_BLOCKS.values()) else 'types.h'
    text = [f'#include "{types_header}"'] + signature_index.preamble(signatures_used.values()) + [""]
    if structs:
        text += structs + [""]
    text += sorted(externs.values())
    # a function retail placed in .init (boot, cache and debug code) must be sectioned the same
    # way, or objdiff pairs nothing and the link puts it in .text
    sect = p.symbols(module).get(name)
    decl_sec = '__declspec(section ".init") ' if sect is not None and sect.section == ".init" else ""
    text += ["", f"{decl_sec}{rtype_c} {name}({', '.join(decl_params) or 'void'}) {{"]
    text += [f"    {b}" for b in body]
    text += ["}", ""]
    return "\n".join(text)


def apply(p: Project, modules: Optional[List[str]] = None, max_size: int = 160, limit: int = 2000,
          workers: int = 12, submit: bool = True, tu: Optional[str] = None,
          callees: Optional[List[str]] = None, engine: str = 'lift', resume: bool = False,
          symbols: Optional[List[str]] = None) -> Dict[str, object]:
    """Lift every unmatched function of the given size that the lifter accepts, check each
    against retail, submit the matches (carve-at-submit; `fzgx verify` relinks once)."""
    import sqlite3
    from concurrent.futures import ThreadPoolExecutor
    from . import api, oracle
    from .project import STATE_DIR
    db = sqlite3.connect(str(STATE_DIR / "ledger.db"))
    q = "select symbol, module, size from functions where status='unmatched' and size <= ?"
    args: List[object] = [max_size]
    if symbols:
        selected = []
        for name in symbols:
            sym = p.resolve(name)
            if sym is None:
                raise ValueError(f'unknown or ambiguous function: {name}')
            selected.append(p.key(sym))
        args[0] = 0xFFFFFFFF
        q += ' and symbol in (%s)' % ','.join('?' for _ in selected)
        args += selected
    if tu:
        selected = []
        for mod in modules or p.modules:
            path = p.module_config_dir(mod) / 'tus.json'
            if not path.exists():
                continue
            for entry in json.loads(path.read_text())['tus']:
                if f'{p.module_src_prefix(mod)}/{entry["file"]}' == tu:
                    selected.extend(p.key(p.symbols(mod)[n]) for n in entry['functions'])
        if not selected:
            raise ValueError(f'unknown TU: {tu}; use a path relative to src/')
        args[0] = 0xFFFFFFFF
        q += ' and symbol in (%s)' % ','.join('?' for _ in selected)
        args += selected
    if callees:
        targets = set()
        for name in callees:
            sym = p.resolve(name)
            if sym is None or p.callable_asm(sym) is None:
                raise ValueError(f'unknown or ambiguous callee: {name}')
            targets.add(p.key(sym))
        selected = []
        for mod in modules or p.modules:
            for fn in p.function_asm(mod).values():
                for line in fn.asm:
                    call = re.match(r'^[0-9A-Fa-f]+:\s*b[l]?\s+(\w+)$', line.strip())
                    if not call:
                        continue
                    target = p.symbols(mod).get(call[1]) or p.find_symbol(call[1])
                    if target and p.key(target) in targets:
                        selected.append(p.key(fn.symbol))
                        break
        if not selected:
            return {"candidates": 0, "lifted": 0, "matched": 0, "fixed": 0,
                    "bytes": 0, "submitted": 0, "failed": [], "near": []}
        args[0] = 0xFFFFFFFF
        q += ' and symbol in (%s)' % ','.join('?' for _ in selected)
        args += selected
    if modules:
        q += " and module in (%s)" % ",".join("?" * len(modules)); args += list(modules)
    rows = db.execute(q + " order by size limit ?", args + [limit or -1]).fetchall()
    linkfail = {s for (s,) in db.execute("select symbol from attempts a where id = (select max(id) from attempts b where b.symbol = a.symbol) and outcome = 'link-mismatch'")}
    lifted = []
    errors = {}
    serial_rows = rows
    out_dir = STATE_DIR / "lift" / engine if engine != 'lift' else STATE_DIR / "lift"
    if resume:
        if engine != 'm2c':
            raise ValueError('--resume requires --engine m2c')
        previous_errors = json.loads((out_dir / 'errors.json').read_text())
        failed_compile = set()
        previous_results = out_dir / 'results.json'
        if previous_results.exists():
            best_scores = {}
            for s, _, _, _, percent in json.loads(previous_results.read_text()):
                best_scores[s] = max(best_scores.get(s, -1), percent)
            failed_compile = {s for s, percent in best_scores.items() if percent < 0}
        retry = []
        for s, m, size in rows:
            sources = [out_dir / (s.replace(':', '__') + suffix + '.c') for suffix in ('', '__v1')]
            if s in previous_errors or s in failed_compile or not sources[0].exists():
                retry.append((s, m, size))
            else:
                for vi, source in enumerate(sources):
                    if source.exists():
                        lifted.append((s if vi == 0 else f'{s}#{vi}', size, source.read_text()))
        serial_rows = retry
    if engine == 'm2c' and workers > 1:
        from concurrent.futures import ProcessPoolExecutor, as_completed
        from .machine import generate_batch
        import sys
        groups = {}
        owners = {}
        for module in modules or p.modules:
            path = p.module_config_dir(module) / 'tus.json'
            if path.exists():
                for entry in json.loads(path.read_text())['tus']:
                    owners.update({(module, name): entry['file'] for name in entry['functions']})
        for row in serial_rows:
            s, m, _ = row
            if s not in linkfail:
                groups.setdefault((m, owners.get((m, s.split(':')[-1]))), []).append(row)
        batches = [group[i:i + 32] for group in groups.values() for i in range(0, len(group), 32)]
        done = 0
        with ProcessPoolExecutor(max_workers=workers) as executor:
            futures = [executor.submit(generate_batch, batch) for batch in batches]
            for future in as_completed(futures):
                for s, size, variants, error in future.result():
                    if error:
                        errors[s] = error
                    for vi, text in enumerate(variants):
                        lifted.append((s if vi == 0 else f'{s}#{vi}', size, text))
                    done += 1
                print(f'm2c: {done}/{len(rows)} functions, {len(lifted)} candidates', file=sys.stderr, flush=True)
        lifted.sort(key=lambda row: (row[1], row[0]))
        serial_rows = []
    for row_index, (s, m, size) in enumerate(serial_rows):
        if s in linkfail:
            continue  # matched the object and failed the link before: the same body fails again
        name = s.split(":", 1)[1] if ":" in s else s
        try:
            if engine == 'm2c':
                from . import machine
                variants = []
                draft = lift_total(p, m, name, max_ins=max(1200, size // 4))
                for descending in (False, True):
                    text, error = machine.generate(p, m, name, draft=draft, descending=descending)
                    if text and text not in variants:
                        variants.append(text)
                    elif error:
                        errors[s] = error
                        break
            elif tu or callees or max_size > 640:
                draft = lift_total(p, m, name, max_ins=max(1200, size // 4))
                variants = [draft] if draft else []
            else:
                variants = lift_variants(p, m, name)
        except Exception as error:
            variants = []
            errors[s] = str(error)
        for vi, t in enumerate(variants):
            lifted.append((s if vi == 0 else f"{s}#{vi}", size, t))
        if engine == 'm2c' and row_index % 50 == 0:
            import sys
            print(f'm2c: {row_index + 1}/{len(rows)} functions, {len(lifted)} candidates', file=sys.stderr, flush=True)
    out_dir = STATE_DIR / "lift" / engine if engine != 'lift' else STATE_DIR / "lift"
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / 'errors.json').write_text(json.dumps(errors, indent=2))
    (out_dir / 'generation.json').write_text(json.dumps(lifted))

    # one mwcc run per module over every lifted body, one cheap score each, the full check only
    # for the ones that score 100 (pool rows, data sections)
    results = []
    by_mod: Dict[str, list] = {}
    for s, size, t in lifted:
        s0 = s.split("#")[0]
        by_mod.setdefault(s0.split(":")[0] if ":" in s0 else p.resolve(s0).module, []).append((s, size, t))
    for mod, items in by_mod.items():
        srcs = []
        for s, size, t in items:
            src = out_dir / (s.replace(":", "__").replace("#", "__v") + ".c"); src.write_text(t); srcs.append(src)
        cands = oracle.version_candidates(p, mod)
        per_ver = {c: oracle.compile_many(p, mod, srcs, out_dir / "obj" / mod / (c[0].replace("/", "_") + ("_stmw" if c[1] else "")), c[0], c[1]) for c in cands}
        for (s, size, t), src in zip(items, srcs):
            s = s.split("#")[0]  # a layout variant of the same function
            sym = p.resolve(s)
            target = p.target_object_for(sym) if sym else None
            if target is None:
                results.append((s, size, t, False, -1)); continue
            tw_ = oracle.words(target, sym.name)
            best = None
            for c in cands:
                o = per_ver[c].get(src)
                ow_ = oracle.words(o, sym.name) if o else None
                if not tw_ or not ow_:
                    continue
                pct_, bad_ = oracle.word_score(tw_, ow_)
                if best is None or pct_ > best[0]:
                    best = (pct_, c, bad_, ow_)
            if best is None:
                results.append((s, size, t, False, -1)); continue
            pct, c, bad_, ow_ = best
            ok_ = (not bad_ and len(ow_) == len(tw_)
                   and not re.search(r'\?\?\?|__(?:MULHU|I2D|XORIS|FCTIWZ)__', t))
            if ok_:
                r = oracle.check(p, s, 4, source=src, mw_version=c[0], extra_cflags=c[1])
                ok_ = r.ok and (r.matched or r.matched_pool) and oracle.unit_fully_matches(r) is None
            results.append((s, size, t, ok_, pct))
    (out_dir / 'results.json').write_text(json.dumps(results))
    # near misses get the deterministic fixup (type flips, symbol substitutions, layout edits)
    from . import fixup
    fixed = 0
    todo_fx = [idx for idx, (s, size, t, ok, pct) in enumerate(results) if not ok and pct >= 60
               and not re.search(r'\?\?\?|__(?:MULHU|I2D|XORIS|FCTIWZ)__', t)]

    groups = {}
    for idx in todo_fx:
        groups.setdefault(results[idx][0], []).append(idx)

    def fix_group(indices):
        out = []
        # Fixup and the oracle have per-symbol scratch objects. Layout variants
        # of one function must be serial, even while other functions run in parallel.
        for idx in sorted(indices, key=lambda i: -results[i][4]):
            s, size, t, ok, pct = results[idx]
            try:
                result = fixup.try_fix(p, s, t, budget_s=10.0)
            except Exception:
                result = {}
            out.append((idx, result))
            if result.get('matched'):
                break
        return out
    # the repairs land on drafts from 60% up (register order and declaration style close them)
    with ThreadPoolExecutor(max_workers=6) as ex:
        for group in ex.map(fix_group, groups.values()):
            for idx, fx in group:
                if fx.get("matched") and fx.get("body"):
                    s, size, t, ok, pct = results[idx]
                    results[idx] = (s, size, fx["body"], True, 100.0); fixed += 1
    best: Dict[str, tuple] = {}
    for s, size, t, ok, pct in results:
        if s not in best or (ok, pct) > (best[s][3], best[s][4]):
            best[s] = (s, size, t, ok, pct)
    results = list(best.values())
    # the per-function best draft and its score, for the lab and the context (no rescoring later)
    scores_path = STATE_DIR / "lift" / "scores.json"
    try:
        prev = json.loads(scores_path.read_text()) if scores_path.exists() else {}
    except ValueError:
        prev = {}
    for s, size, t, ok, pct in results:
        previous = prev.get(s, {})
        if (bool(ok), pct) >= (previous.get('matched', False), previous.get('percent', -1)):
            prev[s] = {"percent": pct, "matched": bool(ok), "text": t, "engine": engine}
    scores_path.write_text(json.dumps(prev))
    matched = [(s, size, t) for s, size, t, ok, _ in results if ok]
    submitted, failed = [], []
    if submit:
        for s, size, t in matched:
            work = p.work_path(s if ":" in s else p.key(p.resolve(s)))
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(t)
            r = api.submit(p, s, agent="lift", message=f"deterministic {engine} output", harness="fzgx", model=engine)
            (submitted if r.get("ok") else failed).append(s if r.get("ok") else (s, str(r.get("error"))[:80]))
            if not r.get('ok'):
                prev[s] = {'percent': r.get('percent', 0), 'matched': False, 'text': t, 'engine': engine}
        scores_path.write_text(json.dumps(prev))
    return {"candidates": len(rows), "lifted": len(lifted), "matched": len(matched), "fixed": fixed, "bytes": sum(x[1] for x in matched),
            "submitted": len(submitted), "failed": failed[:10],
            "near": sorted(((s, round(pc, 1)) for s, _, _, ok, pc in results if not ok and pc >= 80), key=lambda x: -x[1])[:10]}
