"""Retail-derived repair candidates and diagnostics; no search or compilation."""
from __future__ import annotations

import ast
import itertools
import json
import math
import re
import struct
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
# Pointee signedness matters too: loading through char* versus u8* changes sign
# extension even when the pointer itself occupies the same register.
DECL_RE = re.compile(rf"(?<![\w.>])(?:const\s+)?({TYPE_RE})(?:\s+(?:\*\s*)*|\s*\*+\s*)([A-Za-z_]\w*(?:\s*\[[^\]]*\])?)(?=\s*[;,=()\[])")


def _kinds(res: oracle.CheckResult) -> Dict[str, int]:
    lrows, rrows = getattr(res, "_rows", ([], []))
    return stuck.classify_rows(lrows, rrows)


def _wants_type_flip(counts: Dict[str, int], diffs: List[Tuple[str, str]]) -> bool:
    if any(k.startswith("op:cmp") for k in counts) or counts.get("ins:ext"):
        return True
    text = " ".join(t + " " + o for t, o in diffs)
    return bool(re.search(r"\b(extsh|extsb|clrlwi|cmplw|cmpw|cmplwi|cmpwi|rlwinm)\b", text)) or "@" in text


def _decl_sites(body: str, fn_span: Tuple[int, int]) -> List[Tuple[int, int, str, str]]:
    """Integer locals, fields, globals and called functions' return types affect codegen."""
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


def string_literals(p: Project, module: str, body: str, base: oracle.CheckResult) -> List[Tuple[str, str]]:
    """Correct private string literals using the relocation's retail object.

    Identical instructions do not prove the strings agree. Read both strings
    before proposing an edit, then let the ordinary oracle verify its binding.
    """
    from .poolfix import Elf
    obj = getattr(base, '_object', None)
    if obj is None:
        return []
    elf = Elf(obj.read_bytes())
    own = {s['name']: s for s in elf.symbols()}
    syms = p.symbols(module)
    targets = dict(syms)
    targets.update({f'{s.name}_{s.addr:08X}': s for s in syms.values()})
    pattern = r'([A-Za-z_.$@][\w.$@]*)@(?:ha|l|sda21)\b'
    pairs, references = set(), set()
    for left, right in zip(*getattr(base, '_rows', ([], []))):
        lt, rt = re.search(pattern, stuck._fmt(left)), re.search(pattern, stuck._fmt(right))
        if not lt or not rt:
            continue
        target, source = targets.get(lt[1]), own.get(rt[1])
        if not target or not source:
            continue
        expected = p.string_at(module, target.name)
        if expected is not None and source['shndx'] == 0 and re.fullmatch(r'[A-Za-z_]\w*', source['name']):
            references.add((source['name'], expected))
        if not source['name'].startswith('@') or not 0 < source['shndx'] < len(elf.sections):
            continue
        section = elf.sections[source['shndx']]
        start = section['offset'] + source['value']
        raw = bytes(elf.data[start:start + source['size']])
        if expected is None or not raw.endswith(b'\0') or b'\0' in raw[:-1]:
            continue
        current = raw[:-1].decode('latin1')
        if current != expected:
            pairs.add((current, expected))
    out = []
    for name, expected in sorted(references):
        for token in re.finditer(rf'\b{re.escape(name)}\b', body):
            line = body[body.rfind('\n', 0, token.start()) + 1:token.start()]
            if line.lstrip().startswith('extern '):
                continue
            out.append((f'retail string for {name}', body[:token.start()] + json.dumps(expected) + body[token.end():]))
    for current, expected in sorted(pairs):
        for token in re.finditer(r'"(?:\\.|[^"\\])*"', body):
            try:
                value = ast.literal_eval(token[0])
            except (ValueError, SyntaxError):
                continue
            if value == current:
                out.append((f'retail string {expected!r}', body[:token.start()] + json.dumps(expected) + body[token.end():]))
    # Pooled strings are addressed through one section base, so later strings
    # have no instruction relocation of their own. Recover their boundaries
    # from the emitted symbols and retain retail padding when literals shrink.
    pools = {}
    reloc = re.compile(r'([A-Za-z_.$@][\w.$@]*?)([+-]0x[0-9a-f]+)?@(?:ha|l|sda21)\b')
    for left, right in zip(*getattr(base, '_rows', ([], []))):
        lt, rt = reloc.search(stuck._fmt(left)), reloc.search(stuck._fmt(right))
        target, anchor = targets.get(lt[1]) if lt else None, own.get(rt[1]) if rt else None
        if not target or not anchor or not rt[1].startswith('...data'):
            continue
        delta = (int(lt[2], 0) if lt[2] else 0) - (int(rt[2], 0) if rt[2] else 0) - anchor['value']
        pools.setdefault(anchor['shndx'], set()).add((target.name, delta))
    replacements = {}
    for index, bindings in pools.items():
        if len(bindings) != 1 or not 0 < index < len(elf.sections):
            continue
        name, delta = next(iter(bindings)); target = targets[name]
        section = elf.sections[index]
        layout = p._rel_layout(module)
        regions = layout.values() if module == 'main' else [layout.get(target.section, (0, b''))]
        for private in own.values():
            if private['shndx'] != index or not private['name'].startswith('@') or private['size'] < 2:
                continue
            start = section['offset'] + private['value']
            raw = bytes(elf.data[start:start + private['size']])
            if not raw.endswith(b'\0') or b'\0' in raw[:-1]:
                continue
            address = target.addr + delta + private['value']
            expected = next((data[address - base:address - base + 4096].split(b'\0', 1)[0]
                             for base, data in regions if base <= address < base + len(data)
                             and b'\0' in data[address - base:address - base + 4096]), None)
            if expected is None or any(c >= 128 for c in expected) or raw[:-1] == expected:
                continue
            replacements.setdefault(raw[:-1].decode('latin1'), set()).add(expected.decode('ascii'))
    edits = []
    for token in re.finditer(r'"(?:\\.|[^"\\])*"', body):
        try:
            current = ast.literal_eval(token[0])
        except (ValueError, SyntaxError):
            continue
        choices = replacements.get(current, set())
        if len(choices) == 1:
            edits.append((token.start(), token.end(), current, next(iter(choices))))
    for padded in (False, True):
        text = body
        for start, end, current, expected in reversed(edits):
            if padded:
                expected += '\0' * max(0, len(current) - len(expected))
            literal = json.dumps(expected).replace('\\u0000', '\\000')
            text = text[:start] + literal + text[end:]
        if text != body:
            out.insert(0, ('recover pooled strings' + (' with padding' if padded else ''), text))
    return out


