"""Project retail register constraints onto captured virtual values and C edits.

Instruction alignment supplies hypotheses, never match acceptance. Generated
source must be compiled and checked by the normal relocation-aware oracle.
"""
import difflib
import itertools
import math
import re
from collections import defaultdict

from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN

from . import mwgraph, mwconstraints, regalloc

ALIASES = {'li': 'addi', 'lis': 'addis', 'subi': 'addi', 'subis': 'addis',
           'slwi': 'rlwinm', 'srwi': 'rlwinm', 'clrlwi': 'rlwinm', 'clrrwi': 'rlwinm',
           'rotlwi': 'rlwinm', 'clrlslwi': 'rlwinm', 'mtlr': 'mtspr', 'mflr': 'mfspr',
           'mtctr': 'mtspr', 'mfctr': 'mfspr', 'cmpwi': 'cmpi', 'cmplwi': 'cmpli',
           'cmpw': 'cmp', 'cmplw': 'cmpl'}


def mnemonic(name):
    return ALIASES.get(name, name)


def decode(words):
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True
    return [(mnemonic(i.mnemonic), tuple(mwconstraints.REG.findall(i.op_str)), i.op_str)
            for i in md.disasm(b''.join(w.to_bytes(4, 'big') for w in words), 0)]


def web_constraints(captures, target, ours):
    original, retail = decode(ours), decode(target)
    if len(original) != len(ours) or len(retail) != len(target):
        return {'status': 'instruction-shape'}
    shape = lambda row: (row[0], mwconstraints.REG.sub('R', row[2]))
    retail_alignment = difflib.SequenceMatcher(a=[shape(r) for r in original],
                                              b=[shape(r) for r in retail], autojunk=False)
    retail_rows = {block.a + i: block.b + i for block in retail_alignment.get_matching_blocks()
                   for i in range(block.size)}
    nodes = {c['before']['register_class']: {n['virtual_register']: n for n in c['after']['nodes']}
             for c in captures}
    def root(cls, register):
        seen = set()
        while register >= 32 and nodes[cls][register]['flags'] & 4:
            if register in seen:
                raise ValueError('coalescing cycle')
            seen.add(register)
            register = nodes[cls][register]['physical_register']
        return register
    def physical(cls, register):
        register = root(cls, register)
        return register if register < 32 else nodes[cls][register]['physical_register']
    pcode = max((c.get('pcode', []) for c in captures), key=len)
    keys, origins = [], []
    for instruction in pcode:
        operands, regs = [], []
        for a in instruction['operands']:
            cls, r = a['class'], a['reg']
            if cls not in nodes or a['flags'] == 0:
                continue
            prefix = 'r' if cls == 'gpr' else 'f'
            operands.append((cls, root(cls, r)))
            regs.append(prefix + str(physical(cls, r)))
        name = mnemonic(instruction['mnemonic'])
        if name in ('mr', 'fmr') and len(regs) == 2 and regs[0] == regs[1]:
            continue
        keys.append((name, tuple(regs)))
        origins.append(operands)
    matching = difflib.SequenceMatcher(a=keys, b=[r[:2] for r in original], autojunk=False)
    domains, alternatives, anchors = defaultdict(set), [], []
    for block in matching.get_matching_blocks():
        for offset in range(block.size):
            row, index = block.b + offset, block.a + offset
            if row not in retail_rows:
                continue
            name, registers, operand_text = retail[retail_rows[row]]
            if name != original[row][0] or len(registers) != len(origins[index]):
                continue
            if mwconstraints.REG.sub('R', operand_text) != mwconstraints.REG.sub('R', original[row][2]):
                continue
            pairs = list(zip(origins[index], (int(r[1:]) for r in registers)))
            anchors.append(row)
            if name in mwconstraints.COMMUTE and len(pairs) == 3:
                domains[pairs[0][0]].add(pairs[0][1])
                alternatives.append((row, pairs[1:]))
            else:
                for web, color in pairs:
                    domains[web].add(color)
    conflicts = {str(k): sorted(v) for k, v in domains.items() if len(v) > 1}
    desired = {web: next(iter(colors)) for web, colors in domains.items() if len(colors) == 1}
    swapped, unresolved = [], []
    for row, pairs in alternatives:
        (a, x), (b, y) = pairs
        valid = [(swap, u, v) for swap, u, v in [(False, x, y), (True, y, x)]
                 if desired.get(a, u) == u and desired.get(b, v) == v and (a != b or u == v)]
        if not valid:
            unresolved.append(row)
            continue
        if len(valid) > 1 and x != y:
            unresolved.append(row)
            continue
        swap, x, y = valid[0]
        desired[a], desired[b] = x, y
        if swap:
            swapped.append(row)
    return {'status': 'web-hypothesis', 'anchors': anchors,
            'conflicts': conflicts, 'desired': {cls: {r: c for (bank, r), c in desired.items() if cls == bank and r >= 32}
                        for cls in nodes}, 'operand_order_rows': swapped, 'unresolved_rows': unresolved}


