"""C signatures and their type dependencies, recovered from headers and matched units."""
from __future__ import annotations

import re
from collections import defaultdict
from dataclasses import dataclass

from .project import ROOT

WORDS = set('void char short int long signed unsigned float double const volatile struct union enum register restrict'.split())
BASIC = WORDS | set('u8 s8 u16 s16 u32 s32 u64 s64 f32 f64 BOOL size_t'.split())


def split_params(text):
    result, start, depth = [], 0, 0
    for i, ch in enumerate(text):
        depth += (ch in '([') - (ch in ')]')
        if ch == ',' and depth == 0:
            result.append(text[start:i].strip()); start = i + 1
    return result + [text[start:].strip()]


def parameter(text, types):
    text = re.sub(r'\b(register|restrict)\s*', '', text).strip()
    if text == '...':
        return text
    if re.search(r'\(\s*\*', text):
        return re.sub(r'(\(\s*\*\s*)\w+(\s*\))', r'\1\2', text)
    array = re.search(r'\[[^]]*\]', text)
    if array:
        text = text[:array.start()].strip() + ' *' + text[array.end():]
    ids = list(re.finditer(r'\b[A-Za-z_]\w*\b', text))
    if ids and ids[-1][0] not in WORDS and ids[-1][0] not in types:
        last = ids[-1]
        if not text[:last.start()].strip():
            return None
        text = text[:last.start()] + text[last.end():]
    text = re.sub(r'\s*\*\s*', ' *', text).strip()
    if not set(re.findall(r'\b[A-Za-z_]\w*\b', text)) <= BASIC | set(types):
        return None
    return text


@dataclass(frozen=True)
class Signature:
    result: str
    args: tuple[str, ...] | None  # None is C's unspecified parameter list, not (void).
    defined: bool = False
    headers: tuple[str, ...] = ()
    types: tuple[str, ...] = ()
    origin: str = ''

    def declaration(self, name):
        params = '' if self.args is None else ', '.join(self.args) or 'void'
        return f'extern {self.result} {name}({params});'


