"""Instruction -> source line attribution from MWCC's DWARF 1 `.line` table.

`-sym on` leaves the generated code byte-identical (checked on GC/1.3.2, 2026-09-15)
and adds a `.line` section: per function a table of (length, base) followed by
10-byte rows (line, column, address delta). Relocations in `.rela.line` bind each
table's base to its function symbol. With it every differing object row names the
C statement that produced it, so repairs can target that statement instead of
searching blindly over every site.
"""
from __future__ import annotations

import struct
from pathlib import Path
from typing import Dict, List, Optional, Tuple


def _sections(data: bytes):
    shoff = struct.unpack('>I', data[0x20:0x24])[0]
    shentsize, shnum, shstrndx = struct.unpack('>HHH', data[0x2e:0x34])
    raw = []
    for i in range(shnum):
        off = shoff + i * shentsize
        name, typ, flags, addr, offset, size, link, info = struct.unpack('>IIIIIIII', data[off:off + 32])
        raw.append((name, typ, offset, size, link, info))
    strtab = raw[shstrndx]

    def nm(n):
        s = data[strtab[2] + n:]
        return s[:s.index(b'\0')].decode()
    return {nm(name): (i, typ, offset, size, link, info) for i, (name, typ, offset, size, link, info) in enumerate(raw)}


def _symbols(data: bytes, secs) -> List[Tuple[str, int, int, int]]:
    """(name, value, size, shndx) per symbol."""
    _, _, off, size, link, _ = secs['.symtab']
    stroff = [s for s in secs.values() if s[0] == link][0][2]
    out = []
    for k in range(size // 16):
        name, value, sz, info, other, shndx = struct.unpack('>IIIBBH', data[off + k * 16: off + k * 16 + 16])
        s = data[stroff + name:]
        out.append((s[:s.index(b'\0')].decode(), value, sz, shndx))
    return out


def tables(obj: Path) -> Dict[str, List[Tuple[int, int]]]:
    """{function name: [(address offset within the function, line), ...]}."""
    data = obj.read_bytes()
    secs = _sections(data)
    if '.line' not in secs:
        return {}
    _, _, loff, lsize, _, _ = secs['.line']
    line = data[loff:loff + lsize]
    syms = _symbols(data, secs)
    # table base -> function symbol through the relocations against the base fields
    bound: Dict[int, str] = {}
    if '.rela.line' in secs:
        _, _, roff, rsize, _, _ = secs['.rela.line']
        for k in range(rsize // 12):
            r_offset, r_info, r_addend = struct.unpack('>IIi', data[roff + k * 12: roff + k * 12 + 12])
            sym = syms[r_info >> 8]
            name = sym[0]
            if not name:  # a section symbol: the function that starts at the addend
                name = next((s[0] for s in syms if s[3] == sym[3] and s[1] == r_addend and s[0]), '')
                r_addend = 0
            bound[r_offset] = (name, r_addend)
    out: Dict[str, List[Tuple[int, int]]] = {}
    pos = 0
    while pos + 8 <= len(line):
        length, base = struct.unpack('>II', line[pos:pos + 8])
        if length < 8 or pos + length > len(line):
            break
        name, addend = bound.get(pos + 4, ('', 0))
        rows = []
        q = pos + 8
        while q + 10 <= pos + length:
            ln, col, delta = struct.unpack('>IHI', line[q:q + 10])
            rows.append((delta - addend, ln))
            q += 10
        if name:
            out.setdefault(name, []).extend(rows)
        pos += length
    return out


def line_of(table: List[Tuple[int, int]], offset: int) -> Optional[int]:
    """The source line whose code contains the instruction at `offset` (function-relative)."""
    best = None
    for delta, ln in table:
        if delta <= offset and (best is None or delta >= best[0]):
            best = (delta, ln)
    return best[1] if best else None
