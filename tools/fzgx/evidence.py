"""Retail data evidence shared by the lifter and matcher context."""
from __future__ import annotations

import re
import struct
from collections import deque

RELOC = re.compile(r'([\w.$@]+?)([+-](?:0x[\da-fA-F]+|\d+))?@(ha|h|l|sda21)\b')
MEMORY = re.compile(r'(.+)\((r\d+)\)$')
WIDTH = {'lfs': 4, 'lfd': 8, 'lwz': 4, 'lhz': 2, 'lha': 2, 'lbz': 1}


def memory_loads(rows, tables=None, addresses=False, flow=None):
    """Follow symbolic bases through the CFG, intersecting facts at every join.

    Results use aligned-row indices so target and candidate accesses can be
    compared without confusing object addresses with the diff's row offsets.
    """
    tables = tables or {}
    # Objdiff omits zero-valued protobuf fields, including address zero.
    instructions = {i: {'address':0, **row['instruction']} for i, row in enumerate(rows)
                    if row.get('instruction', {}).get('formatted')}
    indices = list(instructions)
    if not indices:
        return {}
    locations = {int(ins['address']): i for i, ins in instructions.items()}
    following = dict(zip(indices, indices[1:]))
    incoming = {indices[0]: {}}
    pending = deque([indices[0]])
    loads = {}
    while pending:
        i = pending.popleft()
        ins = instructions[i]
        parts = ins['formatted'].split(None, 1)
        op = parts[0].rstrip('+-')
        args = [a.strip() for a in parts[1].split(',')] if len(parts) > 1 else []
        before = incoming[i]
        after = dict(before)
        rel = RELOC.search(ins['formatted'])
        symbolic = (rel[1], int(rel[2], 0) if rel[2] else 0, rel[3] in ('ha', 'h')) if rel else None
        value = None
        if op == 'lis' and symbolic:
            value = symbolic
        elif op == 'mr':
            value = before.get(args[1])
        elif op == 'addi':
            base = before.get(args[1])
            if symbolic and base and base[0] == symbolic[0] and base[1] == symbolic[1] and base[2]:
                value = (symbolic[0], symbolic[1], False)
            elif base and not base[2] and re.fullmatch(r'-?(?:0x[\da-f]+|\d+)', args[2]):
                value = (base[0], base[1] + int(args[2], 0), False)
        elif op == 'li' and symbolic and rel[3] == 'sda21':
            value = symbolic
        elif op == 'lwzx':
            for register in args[1:]:
                base = before.get(register)
                if base and not base[2] and base[0] in tables:
                    value = (base[0], base[1], 'table')
        elif op == 'mtctr':
            after.pop('ctr', None)
            if args and args[0] in before:
                after['ctr'] = before[args[0]]
        loads.pop(i, None)
        if addresses and value and value[2] is False and op in ('addi','li'):
            loads[i] = dict(symbol=value[0],offset=value[1],width=0,op=op,
                            address=int(ins['address']))
        if op in WIDTH and len(args) == 2:
            mem = MEMORY.fullmatch(args[1])
            base = before.get(mem[2]) if mem else None
            location = None
            if symbolic and (rel[3] == 'sda21' or (base and base[:2] == symbolic[:2] and base[2])):
                location = symbolic[:2]
            elif mem and base and not base[2] and re.fullmatch(r'-?(?:0x[\da-f]+|\d+)', mem[1]):
                location = (base[0], base[1] + int(mem[1], 0))
            if location:
                loads[i] = dict(symbol=location[0], offset=location[1], width=WIDTH[op], op=op,
                                address=int(ins['address']))
        if args and re.fullmatch(r'r\d+', args[0]) and not op.startswith(('st', 'cmp', 'mt', 'b')):
            after.pop(args[0], None)
            if value:
                after[args[0]] = value
            if op == 'lmw':
                for reg in range(int(args[0][1:]), 32):
                    after.pop(f'r{reg}', None)
        if op.endswith('u') and args and (mem := MEMORY.fullmatch(args[-1])):
            after.pop(mem[2], None)
        call = op in ('bl', 'bctrl', 'blrl')
        if call and not (args and args[0].startswith(('_savegpr_', '_restgpr_', '_savefpr_', '_restfpr_'))):
            after.pop('ctr', None)
            for reg in (0, *range(3, 13)):
                after.pop(f'r{reg}', None)
        successors = []
        if i in following and op not in ('b', 'bctr', 'blr'):
            successors.append(following[i])
        dest = ins.get('branch_dest')
        if dest is not None and not call and int(dest) in locations:
            successors.append(locations[int(dest)])
        if op == 'bctr':
            table = before.get('ctr')
            if table and table[2] == 'table' and table[0] in tables:
                successors = [locations[a] for a in tables[table[0]] if a in locations]
            else:
                # Unknown successors must not inherit a guessed base from one
                # arm. Relocated tables, however, preserve dominating pool bases.
                successors = indices
                after = {}
        if flow is not None:
            flow[i] = (successors, op == 'bctr' and successors == indices)
        for nxt in successors:
            old = incoming.get(nxt)
            merged = after if old is None else {k: v for k, v in old.items() if after.get(k) == v}
            if old != merged:
                incoming[nxt] = dict(merged)
                pending.append(nxt)
    return loads