def optimizer_pragmas(body: str, name: str) -> List[Tuple[str, str]]:
    """Recover optimizer state lost when a function is extracted from its TU.

    These passes can change otherwise correct register allocation and scheduling.
    Keep the state local to the function so a later TU merge does not inherit it.
    """
    span = _function_span(body, name)
    if span is None:
        return []
    start = body.rfind('\n', 0, span[0]) + 1
    out = []
    for option in ('peephole', 'opt_propagation', 'opt_common_subs', 'opt_lifetimes', 'opt_dead_assignments'):
        if re.search(rf'^\s*#pragma\s+{option}\s+off\b', body[:span[1]], re.M):
            continue
        text = (body[:start] + f'#pragma {option} off\n' + body[start:span[1]] +
                f'\n#pragma {option} reset\n' + body[span[1]:])
        out.append((f'{option} off', text))
    return out


def float_literals(p: Project, symbol: str, body: str, base: oracle.CheckResult) -> List[Tuple[str, str]]:
    """Recover incorrect floating literals from the retail relocation's bytes.

    Match the emitted literal's exact bits before replacing C tokens. Try each
    occurrence and all equal occurrences together: changing only one can split
    a shared constant load and obscure an otherwise exact repair.
    """
    from .poolfix import Elf
    sym = p.resolve(symbol)
    span = _function_span(body, sym.name)
    if span is None or getattr(base, '_object', None) is None:
        return []
    elf = Elf(base._object.read_bytes())
    own = {s['name']: s for s in elf.symbols()}
    symbols = p.symbols(sym.module)
    targets = dict(symbols)
    targets.update({f'{s.name}_{s.addr:08X}': s for s in symbols.values()})
    reloc = re.compile(r'([A-Za-z_.$@][\w.$@]*?)([+-]0x[0-9a-f]+)?@(?:ha|h|l|sda21)\b')
    floats = set()
    for left, right in zip(*base._rows):
        if (left.get('diff_kind') or 'DIFF_NONE') == 'DIFF_NONE':
            continue
        lt, rt = reloc.search(stuck._fmt(left)), reloc.search(stuck._fmt(right))
        if not lt or not rt:
            continue
        target = targets.get(lt[1])
        offset = int(lt[2], 0) if lt[2] else 0
        old_offset = int(rt[2], 0) if rt[2] else 0
        private = own.get(rt[1])
        width = {'lfs': 4, 'lfd': 8}.get(stuck._mn(left))
        if not target or not private or not width or not private['name'].startswith('@'):
            continue
        raw = p.bytes_at(sym.module, target.name)
        if raw is None or offset < 0 or offset + width > len(raw):
            continue
        if (not 0 < private['shndx'] < len(elf.sections) or old_offset < 0
                or private['size'] < old_offset + width):
            continue
        pos = elf.sections[private['shndx']]['offset'] + private['value'] + old_offset
        current = bytes(elf.data[pos:pos + width])
        expected = raw[offset:offset + width]
        if current != expected:
            floats.add((width, current, expected))
    # A whole-TU pool often has only one lis/addi relocation: its later loads
    # carry ordinary offsets. Follow both objects' bases rather than expecting
    # a relocation on every lfs/lfd. Conflicting alignments are not evidence.
    from .evidence import memory_loads, retail_bytes
    inferred, locations = {}, {}
    left_loads, right_loads = (memory_loads(rows) for rows in base._rows)
    for i, target in left_loads.items():
        private = right_loads.get(i)
        if not private or target['op'] not in ('lfs', 'lfd') or target['op'] != private['op']:
            continue
        anchor = own.get(private['symbol'])
        if not anchor or not private['symbol'].startswith(('@', '...rodata')):
            continue
        if not 0 < anchor['shndx'] < len(elf.sections):
            continue
        section = elf.sections[anchor['shndx']]
        offset, width = anchor['value'] + private['offset'], private['width']
        if offset < 0 or offset + width > section['size']:
            continue
        if any(r['type'] == 4 and r['info'] == anchor['shndx'] and
               any(offset <= struct.unpack_from('>I', elf.data, pos)[0] < offset + width
                   for pos in range(r['offset'], r['offset'] + r['size'], 12)) for r in elf.sections):
            continue
        current = bytes(elf.data[section['offset'] + offset:section['offset'] + offset + width])
        expected = retail_bytes(p, sym.module, target['symbol'], target['offset'], width)
        if expected is not None:
            inferred.setdefault((width, current), set()).add(expected)
            locations.setdefault((width, current), set()).add((target['symbol'], target['offset']))
    # Equal values can still occupy the wrong shared-pool offsets. They need
    # symbolic layout candidates even though no literal value needs correcting.
    floats.update((width, current, next(iter(expected))) for (width, current), expected in inferred.items()
                  if len(expected) == 1)
    from .sdkimport import masked
    code = masked(body)
    out, all_edits, bound_edits = [], {}, {}
    ambiguous = set()
    for declaration in re.finditer(r'\bconst\s+(f32|f64|float|double)\s+(\w+)\s*=\s*(-?\d+\.\d*(?:[eE][+-]?\d+)?[fF]?)\s*;', code[:span[0]]):
        width = 4 if declaration[1] in ('f32', 'float') else 8
        target, private = targets.get(declaration[2]), own.get(declaration[2])
        if not target or not private or private['size'] != width:
            continue
        raw = retail_bytes(p, sym.module, target.name, 0, width)
        if raw is None:
            continue
        value = struct.unpack('>f' if width == 4 else '>d', raw)[0]
        if math.isfinite(value):
            replacement = repr(value) + ('f' if width == 4 else '')
            if replacement != declaration[3]:
                all_edits[declaration.span(3)] = replacement
    for width, current, expected in sorted(floats):
        fmt = '>f' if width == 4 else '>d'
        value = struct.unpack(fmt, expected)[0]
        if not math.isfinite(value):
            continue
        replacement = repr(value) + ('f' if width == 4 else '')
        edits = []
        for token in re.finditer(r'(?<![\w.])-?\d+\.\d*(?:[eE][+-]?\d+)?[fF]?(?![\w.])', code):
            if (width == 4) != token[0].lower().endswith('f'):
                continue
            try:
                actual = struct.pack(fmt, float(token[0].rstrip('fF')))
            except (OverflowError, ValueError):
                continue
            if actual == current:
                start, end = token.span()
                edits.append((start, end))
                if current != expected:
                    out.append((f'retail float {token[0]} -> {replacement}', body[:start] + replacement + body[end:]))
                if (start, end) in all_edits and all_edits[start, end] != replacement:
                    ambiguous.add((start, end))
                all_edits[start, end] = replacement
                refs = locations.get((width, current), set())
                if len(refs) == 1:
                    anchor, offset = next(iter(refs))
                    if offset >= 0 and not re.search(r'\b' + re.escape(anchor) + r'\b', code):
                        bound_edits[start, end] = (anchor, offset, width)
        if len(edits) > 1 and current != expected:
            combined = body
            for start, end in reversed(edits):
                combined = combined[:start] + replacement + combined[end:]
            out.append((f'all references to retail float {replacement}', combined))
    combined = body
    for (start, end), replacement in sorted(all_edits.items(), reverse=True):
        if (start, end) not in ambiguous:
            combined = combined[:start] + replacement + combined[end:]
    if combined != body:
        out.insert(0, ('recover shared-pool literal values', combined))
    # Express the shared layout in owned C declarations. Code bytes, including
    # load offsets, still have to pass the oracle; this does not patch code or
    # mark unequal pools equivalent.
    layouts = {}
    bound = body
    for (start, end), (anchor, offset, width) in sorted(bound_edits.items(), reverse=True):
        if (start, end) in ambiguous:
            continue
        layouts.setdefault(anchor, {})[offset] = width
        bound = bound[:start] + f'{anchor}.unk_{offset:X}' + bound[end:]
    declarations = []
    for anchor, offsets in sorted(layouts.items()):
        cursor = 0
        fields = []
        for offset, width in sorted(offsets.items()):
            if offset < cursor or offset % width:
                fields = []
                break
            if offset > cursor:
                fields.append(f'    u8 pad_{cursor:X}[0x{offset - cursor:X}];')
            fields.append(f'    {"f32" if width == 4 else "f64"} unk_{offset:X};')
            cursor = offset + width
        if not fields:
            declarations = []
            break
        declarations.append('extern const struct ' + sym.name + '_' + anchor + '_pool {\n'
                            + '\n'.join(fields) + '\n} ' + anchor + ';\n')
    if declarations:
        # Place after includes so the repository's fixed-width types are in scope.
        includes = list(re.finditer(r'^\s*#include[^\n]*\n', bound, re.M))
        pos = includes[-1].end() if includes else 0
        bound = bound[:pos] + '\n' + '\n'.join(declarations) + bound[pos:]
        out.insert(0, ('bind recovered shared-pool fields', bound))
        start = re.search(r'\b' + re.escape(sym.name) + r'\s*\([^;{]*\)\s*\{', bound)
        if start:
            pointers = []
            for anchor in sorted(layouts):
                typ = 'struct ' + sym.name + '_' + anchor + '_pool'
                pointer = 'pool_' + anchor
                pointers.append(f'\n    {typ} *{pointer} = ({typ} *)&{anchor};')
                bound = bound.replace(anchor + '.unk_', pointer + '->unk_')
            start = re.search(r'\b' + re.escape(sym.name) + r'\s*\([^;{]*\)\s*\{', bound)
            bound = bound[:start.end()] + ''.join(pointers) + bound[start.end():]
            out.insert(0, ('retain recovered shared-pool bases', bound))
    return out