def scalar_locals(body, span):
    # Carriers from a previous repair are fixed aggregate declarations; keep
    # scanning so remaining scalars can be repaired in the next captured graph.
    result = []
    for match in re.finditer(r'[^\n]*\n', body[span[1]:span[2]]):
        line = match[0]
        if not line.strip() or re.fullmatch(r'\s*struct \{ [^{};]+ value; \} \w+(?: = \{ .* \})?;\s*', line):
            continue
        decl = regalloc.DECL_RE.match(line.rstrip('\n'))
        if not decl:
            break
        start = span[1] + match.start()
        result.append((start, start + len(line), decl[1], decl[2], decl[3]))
    return result


def declaration_candidates(body, name, captures, constraints, max_orders=50000):
    """Evaluate declaration orders in the actual graph, with no compile loop."""
    if constraints['status'] != 'web-hypothesis' or constraints['operand_order_rows']:
        return [], {'status': constraints['status'], 'orders': 0}
    span = regalloc._function_body_span(body, name)
    if span is None:
        return [], {'status': 'no-body', 'orders': 0}
    locals_ = scalar_locals(body, span)
    if any(regalloc._init_of(body[a:b]) for a, b, *_ in locals_):
        return [], {'status': 'initialized-declarations', 'orders': 0}
    by_name = defaultdict(list)
    for capture in captures:
        cls = capture['before']['register_class']
        for n in capture['before']['nodes']:
            if n.get('name'):
                by_name[n['name']].append((cls, n['virtual_register']))
    if all(all(next(n['physical_register'] for n in c['after']['nodes'] if n['virtual_register'] == r) == color
                   for r, color in constraints['desired'][c['before']['register_class']].items()) for c in captures):
        return [], {'status': 'no-allocation-difference', 'orders': 0}
    movable = [(i, by_name[n][0]) for i, (_, _, _, n, dims) in enumerate(locals_)
               if not dims and len(by_name.get(n, [])) == 1]
    if len(movable) < 2:
        return [], {'status': 'no-movable-stratum', 'orders': 0}
    slots = {cls: sorted((r for _, (bank, r) in movable if bank == cls), reverse=True)
             for cls in constraints['desired']}
    if any([r for _, (bank, r) in movable if bank == cls] != order for cls, order in slots.items()):
        return [], {'status': 'unknown-creation-order', 'orders': 0}
    candidates, checked, best = [], 0, None
    for order in itertools.islice(itertools.permutations(movable), max_orders):
        ranks = {cls: dict(zip((r for _, (bank, r) in order if bank == cls), slots[cls])) for cls in slots}
        score = 0
        for capture in captures:
            before = capture['before']; cls = before['register_class']
            select = mwgraph.simplify(before, ranks[cls])
            if select is None:
                score += 100000
                continue
            colors = mwgraph.replay(before, select)
            score += sum(colors[r] != c for r, c in constraints['desired'][cls].items())
        checked += 1
        best = score if best is None else min(best, score)
        if score:
            continue
        replacements = {i: locals_[j] for (i, _), (j, _) in zip(movable, order)}
        text, cursor = [], 0
        for i, (a, b, *_) in enumerate(locals_):
            text.append(body[cursor:a])
            x, y, *_ = replacements.get(i, locals_[i])
            text.append(body[x:y]); cursor = b
        candidate = ''.join(text) + body[cursor:]
        if candidate != body:
            candidates.append(candidate)
        # Equivalent orders of unused locals do not justify more compiler calls.
        if candidates:
            break
    return candidates, {'status': 'predicted' if candidates else 'no-predicted-declaration-repair',
                        'orders': checked, 'exhaustive': checked == math.factorial(len(movable)),
                        'best_conflicts': best}


