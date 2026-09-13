"""Retail translation units define their file-scope objects and string literals in one place,
and MWCC then addresses every object of a section off one base register: object addresses are
materialized (`addi rX, rBase, off`, even at offset 0) whenever a pointer value is needed, and
only an object's offset 0 is addressed base-relative. A per-function unit that declares the
cluster as one extern struct can never reproduce that shape. This family defines the retail
objects in the unit, in retail order under MWCC's file-scope layout rules (scalars at natural
alignment, arrays 4-aligned, `.bss` objects emitted in first-access order, string literals in
first-use order), with primers in `.fzgxpool` that fix the emission order. Field offsets and
sizes come from an MWCC probe compile of the body's own declarations. The oracle binds the
anonymous section bases (`...bss.N`, `...data.N`) to the retail symbols; the private copies are
dropped at integration. Names a module header declares with another layout are defined under
the `fzgx_obj_` alias, which the BSS base binding accepts."""
from __future__ import annotations

import hashlib
import re
from pathlib import Path

from . import oracle, poolfix
from .project import ROOT, STATE_DIR


INCLUDE_TEXT = None
SCALAR = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4, 'int': 4, 'f32': 4, 'float': 4, 'f64': 8, 'double': 8, 'u64': 8, 's64': 8, 'void': 1}


def include_text():
    global INCLUDE_TEXT
    if INCLUDE_TEXT is None:
        INCLUDE_TEXT = "\n".join(p.read_text(errors='replace') for p in (ROOT / 'include').rglob('*.h'))
    return INCLUDE_TEXT


class Gap:
    def __init__(self, name, addr, end, section):
        self.name, self.addr, self.end, self.size, self.section, self.kind = name, addr, end, end - addr, section, 'object'


def struct_text(tname, text):
    for src in (text, include_text()):
        m = re.search(r"(?:typedef\s+)?struct\s+%s\s*\{(.*?)\n\}" % re.escape(tname), src, re.S)
        if m:
            return m.group(1)
        m = re.search(r"typedef\s+struct\s*\w*\s*\{(.*?)\n\}\s*%s\s*;" % re.escape(tname), src, re.S)
        if m:
            return m.group(1)
    return None


def field_decls(body):
    """field name -> (type text incl. stars, dims list, raw line)."""
    out = {}
    body = re.sub(r"/\*.*?\*/", "", body, flags=re.S)
    body = re.sub(r"//[^\n]*", "", body)
    for line in body.replace('\n', ' ').split(';'):
        line = line.strip() + ';'
        if line == ';':
            continue
        m = re.match(r"((?:const\s+|volatile\s+|unsigned\s+|signed\s+)*(?:struct\s+|union\s+|enum\s+)?\w+(?:\s*\*+)?)\s*(\w+)((?:\[[^\]]+\])*);$", line)
        if m:
            ttext = re.sub(r"\s+", " ", m.group(1)).replace(" *", " *")
            dims = re.findall(r"\[([^\]]+)\]", m.group(3) or '')
            out[m.group(2)] = (ttext, dims, line)
            continue
        pm = re.match(r"([\w\s\*]+)\(\s*\*\s*(\w+)\s*\)\s*(\([^)]*\));$", line)
        if pm:
            out[pm.group(2)] = (None, [], line)
    return out


