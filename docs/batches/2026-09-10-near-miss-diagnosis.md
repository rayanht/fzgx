# Recovered batch: completed near misses

Snapshot: 42 released functions still unmatched at 97%+ in
`deepseek-recovered-above90-128-low-20260910`, totaling 25,820 bytes. Inputs were
frozen before diagnosis; the original batch continued independently.

`tools/diagnose_batch.py` copies saved C and retail objects under the build lock,
then compiles private variants. Nine variants per function produced 378 real
MWCC/object comparisons with no compilation failures: baseline, GC/1.2.5n,
GC/1.3, GC/1.3.2, scheduling off, lifetimes off, dead-store optimization off,
deferred inlining, and inlining off.

Only one alternative flag produced an exact object match: `fn_80021930`,
392 bytes, with `-opt nodeadstore` on GC/1.2.5n. Its existing C was unchanged;
the flag eliminates the extra 16 bytes in the generated stack frame. Provenance
is recorded in `state/repairs/compiler_flags.json`. No alternative compiler
version closed another function in this snapshot.

## Shared obstruction fixed

Compiler probes previously did not persist their selected compiler. For
`fn_80057EC4`, the same C scores 85.62617% with GC/1.2.5n and 98.8785% with
GC/1.3. The worker discovered this, but its next edit silently reverted to the
seed's GC/1.2.5n. Context also reported a hardcoded compiler for seeded functions.

The API now retains the selected compiler for edits and submission, archives
every tested body with its actual compiler/flags, and preserves that metadata
through release repairs and subsequent seed selection. A real shadow replay
confirmed the GC/1.3 choice survives an unchanged-source write and release while
preserving the function's original status and attempt count. Context uses actual
module flags and seed overrides.

## What the high scores hide

Baseline classification: 23 mixed, 10 register allocation, 3 allocation plus
scheduling, 1 scheduling, 2 frame layout, 2 immediate, and 1 relocation. These
categories are diagnostic hints, not acceptance rules. Thirty-three functions
show register-allocation or scheduling differences. Twenty-two have positional
masked-word agreement below 90%; alignment shifts affect that measure too.
Objdiff's similarity percentage is not the fraction of identical instructions.
Matcher feedback now includes the remaining aligned instruction-row count.

Two specific binding/layout cases remain separate from compiler selection:

- `SIGetType`: retail references `cmdTypeAndStatus$371_801A6814`, while the
  per-function compiler emits `cmdTypeAndStatus$1`. This needs deterministic
  local-static binding; inventing a C identifier containing `$` does not fix it.
- `fn_1_87238`: retail references a shared rodata layout at offsets including
  0x10, 0x28, 0x44, 0x70, and 0x680. The candidate has a compact private pool.
  Its load offsets and relocations need the shared layout; renaming the pool
  symbol alone cannot make it match.

There was no evidence for a universal compiler flag or missing header that
would close this group. The oracle's acceptance rules were not relaxed.

Saved diagnostics are under `.fzgx/diagnostics/recovered-near97/`. Export exact
compiler repairs without repeating the comparisons:

```sh
uv run tools/diagnose_batch.py --saved --output .fzgx/diagnostics/recovered-near97
```

The resulting `matches.json` feeds ordinary seeded orchestrator preflight,
submission, and 16-target verification without model work.
