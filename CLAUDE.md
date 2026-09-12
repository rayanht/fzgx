# F-Zero GX (GFZE01) matching decompilation

Matching decompilation of F-Zero GX built on decomp-toolkit / dtk-template.
Targets: `sys/main.dol` plus fifteen RELs (fourteen shipped as `files/fze.*.rel`
and `main.rel`, which `tools/prepare_orig.py` derives from `enemy_line/line__.bin`).
`ninja` must always end with `16 files OK`.

## Setup (once)

```sh
brew install ninja
# put the disc image in orig/ (RVZ/ISO), then:
uv run tools/prepare_orig.py --version GFZE01   # extracts targets, derives main.rel
python3 configure.py --version GFZE01 && ninja  # downloads dtk/objdiff/wibo/compilers on first run
uv run tools/fzgx.py sync                       # loads 7,308 functions into .fzgx/ledger.db
uv run tools/fzgx.py restore                    # (optional) load state/ledger.json history
```

## Agent workflow

Headless batches use `uv run tools/orchestrate.py --harness codex ...`.
One local Codex app server multiplexes the model sessions; a bounded pool of
persistent CLI workers serves dynamic tools. Each request binds its own function
and agent; project indexes are reused until symbols, units or build configuration
change. Active calls and claims share the tool bound with 3:1 fair dispatch, so
claims cannot starve behind a continuous stream of edits. The runner assigns functions
and supplies their existing C and initial diff. Models only edit/check their
bound work copy or release early for a technical reason. Tooling accepts matches
and releases exhausted attempts; the runner interrupts and unloads the thread.
No model-generated claim, submit, limit acknowledgement, or RESULT line is
needed. The manual CLI/MCP operations remain available. See
`AGENTS.md`, `docs/CODEX_APP_SERVER.md`, and `docs/CODING_RULES.md`.

Rules that hold for everyone:

- Never commit anything from `orig/` or `build/`; never commit compilers.
- Never push. Commits are local; the user pushes.
- Commit completed work before reporting it finished, including tooling, provenance,
  and dependent source changes required by generated matches. A working-tree hash
  check does not prove that an incomplete commit will build in CI.
- Adjacent SDK reuse goes through `fzgx sourcealign --compile-sdk NAME --root PATH`
  (repeat `--root`), then `--discover --min-size 64`, `--saved`, and `fzgx verify`.
  `fzgx sourcealign --apply-names` imports unambiguous donor function names after
  verification; it updates references and provenance and checks all target hashes.
  Check all library roots: MK Deception's ADX and MSL sources are separate from Sofdec.
  The importer currently accepts CC0 sources, copies their license and provenance into
  `state/sdkimports/`, and emits owned C without external-project includes. Compile donors
  against their own nested standard-library headers and source-relative includes.
  For game-code reuse, `--rel-only --root PATH` restricts discovery to REL targets
  and selected donor roots. `--compile-sdk NAME --functions --root FILE` compiles
  independent declaration closures when a full donor TU needs unavailable assets;
  unresolved dependencies are excluded. F-Zero X's N64 build defines are supplied
  by the importer, without inheriting F-Zero GX's project defines.
  `sourcealign --fuzzy --rel-only --min-size 256 --root PATH` ranks whole-function
  and partial opcode overlap without the importer's size and similarity cutoffs;
  `.fzgx/sourcealign/fuzzy.jsonl` retains block offsets and operand agreement.
  Compiler variants share shortlist slots; partial ranking counts distinct opcode
  four-grams so repeated stores and structure copies do not dominate. These are
  investigation leads, never evidence for automatic names or matching status.
- Never delete `build/` or `.fzgx/`. `.claude/settings.json` denies `rm -r`,
  `git clean/checkout/restore/reset/stash/rebase/push` and `ninja -t clean`
  for every agent in this repo. If the build looks broken, run
  `python3 configure.py && ninja build/GFZE01/ok` and report; do not "clean".
