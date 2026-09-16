Starter notes on CodeWarrior for GameCube 1.x codegen at `-O4,p`. Grow this
file from what actually unblocked functions; keep each item one or two lines.

## Selection panel evidence (2026-09-15)

- Four-byte color structs reproduce pooled `lwz` initializers; scalar `const u32`
  colors can fold into immediates. Automatic struct initializers keep per-iteration copies inside loops.
- Separate initialized data objects establish MWCC's native data base. A pointer
  to an extern aggregate can change base setup and address lifetimes despite identical field offsets.
- Complete nested calls before binding a localized string table when retail does;
  an inline indexed lookup closed the last four register differences in `fn_10_1C2D8`.
- DTK `pad_` objects contained 93 of this panel's 867 data pointers. Pool proof
  must inspect their relocations, including unused slots, rather than assuming zero padding.
- Split grouped declarations before allocation analysis. On `fn_10_1D314`, this
  preserved the code and exposed ten locals; the resulting partial repairs remain unmatched.

## General observations

- Register allocation follows declaration order of locals and argument order.
  Reordering declarations moves registers; extra temporaries can force a spill
  or a different register.
- `int` vs `u8/s16` locals change sign/zero extension (`extsb`, `extsh`,
  `rlwinm ... 0xff`). Match the extension you see.
- `-inline auto`: small `static` functions in the same file are inlined into
  callers. If retail has the body inline, define the helper `static inline` in
  the same unit.
- Float compares: `fcmpu` + `cror` patterns come from `<=`/`>=`; a plain
  `fcmpo` from `<`/`>`. `frsp` appears when a double is narrowed to float:
  use `f32` literals (`1.0f`) to avoid double promotion.
- `switch` with dense cases produces a jump table (`.data`); sparse cases
  produce compare chains. A `default` placement can change the layout.
- Struct field access uses the field offset directly in `lwz r, off(base)`;
  when you see an offset, add the field at that offset in the struct.
- Loops: `bdnz` implies a counted loop the compiler could prove; `for (i = 0;
  i < n; i++)` with `n` loop-invariant. `mtctr` at loop entry.
- `stwu r1, -N(r1)` frame size N and `_savegpr_NN` tell how many non-volatile
  registers are live across calls: roughly how many values survive a call.
- String literals go to `.rodata` (`-str reuse` pools identical ones); float
  constants to `.rodata` in RELs (`-sdata2 0`) and `.sdata2` in the DOL.
- `lis/addi` (`@ha/@l`) is a normal address materialisation, not a constant:
  declare the symbol and take its address.
- A value loaded into `r4` (or `r5`...) right before a `bl`, while `r3` is left
  untouched, means the callee takes the caller's first argument as its own
  first parameter and the loaded value as the second: write
  `callee(arg0, table[idx])`, not `callee(table[idx])`. Register choice here is
  a signature question, never a compiler quirk.
- The same in reverse: if you need a parameter in `r4`, add the preceding
  parameter to the signature even when the function body ignores it.
- A missing return can look like register allocation: `fn_80069AE0` needs the
  loaded flags in r3 on one path and the callee's result on the other. Returning
  the flags after both paths incorrectly keeps them live across the call.
- (tooling, not codegen) RELs are linked without `-strip_partial` because retail
  kept unreferenced functions; with stripping on, a carved function nobody
  references vanishes from the link and every REL importing later symbols
  fails its hash.
- A value used both before and after a call is loaded once into a local (a
  non-volatile register, `r31` down); reloading it after the call gives a
  second `lwz` retail does not have. The reverse too: two loads in retail mean
  two expressions in the source, not one local.
- Argument materialisation follows source order: `f(1, 15, g)` loads `g`
  after `li r4, 15`; if retail loads `g` first, `g` came from a local set
  earlier in the function.
- Same asm modulo two swapped `li`/`lwz` rows is never a compiler quirk: it is
  statement order or an intermediate local.

## Rules the lifter learned (each verified byte-exact on retail functions, 2026-09-08)

- `p = (struct S *)&sym;` keeps the address in a saved register across calls; a plain
  `&sym` or `sym.field` is rematerialised (`lis/addi`) after every call. When retail
  holds a global's address in r31/r30 and uses `off(r31)` after calls, write the cast form.
- A loaded value that is read again after a store to the same location lived in a
  local: `v = x; x = v + 1; f(v, &x)`. A plain `x++` reuses the register instead.
- A value used twice (two reads of the same register before it is rewritten, a call
  argument plus a return, a field plus a compare) lived in a local; recomputing the
  expression twice gives extra loads or a different register.
- A value computed into a saved register (r14–r31) before a call and used after it is a
  local assigned before the call.
- The same expression passed as several arguments of one call (`f(v, v, v)`, three
  `fmr` from one `lfs`) is a local assigned right before that call, not a CSE across
  calls (which would land in f31 with `stfd f31` saves).
