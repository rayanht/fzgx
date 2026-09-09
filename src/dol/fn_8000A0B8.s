.include "macros.inc"
.file "fn_8000A0B8.c"

# 0x8000A0B8..0x8000A0C4 | size: 0xC
.text
.balign 4

# .text:0x0 | 0x8000A0B8 | size: 0xC
.fn fn_8000A0B8, global
/* 8000A0B8 000070B8  7C 00 04 AC */	sync
/* 8000A0BC 000070BC  7C 79 E2 A6 */	mfspr r3, WPAR
/* 8000A0C0 000070C0  4E 80 00 20 */	blr
.endfn fn_8000A0B8
