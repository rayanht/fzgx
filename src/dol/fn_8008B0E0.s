.include "macros.inc"
.file "fn_8008B0E0.c"

# 0x8008B0E0..0x8008B0E8 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8008B0E0 | size: 0x8
.fn fn_8008B0E0, global
/* 8008B0E0 000880E0  7C 60 00 A6 */	mfmsr r3
/* 8008B0E4 000880E4  4E 80 00 20 */	blr
.endfn fn_8008B0E0
