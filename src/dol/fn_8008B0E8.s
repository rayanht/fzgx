.include "macros.inc"
.file "fn_8008B0E8.c"

# 0x8008B0E8..0x8008B0F0 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8008B0E8 | size: 0x8
.fn fn_8008B0E8, global
/* 8008B0E8 000880E8  7C 60 01 24 */	mtmsr r3
/* 8008B0EC 000880EC  4E 80 00 20 */	blr
.endfn fn_8008B0E8
