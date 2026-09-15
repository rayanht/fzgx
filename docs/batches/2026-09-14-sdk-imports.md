# SDK importer recovery — 2026-09-14

Integrated **15 functions / 9,120 bytes** of matching C. The ledger moved from
**4,989 to 5,004 matched functions**; 2,190 functions remain unmatched.

| Library | Functions | Code bytes |
| --- | ---: | ---: |
| OS | 2 | 1,624 |
| SI | 2 | 892 |
| DVD | 5 | 3,396 |
| PAD | 6 | 3,208 |

Five functions (1,992 bytes) link directly from C. Ten (7,128 bytes) are accepted
**pool matches**: their C passes the object oracle, while the build retains the
retail object until shared-data ownership is completed.

The regenerated build report is **28.602636% matched code**. The initial
on-disk objdiff report was stale; its change is not the byte gain for this batch.
The 9,120-byte gain is the sum of the fifteen newly accepted retail functions.

## What unblocked the imports

- Native SDK object definitions preserve section-base addressing. Measured gaps
  retain object offsets; discarded BSS primers preserve first-access order.
- Empty aggregate views are omitted. Shared strings and typed objects use
  compatible declarations for their common anchor.
- Diagnostic build dates and times bind to measured retail strings of the same
  fixed-width format. Boot-information addresses use linker-generated constants.
- Promoted local/global names normalize consistently in the importer and BSS oracle.
- Subobjects such as PAD ResettingBits use the existing verified relocation alias
  path, with donor object size checked against the owning retail object.
- Declaration closure retains initializer-inferred array bounds for sizeof and
  forward declarations for callbacks referenced by inline helpers.

## Accepted functions

| Retail symbol | SDK function | Bytes |
| --- | --- | ---: |
| `OSExceptionInit` | `OSExceptionInit` | 640 |
| `OSInit` | `OSInit` | 984 |
| `GetTypeCallback` | `GetTypeCallback` | 664 |
| `SISetSamplingRate` | `SISetSamplingRate` | 228 |
| `__DVDInterruptHandler` | `__DVDInterruptHandler` | 736 |
| `fn_800162A0` | `AlarmHandler` | 132 |
| `fn_80016394` | `Read` | 272 |
| `fn_80016524` | `DVDLowRead` | 664 |
| `fn_80018D1C` | `cbForStateBusy` | 1,592 |
| `fn_8001C704` | `PADTypeAndStatusCallback` | 812 |
| `fn_8001CB64` | `PADReset` | 256 |
| `fn_8001CC64` | `PADRecalibrate` | 260 |
| `fn_8001CD68` | `PADInit` | 536 |
| `fn_8001CF80` | `PADRead` | 940 |
| `fn_8001DC3C` | `OnReset` | 404 |

## Validation

- `python3 configure.py && ninja`: **16 files OK**.
- `uv run tools/fzgx.py lint`: **0 findings**.
- Fresh donor preparation and MWCC/object checks reproduced **15/15** matches.
- A real callback candidate with an unproven BSS name was rejected by the oracle.
- `fzgx snapshot` updated the committed ledger.
- Source identities, compiler settings and accepted C hashes are recorded in
  [the batch manifest](2026-09-14-sdk-imports.json). Donor revisions and bindings
  are in `state/sdkimports/{os,si,dvd,pad}.json`.

## Remaining evidence / known issues

- CARD, EXI, AR, DSP and MSL had no remaining saved import candidates.
- SIInterruptHandler now has the native storage offsets, but its section-base
  registers still differ. VI candidates retain layout differences.
- The two 944-byte ADX Wav16 decoder copies remain unmatched. Widening the sample
  local from unsigned short to int reduced one measured candidate from 51
  differing instruction rows to one (235/236 identical words). A remaining
  srawi/extrwi difference in the unrolled stereo loop did not close under the
  compiler and expression probes. It is excluded from the accepted byte count.
- SDK runtime/GX candidates containing inline assembly remain outside C import.

No model workers were launched. The agent contract now records the declaration,
native storage, symbol-promotion and regeneration checks that were missing.