def probe_layout(p, module, prefix, tname, names, decls, tag):
    """offsets/sizes/elemsizes/aligns of the named fields of struct type tname, from MWCC."""
    lines = []
    for i, n in enumerate(names):
        ttext, dims, raw = decls[n]
        lines.append(f"u8 fzgx_off_{i}[1 + (u32)&(({tname} *)0)->{n}];")
        lines.append(f"u8 fzgx_sz_{i}[sizeof((({tname} *)0)->{n})];")
        sub = ''.join('[0]' for _ in dims)
        lines.append(f"u8 fzgx_esz_{i}[sizeof((({tname} *)0)->{n}{sub})];")
        if ttext is None:
            lines.append(f"u8 fzgx_al_{i}[4];")
        else:
            lines.append(f"struct fzgx_al_{i}_s {{ u8 c; {ttext} t; }};")
            lines.append(f"u8 fzgx_al_{i}[(u32)&((struct fzgx_al_{i}_s *)0)->t];")
    src = prefix + "\n" + "\n".join(lines) + "\n"
    d = STATE_DIR / 'fixup' / 'probe'
    d.mkdir(parents=True, exist_ok=True)
    f = d / f"{tag}_{hashlib.sha1(src.encode()).hexdigest()[:10]}.c"
    f.write_text(src)
    obj = f.with_suffix('.o')
    cp = oracle.compile_source(p, module, f, obj, include_dirs=[ROOT / 'include'])
    if cp.returncode != 0 or not obj.exists():
        return None, re.sub(r"\s+", " ", cp.stdout + cp.stderr)[-300:]
    sizes = {s['name']: s['size'] for s in poolfix.Elf(obj.read_bytes()).symbols()}
    out = {}
    for i, n in enumerate(names):
        try:
            out[n] = (sizes[f'fzgx_off_{i}'] - 1, sizes[f'fzgx_sz_{i}'], sizes[f'fzgx_esz_{i}'], sizes[f'fzgx_al_{i}'])
        except KeyError:
            return None, f'probe symbol missing for {n}'
    return out, None


def filler(prefix, pos, end):
    out, q = [], pos
    while q < end and q % 2:
        out.append((q, f"u8 {prefix}_{q:X};", f"{prefix}_{q:X}")); q += 1
    while q < end and q % 4 and q + 2 <= end:
        out.append((q, f"u16 {prefix}_{q:X};", f"{prefix}_{q:X}")); q += 2
    n = (end - q) // 4
    if n == 1:
        out.append((q, f"u32 {prefix}_{q:X};", f"{prefix}_{q:X}")); q += 4
    elif n > 1:
        out.append((q, f"u32 {prefix}_{q:X}[{n}];", f"{prefix}_{q:X}")); q += 4 * n
    while q + 2 <= end:
        out.append((q, f"u16 {prefix}_{q:X};", f"{prefix}_{q:X}")); q += 2
    while q < end:
        out.append((q, f"u8 {prefix}_{q:X};", f"{prefix}_{q:X}")); q += 1
    return out


def fdef(decl, name):
    ttext, dims, raw = decl
    if ttext is None:
        return re.sub(r"\(\s*\*\s*\w+\s*\)", f"(*{name})", raw)
    return f"{ttext}{'' if ttext.endswith('*') else ' '}{name}{''.join(f'[{d}]' for d in dims)};"


def find_models(text):
    """(pvar, tname, base, stmt, kind) for pointer models and direct-global models."""
    models = []
    for m in re.finditer(r"(?:(?:struct\s+)?(\w+)\s*\*\s*)?(\w+)\s*=\s*\((?:struct\s+)?(\w+)\s*\*\)\s*&(lbl_\d+_bss_[0-9A-F]+|lbl_[0-9A-F]{8})\s*;", text):
        models.append((m.group(2), m.group(3), m.group(4), m.group(0), 'ptr'))
    seen = {m[2] for m in models}
    for m in re.finditer(r"\nextern\s+(\w+)\s+(lbl_\d+_bss_[0-9A-F]+|lbl_[0-9A-F]{8})\s*((?:\[[^\]]*\])*)\s*;", text):
        tname, base = m.group(1), m.group(2)
        if base in seen or tname not in SCALAR:
            continue
        if re.search(r"&\s*%s\b" % re.escape(base), text) and not re.search(r"\b%s\s*=\s*\(" % re.escape(base), text):
            models.append((None, tname, base, m.group(0), 'bare'))
            seen.add(base)
    for m in re.finditer(r"\nextern\s+(?:struct\s+)?(\w+)\s+(lbl_\d+_bss_[0-9A-F]+|lbl_[0-9A-F]{8})\s*;", text):
        tname, base = m.group(1), m.group(2)
        if base in seen or tname in ('u8', 'u16', 'u32', 's8', 's16', 's32', 'f32', 'f64', 'int', 'char', 'void'):
            continue
        if re.search(r"\b%s\.\w+" % re.escape(base), text):
            models.append((None, tname, base, m.group(0), 'direct'))
            seen.add(base)
    # declared by an included header: the definition needs the header's extern renamed away
    for base in sorted(set(re.findall(r"\b(lbl_\d+_bss_[0-9A-F]+|lbl_[0-9A-F]{8})\.\w+", text))):
        if base in seen:
            continue
        hm = re.search(r"\nextern\s+(?:struct\s+)?(\w+)\s+%s\s*;" % re.escape(base), include_text())
        if hm:
            models.append((None, hm.group(1), base, '', 'direct-header'))
            seen.add(base)
    return models


