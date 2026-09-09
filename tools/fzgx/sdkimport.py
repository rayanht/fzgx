"""Import identified SDK C with declarations and relocation bindings derived from objects."""

from __future__ import annotations

import json
import ast
import operator
import re
import struct
import subprocess
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from . import api, oracle, sdkmatch
from .ledger import Ledger
from .poolfix import Elf
from .project import ROOT, STATE_DIR, Project
from .reuse import replace_symbols

LEXICAL = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")
FLAGS = '-use_lmw_stmw on -fp fmadd -fp_contract off -char signed -common off'
BASE_TYPES = {'s8', 's16', 's32', 's64', 'u8', 'u16', 'u32', 'u64', 'f32', 'f64', 'BOOL', 'size_t'}


def masked(text: str) -> str:
    return LEXICAL.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)


@dataclass
class Piece:
    kind: str
    names: set
    text: str
    signature: str = ""
    address: int | str | None = None


def integer_expression(text: str) -> int:
    ops = {ast.LShift: operator.lshift, ast.RShift: operator.rshift,
           ast.BitOr: operator.or_, ast.BitAnd: operator.and_, ast.Add: operator.add,
           ast.Sub: operator.sub, ast.Mult: operator.mul}
    def value(node):
        if isinstance(node, ast.Constant) and isinstance(node.value, int):
            return node.value
        if isinstance(node, ast.BinOp) and type(node.op) in ops:
            return ops[type(node.op)](value(node.left), value(node.right))
        raise ValueError(f'unsupported SDK address expression: {text}')
    return value(ast.parse(text, mode='eval').body)


def declarations(text: str) -> list:
    """Split compiler-preprocessed C at top-level declarations/function definitions."""
    text = re.sub(r"^#.*\n?", "", text, flags=re.M)
    text = LEXICAL.sub(lambda m: '' if m[0].startswith(('/',)) else m[0], text)
    clean = masked(text)
    out = []
    start = depth = parens = 0
    function = None
    for i, ch in enumerate(clean):
        if ch == '(':
            parens += 1
        elif ch == ')':
            parens -= 1
        elif ch == '{':
            if depth == 0:
                prefix = clean[start:i].strip()
                m = re.search(r"\b(\w+)\s*\([^;{}]*\)\s*$", prefix)
                if m and not re.match(r"(?:typedef|struct|union|enum)\b", prefix) and '=' not in prefix:
                    function = (m[1], text[start:i].strip())
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0 and function:
                name, signature = function
                out.append(Piece('function', {name}, text[start:i + 1].strip(), signature))
                start = i + 1
                function = None
        elif ch == ';' and depth == 0 and parens == 0:
            part = text[start:i + 1].strip()
            start = i + 1
            if not part:
                continue
            names = set()
            address = None
            if part.startswith('typedef'):
                fp = re.search(r"\(\s*\*\s*(\w+)\s*\)", part)
                tail = re.search(r"\b(\w+)\s*(?:\[[^\]]*\]\s*)*;\s*$", part)
                if fp:
                    names.add(fp[1])
                elif tail:
                    names.add(tail[1])
                names.update(re.findall(r"\b(?:struct|union|enum)\s+(\w+)", part.split('{')[0]))
                kind = 'type'
            elif re.match(r"(?:struct|union|enum)\s+\w+\s*[;{]", part):
                names.add(re.match(r"\w+\s+(\w+)", part)[1])
                kind = 'type'
            else:
                proto = re.search(r"\b(\w+)\s*\([^;{}]*\)\s*;\s*$", part)
                if proto and '=' not in part:
                    names.add(proto[1])
                    kind = 'prototype'
                else:
                    absolute = re.fullmatch(r'([^:{}=]+)\s*:\s*([^{}]+);', masked(part), re.S)
                    if absolute:
                        address = absolute[2].strip() if re.fullmatch(r'\s*\w+\s*', absolute[2]) else integer_expression(absolute[2])
                        if isinstance(address, str) and not address.isidentifier():
                            address = integer_expression(address)
                        part = absolute[1].strip() + ';'
                    decl = part.split('=', 1)[0].rstrip().rstrip(';')
                    var = re.search(r"\b(\w+)\s*(?:\[[^\]]*\]\s*)*$", decl)
                    if var:
                        names.add(var[1])
                    kind = 'object'
            out.append(Piece(kind, names, part, address=address))
    return out


