# Shared-state region closure — 2026-09-15 UTC

Compared with `28d95057`, this pass adds **9,548 bytes linked from C**.
It closes the contiguous **28,220-byte / 115-function** range from `DVDInit`
through `__AIDHandler` (`main`, start `0x8001776C`, exclusive end `0x8001E5A8`). The full VI region is
**7,012 bytes / 19 functions**, `0x8001A55C` through `0x8001C0C0` exclusive.
These region totals include previously linked functions; they are not new-byte counts.

## Accepted changes

| Function | Bytes | Previous state |
| --- | ---: | --- |
| `fn_8001B42C` (VI configuration) | 2,088 | Blocked, code-only match |
| `fn_80018D1C` | 1,592 | Pool match |
| `fn_8001AAB4` (VI initialization) | 1,200 | Pool match |
| `OSInit` | 984 | Pool match |
| `fn_8001C704` | 812 | Pool match |
| `__DVDInterruptHandler` | 736 | Pool match |
| `GetTypeCallback` | 664 | Pool match |
| `fn_80016524` | 664 | Pool match |
| `fn_8001CD68` | 536 | Pool match |
| `fn_80016394` | 272 | Pool match |

One function adds **2,088 newly matched bytes**. Nine previously accepted pool
matches add **7,460 bytes of direct C linkage**. No agents or swarms were launched.

## Structural causes and repairs

- VI configuration's saved data prefix put a timing table at the wrong offset
  and supplied zeros in place of initialized retail data. Reconstructing the
  prefix and its symbolic `getTiming` switch destinations preserves every
  instruction. The switch table retains its existing ownership; the private
  layout copy is removed after verification.
- Shared initialized pools now prove both bytes and every pointer relocation:
  offset, kind, module, section and destination. Anonymous size-zero section
  symbols cannot bypass pointer verification through a shorter byte comparison.
- Native BSS objects were missing canonical bindings. The repair generator now
  handles file-local names and SDK padding, while preserving already verified
  section anchors. Renaming an anchor had invalidated otherwise correct repairs.
- Four missing shared objects were measured from MWCC layouts and retail
  section-relative accesses: `__OSDriveBlock`, `__DVDLowAlarmForWA`,
  `__DVDLowPrev`, and `__DVDLowCurr`. Their **112 bytes** are imported through
  `fzgx data-import`, retaining `DVDCommandBlock`, `OSAlarm`, and buffer types in
  `include/dolphin/dvd/SharedState.h`.
- MWCC emits unused BSS definitions in reverse declaration order. The importer
  now accounts for this in data-only groups. Scoped `--regenerate` also respects
  explicit symbols and retains siblings in the same owning source.
- The whole-unit acceptance gate now honors a proven equivalent SDA binding for
  its selected function. It previously rejected `fn_80016394` after the object
  oracle had already proved the split-label/base-plus-offset equivalence.
- The SI layout primer is explicitly placed in the discarded `.fzgxpool`
  section, so corpus reproduction does not depend on DOL dead-code stripping.

## Largest remaining gaps

The 10,284-byte title state machine and 6,388-byte customization routine remain
unmatched. Their investigation produced reusable source corrections, not closures:

- `fn_8_2660`: bound the title buffer to the 64 bytes available before the next
  retail object. The object still has **155 differing words / 10 shape edits**.
  The layout parser now accepts spaces around `->` in preprocessed bodies.
  Native data/BSS/rodata reconstruction did not reproduce the target's base
  registers and scheduling; those worse candidates were not integrated.
- `fn_3_1D338`: replace six invented palette values with retail zeros and recover
  the opening multiplication association. Residuals fall from **126 words /
  7 shape edits** to **112 / 6**. A palette-only alternative has **109 / 8**.
  Conversion temporary homes and clamp expressions still differ. A stock
  GC/1.3.2 capture reproduced the compiler object; no allocator repair was proven.

Four pool matches remain: `fn_15_2E8C`, `fn_17_3090`, `colchg_selmate_init`,
and `fn_1_5F5C8`. A direct-link trial for `colchg_selmate_init` failed the hash
check. Its previously accepted pool source was restored and retained.

## Reproduction and validation

Portable source bodies, compiler settings and replay edits are in
`state/repairs/shared_regions_20260915.json.gz`; accepted source provenance is
in `state/repairs/fixup_imports.json`. Numeric results are in the adjacent JSON.

```sh
uv run tools/fzgx.py fixup --archive state/repairs/shared_regions_20260915.json.gz
uv run tools/fzgx.py data-import --regenerate --apply \
  __OSDriveBlock __DVDLowAlarmForWA __DVDLowPrev
uv run python configure.py
ninja
uv run tools/fzgx.py lint
uv run tools/fzgx.py snapshot
```

Selecting `__DVDLowPrev` also regenerates `__DVDLowCurr` in the same data unit.
Real MWCC negative probes reject an altered switch destination, a missing pointer
relocation, and an altered unused initializer even though all instruction words
still match. A shifted SDA destination is also rejected. No unit tests were added.

Validation: the archive replay reproduced 23 bodies; scoped regeneration reproduced
all four typed data objects; all six real-function oracle probes passed their
expected acceptance or rejection; lint reported zero findings; and
`configure.py` plus `ninja` printed `16 files OK`. The completion snapshot has
5,013 matched functions, 2,166 unmatched, 15 blocked, 114 assembly units and
four remaining pool matches.
