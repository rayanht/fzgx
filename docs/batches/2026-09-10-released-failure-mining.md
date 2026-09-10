# Released batch: recurrent failures and deterministic repairs

Audited all 457 sessions of `deepseek-released-appserver-457-low-20260910`:
47 verified matches, 410 releases, zero terminal failures. The batch took
4,481.4 seconds and cost an estimated $13.24. Its 30 live verification passes
had no errors or rejected matches.

The revised deterministic fixup recovered **three more functions / 676 bytes**.
All three passed the combined `claim --check` preflight with one check each,
zero model calls, and all 16 target hashes. Source commit: `ec73466`.

## Recurrent issues

| Finding | Measured extent | Action / remaining limitation |
|---|---:|---|
| Stale-check releases | 407 of 410 releases | Code-generation plateaus dominate; raising limits alone does not repair them. |
| Register allocation / instruction ordering only | 134 functions, 39,296 bytes | Preserve the original source through fixup search; one exact closure. |
| Lost optimizer state | One exact match in this batch; another in the preceding batch | Add function-scoped `opt_dead_assignments off/reset`, equivalent here to the successful `-opt nodeadstore` probe. |
| Invalid patch anchors | 28 errors in 24 sessions | Return the current source under the ownership guard, without modifying it or consuming a check. |
| Retriable stream errors | 178 errors in 151 sessions | Record retries separately from final status and emit compact stream-activity counters. This improves diagnosis; it does not repair the network/provider. |
| Excessive reasoning / output-limit failures | 19,975,183 of 20,602,721 reported output tokens were reasoning; 28 output-limit errors in 25 sessions | Confirmed `low` on the actual request. All 25 affected sessions released. Response-length behavior remains unresolved. |
| Compile failures during edits | 78 failures in 63 sessions | Mostly undefined locals, incompatible types, and malformed edits. Correct the missing owned SDK header in hardware-register guidance and generated C. |
| Unintended built-in tools | Three built-in patch failures | Remove the catalog's patch tool and disable request-user-input through runner-local settings. |

Transport errors comprise 144 network/decoding errors, six timeouts, and 28
output-limit errors. Categories overlap across sessions. All were marked
retriable; final outcome counts alone hid them. Reported token totals come from
increments in cumulative usage, avoiding duplicate final usage events. There
were 1,589 usage updates with new output; failed streams without usage are not
included in that response count.

All **410 saved best candidates compile**. There is no evidence of a universal
missing-header or compiler-flag problem. There is a specific header error:
`vu32` belongs to `dolphin/types.h`, while the prompt and lifter allowed only
`types.h`. The lifter now includes the owning header for hardware declarations
and handles a block address formed directly by `lis` plus a load/store offset.
The regenerated `fn_8008EED8` compiles with symbolic `__PIRegs` accesses; it is
92.34849%, not an additional match or a replacement for its better saved C.

Startup also had a two-queue problem: all claims queued before their initial
checks. Median preparation time was 145.472 seconds. Claim and preflight now
execute in one CLI transaction/tool slot. Three real exact-seed preflights
validated that path; no new full-width startup timing is claimed.

## Repair results

| Function | Bytes | Deterministic change |
|---|---:|---|
| `fn_15_2D74` | 280 | Reorder existing local declarations, retaining the original candidate as a search seed. |
| `fn_15_537C` | 224 | Recover both repeated float literals from the retail relocation's bytes together. |
| `fn_8002A698` | 172 | Restore function-local dead-store optimizer state. |

The normal fixup previously missed `fn_15_2D74`: a `peephole off` candidate
improved masked instruction-word agreement from 84.29% to 97.14%, and the
register search discarded the original C. That original still had an exact
declaration-order solution. Keeping both seeds within the existing six-second
budget closed it in 1.07 seconds in the isolated replay.

The complete revised fixup pass tried 107,698 candidates across all 410 releases
in 205.409 seconds and returned these same three matches. A separate nine-way
compiler/flag probe made 3,690 compilations and found only the dead-store match.
No reconstructed C was manually edited.

## Remaining buckets and failed experiments

The initial classification was 263 mixed (96,048 bytes), 94 register allocation
(29,340), 15 scheduling (2,968), 25 allocation plus scheduling (6,988), three
frames (836), six immediates (1,512), three relocations (872), and one extension
plus allocation (392). The 134 allocation/ordering cases form the largest clean
bucket; the larger mixed bucket does not yet have one demonstrated common fix.

The original allocation search found one match in 19,042 candidates. Expanding
declaration permutations inside nested scopes tried another 21,831 candidates
on the remaining 133 functions with no match or score improvement. That search
expansion was removed. The declaration parser correction remains: it preserves
qualifiers and accepts multiword types and multiple pointer levels.

Data-binding experiments also left two concrete gaps. `fn_8001C4A8` requires
retail `lbl_801A697C + 4`; casting to a base, using an array, and using fields
changed MWCC address generation and did not match. `SIGetType` retains a local
static-symbol ownership mismatch involving a compiler-generated `$` name.
Neither was accepted by weakening relocation checks. These binding cases and
the unresolved allocation/ordering corpus are better targets for further tool
work than another undifferentiated matcher batch.

## Reproduction and validation

```sh
uv run tools/diagnose_batch.py --batch BATCH --transcripts --output DIRECTORY
uv run tools/diagnose_batch.py --batch BATCH --seeds ORIGINAL_MANIFEST \
  --min-percent 0 --output NEW_DIRECTORY
uv run tools/diagnose_batch.py --repair --output NEW_DIRECTORY
```

Compilation freezes release C and its recorded compiler settings. `--repair`
exports `repair-manifest.json` for ordinary seeded preflight and verification.
Local inputs/results are in `.fzgx/diagnostics/released-appserver-all/`;
committed summary and provenance are the adjacent JSON and
`state/repairs/released_20260910.json`.

A localhost-only request capture confirmed exactly `write_unit`, `patch_unit`,
`check`, and `release`, plus `reasoning.effort=low`. Replaying all 457 real logs
through the revised event handler retained exact usage totals and counted all
178 retries. An owned shadow copy of real `fn_80021930` verified patch feedback,
unchanged C/counters after invalid anchors, ownership enforcement, and preserved
matching status. Validation added no unit tests and made no model requests.
`fzgx lint` returned zero findings; the verifier accepted all three candidates,
rejected none, and passed all 16 hashes.
