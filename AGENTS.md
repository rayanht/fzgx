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

## Matcher (one function per session)

Headless Codex matchers use `tools/orchestrate.py` and one shared local Codex
app server. The runner claims each function, installs its saved C, and supplies
context plus the initial object diff before starting the model. Matchers have
no shell or filesystem tools. Their dynamic tools are `write_unit(source)`,
`patch_unit(old, new)`, `check(versions)`, and `release(reason)`; the host binds
the function and identity, so models cannot select another unit.

Continue the supplied C. Writes compile and diff immediately. A full oracle
match submits automatically; check/stale limits save and release automatically.
The host interrupts the turn before returning a terminal tool result. No claim,
submit, administrative release, or final RESULT message is required from the
model. Voluntary release is for a concrete technical obstacle. Numeric limits
belong in runner flags and tooling, never matcher prompts. Compiler probes
retain the selected compiler and archive the body with its compiler settings.

The manual CLI (`uv run tools/fzgx.py ...`) and MCP server
(`tools/fzgx_mcp.py`) retain claim/context/check/submit/release operations for
humans and other harnesses. `fzgx verify` relinks all 16 targets and verifies
every hash before committing accepted source. Batches verify every 60 seconds by
default and drain again on exit; completed matches do not wait for outlier models.
Rules enforced by tooling:
no hardcoded addresses, no inline asm, no writes outside the assigned work copy.

## Librarian (serial; stronger model)

Applies name proposals (`fzgx names`), promotes shared structs into
`include/`, merges fully matched ranges into translation units, adjusts data
ownership in `splits.txt`, appends to `docs/MWCC_IDIOMS.md`. Always ends with
`python3 configure.py && ninja` printing `16 files OK`, `fzgx lint`,
`fzgx snapshot`, and a concise commit describing the actual changes.

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
orchestrator from provider usage events (provider-reported cost when available,
otherwise an explicitly labeled token-price estimate).

Model sessions (`--parallel`) and local tool processes (`--tool-parallel`) have
separate limits. App-server JSON-RPC command backpressure is separate again;
a burst of thread starts must not prevent completed turns from being stopped.
Never modify personal Codex configuration or auth. All worker overrides stay
inside the runner. Do not use in-process subagents. See
`docs/CODEX_APP_SERVER.md` for transport, diagnostics, and failure handling.
