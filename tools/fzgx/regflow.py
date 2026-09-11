"""Compare value flow before treating register-field differences as allocation.

Linear regions use symbolic expressions, not physical register numbers. At a
control-flow boundary values become unknown: this pass must not invent a proof
across an unanalysed join. Unknown instructions also invalidate the region.
"""
import hashlib
import re

REG = re.compile(r'\b[rf]\d+\b')
COMMUTATIVE = {'add', 'add.', 'and', 'and.', 'or', 'or.', 'xor', 'xor.',
               'mullw', 'mullw.', 'fmul', 'fmuls', 'fadd', 'fadds'}
ARITHMETIC = COMMUTATIVE | {'addi', 'addis', 'subi', 'subis', 'subf', 'subf.',
    'neg', 'neg.', 'fneg', 'fabs', 'fnabs', 'fsub', 'fsubs', 'fdiv', 'fdivs',
    'divw', 'divwu', 'slw', 'srw', 'sraw', 'srawi', 'extsb', 'extsh', 'frsp',
    'rlwinm', 'rlwinm.', 'rlwimi', 'clrlwi', 'clrlwi.', 'clrrwi', 'slwi', 'srwi',
    'clrlslwi', 'ori', 'oris', 'xori', 'xoris', 'andi.', 'andis.', 'cntlzw',
    'fmadd', 'fmadds', 'fmsub', 'fmsubs', 'fnmadd', 'fnmadds', 'fnmsub', 'fnmsubs'}
LOADS = {'lbz', 'lhz', 'lha', 'lwz', 'lfs', 'lfd', 'lbzx', 'lhzx', 'lhax', 'lwzx', 'lfsx', 'lfdx'}
STORES = {'stb', 'sth', 'stw', 'stfs', 'stfd', 'stbx', 'sthx', 'stwx', 'stfsx', 'stfdx'}


def analyse_rows(left, right):
    boundaries = set()
    for rows in (left, right):
        addresses = {int(r['instruction']['address']): i for i, r in enumerate(rows)
                     if r.get('instruction', {}).get('address') is not None}
        boundaries.update(addresses[int(r['instruction']['branch_dest'])] for r in rows
                          if r.get('instruction', {}).get('branch_dest') is not None
                          and int(r['instruction']['branch_dest']) in addresses)
    return analyse([r.get('instruction', {}).get('formatted', '') for r in left],
                   [r.get('instruction', {}).get('formatted', '') for r in right], boundaries)


def analyse(target, ours, boundaries=()):
    """Inputs are formatted aligned rows. Proofs are confined to supported regions."""
    values = [{f'{bank}{i}': ('entry:' + bank + str(i), 'entry ' + bank + str(i))
               for bank in 'rf' for i in range(32)} for _ in range(2)]
    differences, permutations, unknown = [], [], []
    memory = 0

    def expression(op, args, regs):
        known = True
        origins = []
        def replace(m):
            nonlocal known
            value = regs.get(m[0])
            if value is None:
                known = False
                return '?'
            origins.append(value[1])
            return value[0]
        operands = [REG.sub(replace, a.strip()) for a in args.split(',')]
        if not known:
            return None
        if op in COMMUTATIVE:
            operands.sort()
        key = hashlib.blake2b(repr((op, operands)).encode(), digest_size=12).hexdigest()
        return key, ', '.join(dict.fromkeys(origins))[:160]

    for i, (t, o) in enumerate(zip(target, ours)):
        if i in boundaries:
            values = [{}, {}]
        parsed = [re.split(r'\s+', x.strip(), maxsplit=1) for x in (t, o)]
        op = parsed[0][0] if parsed[0] else ''
        if not op or op != parsed[1][0]:
            values = [{}, {}]
            unknown.append(i)
            continue
        if op.startswith('b'):
            if op == 'bl':
                if parsed[0] != parsed[1]:
                    values = [{}, {}]
                    unknown.append(i)
                    continue
                for regs in values:
                    for bank, indices in (('r', [0, *range(3, 13)]), ('f', range(14))):
                        for n in indices:
                            regs.pop(f'{bank}{n}', None)
                    regs['r3'] = (f'call:{i}:r3', f'call at row {i}')
                    regs['f1'] = (f'call:{i}:f1', f'call at row {i}')
                memory += 1
            else:
                values = [{}, {}]
            continue
        if op in ('nop', 'mflr', 'mtlr', 'mtctr'):
            if op == 'mflr':
                for parts, regs in zip(parsed, values):
                    regs[parts[1]] = ('lr', 'saved LR')
            continue
        if op.startswith(('cmp', 'fcmp')):
            continue
        if op not in ARITHMETIC | LOADS | STORES | {'mr', 'fmr', 'li', 'lis', 'stwu'}:
            values = [{}, {}]
            unknown.append(i)
            continue
        results, destinations = [], []
        for parts, regs in zip(parsed, values):
            dst, _, args = parts[1].partition(',')
            dst, args = dst.strip(), args.strip()
            destinations.append(dst)
            if op in ('li', 'lis'):
                result = (op + ':' + args, op + ' ' + args)
            elif op in ('mr', 'fmr'):
                result = regs.get(args)
            elif op in STORES or op == 'stwu':
                result = expression(op, parts[1], regs)
            else:
                result = expression(op + (f':memory{memory}' if op in LOADS else ''),
                                    dst + ', ' + args if op == 'rlwimi' else args, regs)
            results.append(result)
            if op not in STORES and op != 'stwu':
                regs[dst] = (result[0], f'{op} at row {i}') if result else None
        if all(results):
            # Different intermediate producers at the same row can be legitimate
            # scheduling/allocation. Only an observable use establishes a conflict.
            if results[0][0] != results[1][0] and op in STORES and '(r1)' not in t + o:
                differences.append(dict(row=i, target=t, ours=o, target_inputs=results[0][1], ours_inputs=results[1][1]))
            elif results[0][0] == results[1][0] and t != o:
                permutations.append(i)
        elif t != o:
            unknown.append(i)
        if op in STORES or op == 'stwu':
            memory += 1
        if op == 'stwu':
            # Frame setup is the only updating-address form handled here.
            for parts, regs in zip(parsed, values):
                if re.search(r'^r1,\s*-?(?:0x[\da-f]+|\d+)\(r1\)$', parts[1]):
                    regs['r1'] = ('frame', 'stack frame')
                else:
                    regs.clear()
    return dict(value_flow=differences, equivalent_rows=permutations, unresolved_rows=sorted(set(unknown)))
