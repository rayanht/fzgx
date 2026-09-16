"""Paired-single vector kernels: rewrite per-component float statements into the inline
assembly helpers of include/psvec.h.

Retail addresses the x/y lanes of a Vec with `psq_l`/`psq_st` and a displacement, and
MWCC's __vec2x32float__ only ever emits the indexed `psq_lx`/`psq_stx`, so the retail
form can come only from inline assembly inlined into the caller. Each helper below was
validated byte-exact against retail (2026-09-15: psvec_sub fn_1_105BD8, psvec_add
fn_1_FB50, psvec_set fn_1_2A694/fn_1_7EB8C, psvec_scale_add fn_1_236CC,
psvec_sub_scale_add fn_1_108A90).

The rewrite works on statement triples: three consecutive assignments whose left-hand
sides are the x, y and z components of one vector and whose right-hand sides have the
same shape over the matching components of other vectors.
"""
from __future__ import annotations

import re
from typing import Dict, List, Optional, Tuple

HEADER = '#include "psvec.h"'
KERNEL_MNEMONICS = ('ps_sub', 'ps_add', 'ps_muls0', 'ps_madds0', 'ps_merge00')

# component access forms; each yields (base text, byte offset of the component)
_MEMBER = re.compile(r'^(.*?)(->|\.)(x|y|z)$', re.S)
_ARRAY = re.compile(r'^(.*?)\[\s*([0-2])\s*\]$', re.S)
_HEXMEMBER = re.compile(r'^(.*?)(->|\.)(?:unk|field|v|f|val|var)_?([0-9A-Fa-f]{1,4})$', re.S)
_RAW = re.compile(r'^\*\s*\(\s*(?:const\s+)?(?:f32|float)\s*\*\s*\)\s*\(\s*\(\s*(?:const\s+)?(?:u8|char|unsigned char)\s*\*\s*\)\s*(.*?)\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\)$', re.S)
_CAST = re.compile(r'^\(\s*(?:f32|float)\s*\)\s*', re.S)


def _strip(text: str) -> str:
    text = text.strip()
    while text.startswith('(') and text.endswith(')'):
        depth = 0
        for k, ch in enumerate(text):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0 and k != len(text) - 1:
                    return text
        text = text[1:-1].strip()
    return text


class Access(tuple):
    """(kind, base, byte offset) of a scalar component access plus its source text."""
    text = ''


def _access(text: str) -> Optional[Access]:
    text = _strip(text)
    found = None
    m = _MEMBER.match(text)
    if m:
        base = m.group(1).strip()
        if base and not re.search(r'[+\-*/]\s*$', base):
            found = ('member', base, 'xyz'.index(m.group(3)) * 4)
    if found is None:
        m = _ARRAY.match(text)
        if m:
            base = m.group(1).strip()
            if base and not re.search(r'[+\-*/]\s*$', base):
                found = ('array', base, int(m.group(2)) * 4)
    if found is None:
        m = _RAW.match(text)
        if m:
            found = ('raw', _strip(m.group(1)), int(m.group(2), 0))
    if found is None:
        m = _HEXMEMBER.match(text)
        if m:
            base = m.group(1).strip()
            off = int(m.group(3), 16)
            if base and off % 4 == 0:
                found = ('hex', base + m.group(2) + text[len(m.group(1)) + len(m.group(2)):][:-len(m.group(3))].lower(), off)
    if found is None:
        return None
    out = Access(found)
    out.text = text
    return out


def _paren(text: str) -> str:
    return text if re.fullmatch(r'[\w.>-]+', text) else f'({text})'


def _split_top(text: str, ops: str) -> Optional[Tuple[str, str, str]]:
    """Split `A op B` at the last top-level occurrence of a binary op in `ops`."""
    depth = 0
    best = None
    for k, ch in enumerate(text):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif depth == 0 and ch in ops and k > 0:
            if ch == '-' and text[k + 1:k + 2] == '>':
                continue  # a member arrow, not subtraction
            prev = text[:k].rstrip()
            if prev and prev[-1] not in '(*/+-=<>&|^,':
                best = k
    if best is None:
        return None
    return text[:best].strip(), text[best], text[best + 1:].strip()


