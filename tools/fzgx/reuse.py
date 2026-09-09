"""Reuse verified C when retail functions differ only in their referenced symbols."""

from __future__ import annotations

import re
from collections import defaultdict
from typing import Optional

from . import api, oracle
from .ledger import Ledger
from .project import Project, STATE_DIR


def replace_symbols(text: str, mapping: dict) -> str:
    if not mapping:
        return text
    names = "|".join(re.escape(n) for n in sorted(mapping, key=len, reverse=True))
    return re.sub(r"(?<![\w.$])(" + names + r")(?![\w.$])", lambda m: mapping[m[0]], text)


def shape(fn) -> tuple:
    # Preserve registers, immediates, relocation kinds, addends, and branch destinations.
    # Only names change; a shared global must remain shared at every reference site.
    names = {name: f"$S{i}" for i, name in enumerate(fn.refs)}
    labels = {line[:-1]: f"$L{i}" for i, line in enumerate(fn.asm) if line.endswith(":")}
    return tuple(replace_symbols(line.split(": ", 1)[-1], names | labels)
                 for line in fn.asm if not line.endswith(":"))


def run(p: Project, max_size: int = 255, module: Optional[str] = None, do_submit: bool = True) -> dict:
    ledger = Ledger()
    groups = defaultdict(list)
    for row in ledger.db.execute("SELECT symbol, module, status FROM functions WHERE size<=? "
                                 "AND status IN ('matched', 'unmatched')", (max_size,)):
        key, mod, status = row
        fn = p.function_asm(mod).get(key.split(":")[-1])
        if fn is not None:
            groups[shape(fn)].append((key, mod, status, fn))
    scratch = STATE_DIR / "reuse"
    scratch.mkdir(exist_ok=True)
    sources = {}
    donors = {}
    for group in groups.values():
        matched = [r for r in group if r[2] == "matched"]
        for key, mod, status, fn in group:
            if status != "unmatched" or (module and mod != module):
                continue
            for donor, donor_mod, _, donor_fn in sorted(matched, key=lambda r: (r[1] != mod, r[0])):
                unit = p.unit_of(donor_fn.symbol)
                if unit is None or (p.unit_record(unit) or {}).get("asm"):
                    continue
                text = api._canonical_text(p, unit)
                mapping = dict(zip(donor_fn.refs, fn.refs))
                mapping[donor_fn.symbol.name] = fn.symbol.name
                source = scratch / (key.replace(":", "__") + ".c")
                source.write_text(replace_symbols(text, mapping))
                sources[key] = source
                donors[key] = donor
                break
    checks = oracle.check_many(p, list(sources.items()))
    out = {"candidates": len(sources), "matched": [], "still": []}
    for key, source in sources.items():
        result = checks[key]
        reason = oracle.unit_fully_matches(result)
        if reason:
            out["still"].append((key, reason[:160]))
            continue
        if do_submit:
            work = p.work_path(key)
            work.parent.mkdir(parents=True, exist_ok=True)
            work.write_text(source.read_text())
            accepted = api.submit(p, key, agent="reuse", message=f"same retail instruction shape as {donors[key]}",
                                  harness="fzgx", model="reuse", mw_version=result.mw_version,
                                  extra_cflags=result.extra_cflags)
            if not accepted.get("ok"):
                out["still"].append((key, accepted.get("error")))
                continue
        out["matched"].append((key, donors[key]))
    return out
