"""autotarget.py SYM BODY MW [FLAGS]: map residual register rows to captured webs and print solver targets."""
import sys, json, re, subprocess
sys.path.insert(0,'/Users/rayan/fzgx/tools')
from pathlib import Path
from fzgx.project import Project
from fzgx import oracle, stuck
S=__import__('os').environ.get('FZGX_CAPTURE_DIR','/Users/rayan/fzgx/.fzgx/capture')
sym,body,mw=sys.argv[1:4]; fl=sys.argv[4] if len(sys.argv)>4 else None
cap=f'{S}/{sym}'
p=Project(); res=oracle.check(p,sym,0,source=Path(body),mw_version=mw,extra_cflags=fl)
l,r=res._rows
fin=json.load(open(f'{cap}/pcode-0001-final.json')); sch=json.load(open(f'{cap}/pcode-0001-scheduled.json'))
byaddr={i['address']:i for b in sch['blocks'] for i in b['instructions']}
F=[i for b in fin['blocks'] for i in b['instructions']]
O=[(k,stuck._fmt(r[k])) for k in range(len(r)) if stuck._fmt(r[k])]
print(f'{sym} {res.percent:.2f}: object rows {len(O)}, final pcode {len(F)}')
n=min(len(O),len(F)); mism=[k for k in range(n) if O[k][1].split(' ')[0].split('.')[0].lower()!=F[k]['opcode_descriptor']['mnemonic'].lower().rstrip('.')]
print('mnemonic mismatches (first 8):', [(k,O[k][1].split(' ')[0],F[k]['opcode_descriptor']['mnemonic']) for k in mism[:8]])
targets={}; conflicts=[]
for k in range(n):
    row_i,ours=O[k]; retail=stuck._fmt(l[row_i])
    if not retail or retail==ours or retail.split(' ')[0]!=ours.split(' ')[0]: continue
    ro=[int(x) for x in re.findall(r'\br(\d+)\b',ours)]; rr=[int(x) for x in re.findall(r'\br(\d+)\b',retail)]
    if len(ro)!=len(rr): continue
    gops=[o for o in F[k]['operands'] if o.get('kind')==0]
    sops=[o for o in byaddr[F[k]['address']]['operands'] if o.get('kind')==0] if F[k]['address'] in byaddr else []
    if len(gops)!=len(ro) or len(sops)!=len(gops): continue
    for j,(a,b) in enumerate(zip(ro,rr)):
        if a==b: continue
        if gops[j]['reg']!=a: continue
        v=sops[j]['reg']
        if v in targets and targets[v]!=b: conflicts.append((v,targets[v],b))
        targets.setdefault(v,b)
print('targets:', ','.join(f'v{v}:r{c}' for v,c in sorted(targets.items())))
print('conflicts:', conflicts[:8])
bad={v for v,_,_ in conflicts}
if targets:
    t=','.join(f'v{v}:r{c}' for v,c in sorted(targets.items()) if v not in bad)
    out=subprocess.run(['python3','/Users/rayan/mwcc/tools/source_rank_solver.py',cap,'1','--target',t],capture_output=True,text=True,cwd='/Users/rayan/mwcc')
    print(out.stdout[-2500:]); print(out.stderr[-600:])
