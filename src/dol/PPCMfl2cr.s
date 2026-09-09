.include "macros.inc"
.file "PPCMfl2cr.c"

# 0x80009FDC..0x80009FE4 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FDC | size: 0x8
.fn PPCMfl2cr, global
/* 80009FDC 00006FDC  7C 79 FA A6 */	mfspr r3, L2CR
/* 80009FE0 00006FE0  4E 80 00 20 */	blr
.endfn PPCMfl2cr