def carrier_candidates(body, name, captures, constraints):
    """Move implicated scalar homes into MWCC's aggregate-scalarization stratum.

    A one-field aggregate preserves the scalar's declared type. Only identifier
    uses in the function body are changed; field names, strings and comments
    retain their spelling. Every result still requires a stock compile.
    """
    from .regsolve import TOKEN
    span = regalloc._function_body_span(body, name)
    if span is None or constraints['status'] != 'web-hypothesis':
        return []
    locals_ = scalar_locals(body, span)
    implicated = set()
    for capture in captures:
        cls = capture['before']['register_class']
        desired = {int(r): c for r, c in constraints['desired'][cls].items()}
        nodes = {n['virtual_register']: n for n in capture['after']['nodes']}
        for n in nodes.values():
            r, seen = n['virtual_register'], set()
            while r >= 32 and nodes[r]['flags'] & 4 and r not in seen:
                seen.add(r); r = nodes[r]['physical_register']
            if r >= 32 and r in desired and nodes[r]['physical_register'] != desired[r] and n.get('name'):
                implicated.add(n['name'])
    # Saved compiler temporaries can carry a source scalar whose original home
    # was coalesced into an ABI register. PCode line provenance recovers those
    # assignments instead of mistaking the temporary's @name for a C local.
    assignments = []
    local_names = {l[3] for l in locals_}
    for match in re.finditer(r'^\s*(\w+)\s*=(?!=)[^;{}]+;', body[span[1]:span[2]], re.M):
        if match[1] not in local_names:
            continue
        start = span[1] + match.start(); end = span[1] + match.end()
        assignments.append((body.count('\n', 0, start) + 1, body.count('\n', 0, end) + 2, match[1]))
    for capture in captures:
        cls = capture['before']['register_class']
        desired = {int(r): c for r, c in constraints['desired'][cls].items()}
        nodes = {n['virtual_register']: n for n in capture['after']['nodes']}
        wrong = {r for r, color in desired.items() if nodes[r]['physical_register'] != color}
        for instruction in capture['pcode']:
            line = instruction['line']
            if line is None or line < 1:
                continue
            if any(a['class'] == cls and a['reg'] in wrong and a['flags'] & 2 for a in instruction['operands']):
                implicated.update(var for first, last, var in assignments if first <= line <= last)
    selected = [l for l in locals_ if l[3] in implicated and not l[4]]
    proposals = []
    groups = [(local,) for local in selected]
    groups.extend(itertools.combinations(selected, 2))
    if len(selected) > 2:
        groups.append(tuple(selected))
    for group in groups:
        if any('volatile' in l[2] or 'register' in l[2] for l in group):
            continue
        names = {l[3] for l in group}
        def uses(text):
            changes, previous = [], None
            for match in TOKEN.finditer(text):
                token = match[0]
                if token.startswith(('/*', '//')):
                    continue
                if token in names and previous not in ('.', '->', 'struct', 'union', 'enum'):
                    changes.append((match.start(), match.end(), token + '.value'))
                previous = token
            for a, b, value in reversed(changes):
                text = text[:a] + value + text[b:]
            return text
        changes = []
        for a, b, type_, var, _ in group:
            init = regalloc._init_of(body[a:b])
            initializer = ' = { ' + uses(init) + ' }' if init is not None else ''
            changes.append((a, b, f'    struct {{ {type_} value; }} {var}{initializer};\n'))
        # Rewrite uses between converted declarations too, including scalar
        # initializers depending on an earlier converted local.
        pieces, cursor = [], group[0][0]
        for a, b, declaration in sorted(changes):
            pieces.extend((uses(body[cursor:a]), declaration))
            cursor = b
        pieces.append(uses(body[cursor:span[2]]))
        source = body[:group[0][0]] + ''.join(pieces) + body[span[2]:]
        label = 'carrier:' + ','.join(l[3] for l in group)
        proposals.append((label, source))
        # A block-local value can survive scalarization as a separate web where
        # assigning the aggregate member directly collapses back to a scalar.
        split = source
        changed = False
        for _, _, type_, var, _ in group:
            temp = '__reg_value_' + var
            while re.search(r'\b' + temp + r'\b', split):
                temp += '_'
            pattern = re.compile(r'^(\s*)' + re.escape(var) + r'\.value\s*=\s*([^;{}]+);', re.M)
            def replace_assignment(match):
                nonlocal changed
                changed = True
                return (match[1] + '{ ' + type_ + ' ' + temp + ' = ' + match[2] + '; ' +
                        var + '.value = ' + temp + '; }')
            split = pattern.sub(replace_assignment, split)
        if changed:
            proposals.append((label + ':block-copy', split))
    return proposals
