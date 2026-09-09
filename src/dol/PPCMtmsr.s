.include "macros.inc"
.file "PPCMtmsr.c"

# 0x80009FC4..0x80009FCC | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FC4 | size: 0x8
.fn PPCMtmsr, global
/* 80009FC4 00006FC4  7C 60 01 24 */	mtmsr r3
/* 80009FC8 00006FC8  4E 80 00 20 */	blr
.endfn PPCMtmsr