def _statements(inner: str) -> List[Tuple[int, int, str]]:
    """(start, end, text) of each simple `... ;` statement at any depth (braces are skipped)."""
    out = []
    start = 0
    depth_paren = 0
    k = 0
    while k < len(inner):
        ch = inner[k]
        if ch in '{}':
            start = k + 1
        elif ch == '(':
            depth_paren += 1
        elif ch == ')':
            depth_paren -= 1
        elif ch == ';' and depth_paren == 0:
            text = inner[start:k].strip()
            if text and not text.startswith(('#', '/')):
                lead = start + (len(inner[start:k]) - len(inner[start:k].lstrip()))
                out.append((lead, k + 1, text))
            start = k + 1
        k += 1
    return out


def _parse_assignment(text: str):
    """(lhs access, op, rhs text) for `L = R`, `L += R`, `L -= R`."""
    m = re.match(r'^(.*?)\s*(\+=|-=|=)\s*(?![=])(.*)$', text, re.S)
    if not m or '==' in text.split('=', 1)[0]:
        return None
    lhs = _access(m.group(1))
    if lhs is None:
        return None
    rhs = m.group(3).strip()
    if m.group(2) == '=' and (rhs.startswith('=') or re.search(r'(?<![=!<>])=(?!=)', rhs)):
        return None
    return lhs, m.group(2), rhs


def _same_vector(a, b, c) -> bool:
    return a[0] == b[0] == c[0] and a[1] == b[1] == c[1] and (a[2], b[2], c[2]) == (a[2], a[2] + 4, a[2] + 8)


def _scalar(text: str) -> str:
    text = _strip(text)
    return _strip(_CAST.sub('', text)) if _CAST.match(text) else text


def _classify_triple(stmts) -> Optional[Tuple[str, dict]]:
    """Recognise one kernel over three parsed statements ordered x, y, z."""
    parsed = [_parse_assignment(s) for s in stmts]
    if any(p is None for p in parsed):
        return None
    lhs = [p[0] for p in parsed]
    if not _same_vector(*lhs):
        return None
    ops = {p[1] for p in parsed}
    rhs = [_scalar(p[2]) for p in parsed]
    dst = lhs[0]
    if ops == {'='}:
        # A op B
        parts = [_split_top(r, '+-') for r in rhs]
        if all(parts) and len({p[1] for p in parts}) == 1:
            left = [_access(p[0]) for p in parts]
            right = [_access(p[2]) for p in parts]
            if all(left) and all(right) and _same_vector(*left) and _same_vector(*right):
                return ('add' if parts[0][1] == '+' else 'sub', dict(a=left[0], b=right[0], dst=dst))
            # A + B * s  /  B * s + A
            for acc_side, prod_side in ((0, 2), (2, 0)):
                if parts[0][1] != '+':
                    continue
                acc = [_access(p[acc_side]) for p in parts]
                prods = [_split_top(_strip(p[prod_side]), '*') for p in parts]
                if all(acc) and all(prods) and _same_vector(*acc):
                    vecs = [_access(q[0]) for q in prods]
                    scal = [q[2] for q in prods]
                    if all(vecs) and _same_vector(*vecs) and len(set(scal)) == 1 and _access(scal[0]) is None:
                        return ('scale_add', dict(acc=acc[0], v=vecs[0], s=scal[0], dst=dst))
                    vecs = [_access(q[2]) for q in prods]
                    scal = [q[0] for q in prods]
                    if all(vecs) and _same_vector(*vecs) and len(set(scal)) == 1 and _access(scal[0]) is None:
                        return ('scale_add', dict(acc=acc[0], v=vecs[0], s=scal[0], dst=dst))
        # A * s
        prods = [_split_top(r, '*') for r in rhs]
        if all(prods):
            for vec_side, s_side in ((0, 2), (2, 0)):
                vecs = [_access(q[vec_side]) for q in prods]
                scal = [q[s_side] for q in prods]
                if all(vecs) and _same_vector(*vecs) and len(set(scal)) == 1 and _access(scal[0]) is None:
                    return ('scale', dict(a=vecs[0], s=scal[0], dst=dst))
        # three scalars
        if all(_access(r) is None or _access(r)[1] != dst[1] for r in rhs):
            return ('set', dict(dst=dst, values=rhs))
    if ops == {'+='}:
        prods = [_split_top(r, '*') for r in rhs]
        if all(prods):
            for vec_side, s_side in ((0, 2), (2, 0)):
                vecs = [_access(q[vec_side]) for q in prods]
                scal = [q[s_side] for q in prods]
                if all(vecs) and _same_vector(*vecs) and len(set(scal)) == 1 and _access(scal[0]) is None:
                    return ('scale_add', dict(acc=dst, v=vecs[0], s=scal[0], dst=dst))
        vecs = [_access(r) for r in rhs]
        if all(vecs) and _same_vector(*vecs):
            return ('add', dict(a=dst, b=vecs[0], dst=dst))
    if ops == {'-='}:
        vecs = [_access(r) for r in rhs]
        if all(vecs) and _same_vector(*vecs):
            return ('sub', dict(a=dst, b=vecs[0], dst=dst))
    return None