def preprocess(sdk: Path, source: str, mw: str) -> str:
    scratch = STATE_DIR / 'sdkimport' / sdk.name
    scratch.mkdir(parents=True, exist_ok=True)
    output = scratch / (Path(source).stem + '.i')
    includes = ['include', 'src', 'src/dolphin', 'libs/dolphin']
    includes += [str(d.relative_to(sdk)) for d in sdk.rglob('*')
                 if d.is_dir() and d.name.lower() in ('include', 'inc') and '.git' not in d.parts
                 and len(d.relative_to(sdk).parts) <= 6]
    cmd = [str(ROOT / 'build/tools/wibo'), str(ROOT / 'build/compilers' / mw / 'mwcceppc.exe')]
    cmd += sdkmatch.DOLPHIN_FLAGS
    for inc in dict.fromkeys(includes):
        if (sdk / inc).is_dir():
            cmd += ['-i', inc]
    cp = subprocess.run(cmd + ['-E', source], cwd=sdk, text=True, capture_output=True, timeout=120)
    if cp.returncode:
        raise RuntimeError((cp.stdout + cp.stderr)[-3000:])
    output.write_text(cp.stdout)
    return cp.stdout


def relocations(obj: Path, name: str) -> dict:
    elf = Elf(obj.read_bytes())
    symbols = elf.symbols()
    fn = next(s for s in symbols if s['name'] == name and s['info'] & 15 == 2)
    out = {}
    for section in elf.sections:
        if section['type'] != 4 or section['info'] != fn['shndx']:
            continue
        for off in range(section['offset'], section['offset'] + section['size'], 12):
            addr, info, addend = struct.unpack_from('>IIi', elf.data, off)
            if fn['value'] <= addr < fn['value'] + fn['size']:
                symbol = symbols[info >> 8]
                out[addr - fn['value']] = (symbol['name'], addend, info & 255)
    return out


def candidates(p: Project, library: str) -> list:
    by_addr = {s.addr: s for s in p.functions('main')}
    ledger = Ledger()
    result = []
    for sdk in ('mkdd', 'tww'):
        path = ROOT / 'state/seeds' / f'sdkmatch_{sdk}.json'
        data = json.loads(path.read_text())
        for hit in data['hits']:
            sym = by_addr.get(hit.get('addr'))
            if sym is None or sym.size != hit['size']:
                continue
            row = ledger.get(p.key(sym))
            if row is None or row['status'] != 'unmatched':
                continue
            for source in hit['sources']:
                if f'/{library}/' in source:
                    result.append(dict(symbol=sym.name, size=sym.size, sdk=sdk, source=source,
                                       sdk_symbol=hit['sdk'][0], mw=data['mw']))
    return result


def bindings(p: Project, rec: dict) -> dict:
    source_obj = p.build_dir / 'sdkmatch' / rec['sdk'] / Path(rec['source']).with_suffix('.o')
    sym = p.resolve(rec['symbol'])
    target = p.target_object_for(sym)
    left = relocations(source_obj, rec['sdk_symbol'])
    right = relocations(target, sym.name)
    mapping = {rec['sdk_symbol']: sym.name}
    for off, (name, addend, kind) in left.items():
        if name.startswith('@'):
            continue
        if off not in right:
            raise ValueError(f'{off:#x}: source relocation {name} has no retail relocation')
        dest, dest_addend, dest_kind = right[off]
        if (addend, kind) != (dest_addend, dest_kind):
            raise ValueError(f'{off:#x}: {name}+{addend:#x} -> {dest}+{dest_addend:#x}, relocation {kind}/{dest_kind}')
        if name in mapping and mapping[name] != dest:
            raise ValueError(f'inconsistent binding of {name}: {mapping[name]} / {dest}')
        mapping[name] = dest
    return mapping


