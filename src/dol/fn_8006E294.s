.include "macros.inc"
.file "fn_8006E294.c"

# 0x8006E294..0x8006E2B0 | size: 0x1C
.text
.balign 4

# .text:0x0 | 0x8006E294 | size: 0x1C
.fn fn_8006E294, global
/* 8006E294 0006B294  3C A0 E0 00 */	lis r5, 0xe000
/* 8006E298 0006B298  7C 64 1B 78 */	mr r4, r3
/* 8006E29C 0006B29C  4C 42 12 42 */	crset eq
/* 8006E2A0 0006B2A0  C0 25 00 0C */	lfs f1, 0xc(r5)
/* 8006E2A4 0006B2A4  C0 45 00 1C */	lfs f2, 0x1c(r5)
/* 8006E2A8 0006B2A8  C0 65 00 2C */	lfs f3, 0x2c(r5)
/* 8006E2AC 0006B2AC  48 00 00 2C */	b fn_8006E2D8
.endfn fn_8006E294
