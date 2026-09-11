"""Read and replay the stock MWCC interference graph; no compiler mutation.

Layouts and allocator semantics are verified against the named PE binaries.
See docs/REGISTER_REPAIR.md for reverse-engineering provenance and limits.
This module also runs in Apple's LLDB Python 3.9.
"""
from __future__ import annotations

import struct
import hashlib

PROFILES = {
    'ccf4b465cec73b5aae9c5c5543dcf8cda8a62aba246f89e2e0b200d742f2e55c': {
        'compiler': 'GC/1.2.5n', 'codegen': 0x4351C0, 'select': 0x4CE2D0, 'graph': 0x587E3C,
        'counts': {'gpr': 0x58846E, 'fpr': 0x58846C}, 'count_width': 2,
        'class_global': None, 'register_offset': 12,
        'pcode_blocks': 0x587C74, 'opcode_table': 0x5654B0,
    },
    '4e502c38465500d4fda8d966b268151a6c74c730508e3d9b7efd23d1a6083715': {
        'compiler': 'GC/1.3', 'codegen': 0x433590, 'select': 0x506F50, 'graph': 0x5E67D0,
        'counts': {'gpr': 0x5E6A8C, 'fpr': 0x5E6A88}, 'count_width': 4,
        'class_global': 0x5E7317, 'register_offset': 16,
        'pcode_blocks': 0x5E67B0, 'opcode_table': 0x5BDCF0,
    },
    '7cbae0a5bd81e07d7fa8975bbc4e969b5dea265cc29c5ee6bae0453a6e25f225': {
        'compiler': 'GC/1.3.2', 'codegen': 0x433310, 'select': 0x507A30, 'graph': 0x5E87D0,
        'counts': {'gpr': 0x5E8A8C, 'fpr': 0x5E8A88}, 'count_width': 4,
        'class_global': 0x5E931F, 'register_offset': 16,
        'pcode_blocks': 0x5E87B0, 'opcode_table': 0x5BEE78,
    },
}
PROFILES['0443b5c02b1aa7b575b61e0e24c4d5ad6bed8fd54cc42de5a2204a5216001914'] = {
    **PROFILES['ccf4b465cec73b5aae9c5c5543dcf8cda8a62aba246f89e2e0b200d742f2e55c'],
    'compiler': 'GC/1.2.5',
}

INITIAL = {'gpr': (0, *range(3, 13)), 'fpr': tuple(range(14))}


def header_fingerprint(root, version):
    digest = hashlib.sha256()
    for directory in (root / 'include', root / 'build' / version / 'include'):
        for path in sorted(directory.rglob('*')):
            if path.is_file():
                digest.update(str(path.relative_to(root)).encode() + b'\0' + path.read_bytes())
    return digest.hexdigest()


def read_graph(read, profile, register_class, head=0):
    def number(address, width=4):
        return int.from_bytes(read(address, width), 'little')

    count = number(profile['counts'][register_class], profile['count_width'])
    if not 32 <= count <= 32767:
        raise ValueError(f'invalid virtual register count: {count}')
    graph = number(profile['graph'])
    pointers = struct.unpack('<' + 'I' * count, read(graph, 4 * count))
    offset = profile['register_offset']
    nodes, addresses = [], {}
    for register, pointer in enumerate(pointers):
        if not pointer:
            continue
        data = read(pointer, offset + 10)
        virtual, degree, physical, flags, neighbors = struct.unpack_from('<hhhhh', data, offset)
        if virtual != register or neighbors < 0 or neighbors > count:
            raise ValueError(f'invalid graph node v{register}: {(virtual, neighbors)}')
        adjacent = list(struct.unpack('<' + 'h' * neighbors, read(pointer + offset + 10, neighbors * 2)))
        if any(n < 0 or n >= count for n in adjacent):
            raise ValueError('invalid interference edge')
        node = {'virtual_register': register, 'physical_register': physical,
                'flags': flags, 'degree': degree, 'neighbors': adjacent}
        obj = struct.unpack_from('<I', data, 4)[0]
        if obj:
            name_record = number(obj + 10)
            if name_record:
                name = bytearray()
                for i in range(1024):
                    byte = read(name_record + 10 + i, 1)
                    if byte == b'\0':
                        break
                    name.extend(byte)
                else:
                    raise ValueError('unterminated compiler object name')
                node['name'] = name.decode('utf-8', errors='replace')
        nodes.append(node)
        addresses[pointer] = (register, struct.unpack_from('<I', data)[0])
    order, seen = [], set()
    while head:
        if head in seen or head not in addresses:
            raise ValueError('invalid simplify linked list')
        seen.add(head)
        register, head = addresses[head]
        order.append(register)
    return {'register_class': register_class, 'nodes': nodes, 'simplify_order': order}


def replay(snapshot, order=None):
    """Replay SelectColors, including its nonrecursive coalesced-neighbor reads."""
    nodes = {n['virtual_register']: n for n in snapshot['nodes']}
    colors = {r: n['physical_register'] for r, n in nodes.items()}
    mask = sum(1 << c for c in INITIAL[snapshot['register_class']])
    next_saved = 31
    for register in snapshot['simplify_order'] if order is None else order:
        blocked = 0
        for neighbor in nodes[register]['neighbors']:
            color = colors[neighbor]
            if 0 <= color < 32:
                blocked |= 1 << color
        available = mask & ~blocked
        if available:
            color = (available & -available).bit_length() - 1
        else:
            # The stock allocator claims the next saved color directly. It does
            # not re-resolve coalesced parents or recompute the blocked mask.
            while next_saved >= 14 and mask & (1 << next_saved):
                next_saved -= 1
            color = next_saved if next_saved >= 14 else -1
            if color >= 0:
                mask |= 1 << color
                next_saved -= 1
        colors[register] = color
    return colors


