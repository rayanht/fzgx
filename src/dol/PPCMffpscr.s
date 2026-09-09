.include "macros.inc"
.file "PPCMffpscr.c"

# 0x8000A060..0x8000A080 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x8000A060 | size: 0x20
.fn PPCMffpscr, global
/* 8000A060 00007060  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000A064 00007064  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 8000A068 00007068  FF E0 04 8E */	mffs f31
/* 8000A06C 0000706C  DB E1 00 08 */	stfd f31, 0x8(r1)
/* 8000A070 00007070  80 61 00 0C */	lwz r3, 0xc(r1)
/* 8000A074 00007074  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 8000A078 00007078  38 21 00 18 */	addi r1, r1, 0x18
/* 8000A07C 0000707C  4E 80 00 20 */	blr
.endfn PPCMffpscr