- `fzgx submit` accepts matching functions; `fzgx data-import --apply` accepts independent
  data after compiling its definitions, checking layout/relocations, and verifying all 16 hashes.
  `fzgx data-import --inventory --module MODULE` lists unowned data and existing declarations.
  `--recipes state/dataimports/recipes.json` supplies measured text layouts;
  `--regenerate --recipes state/dataimports/recipes.json --apply` reproduces the saved imports.
  See `docs/DATA_IMPORT.md`. Data units are marked `data: true` and have no function claims.
  The batch verifier drains
  completed matches every 60 seconds (`--verify-interval`) and checks every hash before
  committing. Its normal path runs one incremental Ninja build; baseline restoration and
  bisection run only after a failure. Literal-pool constants: retail pooled
  literals per TU (e.g. the 2^52 int-to-double constant), so a per-function unit's private
  `@N` literal never matches the relocation. When the only diffs are such relocations with
  equal bytes, `check` retargets the private symbols to the retail ones in the object
  (`tools/fzgx/poolfix.py`), the unit records the mapping (`pool` in units.json) and ninja
  applies it after every compile (`mwcc_pool` rule from `configure.py`), so the function
  matches and links from C. If the private rodata cannot be emptied the function is a
  *pool match*: accepted and spliced, retail object still linked (`link_state=pool`).
  REL pool reads must use the relocation target's section: offsets overlap across
  `.text`, `.rodata` and `.data`. DOL strings use address-based segment lookup.
  Shared BSS copies use the same binding path after symbol, size and zero-section
  checks; preserve definitions when their range already belongs to the function's
  unit. Compiler-generated `$N` names are ELF bindings, not valid MWCC C identifiers.
  `fzgx fixup` re-checks every saved body after oracle/header changes (and searches the rest).
- Matchers edit only their own unit, and only through `write_unit`. Headers,
  names and splits belong to the librarian.
- No hardcoded addresses (`fzgx lint`), no inline asm in `src/`.
- Symbols are addressed by name; the REL entry points `_prolog`/`_epilog`
  exist in every module and must be written `module:name` (e.g. `title:_epilog`).
- Nothing is carved before it matches. A function gets a split range and a unit (an object
  in the link) at `submit`; until then `check` diffs the agent's work copy against the retail
  auto object that contains the function (symbol-only, two-object objdiff). Reason: units
  are objects in the link and split ranges in the config; 900 stub units of the DOL made a
  link run for 20 min. Keep units at matched count regardless. mwld also never returns (found
  by bisection, 2026-09-09) when a dtk split object carrying its CodeWarrior `.comment` section
  starts with a size-0 label followed by a function at the same offset: dtk emits symbols in
  symbols.txt line order, so `carve.order_labels_after_functions` keeps every function line
  before a same-address label (10 such pairs, all in the DOL). If a link hangs, bisect the
  units with a capped mwld run, never wait on it.
- Assembly-only functions (privileged instructions, no `blr`, shapes MWCC never emits) are
  `fzgx asm-unit` units: `asm: true` in units.json, the split's `.s` copied to `src/`, GNU as
  builds it, ledger status `asm`. GNU as reads branch hints `+`/`-` relative to the branch
  direction while dtk prints the raw hint bit, so `asmunit.fix_branch_hints` respells hinted
  backward branches on copy. 107 landed on 2026-09-09; the ledger has no `blocked` rows left.
