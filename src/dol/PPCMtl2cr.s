.include "macros.inc"
.file "PPCMtl2cr.c"

# 0x80009FE4..0x80009FEC | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FE4 | size: 0x8
.fn PPCMtl2cr, global
/* 80009FE4 00006FE4  7C 79 FB A6 */	mtspr L2CR, r3
/* 80009FE8 00006FE8  4E 80 00 20 */	blr
.endfn PPCMtl2cr
