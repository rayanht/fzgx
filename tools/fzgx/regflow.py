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


def region_scores(left, right, accepted=()):
    """Score aligned basic blocks independently of physical register names."""
    from .stuck import classify_rows
    instructions={i:r['instruction'] for i,r in enumerate(left) if r.get('instruction',{}).get('formatted')}
    if not instructions:
        return {}
    addresses={int(r.get('address',0)):i for i,r in instructions.items()}
    first=min(addresses);starts={min(instructions)};indices=list(instructions)
    for n,i in enumerate(indices):
        row=instructions[i];op=row['formatted'].split()[0]
        if row.get('branch_dest') is not None and int(row['branch_dest']) in addresses:
            starts.add(addresses[int(row['branch_dest'])])
        if op.startswith('b') and n+1<len(indices):
            starts.add(indices[n+1])
    starts=sorted(starts);result={};accepted=set(accepted);blocks=[]
    for target_start in starts:
        start=target_start
        # Insertions just before a target block belong to that block.
        while start and not left[start-1].get('instruction',{}).get('formatted'):
            start-=1
        blocks.append((target_start,start))
    for n,(target_start,start) in enumerate(blocks):
        end=blocks[n+1][1] if n+1<len(blocks) else max(len(left),len(right))
        rows=[i for i in range(start,end) if i not in accepted]
        l=[left[i] if i<len(left) else {} for i in rows]
        r=[right[i] if i<len(right) else {} for i in rows]
        counts=classify_rows(l,r)
        changed=sum((a.get('diff_kind') or 'DIFF_NONE')!='DIFF_NONE' or
                    (b.get('diff_kind') or 'DIFF_NONE')!='DIFF_NONE' for a,b in zip(l,r))
        key=str(int(instructions[target_start].get('address',0))-first)
        result[key]=[counts.get('op',0)+counts.get('ins',0),
                     counts.get('imm',0)+counts.get('reloc',0)+counts.get('frame',0),changed]
    return result


def analyse_rows(left, right, tables=None):
    boundaries = set()
    for rows in (left, right):
        addresses = {int(r['instruction']['address']): i for i, r in enumerate(rows)
                     if r.get('instruction', {}).get('address') is not None}
        boundaries.update(addresses[int(r['instruction']['branch_dest'])] for r in rows
                          if r.get('instruction', {}).get('branch_dest') is not None
                          and int(r['instruction']['branch_dest']) in addresses)
    result=analyse([r.get('instruction', {}).get('formatted', '') for r in left],
                   [r.get('instruction', {}).get('formatted', '') for r in right], boundaries)
    flows=[cfg_values(rows,table) for rows,table in zip((left,right),tables or ({},{}))]
    conflicts={r['row']:r for r in result['value_flow']};equivalent=set(result['equivalent_rows'])
    for i in flows[0].keys() & flows[1].keys():
        a,b=flows[0][i],flows[1][i]
        if a['value'] is None or b['value'] is None or a['op']!=b['op']:
            continue
        if a['value'][0]==b['value'][0]:
            conflicts.pop(i,None)
            if a['text']!=b['text']:equivalent.add(i)
        elif (a['op'] in STORES and '(r1)' not in a['text']+b['text'] and a['address'] is not None
                and b['address'] is not None and a['address'][0]==b['address'][0]
                and a['stored'] is not None and b['stored'] is not None and a['stored'][0]!=b['stored'][0]):
            conflicts[i]=dict(row=i,target=a['text'],ours=b['text'],target_inputs=a['value'][1],ours_inputs=b['value'][1])
    result['value_flow']=[conflicts[i] for i in sorted(conflicts)]
    result['equivalent_rows']=sorted(equivalent)
    result['unresolved_rows']=sorted(set(result['unresolved_rows'])-equivalent)
    return result


def expression(op, args, regs):
    known=True;origins=[]
    def replace(match):
        nonlocal known
        value=regs.get(match[0])
        if value is None:
            known=False;return '?'
        origins.append(value[1]);return value[0]
    operands=[REG.sub(replace,a.strip()) for a in args.split(',')]
    if not known:
        return None
    if op in COMMUTATIVE:operands.sort()
    elif op in {'fmadd','fmadds','fmsub','fmsubs','fnmadd','fnmadds','fnmsub','fnmsubs'}:
        operands[:2]=sorted(operands[:2])
    key=hashlib.blake2b(repr((op,operands)).encode(),digest_size=12).hexdigest()
    return key,', '.join(dict.fromkeys(origins))[:160]