def tu_objects(p, symbol, text, mode, cache):
    sym = p.resolve(symbol)
    syms = p.symbols(sym.module)
    notes = []
    models = find_models(text)
    if not models:
        return None, ['no bss model']
    out_text = text
    fm = re.search(r"\n[^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" % re.escape(sym.name), out_text)
    if not fm:
        return None, ['function definition not found']
    prefix = out_text[:fm.start() + 1]
    all_defs, all_typedefs = [], []
    for pvar, tname, base, stmt, kind in models:
        b = syms.get(base)
        if b is None or b.section != '.bss':
            notes.append(f'{base}: not a .bss symbol'); return None, notes
        if kind == 'direct-header':
            kind = 'direct'
        if kind == 'direct':
            pvar = f'fzgx_p_{base}'
            out_text = re.sub(r"\b%s\." % re.escape(base), f"{pvar}->", out_text)
            out_text = re.sub(r"&\s*%s\b(?![\.\w])" % re.escape(base), f"((u8 *){pvar} + 0)", out_text)
            body_only = "\n".join(l for l in out_text.replace(stmt, '').split("\n") if not l.lstrip().startswith('#'))
            if re.search(r"(?<![\w>])%s\b(?!\s*->)" % re.escape(base), body_only):
                notes.append(f'{base}: direct global used as a value'); return None, notes
            stmt_removed = stmt
            stmt = ''
        else:
            stmt_removed = stmt
        synthetic = {}
        decls = {}
        byte_model = tname in SCALAR
        if kind == 'bare':
            esz0 = SCALAR[tname]
            pvar = f'fzgx_p_{base}'
            out_text = re.sub(r"&\s*%s\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]" % re.escape(base), lambda mm: f"({tname} *)({pvar} + {int(mm.group(1), 0)})", out_text)
            out_text = re.sub(r"(?<![\w&])%s\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]" % re.escape(base), lambda mm: f"{pvar}[{int(mm.group(1), 0)}]", out_text)
            out_text = re.sub(r"&\s*%s\b(?![\.\[\w])" % re.escape(base), f"({tname} *)({pvar} + 0)", out_text)
            body_only = "\n".join(l for l in out_text.replace(stmt, '').split("\n") if not l.lstrip().startswith('#'))
            if re.search(r"(?<![\w>])%s\b" % re.escape(base), body_only):
                notes.append(f'{base}: bare symbol used as a value'); return None, notes
            stmt_removed = stmt
            kind = 'bytes'
        if byte_model:
            esz = SCALAR[tname]
            def _syn(ttext, n):
                size = SCALAR.get(ttext.replace(' *', '').strip(), 4 if '*' in ttext else None)
                if size is None:
                    return None
                fname = f"fzgx_{re.sub(r'[^A-Za-z0-9]', '_', ttext)}_{n:X}"
                synthetic[fname] = (n, size, size, min(size, 8))
                decls[fname] = (ttext, [], f"{ttext} {fname};")
                return fname
            def _deref(mm):  # *(T *)(p + N)
                f = _syn(mm.group(1).strip(), int(mm.group(2), 0))
                return mm.group(0) if f is None else f"{pvar}->{f}"
            out_text = re.sub(r"\*\s*\(\s*((?:const\s+)?\w+(?:\s*\*)?)\s*\*\s*\)\s*\(\s*%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)" % re.escape(pvar), _deref, out_text)
            def _idx(mm):  # p[N]
                f = _syn(tname, int(mm.group(1), 0) * esz)
                return f"{pvar}->{f}"
            out_text = re.sub(r"\b%s\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]" % re.escape(pvar), _idx, out_text)
            def _addr(mm):  # (T *)(p + N)  -> (T *)&p->byte_N
                f = _syn('u8', int(mm.group(2), 0))
                return f"({mm.group(1).strip()} *)&{pvar}->{f}"
            out_text = re.sub(r"\(\s*((?:const\s+)?\w+(?:\s*\*)?)\s*\*\s*\)\s*\(\s*%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)" % re.escape(pvar), _addr, out_text)
            def _plus(mm):  # p + N
                f = _syn('u8', int(mm.group(1), 0) * esz)
                return f"({tname} *)&{pvar}->{f}"
            out_text = re.sub(r"\b%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\b" % re.escape(pvar), _plus, out_text)
            def _bare(mm):
                f = _syn('u8', 0)
                return f"({tname} *)&{pvar}->{f}"
            if kind == 'ptr':
                out_text = re.sub(r"\n[ \t]*(?:const\s+)?%s\s*\*\s*%s\s*;" % (re.escape(tname), re.escape(pvar)), '', out_text)
                out_text = re.sub(r"(?<=[;{}]\s)(?:const\s+)?%s\s*\*\s*%s\s*;\s*" % (re.escape(tname), re.escape(pvar)), '', out_text)
            marked = out_text.replace(stmt_removed, '\x00STMT\x00') if stmt_removed else out_text
            out_text = re.sub(r"(?<![\w>])%s\b(?!\s*(?:->|=[^=]))" % re.escape(pvar), _bare, marked).replace('\x00STMT\x00', stmt_removed)
        else:
            st = struct_text(tname, text)
            if st is None:
                notes.append(f'{tname}: struct text not found'); return None, notes
            decls = field_decls(st)

        def _byteoff(mm):
            n = int(mm.group(1), 0)
            fname = f"fzgx_byte_{n:X}"
            synthetic[fname] = n
            return f"(u8 *)&{pvar}->{fname}"
        out_text = re.sub(r"\(u8 \*\)\s*(?:\(u32\)\s*)?\b%s\b\s*\+\s*(0x[0-9A-Fa-f]+|\d+)" % re.escape(pvar), _byteoff, out_text)
        uses = list(re.finditer(r"(&?)\b%s->(\w+)((?:\[[^\]]*\])*)" % re.escape(pvar), out_text))
        other = re.sub(r"\b%s->" % re.escape(pvar), '', out_text).replace(stmt_removed, '')
        other = "\n".join(l for l in other.split("\n") if not l.lstrip().startswith('#'))
        other = re.sub(r"(?:struct\s+)?%s\s*\*\s*%s\s*;" % (re.escape(tname), re.escape(pvar)), '', other)
        if re.search(r"\b%s\b" % re.escape(pvar), other):
            notes.append(f'{pvar}: used other than through ->'); return None, notes
        if not uses:
            notes.append(f'{pvar}: no uses'); return None, notes
        names = sorted({u.group(2) for u in uses if u.group(2) not in synthetic})
        missing = [n for n in names if n not in decls]
        if missing:
            notes.append(f'{tname}: fields without declaration text: {missing[:3]}'); return None, notes
        if names:
            key = (tname, tuple(names))
            if key not in cache:
                is_alias = re.search(r"\}\s*%s\s*;|typedef\s+struct\s+\w+\s+%s\s*;" % (re.escape(tname), re.escape(tname)), prefix + include_text())
                cache[key] = probe_layout(p, sym.module, prefix, tname if is_alias else 'struct ' + tname, names, decls, symbol)
            layout, err = cache[key]
            if layout is None:
                notes.append(f'{tname}: probe failed: {err}'); return None, notes
        else:
            layout = {}
        for fname, v in synthetic.items():
            if isinstance(v, tuple):
                layout[fname] = v
            else:
                layout[fname] = (v, 1, 1, 1)
                decls[fname] = ('u8', [], f'u8 {fname};')
        cluster = sorted((s for s in syms.values() if s.section == b.section and s.kind == 'object' and s.addr >= b.addr), key=lambda s: s.addr)
        if not cluster or cluster[0].addr != b.addr:
            notes.append(f'{base}: not an object start'); return None, notes
        # gaps between dtk objects become pseudo-objects
        full = []
        for i, s in enumerate(cluster):
            full.append(s)
            nxt = cluster[i + 1].addr if i + 1 < len(cluster) else None
            if nxt is not None and nxt > s.end:
                full.append(Gap(f"{base}_gap_{s.end:X}", s.end, nxt, b.section))
        cluster = full
        per_obj, rewrites = {}, []
        for um in uses:
            amp, fname, idx = um.group(1), um.group(2), um.group(3)
            foff, fsize, esize, ealign = layout[fname]
            addr = b.addr + foff
            obj = next((s for s in cluster if s.addr <= addr < s.end), None)
            if obj is None:
                notes.append(f'{fname}: offset {foff:#x} outside cluster'); return None, notes
            inner = addr - obj.addr
            if addr + fsize > obj.end:
                notes.append(f'{fname}: crosses object {obj.name}'); return None, notes
            rec = per_obj.setdefault(obj.name, {'sym': obj, 'fields': {}})
            prev = rec['fields'].get(inner)
            synthetic_name = fname.startswith(('fzgx_byte_', 'fzgx_u8_'))
            if prev and prev[0] != fname and decls[prev[0]] != decls[fname]:
                if synthetic_name:
                    pass  # a byte view of a real field shares the field's object slot
                elif prev[0].startswith(('fzgx_byte_', 'fzgx_u8_')):
                    rec['fields'][inner] = (fname, fsize, esize, ealign)
                else:
                    notes.append(f'{fname}: conflicting field at {obj.name}+{inner:#x}'); return None, notes
            rec['fields'].setdefault(inner, (fname, fsize, esize, ealign))
            rewrites.append((um, obj, inner, fname, idx, amp))
        last = max(r['sym'].end for r in per_obj.values())
        before = [s for s in cluster if s.addr < last]
        beyond = [s for s in cluster if s.addr >= last]
        if len(before) < 6 and beyond:
            last = beyond[min(len(beyond), 6 - len(before)) - 1].end
        defs, pos, access = [], b.addr, {}
        for s in cluster:
            if s.addr >= last:
                break
            if s.addr < pos:
                continue
            rec = per_obj.get(s.name)
            if rec is None:
                parts = filler(s.name + '_fill', s.addr, s.end)
                first = f"{s.name}_fill_{s.addr:X}"
                defs += [(a, d.replace(first, s.name) if a == s.addr else d, acc.replace(first, s.name) if a == s.addr else acc) for a, d, acc in parts]
                pos = s.end
                continue
            fl = rec['fields']
            if mode == 'split':
                q = s.addr
                for inner in sorted(fl):
                    fname, fsize, esize, ealign = fl[inner]
                    a = s.addr + inner
                    if a < q:
                        notes.append(f'{s.name}: overlapping fields'); return None, notes
                    if a > q:
                        defs += filler(f'{s.name}_fill', q, a)
                    name = s.name if inner == 0 else f"{s.name}_{inner:X}"
                    dims = decls[fname][1]
                    if a % max(ealign, 1) or (dims and a % 4):
                        notes.append(f'{s.name}: field {fname} misaligned as an object'); return None, notes
                    defs.append((a, fdef(decls[fname], name), name))
                    access[(s.name, inner)] = name
                    q = a + fsize
                if q < s.end:
                    defs += filler(f'{s.name}_fill', q, s.end)
                pos = s.end
                continue
            if list(fl) == [0]:
                fname, fsize, esize, ealign = fl[0]
                dims = decls[fname][1]
                if fsize == s.size and not (dims and s.addr % 4):
                    defs.append((s.addr, fdef(decls[fname], s.name), s.name))
                    access[(s.name, 0)] = s.name
                    pos = s.end
                    continue
            body, off, align = [], 0, 1
            for inner in sorted(fl):
                fname, fsize, esize, ealign = fl[inner]
                if inner % max(ealign, 1):
                    notes.append(f'{s.name}: field {fname} misaligned'); return None, notes
                if inner > off:
                    body.append(f"    u8 pad_{off:X}[{inner - off:#x}];")
                    off = inner
                elif inner < off:
                    notes.append(f'{s.name}: overlapping fields'); return None, notes
                body.append("    " + fdef(decls[fname], fname))
                access[(s.name, inner)] = f"{s.name}.{fname}"
                off += fsize
                align = max(align, ealign)
            usable = s.size // align * align
            if off > usable:
                notes.append(f'{s.name}: fields exceed aligned size'); return None, notes
            if off < usable:
                body.append(f"    u8 pad_{off:X}[{usable - off:#x}];")
            tobj = f"{s.name}_t"
            all_typedefs.append(f"typedef struct {tobj} {{\n" + "\n".join(body) + f"\n}} {tobj};\n\n")
            defs.append((s.addr, f"{tobj} {s.name};", s.name))
            pos = s.addr + usable
            if usable < s.size:
                defs += filler(s.name + '_tail', pos, s.end)
                pos = s.end
        for um, obj, inner, fname, idx, amp in sorted(rewrites, key=lambda r: -r[0].start()):
            repl = f"{amp}{access[(obj.name, inner)]}{idx}"
            out_text = out_text[:um.start()] + repl + out_text[um.end():]
        if stmt_removed:
            out_text = out_text.replace(stmt_removed, '')
        if kind == 'ptr':
            out_text = re.sub(r"\n[ \t]*(?:struct\s+)?%s\s*\*\s*%s\s*;" % (re.escape(tname), re.escape(pvar)), '', out_text)
        all_defs += defs
        notes.append(f'{base}: {len(per_obj)} objects referenced, {len(defs)} definitions')
    all_defs.sort(key=lambda x: x[0])
    for _, d, _ in all_defs:
        dn = re.search(r"(\w+)(?:\[[^\]]*\])*;$", d.replace('(*', '').replace(')(', ''))
        if dn:
            out_text = re.sub(r"\n[^\n]*\bextern\b[^\n;]*\b%s\b[^\n;]*;" % re.escape(dn.group(1)), '', out_text)
    # names a module header declares with its own layout are defined under an alias (the
    # oracle binds the section base through it); every use in this unit follows the alias
    renamed = {}
    for i, (a, d, acc) in enumerate(all_defs):
        dn = re.search(r"(\w+)(?:\[[^\]]*\])*;$", d.replace('(*', '').replace(')(', ''))
        if dn and re.search(r"\bextern\s+[^;\n]*\b%s\b[^;\n]*;" % re.escape(dn.group(1)), include_text()):
            renamed[dn.group(1)] = 'fzgx_obj_' + dn.group(1)
    if renamed:
        pat = re.compile(r"\b(%s)\b" % "|".join(re.escape(k) for k in renamed))
        all_defs = [(a, pat.sub(lambda m: renamed[m.group(1)], d), pat.sub(lambda m: renamed[m.group(1)], acc)) for a, d, acc in all_defs]
        all_typedefs = [pat.sub(lambda m: renamed[m.group(1)], td) for td in all_typedefs]
        body_start = out_text.rfind('\n', 0, re.search(r"\n[^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" % re.escape(sym.name), out_text).start() + 1)
        out_text = out_text[:body_start] + pat.sub(lambda m: renamed[m.group(1)], out_text[body_start:])
    block = ''.join(all_typedefs) + "/* file-scope objects of the retail TU, in retail order: MWCC addresses them off one section base */\n"
    block += "\n".join(d for _, d, _ in all_defs) + "\n\n"
    block += '#pragma section code_type ".fzgxpool"\nstatic void fzgx_bss_layout(void) {\n    volatile u8 s;  /* fzgx-allow: S2 layout primer sink: MWCC emits .bss objects in first-access order */\n'
    block += "".join(f"    s = *(u8 *)&{acc};\n" for _, _, acc in all_defs)
    block += '}\n#pragma section code_type ".text"\n\n'
    fm = re.search(r"\n[^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" % re.escape(sym.name), out_text)
    out_text = out_text[:fm.start() + 1] + block + out_text[fm.start() + 1:]
    return out_text, notes


