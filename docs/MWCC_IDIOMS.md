Starter notes on CodeWarrior for GameCube 1.x codegen at `-O4,p`. Grow this
file from what actually unblocked functions; keep each item one or two lines.

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
