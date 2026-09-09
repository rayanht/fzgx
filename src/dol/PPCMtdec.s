.include "macros.inc"
.file "PPCMtdec.c"

# 0x80009FEC..0x80009FF4 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FEC | size: 0x8
.fn PPCMtdec, weak
/* 80009FEC 00006FEC  7C 76 03 A6 */	mtdec r3
/* 80009FF0 00006FF0  4E 80 00 20 */	blr
.endfn PPCMtdec
