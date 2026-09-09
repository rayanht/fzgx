.include "macros.inc"
.file "fn_8000A050.c"

# 0x8000A050..0x8000A058 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A050 | size: 0x8
.fn fn_8000A050, global
/* 8000A050 00007050  7C 7E EA A6 */	mfspr r3, PMC4
/* 8000A054 00007054  4E 80 00 20 */	blr
.endfn fn_8000A050