def stack_aggregates(body: str, diffs: List[Tuple[str, str]]) -> List[Tuple[str, str]]:
    """Remove a draft's fake aggregate prefix when only the stack copy is biased.

    A pointer before a local array can make field accesses agree while moving the
    aggregate copy into the frame header. Recover the field origin and copy origin
    together; retain the union's array member so its size does not shrink.
    """
    deltas = set()
    for target, ours in diffs:
        pattern = r'addi r\d+, r1, (-?0x[0-9a-f]+|-?\d+)$'
        t, o = re.fullmatch(pattern, target), re.fullmatch(pattern, ours)
        if t and o:
            deltas.add(int(t[1], 0) - int(o[1], 0))
    if len(deltas) != 1 or next(iter(deltas)) <= 0:
        return []
    delta = next(iter(deltas))
    out = []
    union = r'typedef\s+union\s*\{[^{}]*struct\s*\{(?P<fields>[^{}]*)\}\s+\w+;[^{}]*\}\s*(?P<type>\w+)\s*;'
    for declaration in re.finditer(union, body):
        fields = declaration['fields']
        first = re.match(r'\s*(u8|s8|u16|s16|u32|s32)\s+(\w+)(?:\[(0[xX][0-9a-fA-F]+|\d+)\])?\s*;', fields)
        if not first:
            continue
        size = int(first[1][1:]) // 8 * (int(first[3], 0) if first[3] else 1)
        if size != delta or re.search(rf'(?:\.|->){re.escape(first[2])}\b', body[declaration.end():]):
            continue
        assignment = (rf'\b(\w+)\s*=\s*\({re.escape(declaration["type"])}\s*\*\)\s*'
                      r'\(\(u8\s*\*\)\s*(\w+)\s*-\s*(0[xX][0-9a-fA-F]+|\d+)\s*\)')
        for source in re.finditer(assignment, body[declaration.end():]):
            if int(source[3], 0) != delta:
                continue
            start, end = declaration.end() + source.start(), declaration.end() + source.end()
            text = body[:start] + f'{source[1]} = ({declaration["type"]} *){source[2]}' + body[end:]
            at = declaration.start('fields')
            text = text[:at] + fields[first.end():] + text[declaration.end('fields'):]
            pointer, array, typ = source[1], source[2], declaration['type']
            # A real aggregate local rematerializes its address at each call.
            # Keeping the draft's pointer would make MWCC save it across calls.
            split = declaration.end() - first.end()
            prefix, text = text[:split], text[split:]
            text, arrays = re.subn(rf'(?m)^[ \t]*(?:u8|u16|u32)\s+{re.escape(array)}\[[^\]\n]+\];\n', '', text)
            text, pointers = re.subn(rf'\b{re.escape(typ)}\s*\*\s*{re.escape(pointer)}\s*;', f'{typ} {pointer};', text)
            text = re.sub(rf'(?m)^[ \t]*{re.escape(pointer)} = \({re.escape(typ)} \*\){re.escape(array)};\n', '', text)
            text = re.sub(rf'\b{re.escape(pointer)}->', f'{pointer}.', text)
            text = re.sub(rf'\*{re.escape(pointer)}\b', pointer, text)
            if arrays == pointers == 1:
                out.append((f'recover aggregate local with {delta}-byte false prefix', prefix + text))
    return out


