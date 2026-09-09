.include "macros.inc"
.file "PPCSetFpNonIEEEMode.c"

# 0x8000A0F4..0x8000A0FC | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A0F4 | size: 0x8
.fn PPCSetFpNonIEEEMode, global
/* 8000A0F4 000070F4  FF A0 00 4C */	mtfsb1 cr7gt
/* 8000A0F8 000070F8  4E 80 00 20 */	blr
.endfn PPCSetFpNonIEEEMode
