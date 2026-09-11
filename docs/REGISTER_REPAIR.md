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
