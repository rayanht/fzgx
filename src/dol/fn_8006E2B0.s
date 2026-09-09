.include "macros.inc"
.file "fn_8006E2B0.c"

# 0x8006E2B0..0x8006E2C0 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x8006E2B0 | size: 0x10
.fn fn_8006E2B0, global
/* 8006E2B0 0006B2B0  C0 23 00 00 */	lfs f1, 0x0(r3)
/* 8006E2B4 0006B2B4  C0 43 00 04 */	lfs f2, 0x4(r3)
/* 8006E2B8 0006B2B8  C0 63 00 08 */	lfs f3, 0x8(r3)
/* 8006E2BC 0006B2BC  48 00 00 14 */	b lbl_8006E2D0
.endfn fn_8006E2B0
