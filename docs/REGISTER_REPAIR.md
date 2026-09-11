# Register repair measurements, 2026-09-11

The stopped `deepseek-under1k-fast-512-20260911-021006` batch supplied
268 unmatched saved bodies at >=95%, totaling 79,616 bytes. Of these,
70 were classified as register-only from instruction spelling. That label
does not prove equivalent value flow.

## Findings

* The existing search enumerates up to 720 declaration orders before most
  other rewrites. Leading declarations exclude nested blocks. Its operand
  commutations, supplied by the separate spelling search, only recognize
  already-parenthesized simple expressions.
* Operand ordering, common subexpressions, declaration scopes, initialization
  order, and temporary materialization are coupled compiler decisions.
  A rewrite may repair some fields and disturb others; greedy improvement
  and independent-bit composition do not capture all these interactions.
* `fn_1_83CB0` is a concrete false allocation diagnosis: the stores at rows
  21 and 23 consume the wrong load results. Its 99.666664% similarity does
  not imply that physical register reassignment can repair it. The new
  `regflow` diagnostic distinguishes this from reordered intermediate
  producers, such as `fn_800581CC`.

`regflow` follows supported instructions within linear regions, discards
facts at branch targets and unknown operations, and respects call clobbers.
It reports only known non-stack store-value conflicts. It is neither a
whole-function equivalence proof nor permission to accept object differences.
The oracle's matcher output now includes these conflicts; `stuck` labels
them `value-flow`. Match acceptance is unchanged.

## Bounded compiler-response experiment

The original bounded compiler-response experiment preceded consolidation into
`fzgx fixup`. Its candidate generators and response algebra now share the engine. It parses expression precedence, handles
casts and repeated expression sites, probes nested declaration order, scopes,
materialization and optimizer state, then attempts to combine observed
repairs. It uses both disjoint repaired bits and bounded GF(2) response
equations. The compiler is nonlinear: every proposed combination is compiled
again and must pass the complete relocation-aware oracle.

Compiles are grouped across functions by module and recorded compiler options.
The input C hash is checked, and settings are preserved in output manifests.

| Pass on the same 70 bodies | Candidates | Wall time | Exact object matches |
| --- | ---: | ---: | ---: |
| Initial bounded probes | 1,274 | 3.941 s | 0 |
| Nested declarations, optimizer state, response equations | 1,625 | 7.027 s | 1 |
| Final version including value-flow diagnostics | 1,624 | 9.904 s | 1 |

The final pass improved 17 word scores, including its one exact match,
`fn_10_260D4`. That match was also found by the existing repair pass.
Final amortized time was **141.5 ms/function**, including 805.9 ms total
for proposals/reading diffs, 8,355.3 ms for probes, 621.5 ms for composition,
and 117.5 ms for combined compilation. This is throughput, not a per-function
latency guarantee. Frozen baseline compilation is excluded.

This does **not** solve register allocation generally. The old repair pass
found two exact objects in this register-only subset; the bounded pass found
one. It must not silently replace the old pass or claim equivalent coverage.
No equation-composed candidate closed in this corpus. Isolated commutations,
simultaneous repeated commutations, and explicit shared floating temporaries
also failed to close `fn_80015D7C`; more spellings alone lack evidence here.

Run the consolidated engine on the frozen diagnosis directory (the measurements
above describe the original experiment, not this expanded candidate set):

```sh
uv run tools/fzgx.py fixup --corpus .fzgx/near95-fast-batch \
    --output .fzgx/fixup/replay --max-candidates 32
```

Per-function hashes, attempt IDs, settings and measurements are committed in
`state/repairs/register_solver_20260911.json`. A coverage improvement needs
constraints connecting C expression/lifetime decisions to compiler allocation,
including decisions whose intermediate probes do not improve the score.
The current experiment measures responses; it does not recover MWCC's allocator.

## Integrated repairs from the full near-miss pass