- Call arguments are the argument registers written since the previous call; an
  untouched r3..r5 followed by a temporary in r6 means the function's own first three
  parameters are passed straight through: `void f(a, b, c) { g(a, b, c); }`.
- `crclr cr1eq` (`crclr 6`) right before a `bl` marks a variadic callee.
- A variadic entry saves r3-r10 and conditionally f1-f8 under `bne cr1`; these are
  the argument-save area, not sixteen fixed parameters. `fn_1_4AE0C` matches with
  `(const char *format, ...)`, a 512-byte character buffer and `__builtin_va_info`.
- Address arguments need pointer-typed prototypes; `(u32)&x` as an argument is hoisted
  into a saved register, `&x` with a `void *` parameter is recomputed per call.
- An address-taken scalar local stays a scalar (`f(&x)` recomputes `addi rN, r1, off` at
  each use); an array decays once into a saved register. A `u8` buffer is 16-byte
  aligned in the frame, a `u32` array or a struct is not.
- When fields match but a struct-copy loop starts four bytes early, check for a
  fake leading field plus an array-minus-four pointer. `fn_1_133BD8` needs an
  aggregate local with the prefix removed, preserving the union's copy extent.
- Signedness of a compare comes from the operand types: `cmpwi` needs a signed
  operand, `cmplwi` an unsigned one, whatever the width.
- Unsigned division by a constant: `mulhwu` with a magic multiplier, then
  `subf/srwi 1/add/srwi s` (or just `srwi s`); a following `mulli` by the divisor and
  `subf` is the remainder. Write `x / 360`, `x % 360`; never the magic number.
- int → float: `lis 0x4330; stw hi; (xoris x,0x8000;) stw x; lfd; fsub(s) <2^52 constant
  from the pool>` is `(f32)(s32)x` (with the xoris) or `(f32)(u32)x` (without). The
  constant is a pooled `lbl_*_rodata_*` symbol; float → int: `fctiwz; stfd; lwz low` is
  `(s32)f`.
- A struct assignment of 8×N bytes is a counted loop: `li rN, N; mtctr; lwz/lwzu/stw/stwu
  … bdnz` with both bases pre-decremented by 4. Write `dst = src;` with a struct of
  that size; never a loop.
- A `while` loop compiles to a jump to the test at the bottom; loop variables live in
  locals initialised before the loop. Registers assigned inside an `if` block and read
  after it are locals too; a flag set to 0 before an if-chain and to 1 inside is a
  local, not a constant.

## What closed the agents' plateaus (spelling search over 1,285 saved bodies, 2026-09-08)

Each line is a family that turned a 60–99% body into a match; the count is how many.
- Declaration order of locals (5) and moving one local into an inner block (2): the
  allocator follows declaration order, so a swapped r30/r31 is a swapped declaration.
- One extra unused trailing parameter (3): a function that ignores an argument still
  declared it; add `u32 unused` before rewriting anything else.
- Hoisting a call argument into a local right before the call (4), or inlining a
  single-use temporary (4): `f(a, p->x)` vs `t = p->x; f(a, t)` moves the load.
- Signedness of a local (3), a parameter (1), a struct field (2): `s32` vs `u32` changes
  `cmpw`/`cmplw` and `extsh`/`rlwinm`, nothing else; flip one at a time.
- `x == 0` -> `!x`, `x != 0` -> `x` (2), and commuted compare operands `2 == x` (2):
  the branch is the same, the register that holds the constant moves.
- Two adjacent statements that share nothing, swapped (2): free order, different
  scheduling.

## Large saved bodies (2026-09-14)

- `fn_8_1394` (GC/2.0): assigning the zero operand inside a floating comparison
  gives it a separate scalar lifetime and reproduces the retail operand order.
- `fn_1_988DC`: completing a dead integer counter's square immediately after its
  definition changes the later register interference. Its floating clamp also
  needs the retail unordered branch behavior; positive nested tests and a
  min/max expression are not interchangeable for NaNs.
- `fn_1_13C1A0`: a 200-byte stack copy is ten rows of five words. Recovering the
  row shape reproduces the address arithmetic that a flat guessed table misses.
- `fn_1_13D460`: placing the count assignment before packet setup and forming
  the strip base plus width-times-index before the final displacement reproduces
  the allocation and operand order without declaration permutations.
- Shared BSS section bases do not emit relocations to every named object. Bind
  split definitions by measured module, section, address and owner bounds. Give
  interior pieces canonical `OWNER__fzgx_offset_HEX` names. Private primer storage
  can disappear only after its section base is proven and no live relocation
  reaches the remaining storage. This linked the 6,608-byte `fn_1_AD264`.

## Shared SDK state (2026-09-15)

- A code-complete function can still have a wrong unused data prefix. In VI
  configuration, reconstructing the retail prefix and symbolic switch pointers
  closed two unresolved base relocations without changing an instruction.
  Verify pointer relocation kind, module, section and destination as well as
  initialized bytes. A size-zero section symbol is not a relocation-free object.
