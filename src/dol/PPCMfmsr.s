.include "macros.inc"
.file "PPCMfmsr.c"

# 0x80009FBC..0x80009FC4 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FBC | size: 0x8
.fn PPCMfmsr, global
/* 80009FBC 00006FBC  7C 60 00 A6 */	mfmsr r3
/* 80009FC0 00006FC0  4E 80 00 20 */	blr
.endfn PPCMfmsr
