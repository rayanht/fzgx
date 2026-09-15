# Large near-match corpus — 2026-09-14

## Deterministic matches

Four functions totaling **6,056 bytes** pass the complete object oracle.
Integration and final link status are recorded below after verification.

| Symbol | Bytes | Recovered source structure |
| --- | ---: | --- |
| `fn_8_1394` | 2,164 | Floating comparison operand lifetime and shared BSS member bindings |
| `fn_1_988DC` | 1,340 | Retail floating clamp branches and early squared counter |
| `fn_1_13D460` | 1,452 | Early count assignment and strip-position helper expression order |
| `fn_1_13C1A0` | 1,100 | Ten rows of five words, image initialization and temporary lifetimes |

The portable archive `state/repairs/large_regions_20260914.json.gz`
reproduces **4/4** object matches with the recorded compiler settings.
The new floating comparison and scalar-square generators also reproduce their
accepted candidates through the existing deterministic repair engine.

The BSS oracle now proves individual shared members reached through a verified
section base. It checks module, section, address and size before externalizing
any definition. Real ELF mutations with an invalid member size or address were
both rejected.

## Corpus evidence

The saved corpus contains 1,453 unmatched functions covering 1,134,088 bytes.
Refreshing 280 variants of 56 functions at least 1 KiB exposed the actual
instruction differences behind their high objdiff scores. A two-round repair
pass compiled 60,914 candidates, improved 27 functions and closed none by itself.
The four matches above required further measured source changes.

The 10,284-byte title state machine still has 155 differing words and ten
instruction-shape edits in its best saved candidate. A compiler capture
reproduces the stock allocator, but does not provide a source-realizable repair
for that instruction shape. Native pool experiments did not close it; a proposed
pointer-pool serializer produced no valid corpus candidates and was removed.
No entire large translation unit has been closed by this pass so far.