- Hardware register blocks: retail addresses them through linker-defined absolute symbols
  (`lis/addi` of `__DIRegs`, `__VIRegs`, `__SIRegs`... resolved by the link, never a folded
  literal). `config/GFZE01/ldscript.tpl` (dtk `ldscript_template`) defines them; C includes `dolphin/types.h` for `vu32` and declares
  `extern vu32 __DIRegs[];`. The object oracle cannot see the link, so `oracle._abs_rows`
  accepts a relocation against a template symbol wherever retail carries the resolved literal
  (`fzgx verify`'s hash is the guard). The lifter emits this form (`HW_BLOCKS`), the fixup
  renames invented names (`lbl_CC006000`) to the canonical symbol by address. Pooled literals
  in the DOL need `Project.bytes_at` to find the segment by address (it was broken for every
  DOL section until 2026-09-09: no DOL pool match could land).
  `fzgx uncarve --stubs` removes any unit without matched code (verify uncarves what it rejects).
  Symbol promotion must rewrite C `global.member` bases too; a following dot only
  extends a symbol name in assembly, not in C. Preserve separate token boundaries.
- Plateaus are data, not agent work. `fzgx stuck` classifies every saved best body at 80%+ by
  failure mode from the object diff (`.fzgx/stuck.json`, rows included). `fzgx fixup`
  is the sole deterministic repair command. All saved variants, source rewrites,
  byte-derived fixes, allocator evidence and compiler-response combinations share
  one engine, content-addressed compile cache and verification path. Session release
  and lifter repair call that same engine. `--apply` submits exact results and
  verifies all 16 hashes; without it, output remains in the repair corpus.
  `--clones` pools saved C across exact retail instruction families, repairs one
  representative and rechecks its copies. It preserves owned declaration closures,
  source pragmas and compiler settings; differing compiler responses keep independent
  search. `reuse` calls this same engine. Clone runs also save portable partial C
  and replay recipes in `sources.json.gz` for subsequent passes.
  `--capture --corpus PATH --output PATH` captures allocator/PCode evidence;
  `--captures PATH` consumes it. Do not add standalone repair/search runners.
  A unit may carry its own `mw_version`/`extra_cflags` (an `-O` override replaces the module's);
  `check`/`submit` honour them before the carve. The decomp-permuter was dropped: over the whole
  project it closed one function and cost minutes per try.
  Saved-candidate repairs must retain the recorded compiler version and flags through every
  rewrite. `fzgx stuck --seeds PATH` accepts a manifest of saved bodies with those settings.
  Fixup also probes function-scoped optimizer pragmas before source rewrites. A masked-word
  score of 100% is only a shortlist: keep trying candidates until relocation bindings and
  data pass the full oracle. The first code-only match must not stop the search.
  Include `opt_dead_assignments off/reset`: it reproduces the per-function effect
  of `-opt nodeadstore` without leaking optimizer state to a later TU merge.
  Recover floating literals from retail relocation bytes, trying repeated equal
  occurrences together as well as individually. Keep the original C as a register
  search seed alongside a locally improved rewrite, within the same repair budget;
  a better intermediate word score can remove the exact declaration-order solution.
  Shared-pool recovery follows symbolic bases through control-flow joins and reads
  ordinary load offsets as well as direct relocations. It proposes exact literal
  values and sparse external pool layouts, including uses in macros. No load
  immediate or mismatching data is patched in the object. Objdiff JSON addresses
  are decimal strings; parsing them as hex corrupts repair row accounting.
- `fzgx trivial` matches single-`blr` and `li r3,N; blr` functions mechanically (419 landed on
  2026-09-08) and then lifts straight-line functions from the disassembly (`tools/fzgx/lift.py`:
  getters, setters, one-call wrappers, short call-free bodies; 102 landed the same day). Run it
  before spending agents on small functions.
- `fzgx lift --tu rel/main_rel/accessory.c` lifts one whole TU without a size cap, saves drafts
  under `.fzgx/lift/`, and submits exact matches after the deterministic fixup. `--no-submit`
  keeps the results local. Signatures come from owned headers and matched C, with register-flow
  constraints scoped to the TU and its callees; context labels inferred signatures. A matched
  wrapper can still have missing passthrough parameters: follow its callees' entry registers
  (the `memset`/`fn_80008BEC` size argument was one such case). Drafts containing `???` remain
  incomplete and cannot be submitted by this pass.
- Prefer deterministic repairs, and carry recurring manual fixes back into the existing engine.
  Manual reconstruction and tuning are also authorized. Submit only oracle-verified C and
  check all 16 hashes. Use existing retail functions as the repair corpus; do not add unit tests.
  `fzgx lift --callee fn_1_4F734 --callee fn_1_4AE0C` selects the union of direct callers
  across TUs; `--no-submit` retains drafts without carving. Header layouts constrain copied
  stack objects. Integer-to-float recovery tracks both scratch-word stores in either order
  and keeps the encoding internal until its bias subtraction.
- `fzgx lift --all --engine m2c` runs the pinned PowerPC/CodeWarrior backend across every
  unmatched function; `--tu` and `--callee` also support this backend. It consumes owned
  declarations and recovered stack aggregates, lowers byte-addressed accesses to C, and
  rejects unresolved operations rather than including m2c's placeholder macros. Intermediate
  assembly, contexts and drafts live under `.fzgx/machine/`; generated candidates still go
  through the object oracle, `submit`, and all 16 hashes. No reconstructed C is edited by hand.
  Signature recovery follows callable assembly labels without changing their ownership.
  MWCC `_savegpr`/`_restgpr` and FPR frame helpers preserve arguments and return registers;
  never model them as ordinary calls. Self-xor/subtract zeroing idioms have no input.
  Fixup variants of the same symbol run serially because their scratch files are shared;
  different symbols may run in parallel. Keep the best saved draft when trying another backend.
  Backend generation uses isolated worker processes because its IR adapters mutate class methods.
  `fzgx lift --all --engine m2c --resume` reuses saved candidates and retries generation and
  compilation failures; omit `--resume` when changing lowering for already compilable functions.
  Compiler diagnostics and generation/scoring checkpoints stay under `.fzgx/lift/m2c/`.
  Signature flow also covers unmapped DOL functions and switch destinations. A matched `void`
  wrapper can omit a live return register; use caller consumption and callee register flow to
  recover it. Varargs save areas are not fixed arguments, and CR1 controls floating varargs.
  `machine.py` transports retail jump tables, shared stack-copy extents, packed byte/word
  locals, and 64-bit call arguments. `ppc_lowering.py` carries XER_CA through arithmetic and
  recovers consumed condition-register bits. Paired-single data stores must never disappear
  as backend no-ops; only recognized FPR frame saves may be elided.
  The default lifter uses MWCC's `__vec2x32float__` for paired arithmetic and
  unquantized loads/stores. It keeps scalar and paired FPR lifetimes distinct;
  unknown upper lanes and GQR formats remain explicit gaps. Native vector C can
  emit indexed loads and merge/multiply pairs where retail uses displacement
  loads and `ps_muls0`/`ps_madds0`; a compilable draft is not an object match.
  Keep reused int-to-float bias registers alive and follow XER_CA across
  intervening non-carry instructions in signed power-of-two division.
  Declaration normalization must parse lines without nested repetition over arbitrary C;
  the old regex stalled real drafts such as `fn_80005738` beyond repair time budgets.
  Register-only instruction differences are not proof of equivalent value flow.
  The oracle reports known non-stack store-value conflicts; fix those values before
  spending allocation searches. Compiler-response composition and source repairs
  now run together in `fzgx fixup`; see `docs/REGISTER_REPAIR.md` for measurements.
  Read disassembly only from the active `build/GFZE01/config.json` split units. Orphaned
  named `.s` files can retain obsolete local names after promotion and shadow current auto
  units, yielding an object match that fails the link (`SelectThread_800105D0` was one).
- The font/sprite UI interface has many large callers, but that dependency count is not
  evidence of a collapsible matching bucket: the corrected 318-function UI lift closed zero.
  `include/font.h` records the variadic text wrapper and 0x58-byte packet submission result;
  do not infer sixteen fixed parameters from a varargs register-save prologue.
- Prioritize deterministic SDK C imports (CARD, then OS, EXI, SI) regardless of size.
  Include REL middleware: the reconstructed Sofdec sources in the CC0 MK Deception decomp
  yielded 60,888 bytes from 24 functions (including one complete `mpvabdec.c` TU).
  Owned sources, headers and provenance are under `src/rel/movie_module/`, `include/sofdec/`
  and `state/sdkimports/sofdec.json`. GX and later Sofdec player layouts differ; only the
  recovered fields in `mwsfd.h` are named. Compare code bytes when tracking the 30% target.
  SDK imports must retain active compiler pragmas and distinguish function-pointer objects
  from prototypes. After a pool-backed submit re-splits retail objects, invalidate the
  in-memory object index before checking the next function (`api._reconfigure_and_split`).
  Code relocation masks apply to the containing instruction: MWCC's halfword SDA21 offsets
  and DTK's word offsets denote the same field. Use `poolfix.masked_code` for SDK signatures
  and candidate scoring, and normalized offsets for symbol binding. Never mask four bytes
  starting at a halfword relocation; that erases part of the following instruction.
  The corrected scan exposed 202 unmatched signatures / 76,612 bytes at >=64 bytes.
  SDK declaration closure includes enum members and local statics; symbol replacement must
  preserve struct members and parameter scope. Reject inline assembly in dependencies too.
  `sdkimport --library` also supports AR, VI, DVD, GX, DSP, PAD, AI and runtime libraries;
  generated sources use owned declarations, never build/tools headers.
  Refresh compiled SDK objects when the compiler or flags change; source mtime alone is
  insufficient. Imported callback names must follow local-to-global promotion. A C function
  can also own a retail entry label: `carve.retain_entry_labels` keeps that name as a symbolic
  linker alias. Link failures are retained in `.fzgx/verify_last_failure.log`.
  Functions **under 256 bytes** (`--max-size 255`) are a repair corpus, not a prerequisite. `fzgx stuck --max-size 255` classifies the saved attempts; `fzgx fixup --max-size 255`
  searches them. `fzgx reuse --max-size 255` rebinds verified C when retail instruction
  shapes agree, retaining registers, immediates, relocation kinds/addends and branch targets;
  all candidates pass the oracle and `fzgx verify`. Use 48 headless Luna workers only for
  remaining work the deterministic tools cannot compute. Do not add unit tests: use real
  MWCC/object-diff checks, lint, and the 16-target hash check.
- Readability tooling: `fzgx tu-organize` (TU directories from `tus.json`), `fzgx headers`
  (layouts from disassembly → `include/rel/<module>/globals.h`, offset self-checked under MWCC;
  `--symbol` prints one layout, `--oversize` lists dtk under-sized symbols), `fzgx rename`,
  `fzgx naming-bundle`/`naming-apply`. TU passes: `fzgx tu-migrate` (once per module),
  `fzgx tu-check` (the whole file as one unit: the goal state) and `fzgx tu-finish` (include,
  tidy, hoist, reflag, collapse as internal stages; the orchestrator's finish round). Agent ids
  prefixed `revise-` rewrite a matched unit and keep it only if still 100%; `shadow-` run A/B
  trials without committing.
- Naming: `fzgx naming-bundle <tu.c>` (sources, header, retail strings, assert hints) →
  a cheap model answers JSON → `fzgx naming-apply --file p.json`, which renames symbols,
  records typedef names in `config/GFZE01/<module>/typedefs.json`, re-splits, regenerates
  every header of the module (offset self-check) and relinks. Headers are generated:
  never hand-edit `include/rel/<module>/*.h`; change the analyzer or the name map.
- The split runs `dtk dol split --no-update`: dtk never rewrites `symbols.txt`/`splits.txt` (its rewrite
  dropped attributes). A carved DOL function with no callers is marked `force_active` in symbols.txt
  (alone in its object mwld dead-strips it and every hash after it fails); carve does this.
- Header changes can alter a matched unit's code. `ninja build/GFZE01/ok` must pass after
  regenerating; if a REL fails, byte-diff `build/GFZE01/<m>/<m>.rel` against `orig/` and
  map the first divergence to a function.
- `tools/seeds/asserts.py` → `state/seeds/asserts_<module>.json` (file:line + message per
  assert call); `tools/seeds/debug_strings.py --write` refreshes `tus.json` from `__FILE__`
  anchors (then `fzgx tu-organize` and regenerate headers).
- Batches: `uv run tools/orchestrate.py --harness codex ...` (codex only; tiers: gpt-5.6-luna, then gpt-5.6-terra;
  Sonnet and Gemini Flash were tried and dropped) (headless, one report
  per batch, periodic live verification and a final drain). Never use in-process subagents.
- DeepSeek trials use the same Codex harness: `--provider deepseek --model deepseek-flash`
  selects DeepSeek-V4.1-Flash. Supply `DEEPSEEK_API_KEY` or `--api-key-file PATH`;
  keys stay outside the repository and out of command arguments. The provider and
  `tools/codex_models.json` are selected with run-local overrides; normal Codex config
  is untouched. Never set `forced_login_method="api"` for these runs: Codex 0.153.4
  deletes the shared ChatGPT login when enforcing it. `env_key` authenticates the
  custom provider without changing the OpenAI login. Keep all worker feature
  overrides inside `tools/orchestrate.py`; do not apply them through standalone
  Codex commands or write the user's personal Codex config/auth files.
  DeepSeek returns token usage,
  not dollar cost (confirmed with the live Responses API). Estimate each response
  at weekday UTC 01:00-04:00 / 06:00-10:00 peak rates, half otherwise; retain usage
  from failed turns too. Label estimates explicitly; use provider-reported dollar
  cost when available. Supported effort levels are `low`, `high`, and `max`.
  Load the four matcher dynamic tools directly (`supports_search_tool=false`): DeepSeek rejects
  duplicate MCP namespaces returned by parallel Codex tool searches. Shadow trials
  retain matched C and compiler options under `.fzgx/attempts/` for later integration;
  finishing or aborting them preserves the function's original matching status.
  App-server control commands use bounded concurrency with separate completion
  slots. Retry only explicit JSON-RPC -32001 overload rejections, never ambiguous
  timeouts. Codex 0.153.4 requires each inherited MCP server to be disabled in
  thread-local config; the global orchestrator MCP switch does not suppress
  their initialization. Disable worker hooks through runner overrides too.
  Completed items retain reasoning/text; do not persist every token delta at scale.
  Record compact stream progress every 30 seconds of activity and count retriable
  errors separately from final outcomes. Claim and initial check share one tool
  slot (`claim --check`), so a full-width startup does not enqueue all claims ahead
  of all preflights. Patch-anchor errors return current C under the ownership guard.
  The DeepSeek catalog must also set `apply_patch_tool_type=null`; disable the
  request-user-input tool in runner-local settings to leave exactly four tools.
  Compiler probes must persist their selected version for subsequent edits,
  submit, release repairs, and the next batch's saved-body selection. Context
  must display the actual seed compiler/flags. Similarity scores near 100% can
  still hide many register or scheduling differences; show remaining diff rows.
  Bind each headless worker to its assigned symbol and agent id. A successful
  submit/release ends that worker's attempt; reclaiming cannot reset its counters.
  Reject repeated shadow submits before checking or finishing: a finished trial no
  longer has the saved previous status and must not mark existing matched C unmatched.
  Direct checks and compiler-version probes must honor the same stop as source edits.
  Set catalog `multi_agent_version=null` as well as disabling `multi_agent` and
  `multi_agent_v2`: catalog v2 can enable delegation despite those feature flags. Nested agents
  otherwise share the claimed work copy and corrupt each other's checks. Enforce
  the assigned symbol and identity on every CLI tool call, serialize calls for that
  function, and pass the release caller's identity through to the ledger guard.
  Disable `goals` for matcher processes too: its unrelated `get_goal` call adds a
  model round trip before claiming the function.
  Provider/catalog reference: [DeepSeek's Codex integration](https://api-docs.deepseek.com/quick_start/agent_integrations/codex/).
  Example: `uv run tools/orchestrate.py --harness codex --provider deepseek
  --api-key-file ~/.config/fzgx/deepseek.key --seeds PATH --parallel 1 --no-trivial`.
- Whole-project seed batches use `uv run tools/seeds/small.py --max-size 0 --fresh-lift --output NEW_DIRECTORY`.
  Freeze a full-size deterministic lift for every unmatched function, compare the best saved C with its
  compiler settings through the unified fixup engine, and retain the best current word score
  (full oracle matches take precedence). No size, SDK or prior-attempt exclusions apply.
  The manifest retains fresh lifts alongside selected bodies. DeepSeek `--effort none` disables
  reasoning through the runner's DeepSeek transport, which removes the incompatible
  `x-codex-turn-metadata` header. Verify actual streamed items, not just thread settings;
  the runner stops a `none` batch if reasoning appears. Personal config is never edited.
- Fresh-function batches use `uv run tools/seeds/untouched.py --max-size 511 --output PATH`.
  It excludes prior matcher candidates/successful checks, known SDK signatures,
  prepared imports and ranked donor candidates, and freezes `lift_total` output
  with hashes. These are inferred drafts, including unresolved markers, not
  high-scoring repair seeds; workers complete the missing lowering before compiling.
  The selector rejects stale ledger symbols and fails if any selected function has
  no draft. Accepted C installs serially under `submit.lock`: different functions
  can share a TU, splits and symbol tables even when their work copies are isolated.
- Largest-function batches use `uv run tools/seeds/largest.py --count 50 --output NEW_DIRECTORY`.
  Select globally by unmatched retail byte size, without SDK or attempt exclusions.
  Size `lift_total`'s instruction allowance to each selected function and fail if any
  draft is missing. Include existing saved reconstructions as additional seed references.
  Context budgets apply to auxiliary examples/history; never truncate the target
  assembly or its referenced declarations, since matchers have no file reader.
- Recovered-candidate batches use `uv run tools/seeds/recovered.py --above 90 --output PATH`.
  This selects strict historical scores above the threshold without a size cap or SDK
  exclusion, joining attempt bodies, check archives, lifter drafts, owned SDK imports,
  repair results and sweep/spelling history. Donor fuzzy scores are not C match scores.
  Freeze the actual saved C, hashes, provenance and compiler settings; recheck it and
  try saved alternatives for regressed seeds. Keep historical eligibility separate
  from current scores in the manifest. Missing saved bodies fail preparation.
  Pass the resulting manifest to the orchestrator with `--seeds PATH --no-trivial`;
  `--provider deepseek --parallel 128 --effort low` requests the lowest supported
  reasoning effort through worker-local overrides.
- Retry a completed batch's still-unmatched releases with `uv run tools/seeds/released.py
  --batch BATCH --seeds ORIGINAL_MANIFEST --output NEW_DIRECTORY`. This freezes each
  release's saved C and compiler settings without a size or score cutoff. Older metadata
  is recovered only from identical checked C or an identical original seed. The runner
  performs the current compile as preflight. Use a new batch name and set `--parallel`
  to the manifest's function count for full-width concurrency.
- The orchestrator does three things: pick a pool, run the batch, run the TU-finish round
  (`--finish`, or `--finish-only --module M`). It reads reports. It does not edit blocks,
  headers or splits by hand, and does not experiment on the live tree (use `--shadow`).
- Agents only where the answer is not computable. The TU-finish pass (`fzgx tu-finish`,
  `tools/fzgx/reconcile.py`) is deterministic: it isolates colliding private typedefs by
  function prefix, tries each candidate declaration of every symbol (definition first, then
  the blocks' variants) and keeps the first under which every block naming the symbol still
  matches, marks the rest contested, and collapses complete TUs. Verdicts are memoised by
  generated-unit hash (`.fzgx/verify_cache.json`), so a pass over main.rel is ~30 s. The only
  agent task it emits is the fixed list of blocks that cannot compile under their prologue
  (one revise batch; a block that fails twice is blocked, never re-queued).
- Build speed: units compile in groups of 48 per mwcc process (`tools/mwcc_batch.sh`, one depfile
  per group, `mwcc_batch` rule); a full rebuild is ~8 s, of which ~5 s is the two-stage main_rel
  link. `build.ninja` names the interpreter `python3` on purpose: a baked-in path changed with every
  caller (uv venv vs homebrew) and rebuilt every unit. Candidate loops (fixup, spell, lifter)
  score by masked machine words (`oracle.words`/`word_score`), objdiff only on winners; batch passes
  compile through `oracle.compile_many`/`check_many` (parallel chunks), never one process per body.
- While a batch runs, never call `configure.py`, `ninja` or `dtk` by hand: go through
  `fzgx verify` or `oracle.build_lock()`. Two concurrent splits kill each other (exit 137)
  and a broken baseline makes a bisect blame every pending unit. Verification holds
  submit.lock then the build lock; after a failed incremental build it establishes a
  known-good baseline before bisection. Never wrap verify in another submit.lock.

- Near-miss fixup must preserve a proven store-value correction in its search
  frontier even when register differences initially lower its word score. Value-flow
  diagnostics invalidate unsupported regions locally; mixed diffs must not disable
  them for the entire function. Operand swaps that compile identically can become
  effective under a different optimizer policy, so probe those combinations explicitly.
  Extra helper definitions block integration in both DOL and REL units. Separate
  inlined uses from calls to an already-owned helper when both appear in retail.
  Interior references use generated `OWNER__fzgx_offset_HEX` declarations and the
  existing pool-binding path: prove module, section, owner bounds, relocation type
  and resolved target, then adjust only relocation addends. Never patch instructions.
  Fixed hardware literals belong in `include/dolphin/hw_regs.h`, not matcher C.
  Repair provenance must be acyclic; rechecking an identical content-addressed
  candidate must not create a parent reference to itself.

## Layout

- `config/GFZE01/` — dtk config, per-module `symbols.txt`/`splits.txt`, `units.json` (generated units, read by `configure.py`).
- `src/rel/<module>/<tu>.c` — one file per recovered translation unit, functions in retail
  order as blocks between `/* fzgx:begin NAME */ … /* fzgx:end NAME */` markers (tooling-owned;
  never hand-edit the markers). Every block is compiled as its own generated unit
  (`build/GFZE01/gen/…`, one split range per function) so the link and the oracle stay per
  function; `fzgx tu-check rel/<module>/<tu>.c` compiles the whole file as one unit (the goal
  state). Agents edit private work copies under `.fzgx/work/`; `submit` splices a block in.
  `src/dol/` and modules without a TU map keep one file per function (`fzgx tu-migrate --module M`
  converts a module once `tus.json` exists).
- `include/` — shared headers (generated per module/TU; see readability tooling).
- `tools/fzgx/` — ledger, carve, oracle, context, lint; `tools/linecrypt.py`, `tools/avlz.py`, `tools/prepare_orig.py`.
- `.fzgx/reports/` — per-batch reports (local, not committed, like SPEC.md); `state/ledger.json` — committed ledger snapshot.