- Keep section anchors that already have verified bindings. Rename remaining
  native BSS members from their measured positions, including SDK layout gaps.
  Missing BSS symbols can hide complete typed objects: the OS inquiry block and
  DVD workaround alarm/buffers accounted for 112 bytes of shared storage.
- MWCC emits unreferenced BSS definitions in reverse declaration order. Data-only
  grouped imports must reverse definitions and still prove every object offset,
  section extent and alignment. First-use order in a function primer is a
  different case; put such primers explicitly in `.fzgxpool`.
- Preprocessed C may contain spaces around `->`. Normalize the member-access
  token before the layout parser checks whether a base pointer escapes.

## Lost switch cases and string objects (2026-09-15)

- An integer interval recovered as `if (value < 2 && value >= 0)` can be a
  switch with cases 0 and 1. MWCC retains a different conditional/unconditional
  branch pair for the switch. Restoring contiguous cases exactly matched
  `fn_8002A74C`, `fn_8006BA74` and `fn_12_3256C`. This is a source control-flow
  distinction; disabling dead-code elimination did not repair these examples.
- A shifted sign-bit test can be an incorrectly lifted rotated low-bit test.
  Recover the retail `__rlwnm(value, amount, 31, 31)` expression before changing
  register allocation. This closed `fn_1_7F3AC`, `fn_1_557C4` and `fn_1_55A84`.
- Error-string pools need separate native string objects. A pointer to one
  external character array changes both base initialization and offset-zero
  address formation. Recover each string, its terminating zero and measured
  padding, and reject any intersecting data relocation. This closed
  `fn_12_34390`, `fn_12_346BC` and `fn_12_34798` with the original compiler.
  The repair archive retains all nine inputs, outputs and compiler settings.

## Root causes measured over the whole stuck corpus (2026-09-15)

`fzgx stuck --min-percent 50` over 1,962 saved bodies, counting mnemonics per side
without row alignment (`retail - ours` net rows):

- `lis` -2073 / `addi` +1622 (731 functions): the TU section base and shared literal
  pool (existing primer/layout families).
- `psq_st` +608, `psq_l` +579, `ps_madds0` +148, `ps_sub` +111: 164 unmatched
  functions (244 KB) use paired-single vector kernels. **MWCC's `__vec2x32float__`
  only emits the indexed `psq_lx`/`psq_stx`; the displacement form `psq_l f, 0x10(r29)`
  comes only from inline assembly inlined into the caller.** `include/psvec.h` holds
  the helpers (sub, add, scale, scale_add, sub_scale_add, set), each byte-exact on
  retail: fn_1_FB50 and fn_1_7EB8C match with one call. An inlined asm block's
  register parameters take f0, f1, f2 in declaration order, which is why `psvec_set`
  declares (dst, z, y, x): retail merges x from f2 with y from f1 and stores z from
  f0. Loads passed straight as arguments keep that order; loading into locals first
  changes it (fn_1_2A694). The lifter recognises the kernels (`psvec.kernels`) and the
  engine rewrites per-component statement triples (`paired_vector_kernels`).
- `fmuls` +615 / `fmadds` -525 / `fadds` +318 (251 functions): retail keeps products
  separate where ours fuse. Probe law (GC/1.3.2): `a + b*c` fuses; a product held in a
  named temporary or wrapped in an explicit `(f32)` cast does not (`t = b*c; a + t`
  and `a + (f32)(b*c)` give `fmuls; fadds`), and only the multiply that is a direct
  operand of the add/sub fuses: `(f32)(a*b) - c*d` gives `fmuls; fnmsubs`, `a*b - c*d`
  gives `fmuls(c*d); fmsubs`. `x*x + y*y + z*z` accumulated from the first product
  (`fmuls x; fmadds y; fmadds z`) is `(f32)(x*x) + y*y + z*z`; the plain expression
  materialises `y*y` first. Family: `fusion_control`.
- `cmpwi` +764 / `cmplwi` -443 (460 functions) and `lha` +93: our bodies are
  unsigned where retail is signed. With `-sym on` MWCC emits a DWARF 1 `.line` table
  and byte-identical code, so every differing row names its statement
  (`tools/fzgx/linemap.py`); `attributed_type_flips` flips the casts and declarations
  of that statement's operands toward retail's signedness, `attributed_inlines` folds a
  single-use local read there back into its use (fn_1_76704: the call evaluated
  inside the multiply fixes `mullw` operand order), and the engine tries candidates
  that edit implicated statements before the rest.
- Epilogue `lwz r31; lwz r0` against `lwz r0; lwz r31` (10 functions): the scheduler
  hoists the LR reload only when nothing ties it; same instruction stream, different
  DAG, not closable by flags (`-O3` disables scheduling entirely).
- No other retail-only opcode family above 40 functions exists; the rest of the
  residuals are register allocation, frame layout and control-flow shape.
