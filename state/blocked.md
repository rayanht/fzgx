# Blocked large near matches

Triage stays local. Candidates and compiler settings are preserved in
`state/repairs/large_near_frontier_20260914.json.gz`. The measured differences
below do not imply that declaration order alone can repair a function.

| Function | Words | Shape edits |
| --- | ---: | ---: |
| `fn_12_975C` | 12 | 0 |
| `fn_12_3DB8` | 16 | 0 |
| `fn_1_D123C` | 16 | 2 |
| `fn_8_2660` | 155 | 10 |
| `fn_10_1C2D8` | 71 | 21 |
| `fn_12_BBC0` | 28 | 13 |
| `fn_3_1D338` | 112 | 6 |
| `fn_12_364CC` | 95 | 3 |
| `fn_1_9012C` | 111 | 26 |
| `fn_16_4E90` | 139 | 35 |
| `fn_1_AFC8` | 48 | 4 |
| `fn_1_15C6C0` | 254 | 43 |
| `fn_3_255DC` | 240 | 27 |
| `fn_1_13B98` | 241 | 17 |
| `fn_12_23F5C` | 87 | 5 |

The 2026-09-15 shared-state pass linked `fn_8001B42C` from C.
`fn_3_1D338` now has a retail zero palette and corrected multiplication
association; the 109-word/8-shape alternative is also preserved in
`state/repairs/shared_regions_20260915.json.gz`. Neither customization
candidate is a full match. See `docs/batches/2026-09-15-shared-regions.md`.
