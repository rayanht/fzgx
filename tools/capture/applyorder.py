"""applyorder.py SYM BODY MW FLAGS 'v46, v34, ...': reorder the leading local declarations so the named webs follow the solver's rank (first declared = highest rank) and check."""
import sys, re, subprocess
sys.path.insert(0,'/Users/rayan/fzgx/tools')
from pathlib import Path
from fzgx.project import Project
from fzgx import oracle, fixup_source as fs
S=__import__('os').environ.get('FZGX_CAPTURE_DIR','/Users/rayan/fzgx/.fzgx/capture')
sym,body,mw,fl,order=sys.argv[1:6]; fl=fl or None
cap=f'{S}/{sym}'
vm=subprocess.run(['python3','/Users/rayan/mwcc/tools/vreg_map.py',cap,'0001'],capture_output=True,text=True,cwd='/Users/rayan/mwcc').stdout
names={}
for ln in vm.split('\n'):
    f=ln.split()
    if len(f)>=5 and f[2]=='fn-scope' and f[1]!='?': names[int(f[0])]=f[1]
ranks=[int(v.strip().lstrip('v')) for v in order.split(',')]
wanted=[names[v] for v in ranks if v in names][::-1]   # highest rank first = first declared
text=open(body).read(); p=Project()
span=fs._function_body_span(text,sym); locs=fs._locals(text,span)
decl={l[3]:text[l[0]:l[1]] for l in locs}
others=[l[3] for l in locs if l[3] not in wanted]
print('wanted order:', wanted, '| other locals kept first:', others)
new=''.join(decl[n] for n in others)+''.join(decl[n] for n in wanted if n in decl)
out=text[:locs[0][0]]+new+text[locs[-1][1]:]
f=Path(S)/f'{sym}_solver.c'; f.write_text(out)
r=oracle.check(p,sym,0,source=f,mw_version=mw,extra_cflags=fl)
base=oracle.check(p,sym,0,source=Path(body),mw_version=mw,extra_cflags=fl)
print(f'{sym}: base {base.percent:.2f} -> solver order {r.percent if r.ok else -1:.2f}', 'MATCH' if r.ok and (r.matched or r.matched_pool) else '', '' if r.ok else r.error[-200:])
