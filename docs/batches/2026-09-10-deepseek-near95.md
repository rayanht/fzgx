# DeepSeek replay of the Luna near-95% batch

Replayed the same 287 frozen C candidates from
`near95-under500-20260910-001452`, using Codex 0.153.4 with
DeepSeek-V4.1-Flash (`deepseek-flash`, high effort), at most 48 workers,
16 matcher checks and four consecutive stale checks. Claims installed each
original candidate, verified by SHA-256; no function started from a stub.

The consolidated comparison has 92 object matches and 195 releases. Each
selected result has a terminal tool outcome, stays within the requested
limits, and has no nested worker. Of those matches, 41 functions / 9,392 bytes
were unmatched before this experiment; the other 51 were already integrated.
Deterministic release repairs are included, as in the Luna batch.

| Run | Matches | Check / stale limits | Recorded-usage cost |
| --- | ---: | ---: | ---: |
| Original Luna | 63 / 287 | 128 / 32 | $7.025 estimate |
| Selected DeepSeek results | 92 / 287 | 16 / 4 | $5.290254 estimate |
| All DeepSeek runs, including interrupted work and retries | — | — | $11.041200 estimate |

The selected-result cost covers those workers; the batch total includes interrupted
workers and replays. Initial integration smoke runs and the API metadata probe
are outside this batch accounting.
Limits, harness fixes, recovered headers and deterministic repairs differ between
runs, so these results do not isolate model quality. Raw intermediate reports
include invalid trials and misleading crash labels; the consolidated result
supersedes their totals. Original Luna wall time was 1,167.3 seconds; interrupted
DeepSeek trials do not provide a comparable batch-throughput measurement.

DeepSeek's live Responses API returned token usage, with no dollar-cost field or
billing header. Pricing uses each recorded response's UTC timestamp: weekday
01:00–04:00 and 06:00–10:00 are peak, all other times half price. This experiment
was off-peak. Usage from failed turns is retained; request IDs deduplicate inherited
history. The total includes 506 root sessions and 20 unintended child sessions,
184,049,409 input tokens and 16,044,188 output tokens. Streams aborted before final
usage may incur additional unrecorded charges. Sources:
[pricing](https://api-docs.deepseek.com/quick_start/pricing/) and
[Codex integration](https://api-docs.deepseek.com/quick_start/agent_integrations/codex/).

## Failures fixed

- Parallel tool searches produced duplicate MCP namespaces and HTTP 400 errors.
  The catalog now loads the six matcher tools directly.
- Catalog `multi_agent_version=v2` enabled delegation despite disabled feature
  flags. Nested workers shared a function's scratch files. The catalog now uses
  `null`; calls also enforce assigned identity and serialize per function.
- Reclaims, compiler probes and failed compilations bypassed attempt accounting.
  They now obey the same stop rules; version probes check the current candidate.
- Models sometimes returned malformed RESULT lines after a successful tool release.
  The runner now reports the ledger's outcome and counters.
- Shadow submissions modified compiler options; prologue probes overwrote linked
  objects. Trials now preserve options and compile probes to scratch objects.
- Repeated shadow submits after completion could demote existing matched ledger
  rows. They now fail before any mutation; five affected rows were restored to
  their previously verified state. Existing C was retained.
- The earlier `forced_login_method="api"` override deleted shared ChatGPT auth.
  It is removed; provider credentials and overrides remain local to each run.

The final 14 workers using the corrected catalog all reached a terminal tool
outcome without crashing. No unit tests were added.

## Worker capacity

A 48-worker snapshot used 194 processes and 11,524.7 MiB summed RSS on this
128 GiB / 16-core Mac. For this small-function workload, linear projections are
30 GiB at 128 workers, 60 GiB at 256, and 586 GiB at 2,500. These are projections,
not tested capacities; summed RSS can count shared pages more than once.
The per-user process cap is 10,666, with approximately 940 user processes in the
later idle-batch snapshot. Four processes per worker also make 2,500 workers
impractical under that cap.

128 workers is the next useful measurement. Invoking native Codex and the venv
interpreter directly could remove the Node and uv wrappers, which accounted for
approximately 3.4 GiB at 48 workers. For substantially greater concurrency, use
a small number of persistent [Codex app-server](https://learn.chatgpt.com/docs/app-server)
processes, separate threads per function, client-handled matcher tools, a shared
bounded compiler pool and a request-level concurrency gate. Threads doing tool
work need not consume DeepSeek's 2,500-request allowance. This architecture has
not been implemented or load-tested in this change.

Profiling a real `context fn_1_6755C` also exposed repeated whole-type-set copies
in parameter validation. Membership checks now use the existing type dictionary.
Signature-index recovery fell from 12.669 to 4.547 profiled seconds; total context
time fell from 17.224 to 11.216 seconds, with byte-identical output. A shared tool
service can reuse the recovered index across workers.

## Integration and validation

All 53 saved exact candidates were imported through the existing claim/submit
path and link-verified in `d49833d`, with zero rejections: the 41 new comparison
matches / 9,392 bytes, plus 12 additional matches / 1,880 bytes saved during
interrupted trials. No reconstructed C was edited manually.

All 16 target hashes passed, `fzgx lint` reported zero findings, and
`ninja all_source progress build/GFZE01/report.json` succeeded. Matched code
increased from 505,192 to 516,464 of 2,929,056 bytes (17.63%); the report has
4,283 of 7,311 functions matched. The original 78 already matched functions in
the comparison remain matched and verified.

## Local artifacts

- Frozen inputs: `.fzgx/seeds/near95-under500-20260910-001452/manifest.json`.
- Consolidated comparison and cost accounting: `.fzgx/runs/deepseek-near95-comparison.json`.
- Saved-body hashes and compiler settings: `.fzgx/runs/deepseek-import-candidates.json`.
- Deterministic integration through `api.claim` / `api.submit`: `.fzgx/runs/deepseek-import.py`.
- Per-candidate import results: `.fzgx/runs/deepseek-import-results.json`.
- Before/after context profiles: `.fzgx/runs/context-profile*.pstats` and matching `.log` files.