def store_values(body, name, base):
    """Swap store operands only when retail shows a reciprocal value conflict.

    These are source candidates, never object patches. The compiler oracle also
    checks that evaluation order and every other use of the values are retained.
    """
    conflicts = base.value_flow
    span = _function_span(body, name)
    if not span or len(conflicts) < 2:
        return []
    stores = []
    for row in conflicts:
        t = re.fullmatch(r'(st\w+) ([rf]\d+), (.+)', row['target'])
        o = re.fullmatch(r'(st\w+) ([rf]\d+), (.+)', row['ours'])
        if t and o and t[1] == o[1] and t[3] == o[3]:
            stores.append((t[1], t[2], o[2]))
    if not any(a == d and b == f and c == e and b != c
               for a,b,c in stores for d,e,f in stores):
        return []
    assignments = []
    for m in re.finditer(r'(?m)^[ \t]*(?P<lhs>[^;\n=]+)\s*=\s*(?P<rhs>[A-Za-z_]\w*)\s*;', body[span[0]:span[1]]):
        if any(x in m['lhs'] for x in ('*', '->', '.', '[')):
            assignments.append((span[0]+m.start('rhs'), span[0]+m.end('rhs'), m['rhs']))
    out = []
    for i,(a,b,x) in enumerate(assignments):
        for c,d,y in assignments[i+1:]:
            if x != y:
                out.append((f'retail store-value swap {x}/{y}', body[:a]+y+body[b:c]+x+body[d:]))
    return out


