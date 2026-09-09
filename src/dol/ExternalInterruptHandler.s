.include "macros.inc"
.file "ExternalInterruptHandler.c"

# 0x8000DD10..0x8000DD60 | size: 0x50
.text
.balign 4

# .text:0x0 | 0x8000DD10 | size: 0x50
.fn ExternalInterruptHandler_8000DD10, global
/* 8000DD10 0000AD10  90 04 00 00 */	stw r0, 0x0(r4)
/* 8000DD14 0000AD14  90 24 00 04 */	stw r1, 0x4(r4)
/* 8000DD18 0000AD18  90 44 00 08 */	stw r2, 0x8(r4)
/* 8000DD1C 0000AD1C  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 8000DD20 0000AD20  7C 11 E2 A6 */	mfspr r0, GQR1
/* 8000DD24 0000AD24  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 8000DD28 0000AD28  7C 12 E2 A6 */	mfspr r0, GQR2
/* 8000DD2C 0000AD2C  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 8000DD30 0000AD30  7C 13 E2 A6 */	mfspr r0, GQR3
/* 8000DD34 0000AD34  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 8000DD38 0000AD38  7C 14 E2 A6 */	mfspr r0, GQR4
/* 8000DD3C 0000AD3C  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 8000DD40 0000AD40  7C 15 E2 A6 */	mfspr r0, GQR5
/* 8000DD44 0000AD44  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 8000DD48 0000AD48  7C 16 E2 A6 */	mfspr r0, GQR6
/* 8000DD4C 0000AD4C  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 8000DD50 0000AD50  7C 17 E2 A6 */	mfspr r0, GQR7
/* 8000DD54 0000AD54  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 8000DD58 0000AD58  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 8000DD5C 0000AD5C  4B FF FC 70 */	b fn_8000D9CC
.endfn ExternalInterruptHandler_8000DD10
