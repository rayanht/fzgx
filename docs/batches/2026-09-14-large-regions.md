# Large near-match corpus — 2026-09-14

Integrated **8 new matches / 11,240 bytes**. Another **17 existing pool matches /
11,100 bytes** now link from C. Seven new matches link from C; the remaining
1,200-byte function is accepted as a pool match. Total additional code linked
from C: **21,140 bytes**.

The largest linked closure is the **6,608-byte memory-card state machine
`fn_1_AD264`**. The 2,164-byte title intro also links from C. No entire large
translation unit was closed; the 10,284-byte title state machine remains open.

The ledger moved from **5,004 to 5,012 matched functions**. There are 2,166
unmatched and 16 locally blocked functions, plus 114 assembly units. The fresh
build report is **28.985332% matched code** (851,312 / 2,937,044 bytes), up from
28.602636%; code linked from C/assembly is **28.69%**.

## New matches

| Function | Bytes | Repair |
| --- | ---: | --- |
| `fn_8_1394` | 2,164 | Floating comparison lifetime and shared BSS subobjects |
| `fn_1_988DC` | 1,340 | Retail floating clamp branches and early squared counter |
| `fn_1_13D460` | 1,452 | Count assignment and strip-position expression order |
| `fn_1_13C1A0` | 1,100 | Ten rows of five words and packet initialization order |
| `fn_8001AAB4` | 1,200 | Luna; accepted pool match |
| `fn_8007C910` | 1,276 | Luna; linked |
| `fn_1_E174` | 1,300 | Luna; linked |
| `fn_14_380` | 1,408 | Luna; linked |

## Shared tooling repairs

- Added measured floating comparison and scalar-square lifetime proposals, and
  the retail floating-clamp branch form, to the existing deterministic engine.
- Prove named BSS members reached through section bases by module, section,
  address and owner bounds. Normalize generated subobjects to canonical aliases.
- Remove private data primers only after their shared section is proven and no
  live relocation reaches the remaining storage. This links the memory-card
  state machine and several older pool matches.
- Compiler-response cache keys now include allocated symbol definitions. Code
  and relocation equality alone missed differently named BSS members accessed
  through a section base and could reuse stale binding evidence.
- Pool submissions now journal source and split dependencies for the next
  verified commit. Fixup provenance records pool status and joins that commit.
- Archives retain frontier variants scored by instruction words even without a
  full objdiff score; 34 such variants were previously omitted from this archive.
- Triage is local only. Removed GitHub issue creation from the CLI, API, agent
  instructions and ledger. Existing snapshots remain readable. The 16 issues
  opened during this pass were closed and the newly created label was removed.

## Corpus results

The saved corpus contained 1,453 unmatched functions covering 1,134,088 bytes.
Refreshing 280 variants of 56 functions at least 1 KiB exposed instruction
mismatches behind their high objdiff percentages. A two-round repair pass compiled
60,914 candidates and improved 27 functions but closed none by itself. Four new
matches required the subsequent measured source repairs.

The external Luna batch processed **48 functions / 111,592 bytes**, with 48 model
sessions and 16 local tool processes. It produced **4 matches**, 44 saved releases,
no failed sessions and no link rejections. Runtime: **695.5 seconds**. Cost:
**$2.853, an OpenAI standard-rate estimate**. See the
[worker report](2026-09-14-large-regions-workers.md).

The archive preserves **78 variants of 44 remaining functions**, including initial
candidates when worker edits did not improve their instruction match. Sixteen
functions with repeated attempts have [local triage notes](../../state/blocked.md).

## Validation

- `python3 configure.py && ninja` succeeded; `ninja progress` refreshed the report.
- `dtk shasum -q -c config/GFZE01/build.sha1`: **16 files OK**.
- `fzgx lint`: **0 findings**.
- All **21 deterministic object matches** and all **78 archived near-match
  variants reproduced from portable C and recorded compiler settings.
- Real ELF mutations with an invalid BSS member size or address were rejected.
- A private data object with an added live relocation was retained.
- Memory-card variants with different BSS definitions now have distinct response
  hashes and independent binding proofs.
- The issue-metadata migration preserved every ledger row; a historical snapshot
  restored successfully, and the local block operation retained its reason.
- `fzgx snapshot` refreshed the ledger. Source hashes, compiler settings and link
  states are in the [manifest](2026-09-14-large-regions.json).

## Remaining evidence

- The `colchg_selmate_init` upgrade passed the object oracle but failed a link
  hash. Its previous accepted pool source was reinstalled and hash-verified;
  it is excluded from the linked gain.
- `fn_8_2660` retains 155 differing words and ten instruction-shape edits in its
  strongest word match. Its stock allocator capture reproduces but does not
  supply a source-realizable repair for that shape.
- A pointer-pool serializer produced no valid corpus candidates and was removed.
  Native pool probes did not close the title state machine.
- Luna reduced `fn_1_D4370` to four differing words and one shape edit. Further
  clamp probes exposed the remaining branch/NaN distinction without closing it;
  those candidates remain archived.

All commits are local. Nothing was pushed.