def dependency_closure(pieces: list, function: Piece, mapping: dict) -> tuple:
    providers = defaultdict(list)
    for i, piece in enumerate(pieces):
        for name in piece.names:
            providers[name].append(i)
    selected = set()
    todo = set(IDENT.findall(masked(function.text))) - function.names
    seen = set(function.names)
    while todo:
        name = todo.pop()
        if name in seen:
            continue
        seen.add(name)
        for i in providers.get(name, []):
            piece = pieces[i]
            selected.add(i)
            text = (piece.signature if piece.names & mapping.keys() else piece.text) if piece.kind == 'function' else piece.text.split('=', 1)[0] if piece.kind == 'object' else piece.text
            todo.update(set(IDENT.findall(masked(text))) - seen)
    types, externs = [], []
    for i in sorted(selected):
        piece = pieces[i]
        if piece.kind == 'type':
            types.append(piece.text)
        elif piece.kind == 'function':
            if piece.names & mapping.keys():
                externs.append(re.sub(r'^(?:static\s+|inline\s+)+', '', piece.signature) + ';')
            else:
                externs.append('static inline ' + re.sub(r'^(?:static\s+|inline\s+)+', '', piece.text))
        elif piece.kind == 'object':
            decl = piece.text.split('=', 1)[0].strip().rstrip(';')
            externs.append('extern ' + re.sub(r'^(?:static\s+|extern\s+)+', '', decl) + ';')
        else:
            externs.append(piece.text)
    return list(dict.fromkeys(types)), list(dict.fromkeys(externs))


def prepare(p: Project, library: str) -> dict:
    records = candidates(p, library)
    by_source = defaultdict(list)
    for rec in records:
        by_source[(rec['sdk'], rec['source'], rec['mw'])].append(rec)
    result = {'library': library, 'candidates': len({r['symbol'] for r in records}), 'prepared': [], 'errors': []}
    root = STATE_DIR / 'sdkimport' / library
    root.mkdir(parents=True, exist_ok=True)
    for (sdk_name, source, mw), group in by_source.items():
        sdk = ROOT / 'build/tools' / sdk_name
        pieces = declarations(preprocess(sdk, source, mw))
        functions = {next(iter(piece.names)): piece for piece in pieces if piece.kind == 'function'}
        for rec in group:
            try:
                function = functions[rec['sdk_symbol']]
                if re.search(r'\basm\b', masked(function.text)):
                    raise ValueError('assembly definition')
                mapping = bindings(p, rec)
                types, externs = dependency_closure(pieces, function, mapping)
                text = '\n\n'.join(types + externs + [re.sub(r'^static\s+', '', function.text)]) + '\n'
                text, absolutes = absolute_declarations(pieces, text)
                text = shared_storage(p, rec, pieces, text, mapping)
                text = replace_symbols(text, mapping)
                path = root / f"{rec['symbol']}.{sdk_name}.c"
                path.write_text(text)
                result['prepared'].append({**rec, 'path': str(path), 'bindings': mapping, 'absolutes': absolutes})
            except (KeyError, ValueError, StopIteration) as e:
                result['errors'].append({**rec, 'error': str(e)})
    (root / 'prepare.json').write_text(json.dumps(result, indent=2) + '\n')
    return result


def absolute_declarations(pieces: list, text: str) -> tuple:
    """Preserve MWCC absolute declarations; constants come from the linker script."""
    addresses = {}
    for piece in pieces:
        if piece.address is None:
            continue
        name = next(iter(piece.names))
        decl = 'extern ' + re.sub(r'^(?:static\s+|extern\s+)+', '', piece.text)
        if decl not in text:
            continue
        text = text.replace(decl, piece.text.rstrip(';') + f' : FZGX_ADDR_{name};')
        addresses[name] = piece.address
    if addresses:
        text = '#include "sdk_addresses.h"\n\n' + text
    return text, addresses