def stack_locals(body, name, diffs):
    """Pack address-taken scalar locals whose separately allocated slots differ.

    An aggregate expresses shared frame storage and natural subword alignment;
    it does not force machine offsets or alter emitted instructions afterward.
    """
    if not any('(r1)' in t+o and t != o for t,o in diffs):
        return []
    span = _function_span(body, name)
    if not span:
        return []
    start = body.index('{', span[0])+1
    pattern = re.compile(r'(?m)^[ \t]*((?:volatile\s+)?(?:u8|s8|u16|s16|u32|s32|f32|f64|int|float|double))\s+(\w+)\s*;[ \t]*\n')
    sites = [m for m in pattern.finditer(body,start,span[1])
             if re.search(r'&\s*'+re.escape(m[2])+r'\b',body[m.end():span[1]])]
    if not 2 <= len(sites) <= 12:
        return []
    # Do not move a declaration out of a nested lexical scope.
    sites = [m for m in sites if body[start:m.start()].count('{') == body[start:m.start()].count('}')]
    if len(sites) < 2:
        return []
    widths={'u8':1,'s8':1,'u16':2,'s16':2,'u32':4,'s32':4,'f32':4,'f64':8,'int':4,'float':4,'double':8}
    orders=[sites,list(reversed(sites)),sorted(sites,key=lambda m:widths[m[1].split()[-1]]),sorted(sites,key=lambda m:-widths[m[1].split()[-1]])]
    orders += [sites[:i]+[sites[i+1],sites[i]]+sites[i+2:] for i in range(len(sites)-1)]
    var='fzgx_frame'
    while re.search(r'\b'+var+r'\b',body):
        var += '_'
    inner=body[start:span[1]-1]
    for m in reversed(sites):
        inner=inner[:m.start()-start]+inner[m.end()-start:]
    names={m[2] for m in sites}
    inner=re.sub(r'\b[A-Za-z_]\w*\b',lambda m:var+'.'+m[0] if m[0] in names else m[0],inner)
    out=[]
    for order in orders:
        fields=' '.join(m[1]+' '+m[2]+';' for m in order)
        text=body[:start]+'\n    struct { '+fields+' } '+var+';\n'+inner+body[span[1]-1:]
        out.append(('pack stack scalars '+','.join(m[2] for m in order),text))
    # Retail can reuse one address-taken slot across distinct scalar lifetimes.
    # Packing alone cannot express that overlap. Propose equal-width reuse
    # only when the object diff shows two compiler slots mapping to one retail
    # slot; the stock compiler and full oracle decide source realizability.
    slots = {}
    for target, ours in diffs:
        t = re.fullmatch(r'(\w+) [rf]\d+, (0x[0-9a-f]+)\(r1\)', target)
        o = re.fullmatch(r'(\w+) [rf]\d+, (0x[0-9a-f]+)\(r1\)', ours)
        if t and o and t[1] == o[1]:
            slots.setdefault(int(t[2], 0), set()).add(int(o[2], 0))
    if len(sites) <= 7 and any(len(v) > 1 for v in slots.values()):
        merged = []
        def qualified_reuse(keep, drop, lo, hi, remove=False):
            if not keep[1].startswith('volatile ') or drop[1].startswith('volatile '):
                return
            ty = keep[1].removeprefix('volatile ')
            edits = [(keep.start(1), keep.end(1), ty)]
            for token in re.finditer(r'(?<![.\w])(?<!->)'+re.escape(keep[2])+r'\b', body[keep.end():span[1]]):
                a = keep.end()+token.start()
                edits.append((a,a+len(keep[2]),'(*(volatile '+ty+' *)&'+keep[2]+') /* Keep this staged access volatile. */'))
            for token in re.finditer(r'(?<![.\w])(?<!->)'+re.escape(drop[2])+r'\b', body[lo:hi]):
                a = lo+token.start()
                edits.append((a,a+len(drop[2]),keep[2]))
            if remove:
                edits.append((drop.start(),drop.end(),''))
            text = body
            for a,b,value in sorted(edits,reverse=True):
                text = text[:a]+value+text[b:]
            merged.append(('pack stack qualified lifetime '+drop[2]+' as '+keep[2]+f' at {lo}', text))
        for keep, drop in itertools.permutations(sites, 2):
            if widths[keep[1].split()[-1]] != widths[drop[1].split()[-1]]:
                continue
            text = body[:drop.start()] + body[drop.end():]
            fn = _function_span(text, name)
            inner_text = text[fn[0]:fn[1]]
            if keep[1] != drop[1]:
                inner_text = re.sub(r'&\s*'+re.escape(drop[2])+r'\b',
                                    '('+drop[1]+' *)&'+keep[2], inner_text)
            inner_text = re.sub(r'(?<![.\w])(?<!->)'+re.escape(drop[2])+r'\b', keep[2], inner_text)
            merged.append(('pack stack reuse '+drop[2]+' as '+keep[2], text[:fn[0]]+inner_text+text[fn[1]:]))
            qualified_reuse(keep,drop,drop.end(),span[1],True)
            # A temporary may occupy different retail slots in distinct live
            # ranges. Retain its declaration and redirect one assignment/use
            # interval instead of forcing every occurrence into the same slot.
            assigns = list(re.finditer(r'(?m)^\s*'+re.escape(drop[2])+r'\s*=(?!=)', body[drop.end():span[1]]))
            for j, assignment in enumerate(assigns):
                lo = drop.end() + assignment.start()
                hi = drop.end() + assigns[j+1].start() if j+1 < len(assigns) else span[1]
                segment = body[lo:hi]
                if not re.search(r'&\s*'+re.escape(drop[2])+r'\b', segment):
                    continue
                if keep[1] != drop[1]:
                    segment = re.sub(r'&\s*'+re.escape(drop[2])+r'\b', '('+drop[1]+' *)&'+keep[2], segment)
                segment = re.sub(r'(?<![.\w])(?<!->)'+re.escape(drop[2])+r'\b', keep[2], segment)
                merged.append(('pack stack lifetime '+drop[2]+' as '+keep[2]+f' at {lo}', body[:lo]+segment+body[hi:]))
                qualified_reuse(keep,drop,lo,hi)
        out = merged + out
    return list(dict.fromkeys(out))