def _addr(acc: Access, _unused=None) -> str:
    """The vector's address: its lowest component's lvalue, or the raw byte pointer."""
    kind, base, off = acc
    if kind == 'raw':
        return f'(u8 *){_paren(base)} + {off:#x}' if off else f'(u8 *){_paren(base)}'
    return f'&{acc.text}'


def _emit(kind: str, info: dict) -> str:
    if kind in ('add', 'sub'):
        return f'psvec_{kind}({_addr(info["a"], [])}, {_addr(info["b"], [])}, {_addr(info["dst"], [])});'
    if kind == 'scale':
        return f'psvec_scale({_addr(info["a"], [])}, {info["s"]}, {_addr(info["dst"], [])});'
    if kind == 'scale_add':
        return f'psvec_scale_add({_addr(info["acc"], [])}, {_addr(info["v"], [])}, {info["s"]}, {_addr(info["dst"], [])});'
    if kind == 'set':
        z, y, x = info['values'][2], info['values'][1], info['values'][0]
        return f'psvec_set({_addr(info["dst"], [])}, {z}, {y}, {x});'
    raise ValueError(kind)


def kernel_sites(inner: str, allow_set: bool = True, kinds: Optional[set] = None) -> List[Tuple[int, int, str, str]]:
    """(start, end, kind, replacement) for every recognised statement triple in `inner`.

    Within a run of adjacent component assignments the triples may interleave (retail's
    interpolation kernel writes d.x, d.y, p.x, p.y, d.z, p.z); the run is partitioned by
    destination vector and every complete triple is classified on its own. The run's
    statements are replaced together, the calls ordered by each triple's last statement."""
    stmts = _statements(inner)
    out = []
    k = 0
    while k < len(stmts):
        run = []
        j = k
        while j < len(stmts):
            parsed = _parse_assignment(stmts[j][2])
            if parsed is None or (run and inner[stmts[j - 1][1]:stmts[j][0]].strip()):
                break
            run.append((j, parsed))
            j += 1
        if len(run) < 3:
            k = max(j, k + 1)
            continue
        by_base: Dict[tuple, list] = {}
        for idx, parsed in run:
            lhs = parsed[0]
            by_base.setdefault((lhs[0], lhs[1]), []).append((lhs[2], idx))
        # a base's components form triples of consecutive offsets (x, y, z) greedily from the lowest
        groups: Dict[tuple, list] = {}
        for key, members in by_base.items():
            members.sort()
            while len(members) >= 3:
                (o0, i0), (o1, i1), (o2, i2) = members[:3]
                if (o1, o2) == (o0 + 4, o0 + 8):
                    groups[key + (o0,)] = [i0, i1, i2]
                    members = members[3:]
                else:
                    groups[key + (o0, 'partial')] = [i0]
                    members = members[1:]
            for o, i in members:
                groups[key + (o, 'partial')] = [i]
        calls = []
        for key, members in groups.items():
            if len(members) != 3:
                continue
            texts = [stmts[m][2] for m in members]
            order = sorted(range(3), key=lambda q: _parse_assignment(texts[q])[0][2])
            found = _classify_triple([texts[q] for q in order])
            if not found or (not allow_set and found[0] == 'set') or (kinds is not None and found[0] not in kinds):
                continue
            calls.append((max(members), min(members), found[0], _emit(*found)))
        if calls:
            # only whole runs made of recognised triples are rewritten as a block; a run with
            # leftover statements keeps them in place (their relative order is preserved)
            covered = set()
            for last, first, kind, text in calls:
                covered.update(range(first, last + 1))
            if len(calls) == 1:
                last, first, kind, text = calls[0]
                members = groups[next(key for key, m in groups.items() if len(m) == 3 and max(m) == last)]
                if members == list(range(first, last + 1)):
                    out.append((stmts[first][0], stmts[last][1], kind, text))
                    k = last + 1
                    continue
            lo = min(first for _, first, _, _ in calls); hi = max(last for last, _, _, _ in calls)
            indices = set()
            for key, members in groups.items():
                if len(members) == 3 and min(members) >= lo and max(members) <= hi:
                    indices.update(members)
            if indices == set(range(lo, hi + 1)):
                indent = ''
                m = re.search(r'\n([ \t]*)$', inner[:stmts[lo][0]])
                if m:
                    indent = m.group(1)
                text = ('\n' + indent).join(t for _, _, _, t in sorted(calls))
                out.append((stmts[lo][0], stmts[hi][1], '+'.join(kind for _, _, kind, _ in sorted(calls)), text))
                k = hi + 1
                continue
        k = max(j, k + 1)
    return out