def shared_storage(p: Project, rec: dict, pieces: list, text: str, mapping: dict) -> str:
    """Recover a compiler-generated data base as a typed aggregate, checking retail layout."""
    anchors = [n for n in mapping if n.startswith('.')]
    if not anchors:
        return text
    obj = p.build_dir / 'sdkmatch' / rec['sdk'] / Path(rec['source']).with_suffix('.o')
    symbols = Elf(obj.read_bytes()).symbols()
    retail = list(p.symbols('main').values())
    for anchor in anchors:
        source = next(s for s in symbols if s['name'] == anchor)
        dest = p.symbols('main')[mapping[anchor]]
        fields, cursor, replacements = [], 0, {}
        tag = 'SDK_' + Path(rec['source']).stem + '_' + re.sub(r'\W', '_', anchor)
        local = 'sdk_storage_' + re.sub(r'\W', '_', anchor)
        for s in sorted(symbols, key=lambda s: s['value']):
            if s['shndx'] != source['shndx'] or s['info'] & 15 != 1 or s['value'] < source['value']:
                continue
            offset = s['value'] - source['value']
            if not any(t.addr == dest.addr + offset and t.size == s['size'] for t in retail):
                raise ValueError(f"data-base layout differs: {anchor} + {offset:#x} ({s['name']})")
            piece = next(x for x in pieces if x.kind == 'object' and s['name'] in x.names)
            decl = re.sub(r'^(?:static\s+|extern\s+)+', '', piece.text.split('=', 1)[0].strip().rstrip(';'))
            if offset < cursor:
                raise ValueError(f"overlapping data-base fields: {s['name']}")
            if offset > cursor:
                fields.append(f'unsigned char sdk_padding_{cursor}[{offset - cursor}];')
            field = 'sdk_' + s['name']
            fields.append(replace_symbols(decl, {s['name']: field}) + ';')
            replacements[s['name']] = f'({local}->{field})'
            text = text.replace('extern ' + decl + ';', '')
            cursor = offset + s['size']
        # Place the aggregate after its type dependencies and before function bodies.
        decl = 'struct ' + tag + ' {\n' + '\n'.join(fields) + '\n};\nextern struct ' + tag + ' ' + mapping[anchor] + ';\n\n'
        index = next((i for i in range(len(text)) if text.startswith('static inline ', i)), -1)
        if index < 0:
            signature = next(x.signature for x in pieces if x.kind == 'function' and rec['sdk_symbol'] in x.names)
            index = text.index(re.sub(r'^static\s+', '', signature))
        text = text[:index] + decl + text[index:]
        for piece in declarations(text):
            if piece.kind == 'function' and set(IDENT.findall(masked(piece.text))) & replacements.keys():
                body = piece.text.replace('{', '{\nstruct ' + tag + '* ' + local + ' = &' + mapping[anchor] + ';\n', 1)
                text = text.replace(piece.text, body)
        mapping.update(replacements)
    return text


def format_c(text: str) -> str:
    import shutil
    formatter = shutil.which('clang-format')
    if formatter is None:
        cp = subprocess.run(['xcrun', '--find', 'clang-format'], text=True, capture_output=True)
        formatter = cp.stdout.strip() if cp.returncode == 0 else None
    if not formatter:
        raise RuntimeError('clang-format is required to format imported SDK C')
    # MWCC's absolute-declaration colon is not a bitfield. Hide it from the formatter.
    text = re.sub(r' : (FZGX_ADDR_\w+);', r' /* SDK_ABSOLUTE \1 */;', text)
    cp = subprocess.run([formatter, '--style={BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 100, SortIncludes: Never}'],
                        input=text, text=True, capture_output=True, check=True)
    return re.sub(r' /\* SDK_ABSOLUTE (FZGX_ADDR_\w+) \*/\s*;', r' : \1;', cp.stdout).rstrip() + '\n'