def _diff_rows(r):
    rows = r._rows if r._rows else ([], [])
    return sum(1 for l, rr in zip(*rows) if (l.get('diff_kind') or 'DIFF_NONE') != 'DIFF_NONE' or (rr.get('diff_kind') or 'DIFF_NONE') != 'DIFF_NONE')





def section_bytes(p, module, section, addr=None):
    if module == 'main':
        for base, raw in p._rel_layout('main').values():
            if addr is not None and base <= addr < base + len(raw):
                return base, raw
        return None
    sec = p._raw_section(module, section)
    base = p._section_base(module, section)
    return (base, sec) if sec is not None else None


def c_literal(b):
    out = ''
    for ch in b:
        if ch == 0x5c:
            out += '\\\\'
        elif ch == 0x22:
            out += '\\"'
        elif ch == 0x0a:
            out += '\\n'
        elif ch == 0x0d:
            out += '\\r'
        elif ch == 0x09:
            out += '\\t'
        elif 0x20 <= ch < 0x7f:
            out += chr(ch)
        else:
            return None
    return '"' + out + '"'


def string_at(raw, off):
    """(bytes without NUL, padded length) of the NUL-terminated string at off, or None."""
    e = raw.find(b'\0', off)
    if e < 0 or e == off:
        return None
    s = raw[off:e]
    if c_literal(s) is None:
        return None
    n = (e - off + 1 + 3) & ~3
    return s, n