def merge_lerps(text: str) -> str:
    """`psvec_sub(A, B, D); psvec_scale_add(B, D, s, O);` is one retail kernel."""
    pattern = re.compile(r'psvec_sub\(([^;]*?), ([^;]*?), ([^;]*?)\);(\s*)psvec_scale_add\(\2, \3, ([^;]*?), ([^;]*?)\);')
    return pattern.sub(lambda m: f'psvec_sub_scale_add({m.group(1)}, {m.group(2)}, {m.group(5)}, {m.group(3)}, {m.group(6)});', text)


def with_header(body: str) -> str:
    if HEADER in body:
        return body
    m = re.search(r'^#include\s+"types\.h"[^\n]*\n', body, re.M)
    if m:
        return body[:m.end()] + HEADER + '\n' + body[m.end():]
    return HEADER + '\n' + body


def rewrite(body: str, span: Tuple[int, int, int], allow_set: bool = True, sites: Optional[List[int]] = None) -> Optional[str]:
    """Replace the selected kernel sites (all when `sites` is None) inside the function body."""
    inner = body[span[1]:span[2]]
    found = kernel_sites(inner, allow_set)
    if not found:
        return None
    chosen = [f for i, f in enumerate(found) if sites is None or i in sites]
    text = inner
    for start, end, kind, replacement in sorted(chosen, reverse=True):
        text = text[:start] + replacement + text[end:]
    text = merge_lerps(text)
    text = fold_set_arguments(text, body[:span[1]] + text + body[span[2]:])
    return with_header(body[:span[1]] + text + body[span[2]:])


def fold_set_arguments(inner: str, whole: str) -> str:
    """`ax = e1; ay = e2; az = e3; psvec_set(d, az, ay, ax);` -> `psvec_set(d, e3, e2, e1);`

    Retail's register assignment for the merged pair follows argument evaluation order
    (fn_1_2A694 matches only with the loads inside the call), so single-use scalar locals
    assigned right before the call are folded into it and their declarations dropped."""
    pattern = re.compile(r'((?:[ \t]*(?:\w+)\s*=\s*(?:[^;{}]+);\s*){1,3})([ \t]*)psvec_set\(([^;]*?), (\w+), (\w+), (\w+)\);')
    folded_names = []

    def fold(m):
        assigns = re.findall(r'(\w+)\s*=\s*([^;{}]+);', m.group(1))
        values = dict(assigns)
        args = [m.group(4), m.group(5), m.group(6)]
        if not all(a in values for a in args) or len(set(args)) != len(args):
            return m.group(0)
        for a in args:
            if len(re.findall(rf'\b{re.escape(a)}\b', whole)) != 3:  # declaration, assignment, argument
                return m.group(0)
        folded_names.extend(args)
        kept = ''.join(f'{m.group(2)}{n} = {v}; ' for n, v in assigns if n not in args)
        return f'{kept}{m.group(2)}psvec_set({m.group(3)}, {values[args[0]].strip()}, {values[args[1]].strip()}, {values[args[2]].strip()});'
    folded = pattern.sub(fold, inner)
    for a in folded_names:
        if len(re.findall(rf'\b{re.escape(a)}\b', folded)) != 1:
            continue
        before = folded
        folded = re.sub(rf'^[ \t]*(?:f32|float)\s+{re.escape(a)}\s*;[ \t]*\n', '', folded, count=1, flags=re.M)
        if folded == before:
            folded = re.sub(rf'\b((?:f32|float)\s+(?:\w+\s*,\s*)*){re.escape(a)}\s*,\s*', r'\1', folded, count=1)
        if folded == before:
            folded = re.sub(rf',\s*{re.escape(a)}\s*;', ';', folded, count=1)
        if folded == before:
            folded = re.sub(rf'(?:f32|float)\s+{re.escape(a)}\s*;\s*', '', folded, count=1)
    return folded


