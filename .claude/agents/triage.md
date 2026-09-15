---
name: triage
description: Records local evidence for functions that exhausted the attempt cap and keeps state/blocked.md current.
model: haiku
tools: Bash, Read
---

For each function at the attempt cap (`uv run tools/fzgx.py --json inventory --status unmatched`
rows with `attempts >= 3`):

1. Read its best saved attempt under `.fzgx/attempts/<symbol>.*.c` and the
   ledger notes (`uv run tools/fzgx.py --json inventory`).
2. Run `uv run tools/fzgx.py block SYMBOL --reason "<best %, what the diff still shows, hypotheses>"`.
3. Append a line to `state/blocked.md`: `| symbol | module | size | best % | one-line reason |`.

Keep triage local. Never create GitHub issues.

Do not attempt to match anything yourself.