def selection_order(snapshot, desired):
    """Construct a sufficient ordering witness, not a C-realizability proof.

    A node is eligible when its desired color is the compiler's current first
    choice. Prefer lower colors already in the pool; open saved colors only
    when none of those nodes is eligible. No permutations or compile probes.
    Failure is inconclusive: coalesced aliases and partial constraints can
    require a different witness. Every returned order is replay-validated.
    """
    nodes = {n['virtual_register']: n for n in snapshot['nodes']}
    remaining = set(snapshot['simplify_order'])
    if set(desired) != remaining or any(not 0 <= c < 32 for c in desired.values()):
        raise ValueError('desired colors must cover every active node without spills')
    colors = {r: n['physical_register'] for r, n in nodes.items()}
    mask = sum(1 << c for c in INITIAL[snapshot['register_class']])
    next_saved, order = 31, []
    while remaining:
        eligible = []
        for register in remaining:
            blocked = 0
            for neighbor in nodes[register]['neighbors']:
                color = colors[neighbor]
                if 0 <= color < 32:
                    blocked |= 1 << color
            available = mask & ~blocked
            color = (available & -available).bit_length() - 1 if available else next_saved
            if color == desired[register]:
                eligible.append((not bool(available), color, register))
        if not eligible:
            return None
        claimed, color, register = min(eligible)
        if claimed:
            if next_saved < 14:
                return None
            mask |= 1 << color
            next_saved -= 1
        colors[register] = color
        remaining.remove(register)
        order.append(register)
    actual = replay(snapshot, order)
    if any(actual[r] != c for r, c in desired.items()):
        raise AssertionError('invalid allocation witness')
    return order


def simplify(snapshot, ranks=None):
    """Replay the non-spilling simplify path, retaining coalesced ghost edges.

    Unknown spill decisions are returned explicitly instead of approximating
    the compiler's floating-point cost comparison and tie-breaking.
    """
    nodes = {n['virtual_register']: n for n in snapshot['nodes']}
    remaining = set(snapshot['simplify_order'])
    degree = {r: len(n['neighbors']) for r, n in nodes.items()}
    ranks = ranks or {}
    order = sorted(remaining, key=lambda r: (ranks.get(r, r), r))
    removed = []
    available = 29 if snapshot['register_class'] == 'gpr' else 32
    while remaining:
        changed = False
        for register in order:
            if register not in remaining or degree[register] >= available:
                continue
            remaining.remove(register)
            removed.append(register)
            for neighbor in nodes[register]['neighbors']:
                degree[neighbor] -= 1
            changed = True
        if not changed:
            return None
    return removed[::-1]


def read_pcode(read, profile):
    """Capture instruction identities, virtual operands and source lines."""
    modern = profile['register_offset'] == 16
    block_global = profile['pcode_blocks']
    table, stride = profile['opcode_table'], 18 if modern else 16
    header_size, opcode_offset = (36, 32) if modern else (28, 20)
    def u32(address):
        return int.from_bytes(read(address, 4), 'little')
    def string(address):
        result = bytearray()
        for i in range(1024):
            byte = read(address + i, 1)
            if byte == b'\0':
                return result.decode('utf-8', errors='replace')
            result.extend(byte)
        raise ValueError('unterminated PCode string')
    block, seen_blocks, rows, descriptors = u32(block_global), set(), [], {}
    while block:
        if block in seen_blocks or len(seen_blocks) > 100000:
            raise ValueError('invalid PCode block list')
        seen_blocks.add(block)
        instruction, seen = u32(block + 20), set()
        block_index = u32(block + 28)
        while instruction:
            if instruction in seen or len(seen) > 100000:
                raise ValueError('invalid PCode instruction list')
            seen.add(instruction)
            header = read(instruction, header_size)
            opcode = struct.unpack_from('<h', header, opcode_offset)[0]
            count = struct.unpack_from('<h', header, header_size - 2)[0]
            if not 0 <= opcode < 512 or not 0 <= count <= 4096:
                raise ValueError(f'invalid PCode instruction: {opcode}, {count}')
            if opcode not in descriptors:
                descriptor = read(table + opcode * stride, stride)
                descriptors[opcode] = (string(int.from_bytes(descriptor[:4], 'little')),
                                       string(int.from_bytes(descriptor[4:8], 'little')))
            operands = []
            for i in range(count):
                raw = read(instruction + header_size + i * 12, 12)
                if modern:
                    kind = {4: 'gpr', 3: 'fpr'}.get(raw[1]) if raw[0] == 0 else None
                    reg = struct.unpack_from('<h', raw, 4)[0]
                    flags = int.from_bytes(raw[2:4], 'little')
                else:
                    kind = {0: 'gpr', 1: 'fpr'}.get(raw[0])
                    reg = struct.unpack_from('<h', raw, 2)[0]
                    flags = raw[1]
                operands.append({'class': kind, 'reg': reg if kind else None,
                                 'flags': flags, 'raw': raw.hex()})
            mnemonic, fmt = descriptors[opcode]
            rows.append({'id': instruction, 'block': block_index, 'mnemonic': mnemonic.lower(),
                         'format': fmt, 'line': struct.unpack_from('<i', header, 28)[0] if modern else None,
                         'operands': operands})
            instruction = int.from_bytes(header[:4], 'little')
        block = u32(block)
    return rows