def stack_field_origins(body, diffs):
    """Move false leading padding to the tail, retaining the aggregate extent."""
    deltas=set()
    for t,o in diffs:
        tm=re.fullmatch(r'(\w+ [rf]\d+, )(-?0x[0-9a-f]+)\(r1\)',t)
        om=re.fullmatch(r'(\w+ [rf]\d+, )(-?0x[0-9a-f]+)\(r1\)',o)
        if tm and om and tm[1]==om[1] and tm[2]!=om[2]:
            deltas.add(int(tm[2],0)-int(om[2],0))
    out=[]
    for m in re.finditer(r'\bstruct\s+(\w+)\s*\{(?P<fields>[^{}]+)\}',body):
        prefix=re.match(r'\s*u8\s+(\w+)\[(0x[0-9a-fA-F]+|\d+)\];',m['fields'])
        if not prefix or re.search(r'(?:\.|->)\s*'+re.escape(prefix[1])+r'\b',body):
            continue
        size=int(prefix[2],0)
        for delta in sorted(deltas):
            if not -size<=delta<0:
                continue
            remaining=size+delta
            first=f'\n    u8 {prefix[1]}[{remaining}];' if remaining else ''
            fields=first+m['fields'][prefix.end():]+f'\n    u8 fzgx_tail_padding[{-delta}];\n'
            out.append((f'recover aggregate field origin {m[1]} {delta}',body[:m.start('fields')]+fields+body[m.end('fields'):]))
    return out


