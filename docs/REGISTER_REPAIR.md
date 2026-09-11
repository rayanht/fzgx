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

`tools/solve_regalloc.py` is an explicit experiment, not the production
replacement for `regalloc.search`. It parses expression precedence, handles
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

Reproduce from the frozen diagnosis directory:

```sh
uv run tools/solve_regalloc.py --corpus .fzgx/near95-fast-batch \
    --output .fzgx/regsolve-replay --probes 32
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

`tools/capture_mwgraph.py` now reads the **actual** interference graph before
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
uv run tools/capture_mwgraph.py --archive state/repairs/register_graphs_20260911.json.gz
```

Capture a frozen diagnosis corpus, or recompute constraints from its cache:

```sh
uv run tools/capture_mwgraph.py --corpus .fzgx/near95-fast-batch --output .fzgx/mwgraph
uv run tools/capture_mwgraph.py --corpus .fzgx/near95-fast-batch --output .fzgx/mwgraph --replay
```

Capture requires macOS's `xcrun lldb` and the repository's native Wibo with its
loader symbols. Cached replay rejects changed source hashes, header hashes or
compiler settings. The normal relocation-aware oracle and all 16 target hashes
remain the acceptance authority. No model batch was resumed.