def object_jump_tables(path, name, project=None, module=None):
    """Internal switch edges from ELF relocations; no guessed branch targets."""
    from .poolfix import Elf
    elf = Elf(path.read_bytes())
    symbols = elf.symbols()
    fn = next((s for s in symbols if s['name'] == name), None)
    if not fn:
        return {}
    relocations = {}
    for section in elf.sections:
        if section['type'] != 4:
            continue
        for pos in range(section['offset'], section['offset']+section['size'], 12):
            offset, info, addend = struct.unpack_from('>IIi', elf.data, pos)
            target = symbols[info >> 8]
            address = target['value']+addend
            if info & 255 == 1 and target['shndx'] == fn['shndx'] and fn['value'] <= address < fn['value']+fn['size']:
                relocations[section['info'],offset] = address
    tables = {}
    if project is not None:
        function = project.function((module+':'+name) if module else name)
        if function:
            tables.update({table: [a-function.symbol.addr+fn['value'] for a in targets]
                           for table,targets in jump_tables(project, function).items()})
    for symbol in symbols:
        if symbol['shndx'] == fn['shndx'] or symbol['size'] < 8 or symbol['size'] % 4:
            continue
        entries = [relocations.get((symbol['shndx'],offset))
                   for offset in range(symbol['value'],symbol['value']+symbol['size'],4)]
        if entries and all(a is not None and a % 4 == 0 for a in entries):
            tables[symbol['name']] = entries
    return tables


def assembly_rows(fn):
    rows = []
    for line in fn.asm:
        match = re.match(r'^([\da-fA-F]+):\s*(.*)', line)
        if not match:
            continue
        ins = dict(address=int(match[1], 16), formatted=match[2])
        branch = re.match(r'b\w*[+-]?\s+(?:cr\d+, )?(?:\.L_|0x)([\da-fA-F]+)$', match[2])
        if branch:
            ins['branch_dest'] = int(branch[1], 16)
        rows.append(dict(instruction=ins))
    return rows


