# Matcher data access and vector lowering

Matchers can read every differing row and decoded retail data through
`read_evidence(section, cursor)`, without compiling or spending checks. Existing
threads can use `check(versions="diff:80")` / `check(versions="data:0")`.
Switch decoding is shared with the m2c assembly adapter. Pool recovery follows
symbolic bases across CFG joins and repairs literals inside macros as well as
function bodies. Relocation equivalence now requires the same REL section.

The default lifter emits native MWCC paired-float C. It separates scalar/vector
register lifetimes, preserves integer conversion bias registers, handles scheduled
signed shift/divide sequences and lowers unsigned high-word multiplication.
Arithmetic expressions no longer get mistaken for pointer casts. Repair row
accounting now parses objdiff's decimal addresses correctly.

Real-function validation under GC/1.3.2:

| Function | Bytes | Unresolved instructions before → after | Compiles |
| --- | ---: | ---: | --- |
| fn_1_10E3B4 | 7,252 | 182 → 0 | Yes |
| fn_1_120804 | 6,980 | 138 → 0 | Yes |
| fn_1_123050 | 5,280 | 111 → 0 | Yes |

These are generated drafts, not new matches. Their objects preserve all 132 paired
arithmetic operations, but MWCC emits indexed accesses and merge/multiply forms
where retail uses displacement accesses and scalar-lane operations. Other
instruction differences also remain. Regenerate with `lift.lift_total` or the
largest-function seed selector; no reconstructed C was edited manually.

The reader recovered all 39 switch entries for fn_1_B03CC with the auxiliary
context budget set to zero. Both pages of fn_1_B277C's 118 rendered rows were
retrieved without changing its ledger counters. Shared-base decoding recovered
39 floating constants for fn_3_1D338. Correcting its placeholder literal values
alone did not improve instruction similarity; binding its sparse external pool
layout also did not produce a match.

Replaying the deterministic repair on the 17 frozen releases tried 6,475 candidates
in 55.2 seconds and closed zero functions. Inputs and generated drafts are under
`.fzgx/diagnostics/largest50-blockers-1789066143/` and
`.fzgx/diagnostics/paired-lowering-20260910/`; measured outputs and draft hashes
are recorded in `2026-09-10-tooling-blockers.json`.

Validation: configure/Ninja succeeded, the explicit DTK hash check reported
`16 files OK`, and `fzgx lint` returned no findings. No unit tests were added.
