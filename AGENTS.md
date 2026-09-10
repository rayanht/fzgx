# Agent contract (Codex and any other harness)

This repository is driven by a small CLI so that any agent harness can do the
same work. Read `CLAUDE.md` for the project overview; this file is the
contract a subagent must follow. The Claude Code versions of these roles live
in `.claude/agents/*.md` and say the same things.

Do not add unit tests to this repository. Validate tooling changes against real
functions with MWCC, retail object diffs, `fzgx lint`, and the 16-target hash check.
Commit completed work locally before reporting it finished. Include the tooling,
provenance, and dependent source changes needed to reproduce generated matches.
Never push.

## Matcher (one function per session; cheap tier: GPT 5.6 Luna, Haiku 4.5)

Matchers get **no shell**. Their only tools are the `fzgx` MCP server
(`tools/fzgx_mcp.py`, registered in `.mcp.json` for Claude Code; for Codex add
to `~/.codex/config.toml`:

```toml
[mcp_servers.fzgx]
command = "uv"
args = ["run", "tools/fzgx_mcp.py"]
cwd = "/path/to/fzero_gx"
```

) plus a read-only file tool. Tools: `claim`, `context`, `read_unit`,
`write_unit`, `check`, `submit`, `release`. `write_unit` only accepts the unit
the caller has claimed; `submit` queues a matched unit, and `fzgx verify` relinks
all 16 targets and verifies every hash before committing the batch. The same operations exist as CLI subcommands
(`uv run tools/fzgx.py ...`) for humans and the orchestrator.

Loop: `claim` (returns the context bundle) → `write_unit` (complete file:
`#include "types.h"`, externs, minimal structs, the function; compiles and
diffs immediately, one call per iteration) → `submit(..., names=[...])` or
`release(reason)`. The runner and server enforce attempt limits; do not put limit
guidance in matcher prompts. `check(symbol, versions="all")` only
probes compiler versions. No messages, no summaries: the final line is exactly
`RESULT: matched|released SYMBOL <percent>% checks=<n>`.

Rules enforced by the tools, not by prose: no hardcoded addresses (lint A1/A2),
no inline asm, no edits outside the claimed unit, no build or git access.

## Librarian (serial; stronger model)

Applies name proposals (`fzgx names`), promotes shared structs into
`include/`, merges fully matched ranges into translation units, adjusts data
ownership in `splits.txt`, appends to `docs/MWCC_IDIOMS.md`. Always ends with
`python3 configure.py && ninja` printing `16 files OK`, `fzgx lint`,
`fzgx snapshot`, and a commit prefixed `librarian:`.

## Triage

For functions with `attempts >= 3`: `fzgx block SYMBOL --issue --reason "..."`
and a row in `state/blocked.md`.

## Orchestrator

Prioritize deterministic SDK C imports (CARD, then OS, EXI, SI) regardless of
function size. Under-256-byte functions (`--max-size 255`) remain useful repair
corpora, not a gate on identified larger functions. Prefer deterministic work: `fzgx trivial`, `fzgx reuse`, and size-filtered `fzgx sweep`/`fzgx stuck`;
fix recurring failure modes in the tooling before spending agents on them.
Picks remaining work with `fzgx --json inventory --status unmatched --max-size N`
(smallest first), runs 48 Luna workers via the headless orchestrator, then librarian,
then triage; writes `docs/batches/<date>.md` from `fzgx report` and commits
`state/ledger.json` via `fzgx snapshot`. Budget per batch is enforced by the
orchestrator from the `--cost-usd` values matchers report.