def conversion_values(project, module, rows, tables=None):
    """Typed int-to-FP values at observable uses, including the actual bias bytes.

    Definition identities are finite, so loops converge without expanding
    expressions. Conflicting paths lose the fact instead of choosing one arm.
    """
    from .lift import integer_float_pairs
    present = [(i, {'address':0, **row['instruction']}) for i, row in enumerate(rows)
               if row.get('instruction', {}).get('formatted')]
    addresses = {int(ins['address']): n for n, (_, ins) in enumerate(present) if ins.get('address') is not None}
    ins, labels = [], {}
    for _, row in present:
        parts = row['formatted'].split(None, 1)
        args = [a.strip() for a in parts[1].split(',')] if len(parts) > 1 else []
        if row.get('branch_dest') is not None and int(row['branch_dest']) in addresses:
            labels[args[-1]] = addresses[int(row['branch_dest'])]
        ins.append((parts[0].rstrip('+-'), args))
    if not ins:
        return {}
    flow = {}
    loads = memory_loads(rows, tables, flow=flow)
    positions = {i:n for n,(i,_) in enumerate(present)}
    edges = [[positions[j] for j in flow.get(i, ([],False))[0] if j in positions] for i,_ in present]
    pairs = integer_float_pairs(ins, labels, edges)
    stores = {n for pair in pairs.values() for n in pair}
    incoming = {0: {f'r{r}': ('entry', f'r{r}') for r in range(3, 11)}}
    queue = deque([0])
    result, produced, comparisons, estimates = {}, {}, {}, {}
    while queue:
        n = queue.popleft(); before = incoming[n]; after = dict(before)
        op, args = ins[n]; row_index = present[n][0]
        value = None
        produced.pop(row_index, None)
        if args:
            if op in ('fcmpu', 'fcmpo'):
                comparisons[row_index] = tuple(before.get(reg) for reg in args[-2:])
            if op == 'frsqrte':
                estimates[row_index] = before.get(args[1])
            if op in ('mr', 'fmr'):
                value = before.get(args[1])
            elif op == 'xoris' and args[2] in ('0x8000', '32768'):
                value = ('signed-word', ('read', n, args[1]))
            elif n in pairs:
                word = before.get('store:' + str(pairs[n][1]))
                if word:
                    value = ('encoded', word)
            elif row_index in loads and op in ('lfs', 'lfd'):
                load = loads[row_index]
                raw = retail_bytes(project, module, load['symbol'], load['offset'], load['width'])
                if raw:
                    value = ('literal', raw.hex())
            elif op in ('fsub', 'fsubs'):
                encoded, bias = before.get(args[1]), before.get(args[2])
                if encoded and encoded[0] == 'encoded' and bias and bias[0] == 'literal':
                    word = encoded[1]; signed = word[0] == 'signed-word'
                    expected = '4330000080000000' if signed else '4330000000000000'
                    if bias[1] == expected:
                        value = ('conversion', 'f32' if op == 'fsubs' else 'f64',
                                 's32' if signed else 'u32', word[1] if signed else word)
                        produced[row_index] = value
            elif op == 'frsp':
                previous = before.get(args[1])
                if previous and previous[0] == 'conversion':
                    value = ('conversion', 'f32', *previous[2:])
                elif previous and previous[0] == 'arithmetic':
                    value = ('rounded', 'f32', previous)
            if value is None and op in ('fadd', 'fsub'):
                left, right = before.get(args[1]), before.get(args[2])
                if left and right and {left[0], right[0]} == {'conversion', 'literal'}:
                    value = ('arithmetic', op, left, right)
            if n in stores:
                after['store:' + str(n)] = before.get(args[0], ('definition', n, args[0]))
            if op in ('bl', 'bctrl', 'blrl'):
                result[row_index] = {r: v for r, v in before.items() if re.fullmatch(r'f[1-8]', r) and v[0] in ('conversion', 'arithmetic', 'rounded')}
                if not (args and re.fullmatch(r'_(save|rest)(gpr|fpr)_\d+', args[0])):
                    for reg in list(after):
                        if reg.startswith('store:') or re.fullmatch(r'r(?:0|[3-9]|1[0-2])|f(?:\d|1[0-3])', reg):
                            after.pop(reg)
                    after['r3'] = ('definition', n, 'r3')
            elif not op.startswith(('st', 'cmp', 'fcmp', 'b', 'mt')) and re.fullmatch(r'[rf]\d+', args[0]):
                after.pop(args[0], None)
                if value is not None:
                    after[args[0]] = value
                elif args[0].startswith('r'):
                    after[args[0]] = ('definition', n, args[0])
        if flow.get(row_index, ([],False))[1]:
            after = {}
        for nxt in edges[n]:
            old = incoming.get(nxt)
            merged = after if old is None else {k: v for k, v in old.items() if after.get(k) == v}
            if old != merged:
                incoming[nxt] = dict(merged); queue.append(nxt)
    return dict(calls=result, conversions=produced, comparisons=comparisons, estimates=estimates,
                pairs={present[n][0]:tuple(present[store][0] for store in pair) for n,pair in pairs.items()})


