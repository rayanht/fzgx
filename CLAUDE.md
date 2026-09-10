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

Matching is done by many cheap subagents, one function each, through the
`fzgx` MCP server (`tools/fzgx_mcp.py`, registered in `.mcp.json`; approve it
when Claude Code asks at startup). Matchers have **no shell**: their tools are
`claim` → `context` → `write_unit` → `check` (≤ 8) → `submit` or `release`,
plus read-only `Read`. The same operations exist as `uv run tools/fzgx.py ...`
for humans, the orchestrator and the librarian. The orchestrator picks
functions with `fzgx inventory --status unmatched --max-size N`, fans out
`matcher` subagents (`.claude/agents/matcher.md`), then runs the `librarian`
once per wave, then `triage` for functions at the attempt cap. Details:
SPEC.md (local, not committed) and `docs/CODING_RULES.md`.

Rules that hold for everyone:

- Never commit anything from `orig/` or `build/`; never commit compilers.
- Never push. Commits are local; the user pushes.
- Adjacent SDK reuse goes through `fzgx sourcealign --compile-sdk NAME --root PATH`
  (repeat `--root`), then `--discover --min-size 64`, `--saved`, and `fzgx verify`.
  `fzgx sourcealign --apply-names` imports unambiguous donor function names after
  verification; it updates references and provenance and checks all target hashes.
  Check all library roots: MK Deception's ADX and MSL sources are separate from Sofdec.
  The importer currently accepts CC0 sources, copies their license and provenance into
  `state/sdkimports/`, and emits owned C without external-project includes. Compile donors
  against their own nested standard-library headers and source-relative includes.
- Never delete `build/` or `.fzgx/`. `.claude/settings.json` denies `rm -r`,
  `git clean/checkout/restore/reset/stash/rebase/push` and `ninja -t clean`
  for every agent in this repo. If the build looks broken, run
  `python3 configure.py && ninja build/GFZE01/ok` and report; do not "clean".
- `fzgx submit` is the only path that flips a unit to `matching`; `fzgx verify` relinks once
  per batch and verifies every hash before committing. Literal-pool constants: retail pooled
  literals per TU (e.g. the 2^52 int-to-double constant), so a per-function unit's private
  `@N` literal never matches the relocation. When the only diffs are such relocations with
  equal bytes, `check` retargets the private symbols to the retail ones in the object
  (`tools/fzgx/poolfix.py`), the unit records the mapping (`pool` in units.json) and ninja
  applies it after every compile (`mwcc_pool` rule from `configure.py`), so the function
  matches and links from C. If the private rodata cannot be emptied the function is a
  *pool match*: accepted and spliced, retail object still linked (`link_state=pool`).
  `fzgx sweep` re-checks every saved body after oracle/header changes (and searches the rest).
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
  literal). `config/GFZE01/ldscript.tpl` (dtk `ldscript_template`) defines them; C declares
  `extern vu32 __DIRegs[];`. The object oracle cannot see the link, so `oracle._abs_rows`
  accepts a relocation against a template symbol wherever retail carries the resolved literal
  (`fzgx verify`'s hash is the guard). The lifter emits this form (`HW_BLOCKS`), the fixup
  renames invented names (`lbl_CC006000`) to the canonical symbol by address. Pooled literals
  in the DOL need `Project.bytes_at` to find the segment by address (it was broken for every
  DOL section until 2026-09-09: no DOL pool match could land).
  `fzgx uncarve --stubs` removes any unit without matched code (verify uncarves what it rejects).
- Plateaus are data, not agent work. `fzgx stuck` classifies every saved best body at 80%+ by
  failure mode from the object diff (`.fzgx/stuck.json`, rows included). `fzgx sweep` is the one
  search pass over every saved body (the agents' best attempts, or the lifter's drafts with
  `--drafts`), three stages: re-check against today's oracle and headers (submits outright and
  pool matches), the deterministic fixup (`tools/fzgx/fixup.py`: edits the diff rows name, with a
  short register-allocation search), then the spelling search (`tools/fzgx/spell.py`: a beam over
  every rewrite family, lockstep across the remaining bodies, from the fixup's improved body).
  Stages are memoised by body + headers + tooling; `fzgx sweep SYMBOL` runs the same stages on one
  body. `release` runs the fixup on an agent's best body and submits a match in the agent's name.
  A unit may carry its own `mw_version`/`extra_cflags` (an `-O` override replaces the module's);
  `check`/`submit` honour them before the carve. The decomp-permuter was dropped: over the whole
  project it closed one function and cost minutes per try.
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
- Current work is strictly deterministic tool development. Do not hand-write or manually tune
  reconstructed C. Fix the generator, type recovery or lowering and submit only its verified
  output. Use existing retail functions as the repair corpus; do not add unit tests.
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
  Declaration normalization must parse lines without nested repetition over arbitrary C;
  the old regex stalled real drafts such as `fn_80005738` beyond repair time budgets.
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
  Functions **under 256 bytes** (`--max-size 255`) are a repair corpus, not a prerequisite. `fzgx stuck --max-size 255` classifies the saved attempts; `fzgx sweep --max-size 255`
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
  per batch, `fzgx verify` relinks once at the end). Never use in-process subagents.
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
  and a broken baseline makes a bisect blame every pending unit (verify now checks the
  baseline first, but the split race still corrupts `build/`).

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