def materialize(result: dict) -> list:
    """Adapt reference C to the project's Dolphin interface; retain TU-local declarations."""
    header = {'card': 'dolphin/card/CARDPriv.h', 'os': 'dolphin/os.h',
              'exi': 'dolphin/exi.h', 'si': 'dolphin/si.h'}[result['library']]
    if not (ROOT / 'include' / header).exists():
        raise ValueError(f'add the project-owned interface {header} before importing {result["library"]}')
    provided = set(BASE_TYPES)
    shared_prototypes = set()
    for path in (ROOT / 'include/dolphin').rglob('*.h'):
        for piece in declarations(path.read_text()):
            if piece.kind == 'type':
                provided.update(piece.names)
            elif piece.kind == 'prototype':
                shared_prototypes.update(piece.names)
    output = []
    for rec in result['prepared']:
        pieces = declarations(Path(rec['path']).read_text())
        used = set(IDENT.findall(masked('\n'.join(x.text for x in pieces if x.kind != 'prototype'))))
        body = []
        for piece in pieces:
            if piece.kind == 'type':
                continue
            if piece.kind == 'prototype' and (piece.names & shared_prototypes or not piece.names & used):
                continue
            text = piece.text
            if piece.address is not None:
                text = text.rstrip(';') + f' : {piece.address};'
            text = re.sub(r'(?m)^(.*\bgoto\b.*)$', r'\1 // fzgx-allow: S1 SDK error cleanup path', text)
            text = re.sub(r'(?m)^(.*\bvolatile\b.*)$', r'\1 // fzgx-allow: S2 SDK asynchronous state', text)
            # This SDK revision uses the public DVDDiskID field names.
            text = re.sub(r'(->|\.)game_name\b', r'\1gameName', text)
            body.append(text)
        needed = set(IDENT.findall(masked('\n'.join(body)))) - provided
        selected = set()
        while True:
            new = {i for i, piece in enumerate(pieces)
                   if piece.kind == 'type' and piece.names & needed and not piece.names & provided} - selected
            if not new:
                break
            selected.update(new)
            for i in new:
                needed.update(set(IDENT.findall(masked(pieces[i].text))) - provided)
        local_types = [pieces[i].text for i in sorted(selected)]
        prefix = f'#include <{header}>\n'
        if rec['absolutes']:
            prefix += '#include "sdk_addresses.h"\n'
        path = Path(rec['path']).with_name(Path(rec['path']).stem + '.import.c')
        path.write_text(format_c(prefix + '\n' + '\n\n'.join(local_types + body)))
        output.append({**rec, 'path': str(path)})
    return output