def retail_bytes(project, module, name, offset, width):
    sym = project.find_symbol(name, module)
    if sym is None:
        local = re.fullmatch(r'(.+)_([\da-fA-F]{8})', name)
        sym = project.find_symbol(local[1], module) if local else None
        if sym and sym.addr != int(local[2], 16):
            sym = None
    if not sym or sym.kind != 'object' or sym.section in ('.bss', '.sbss', '.sbss2'):
        return None
    address = sym.addr + offset
    layout = project._rel_layout(sym.module)
    regions = layout.values() if sym.module == 'main' else [layout.get(sym.section, (0, b''))]
    for base, data in regions:
        if base <= address and address + width <= base + len(data):
            return data[address - base:address - base + width]
    return None


def jump_tables(project, fn):
    """Decode relocated entries, rejecting tables that leave this function."""
    if not any(re.search(r'\bbctr\b', line) for line in fn.asm):
        return {}
    module = fn.symbol.module
    cache = project.__dict__.setdefault('_retail_data_objects', {})
    if module not in cache:
        objects = {}
        for path in project._asm_files(module):
            for match in re.finditer(r'(?ms)^\.obj\s+(\S+),[^\n]*\n(.*?)^\.endobj', path.read_text()):
                objects[match[1]] = match[2]
        cache[module] = objects
    tables = {}
    for name in fn.refs:
        sym = project.find_symbol(name, module)
        values = re.findall(r'^\s*\.4byte\s+([^\n]+)', cache[module].get(name, ''), re.M)
        if not sym or not values or len(values) * 4 != sym.size:
            continue
        targets = []
        for value in values:
            match = re.fullmatch(r'([\w.$]+)(?:\+(0x[0-9a-fA-F]+|\d+))?', value.strip())
            target = project.find_symbol(match[1], module) if match else None
            if not target or target.module != module or target.section != fn.symbol.section:
                break
            address = target.addr + (int(match[2], 0) if match[2] else 0)
            if not fn.symbol.addr <= address < fn.symbol.end or address % 4:
                break
            targets.append(address)
        else:
            tables[name] = targets
    return tables


def data_context(project, fn, full=False):
    lines = []
    for name, targets in jump_tables(project, fn).items():
        lines.append(f'{name}: {len(targets)} relocated entries; indices are table indices, before any switch bias.')
        for index, address in enumerate(targets):
            lines.append(f'  [{index}] -> {fn.symbol.name}+0x{address - fn.symbol.addr:X} (assembly {address:08X})')
    accesses = {}
    loads = memory_loads(assembly_rows(fn), jump_tables(project, fn))
    for load in loads.values():
        if load['op'] not in ('lfs', 'lfd'):
            continue
        key = (load['symbol'], load['offset'], load['width'])
        accesses.setdefault(key, []).append(load['address'])
    if accesses:
        lines.append('Retail floating loads (symbol-relative byte offsets, exact big-endian bytes):')
    for (name, offset, width), sites in sorted(accesses.items()):
        raw = retail_bytes(project, fn.symbol.module, name, offset, width)
        if raw is None:
            continue
        value = struct.unpack('>f' if width == 4 else '>d', raw)[0]
        kind = 'f32' if width == 4 else 'f64'
        lines.append(f'  {name}{offset:+#x}: {kind} {value!r}; bits {raw.hex()}; '
                     f'{len(sites)} load(s), first at {sites[0]:08X}')
    from .datacontext import evidence
    lines.extend(evidence(project, fn, loads, full))
    return lines
