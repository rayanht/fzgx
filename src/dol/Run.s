.include "macros.inc"
.file "Run.c"

# 0x8000EAF4..0x8000EB04 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x8000EAF4 | size: 0x10
.fn Run, global
/* 8000EAF4 0000BAF4  7C 00 04 AC */	sync
/* 8000EAF8 0000BAF8  4C 00 01 2C */	isync
/* 8000EAFC 0000BAFC  7C 68 03 A6 */	mtlr r3
/* 8000EB00 0000BB00  4E 80 00 20 */	blr
.endfn Run