class Index:
    def __init__(self, p):
        # The SDK importer already uses this balanced declaration scanner for MWCC C.
        from .sdkimport import declarations, masked
        from . import tufile
        self.p = p
        self.types = {}
        self.signatures = {}
        self.scoped = {}
        self.conflicts = {}
        self.inferred = {}
        header_pieces = {}
        providers = defaultdict(list)
        for path in sorted((ROOT / 'include').rglob('*.h')):
            rel = path.relative_to(ROOT / 'include').as_posix()
            text = path.read_text()
            pieces = declarations(text)
            header_pieces[rel] = (text, pieces)
            for piece in pieces:
                if piece.kind == 'type':
                    for n in piece.names:
                        providers[n].append((rel, piece.text))
                        if n not in self.types or ('{' not in self.types[n] and '{' in piece.text):
                            self.types[n] = piece.text
        self.providers = providers
        choices = defaultdict(list)

        def collect(text, module, source, own=()):
            pieces = declarations(text)
            includes = set(re.findall(r'#\s*include\s*[<"]([^">]+)', text))
            todo = list(includes)
            while todo:
                h = todo.pop()
                if h in header_pieces:
                    for child in re.findall(r'#\s*include\s*[<"]([^">]+)', header_pieces[h][0]):
                        if child not in includes:
                            includes.add(child); todo.append(child)
            local = {}
            if not source.startswith('include/'):
                for piece in pieces:
                    if piece.kind == 'type':
                        for n in piece.names:
                            local[n] = local.get(n, '') + piece.text + '\n'
            available = dict(self.types); available.update(local)
            for piece in pieces:
                if piece.kind not in ('function', 'prototype'):
                    continue
                sig = piece.signature if piece.kind == 'function' else piece.text.rstrip(';')
                sig = re.sub(r'__declspec\s*\([^)]*\)\s*', '', sig)
                sig = re.sub(r'^(?:(?:extern|static|inline|asm)\s+)+', '', sig)
                match = re.fullmatch(r'([\w\s*]+?)\b(\w+)\s*\((.*)\)\s*', sig, re.S)
                if not match:
                    continue
                result, name, params = match.groups()
                result = parameter(result, available)
                if not result:
                    continue
                args = None if not params.strip() else () if params.strip() == 'void' else tuple(parameter(x, available) for x in split_params(params))
                if args is not None and any(x is None for x in args):
                    continue
                if piece.kind == 'function' and name not in own:
                    continue  # An inlined private helper is not a separately callable definition.
                needed = set(re.findall(r'\b[A-Za-z_]\w*\b', result + ' ' + ' '.join(args or ()))) - BASIC
                headers, copied, visited = set(), [], set()
                def dependency(n):
                    if n in BASIC or n in visited:
                        return
                    visited.add(n)
                    defs = providers.get(n, [])
                    visible = [x for x in defs if x[0] in includes]
                    if n not in local and (visible or defs):
                        headers.add((visible or defs)[0][0]); return
                    if n not in local:
                        return
                    decl = local[n]
                    for dep in re.findall(r'\b[A-Za-z_]\w*\b', masked(decl)):
                        if dep in available and dep != n:
                            dependency(dep)
                    if decl not in copied:
                        copied.append(decl)
                for n in sorted(needed):
                    dependency(n)
                # A private type travels with its defining signature, under a collision-free name.
                rename = {n: f'Sig_{name}_{n}' for n in visited if n in local}
                def rename_all(s):
                    return re.sub(r'\b[A-Za-z_]\w*\b', lambda m: rename.get(m[0], m[0]), s)
                copied = [rename_all(s) for s in copied]
                result = rename_all(result)
                args = tuple(rename_all(s) for s in args) if args is not None else None
                for old, new in rename.items():
                    self.types[new] = rename_all(local[old])
                sym = p.symbols(module).get(name) if module else p.find_symbol(name)
                if sym is None:
                    sym = p.find_symbol(name)
                if sym is None or (sym.kind != 'function' and sym.section not in ('.text', '.init')):
                    continue
                key = p.key(sym)
                defined = piece.kind == 'function'
                rank = 3 if defined else 2 if source.startswith('include/') else 1
                choices[key].append((rank, Signature(result, args, defined, tuple(sorted(headers)), tuple(copied), source)))

        for rel, (text, _) in header_pieces.items():
            module = rel.split('/')[1] if rel.startswith('rel/') else 'main'
            collect(text, module, 'include/' + rel)
        files = defaultdict(list)
        for u in p.load_units():
            if u['status'] == 'matching' and not u.get('asm'):
                files[u.get('tu') or u['source']].append(u)
        for source, units in sorted(files.items()):
            path = ROOT / 'src' / source
            if not path.exists():
                continue
            tf = tufile.parse(path.read_text())
            if tf.blocks:
                for u in units:
                    for n in u['symbols']:
                        b = tf.get(n)
                        if b:
                            collect(('' if 'noprologue' in b.flags else tf.prologue) + b.body, u['module'], source, (n,))
            else:
                collect(tf.prologue, units[0]['module'], source, tuple(n for u in units for n in u['symbols']))
        for key, values in choices.items():
            by_source = defaultdict(list)
            for _, sig in values:
                by_source[sig.origin].append(sig)
            for source, candidates in by_source.items():
                if len({(s.result, s.args) for s in candidates}) == 1:
                    self.scoped[(source, key)] = candidates[0]
            rank = max(x[0] for x in values)
            best = [v for r, v in values if r == rank]
            specified = [s for s in best if s.args is not None]
            best = specified or best
            shapes = {(s.result, s.args) for s in best}
            if len(shapes) == 1:
                self.signatures[key] = best[0]
            else:
                self.conflicts[key] = best

    def get(self, module, name, source=None):
        sym = self.p.symbols(module).get(name) or self.p.find_symbol(name)
        if sym is None:
            match = re.fullmatch(r'(.*)_[0-9A-F]{8}', name)
            sym = self.p.find_symbol(match[1], module) if match else None
        if sym is None:
            return None
        key = self.p.key(sym)
        sig = self.signatures.get(key) or self.scoped.get((source, key))
        constraints = self.inferred.get(key, {})
        entries = getattr(self, 'required', {})
        required = entries.get(key, set())
        if not constraints and key not in entries:
            return sig
        args = sig.args if sig else None
        machine_variadic = key in getattr(self, 'variadic', set())
        weak = sig is None or not sig.defined and not sig.origin.startswith('include/')
        if key in entries and (weak or machine_variadic and not (args and '...' in args)):
            args = None
        slots = self.registers(sig) if sig else None
        if slots is not None and args is not None:
            # Some old matched wrappers omitted arguments passed through untouched.
            # A downstream call's entry liveness supplies those missing ABI slots.
            missing = required - {r for r, _ in slots}
            args = args + tuple('f32' if r.startswith('f') else 'u32'
                                for r in sorted(missing, key=lambda r: (r[0], int(r[1:]))))
        if args is None and key in entries:
            regs = [f'r{k}' for k in range(3, max([int(r[1:]) for r in required if r.startswith('r')], default=2) + 1)]
            regs += [f'f{k}' for k in range(1, max([int(r[1:]) for r in required if r.startswith('f')], default=0) + 1)]
            args = tuple(constraints.get(('arg', r), ('f32' if r.startswith('f') else 'u32', None))[0] for r in regs)
            if machine_variadic:
                args += ('...',)
        result = sig.result if sig else 'u32'
        header = sig is not None and sig.origin.startswith('include/')
        if not header and key in getattr(self, 'float_returns', ()) and ('return', 'f1') in constraints:
            inferred = constraints[('return', 'f1')][0]
            if self.category(inferred) == 'float':
                result = inferred
        elif not header and result == 'void' and key in getattr(self, 'integer_returns', ()):
            result = 'u32'
        rr = 'f1' if self.category(result) == 'float' else 'r3'
        if ('return', rr) in constraints and self.category(result) in ('integer', 'pointer'):
            inferred = constraints[('return', rr)][0]
            if self.category(inferred) == 'pointer':
                result = inferred
        deps = [sig] if sig else []
        slots = self.registers(Signature(result, args))
        if slots is not None:
            args = list(args)
            cursor = 0
            for i, typ in enumerate(args):
                reg = slots[cursor][0]
                cursor += 2 if self.category(typ) == 'wide' else 1
                found = constraints.get(('arg', reg))
                if found and self.category(typ) in ('integer', 'pointer') and self.category(found[0]) == 'pointer':
                    args[i] = found[0]
            args = tuple(args)
        for typ, support in constraints.values():
            if support and typ in (result, *(args or ())) and set(re.findall(r'\b\w+\b', typ)) - BASIC:
                deps.append(support)
        headers = tuple(sorted({h for s in deps for h in s.headers}))
        types = tuple(dict.fromkeys(t for s in deps for t in s.types))
        origin = sig.origin if sig else 'register-flow constraints (unproven C signature)'
        if sig and (result, args) != (sig.result, sig.args):
            origin += '; register-flow constraints'
        return Signature(result, args, sig.defined if sig else False, headers, types, origin)

    def category(self, typ, seen=()):
        if '*' in typ:
            return 'pointer'
        t = re.sub(r'\b(const|volatile|register)\s*', '', typ).strip()
        if t in ('f32', 'f64', 'float', 'double'):
            return 'float'
        if t in ('u64', 's64', 'long long', 'unsigned long long'):
            return 'wide'
        if t == 'void':
            return 'void'
        if t in BASIC:
            return 'integer'
        if t in seen:
            return 'aggregate'
        definition = self.types.get(t, '')
        alias = re.fullmatch(r'typedef\s+(.+?)\s+' + re.escape(t) + r'\s*(\[[^;]+)?;', definition, re.S)
        if alias:
            if alias[2]:
                return 'pointer'
            return self.category(alias[1], seen + (t,))
        if re.search(r'\(\s*\*\s*' + re.escape(t) + r'\)', definition):
            return 'pointer'
        return 'aggregate'

    def registers(self, sig):
        if sig.args is None or '...' in sig.args:
            return None
        gpr, fpr, out = 3, 1, []
        for typ in sig.args:
            category = self.category(typ)
            if category == 'float':
                if fpr > 8:
                    return None
                out.append((f'f{fpr}', typ)); fpr += 1
            elif category in ('integer', 'pointer'):
                if gpr > 10:
                    return None
                out.append((f'r{gpr}', typ)); gpr += 1
            elif category == 'wide':
                gpr += (gpr % 2 == 0)
                if gpr + 1 > 10:
                    return None
                out.extend(((f'r{gpr}', 'u32'), (f'r{gpr + 1}', 'u32')))
                gpr += 2
            else:
                return None
        return out

    def layout(self, pointer):
        """Flat MWCC fields, including grouped declarators and callback pointers."""
        base = re.sub(r'\b(const|volatile)\s*', '', pointer).strip()
        if not base.endswith('*'):
            return None
        base = re.sub(r'^struct\s+', '', base[:-1].strip())
        definition = self.types.get(base, '')
        if '{' not in definition or re.search(r'\bunion\b', definition):
            return None
        body = definition[definition.index('{') + 1:definition.rfind('}')]
        body = re.sub(r'//[^\n]*|/\*.*?\*/', '', body, flags=re.S)
        parts, start, depth = [], 0, 0
        for i, ch in enumerate(body):
            depth += (ch == '{') - (ch == '}')
            if ch == ';' and depth == 0:
                parts.append(body[start:i].strip()); start = i + 1
        cursor, alignment, out = 0, 1, []
        widths = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'short': 2,
                  'u32': 4, 's32': 4, 'int': 4, 'BOOL': 4, 'f32': 4, 'float': 4,
                  'u64': 8, 's64': 8, 'f64': 8, 'double': 8}
        for part in parts:
            callback = re.fullmatch(r'(.+?)\(\s*\*\s*(\w+)\s*\)\s*(\(.*\))', part, re.S)
            anonymous = re.search(r'}\s*\*\s*(\w+)$', part)
            if callback:
                fields = [(callback[2], callback[1].strip() + ' (*)' + callback[3], 1, False)]
            elif anonymous:
                fields = [(anonymous[1], 'void *', 1, False)]
            else:
                fields, common = [], None
                for declarator in split_params(part):
                    if common is None:
                        first = re.fullmatch(r'([\w\s]+?)(\s+\w+(?:\s*\[[^]]+\])?|\s*\*+\s*\w+(?:\s*\[[^]]+\])?)', declarator)
                        if not first:
                            return None
                        common, declarator = first.groups()
                    field = re.fullmatch(r'(\**)(\w+)\s*(\[(0x[0-9a-fA-F]+|\d+)\])?', re.sub(r'\s*\*\s*', '*', declarator).strip())
                    if not field:
                        return None
                    stars, name, array, count = field.groups()
                    fields.append((name, common.strip() + (' ' + stars if stars else ''), int(count, 0) if count else 1, bool(array)))
            for name, typ, count, array in fields:
                width = 4 if self.category(typ) == 'pointer' else widths.get(typ)
                if width is None:
                    return None
                align = min(width, 8)
                alignment = max(alignment, align)
                cursor = (cursor + align - 1) // align * align
                out.append((name, typ, cursor, width, count, array))
                cursor += width * count
        return out, (cursor + alignment - 1) // alignment * alignment

    def member(self, pointer, offset, access):
        layout = self.layout(pointer)
        if layout is None:
            return None
        widths = {'u8': 1, 's8': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4, 'f32': 4, 'f64': 8}
        for name, typ, cursor, width, count, array in layout[0]:
            if (cursor <= offset < cursor + width * count and (offset - cursor) % width == 0
                    and width == widths.get(access)
                    and (self.category(typ) == "float") == (self.category(access) == "float")):
                # A word copy of a color array must remain a word access, not one byte.
                suffix = f'[{(offset - cursor) // width}]' if array else ''
                return name + suffix, typ
        return None

    def preamble(self, signatures):
        headers, types = set(), []
        for sig in signatures:
            headers.update(sig.headers)
            for text in sig.types:
                if text not in types:
                    types.append(text)
        return [f'#include "{h}"' for h in sorted(headers)] + types