def string_run(p, symbol, text, cast=''):
    sym = p.resolve(symbol)
    syms = p.symbols(sym.module)
    first = next((syms[l] for l in re.findall(r"\b(lbl_\d+_data_[0-9A-F]+|lbl_[0-9A-F]{8})\b", text) if syms.get(l) and syms[l].section == '.data'), None)
    sb = section_bytes(p, sym.module, '.data', first.addr if first else None)
    if sb is None:
        return None, ['no raw .data for this module']
    base_addr, raw = sb
    notes = []
    out = text
    uses = {}  # (addr) -> list of (span, replacement builder)
    # byte-pointer models: P = (u8 *)&LBL; ... ((u8 *)(u32)P + N) / (P + N) / P
    for m in re.finditer(r"(\w+)\s*=\s*\(u8 \*\)\s*&(lbl_\d+_data_[0-9A-F]+|lbl_[0-9A-F]{8})\s*;", out):
        pvar, lbl = m.group(1), m.group(2)
        out = out.replace(m.group(0), '')
        out = re.sub(r"\n[ \t]*u8\s*\*\s*%s\s*;" % re.escape(pvar), '', out)
        out = re.sub(r"\(u8 \*\)\s*\(u32\)\s*%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)" % re.escape(pvar), lambda mm: f"{lbl} + {int(mm.group(1), 0)}", out)
        out = re.sub(r"\b%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)" % re.escape(pvar), lambda mm: f"{lbl} + {int(mm.group(1), 0)}", out)
        out = re.sub(r"\b%s\b" % re.escape(pvar), lbl, out)
    addrs = {}
    def repl_use(mm):
        lbl, off = mm.group(1), int(mm.group(2) or '0', 0)
        s = syms.get(lbl)
        if s is None or s.section != '.data':
            return mm.group(0)
        a = s.addr + off
        st = string_at(raw, a - base_addr)
        if st is None or (a - 1 - base_addr >= 0 and raw[a - 1 - base_addr] != 0 and a != s.addr):
            addrs[a] = None
            return mm.group(0)
        addrs[a] = st[0]
        return c_literal(st[0])
    pat = re.compile(r"(?:\((?:const )?(?:char|u8|void) \*\)\s*)?&?\b(lbl_\d+_data_[0-9A-F]+|lbl_[0-9A-F]{8})\b(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?(?!\s*\[|\s*\.|\w)")
    fm0 = re.search(r"\n[^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" % re.escape(sym.name), out)
    if not fm0:
        return None, ['function definition not found']
    head, tail = out[:fm0.start()], out[fm0.start():]
    # string literals are `char[]`: uses typed as u8/void pointers keep an explicit cast
    def repl_use2(mm):
        r = repl_use(mm)
        if r.startswith('"') and mm.group(0).lstrip().startswith('('):
            return mm.group(0)[:mm.group(0).index(')') + 1] + r
        if r.startswith('"') and cast:
            return cast + r
        return r
    out = head + pat.sub(repl_use2, tail)
    if not addrs:
        return None, ['no string references']
    if any(v is None for v in addrs.values()):
        return None, [f'non-string reference at {a:#x}' for a, v in addrs.items() if v is None][:3]
    lo, hi = min(addrs), max(addrs)
    # retail addresses the strings off the TU's first .data object: when that object starts
    # before the string run, the unit reproduces the bytes in between as a private pad
    pad = ''
    bases = [syms[l] for l in set(re.findall(r"\b(lbl_\d+_data_[0-9A-F]+|lbl_[0-9A-F]{8})\b", text)) if syms.get(l) and syms[l].section == '.data' and syms[l].addr < lo]
    if bases:
        b0 = min(bases, key=lambda s: s.addr)
        if lo - b0.addr > 0x4000:
            return None, [f'pad from {b0.name} to the string run is {lo - b0.addr:#x} bytes']
        pb = raw[b0.addr - base_addr:lo - base_addr]
        lines = ["    " + ", ".join(f"0x{x:02X}" for x in pb[i:i + 32]) + "," for i in range(0, len(pb), 32)]
        pad = f"static u8 fzgx_data_{b0.name}[{len(pb):#x}] = {{  /* fzgx-allow: A1 retail data bytes: the TU's .data objects before its string literals; dropped at integration */\n" + "\n".join(lines) + "\n};\n\n"
    run, a = [], lo
    while a <= hi:
        st = string_at(raw, a - base_addr)
        if st is None:
            return None, [f'string run broken at {a:#x}']
        run.append(st[0])
        a += st[1]
    for lbl in set(re.findall(r"\b(lbl_\d+_data_[0-9A-F]+|lbl_[0-9A-F]{8})\b", text)):
        if syms.get(lbl) and lo <= syms[lbl].addr <= hi:
            out = re.sub(r"\n[^\n]*\bextern\b[^\n;]*\b%s\b[^\n;]*;" % re.escape(lbl), '', out)
    if not re.search(r"\bOSReport\s*\(", out.split('{')[0]) and 'extern void OSReport' not in out:
        decl = "extern void OSReport(const char *, ...);\n"
    else:
        decl = ''
    prim = '#pragma section code_type ".fzgxpool"\nstatic void fzgx_string_layout(void) {\n    /* fzgx-allow: S2 layout primer: MWCC emits string literals in first-use order; the section is dropped at integration */\n'
    prim += "".join(f"    OSReport({c_literal(s)});\n" for s in run)
    prim += '}\n#pragma section code_type ".text"\n\n'
    fm = re.search(r"\n[^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" % re.escape(sym.name), out)
    if not fm:
        return None, ['function definition not found']
    out = out[:fm.start() + 1] + decl + pad + prim + out[fm.start() + 1:]
    notes.append(f'{len(addrs)} string uses, run of {len(run)} literals from {lo:#x}')
    return out, notes


