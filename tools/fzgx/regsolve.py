"""Bounded compiler-response repair, with compile batches shared across functions.

Probe source decisions once, retain their exact changed instruction bits, then
compose disjoint repairs. No factorial orders, beam, or recursive recompilation.
The compiler remains the authority: response composition is a prediction and
every predicted solution must compile and pass the relocation-aware oracle.
"""
from __future__ import annotations

import difflib
import hashlib
import json
import re
import time
from collections import defaultdict
from pathlib import Path

from . import oracle, regalloc


TOKEN = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
                   r'[A-Za-z_]\w*|(?:0[xX][0-9a-fA-F]+|\d+(?:\.\d*)?)(?:[eE][+-]?\d+)?[uUlLfF]*|'
                   r'->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||[+*/%&|^!-]=|[^\s]', re.S)
PREC = {'=': 1, '+=': 1, '-=': 1, '*=': 1, '/=': 1, '|=': 1, '&=': 1,
        '||': 2, '&&': 3, '|': 4, '^': 5, '&': 6, '==': 7, '!=': 7,
        '<': 8, '>': 8, '<=': 8, '>=': 8, '<<': 9, '>>': 9,
        '+': 10, '-': 10, '*': 11, '/': 11, '%': 11}
COMMUTE = {'+', '*', '&', '|', '^', '==', '!='}


def commutations(body, name):
    """Parse expression precedence, retaining source spans and parenthesization.

    Calls, updates and assignments make an expression ineligible to commute,
    though pure subexpressions within it remain eligible. Casts and unsupported
    syntax end a parse; compilation checks all proposals against retail.
    """
    span = regalloc._function_body_span(body, name)
    if not span:
        return []
    tokens = [(m[0], m.start() + span[1], m.end() + span[1])
              for m in TOKEN.finditer(body[span[1]:span[2]])
              if not m[0].startswith(('/*', '//'))]
    proposals, sites = [], defaultdict(list)
    types = {'void', 'char', 'short', 'int', 'long', 'signed', 'unsigned', 'float', 'double',
             'u8', 's8', 'u16', 's16', 'u32', 's32', 'u64', 's64', 'f32', 'f64'}
    types.update(re.findall(r'\btypedef\s+[^;{}]+\s+(\w+)\s*;', body))

    def parse(i, minimum=1):
        if i >= len(tokens):
            raise ValueError
        tok, start, end = tokens[i]
        i += 1
        pure = True
        if tok == '(':
            close = i
            while close < len(tokens) and (re.fullmatch(r'\w+', tokens[close][0]) or tokens[close][0] == '*'):
                close += 1
            cast = (i < close < len(tokens) and tokens[close][0] == ')' and
                    (tokens[i][0] in types or tokens[i][0] in ('struct', 'union', 'enum', 'const', 'volatile')))
            if cast:
                i, (_, end, pure) = parse(close + 1, 12)
            else:
                i, (_, end, pure) = parse(i)
                if i >= len(tokens) or tokens[i][0] != ')':
                    raise ValueError
                end = tokens[i][2]
                i += 1
        elif tok in ('-', '+', '!', '~', '*', '&', '++', '--'):
            i, (_, end, pure) = parse(i, 12)
            pure &= tok not in ('++', '--')
        elif not re.match(r'[\w"\']', tok):
            raise ValueError
        while i < len(tokens):
            op = tokens[i][0]
            if op in ('->', '.') and i + 1 < len(tokens):
                end = tokens[i + 1][2]
                i += 2
                continue
            if op == '[':
                j, _ = parse(i + 1)
                if j >= len(tokens) or tokens[j][0] != ']':
                    raise ValueError
                # Index expressions can have side effects too.
                pure &= not any(t[0] in ('(', '++', '--', '=') for t in tokens[i + 1:j])
                end, i = tokens[j][2], j + 1
                continue
            if op == '(':
                # Parse arguments to discover commutations inside calls.
                j = i + 1
                while j < len(tokens) and tokens[j][0] != ')':
                    j, _ = parse(j)
                    if j < len(tokens) and tokens[j][0] == ',':
                        j += 1
                    else:
                        break
                if j >= len(tokens) or tokens[j][0] != ')':
                    raise ValueError
                end, i, pure = tokens[j][2], j + 1, False
                continue
            if op in ('++', '--'):
                end, i, pure = tokens[i][2], i + 1, False
                continue
            precedence = PREC.get(op, 0)
            if precedence < minimum:
                break
            j, (rs, re_, rp) = parse(i + 1, precedence + (precedence != 1))
            if op in COMMUTE and pure and rp and body[start:end] != body[rs:re_]:
                replacement = f'(({body[rs:re_]}) {op} ({body[start:end]}))'
                proposals.append((f'operand {op} at {start}', body[:start] + replacement + body[re_:]))
                sites[(body[start:re_], replacement)].append((start, re_))
            end, i, pure = re_, j, pure and rp and precedence != 1
        return i, (start, end, pure)

    i = 0
    while i < len(tokens):
        try:
            j, _ = parse(i)
            i = max(i + 1, j)
        except (ValueError, RecursionError):
            i += 1
    # CSE couples identical occurrences: changing one may leave the shared
    # expression's operand order determined by the unchanged occurrence.
    grouped = []
    for (old, replacement), ranges in sites.items():
        ranges = sorted(set(ranges))
        if len(ranges) > 1 and all(b <= c for (_, b), (c, _) in zip(ranges, ranges[1:])):
            text = body
            for a, b in reversed(ranges):
                text = text[:a] + replacement + text[b:]
            grouped.append((f'shared operands {old}', text))
    return list(dict.fromkeys(grouped + proposals))


