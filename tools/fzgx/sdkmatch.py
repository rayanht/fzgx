"""Identify SDK/runtime functions in the DOL by masked-byte signatures. No model involved.

Compile a public decompilation of the same-era Dolphin SDK (build/tools/mkdd, CC0)
with our compiler, hash every function of the resulting objects with relocation
fields masked, hash every function of dtk's split objects of the DOL the same way,
and join. A hit names the DOL function, says which SDK source defines it and how
big it is. Output: state/seeds/sdkmatch.json.
"""

from __future__ import annotations

import hashlib
import json
import subprocess
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Tuple

from .poolfix import Elf, CODE_RELOC_MASKS, masked_code
from .project import ROOT, Project

SHT_RELA = 4
STT_FUNC = 2
# relocation type -> mask of the bits the linker keeps (big-endian word)
MASKS = CODE_RELOC_MASKS

BASE = ["-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int", "-fp", "hardware",
        "-Cpp_exceptions", "off", "-pragma", "cats off", "-pragma", "warn_notinlined off",
        "-use_lmw_stmw", "on", "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-multibyte", "-DMATCHING=1"]
DOLPHIN_FLAGS = BASE + ["-inline", "auto", "-lang=c", "-fp", "fmadd", "-fp_contract", "off", "-char", "signed",
                        "-str", "reuse", "-common", "off", "-O4,p"]
RUNTIME_FLAGS = BASE + ["-fp_contract", "on", "-str", "readonly", "-common", "off",
                        "-inline", "auto,deferred", "-O4,p"]  # no -gccinc: unknown to 1.2.5n


def function_hashes(obj: Path, min_size: int) -> Dict[str, Tuple[str, int]]:
    """{name: (hash, size)} for every function of an object, relocation fields masked."""
    data = obj.read_bytes()
    elf = Elf(data)
    text = elf.section(".text")
    if text is None:
        return {}
    buf = masked_code(elf, text)
    out = {}
    for sym in elf.symbols():
        if (sym["info"] & 0xF) == STT_FUNC and sym["shndx"] == text["index"] and sym["size"] >= min_size:
            chunk = bytes(buf[sym["value"]:sym["value"] + sym["size"]])
            out[sym["name"]] = (hashlib.sha1(chunk).hexdigest(), sym["size"])
    return out


SMB_FLAGS = ["-O4,p", "-inline", "auto", "-nodefaults", "-proc", "gekko", "-fp", "hard", "-Cpp_exceptions", "off",
             "-enum", "int", "-pragma", "cats off", "-maxerrors", "1", "-nosyspath"]
FLAG_SETS = {"dolphin": DOLPHIN_FLAGS, "runtime": RUNTIME_FLAGS, "smb": SMB_FLAGS}


def compile_sdk(sdk: Path, mw: str, out_dir: Path, roots=None):
    """Compile every SDK/runtime source (or `roots`: [(relative dir, flag set name)]);
    returns ([(source, object)], [failed sources])."""
    wibo = ROOT / "build/tools/wibo"
    mwcc = ROOT / "build/compilers" / mw / "mwcceppc.exe"
    incs = []
    for inc in ("include", "src", "src/dolphin", "libs/dolphin"):
        if (sdk / inc).is_dir():
            incs += ["-i", inc]
    # every `include` directory of the tree (runtime headers live in odd places per project)
    for d in sorted(x for x in sdk.rglob("*") if x.is_dir() and x.name.lower() in ("include", "inc")
                    and len(x.relative_to(sdk).parts) <= 6 and ".git" not in x.parts):
        rel = str(d.relative_to(sdk))
        if rel not in incs:
            incs += ["-i", rel]
    jobs = []
    plan = [(r, FLAG_SETS[f]) for r, f in roots] if roots else [
        ("libs/dolphin", DOLPHIN_FLAGS), ("src/dolphin", DOLPHIN_FLAGS),
        ("libs/PowerPC_EABI_Support", RUNTIME_FLAGS), ("src/PowerPC_EABI_Support", RUNTIME_FLAGS),
        ("libs/runtime_libs", RUNTIME_FLAGS), ("src/MetroTRK", RUNTIME_FLAGS)]
    for rel, flags in plan:
        root = sdk / rel
        if root.exists():
            jobs += [(src, flags) for src in sorted(root.rglob("*.c"))]
    done, failed = [], []
    for src, flags in jobs:
        rel = src.relative_to(sdk)
        obj = out_dir / rel.with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        cmd = [str(wibo), str(mwcc)] + flags + incs + ["-c", str(rel), "-o", str(obj)]
        stamp = obj.with_suffix('.command.json')
        command = json.dumps(cmd)
        if (obj.exists() and obj.stat().st_mtime >= src.stat().st_mtime
                and stamp.exists() and stamp.read_text() == command):
            done.append((rel, obj))
            continue
        cp = subprocess.run(cmd, cwd=sdk, text=True, capture_output=True, timeout=120)
        if cp.returncode == 0 and obj.exists():
            stamp.write_text(command)
            done.append((rel, obj))
        else:
            failed.append(str(rel))
    return done, failed


