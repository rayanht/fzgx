# Region recovery: results and failed strategy

Baseline: `ff1a30f9`. Eight functions added **22,820 verified C-linked bytes**,
or **0.777 percentage points** of the 2,937,044-byte function corpus.
The baseline ledger has 845,136 matched bytes. Earlier commentary's 857,556-byte
baseline was incorrect; the gain above comes from comparing function statuses
against the committed baseline, not subtracting those inconsistent totals.

| Function | Bytes | Repair |
| --- | ---: | --- |
| fn_8_2660 | 10,284 | Native DATA/RODATA/BSS layout, DATA pool creation before BSS, active lifetime settings, array address expressions, measured BSS subobject bindings |
| fn_3_1D338 | 6,388 | Palette bytes, float rounding, coordinate store order, reciprocal division and integer compound assignment |
| fn_1_B3900 | 1,972 | CARDUnmount result width and distinct state/address loads |
| fn_12_3DB8 | 1,776 | Counted-loop variable lifetimes and outgoing counter values |
| fn_1_18B40 | 1,000 | Reversed indirect callback arguments |
| fn_1_9FFD8 | 572 | Native BSS and allocation-size argument type |
| fn_1_51C74 | 492 | FPR declaration projection and multiply operand order |
| fn_3_10B68 | 336 | Overlapping strided field views |

Source commits: `a12e5944`, `9cbfc97d`, `89701533`, `8a610432`.
Title initially entered as a pool match. Canonical names for individually proved
BSS subobjects then allowed its compiled C object to link. Final link verification
passed all 16 hashes; `fzgx lint` reported zero findings.

Portable inputs, compiler settings, source edits and remaining candidates are in
`state/repairs/region_scale*20260915.json.gz` and `fixup_imports.json`.

## Why this did not meet the requested scale

The user reported roughly one hour and $80 in model credits. I do not have an
independent billing measurement. The achieved gain did not justify the approach.
I repeatedly returned to function-local spelling and allocation probes instead
of demonstrating a repair with substantial corpus-wide closure yield.

- Refreshing 702 shortlisted saved functions produced no immediate exact matches.
- The large-layout followthrough compiled 28,668 candidates without an exact match.
- Several movie constructor batches changed allocation without closing its seven
  repeated cleanup loops. Its retained frontier has 70 differing words, zero shape
  differences. The constructor is still unmatched.
- fn_1_9012C remains unmatched; native data reconstruction improved its instruction
  structure but did not close the function.
- Some manual title index replacements were no-ops because preprocessed C had a
  space before `]`. Some pragma experiments were overridden by later pragmas.
  Those experiments established nothing about the intended changes.

All search processes were stopped/finished when the user rejected this strategy.
Do not resume these broad batches. A future approach needs a measured cohort,
a demonstrated shared cause, and a stopping condition based on verified bytes
closed per unit of work. Higher similarity alone is insufficient.

## Reusable evidence

- Read floating allocation constraints from the FPR preallocation snapshot;
  the later GPR snapshot already contains physical floating registers.
- Split column-zero grouped declarations before capturing local allocation.
- MWCC required three referenced initialized DATA objects in a preceding primer
  to establish the title DATA pool before BSS. One or two references did not.
- Inferred pointer arrays can extend into string bytes. Preserve bounds through a
  union of word storage and the original pointer-array view. Do not emit string
  words as literal pointer casts. The title's full oracle verified this layout.
- BSS section-base equality does not establish each member's ownership. Prove and
  bind every physical member before externalizing the private section.