def probes(body, name, limit=32):
    """Linear probes, not permutations; each observed response is reusable."""
    choices = commutations(body, name)
    normalized = regalloc.normalise(body)
    span = regalloc._function_body_span(normalized, name)
    if span:
        locs = regalloc._locals(normalized, span)
        lines = [normalized[s:e] for s, e, *_ in locs]
        for i in range(len(locs) - 1):
            order = list(range(len(locs)))
            order[i:i + 2] = reversed(order[i:i + 2])
            if regalloc._order_ok(locs, lines, order):
                choices.append((f'adjacent declarations {i}', regalloc.reorder(normalized, locs, order)))
    # Scope and materialization change live ranges; they are not register renames.
    nested = []
    if span:
        declarations = [(m.start() + span[1], m.end() + span[1], m[0])
                        for m in re.finditer(r'[^\n]*\n', normalized[span[1]:span[2]])
                        if (match := regalloc.DECL_RE.match(m[0].rstrip('\n')))
                        and match[1].strip() not in ('return', 'goto', 'break', 'continue')]
        for (a, b, first), (c, d, second) in zip(declarations, declarations[1:]):
            if b != c:
                continue
            fm, sm = (regalloc.DECL_RE.match(line.rstrip('\n')) for line in (first, second))
            if re.search(r'\b' + re.escape(fm[2]) + r'\b', sm[4] or ''):
                continue
            nested.append((f'block declarations {fm[2]}, {sm[2]}', normalized[:a] + second + first + normalized[d:]))
    from .fixup import optimizer_pragmas
    families = [choices, nested, regalloc.scope_moves(normalized, name),
                optimizer_pragmas(body, name),
                regalloc.through_local(normalized, name), regalloc.split_inits(normalized, name)]
    out, seen = [], {body}
    for i in range(max(map(len, families), default=0)):
        for family in families:
            if i < len(family) and family[i][1] not in seen:
                seen.add(family[i][1])
                out.append(family[i])
                if len(out) == limit:
                    return out
    return out


def edits(before, after):
    return [(a, b, after[c:d]) for tag, a, b, c, d in
            difflib.SequenceMatcher(None, before, after, autojunk=False).get_opcodes() if tag != 'equal']


def compose(body, target, baseline, responses):
    """Set cover over exact repaired bits, constrained by source-span conflicts.

    Responses that change any correct bit are excluded. A combined compile is
    essential: register allocation can couple otherwise disjoint source edits.
    """
    remaining = {(i, bit) for i, (a, b) in enumerate(zip(target, baseline))
                 for bit in range(32) if (a ^ b) & (1 << bit)}
    eligible = []
    for label, source, words in responses:
        if words is None or len(words) != len(target):
            continue
        if any((old ^ new) & (wanted ^ new) for wanted, old, new in zip(target, baseline, words)):
            continue
        fixed = {(i, bit) for i, (old, new) in enumerate(zip(baseline, words))
                 for bit in range(32) if (old ^ new) & (1 << bit)}
        if fixed:
            eligible.append((fixed, label, edits(body, source)))
    chosen, patches = [], []
    while eligible:
        eligible.sort(key=lambda r: -len(r[0] & remaining))
        fixed, label, changes = eligible.pop(0)
        if not fixed & remaining:
            break
        if any(max(a, c) <= min(b, d) for a, b, _ in changes for c, d, _ in patches):
            continue
        chosen.append(label)
        patches.extend(changes)
        remaining -= fixed
    if len(chosen) < 2:
        return None
    for a, b, text in sorted(patches, reverse=True):
        body = body[:a] + text + body[b:]
    return ' + '.join(chosen), body


