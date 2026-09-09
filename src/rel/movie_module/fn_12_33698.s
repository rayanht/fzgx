.include "macros.inc"
.file "fn_12_33698.c"

# 0x00033698..0x000336CC | size: 0x34
.text
.balign 4

# .text:0x0 | 0x33698 | size: 0x34
.fn fn_12_33698, global
/* 00033698 00033784  7C 12 E2 A6 */	mfspr r0, GQR2
/* 0003369C 00033788  7C 93 E2 A6 */	mfspr r4, GQR3
/* 000336A0 0003378C  7C B4 E2 A6 */	mfspr r5, GQR4
/* 000336A4 00033790  7C D5 E2 A6 */	mfspr r6, GQR5
/* 000336A8 00033794  7C F6 E2 A6 */	mfspr r7, GQR6
/* 000336AC 00033798  7D 17 E2 A6 */	mfspr r8, GQR7
/* 000336B0 0003379C  90 03 00 08 */	stw r0, 0x8(r3)
/* 000336B4 000337A0  90 83 00 0C */	stw r4, 0xc(r3)
/* 000336B8 000337A4  90 A3 00 10 */	stw r5, 0x10(r3)
/* 000336BC 000337A8  90 C3 00 14 */	stw r6, 0x14(r3)
/* 000336C0 000337AC  90 E3 00 18 */	stw r7, 0x18(r3)
/* 000336C4 000337B0  91 03 00 1C */	stw r8, 0x1c(r3)
/* 000336C8 000337B4  4E 80 00 20 */	blr
.endfn fn_12_33698
