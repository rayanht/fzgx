"""Retail data evidence shared by the lifter and matcher context."""
from __future__ import annotations

import re
import struct
from collections import deque

RELOC = re.compile(r'([\w.$@]+?)([+-](?:0x[\da-fA-F]+|\d+))?@(ha|h|l|sda21)\b')
MEMORY = re.compile(r'(.+)\((r\d+)\)$')
WIDTH = {'lfs': 4, 'lfd': 8, 'lwz': 4, 'lhz': 2, 'lha': 2, 'lbz': 1}


def memory_loads(rows, tables=None):
    """Follow symbolic bases through the CFG, intersecting facts at every join.

    Results use aligned-row indices so target and candidate accesses can be
    compared without confusing object addresses with the diff's row offsets.
    """
    tables = tables or {}
    instructions = {i: row['instruction'] for i, row in enumerate(rows)
                    if row.get('instruction', {}).get('address') is not None}
    indices = list(instructions)
    if not indices:
        return {}
    addresses = {int(ins['address']): i for i, ins in instructions.items()}
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
        if op in WIDTH and len(args) == 2 and (mem := MEMORY.fullmatch(args[1])):
            base = before.get(mem[2])
            location = None
            if symbolic and (rel[3] == 'sda21' or (base and base[:2] == symbolic[:2] and base[2])):
                location = symbolic[:2]
            elif base and not base[2] and re.fullmatch(r'-?(?:0x[\da-f]+|\d+)', mem[1]):
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
        if dest is not None and not call and int(dest) in addresses:
            successors.append(addresses[int(dest)])
        if op == 'bctr':
            table = before.get('ctr')
            if table and table[2] == 'table' and table[0] in tables:
                successors = [addresses[a] for a in tables[table[0]] if a in addresses]
            else:
                # Unknown successors must not inherit a guessed base from one
                # arm. Relocated tables, however, preserve dominating pool bases.
                successors = indices
                after = {}
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
