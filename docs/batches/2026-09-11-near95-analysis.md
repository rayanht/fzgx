# Unmatched near-miss audit, 2026-09-11

After `all-none-workers-20260911` finished, collected historical C candidates
through `seeds.recovered.SavedCandidates(95)`, including check archives, attempts,
lifts, SDK imports and unified fixup results. Selected the highest recorded score
per function, preferring recorded compiler settings on ties. This is a census of
one best historical candidate per function, not every alternate compiled again.

598 functions / 313,300 bytes had saved candidates above 95% (17,361 candidate
records). All 598 compiled with their saved compiler/settings. 592 / 311,948 bytes
still scored above 95%; six selected candidates fell below the threshold. Other
historical alternatives for those six were not rechecked. The ledger alone listed
526 functions / 268,708 bytes: it misses some saved repair/check results.

Local evidence: `.fzgx/reports/near95-current/seeds.json`, `analysis.json`,
`detailed.json`, and `releases.json`. Sources are frozen alongside the manifest.
The first pass used `fzgx stuck --min-percent 95 --seeds` on that manifest.
The detailed pass uses the same batched oracle and row classifier but removes
oracle-accepted pool/absolute/equivalent-relocation rows before classification.
No reconstructed C or shared declarations were changed.

## Current differences, excluding already accepted binding rows

| Structural category | Functions | Retail bytes |
|---|---:|---:|
| Mixed instruction, address, type, binding or frame differences | 397 | 230,480 |
| Register fields only | 125 | 53,332 |
| Register fields and scheduling | 22 | 12,084 |
| Scheduling only | 13 | 3,868 |
| Immediate/address differences, possibly with registers | 19 | 5,884 |
| Stack offsets, possibly with registers | 5 | 1,276 |
| Extensions plus registers | 4 | 1,516 |
| Relocation targets only | 2 | 412 |
| Already exact in the function oracle | 5 | 3,096 |

These are structural classifications, not proofs of semantic equivalence. Three
of the register-only functions trigger the value-flow diagnostic. Two definitely
swap different loaded values at stores; the third involves fused floating-point
operand ordering and requires a more precise diagnostic before calling it wrong.
Mixed categories overlap: 82 functions have remaining relocation rows, 57 have
frame differences, and 202 have opcode substitutions. Those are not 82 or 57
independent closures. Accepted binding rows already exist in 549 candidates.

170 non-exact candidates have at most four actionable differing rows; 306 have
at most eight. 135 still have more than twenty. The original aligned-diff median
is eight rows. Objdiff similarity is not the fraction of exact instruction words:
`fn_80072EDC` scores 98.07% yet differs in 121 register-bearing rows, and
`fn_80048340` scores 99.53% with 200 differing rows. Rank remaining rows and
machine-word errors alongside similarity.

## Concrete recurring blockers

1. **Register lifetime, expression selection and scheduling.** The combined
   structural bucket is 160 functions / 69,284 bytes. Direct operand-order
   witnesses occur in 31 functions; nine differ *only* in operand commutation:
   `fn_1_3FCB0`, `fn_1_530C8`, `fn_1_79C88`, `fn_1_84038`, `fn_1_F7F48`,
   `fn_1_E594C`, `fn_15_5864`, `fn_80015D7C`, `fn_80053DB4`.
   `fn_1_530C8` has four `fadds f0,f0,f1` versus `fadds f0,f1,f0` differences.
   The existing unified fixup was probed on this actual seed: one round, 80
   proposals, 81 compiles including baseline, 0.356 seconds, zero improvement.
   The proposal list contains expression swaps, pointer arithmetic swaps,
   declaration changes and optimizer pragmas; its cap truncates later expression
   sites. Reversing source operands is not guaranteed to reverse MWCC operands.
   The missing step is selecting and composing source-realizable changes from
   the actual mismatching value/expression, rather than broad spelling retries.
   Existing capture/response composition should be extended, not duplicated.

2. **Wrong values masquerading as allocation.** `fn_1_72318` and `fn_1_83CB0`
   store f0/f2 into the opposite 0x0c/0x2c fields while the producing loads have
   not swapped. They score 99.8% and 99.67%. This is a source data-flow problem.
   `fn_80039C40` writes offset 0x6c2 where retail writes 0x7a8 alongside genuine
   register differences. Register search alone cannot repair these bodies.
   The current oracle only invokes value-flow analysis when *all* aligned
   instructions normalize identically after removing registers
   (`tools/fzgx/oracle.py:309`). Mixed functions therefore lose that diagnostic.

3. **Interior symbols and entrypoints.** Both `fn_8001C4A8` and `fn_8001C62C`
   differ only between `lbl_801A697C+4` and `lbl_801A6980`. The latter is an extern
   invented in the candidate, absent from current symbols.txt; the former is an
   owned eight-byte object. `_equivalent_reloc_rows` requires both names in the
   project symbol map, so it correctly refuses to accept this undefined name.
   This needs a proven symbolic binding/generator repair, not just treating the
   two printed addresses as equivalent. Separately `fn_1_129D9C` has just one
   differing call: retail calls `mathutil_mtxA_rotate_z+0xc`, the candidate calls
   the start. Similarity is 99.97%, but these are different entrypoints.

4. **Shared pools and stack layout.** `fn_1_59B00` has six remaining rows:
   two pool relocations and four pool-load offsets. Its literals are packed
   privately rather than at the retail shared pool offsets. A simple symbol
   retarget cannot change ordinary load immediates. `fn_80048340` is a coherent
   5,096-byte layout target: 196 of 200 differing rows are stack offsets, with
   four insertion/deletion rows. Many locals are shifted by four bytes.
   `fn_14_A2A4` has four stack offsets shifted by eight bytes. These need generated
   local-object layout/lifetime constraints, not another compiler-flag sweep.

5. **Object success does not imply integration.** Five selected bodies currently
   pass the function oracle: `fn_12_8F80`, `fn_1_11ABC`, `fn_1_12CCB0`,
   `fn_80010CB0`, `fn_80072614`. Three have recorded link rejection. The saved
   `fn_1_12CCB0` body defines `fn_1_12C7B8` again; prior link output reports that
   duplicate definition. The latest verifier rejected `fn_12_8F80` on the movie
   REL hash; the exact byte-level cause was not established in this audit.
   `fn_1_11ABC` comes from check archive 19; `fn_80072614` from a session-fixup
   report with GC/1.3. Their latest attempts ended at the check limit. They are
   integration candidates, not counted as verified or newly closed here.

## Harness implications

Across the two corrected non-reasoning batches, 517 released sessions in this
selected corpus ended above 95%; 47 included a voluntary release reason. Many
correctly name concrete diffs, but statements that a register permutation is
unavoidable are not compiler proofs. Some confuse binding and data-flow failures
with register allocation. Increasing check limits does not address these gaps.

Prioritize the 170 candidates with up to four actionable rows: resolve known
value/address errors and exact-but-unintegrated results first, then drive the
existing unified engine with operand/lifetime constraints. In parallel within
that same engine, stack-layout recovery has a concrete large-function exemplar.
No evidence here supports a single missing header or global compiler flag: every
selected candidate compiled, and the remaining differences have distinct causes.