def linear_compositions(body, target, baseline, responses):
    """Solve the measured bit responses over GF(2), including cancelling effects.

    This is a shortlist, never an assertion that the allocator is linear. Rotating
    pivot order exposes bounded alternative solutions without subset enumeration.
    """
    def vector(words):
        return int.from_bytes(b''.join((a ^ b).to_bytes(4, 'big') for a, b in zip(baseline, words)), 'big')
    wanted = vector(target)
    choices = [(label, source, vector(words)) for label, source, words in responses
               if words and len(words) == len(target)]
    choices = [c for c in choices if c[2]]
    proposals, seen = [], set()
    for offset in range(min(len(choices), 8)):
        ordered = choices[offset:] + choices[:offset]
        basis = {}
        for i, (_, _, value) in enumerate(ordered):
            mask = 1 << i
            while value:
                pivot = value.bit_length()
                if pivot not in basis:
                    basis[pivot] = value, mask
                    break
                other, selected = basis[pivot]
                value ^= other
                mask ^= selected
        value, mask = wanted, 0
        while value and value.bit_length() in basis:
            other, selected = basis[value.bit_length()]
            value ^= other
            mask ^= selected
        if value or mask.bit_count() < 2:
            continue
        patches, labels = [], []
        for i, (label, source, _) in enumerate(ordered):
            if not mask & (1 << i):
                continue
            changes = edits(body, source)
            if any(max(a, c) <= min(b, d) for a, b, _ in changes for c, d, _ in patches):
                break
            patches.extend(changes)
            labels.append(label)
        else:
            text = body
            for a, b, replacement in sorted(patches, reverse=True):
                text = text[:a] + replacement + text[b:]
            if text not in seen:
                seen.add(text)
                proposals.append(('response equations: ' + ' + '.join(labels), text))
    return proposals


def batch(project, records, output, limit=32):
    """Records bind frozen source/target/baseline objects and compiler settings."""
    started = time.perf_counter()
    output.mkdir(parents=True, exist_ok=True)
    states, pending, timings = {}, [], {}
    for symbol, record in records.items():
        body = Path(record['source']).read_text()
        if hashlib.sha256(body.encode()).hexdigest() != record['sha256']:
            raise ValueError(f'{symbol}: changed input')
        name = project.resolve(symbol).name
        target = oracle.words(Path(record['target']), name)
        baseline = oracle.words(Path(record['object']), name)
        if not target or not baseline or len(target) != len(baseline):
            continue
        from . import regflow
        rows = oracle.function_rows(project, name, Path(record['target']), Path(record['object']))
        flow = regflow.analyse_rows(*rows[:2]) if rows else None
        candidates = probes(body, name, limit)
        states[symbol] = dict(body=body, target=target, baseline=baseline, responses=[],
                              flow=flow, probes=len(candidates), before=oracle.word_score(target, baseline)[0])
        pending.extend((symbol, label, text) for label, text in candidates)
    timings['proposals_ms'] = (time.perf_counter() - started) * 1000
    manifest = {}

    def evaluate(items, stage):
        groups = defaultdict(list)
        for i, (symbol, label, source) in enumerate(items):
            record = records[symbol]
            path = output / f'{stage}_{i}.c'
            path.write_text(source)
            groups[(project.resolve(symbol).module, record['mw'], record['flags'])].append((symbol, label, source, path))
        for group, values in groups.items():
            module, mw, flags = group
            objects = oracle.compile_many(project, module, [v[3] for v in values], output / stage, mw, flags)
            for symbol, label, source, path in values:
                state = states[symbol]
                obj = objects.get(path)
                words = oracle.words(obj, project.resolve(symbol).name) if obj else None
                state['responses'].append((label, source, words))
                if words == state['target'] and symbol not in manifest:
                    result = oracle._diff(project, module, project.resolve(symbol).name, '', 0,
                                          target=Path(records[symbol]['target']), base=obj)
                    if result.matched or result.matched_pool:
                        manifest[symbol] = dict(path=str(path.resolve()), sha256=hashlib.sha256(source.encode()).hexdigest(),
                                                mw=mw, flags=flags, percent=100, kind='regsolve', repair=label)
    tick = time.perf_counter()
    evaluate(pending, 'probe')
    timings['probes_ms'] = (time.perf_counter() - tick) * 1000
    tick = time.perf_counter()
    combined = []
    for symbol, state in states.items():
        if symbol not in manifest:
            result = compose(state['body'], state['target'], state['baseline'], state['responses'])
            if result:
                combined.append((symbol, *result))
            combined.extend((symbol, *result) for result in
                            linear_compositions(state['body'], state['target'], state['baseline'], state['responses']))
    timings['composition_ms'] = (time.perf_counter() - tick) * 1000
    tick = time.perf_counter()
    evaluate(combined, 'combined')
    timings['combined_compile_ms'] = (time.perf_counter() - tick) * 1000
    details = {}
    for symbol, state in states.items():
        best = max([state['before']] + [oracle.word_score(state['target'], w)[0]
                                      for _, _, w in state['responses'] if w])
        details[symbol] = dict(before=state['before'], best=best, probes=state['probes'], matched=symbol in manifest,
                               flow=state['flow'])
    summary = dict(functions=len(states), matched=len(manifest), probes=len(pending), combinations=len(combined),
                   improved=sum(r['best'] > r['before'] for r in details.values()), timings=timings,
                   elapsed_ms=(time.perf_counter() - started) * 1000)
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    (output / 'results.json').write_text(json.dumps(dict(summary=summary, functions=details), indent=2) + '\n')
    return summary
