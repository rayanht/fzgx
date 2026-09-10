"""Rank whole-function and partial donor overlap without treating it as a match."""

from __future__ import annotations

import difflib
import json
import math
from collections import defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

from . import sourcealign
from .ledger import Ledger
from .project import STATE_DIR


def compare(job):
    row, words, candidates = job
    ops = tuple(map(sourcealign.operation, words))
    operands = tuple(map(sourcealign.operand_shape, words))
    results = []
    for donor, other, overlap, containment in candidates:
        source = tuple(map(sourcealign.operation, other))
        matcher = difflib.SequenceMatcher(None, source, ops, autojunk=False)
        blocks = [block for block in matcher.get_matching_blocks() if block.size >= 8]
        count = sum(block.size for block in blocks)
        diverse = [block for block in blocks if len(set(source[block.a:block.a + block.size])) >= 4]
        # Repeated initialization and structure copies otherwise overwhelm the
        # ranking even when they implement unrelated behavior.
        unique_grams = {source[i:i + 4] for block in diverse
                        for i in range(block.a, block.a + block.size - 3)}
        operand_matcher = difflib.SequenceMatcher(None, tuple(map(sourcealign.operand_shape, other)),
                                                operands, autojunk=False)
        results.append(donor | dict(opcode_similarity=matcher.ratio(), operand_similarity=operand_matcher.ratio(),
                                   weighted_overlap=overlap, containment=containment, source_size=4 * len(other),
                                   block_bytes=4 * count, target_coverage=count / len(words),
                                   diverse_block_bytes=4 * sum(block.size for block in diverse),
                                   unique_block_grams=len(unique_grams),
                                   source_coverage=count / len(other),
                                   longest_block_bytes=4 * max((block.size for block in blocks), default=0),
                                   blocks=[dict(source=4 * a, target=4 * b, size=4 * n,
                                                distinct_operations=len(set(source[a:a + n]))) for a, b, n in blocks]))
    results.sort(key=lambda r: (-r['unique_block_grams'], -r['operand_similarity'], -r['block_bytes']))
    return row | dict(candidates=results)


def run(p, minimum=256, roots=(), rel_only=False):
    donors = [row for row in sourcealign.catalog(p, minimum)
              if not roots or any(Path(row['source']).is_relative_to(root) for root in roots)]
    index = defaultdict(list)
    for i, row in enumerate(donors):
        for gram, count in sourcealign.grams(row['words']).items():
            index[gram].append((i, count))
    weights = {gram: math.log1p(len(donors) / len(rows)) for gram, rows in index.items()}
    totals = [sum(weights[gram] * n for gram, n in sourcealign.grams(row['words']).items()) for row in donors]
    ledger = Ledger()
    targets = defaultdict(dict)
    for module in p.modules:
        if rel_only and module == 'main':
            continue
        for sym in p.functions(module):
            row = ledger.get(p.key(sym))
            if sym.size >= minimum and row and row['status'] == 'unmatched':
                obj = p.target_object_for(sym)
                if obj:
                    targets[obj][sym.name] = sym

    def jobs():
        for obj, names in targets.items():
            for name, words in sourcealign.instructions(obj, minimum).items():
                if name not in names:
                    continue
                query = sourcealign.grams(words)
                total = sum(weights.get(gram, math.log1p(len(donors))) * n for gram, n in query.items())
                hits = defaultdict(float)
                for gram, n in query.items():
                    for i, count in index.get(gram, ()):
                        hits[i] += weights[gram] * min(n, count)
                whole = sorted(hits, key=lambda i: -2 * hits[i] / (total + totals[i]))
                partial = sorted(hits, key=lambda i: -hits[i] / min(total, totals[i]))
                selected = {}
                # Compiler variants must not consume the shortlist before distinct
                # source functions have a chance to be aligned.
                for ranked in (whole, partial):
                    seen = set()
                    for i in ranked:
                        donor = donors[i]
                        identity = donor['sdk'], donor['source'], donor['sdk_symbol']
                        if identity in seen:
                            continue
                        seen.add(identity)
                        selected.setdefault(identity, i)
                        if len(seen) == 6:
                            break
                sym = names[name]
                yield (dict(symbol=p.key(sym), module=sym.module, size=sym.size), words,
                       [({k: v for k, v in donors[i].items() if k != 'words'}, donors[i]['words'],
                         2 * hits[i] / (total + totals[i]), hits[i] / min(total, totals[i]))
                        for i in selected.values()])

    directory = STATE_DIR / 'sourcealign'
    directory.mkdir(parents=True, exist_ok=True)
    output = directory / 'fuzzy.jsonl'
    results = []
    with output.open('w') as stream, ProcessPoolExecutor(max_workers=8) as pool:
        for row in pool.map(compare, jobs(), chunksize=4):
            results.append(row)
            stream.write(json.dumps(row) + '\n')
            stream.flush()
            if len(results) % 100 == 0:
                print(f'{len(results)} REL/target functions ranked', flush=True)
    ranked = sorted((row | dict(best=row['candidates'][0]) for row in results if row['candidates']),
                    key=lambda row: (-row['best']['unique_block_grams'], -row['best']['operand_similarity']))
    whole = sorted((dict(symbol=row['symbol'], module=row['module'], size=row['size'],
                         best=max(row['candidates'], key=lambda c: c['opcode_similarity']))
                    for row in results if row['candidates']), key=lambda row: -row['best']['opcode_similarity'])
    summary = dict(donors=len(donors), targets=len(results), roots=list(roots), rel_only=rel_only,
                   minimum=minimum, results=str(output),
                   opcode_buckets={str(threshold): sum(any(c['opcode_similarity'] >= threshold for c in row['candidates'])
                                                       for row in results) for threshold in (0.5, 0.6, 0.7, 0.8, 0.9)},
                   top_partial=ranked[:30], top_whole=whole[:30])
    (directory / 'fuzzy.json').write_text(json.dumps(summary, indent=2) + '\n')
    return {k: v for k, v in summary.items() if not k.startswith('top_')}