def cfg_values(rows, tables):
    """Must-values across branches/loops; a disagreeing predecessor loses a fact.

    Memory histories are separate from register lifetimes. Unknown calls and
    stores invalidate load proofs, while preserved register values can survive.
    """
    from collections import deque
    from .evidence import memory_loads
    flow={};memory_loads(rows,tables,flow=flow)
    if not flow:
        return {}
    initial={f'{bank}{i}':('entry:'+bank+str(i),'entry '+bank+str(i)) for bank in 'rf' for i in range(32)}
    initial.update(memory=('memory-entry','memory entry'),stack=('stack-entry','stack entry'))
    incoming={min(flow):initial};pending=deque(incoming);result={}
    while pending:
        i=pending.popleft();before=incoming[i];after=dict(before)
        text=rows[i]['instruction']['formatted'];parts=text.split(None,1);op=parts[0].rstrip('+-')
        args=parts[1] if len(parts)>1 else '';dst,_,rest=args.partition(',');dst=dst.strip();rest=rest.strip();value=None
        if op in ('li','lis'):value=(op+':'+rest,op+' '+rest)
        elif op in ('mr','fmr'):value=before.get(rest)
        elif op=='mflr':value=('lr','saved LR')
        elif op=='stwu' and re.fullmatch(r'r1,\s*-?(?:0x[\da-f]+|\d+)\(r1\)',args):
            after['r1']=('frame','stack frame')
        elif op in STORES|LOADS:
            memory='stack' if '(r1)' in args else 'memory'
            history=before.get(memory)
            if op in LOADS:
                value=expression(op+':'+history[0],rest,before) if history else None
            else:
                value=expression(op,args,before)
                after[memory]=expression('memory:'+op+':'+history[0],args,before) if history else None
                # A pointer can alias stack storage. Keep the register values,
                # but invalidate the other memory partition after any store.
                after.pop('memory' if memory=='stack' else 'stack',None)
        elif op in ARITHMETIC:
            value=expression(op,dst+', '+rest if op=='rlwimi' else rest,before)
        elif op in ('bl','bctrl','blrl'):
            if not re.match(r'_(save|rest)(gpr|fpr)_\d+',args):
                for bank,registers in (('r',(0,*range(3,13))),('f',range(14))):
                    for n in registers:after.pop(f'{bank}{n}',None)
                after.pop('memory',None);after.pop('stack',None)
        elif op.startswith(('b','cmp','fcmp')) or op in ('mtlr','mtctr','nop'):
            pass
        else:
            after={}
        if op in ARITHMETIC|LOADS|{'li','lis','mr','fmr','mflr'}:
            after.pop(dst,None)
            if value:after[dst]=value
        result[i]=dict(op=op,text=text,value=value,
                       address=expression('address',rest,before) if op in STORES else None,
                       stored=before.get(dst) if op in STORES else None)
        successors,unknown=flow[i]
        if unknown:after={}
        for nxt in successors:
            old=incoming.get(nxt)
            merged=after if old is None else {key:value for key,value in old.items() if value is not None and after.get(key)==value}
            if old!=merged:
                incoming[nxt]=dict(merged);pending.append(nxt)
    return result


def analyse(target, ours, boundaries=()):
    """Inputs are formatted aligned rows. Proofs are confined to supported regions."""
    values = [{f'{bank}{i}': ('entry:' + bank + str(i), 'entry ' + bank + str(i))
               for bank in 'rf' for i in range(32)} for _ in range(2)]
    differences, permutations, unknown, operand_order = [], [], [], []
    memory = 0

    for i, (t, o) in enumerate(zip(target, ours)):
        if i in boundaries:
            values = [{}, {}]
        parsed = [re.split(r'\s+', x.strip(), maxsplit=1) for x in (t, o)]
        op = parsed[0][0] if parsed[0] else ''
        if not op or op != parsed[1][0]:
            values = [{}, {}]
            unknown.append(i)
            continue
        if op in COMMUTATIVE and len(parsed[0]) == len(parsed[1]) == 2:
            ta = [a.strip() for a in parsed[0][1].split(',')]
            oa = [a.strip() for a in parsed[1][1].split(',')]
            if (len(ta) == len(oa) == 3 and ta[0] == oa[0] and ta[1] != ta[2]
                    and ta[1:] == oa[1:][::-1] and all(REG.fullmatch(a) for a in ta + oa)):
                operand_order.append(dict(row=i, target=t, ours=o))
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
    return dict(value_flow=differences, equivalent_rows=permutations,
                operand_order=operand_order, unresolved_rows=sorted(set(unknown)))
