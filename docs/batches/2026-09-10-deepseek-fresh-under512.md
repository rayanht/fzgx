# Fresh under-512-byte DeepSeek batch

Batch `deepseek-fresh-under512-128-20260910-095154` uses 128 Codex workers, DeepSeek-V4.1-Flash
(`deepseek-flash`, high effort), 16 matcher checks and four consecutive stale
checks. Timeout is 7,200 seconds per worker.

The pool is 165 functions / 59,648 bytes, selected from 1,556 unmatched
ledger rows smaller than 512 bytes. The selector excludes 1364 rows with
prior saved matcher C or successful checks, 23 with SDK signatures/prepared
imports/ranked donor candidates, and four obsolete runtime-helper ledger names.
This is fresh reconstruction work, not another near-match repair sweep.

`uv run tools/seeds/untouched.py --max-size 511 --output PATH` freezes the
never-give-up lifter's complete output and a SHA-256 for every function. All 165
functions received drafts; 79 contain unresolved instruction markers. Claims
install the seed as the worker's private C and tell it to complete missing
lowering while preserving recovered types, names and structure. The seed
transport was exercised on `fn_3_1A0F4`; its generated C compiled and scored
77.89796% without modifying its prior status or attempt count.

Accepted C installation now takes a shared submission lock: independent
functions can modify the same TU, splits and symbol table. Work-copy checks
remain independent. Pool-match tool outcomes are also recognized as successful
worker results. No unit tests were added.

Local artifacts:

- Seeds and selection evidence: `.fzgx/seeds/deepseek-fresh-under512-128`.
- Active-run metadata: `.fzgx/runs/deepseek-fresh-under512-active.json`.
- Worker logs: `.fzgx/runs/deepseek-fresh-under512-128-20260910-095154/`.
- Resource samples: `.fzgx/runs/deepseek-fresh-under512-128-20260910-095154-resources.jsonl`.

The initial 128-worker startup snapshot used 633 processes and 43,989 MiB
summed RSS (43.0 GiB), with 1,243.5% aggregate process CPU. After context
generation, an idle model-wait snapshot used 514 processes and 29,543 MiB
(28.9 GiB). Summed RSS can count shared pages more than once.

## Completed-worker timing sample

The `fn_80008A4C` worker matched a 348-byte function after three checks in
161.5 seconds. Its timestamped Codex rollout recorded 147.513 seconds inside
the task; the remaining 13.987 seconds cover process startup, exit and runner
bookkeeping. Local MCP durations were 30.673 seconds for claim/context,
0.418 + 0.333 + 0.346 seconds for the three compile/check calls, and 0.402
seconds for submission. The remaining 115.341 seconds inside the task were
model/API/harness intervals, including an unrelated `get_goal` call. Provider
queuing, inference and network time cannot be separated from this transcript.

There were seven model responses, 96,684 input tokens (87,168 cached), and
3,983 output tokens, of which 2,470 were reported as reasoning. The first
edit took 39.229 seconds after claim returned, and the frame-size correction
took another 19.138 seconds after the first check returned. It patched a
local declaration without updating its use, spending a failed check and
another model round trip to repair that use. The matching tool result was
ready 32.718 seconds before the Codex task ended.

The change restored one omitted call and reduced a five-word stack local to
one word. This sample identifies context generation and model round trips
as the latency targets, not compilation. The worker's unnecessary goal-tool
call prompted disabling `goals` for future launches; this running batch keeps
its original process configuration. Derived timing data are in
`.fzgx/runs/fn_80008A4C-timing.json`.