# --- retail-side recognition for the lifter -------------------------------------------

_MEM = re.compile(r'^(-?0x[0-9a-f]+|-?\d+)\((r\d+)\)$')
_SAVED_FPR = re.compile(r'f(1[4-9]|2\d|3[01])')


def _mem_plus(mem: str, delta: int) -> Optional[str]:
    m = _MEM.match(mem)
    if not m:
        return None
    return f'{int(m.group(1), 0) + delta:#x}({m.group(2)})'.replace('0x-', '-0x')


def _fpr_defs_uses(mn: str, a: List[str]):
    fs = [x for x in a if re.fullmatch(r'f\d+', x)]
    if mn.startswith(('stfs', 'stfd', 'psq_st', 'stfsx', 'psq_stx', 'fcmp')):
        return [], fs
    return fs[:1], fs[1:]


def kernels(ins, labels: Dict[str, int]) -> List[Tuple[int, str, List[str], List[int]]]:
    """Retail kernels in an instruction list: (anchor index, kind, operands, consumed indices).

    The anchor is the kernel's last instruction (every input is computed by then, and the
    instructions the scheduler interleaved keep their place before the call). Operands are
    memory operand texts (`0x10(r29)`) for vectors and register names for scalars; `set`
    carries (dst, z, y, x) registers in the helper's parameter order."""
    starts = set(labels.values())
    blocks = []
    b = 0
    for i, (mn, a) in enumerate(ins):
        if i in starts and i > b:
            blocks.append((b, i)); b = i
        if mn.startswith('b') and mn not in ('bl',) or mn in ('blr', 'bctr', 'bctrl'):
            blocks.append((b, i + 1)); b = i + 1
    if b < len(ins):
        blocks.append((b, len(ins)))
    found = []
    taken = set()
    for lo, hi in blocks:
        # last definition of each FPR at each index, within the block
        defs: Dict[str, int] = {}
        def_at = []
        for i in range(lo, hi):
            d, u = _fpr_defs_uses(*ins[i])
            def_at.append(dict(defs))
            for r in d:
                defs[r] = i
        def producer(reg, at):
            return def_at[at - lo].get(reg)
        def dead_after(reg, at):
            """No read of `reg` after `at` before its next definition (linear scan)."""
            for j in range(at + 1, len(ins)):
                d, u = _fpr_defs_uses(*ins[j])
                if reg in u:
                    return False
                if reg in d:
                    return True
                if ins[j][0] == 'blr':
                    return True
            return True
        def base_stable(mems, first, last):
            bases = {_MEM.match(m).group(2) for m in mems if _MEM.match(m)}
            for j in range(first, last + 1):
                mn, a = ins[j]
                if a and a[0] in bases and not mn.startswith(('st', 'cmp', 'psq_st', 'b')):
                    return False
            return True
        def load_of(reg, at, width=8):
            j = producer(reg, at)
            if j is None or j in taken:
                return None
            mn, a = ins[j]
            if width == 8 and mn == 'psq_l' and len(a) == 4 and a[2] == '0' and a[3] == 'qr0' and _MEM.match(a[1]) and not (_SAVED_FPR.fullmatch(a[0]) and '(r1)' in a[1]):
                return j
            if width == 4 and mn == 'lfs' and _MEM.match(a[1]):
                return j
            return None
        def store_of(reg, after, width=8):
            """The unique store consuming `reg` after `after` in the block."""
            for j in range(after + 1, hi):
                mn, a = ins[j]
                d, u = _fpr_defs_uses(mn, a)
                if reg in u:
                    if width == 8 and mn == 'psq_st' and len(a) == 4 and a[2] == '0' and a[3] == 'qr0' and _MEM.match(a[1]) and a[0] == reg:
                        return j
                    if width == 4 and mn == 'stfs' and _MEM.match(a[1]) and a[0] == reg:
                        return j
                    return None
                if reg in d:
                    return None
            return None
        def zlane(op, mems_in, mem_out, first, last, scalar=None):
            """The scalar z-lane instructions of a kernel: loads at +8, the op, the store at +8."""
            zin = [_mem_plus(m, 8) for m in mems_in]
            zout = _mem_plus(mem_out, 8)
            if None in zin or zout is None:
                return None
            for j in range(lo, hi):
                mn, a = ins[j]
                if mn != op or j in taken:
                    continue
                srcs = a[1:]
                loads = []
                ok = True
                for r, m in zip(srcs if op != 'fmadds' else [srcs[2], srcs[0]], zin):
                    k = load_of(r, j, 4)
                    if k is None or ins[k][1][1] != m:
                        ok = False; break
                    loads.append(k)
                if not ok:
                    continue
                if op in ('fmuls', 'fmadds') and scalar is not None and (srcs[1] != scalar):
                    continue
                st = store_of(a[0], j, 4)
                if st is None or ins[st][1][1] != zout:
                    continue
                if not dead_after(a[0], st):
                    continue
                return loads + [j, st]
            return None
        for i in range(lo, hi):
            if i in taken:
                continue
            mn, a = ins[i]
            if mn in ('ps_sub', 'ps_add'):
                la, lb = load_of(a[1], i), load_of(a[2], i)
                if la is None or lb is None:
                    continue
                st = store_of(a[0], i)
                if st is None and mn == 'ps_sub':
                    # d = a - b; out = d * s + b: the difference feeds a ps_madds0 whose
                    # accumulator is the same loaded b, and both results are stored
                    madd = next((j for j in range(i + 1, hi) if ins[j][0] == 'ps_madds0' and ins[j][1][1] == a[0]
                                 and ins[j][1][3] == a[2] and producer(a[2], j) == lb and producer(a[0], j) == i), None)
                    if madd is None:
                        continue
                    st = next((j for j in range(i + 1, madd) if ins[j][0] == 'psq_st' and ins[j][1][0] == a[0]), None) \
                        or store_of(a[0], madd)
                    sto = store_of(ins[madd][1][0], madd)
                    if st is None or sto is None or not _MEM.match(ins[st][1][1]) or not _MEM.match(ins[sto][1][1]):
                        continue
                    if any(a[0] in _fpr_defs_uses(*ins[j])[1] for j in range(i + 1, hi) if j not in (st, madd)) and not dead_after(a[0], max(st, madd)):
                        continue
                    mems = [ins[la][1][1], ins[lb][1][1]]
                    zin = [_mem_plus(m, 8) for m in mems]
                    zd, zo = _mem_plus(ins[st][1][1], 8), _mem_plus(ins[sto][1][1], 8)
                    z = None
                    for j in range(lo, hi):
                        if ins[j][0] != 'fsubs' or j in taken:
                            continue
                        az, bz = load_of(ins[j][1][1], j, 4), load_of(ins[j][1][2], j, 4)
                        if az is None or bz is None or ins[az][1][1] != zin[0] or ins[bz][1][1] != zin[1]:
                            continue
                        zdiff = ins[j][1][0]
                        fm = next((k for k in range(j + 1, hi) if ins[k][0] == 'fmadds' and ins[k][1][1] == zdiff
                                   and ins[k][1][2] == ins[madd][1][2] and ins[k][1][3] == ins[j][1][2]
                                   and producer(ins[k][1][3], k) == bz and producer(zdiff, k) == j), None)
                        if fm is None:
                            continue
                        std = next((k for k in range(j + 1, hi) if ins[k][0] == 'stfs' and ins[k][1][0] == zdiff and ins[k][1][1] == zd), None)
                        sto_z = store_of(ins[fm][1][0], fm, 4)
                        if std is None or sto_z is None or ins[sto_z][1][1] != zo:
                            continue
                        if not dead_after(zdiff, max(std, fm)) or not dead_after(ins[fm][1][0], sto_z):
                            continue
                        z = [az, bz, j, fm, std, sto_z]
                        break
                    if z is None or not dead_after(ins[madd][1][0], sto):
                        continue
                    z1, z2 = z, []
                    members = sorted({la, lb, i, st, madd, sto, *z1, *z2})
                    if not base_stable(mems + [ins[st][1][1], ins[sto][1][1]], members[0], members[-1]):
                        continue
                    found.append((members[-1], 'sub_scale_add', [mems[0], mems[1], ins[madd][1][2], ins[st][1][1], ins[sto][1][1]], members))
                    taken.update(members)
                    continue
                if st is None:
                    continue
                mems = [ins[la][1][1], ins[lb][1][1]]
                z = zlane('fsubs' if mn == 'ps_sub' else 'fadds', mems, ins[st][1][1], la, st)
                if z is None or not dead_after(a[0], st):
                    continue
                members = sorted({la, lb, i, st, *z})
                if not base_stable(mems + [ins[st][1][1]], members[0], members[-1]):
                    continue
                kind = 'sub' if mn == 'ps_sub' else 'add'
                found.append((members[-1], kind, [mems[0], mems[1], ins[st][1][1]], members))
                taken.update(members)
            elif mn == 'ps_muls0':
                la = load_of(a[1], i)
                if la is None:
                    continue
                st = store_of(a[0], i)
                if st is None:
                    continue
                mems = [ins[la][1][1]]
                z = zlane('fmuls', mems, ins[st][1][1], la, st, scalar=a[2])
                if z is None or not dead_after(a[0], st):
                    continue
                members = sorted({la, i, st, *z})
                if not base_stable(mems + [ins[st][1][1]], members[0], members[-1]):
                    continue
                found.append((members[-1], 'scale', [mems[0], a[2], ins[st][1][1]], members))
                taken.update(members)
            elif mn == 'ps_madds0':
                # ps_madds0 X, V, S, ACC
                lv, lacc = load_of(a[1], i), load_of(a[3], i)
                if lv is None or lacc is None:
                    continue
                st = store_of(a[0], i)
                if st is None:
                    continue
                mems = [ins[lacc][1][1], ins[lv][1][1]]
                z = zlane('fmadds', mems, ins[st][1][1], min(lv, lacc), st, scalar=a[2])
                if z is None or not dead_after(a[0], st):
                    continue
                members = sorted({lv, lacc, i, st, *z})
                if not base_stable(mems + [ins[st][1][1]], members[0], members[-1]):
                    continue
                found.append((members[-1], 'scale_add', [mems[0], mems[1], a[2], ins[st][1][1]], members))
                taken.update(members)
            elif mn == 'ps_merge00' and a[1] != a[2]:
                st = store_of(a[0], i)
                if st is None:
                    continue
                zout = _mem_plus(ins[st][1][1], 8)
                zst = None
                for j in range(lo, hi):
                    if ins[j][0] == 'stfs' and ins[j][1][1] == zout and j not in taken:
                        zst = j; break
                if zst is None or not dead_after(a[0], st):
                    continue
                members = sorted({i, st, zst})
                if not base_stable([ins[st][1][1]], members[0], members[-1]):
                    continue
                found.append((members[-1], 'set', [ins[st][1][1], ins[zst][1][0], a[2], a[1]], members))
                taken.update(members)
    # a sub whose difference feeds a scale_add with the subtrahend as accumulator is one kernel
    merged = []
    by_anchor = {f[0]: f for f in found}
    used = set()
    for f in sorted(found):
        if f[0] in used:
            continue
        if f[1] == 'sub':
            for g in sorted(found):
                if g[1] == 'scale_add' and g[0] not in used and g[2][0] == f[2][1] and g[2][1] == f[2][2]:
                    members = sorted(set(f[3]) | set(g[3]))
                    merged.append((members[-1], 'sub_scale_add', [f[2][0], f[2][1], g[2][2], f[2][2], g[2][3]], members))
                    used.update((f[0], g[0]))
                    break
            if f[0] in used:
                continue
        merged.append(f)
        used.add(f[0])
    return sorted(merged)