def install_addresses(p: Project, records: list) -> None:
    path = p.module_config_dir('main') / 'ldscript.tpl'
    text = path.read_text()
    existing = {name: int(value, 16) for name, value in
                re.findall(r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', text, re.M)}
    additions = {}
    for rec in records:
        for name, address in rec['absolutes'].items():
            if name in existing and existing[name] != address:
                raise ValueError(f'conflicting absolute binding: {name}')
            if name not in existing:
                additions[name] = address
    if additions:
        lines = '\n    /* SDK absolute globals; configure.py generates their C constants. */\n'
        lines += ''.join(f'    {name} = 0x{value:08X};\n' for name, value in sorted(additions.items()))
        text = text.replace('\n}\n\nFORCEACTIVE', lines + '}\n\nFORCEACTIVE')
        path.write_text(text)
    cp = oracle.configure(p)
    if cp.returncode:
        raise RuntimeError(cp.stdout + cp.stderr)


def run(p: Project, library: str, do_submit: bool = True) -> dict:
    result = prepare(p, library)
    records = materialize(result)
    install_addresses(p, records)
    result.update(matched=[], still=[], bytes=0)
    groups = defaultdict(list)
    for rec in records:
        groups[(rec['sdk'], rec['mw'])].append(rec)
    chosen = set()
    for (_, mw), group in groups.items():
        group = [r for r in group if r['symbol'] not in chosen]
        checks = oracle.check_many(p, [(r['symbol'], Path(r['path'])) for r in group],
                                   max_diff_lines=10, mw_version=mw, extra_cflags=FLAGS)
        for rec in group:
            check = checks[rec['symbol']]
            reason = oracle.unit_fully_matches(check)
            if reason:
                result['still'].append({**rec, 'reason': reason, 'check': check.to_json()})
                continue
            if do_submit:
                work = p.work_path(rec['symbol'])
                work.parent.mkdir(parents=True, exist_ok=True)
                work.write_text(Path(rec['path']).read_text())
                accepted = api.submit(p, rec['symbol'], agent='sdkimport', harness='fzgx', model='sdkimport',
                                      message=f"SDK C import: {rec['sdk']}/{rec['source']}:{rec['sdk_symbol']}",
                                      mw_version=mw, extra_cflags=FLAGS)
                if not accepted.get('ok'):
                    result['still'].append({**rec, 'reason': accepted})
                    continue
            chosen.add(rec['symbol'])
            result['bytes'] += rec['size']
            sdk = ROOT / 'build/tools' / rec['sdk']
            revision = subprocess.run(['git', 'rev-parse', 'HEAD'], cwd=sdk, text=True,
                                      capture_output=True, check=True).stdout.strip()
            result['matched'].append({**rec, 'revision': revision, 'submitted': do_submit})
            print(f"sdkimport: {rec['symbol']} ({rec['size']} bytes)", flush=True)
    result['still'] = [r for r in result['still'] if r['symbol'] not in chosen]
    report = STATE_DIR / 'sdkimport' / library / 'result.json'
    report.write_text(json.dumps(result, indent=2) + '\n')
    if do_submit and chosen:
        dest = ROOT / 'state/sdkimports' / (library + '.json')
        dest.parent.mkdir(parents=True, exist_ok=True)
        old = json.loads(dest.read_text()) if dest.exists() else {}
        for rec in result['matched']:
            old[rec['symbol']] = {k: v for k, v in rec.items() if k not in ('path', 'submitted')}
        dest.write_text(json.dumps(old, indent=2, sort_keys=True) + '\n')
    return {k: v for k, v in result.items() if k != 'prepared'}


def consolidate(p: Project, library: str) -> dict:
    """Collapse only source files whose emitted functions all have proven retail identities."""
    from . import collapse
    by_addr = {s.addr: s for s in p.functions('main')}
    result = {'collapsed': [], 'partial': [], 'failed': []}
    done = set()
    for sdk in ('mkdd', 'tww'):
        data = json.loads((ROOT / 'state/seeds' / f'sdkmatch_{sdk}.json').read_text())
        sources = sorted({s for hit in data['hits'] for s in hit['sources'] if f'/{library}/' in s})
        for source in sources:
            stem = Path(source).stem
            if stem in done:
                continue
            hits = {h['sdk'][0]: by_addr[h['addr']] for h in data['hits']
                    if source in h['sources'] and h['addr'] in by_addr}
            obj = p.build_dir / 'sdkmatch' / sdk / Path(source).with_suffix('.o')
            functions = sorted((s for s in Elf(obj.read_bytes()).symbols()
                                if s['info'] & 15 == 2 and s['size'] and s['shndx']), key=lambda s: s['value'])
            missing = [s['name'] for s in functions if s['name'] not in hits]
            if missing:
                result['partial'].append({'sdk': sdk, 'source': source, 'missing': missing})
                continue
            members = [hits[s['name']] for s in functions]
            units = p.load_units()
            old = [u for u in units if any(s.name in u['symbols'] for s in members)]
            if len(old) == 1 and old[0].get('collapsed'):
                done.add(stem)
                continue
            if len(old) != len(members) or any(u['status'] != 'matching' or u.get('asm') for u in old):
                continue
            lo, hi = min(s.addr for s in members), max(s.end for s in members)
            if {s.name for s in p.functions('main') if lo <= s.addr < hi} != {s.name for s in members}:
                result['failed'].append({'source': source, 'error': 'retail functions are not contiguous'})
                continue
            pieces = declarations(preprocess(ROOT / 'build/tools' / sdk, source, data['mw']))
            mapping = {}
            rec = dict(sdk=sdk, source=source, mw=data['mw'], symbol=members[0].name,
                       sdk_symbol=functions[0]['name'], size=hi-lo)
            try:
                for fn in functions:
                    m = bindings(p, {**rec, 'symbol': hits[fn['name']].name, 'sdk_symbol': fn['name']})
                    for name, target in m.items():
                        if name in mapping and mapping[name] != target:
                            raise ValueError(f'inconsistent whole-TU binding: {name}')
                        mapping[name] = target
                bodies = [x for x in pieces if x.kind == 'function' and x.names & hits.keys()]
                combined = Piece('function', set(), '\n'.join(x.text for x in bodies))
                types, externs = dependency_closure(pieces, combined, mapping)
                text = '\n\n'.join(types + externs + [re.sub(r'^static\s+', '', x.text) for x in bodies])
                text, absolutes = absolute_declarations(pieces, text)
                text = shared_storage(p, rec, pieces, text, mapping)
                path = STATE_DIR / 'sdkimport' / library / f'{stem}.{sdk}.whole.c'
                path.write_text(replace_symbols(text, mapping))
                row = {**rec, 'path': str(path), 'bindings': mapping, 'absolutes': absolutes}
                imported = materialize({'library': library, 'prepared': [row]})[0]
                install_addresses(p, [row])
                compiled = path.with_suffix('.o')
                cp = oracle.compile_source(p, 'main', Path(imported['path']), compiled, data['mw'], FLAGS)
                if cp.returncode:
                    raise ValueError((cp.stdout + cp.stderr)[-1000:])
                for sym in members:
                    check = oracle._diff(p, 'main', sym.name, '', 5,
                                         target=p.target_object_for(sym), base=compiled)
                    check.uncarved = True
                    if oracle.unit_fully_matches(check):
                        raise ValueError(f'whole-TU mismatch: {sym.name}: {check.percent}: {check.diff}')
            except (ValueError, KeyError, StopIteration) as e:
                result['failed'].append({'source': source, 'error': str(e)})
                continue
            tu_source = 'dol/' + stem + '.c'
            tu_path = ROOT / 'src' / tu_source
            if tu_path.exists() and tu_source not in {u['source'] for u in old}:
                result['failed'].append({'source': source, 'error': 'TU destination already exists'})
                continue
            previous_source = tu_path.read_text() if tu_path.exists() else None
            tpath = p.module_config_dir('main') / 'tus.json'
            tus = json.loads(tpath.read_text()) if tpath.exists() else {'module': 'main', 'tus': []}
            entry = {'file': stem + '.c', 'text': [lo, hi], 'functions': [s.name for s in members],
                     'sdk': sdk, 'source': source}
            tus['tus'] = [t for t in tus['tus'] if t['file'] != entry['file']] + [entry]
            tpath.write_text(json.dumps(tus, indent=2) + '\n')
            tu_path.write_text(Path(imported['path']).read_text())
            changed = [dict(u, tu=tu_source, mw_version=data['mw'], extra_cflags=FLAGS.split()) if u in old else u for u in units]
            p.save_units(changed)
            collapsed = collapse.collapse(p, tu_source)
            if not collapsed['ok']:
                p.save_units(units)
                if previous_source is None:
                    tu_path.unlink()
                else:
                    tu_path.write_text(previous_source)
                oracle.configure(p)
                oracle.relink(p)
                result['failed'].append({'source': source, 'error': collapsed})
                continue
            ledger = Ledger()
            for sym in members:
                ledger.db.execute('UPDATE functions SET unit=? WHERE symbol=?', (tu_source, p.key(sym)))
            for u in old:
                if u['source'] != tu_source:
                    (ROOT / 'src' / u['source']).unlink(missing_ok=True)
            result['collapsed'].append({'source': source, 'sdk': sdk, 'tu': tu_source,
                                        'functions': len(members), 'bytes': hi-lo})
            done.add(stem)
            print(f'sdkimport: collapsed {tu_source} ({len(members)} functions)', flush=True)
    (STATE_DIR / 'sdkimport' / library / 'consolidated.json').write_text(json.dumps(result, indent=2) + '\n')
    return result
