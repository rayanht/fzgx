"""Independent field-offset probes for SDK revisions with reordered record fields."""

import re
import struct

from . import oracle, sdkimport
from .poolfix import Elf


def independent(p, rec, text, directory):
    """Keep a record's ABI while exposing independently adjustable member offsets.

    The compiler supplies offsetof/sizeof values. An unchanged-code check below
    certifies the probe representation before any retail constraints are applied.
    """
    from .sourcealign import instructions
    accessed = set(re.findall(r'(?:->|\.)\s*(\w+)', sdkimport.masked(text)))
    records = []
    queries = []
    pieces = sdkimport.declarations(text)
    owners = {}
    for piece in pieces:
        if piece.kind == 'type' and '{' in piece.text:
            for name in re.findall(r'\b(\w+)\s*(?:\[[^;\]]*\]\s*)*;', piece.text):
                owners.setdefault(name, set()).add(piece.text)
    for piece in pieces:
        if piece.kind != 'type':
            continue
        match = re.fullmatch(r'(?P<typedef>typedef\s+)?(?P<kind>struct|union)\s*(?P<tag>\w+)?\s*'
                             r'\{(?P<body>[^{}]*)\}\s*(?P<alias>\w+)?\s*;', piece.text, re.S)
        if not match:
            continue
        typename = match['alias'] if match['typedef'] else match['kind'] + ' ' + (match['tag'] or '')
        if not typename or not typename.strip() or match['typedef'] and not match['alias']:
            continue
        fields = []
        for declaration in match['body'].split(';'):
            declaration = declaration.strip()
            if not declaration:
                continue
            fp = re.search(r'\(\s*\*\s*(\w+)\s*\)', declaration)
            member = fp or re.search(r'\b(\w+)\s*(?:\[[^\]]*\]\s*)*$', declaration)
            if member and member[1] in accessed and ':' not in declaration:
                fields.append((member[1], declaration + ';'))
        if not fields:
            continue
        start = len(queries)
        queries.append(f'sizeof({typename})')
        queries.extend(f'(unsigned long)&(({typename}*)0)->{name}' for name, _ in fields)
        records.append((piece, match, fields, start))
    while True:
        selected = {piece.text for piece, _, _, _ in records}
        kept = [row for row in records if all(owners.get(name, set()) <= selected for name, _ in row[2])]
        if len(kept) == len(records):
            break
        records = kept
    if not records:
        raise ValueError('no flat records with accessed fields')
    directory.mkdir(parents=True, exist_ok=True)
    source = directory / 'offsets.c'
    source.write_text(text + '\nconst unsigned long sdk_layout_offsets[] = {\n' + ',\n'.join(queries) + '\n};\n')
    module = p.resolve(rec['symbol']).module
    compiled = oracle.compile_many(p, module, [source], directory / 'query', rec['mw'], rec.get('flags') or None)
    if source not in compiled:
        raise ValueError('record offset queries do not compile')
    elf = Elf(compiled[source].read_bytes())
    symbol = next(s for s in elf.symbols() if s['name'] == 'sdk_layout_offsets')
    section = elf.sections[symbol['shndx']]
    offset = section['offset'] + symbol['value']
    values = struct.unpack_from('>' + 'I' * len(queries), elf.data, offset)
    replacements = {}
    fields = {name for _, _, members, _ in records for name, _ in members}
    for piece, match, members, start in records:
        views = [f'unsigned char sdk_padding_extent[{values[start]}];']
        for (name, declaration), at in zip(members, values[start + 1:start + 1 + len(members)]):
            padding = f'unsigned char sdk_padding_{name}[{at}];\n' if at else ''
            views.append('struct {\n' + padding + declaration + '\n} view_' + name + ';')
        body = 'union {\n' + '\n'.join(views) + '\n} sdk_fields;'
        replacements[piece.text] = piece.text[:match.start('body')] + '\n' + body + '\n' + piece.text[match.end('body'):]
    # Rewrite original accesses only; declarations inserted below retain ordinary
    # member names and cannot recursively acquire another view prefix.
    adapted = re.sub(r'(->|\.)\s*(\w+)',
                     lambda m: m[1] + 'sdk_fields.view_' + m[2] + '.' + m[2] if m[2] in fields else m[0], text)
    for original, replacement in replacements.items():
        if original not in adapted:
            raise ValueError('record declaration contains field expressions')
        adapted = adapted.replace(original, replacement)
    candidate = directory / 'views.c'
    candidate.write_text(adapted)
    objects = oracle.compile_many(p, module, [candidate], directory / 'views', rec['mw'], rec.get('flags') or None)
    if candidate not in objects:
        raise ValueError('independent record views do not compile')
    old = instructions(compiled[source], 0)[rec['sdk_symbol']]
    new = instructions(objects[candidate], 0)[rec['sdk_symbol']]
    if old != new:
        raise ValueError('independent record views change baseline instructions')
    return adapted
