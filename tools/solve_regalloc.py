#!/usr/bin/env python3
"""Benchmark bounded register repair on a frozen diagnose_batch corpus; no model calls."""
import argparse
import json
from pathlib import Path

from fzgx import oracle, regsolve
from fzgx.project import Project


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--corpus', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--probes', type=int, default=32)
    args = parser.parse_args()
    if args.probes < 1:
        parser.error('--probes must be positive')
    inputs = json.loads((args.corpus / 'inputs.json').read_text())
    results = json.loads((args.corpus / 'results.json').read_text())
    selected = {s: dict(record, object=results[s]['baseline']['object']) for s, record in inputs.items()
                if results[s]['baseline']['pure'] in ('regalloc', 'value-flow')}
    with oracle.build_lock():
        print(json.dumps(regsolve.batch(Project(), selected, args.output.resolve(), args.probes), indent=2))