def _diff_rows_unused(r):
    rows = r._rows if r._rows else ([], [])
    return sum(1 for l, rr in zip(*rows) if (l.get('diff_kind') or 'DIFF_NONE') != 'DIFF_NONE' or (rr.get('diff_kind') or 'DIFF_NONE') != 'DIFF_NONE')



def tu_section_layout(p, symbol, body, check):
    """Proposals: retail BSS objects defined in the unit (per dtk symbol / per referenced field),
    each also with the TU's string run reproduced, and the string run alone."""
    if not re.search(r"\blbl_(?:\d+_(?:bss|data)_[0-9A-F]+|[0-9A-F]{8})\b", body):
        return []
    out = []
    cache = {}
    bases = []
    for mode in ('dtk', 'split'):
        try:
            text, notes = tu_objects(p, symbol, body, mode, cache)
        except (ValueError, KeyError, IndexError, AttributeError, OSError):
            text = None
        if text:
            out.append((f'define retail TU bss objects ({mode})', text))
            bases.append((mode, text))
    for name, base in bases + [('body', body)]:
        for cast in ('', '(u8 *)'):
            try:
                text, notes = string_run(p, symbol, base, cast)
            except (ValueError, KeyError, IndexError, AttributeError, OSError):
                text = None
            if text:
                out.append((f'reproduce retail string run ({name}{", cast" if cast else ""})', text))
    return out