_CACHE = {}


def recovered(p):
    # Invalidate after a submitted source or recovered header changes, including in long-lived MCP sessions.
    paths = sorted((ROOT / 'include').rglob('*.h')) + sorted((ROOT / 'src').rglob('*.c')) + [p.units_path]
    stamp = tuple((str(f), f.stat().st_mtime_ns, f.stat().st_size) for f in paths)
    key = (p.version, stamp)
    if key not in _CACHE:
        _CACHE.clear()
        _CACHE[key] = Index(p)
    return _CACHE[key]


def propagate(index, module, names):
    """Unify register origins across direct calls, retaining only constraints valid at CFG joins."""
    from collections import deque
    from copy import copy
    p = index.p
    cache_key = (module, tuple(names))
    flows = index.__dict__.setdefault('_flows', {})
    if cache_key in flows:
        return flows[cache_key]
    # Caller constraints belong to this TU; visiting another TU must not change its result.
    index = copy(index)
    index.inferred = {}
    index.required = {}
    index.conflicts = dict(index.conflicts)
    functions = {}
    for name in names:
        fn = p.function_asm(module).get(name)
        if fn:
            functions[p.key(fn.symbol)] = fn
    # Function.refs omits resolved cross-module branches; read call targets from instructions.
    frontier = list(functions.values())
    while frontier:
        next_frontier = []
        for fn in frontier:
            for line in fn.asm:
                call = re.match(r'^[0-9A-Fa-f]+:\s*bl\s+(\w+)$', line.strip())
                if call and re.fullmatch(r'_(save|rest)(gpr|fpr)_\d+', call[1]):
                    continue
                sym = (p.symbols(fn.symbol.module).get(call[1]) or p.find_symbol(call[1])) if call else None
                if sym and p.key(sym) not in functions:
                    other = p.callable_asm(sym)
                    if other:
                        functions[p.key(sym)] = other; next_frontier.append(other)
        frontier = next_frontier
    parent, seeds, support = {}, defaultdict(set), {}
    def root(x):
        parent.setdefault(x, x)
        if parent[x] != x:
            parent[x] = root(parent[x])
        return parent[x]
    def join(a, b):
        ra, rb = root(a), root(b)
        if ra != rb:
            parent[rb] = ra
    def seed(node, typ, sig=None):
        seeds[node].add(typ)
        if sig:
            support[typ] = sig
    parsed, required, variadic, vararg_saves = {}, {}, set(), {}
    index.float_returns = set()
    index.integer_returns = set()
    volatile = {f'r{k}' for k in range(13)} | {f'f{k}' for k in range(14)}
    argument_regs = {f'r{k}' for k in range(3, 11)} | {f'f{k}' for k in range(1, 9)}
    for key, fn in functions.items():
        ins, labels, addresses = [], {}, {}
        for line in fn.asm:
            if line.strip().startswith('.L_') and line.strip().endswith(':'):
                labels[line.strip()[:-1]] = len(ins)
            m = re.match(r'^[0-9A-Fa-f]+:\s*(\S+)\s*(.*)', line.strip())
            if m:
                addresses[int(line.split(':')[0], 16)] = len(ins)
                ins.append((m[1].rstrip('+-'), [x.strip() for x in m[2].split(',')] if m[2] else []))
        switch_targets = []
        if any(mn == 'bctr' for mn, _ in ins):
            from .machine import assembly
            switch_targets = sorted({addresses[int(address, 16)] for address in
                                     re.findall(r'(?m)^\.4byte \.L_([0-9A-Fa-f]+)$', assembly(p, fn))
                                     if int(address, 16) in addresses})
        def successors(i):
            mn, a = ins[i]
            if mn == 'bctr':
                return switch_targets
            if mn == 'blr':
                return []
            nxt = [i + 1] if i + 1 < len(ins) else []
            if mn.startswith('b') and mn not in ('bl', 'bctrl', 'blrl'):
                dest = labels.get(a[-1]) if a else None
                if mn == 'b':
                    return [dest] if dest is not None and dest < len(ins) else []
                if dest is not None and dest < len(ins):
                    nxt.append(dest)
            return nxt
        edges = [successors(i) for i in range(len(ins))]
        parsed[key] = (fn, ins, edges)
        # The CR1-guarded f1-f8 save and contiguous r3-r10 area identify the
        # CodeWarrior varargs prologue. These stores are not fixed parameters.
        save_sites = {i for i, (mn, a) in enumerate(ins[:100]) if mn in ('stw', 'stfd')
                      and len(a) == 2 and re.fullmatch(r'(?:0x[0-9a-f]+|\d+)\(r1\)', a[1])
                      and a[0] in argument_regs}
        saved = {ins[i][1][0] for i in save_sites}
        if argument_regs <= saved and any(mn == 'bne' and a[0] == 'cr1' for mn, a in ins[:100] if a):
            variadic.add(key)
            vararg_saves[key] = save_sites
        sig = index.get(fn.symbol.module, fn.symbol.name)
        if sig and sig.args and '...' in sig.args:
            variadic.add(key)
            sig = Signature(sig.result, sig.args[:sig.args.index('...')], sig.defined, sig.headers, sig.types, sig.origin)
        slots = index.registers(sig) if sig else None
        strong = sig and (sig.defined or sig.origin.startswith('include/'))
        required[key] = {r for r, _ in slots} if slots is not None and strong and key not in vararg_saves else set()
        if slots is not None and strong:
            for r, typ in slots:
                seed((key, 'arg', r), typ, sig)
        if strong and index.category(sig.result) not in ('void', 'wide'):
            seed((key, 'return', 'f1' if index.category(sig.result) == 'float' else 'r3'), sig.result, sig)
    def rw(key, i):
        fn, ins, _ = parsed[key]; mn, a = ins[i]
        if i in vararg_saves.get(key, ()):
            return {'r1'}, set()
        regs = set(re.findall(r'\b[rf]\d+\b', ','.join(a)))
        if mn in ('bl', 'bctrl', 'blrl'):
            if mn == 'bl' and a and re.fullmatch(r'_(save|rest)(gpr|fpr)_\d+', a[0]):
                return set(), set()
            callee = p.symbols(fn.symbol.module).get(a[0]) or p.find_symbol(a[0]) if a else None
            if not callee:
                return set(), volatile
            slots = index.registers(index.get(callee.module, callee.name)) if index.get(callee.module, callee.name) else None
            return required.get(p.key(callee), {r for r, _ in slots} if slots is not None else set()), volatile
        if mn.startswith(('st', 'cmp', 'fcmp', 'b', 'mt', 'cr')):
            return regs, set()
        dest = {a[0]} if a and re.fullmatch(r'[rf]\d+', a[0]) else set()
        if mn.rstrip('.') in ('xor', 'subf') and len(a) == 3 and a[1] == a[2]:
            # Zeroing idioms do not consume the incoming value. Counting xor r3,r3,r3
            # as an input invents a parameter and propagates it through every caller.
            return set(), dest
        # Read-modify-write instructions retain their input when it aliases the destination.
        read = set(re.findall(r'\b[rf]\d+\b', ','.join(a[1:])))
        return read, dest
    # Entry liveness gives a callee's required registers without guessing from caller temporaries.
    for _ in range(len(parsed) + 1):
        changed = False
        for key, (_, ins, edges) in parsed.items():
            live = [set() for _ in ins]
            again = True
            while again:
                again = False
                for i in reversed(range(len(ins))):
                    reads, writes = rw(key, i)
                    value = reads | (set().union(*(live[j] for j in edges[i])) - writes)
                    if value != live[i]:
                        live[i] = value; again = True
            entry = live[0] & argument_regs if live else set()
            if not entry <= required[key]:
                required[key] |= entry; changed = True
        if not changed:
            break
    index.required = {**getattr(index, 'required', {}), **required}
    index.variadic = variadic
    for key, (fn, ins, edges) in parsed.items():
        if not ins:
            continue
        states = [None] * len(ins)
        states[0] = {r: (key, 'arg', r) for r in argument_regs}
        queue = deque([0])
        def transfer(i, state, record=False):
            mn, a = ins[i]; out = dict(state)
            reads, writes = rw(key, i)
            if mn == 'bl' and a and re.fullmatch(r'_(save|rest)(gpr|fpr)_\d+', a[0]):
                # MWCC's frame helpers preserve argument and return registers;
                # treating them as C calls erases parameters before the first statement.
                return out
            if record:
                for reg in reads:
                    if state.get(reg) and state[reg][1:] == ('return', 'r3'):
                        index.integer_returns.add(state[reg][0])
                for reg in reads:
                    if reg.startswith('f') and state.get(reg) and i not in vararg_saves.get(key, ()):
                        seed(state[reg], 'f32')
                        if state[reg][1:] == ('return', 'f1'):
                            index.float_returns.add(state[reg][0])
                for operand in a[1:] if mn.startswith(('l', 'st')) else []:
                    mem = re.search(r'\((r\d+)\)', operand)
                    if mem and mem[1] != 'r1' and state.get(mem[1]):
                        seed(state[mem[1]], 'void *')
            if mn in ('bl', 'bctrl', 'blrl'):
                sym = (p.symbols(fn.symbol.module).get(a[0]) or p.find_symbol(a[0])) if mn == 'bl' else None
                callee = p.key(sym) if sym else None
                if record and callee:
                    for r in required.get(callee, ()):
                        if state.get(r):
                            join(state[r], (callee, 'arg', r))
                for r in volatile:
                    out.pop(r, None)
                if callee:
                    out['r3'] = (callee, 'return', 'r3')
                    out['f1'] = (callee, 'return', 'f1')
            elif mn in ('mr', 'mr.', 'fmr', 'fneg', 'fabs', 'fnabs') and len(a) == 2:
                out[a[0]] = state.get(a[1])
            else:
                for r in writes:
                    out.pop(r, None)
                if a and a[0].startswith('f') and (mn.startswith(('lfs', 'lfd'))
                        or mn.startswith('f') and mn not in ('fctiw', 'fctiwz')):
                    node = (key, 'value', str(i))
                    out[a[0]] = node
                    if record:
                        seed(node, 'f32' if mn.startswith('lfs') or mn.rstrip('.').endswith('s') or mn == 'frsp' else 'f64')
            if record and (mn == 'blr' or mn.endswith('lr') and mn.startswith('b')):
                sig = index.get(fn.symbol.module, fn.symbol.name)
                if sig and index.category(sig.result) != 'void':
                    r = 'f1' if index.category(sig.result) == 'float' else 'r3'
                    if state.get(r):
                        join(state[r], (key, 'return', r))
                if (not sig or not sig.origin.startswith('include/')) and state.get('f1'):
                    origin = state['f1']
                    if origin != (key, 'arg', 'f1'):
                        join(origin, (key, 'return', 'f1'))
            return {r: origin for r, origin in out.items() if origin is not None}
        while queue:
            i = queue.popleft(); out = transfer(i, states[i])
            for j in edges[i]:
                merged = out if states[j] is None else {r: origin for r, origin in states[j].items() if out.get(r) == origin}
                if merged != states[j]:
                    states[j] = dict(merged); queue.append(j)
        for i, state in enumerate(states):
            if state is not None:
                transfer(i, state, True)
    groups = defaultdict(set)
    for node, types in seeds.items():
        groups[root(node)].update(types)
    for node in parent.keys() | seeds.keys():
        types = set(groups[root(node)])
        pointers = {t for t in types if index.category(t) == 'pointer'}
        if types and all(index.category(t) == 'float' for t in types):
            types = {'f64' if types & {'f64', 'double'} else 'f32'}
        if pointers:
            # Register-sized integer definitions cannot distinguish a pointer from its bit pattern.
            types = pointers - {'void *'} or pointers
        if len(types) == 1:
            typ = next(iter(types))
            key, kind, reg = node
            index.inferred.setdefault(key, {})[(kind, reg)] = (typ, support.get(typ))
        elif types:
            index.conflicts.setdefault(node, tuple(sorted(types)))
    flows[cache_key] = index
    return index