The existing deterministic pass found four exact objects. Two passed source
lint and all 16 target hashes: `fn_10_260D4` and `fn_1_FC60C`, totaling
612 bytes. `fn_8006EFB4` remains unintegrated because of a literal pointer
to locked-cache memory; `fn_80083BCC` needs justified shared-control-flow
annotations. Neither is counted as an integrated match.

The batch remains stopped. No model sessions were launched for this work.

## Exact allocator capture and replay

`fzgx fixup --capture` reads the **actual** interference graph before
and after `SelectColors` in SHA-256-pinned GC/1.2.5n and GC/1.3.2. Native Wibo
runs under local LLDB; the compiler and generated instructions are not patched.
Sources with identical compiler settings share an invocation. Function-entry
breakpoints bind captures to function names, excluding emitted helper functions.
No personal debugger or Codex configuration is changed.

`mwgraph.py` implements the non-spilling simplify pass and color selection.
It preserves coalesced ghost edges in degree counts and reads neighbors'
physical fields directly, as the compiler does. It does **not** recursively
resolve coalesced parents while coloring. Unsupported simplify spill decisions
are explicit, not guessed. A constructive inverse finds sufficient selection
orders without enumerating permutations. Failure to construct an order is
inconclusive; a witness is not proof that a C edit can realize it.

Measured on the same 70 frozen candidates:

| Operation | Total | Per function |
| --- | ---: | ---: |
| Cold capture, one compiler process per source | 37.18 s | 531 ms amortized |
| Cold capture, five grouped compiler invocations | 4.45 s | 63.6 ms amortized |
| Simplify + color replay | 3.56 ms | 0.048 ms median |
| Reconstruct captured-color order witnesses | 25.44 ms | 0.257 ms median, 2.44 ms maximum |
| Target constraints and declaration projection | 34.34 ms | 0.415 ms median |

All **70 emitted function bodies are unchanged**, including 100% relocation-aware
object comparisons against their frozen baseline compiles. All **90 allocation passes**
for those named functions replay exactly. The earlier 93-pass count included
three passes from helpers emitted alongside `fn_1_579A0`; grouped capture now
separates those identities. Cold times include LLDB startup/capture, not corpus
loading; algorithm times exclude compilation and graph input decoding. These
are corpus measurements, not a general latency guarantee.

Target analysis finds 10 consistent fixed-graph hypotheses, 54 cases requiring
value-web alignment, and six with unsupported instructions. The ten hypotheses
produce nine selection witnesses across eleven graphs. **Zero declaration
projections pass the graph prediction; zero new functions are matched.**
Parameters, generated temporaries, coalescing, and scope-dependent creation
order cannot be arbitrarily reordered by shuffling declarations. We now check
that restriction before proposing a compile. Unsupported cases remain available
for further reconstruction; this does not prune them as impossible.

`fn_80015D7C` specifically needs reversed multiply operands at rows 8 and 20,
with an otherwise identity register map. Normal matcher check output now names
such operand-order differences separately from value-flow conflicts. Capturing
a graph does not recover the frontend expression/CSE decisions that produced it.
The remaining integration work is PCode value-web/source-origin alignment and
source transformations that realize those constraints. This tooling is an exact
allocator model and diagnostic foundation, **not a completed universal repair**.