def member_layouts(body, diffs):
    """Recover internal gaps from emitted member offsets, not identifier spelling."""
    pairs = set()
    for target, ours in diffs:
        t = re.fullmatch(r'(\w+) [rf]\d+, (-?0x[0-9a-f]+)\(r\d+\)', target)
        o = re.fullmatch(r'(\w+) [rf]\d+, (-?0x[0-9a-f]+)\(r\d+\)', ours)
        if t and o and t[1] == o[1] and t[2] != o[2] and '(r1)' not in target + ours:
            pairs.add((int(o[2], 0), int(t[2], 0)))
        t = re.fullmatch(r'addi r\d+, r(?!1\b)\d+, (0x[0-9a-f]+)', target)
        o = re.fullmatch(r'addi r\d+, r(?!1\b)\d+, (0x[0-9a-f]+)', ours)
        if t and o and t[1] != o[1]:
            pairs.add((int(o[1], 0), int(t[1], 0)))
    if not pairs:
        return []
    sizes = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'short': 2,
             'u32': 4, 's32': 4, 'int': 4, 'f32': 4, 'float': 4, 'f64': 8, 'double': 8}
    from .sdkimport import masked
    code = masked(body)
    out = []
    for sm in re.finditer(r'\bstruct\s*\w*\s*\{([^{}]*)\}', code):
        fields, cursor, valid = [], 0, True
        for part in re.finditer(r'([^;]+);', sm[1]):
            field = re.fullmatch(r'\s*(?:const\s+|volatile\s+)*(\w+)\s*(\*)?\s+(\w+)\s*(?:\[\s*(0x[\da-fA-F]+|\d+)\s*\])?\s*;', part[0])
            # Also accept the common `u8 *cur` declarator spelling.
            if not field:
                field = re.fullmatch(r'\s*(?:const\s+|volatile\s+)*(\w+)\s+(\*)?\s*(\w+)\s*(?:\[\s*(0x[\da-fA-F]+|\d+)\s*\])?\s*;', part[0])
            if not field or (not field[2] and field[1] not in sizes):
                valid = False
                break
            width = 4 if field[2] else sizes[field[1]]
            cursor = (cursor + width - 1) // width * width
            start = sm.start(1) + part.start()
            fields.append((field, cursor, start, sm.start(1) + part.end()))
            cursor += width * (int(field[4], 0) if field[4] else 1)
        if not valid:
            continue
        edits = {}
        for i, (field, offset, start, end) in enumerate(fields):
            if not re.search(r'(?:\.|->)\s*' + re.escape(field[3]) + r'\b', code):
                continue
            for old, new in sorted(pairs):
                if old != offset or new < 0:
                    continue
                delta = new - old
                if i:
                    pad, _, ps, pe = fields[i - 1]
                    if (pad[1] == 'u8' and pad[4] and not pad[2]
                            and not re.search(r'(?:\.|->)\s*' + re.escape(pad[3]) + r'\b', code)):
                        length = int(pad[4], 0) + delta
                        if length >= 0:
                            a, b = ps + pad.start(4), ps + pad.end(4)
                            edit = (a, b, f'0x{length:X}') if length else (ps, pe, '')
                            edits.setdefault(edit[:2], set()).add(edit[2])
                            out.append((f'recover member gap {field[3]} {old:#x}->{new:#x}',
                                        body[:edit[0]] + edit[2] + body[edit[1]:]))
                if delta > 0:
                    text = f'\n    u8 fzgx_pad_before_{field[3]}[0x{delta:X}];'
                    out.append((f'recover member gap before {field[3]} {old:#x}->{new:#x}',
                                body[:start] + text + body[start:]))
        combined = body
        for (a, b), choices in sorted(edits.items(), reverse=True):
            if len(choices) == 1:
                combined = combined[:a] + next(iter(choices)) + combined[b:]
        if combined != body:
            out.insert(0, ('recover member gaps together', combined))
    return list(dict.fromkeys(out))


def interior_references(p, module, body, diffs):
    """Explicit symbolic subobject/entry declarations, proven by the pool oracle."""
    out=[]
    for target,ours in diffs:
        t=re.fullmatch(r'(\w+ .+?, )([A-Za-z_]\w*)\+(0x[0-9a-f]+)@(\w+)',target)
        o=re.fullmatch(r'(\w+ .+?, )([A-Za-z_]\w*)@(\w+)',ours)
        if t and o and t[1]==o[1] and t[4]==o[3]:
            owner=p.find_symbol(t[2],module) or p.resolve(t[2])
            delta=int(t[3],0)
            if owner is None or not 0<delta<owner.size:
                continue
            declaration=re.search(r'(?m)^extern\s+(u32|s32|u16|s16|u8|s8|f32|f64)\s+'+re.escape(o[2])+r'\s*;',body)
            if not declaration or delta+int(declaration[1][1:])//8>owner.size:
                continue
            alias=f'{owner.name}__fzgx_offset_{delta:X}'
            text=re.sub(r'\b'+re.escape(o[2])+r'\b',alias,body)
            out.append((f'interior data {o[2]} -> {owner.name}+{delta}',text))
        t=re.fullmatch(r'bl ([A-Za-z_]\w*)\+(0x[0-9a-f]+)',target)
        if t and ours=='bl '+t[1]:
            owner=p.find_symbol(t[1],module) or p.resolve(t[1])
            delta=int(t[2],0)
            if not owner or not 0<delta<owner.size or delta%4:
                continue
            decl=re.search(r'(?m)^extern\s+([\w *]+?)\s+'+re.escape(t[1])+r'\s*\(([^;{}]*)\);',body)
            alias=f'{owner.name}__fzgx_offset_{delta:X}'
            # An implicit declaration retains C's default argument promotions.
            prototype=f'extern {decl[1] if decl else "int"} {alias}({decl[2] if decl else ""});\n'
            uses=list(re.finditer(r'\b'+re.escape(t[1])+r'(?=\s*\()',body[decl.end() if decl else 0:]))
            start=decl.end() if decl else 0
            for use in uses:
                a,b=start+use.start(),start+use.end()
                text=body[:a]+alias+body[b:]
                pos=decl.end() if decl else (max((m.end() for m in re.finditer(r'^#include[^\n]*\n',body,re.M)),default=0))
                out.append((f'interior call {owner.name}+{delta}',text[:pos]+'\n'+prototype+text[pos:]))
    return list(dict.fromkeys(out))