def run(p: Project, sdk: str = "build/tools/mkdd", mw: str = "GC/1.2.5n", min_size: int = 16,
        roots=None) -> Dict[str, object]:
    sdk_dir = ROOT / sdk
    done, failed = compile_sdk(sdk_dir, mw, p.build_dir / "sdkmatch" / Path(sdk).name, roots)
    sdk_hashes: Dict[str, List[tuple]] = defaultdict(list)
    for rel, obj in done:
        for name, (h, size) in function_hashes(obj, min_size).items():
            sdk_hashes[h].append((name, str(rel), size))
    # Old split objects remain on disk after a carve; only scan current ownership.
    dol_objs = {obj for sym in p.functions('main') if (obj := p.target_object_for(sym))}
    dol: Dict[str, Tuple[str, int]] = {}
    for o in dol_objs:
        dol.update(function_hashes(o, min_size))
    syms = p.symbols("main")
    hits, ambiguous = [], []
    for name, (h, size) in dol.items():
        if name not in syms or syms[name].kind != 'function':
            continue
        cands = sdk_hashes.get(h)
        if not cands:
            continue
        names = sorted({c[0] for c in cands})
        rec = {"dol": name, "size": size, "addr": syms[name].addr if name in syms else None,
               "sdk": names, "sources": sorted({c[1] for c in cands}), "named": not name.startswith("fn_")}
        (hits if len(names) == 1 else ambiguous).append(rec)
    hits.sort(key=lambda r: r["addr"] or 0)
    by_lib: Dict[str, int] = defaultdict(int)
    for r in hits:
        parts = r["sources"][0].split("/")
        by_lib[parts[2] if len(parts) > 3 else parts[1]] += r["size"]
    unnamed = [r for r in hits if not r["named"]]
    out = {"sdk": sdk, "mw": mw, "compiled": len(done), "failed": failed,
           "sdk_functions": sum(len(v) for v in sdk_hashes.values()), "dol_functions": len(dol),
           "hits": hits, "ambiguous": ambiguous,
           "summary": {"hits": len(hits), "bytes": sum(r["size"] for r in hits), "unnamed_hits": len(unnamed),
                       "unnamed_bytes": sum(r["size"] for r in unnamed), "ambiguous": len(ambiguous),
                       "by_lib": dict(sorted(by_lib.items(), key=lambda kv: -kv[1]))}}
    path = ROOT / "state" / "seeds" / f"sdkmatch_{Path(sdk).name}.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(out, indent=1) + "\n")
    return out


def apply_names(p: Project, sdks=None) -> Dict[str, object]:
    """Name every unnamed DOL function the signature runs identified (first SDK wins);
    a static that several SDK files define gets its source file as a suffix. Names that
    dtk already assigned are never touched. Link-verified through rename_many."""
    import re
    from .tu import rename_many
    union: Dict[str, dict] = {}
    paths = ([ROOT / "state" / "seeds" / f"sdkmatch_{s}.json" for s in sdks] if sdks
             else sorted((ROOT / "state" / "seeds").glob("sdkmatch_*.json")))
    for path in paths:  # exact SDK sources first (tww, mkdd), engine vocabulary last
        if not path.exists():
            continue
        for r in json.loads(path.read_text())["hits"]:
            union.setdefault(r["dol"], r)
    syms = p.symbols("main")
    taken = {n for m in p.modules for n in p.symbols(m)}
    mapping: Dict[str, str] = {}
    for r in union.values():
        if r["named"] or r["dol"] not in syms or not r["dol"].startswith("fn_"):
            continue
        new = r["sdk"][0]
        if new in taken:
            stem = re.sub(r"\W", "_", r["sources"][0].rsplit("/", 1)[-1].rsplit(".", 1)[0])
            new = f"{new}_{stem}"
        if new in taken:
            continue
        mapping[r["dol"]] = new
        taken.add(new)
    if not mapping:
        return {"ok": True, "applied": 0}
    res = rename_many(p, mapping, verify=True)
    return {"ok": res.get("ok"), "applied": res.get("applied"), "planned": len(mapping),
            "failed": [x for x in res["results"] if not x.get("ok")][:5]}