The implementation is local and has no donor imports. Algorithm/layout research
used the CC0 [inspiredrobot/mwcc reconstruction](https://github.com/inspiredrobot/mwcc/tree/ef08e865561446c072f457eaf89bde9030cccb30),
particularly `Coloring.c`, `allocator_snapshot.py`, and `coloring_model.py`.
Its license is retained in `tools/licenses/mwcc-CC0.txt`. GC/1.3.2 addresses and
layouts were recovered from the installed PE and validated by live captures;
`mwgraph.PROFILES` records exact binary identities. Only owned Python and
measurement data are included here, not compiler binaries or external-project
includes.

The committed compressed archive contains real graph captures, saved C seeds,
compiler flags/hashes, and header/source hashes. It is a repair corpus, not a
unit-test suite. Replay it without MWCC, LLDB, or the original scratch directory:

```sh
uv run tools/fzgx.py fixup --archive state/repairs/register_graphs_20260911.json.gz
```

Capture a frozen diagnosis corpus, or recompute constraints from its cache:

```sh
uv run tools/fzgx.py fixup --capture --corpus .fzgx/near95-fast-batch --output .fzgx/mwgraph
uv run tools/fzgx.py fixup --capture --corpus .fzgx/near95-fast-batch --output .fzgx/mwgraph --replay
```

Capture requires macOS's `xcrun lldb` and the repository's native Wibo with its
loader symbols. Cached replay rejects changed source hashes, header hashes or
compiler settings. The normal relocation-aware oracle and all 16 target hashes
remain the acceptance authority. No model batch was resumed.


## PCode-directed source repairs (2026-09-11)

The next pass connects captured PCode operands and source lines to virtual value
webs, aligns their emitted instructions with retail, and proposes C changes for
the implicated locals. Commutative operand choices, conflicting constraints and
unresolved rows remain explicit hypotheses. Declaration orders are evaluated in
the captured allocator before compilation; bounded exhaustion is reported as
such. One-field scalar carriers change MWCC's scalarization/temporary creation
order while retaining the declared scalar type. Source-line provenance also
finds locals hidden behind compiler-generated `@` temporaries. Generated C must
still pass the stock compiler, relocation-aware oracle and all target hashes.

This integrated **9 generated repairs / 2,944 bytes**. A target-binding correction
also recovered **5 already-exact saved bodies / 868 bytes**: **14 functions and
3,812 bytes total**, verified in commits `d684864`, `b1e4500`, and `44b5f02`.

The auto-object index previously keyed functions globally by bare symbol name.
Consequently, `title:_prolog` was compared against car_colchg's 664-byte entrypoint
instead of title's 296-byte entrypoint. Index keys, normalized-object caches and
caller/context lookups now retain module identity. The oracle rejects foreign
frozen targets, including same-sized ambiguous targets with different bindings.
One generated candidate was recovered for its actual owner, car_colchg; no
foreign-target score is accepted as a match. The historical audit invalidated
48 attempt records across 15 functions and re-scored 47 saved sources. Original
scores are preserved in `state/repairs/target_binding_v4.json`; replacement
attempts carry correct-module scores. The migration cutoff protects new attempts.

Measured on 265 frozen near misses:

| Pass | Compiler probes | Exact candidate functions | Improved functions, including exact |
| --- | ---: | ---: | ---: |
| Named scalar carriers | 228 | 5 | 21 |
| Source-origin and initialized carriers | 545 | 9 | 34 |
| Add generated block-copy temporaries | 1,073 | 9 | 40 |

The final pass spent **12.605 s generating candidates and 3.085 s compiling**;
cold grouped PCode capture took **11.860 s** separately. These are corpus totals,
not per-function latency guarantees. The nine candidate functions include the
misbound entrypoint subsequently recovered for its correct owner. Parameter-home
rewrites added 32 probes with zero improvements and were removed. A further pass
on the 31 nonexact improvements used 240 probes, improved five seeds, and closed
zero additional functions. These results do not imply universal register repair.

Live capture now supports hash-identified GC/1.2.5, GC/1.2.5n, GC/1.3 and GC/1.3.2.
The remaining three GC/1.3 corpus functions also captured and replayed exactly;
14 repair probes yielded no improvements. All captured objects stayed unchanged.
There is no runtime dependency on donor sources or modified compiler binaries.

```sh
uv run tools/fzgx.py fixup --capture --corpus CORPUS --output CAPTURES
uv run tools/fzgx.py fixup --corpus CORPUS --captures CAPTURES --output REPAIRS
uv run tools/fzgx.py fixup --corpus CORPUS --output REPAIRS --saved --apply
```

Recapture after changing source, headers or compiler settings. Improved corpora
preserve compiler settings and replace seeds only on a strictly improved word
score; that score is not relocation-aware match acceptance. Integration rechecks
current module targets and performs the complete link verification.

The portable archive preserves all 14 seeds, generated hashes, the nine repairs'
PCode/allocator captures and baseline/retail words, plus the best 31 nonexact
improved seeds (including the five further improvements). Reproduce the accepted
source transformations without scratch files or a compiler:

```sh
uv run tools/fzgx.py fixup --archive state/repairs/mwgraph_repairs_20260911.json.gz
```

This reproduces all 14 source hashes; compilation and link acceptance are separate
checks. `state/repairs/mwgraph_imports.json` records compiler settings, transforms,
owning source and verification commits. No unit tests were added and no model
batch was resumed.


## Consolidated engine

`fzgx fixup` is the only repair command. Session release, lifter repair and the
orchestrator API invoke the same engine in `tools/fzgx/fixup.py`.
The former regalloc, spell, line-repair, lab, response-solver and graph-repair
search loops are removed. Their source transformations live in
`fixup_source.py`; retail-derived candidates and line diagnostics live in
`fixup_evidence.py`. These helpers do not compile, run searches, cache or submit.
Stock allocator capture/replay lives in `mwgraph.py` and is dispatched through
this command too. SDK/data import and `stuck` remain separate because they import
sources/data or diagnose failures, rather than running competing fixup searches.

The engine batches compilation across symbols by module/compiler/flags, caches
by source, headers, compiler flags/binary, retail object and oracle fingerprint, and
confirms potential matches with the relocation-aware oracle. A bounded frontier
retains distinct emitted bodies; all candidate families share its limits.
Compiler-response compositions return to that same evaluator. There is one
report and one cache in the output directory; `--saved --apply` verifies and
integrates completed results without repeating search. Frozen sources and their
compiler settings survive every round. Historical scores select candidates;
current module targets determine their actual scores.

```sh
uv run tools/fzgx.py fixup --min-percent 95 --output .fzgx/fixup/near95
uv run tools/fzgx.py fixup SYMBOL --body candidate.c --output .fzgx/fixup/one
uv run tools/fzgx.py fixup --output .fzgx/fixup/near95 --saved --apply
```

The default corpus includes every distinct saved C/compiler combination above
the threshold, not only one best body per function. `--rounds 0` rechecks and
freezes that corpus without searching. `inputs.json`/`results.json` expose the
best unfinished seeds for graph capture; `report.json` retains all variants.
Use `--corpus PATH` to repair an existing frozen corpus. `--rounds`, `--beam`,
`--max-candidates`, and optional total `--budget` bound the single shared search.


Consolidation validation used 4,242 distinct saved C/compiler combinations across
399 unfinished functions. One round evaluated 22,896 additional candidates:
299.11 seconds cold, including 261.36 seconds in compilation/oracle evaluation.
The cached repeat, after replacing whole-body character LCS in edit composition
with line alignment and local span trimming, reused 27,138 results and compiled
one new combination: 14.29 seconds total, 0.132 seconds in compiler evaluation.
These are different cold/warm workloads, not a claimed 21x compiler speedup.
The round improved 153 best word scores and found 12 function-level matches.

Nine passed all target hashes immediately (2,596 bytes). Two other candidates
emitted 1,004 bytes of unused static helper copies outside their matching
functions. The unified engine now rejects such extra REL functions before
integration and generates explicit inline helpers. The two repairs passed the
stock object comparison in 0.49 seconds for 34 compiles, then one additional
cached-pass compile selected the all-helpers rewrite. Both subsequently passed
all 16 hashes: **11 functions / 3,564 bytes integrated** in total during
consolidation, with source and recipe provenance in `state/repairs/fixup_imports.json`. The remaining original
candidate is lint-rejected; it is not counted as integrated.

Known link-rejected source/compiler combinations are retained with header and
oracle fingerprints so unchanged saved inputs are not resubmitted repeatedly.
Best bodies also retain current relocation-aware percentages; the shared saved
candidate collector consumes those reports for subsequent repair/model batches.
The one-time target-index history migration is complete: its standalone auditor
is removed, and its immutable migration/provenance records remain in `state/`.
All future compilation goes through module-qualified targets in the engine.

## Expanded corpus and binding repairs

A three-round continuation covered 387 unfinished functions / 161,896 bytes.
It evaluated 57,127 new candidate records, with 44,912 actual compiles and
12,602 cache hits including baselines. Four functions (724 bytes) reached the
object oracle; 80 best instruction-word scores improved. Wall time was
1,045.16 seconds, including 824.21 seconds in compiler/oracle evaluation.
This broader search is not a millisecond-per-function result. Its four closures
used response composition, field order, a scalar carrier, and graph-guided
declaration order.

Graph evidence now follows changed frontier bodies across rounds. Captures
retain stock object/color replay validation; an unsupported spilling simplify
path is reported separately from a replay mismatch. Three such graphs previously
aborted an otherwise valid 380-function capture. Binding quality participates in
frontier selection, so identical instruction words no longer automatically erase
better data bindings.

The same engine now derives string-pool boundaries and padding from emitted
symbols and retail bytes and recovers named floating initializer anchors. Whole readonly pools require complete byte
and padding equality with no internal relocations. Newly recognized DOL switch
tables require every entry to resolve to the correct containing-function offset.
REL pool reads are section-qualified, including local-symbol suffix resolution.

Shared BSS uses the existing relocation-retargeting path: symbol identity,
object size, zero-initialized section and addends are checked before copies are
removed. Data already owned by the function's unit remains defined there.
This preserves MWCC's code generation for shared section bases and handles its
compiler-generated `$N` local-static symbols without inventing invalid C names.
Exact bodies with unresolved shared definitions or source-lint failures remain
searchable. Branch comments are generated only after a full object match; lint
rules and address restrictions are not waived.

The expanded historical eligibility threshold is 90%, selecting 595 functions
and 7,063 distinct source/compiler combinations. All were recompiled against
current module targets; historical percentages are eligibility, not acceptance.


The 595-function pass evaluated 57,644 bodies including baselines in 984.13
seconds (864.49 seconds in compiler/oracle evaluation). It found 22 object
matches and improved 150 best instruction-word scores. A final pass over those
595 best bodies evaluated 5,163 bodies in 44.42 seconds, including 21.33 seconds
in compiler/oracle evaluation. It reached **25 functions / 6,844 bytes**, all
subsequently linked from C and verified against all 16 target hashes. Code
progress moved from 21.80% to **22.03% (647,044 / 2,937,044 bytes)**.

Direct extern conversions, byte-pointer aliases and typed array views did not
close the remaining scalar-alias examples: their instruction sequences changed.
Those added generators were removed rather than retained as another low-yield
search family. Shared BSS was instead repaired by the verified binding path.

Integration exposed two additional symbol-promotion gaps: existing pool mappings
retained stale suffixed targets, and renamed source definitions also needed their
private mapping keys updated. Promotion now updates both, including `@`/`$`
identifiers. Ninja mappings quote and escape compiler-generated `$N` symbols
through both expansion layers. The verifier filters absent, untracked rejected
files from its dependency journal before staging, while retaining tracked deletions.
The final 24-function and one-function link checks both used the fast path.

`state/repairs/fixup_imports.json` retains all 25 original seeds and 51 successive
source-repair steps, in addition to generated C, compiler settings and verification
commits. No model sessions or standalone repair tools were added.
