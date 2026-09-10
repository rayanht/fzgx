# Deterministic repairs after the Luna batch

Batch `near95-under500-20260910-001452` matched 63 functions and released 224.
The saved-candidate corpus contains 223 still-unmatched bodies, 50,288 bytes,
frozen with their checked compiler versions and flags.

Six additional object matches (648 bytes) came from:

| Repair | Functions | Bytes |
| --- | ---: | ---: |
| Read REL literal pools from the relocation target's section | 2 | 408 |
| Recover retail strings through DOL segment lookup | 2 | 128 |
| Recover an omitted return and forward the conditional callee's result | 1 | 48 |
| Apply existing hardware-access lint annotations to an exact saved body | 1 | 64 |

The largest clean category was 80 register/scheduling candidates, 15,292 bytes.
Existing declaration search tried 7,370 variants and matched none. Operand
commutation and stored-value swaps tried another 1,658 variants and matched
none; these unsuccessful additions were discarded. Return recovery tried 195
variants and closed `fn_80069AE0`. Rechecking 301 other saved bodies above 90%
after the pool fix found no further matches.

High objdiff scores are insufficient to select a repair: `TRK_main` scored
99.55% while referring to the wrong string. The remaining register/scheduling
category needs evidence about value lifetimes and call signatures, beyond
declaration permutations.

Local reproduction inputs and results are in `.fzgx/repair-near95/`:
`manifest.json`, `analysis.json`, `regalloc-before.json`, `return-results.json`,
`string-results.json`, `wider-results.json`, and `winners.json`. The frozen
manifest can be classified with `fzgx stuck --seeds PATH`.