def hardware_lvalues(body):
    """Use the shared hardware map for fixed-address scratch lvalues."""
    number=r'0[xX][0-9a-fA-F]+'
    pattern=re.compile(r'\(\s*((?:volatile\s+)?(?:f32|f64|u8|u16|u32|s8|s16|s32))\s*\*\s*\)\s*('+number+r'|\(\s*'+number+r'\s*\+\s*'+number+r'\s*\))')
    from .project import ROOT
    header=ROOT/'include/dolphin/hw_regs.h'
    bases=sorted(((int(addr,16),name) for name,addr in re.findall(
        r'^#define (\w+_BASE) (0x[0-9A-Fa-f]+)[uU]?$',header.read_text(),re.M)),reverse=True)
    edits=[]
    hardware_variables=set()
    for m in pattern.finditer(body):
        address=sum(int(n,16) for n in re.findall(number,m[2]))
        owner=next(((addr,name) for addr,name in bases if 0<=address-addr<0x1000),None)
        if owner:
            addr,name=owner
            edits.append((m.start(2),m.end(2),f'({name} + 0x{address-addr:X})'))
    for m in re.finditer(r'\b(\w+)\s*=\s*('+number+r')[uUlL]*(?=\s*;)',body):
        address=int(m[2],16)
        owner=next((name for addr,name in bases if addr==address),None)
        if owner and re.search(r'\([^();]+\*\)\s*'+re.escape(m[1])+r'\b',body[m.end():]):
            edits.append((m.start(2),m.end(2),owner))
            hardware_variables.add(m[1])
    edits=sorted(set(edits))
    if not edits:
        return []
    text=body
    for a,b,replacement in reversed(edits):
        text=text[:a]+replacement+text[b:]
    names=hardware_variables | {name for _,name in bases}
    fifo_macros = {m[1] for m in re.finditer(r'^#define\s+(\w+)\([^\n]+GX_FIFO_BASE[^\n]*', text, re.M)}
    fifo_inputs = {m[1] for macro in fifo_macros for m in re.finditer(r'\b'+re.escape(macro)+r'\((\w+)\)', text)}
    text = re.sub(r'(?m)^extern volatile const (f32|f64) (\w+);$',
                  lambda m: m[0] + (' /* Reload before each ordered FIFO write. */' if m[2] in fifo_inputs else ''), text)
    text='\n'.join(line+' /* Hardware access must remain ordered. */'
                   if 'volatile' in line and not any(c in line for c in ('//','/*'))
                   and any(re.search(r'\b'+re.escape(name)+r'\b',line) for name in names)
                   else line for line in text.split('\n'))
    if '#include "dolphin/hw_regs.h"' not in text:
        text='#include "dolphin/hw_regs.h"\n'+text
    return [('bind hardware lvalues',text)]



def candidates(p: Project, symbol: str, body: str, base: oracle.CheckResult):
    sym = p.resolve(symbol)
    counts = _kinds(base)
    lrows, rrows = base._rows
    diffs = [(stuck._fmt(a), stuck._fmt(b)) for a, b in zip(lrows, rrows) if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE"]
    span = _function_span(body, sym.name)
    candidates: List[Tuple[str, str]] = store_values(body, sym.name, base)
    candidates += stack_locals(body, sym.name, [(stuck._fmt(a), stuck._fmt(b)) for a,b in zip(lrows,rrows)])
    candidates += stack_field_origins(body, diffs)
    candidates += member_layouts(body, diffs)
    candidates += interior_references(p, sym.module, body, diffs)
    candidates += hardware_lvalues(body)
    candidates += string_literals(p, sym.module, body, base)
    # These candidates are derived from retail bytes. Large functions can
    # exhaust the candidate budget on type permutations before reaching them.
    literals = float_literals(p, symbol, body, base)
    candidates += literals
    candidates += optimizer_pragmas(body, sym.name)
    if span and _wants_type_flip(counts, diffs):
        sites = _decl_sites(body, span)
        for s, e, typ, name in sites:
            alts = [FLIP[typ]] if typ in FLIP else []
            if counts.get("ins:ext") or "@" in " ".join(t + o for t, o in diffs):
                alts += WIDEN.get(typ, [])
            for alt in alts:
                candidates.append((f"{name}:{typ}->{alt}", body[:s] + alt + body[e:]))
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
    candidates += literals[3:]
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
    candidates += stack_aggregates(body, diffs)
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
    return candidates

def first_divergence(p: Project, sym, target, obj) -> Optional[Tuple[int, Optional[int], int]]:
    """(row index of the first differing row, our source line at that row, row count)."""
    rows = oracle.function_rows(p, sym.name, target, obj)
    if not rows:
        return None
    l, r, _ = rows
    for k, (a, b) in enumerate(zip(l, r)):
        if (a.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE" or (b.get("diff_kind") or "DIFF_NONE") != "DIFF_NONE":
            line = None
            for j in range(k, -1, -1):
                ln = (r[j].get("instruction") or {}).get("line_number")
                if ln:
                    line = ln; break
            return k, line, len(l)
    if len(l) != len(r):
        return min(len(l), len(r)), None, len(l)
    return None
