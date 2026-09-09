.include "macros.inc"
.file "PPCMtfpscr.c"

# 0x8000A080..0x8000A0A8 | size: 0x28
.text
.balign 4

# .text:0x0 | 0x8000A080 | size: 0x28
.fn PPCMtfpscr, global
/* 8000A080 00007080  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8000A084 00007084  DB E1 00 18 */	stfd f31, 0x18(r1)
/* 8000A088 00007088  38 80 00 00 */	li r4, 0x0
/* 8000A08C 0000708C  90 81 00 10 */	stw r4, 0x10(r1)
/* 8000A090 00007090  90 61 00 14 */	stw r3, 0x14(r1)
/* 8000A094 00007094  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 8000A098 00007098  FD FE FD 8E */	mtfsf 255, f31
/* 8000A09C 0000709C  CB E1 00 18 */	lfd f31, 0x18(r1)
/* 8000A0A0 000070A0  38 21 00 20 */	addi r1, r1, 0x20
/* 8000A0A4 000070A4  4E 80 00 20 */	blr
.endfn PPCMtfpscr
