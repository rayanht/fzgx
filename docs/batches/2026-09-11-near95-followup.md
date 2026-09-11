# Remaining near misses after deterministic repairs

Refreshed after the 18 functions / 7,348 bytes integrated in `f7bf82d` and
documented in `b18aac1`. No additional functions were integrated during this audit.

Collected saved C through `SavedCandidates(95)` and selected the highest historical
score per unmatched function, preferring recorded settings on ties. Recompiled
all 580 selected bodies with their saved compiler/settings. All compiled; 574
still score above 95%, covering 304,600 bytes. Six selected bodies regressed below
95%; their other historical alternatives were not recompiled. This is a census
of selected candidates, not proof that every alternate has been exhausted.

Local frozen evidence: `.fzgx/reports/near95-after-repairs/seeds.json`, the adjacent
C files, and `analysis.json`. Reproduce with
`uv run tools/fzgx.py stuck --min-percent 95 --seeds .fzgx/reports/near95-after-repairs/seeds.json`.
Scores use the maximum of the oracle's reported and adjusted similarities for
eligibility; these percentages are not exact instruction agreement percentages.

## Distribution

The existing `stuck` diagnostic now excludes oracle-accepted binding rows from
failure categories, retains raw counts separately, runs value-flow diagnostics
on mixed candidates too, and separates stale historical scores in its summary.
536 of the 574 candidates have accepted rows. Those rows are not remaining work.

| Remaining structural category | Functions | Bytes |
|---|---:|---:|
| Mixed | 394 | 227,368 |
| Register differences only | 117 | 52,184 |
| Registers and scheduling | 21 | 11,124 |
| Scheduling | 14 | 4,928 |
| Immediates, possibly registers | 18 | 5,144 |
| Extensions and registers | 5 | 1,928 |
| Stack offsets, possibly registers | 4 | 1,032 |
| Object-exact, still unintegrated | 1 | 892 |

These are structural categories, not semantic proofs. In overlapping categories,
80 functions / 36,900 bytes have unresolved relocation rows, and 54 / 44,556 bytes
have stack-offset rows. Median actionable diff count is eight; 166 non-exact
candidates have at most four rows, 299 at most eight, and 131 exceed twenty.
29 candidates have explicit commutative operand-order witnesses.

## Concrete blockers and machinery gaps

* **Shared pool layout:** 27 candidates / 6,284 bytes have differing references
  to `lbl_1_rodata_2950`, the largest repeated named rodata group in this audit.
  `fn_1_59B00` (99.06%, 144 bytes) has six rows: the pool base and four load
  offsets. Retail uses 0x38/0x60/0x28/0x64; the private pool uses 0x10/0/4/8.
  The implicit integer-conversion bias belongs in that same retail pool.
  Equal literal bytes do not justify changing load instructions. The engine
  needs source-level recovery of the shared base and conversion lowering
  together. This is a coherent investigation set, not 27 promised closures.
* **Incorrect member layouts:** `fn_12_B9E8` (96.58%, 472 bytes) declares a
  0x3C-byte gap after offset 0x28C, placing `field_12c8` at 0x2C8 and
  `field_1304` at 0x304. Retail accesses 0x12C8 and 0x1304. The missing 0x1000
  bytes are in an internal gap, while earlier fields are correctly placed.
  `fn_80039C40` (98.92%, 520 bytes) places a field named `unk_7A8` at 0x6C2.
  Existing immediate substitution cannot recover a field's computed offset
  when that number never appears as a C literal. Front-padding and adjacent-field
  swaps do not solve selective internal padding; the missing machinery is
  member-to-access constraints and compiler-checked layout proposals.
* **Bad intermediates remain selectable:** `fn_12_4D14` (98.94%, 256 bytes)
  contains an eight-byte `lab_pad` before its shared tables. Retail stores its
  result at 0x400; the candidate stores at 0x408 and shifts both table bases.
  Existing front-padding repair can propose removing it, but proposal availability
  is not proof that the entire candidate closes. Scoring must distinguish
  correcting an address from reducing register differences.
* **Stack object/lifetime recovery:** `fn_80048340` is 5,096 bytes and 99.53%,
  but has 200 actionable rows, 196 involving stack offsets, commonly shifted
  by four bytes. Many inlined serialization helpers contribute stack objects.
  `fn_8008EDF0` has only two rows, both using stack 0x24 instead of 0x10.
  Aggregate-copy temporaries in `fn_1_53B14` and `fn_1_53E40` start eight bytes
  too late while conversion scratch appears elsewhere. Local declaration
  permutations and scalar packing have not recovered these interacting layouts.
* **Type-driven instructions:** `fn_3_1A2EC` (98.98%, 412 bytes) has an extra
  `extsh` after a halfword load; the draft copies a `u16` field into `s16 flags`.
  Existing type-flip proposals should be evaluated against that use chain,
  rather than treated as an allocator problem. Other candidates mix rounding,
  comparisons and register changes; a global compiler flag is not established
  by these observations.
* **Integration requirements:** `fn_1_9EDE8` is currently object-exact (892
  bytes), but its saved body fails lint: hardcoded FIFO pointer plus unjustified
  volatile declarations. The existing hardware canonicalizer is the relevant
  path; this is not a remaining allocation mismatch.

The flow walker flags twelve candidates, but this is not twelve proven source
bugs: private-pool aliases and algebraically equivalent effective addresses also
produce different symbolic expressions. Inspect producer chains before using
these flags as repair constraints. In particular, identical store text can inherit
a difference from a prior pool load. Conversely, the explicit struct offsets
above are visible directly in the compiled accesses and C layouts.

There is no evidence of one missing header or universal compiler option blocking
this corpus. All 580 bodies compile. The largest category is mixed, while the
most concrete common repair targets are shared-pool lowering and member/stack
layout recovery within the existing fixup engine. More generic register search
alone does not address those failures.

Validation: real MWCC/object diffs for all 580 candidates; repository lint clean.
No reconstructed C, shared headers, or unit tests changed. The linked build was
already current; its 16 target hashes were rechecked.
