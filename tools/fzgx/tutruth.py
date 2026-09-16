"""One truth per symbol for a TU file.

A block matched under whatever declarations it wrote; blocks disagree, and a single-TU
compile rejects the second spelling of any symbol. The truth of a function is its matched
definition (its own code proves the parameter types), else a header, else the prologue, else
the most common spelling. A block that declared other parameter types keeps its code by
casting each argument to the type it relied on (`fn((u8)x, y, (u8)z)`): the conversion the
old prototype implied is now explicit. Every rewritten block is re-verified under the new
prologue; a block that no longer matches is reverted and reported.
"""
from __future__ import annotations

import re
from collections import Counter, OrderedDict
from typing import Dict, List, Optional, Tuple

from . import oracle, reconcile, tufile, tutidy
from .project import ROOT, Project

SCALAR = {'void', 'int', 'char', 'short', 'long', 'unsigned', 'signed', 'float', 'double',
          's8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 'f32', 'f64', 'BOOL', 'size_t'}
PROTO_RE = re.compile(r'^\s*(?:extern\s+)?(.*?)\b([A-Za-z_]\w*)\s*\(([^()]*)\)\s*(?:,|;)')


def _sig(decl: str) -> Optional[Tuple[str, str, List[str]]]:
    """(return type, name, [parameter types]) of a prototype line, or None for data."""
    m = PROTO_RE.match(decl.strip())
    if not m:
        return None
    ret = re.sub(r'\s+', ' ', m.group(1)).strip()
    params = []
    inner = m.group(3).strip()
    if inner and inner != 'void':
        for part in inner.split(','):
            part = part.strip()
            if part == '...':
                params.append('...')
                continue
            # drop the parameter name: the last identifier not followed by '*' or a type word
            t = re.sub(r'\b([A-Za-z_]\w*)\s*$', lambda mm: '' if mm.group(1) not in SCALAR else mm.group(1), part).strip()
            params.append(re.sub(r'\s+', ' ', t))
    return ret, m.group(2), params


def _same(a: str, b: str) -> bool:
    n = lambda s: re.sub(r'\s+', '', s).replace('int', 's32').replace('const', '')
    return n(a) == n(b)


def project_definition(p: Project, name: str) -> Optional[str]:
    """`extern <signature>;` of the project's matched definition of `name`, if any."""
    pat = re.compile(r'^((?:[A-Za-z_][\w\s\*]*?)\b' + re.escape(name) + r'\s*\(([^;{}()]*)\))\s*\{', re.M)
    for f in sorted((ROOT / 'src').rglob('*.c')):
        text = f.read_text()
        if name not in text:
            continue
        m = pat.search(text)
        if m:
            return 'extern ' + re.sub(r'\s+', ' ', m.group(1)).strip() + ';'
    return None


def split_args(text: str, start: int) -> Optional[Tuple[List[Tuple[int, int]], int]]:
    """Top-level argument spans of the call whose '(' is at `start`; returns (spans, end)."""
    depth = 0
    spans = []
    a = start + 1
    i = start
    while i < len(text):
        c = text[i]
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1
            if depth == 0:
                if text[a:i].strip():
                    spans.append((a, i))
                return spans, i
        elif c == ',' and depth == 1:
            spans.append((a, i))
            a = i + 1
        elif c == '"':
            i += 1
            while i < len(text) and text[i] != '"':
                i += 2 if text[i] == '\\' else 1
        i += 1
    return None


INTS = {'s8', 'u8', 's16', 'u16', 's32', 'u32', 'int', 'char', 'short', 'long', 'unsigned', 'signed', 'BOOL', 'size_t'}


def cast_calls(body: str, name: str, old: List[str], new: List[str], force: bool = False) -> str:
    """Wrap every argument whose old declared type differs from the truth's in a cast to the
    old type, so the conversion the block's prototype implied stays in the code."""
    out = body
    for m in reversed(list(re.finditer(r'\b' + re.escape(name) + r'\s*\(', body))):
        line_start = body.rfind('\n', 0, m.start()) + 1
        line_end = body.find('\n', m.start())
        if tutidy.DECL_LINE_RE.match(body[line_start:line_end if line_end >= 0 else len(body)]):
            continue  # a declaration, not a call
        res = split_args(body, m.end() - 1)
        if not res:
            continue
        spans, end = res
        if body[end + 1:].lstrip().startswith('{'):
            continue  # the definition
        if len(spans) != len(old) or len(old) != len(new):
            continue
        text = out
        for (a, b), t_old, t_new in reversed(list(zip(spans, old, new))):
            if t_old == '...' or t_new == '...' or _same(t_old, t_new):
                continue
            if not force and t_old.split()[-1] in INTS and t_new.split()[-1] in INTS:
                continue  # integer widening/sign at the call is the parameter's own conversion
            arg = text[a:b].strip()
            castable = '*' in t_old or t_old.split()[-1] in SCALAR
            if not castable:
                if t_new.split()[-1] in SCALAR and '*' not in t_new:
                    text = text[:a] + f' ({t_new})({arg})' + text[b:]
                continue
            if re.fullmatch(r'\(\s*' + re.escape(t_old) + r'\s*\)\s*.*', arg):
                if '*' in t_new or (t_new.split()[-1] in SCALAR and '*' in t_old):
                    text = text[:a] + f' ({t_new})({arg})' + text[b:]  # already cast to the old type
                continue
            if '*' in t_new or (t_new.split()[-1] in SCALAR and '*' in t_old):
                text = text[:a] + f' ({t_new})({t_old})({arg})' + text[b:]  # the truth's type outermost
            else:
                text = text[:a] + f' ({t_old})({arg})' + text[b:]
        out = text
    return out


def join_declarations(body: str) -> str:
    """A declaration continued over several lines becomes one line."""
    out = []
    buf = None
    for ln in body.splitlines():
        if buf is not None:
            buf += ' ' + ln.strip()
            if ln.rstrip().endswith(';'):
                out.append(buf)
                buf = None
            continue
        if re.match(r'^\s*(?:extern\s+)?[A-Za-z_][\w \*]*\b[A-Za-z_]\w*\s*\([^;{}]*,\s*$', ln) or (re.match(r'^\s*extern\b[^;{}]*$', ln) and not ln.rstrip().endswith(';')):
            buf = ln.rstrip()
            continue
        out.append(ln)
    if buf is not None:
        out.append(buf)
    return '\n'.join(out) + ('\n' if body.endswith('\n') else '')


def split_multi(body: str) -> str:
    """`extern void a(...), b(...);` becomes one declaration line per prototype."""
    out = []
    for ln in body.splitlines():
        m = re.match(r'^(\s*(?:extern\s+)?[A-Za-z_][^(;=]*?)\b([A-Za-z_]\w*)\s*\(([^()]*)\)\s*,\s*(.*);\s*$', ln)
        if m and re.search(r'\b[A-Za-z_]\w*\s*\([^()]*\)', m.group(4)):
            head = m.group(1)
            protos = re.findall(r'(\**\s*[A-Za-z_]\w*\s*\([^()]*\))', m.group(2) + '(' + m.group(3) + '), ' + m.group(4))
            for pr in protos:
                out.append(f'{head.rstrip()} {pr.strip()};')
            continue
        out.append(ln)
    return '\n'.join(out) + ('\n' if body.endswith('\n') else '')


def type_definition_span(body: str, tname: str) -> Optional[Tuple[int, int]]:
    """Span of `typedef struct [tag] { ... } tname;` or `struct tname { ... };` in a block."""
    for m in re.finditer(r'^(?:typedef\s+)?(?:struct|union|enum)\s*(?:[A-Za-z_]\w*\s*)?\{', body, re.M):
        depth = 0
        i = m.end() - 1
        while i < len(body):
            if body[i] == '{':
                depth += 1
            elif body[i] == '}':
                depth -= 1
                if depth == 0:
                    tail = re.match(r'\s*([A-Za-z_]\w*)?\s*;', body[i + 1:])
                    if not tail:
                        break
                    end = i + 1 + tail.end()
                    head = body[m.start():m.end()]
                    name = tail.group(1) if m.group(0).startswith('typedef') else re.search(r'(?:struct|union|enum)\s*([A-Za-z_]\w*)', head)
                    name = name if isinstance(name, str) or name is None else name.group(1)
                    if name == tname:
                        return m.start(), end + (1 if body[end:end + 1] == '\n' else 0)
                    break
            i += 1
    return None


def hoist_private_types(tf: tufile.TuFile, truths: Dict[str, str], report: Dict[str, object]) -> None:
    """Move the definitions of block-private types that a truth names into the prologue,
    when exactly one block defines the type (reconcile prefixed the colliding ones)."""
    private: Dict[str, List[str]] = {}
    for b in tf.blocks:
        for t in set(re.findall(r'^\}\s*([A-Za-z_]\w*)\s*;', b.body, re.M)) | set(re.findall(r'^typedef\s+struct\s+([A-Za-z_]\w*)\s*\{', b.body, re.M)) | set(re.findall(r'^struct\s+([A-Za-z_]\w*)\s*\{', b.body, re.M)):
            private.setdefault(t, []).append(b.name)
    hoisted = []
    pending = [t for truth in truths.values() for t in re.findall(r'[A-Za-z_]\w*', truth) if t in private]
    seen = set()
    while pending:
        t = pending.pop(0)
        if t in seen:
            continue
        seen.add(t)
        owners = private[t]
        if len(set(owners)) != 1:
            report.setdefault('unhoistable', []).append(f'{t}: defined in {sorted(set(owners))}')
            continue
        b = tf.get(owners[0])
        span = type_definition_span(b.body, t)
        if not span:
            report.setdefault('unhoistable', []).append(f'{t}: no definition span in {b.name}')
            continue
        text = b.body[span[0]:span[1]]
        # a type the hoisted definition names must come first
        for inner in re.findall(r'[A-Za-z_]\w*', text):
            if inner in private and inner != t and inner not in seen:
                pending.insert(0, inner)
        b.body = b.body[:span[0]] + b.body[span[1]:]
        tf.prologue = tf.prologue.rstrip('\n') + '\n\n' + text.rstrip('\n') + '\n'
        hoisted.append((t, b.name))
    report['hoisted_types'] = hoisted


def cast_results(body: str, name: str, old_ret: str) -> str:
    """`x = f(...)` under a truth with another return type: cast the call to the old type."""
    out = body
    for m in reversed(list(re.finditer(r'\b' + re.escape(name) + r'\s*\(', body))):
        line_start = body.rfind('\n', 0, m.start()) + 1
        line_end = body.find('\n', m.start())
        if tutidy.DECL_LINE_RE.match(body[line_start:line_end if line_end >= 0 else len(body)]):
            continue
        res = split_args(body, m.end() - 1)
        if not res or body[res[1] + 1:].lstrip().startswith('{'):
            continue
        before = body[line_start:m.start()]
        if not re.search(r'(=|return|\(|,|\?|:)\s*$', before):
            continue
        out = out[:m.start()] + f'({old_ret})' + out[m.start():res[1] + 1] + out[res[1] + 1:]
    return out


def min_call_args(body: str, name: str) -> Optional[int]:
    """Fewest arguments any call of `name` in the body passes (None: no call)."""
    least = None
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', body):
        line_start = body.rfind('\n', 0, m.start()) + 1
        line_end = body.find('\n', m.start())
        if tutidy.DECL_LINE_RE.match(body[line_start:line_end if line_end >= 0 else len(body)]):
            continue
        res = split_args(body, m.end() - 1)
        if not res or body[res[1] + 1:].lstrip().startswith('{'):
            continue
        least = len(res[0]) if least is None else min(least, len(res[0]))
    return least


def view_rewrite(body: str, name: str, decl: str, truth_is_pointer: bool = False) -> Optional[str]:
    """Every use of a data symbol goes through the block's own view of the object:
    `extern T n;` -> `(*(T *)&n)`, `extern T n[..];` -> `((T *)&n)`, `extern T *n;` -> `(*(T **)&n)`.
    The address is the same symbol; the code is unchanged."""
    m = re.match(r'^\s*extern\s+(.*?)\s*\b' + re.escape(name) + r'\s*((?:\[[^\]]*\])*)\s*;', decl.strip())
    if not m:
        return None
    t = re.sub(r'\s+', ' ', m.group(1)).strip()
    if m.group(2):
        view = f'((({t} *)&{name}))'
    elif t.endswith('*') and truth_is_pointer:
        view = f'(({t}){name})'  # the loaded pointer, cast: no address materialisation
    else:
        view = f'(*(({t} *)&{name}))'
    ident = re.compile(r'(?<![\w.>])' + re.escape(name) + r'\b')
    out_lines = []
    for ln in body.splitlines():
        if tutidy.DECL_LINE_RE.match(ln) and tutidy._decl_name(ln) == name:
            continue
        out_lines.append(ident.sub(view, ln))
    return '\n'.join(out_lines) + ('\n' if body.endswith('\n') else '')


def adapt(body: str, n: str, old_decl: Optional[str], truth: str, report_bad: List[str], force: bool = False) -> Optional[str]:
    """The block's body under `truth` for symbol n, given the declaration it was written
    against (`old_decl`: its private line, or the old prologue line, or None). Returns None
    when no mechanical adaptation exists (a data view whose declaration cannot be parsed)."""
    lines = [x for x in body.splitlines() if not (tutidy.DECL_LINE_RE.match(x) and tutidy._decl_name(x) == n)]
    body = '\n'.join(lines) + ('\n' if body.endswith('\n') else '')
    if old_decl is None or old_decl.strip() == truth.strip():
        return body
    sv, st = _sig(old_decl), _sig(truth)
    if sv and st:
        if st[2] and st[2][-1] == '...':
            return body
        if len(sv[2]) == len(st[2]):
            if sv[2] != st[2] and '...' not in sv[2]:
                permuted = permute_args(body, n, sv[2], st[2])
                body = permuted if permuted is not None else cast_calls(body, n, sv[2], st[2], force)
        elif len(sv[2]) > len(st[2]) and all(_same(a, b) for a, b in zip(sv[2][len(sv[2]) - len(st[2]):], st[2])):
            body = drop_leading_args(body, n, len(sv[2]) - len(st[2]))
        if sv[0] != st[0] and not _same(sv[0], st[0]) and re.sub(r'\s', '', sv[0]) != 'void':
            if re.sub(r'\s', '', st[0]) == 'void' and re.search(r'=\s*' + re.escape(n) + r'\s*\(', body):
                return None
            body = cast_results(body, n, sv[0])
        return body
    if not sv and not st:
        truth_ptr = bool(re.match(r'^\s*extern\s+.*\*\s*' + re.escape(n) + r'\s*;', truth))
        return view_rewrite(body, n, old_decl, truth_is_pointer=truth_ptr)
    return None


def _reg_class(t: str) -> str:
    return 'F' if re.sub(r'\bconst\b', '', t).strip() in ('f32', 'f64', 'float', 'double') else 'G'


def permute_args(body: str, name: str, old: List[str], new: List[str]) -> Optional[str]:
    """Two prototypes that place the same values in the same registers in another order
    (`(u8, f32, f32)` against `(f32, f32, s32)`): reorder the call's arguments so each
    register still receives what it did. Returns None when the classes do not permute."""
    oc, nc = [_reg_class(t) for t in old], [_reg_class(t) for t in new]
    if sorted(oc) != sorted(nc) or oc == nc:
        return None
    order = []
    used = set()
    for c in nc:
        j = next((j for j, c2 in enumerate(oc) if c2 == c and j not in used), None)
        if j is None:
            return None
        used.add(j)
        order.append(j)
    out = body
    for m in reversed(list(re.finditer(r'\b' + re.escape(name) + r'\s*\(', body))):
        line_start = body.rfind('\n', 0, m.start()) + 1
        line_end = body.find('\n', m.start())
        if tutidy.DECL_LINE_RE.match(body[line_start:line_end if line_end >= 0 else len(body)]):
            continue
        res = split_args(body, m.end() - 1)
        if not res or body[res[1] + 1:].lstrip().startswith('{') or len(res[0]) != len(old):
            continue
        args = [body[a:b].strip() for a, b in res[0]]
        new_args = [f'({new[i]})({args[order[i]]})' if not _same(old[order[i]], new[i]) else args[order[i]] for i in range(len(new))]
        out = out[:res[0][0][0]] + ', '.join(new_args) + out[res[0][-1][1]:]
    return out


def drop_leading_args(body: str, name: str, k: int) -> str:
    """Calls that passed k more leading arguments than the truth declares."""
    out = body
    for m in reversed(list(re.finditer(r'\b' + re.escape(name) + r'\s*\(', body))):
        line_start = body.rfind('\n', 0, m.start()) + 1
        line_end = body.find('\n', m.start())
        if tutidy.DECL_LINE_RE.match(body[line_start:line_end if line_end >= 0 else len(body)]):
            continue
        res = split_args(body, m.end() - 1)
        if not res or body[res[1] + 1:].lstrip().startswith('{') or len(res[0]) <= k:
            continue
        spans = res[0]
        out = out[:spans[0][0]] + out[spans[k][0]:]
    return out


def resolve(p: Project, tu_source: str, v, apply: bool = True) -> Dict[str, object]:
    module = tu_source.split('/')[1] if tu_source.startswith('rel/') else 'main'
    units = {u['symbols'][0]: u for u in p.load_units() if u.get('tu') == tu_source}
    tf = tufile.load(p, tu_source)
    report: Dict[str, object] = {'tu': tu_source, 'truth': {}, 'rewritten': [], 'reverted': [], 'unresolved': {}}
    tf.prologue = split_multi(join_declarations(tf.prologue))
    for b in tf.blocks:
        b.body = split_multi(join_declarations(b.body))
        b.flags = [x for x in b.flags if x != 'noprologue']  # every block under the one prologue
    # one include set for the TU: headers a block includes join the prologue
    block_includes = []
    own_includes: Dict[str, List[str]] = {}
    for b in tf.blocks:
        inc, rest = tufile.split_includes(b.body)
        own_includes[b.name] = [ln.strip() for ln in inc if ln.strip()]
        for ln in inc:
            if ln.strip() and ln.strip() not in {x.strip() for x in tf.prologue.splitlines()} and ln.strip() not in block_includes:
                block_includes.append(ln.strip())
        b.body = rest.lstrip('\n')
    if block_includes:
        tf.prologue = tufile.merge_prologue(tf.prologue, block_includes)
        report['promoted_includes'] = block_includes
    header_names, header_typedefs = tutidy._header_names(p, tf.prologue)
    hdecl: Dict[str, str] = {}
    for ln in tf.prologue.splitlines():
        m = re.search(r'#include\s+"([^"]+)"', ln)
        if m and (ROOT / 'include' / m.group(1)).exists():
            for hl in (ROOT / 'include' / m.group(1)).read_text().splitlines():
                if tutidy.DECL_LINE_RE.match(hl):
                    n = tutidy._decl_name(hl)
                    if n:
                        hdecl.setdefault(n, hl.strip())
    # block typedefs that collide with a header typedef get the block's prefix
    for b in tf.blocks:
        for t in set(re.findall(r'^\}\s*([A-Za-z_]\w*)\s*;', b.body, re.M)) & set(header_typedefs):
            b.body = re.sub(r'\b' + re.escape(t) + r'\b', f'{b.name}_{t}', b.body)
            report.setdefault('renamed_typedefs', []).append((b.name, t))
    pdecl: Dict[str, str] = {}
    kept_pro = []
    for ln in tf.prologue.splitlines():
        if tutidy.DECL_LINE_RE.match(ln):
            n = tutidy._decl_name(ln)
            if n:
                pdecl[n] = ln.strip()
                continue  # every prologue declaration is re-decided below
        kept_pro.append(ln)
    base_prologue = '\n'.join(kept_pro).rstrip('\n') + '\n'
    definitions: Dict[str, str] = {}
    for b in tf.blocks:
        for m in reconcile.DEF_RE.finditer(b.body):
            definitions[m.group(2)] = 'extern ' + re.sub(r'\s+', ' ', m.group(1)).strip() + ';'
    variants: Dict[str, Counter] = OrderedDict()
    where: Dict[str, Dict[str, str]] = {}
    for b in tf.blocks:
        for n, ln in reconcile._decls(b.body):
            variants.setdefault(n, Counter())[ln] += 1
            where.setdefault(n, {})[b.name] = ln
    symbols = list(dict.fromkeys(list(variants) + list(pdecl)))
    private_types = set()
    for b in tf.blocks:
        private_types |= set(re.findall(r'^\}\s*([A-Za-z_]\w*)\s*;', b.body, re.M)) | set(re.findall(r'^(?:typedef\s+)?struct\s+([A-Za-z_]\w*)\s*\{', b.body, re.M))
    known_types = SCALAR | set(header_typedefs) | private_types | {'struct', 'union', 'enum', 'extern', 'const', 'volatile', 'static', 'inline', 'unsigned', 'signed'}

    def admissible(decl: str) -> bool:
        sig = _sig(decl)
        words = set(re.findall(r'[A-Za-z_]\w*', sig[0] + ' ' + ' '.join(sig[2]))) if sig else set(re.findall(r'[A-Za-z_]\w*', decl.split('=')[0]))
        if not sig:
            words -= {tutidy._decl_name(decl)}
        return all(w in known_types or w == '...' for w in words)

    candidates: Dict[str, List[Tuple[str, str]]] = {}
    for n in symbols:
        c: List[Tuple[str, str]] = []
        if n in hdecl:
            c.append(('header', hdecl[n]))
        d = definitions.get(n) or project_definition(p, n)
        if d:
            c.append(('definition', d))
        if n in pdecl:
            c.append(('prologue', pdecl[n]))
        for t, _ in sorted(variants.get(n, {}).items(), key=lambda kv: (-kv[1], len(kv[0]))):
            c.append(('variant', t))
        seen = set()
        c = [(src, t) for src, t in c if not (t.strip() in seen or seen.add(t.strip())) and admissible(t)] or c[:1]
        # a definition's parameter order across register classes is unconstrained by its own
        # code; a caller's spelling that permutes it by class carries the evaluation-order
        # evidence (fn_1_563E4: retail loads the s32 colour before the two floats)
        d_ = next((t for src, t in c if src == 'definition'), None)
        if d_ and _sig(d_):
            dc = [_reg_class(t) for t in _sig(d_)[2]]
            if len(set(dc)) > 1:
                perms = [(src, t) for src, t in c if src == 'variant' and _sig(t) and len(_sig(t)[2]) == len(dc)
                         and sorted(_reg_class(x) for x in _sig(t)[2]) == sorted(dc) and [_reg_class(x) for x in _sig(t)[2]] != dc]
                if perms:
                    c = perms + [x for x in c if x not in perms]
                    report.setdefault('definition_order_from_callers', []).append((n, perms[0][1]))
        # a definition whose return type is register-identical to the callers' (u32 against
        # void *): the callers' type, with the definition retyped to it (fn_1_548AC)
        if d_ and _sig(d_) and n in definitions:
            dr = _sig(d_)

            def gpr_equivalent(a: str, b: str) -> bool:
                # identical, or an integer against a pointer (never two different pointer types:
                # a definer's field accesses need its own struct pointer)
                if _same(a, b):
                    return True
                ia, ib = a.split()[-1] in INTS and '*' not in a, b.split()[-1] in INTS and '*' not in b
                return ia != ib and ('*' in a or '*' in b) and a != '...' and b != '...'

            for src, t in list(c):
                vs_ = _sig(t)
                if src == 'variant' and vs_ and len(vs_[2]) == len(dr[2]) and t.strip() != d_.strip() \
                        and all(gpr_equivalent(a, b) for a, b in zip(vs_[2], dr[2])) and gpr_equivalent(vs_[0], dr[0]):
                    retyped = f'extern {vs_[0]} {n}({", ".join(vs_[2]) or "void"});'
                    c.insert(0, ('definition-retyped', retyped))
                    break
        if n in definitions:
            # the definer must agree with the prologue: only its own signature or a retyping of it
            c = [(src, t) for src, t in c if src in ('definition', 'definition-retyped')] or c[:1]
        candidates[n] = c
    # users of a symbol: blocks that declared it privately, called it, or defined it
    users: Dict[str, List[str]] = {}
    for n in symbols:
        pat = re.compile(r'\b' + re.escape(n) + r'\b')
        users[n] = [b.name for b in tf.blocks if b.name in where.get(n, {}) or pat.search(b.body)]
    original = {b.name: b.body for b in tf.blocks}
    choice: Dict[str, int] = {n: 0 for n in symbols}

    def old_decl_for(bname: str, n: str) -> Optional[str]:
        return where.get(n, {}).get(bname) or pdecl.get(n)

    forced: set = set()

    def derive(bname: str) -> Optional[str]:
        body = original[bname]
        for n in symbols:
            if bname not in users[n]:
                continue
            truth = candidates[n][choice[n]][1]
            if n in definitions and bname == next((b.name for b in tf.blocks if re.search(r'\b' + re.escape(n) + r'\s*\([^;{}()]*\)\s*\{', b.body)), None):
                # the definer: its own private declaration goes, its signature is the truth
                body = '\n'.join(x for x in body.splitlines() if not (tutidy.DECL_LINE_RE.match(x) and tutidy._decl_name(x) == n)) + '\n'
                if candidates[n][choice[n]][0] == 'definition-retyped':
                    st_ = _sig(truth)
                    dm = re.search(r'^([A-Za-z_][\w \*]*?)\b' + re.escape(n) + r'\s*\(([^;{}()]*)\)\s*\{', body, re.M)
                    if dm:
                        params = [x.strip() for x in dm.group(2).split(',')] if dm.group(2).strip() not in ('', 'void') else []
                        names_ = [re.search(r'([A-Za-z_]\w*)\s*$', x).group(1) if re.search(r'([A-Za-z_]\w*)\s*$', x) else '' for x in params]
                        new_params = ', '.join(f'{t} {nm}'.replace('* ', '*') for t, nm in zip(st_[2], names_)) if params else 'void'
                        body = body[:dm.start()] + f'{st_[0]} {n}({new_params}) {{' + body[dm.end():]
                    if not _same(st_[0], dr_ret := _sig(d_full := definitions[n])[0]):
                        body = re.sub(r'\breturn\s+([^;]+);', lambda mm: f'return ({st_[0]})({mm.group(1)});' if not mm.group(1).strip().startswith('(' + st_[0]) else mm.group(0), body)
                continue
            body = adapt(body, n, old_decl_for(bname, n), truth, [], force=bname in forced)
            if body is None:
                return None
        return body

    def render_prologue() -> str:
        lines = []
        knr = set()
        for n in symbols:
            truth = candidates[n][choice[n]][1]
            st = _sig(truth)
            if st and '...' not in st[2]:
                for bname in users[n]:
                    least = min_call_args(tf.get(bname).body, n)
                    if least is not None and least != len(st[2]):
                        knr.add(n)
            if n in hdecl and candidates[n][choice[n]][0] == 'header':
                continue
            if n in knr and st:
                lines.append(f'extern {st[0]} {n}();')
            elif n in definitions and candidates[n][choice[n]][0] == 'definition':
                lines.append(truth)  # the TU's own definition, declared ahead of its callers
            else:
                lines.append(truth)
        report['knr'] = sorted(knr)
        return base_prologue.rstrip('\n') + '\n' + '\n'.join(dict.fromkeys(lines)) + '\n'

    before_hoist = tf.prologue
    hoist_private_types(tf, {n: candidates[n][choice[n]][1] for n in symbols if _sig(candidates[n][choice[n]][1])}, report)
    base_prologue = base_prologue.rstrip('\n') + '\n' + tf.prologue[len(before_hoist):]  # the hoisted types
    original = {b.name: b.body for b in tf.blocks}

    def rebuild() -> None:
        for b in tf.blocks:
            nb = derive(b.name)
            b.body = nb if nb is not None else original[b.name]
        tf.prologue = render_prologue()
        for n_, u in units.items():
            tufile.write_gen(p, u, tf)

    rebuild()
    names = [b.name for b in tf.blocks if b.name in units]
    verdict = v.verdicts(p, names, module)
    failing = [n for n in names if not verdict.get(n)]
    for bname in list(failing):
        fixed = False
        forced.add(bname)
        rebuild()
        if v.verdicts(p, [bname], module).get(bname):
            fixed = True
        else:
            forced.discard(bname)
        for n in [n for n in symbols if not fixed and bname in users[n] and len(candidates[n]) > 1]:
            prev = choice[n]
            for k in range(len(candidates[n])):
                if k == prev:
                    continue
                choice[n] = k
                rebuild()
                affected = sorted(set(users[n]) | {bname})
                vd = v.verdicts(p, affected, module)
                if vd.get(bname) and all(vd.get(x) for x in affected if verdict.get(x)):
                    fixed = True  # the block matches and no other user regressed
                    break
            if fixed:
                break
            choice[n] = prev
        if fixed:
            rebuild()
            verdict = v.verdicts(p, names, module)
            failing = [n for n in names if not verdict.get(n)]
    for n in symbols:
        report['truth'][n] = candidates[n][choice[n]]
    report['rewritten'] = [n for n in names if verdict.get(n)]
    report['reverted'] = failing
    # a block that cannot be adapted keeps its original, self-contained form (still contested)
    pristine = tufile.load(p, tu_source)
    for bname in failing:
        b = tf.get(bname)
        b.body = pristine.get(bname).body
        if 'noprologue' not in b.flags:
            b.flags.append('noprologue')
    for n_, u in units.items():
        tufile.write_gen(p, u, tf)
    final = v.verdicts(p, names, module)
    for n in [n for n, ok in final.items() if not ok]:
        # a second opinion outside the batched path before a block is called failing
        res = oracle.check(p, f'{module}:{n}', 20)
        if res.ok and (res.matched or res.matched_pool) and oracle.unit_fully_matches(res) is None:
            final[n] = True
    report['final_matching'] = sum(1 for x in final.values() if x)
    report['final_failing'] = [n for n, ok in final.items() if not ok]
    if apply and not report['final_failing']:
        tufile._write_atomic(tufile.tu_path(p, tu_source), tf.render())
        # a rewritten block may renumber its private literals: keep pool mappings current
        for u in list(units.values()):
            if isinstance(u.get('pool'), dict):
                res = oracle.check(p, f"{module}:{u['symbols'][0]}", 20)
                if res.ok and (res.matched or res.matched_pool) and res.pool_map != u['pool']:
                    with oracle.build_lock('units.lock'):
                        all_units = p.load_units()
                        for x in all_units:
                            if x['source'] == u['source']:
                                x['pool'] = dict(res.pool_map)
                        p.save_units(all_units)
                    report.setdefault('pool_remapped', []).append(u['symbols'][0])
    elif apply == 'keep':
        pass  # leave the generated units in the resolved state for inspection
    else:
        for u in units.values():
            tufile.write_gen(p, u, pristine)
    return report
