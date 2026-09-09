.include "macros.inc"
.file "fn_8003D4C0.c"

# 0x8003D4C0..0x8003D4E0 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x8003D4C0 | size: 0x20
.fn fn_8003D4C0, global
/* 8003D4C0 0003A4C0  7C 7C E2 A6 */	mfspr r3, 924
/* 8003D4C4 0003A4C4  7C 9D E2 A6 */	mfspr r4, 925
/* 8003D4C8 0003A4C8  7C BE E2 A6 */	mfspr r5, 926
/* 8003D4CC 0003A4CC  7C DF E2 A6 */	mfspr r6, 927
/* 8003D4D0 0003A4D0  7C 63 22 78 */	xor r3, r3, r4
/* 8003D4D4 0003A4D4  7C 63 2A 78 */	xor r3, r3, r5
/* 8003D4D8 0003A4D8  7C 63 32 78 */	xor r3, r3, r6
/* 8003D4DC 0003A4DC  4E 80 00 20 */	blr
.endfn fn_8003D4C0
