# Shared Codex matcher server

`tools/orchestrate.py --harness codex` uses one local `codex app-server`
process for a batch. Each function gets an independent thread. There is no
Codex CLI or MCP server per matcher. `tools/codex_server.py` implements the
stdio JSON-RPC transport described in the
[official OpenAI App Server documentation](https://learn.chatgpt.com/docs/app-server).

```sh
uv run tools/orchestrate.py --provider deepseek --model deepseek-flash \
  --api-key-file ~/.config/fzgx/deepseek.key --effort low \
  --parallel 1024 --tool-parallel 8 \
  --max-checks 16 --max-stale 4 --max-attempts 100 --timeout 7200 \
  --seeds PATH/manifest.json --no-trivial --batch UNIQUE_BATCH_NAME
```

Use the prepared manifest for the intended pool; the concurrency setting does
not select functions. An already-running CLI batch keeps its existing transport.

## Ownership and limits

The runner claims the function, verifies and installs the saved C, and performs
the initial compile before starting a model turn. An exact seed completes without
a model request. Seeded context excludes duplicate old attempts and fresh lifter
drafts; it reports the seed's actual compiler and flags.
The complete target assembly and referenced declarations are mandatory; the context
budget bounds auxiliary examples/history only. A `lift_total` seed can include a
`prior_attempt` reference so a new draft does not hide an existing reconstruction.
Assignment and preflight use one `claim --check` CLI call in one tool slot.
A full-width claim queue therefore cannot put every initial check behind all
the remaining claims before any model starts.
The local tool queue prioritizes existing sessions over new claims. Shared signature
and call-constraint caches avoid rebuilding the same source/TU analysis per CLI
process; source, header, symbol, TU and tooling changes invalidate them. One producer
builds each cache, then publishes it atomically. Assembly caches also publish atomically.
Assignment records separate context preparation and initial-check timings; session
logs record local tool queue and execution times.

The model has five dynamic tools: `write_unit`, `patch_unit`, `check`,
`read_evidence`, and `release`. Their schemas omit symbol, agent identity,
paths, harness, and model.
The host supplies these from the thread's assignment, rejects extra arguments,
and serializes calls within each function. The bound CLI independently checks
ownership. There is no shell, file-reading, claim, or submit tool for the model.
An invalid patch anchor returns the current C without changing it or consuming a
compiler check, so the next patch can use an exact span of the installed source.

`read_evidence(section="diff", cursor="0")` reads the selected compile's cached
diff in pages of 80 lines. The response supplies the next cursor and separate
target/candidate object addresses; the old first column is an aligned row index
times four, not a retail code address. `section="data"` supplies relocated switch
entries and exact floating constants, including loads through a shared TU base.
Imported data contributes its owned header declarations, complete typedefs, relevant
string bytes and symbolic relocation bindings. Initial context bounds string/table
previews; data pages retain the complete evidence. Large structured text pools show
their recovered dimensions instead of embedding all text. Mutable BSS values are
not treated as constants. Data-only units are excluded from matched-function examples.
Reads never compile, increment checks/stale counts, or change the selected compiler.
Cache identity includes the source hash, attempt and compiler options. Failed
compiles invalidate successful evidence; compiler probes cache the selected result.
Existing app-server threads keep their original schemas and may use
`check(versions="diff:80")` or `check(versions="data:0")` for the same read-only
operations. Check responses advertise this route; restarting a running batch is
unnecessary. New assignments include decoded retail data in mandatory context.

The API submits a full object match automatically and saves/releases attempts
when check or stale limits are reached. The CLI writes its terminal record only
after all mutations finish. The host interrupts the turn before returning the
terminal tool result, eliminating a final model request for administrative
release or summary. A model may still release early with a technical diagnosis.

There are three independent concurrency bounds:

| Work | Bound |
|---|---|
| Live function sessions | `--parallel` |
| Local claim/context/compile/submit/release processes | `--tool-parallel` |
| Outstanding app-server commands | 16 starts plus 16 control commands |

The command bound does not limit already-running model turns. Explicit JSON-RPC
`-32001` overload rejections are retried with bounded backoff. Timeouts and other
ambiguous failures are never retried as thread/turn creation might already have
executed. Completion has separate command capacity and tool responses bypass
the command semaphores.

On timeout or disconnect the host stops the turn, drains any in-flight tool
mutation, and releases the saved best candidate. Finished threads are unsubscribed
with an unload delay of zero. SIGTERM follows the same cleanup path. Killing a
compiler submission halfway through carving is avoided. All accepted source
still passes all 16 target hashes before being committed.
SIGTERM sets a batch stop event instead of cancelling workers inside their cleanup.
Queued claims and tool calls stop before execution; running mutations finish. Cleanup
is shielded from cancellation and uses `release --save-only`, preserving the saved
C, compiler settings and score without compiling or running repair searches.
Ordinary completed releases retain their deterministic repair pass. Insufficient-balance
errors stop the batch globally so the remaining queue survives for a funded resume.

## Live verification

One verifier process drains completed matches every 60 seconds, independently of
model sessions. `--verify-interval SECONDS` changes the interval; zero selects
end-only verification. Shutdown waits for any active transaction and drains again.
SIGTERM/SIGINT stop the watcher between transactions. To attach to an older runner:

```sh
uv run tools/fzgx.py --json verify --watch --interval 60 --until-pid RUNNER_PID
```

The normal path runs one incremental Ninja build and hash check. It does not
disable accepted units or rerun configure unconditionally. Only a failed build
triggers baseline restoration and bisection. Submission and build locks cover
the transaction and commit; model reasoning and private compiles continue.
Symbol promotion journals dependent caller/header edits so they are committed
with the verified source. Rejection preserves the saved C and restores ownership.
Commits include only these paths, leaving unrelated staged work alone.

`verify.jsonl` records pass results in the batch directory; `verify.stderr.log`
retains watcher errors. Final reports include periodic acceptances/rejections.
Build output is retained in `.fzgx/verify_builds.jsonl`.

On real `fn_80021930`, rechecking already-built accepted C fell from 8.630 seconds
to 0.118 seconds. Forcing its MWCC recompile and relink took 1.837 seconds and
passed all 16 hashes. These are single-function measurements, not full-batch
throughput. Replaying the archived object-only match `fn_1_F9028` exercised the
watcher's failure path: it rejected the candidate, restored all 16 hashes, and
exited cleanly in 26.834 seconds.

To resume a batch's releases, preserving their saved reconstructions:

```sh
uv run tools/seeds/released.py --batch PREVIOUS_BATCH \
  --seeds ORIGINAL_MANIFEST --output NEW_SEED_DIRECTORY
```

This selects still-unmatched final releases, with no size or score cutoff. It
excludes functions already integrated since that release. Use the resulting
manifest with a new batch name; its function count is the full-width `--parallel`.
For a paused batch, add `--resume --seeds ORIGINAL_MANIFEST`: this selects
interrupted/failed attempts and unstarted functions, preserving updated C and
compiler metadata while excluding work that completed normally. Reports distinguish
interrupted and unstarted work from failures.

On the real `fn_1_EBE4` seed, profiled context plus MWCC preflight fell from
10.876 to 0.599 seconds with the shared caches warm. The context and 95.11029%
object score stayed identical; cached signatures and propagated constraints matched
fresh recovery. A cold cache still needs one producer per source revision/TU.
A 32-function DeepSeek low run on 2026-09-11 started its first model at 1.003 seconds,
all 32 by 6.029 seconds, and saved/stopped all workers in 1.368 seconds with no open
claims. This measures 32 real sessions, not full 512-session startup latency.

## Runtime isolation and records

To prepare every currently unmatched function below 1 KiB, retaining the best saved
C and its compiler settings before lifting functions without a candidate:

```sh
uv run tools/seeds/small.py --max-size 1023 --output NEW_SEED_DIRECTORY
```

The frozen manifest records source hashes and origins. Selection excludes obsolete
ledger names absent from the current function map and fails if any selected function
cannot be seeded. Use it with the requested `--parallel` and `--effort` settings.

All provider, model, effort, feature, and MCP settings are process/thread-local
overrides constructed by the runner. It never writes personal Codex configuration
or authentication, never forces a login method, and passes the provider key only
through the environment. The app server can still read global user instructions;
project instruction concatenation and automatic skill instructions are disabled.

Codex 0.153.4 still initializes inherited MCP servers with the global orchestrator
MCP switch disabled. The runner reads effective server names and explicitly
disables each in thread-local configuration. Unexpected MCP initialization fails
the transport before a matcher can use it. Worker hooks, shell snapshots, plugins,
and unrelated tools are disabled in the runner. Shell snapshots were launching
login shells despite matchers having no shell tools.
Disable the request-user-input tool through its worker-local setting and clear
`apply_patch_tool_type` in the DeepSeek catalog as well as the freeform-patch
feature. The original local HTTP capture of Codex 0.153.4 confirmed exactly the
then-four dynamic matcher tools and `reasoning.effort=low`; disabling shell alone left a built-in
patch tool available.

DeepSeek requests pass through an asyncio byte relay owned by the runner. It removes
`x-codex-turn-metadata`: measured provider responses emitted reasoning whenever this
OpenAI-specific header was present, even with `reasoning.effort="none"`. Removing it
preserved the requested mode. The relay keeps the JSON and streaming response unchanged,
verifies upstream TLS, and cancels upstream connections when Codex disconnects. It binds
only to loopback and modifies no personal configuration. A real `fn_8004BDD8` prompt
reached its first tool call in 2.70 seconds with no reasoning item after this change.
A `none` batch stops if any matcher receives a reasoning item; thread configuration alone
is not proof that the provider honored the setting. Missing usage events remain unknown,
not evidence of zero reasoning or zero cost.

Assignments, prompts, completed reasoning/messages, tool calls/results, usage,
terminal records, and result rows live under `.fzgx/runs/BATCH/`. Token deltas are
discarded because completed items contain the full text. Usage events drive cost
estimates even on interrupted turns. Token deltas also update cumulative character
and event counters, logged at most once every 30 seconds while streaming, so a
long reasoning response is distinguishable from a connection with no new output.
Result rows record retriable stream errors and reasoning tokens; batch summaries
count retries and affected sessions independently of final match/release status.
DeepSeek estimates use the usage event's UTC
timestamp for peak/off-peak pricing. The app-server token-usage schema does not
expose a dollar cost. No claim of provider-reported billing is made.

For completed batches, `uv run tools/diagnose_batch.py --batch BATCH --transcripts
--output DIRECTORY` counts release reasons, patch/compiler failures, transport
retries and reasoning tokens without model calls or compilation. Compile the
saved releases with `--batch BATCH --seeds ORIGINAL_MANIFEST --min-percent 0
--output NEW_DIRECTORY`, then use `--repair --output NEW_DIRECTORY` to run the
current release fixup and export exact candidates. Repair holds the build lock;
run it between batches. Saved release metadata takes precedence over older seed
settings, with the source hash checked before replay.

## Measured validation — 2026-09-10

Codex 0.153.4, DeepSeek `deepseek-flash`, effort `low`:

| Trial | Completed | Wall time | Peak RSS | Estimated cost |
|---|---:|---:|---:|---:|
| 256 sessions, shell snapshots enabled | 256/256 | 101.121 s | 674.8 MiB | $0.014438 |
| 256 sessions, shell snapshots disabled | 256/256 | 10.572 s | 636.8 MiB | $0.014455 |
| 1,024 sessions, shell snapshots disabled | 1,024/1,024 | 39.155 s | 1,792.9 MiB | $0.064510 |

The final two runs had zero wrong-thread results, overloads, retries, or hook
executions. Peak started turns awaiting their tool call were 256 and 1,009.
Both settled to two resident processes: the Node launcher and Codex binary.
Git metadata collection briefly raised process counts to 55 and 38 respectively,
including short-lived defunct entries; no idle MCP servers remained.

These capacity probes use short nonce-returning model calls, not full decompilation
contexts or sustained 1,024-function compiler load. Two real function sessions
separately exercised seeded context, dynamic C writes, MWCC diffs, best-body
preservation, automatic release at three checks, and terminal interruption.
`fn_800791E8` improved from 97.11382% to 99.227646%. An exact compiler-repaired
seed for `fn_80021930` completed preflight with one check and zero model calls.

To repeat the billable transport measurement explicitly:

```sh
uv run tools/profile_app_server.py --parallel 1024 \
  --api-key-file ~/.config/fzgx/deepseek.key --name UNIQUE_DIAGNOSTIC_NAME
```

This is a manual capacity diagnostic, not a unit test or CI job. Raw events and
process samples are retained under `.fzgx/diagnostics/NAME/`.
