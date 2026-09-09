.include "macros.inc"
.file "fn_8000B8AC.c"

# 0x8000B8AC..0x8000B8C0 | size: 0x14
.text
.balign 4

# .text:0x0 | 0x8000B8AC | size: 0x14
.fn fn_8000B8AC, global
/* 8000B8AC 000088AC  7C 98 E2 A6 */	mfspr r4, HID2
/* 8000B8B0 000088B0  54 84 47 3E */	extrwi r4, r4, 4, 4
/* 8000B8B4 000088B4  7C 04 18 00 */	cmpw r4, r3
/* 8000B8B8 000088B8  41 81 FF F4 */	bgt fn_8000B8AC
/* 8000B8BC 000088BC  4E 80 00 20 */	blr
.endfn fn_8000B8AC
