# Deterministic small-function repairs, 2026-09-09

Starting point: 77df36b; 3,545 matched C functions, 107 assembly units,
3,656 unmatched. The under-256-byte corpus contained 1,176 functions / 179,864 bytes.

19 C functions were added, with every addition verified against all 16 target hashes:

| Pass | New matches | Evidence |
|---|---:|---|
| Saved-body baseline | 1 | AlarmHandler; 207,625 spelling variants closed zero additional functions |
| Accept existing CTR indirect-call handling | 3 | fn_80006D1C, fn_12_8A10, fn_12_2E374; 532 bytes |
| Rebind verified C with identical instruction shapes | 8 | All eight candidates passed the oracle and link |
| Targeted type/scheduling repairs before register permutations | 6 | Two callee return-type repairs, three statement-order repairs, one combined type/order repair |
| Include pointee types in repairs | 1 | fn_800829EC: char* to u8*, 99.861115% to 100% in 0.7 s |

The second full spelling pass tried 204,740 variants and closed zero functions.
The subsequent LR/CTR liveness changes produced drafts for 91 of 106 previously
filtered indirect-call functions, but the full lift pass closed no further functions.
A final repair-only pass over 1,137 saved bodies also closed none. These results
favor identified SDK source imports over more broad spelling searches.

Tooling now supports size-filtered classification/sweeps, repair-only sweeps, and
verified source reuse. Search candidates are prioritized before truncation, discarded
candidates remain eligible, and confirmation preserves compiler flags. Diagnostics
compare relocation names instead of unrelated symbol-table indices. Draft guidance
no longer asserts that inferred declarations are correct by construction.

Validation: configure/ninja succeeded; `dtk shasum -q -c config/GFZE01/build.sha1`
printed `16 files OK`; `fzgx lint` reported zero findings. No unit tests retained.
No pushes. The interrupted eight-worker batch's claims were released; no further
Luna workers were launched after the deterministic-work redirect.

Next priority: deterministic SDK C imports, CARD first (52 functions / 19,080 bytes),
then OS, EXI and SI. Small-function closure is no longer a prerequisite.
