.include "macros.inc"
.file "DecrementerExceptionHandler.c"

# 0x8000B2C4..0x8000B314 | size: 0x50
.text
.balign 4

# .text:0x0 | 0x8000B2C4 | size: 0x50
.fn DecrementerExceptionHandler_8000B2C4, global
/* 8000B2C4 000082C4  90 04 00 00 */	stw r0, 0x0(r4)
/* 8000B2C8 000082C8  90 24 00 04 */	stw r1, 0x4(r4)
/* 8000B2CC 000082CC  90 44 00 08 */	stw r2, 0x8(r4)
/* 8000B2D0 000082D0  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 8000B2D4 000082D4  7C 11 E2 A6 */	mfspr r0, GQR1
/* 8000B2D8 000082D8  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 8000B2DC 000082DC  7C 12 E2 A6 */	mfspr r0, GQR2
/* 8000B2E0 000082E0  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 8000B2E4 000082E4  7C 13 E2 A6 */	mfspr r0, GQR3
/* 8000B2E8 000082E8  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 8000B2EC 000082EC  7C 14 E2 A6 */	mfspr r0, GQR4
/* 8000B2F0 000082F0  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 8000B2F4 000082F4  7C 15 E2 A6 */	mfspr r0, GQR5
/* 8000B2F8 000082F8  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 8000B2FC 000082FC  7C 16 E2 A6 */	mfspr r0, GQR6
/* 8000B300 00008300  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 8000B304 00008304  7C 17 E2 A6 */	mfspr r0, GQR7
/* 8000B308 00008308  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 8000B30C 0000830C  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 8000B310 00008310  4B FF FD 84 */	b DecrementerExceptionCallback
.endfn DecrementerExceptionHandler_8000B2C4
