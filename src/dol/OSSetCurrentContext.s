.include "macros.inc"
.file "OSSetCurrentContext.c"

# 0x8000BE00..0x8000BE5C | size: 0x5C
.text
.balign 4

# .text:0x0 | 0x8000BE00 | size: 0x5C
.fn OSSetCurrentContext, global
/* 8000BE00 00008E00  3C 80 80 00 */	lis r4, 0x8000
/* 8000BE04 00008E04  90 64 00 D4 */	stw r3, 0xd4(r4)
/* 8000BE08 00008E08  54 65 00 BE */	clrlwi r5, r3, 2
/* 8000BE0C 00008E0C  90 A4 00 C0 */	stw r5, 0xc0(r4)
/* 8000BE10 00008E10  80 A4 00 D8 */	lwz r5, 0xd8(r4)
/* 8000BE14 00008E14  7C 05 18 00 */	cmpw r5, r3
/* 8000BE18 00008E18  40 82 00 20 */	bne .L_8000BE38
/* 8000BE1C 00008E1C  80 C3 01 9C */	lwz r6, 0x19c(r3)
/* 8000BE20 00008E20  60 C6 20 00 */	ori r6, r6, 0x2000
/* 8000BE24 00008E24  90 C3 01 9C */	stw r6, 0x19c(r3)
/* 8000BE28 00008E28  7C C0 00 A6 */	mfmsr r6
/* 8000BE2C 00008E2C  60 C6 00 02 */	ori r6, r6, 0x2
/* 8000BE30 00008E30  7C C0 01 24 */	mtmsr r6
/* 8000BE34 00008E34  4E 80 00 20 */	blr
.L_8000BE38:
/* 8000BE38 00008E38  80 C3 01 9C */	lwz r6, 0x19c(r3)
/* 8000BE3C 00008E3C  54 C6 04 E2 */	rlwinm r6, r6, 0, 19, 17
/* 8000BE40 00008E40  90 C3 01 9C */	stw r6, 0x19c(r3)
/* 8000BE44 00008E44  7C C0 00 A6 */	mfmsr r6
/* 8000BE48 00008E48  54 C6 04 E2 */	rlwinm r6, r6, 0, 19, 17
/* 8000BE4C 00008E4C  60 C6 00 02 */	ori r6, r6, 0x2
/* 8000BE50 00008E50  7C C0 01 24 */	mtmsr r6
/* 8000BE54 00008E54  4C 00 01 2C */	isync
/* 8000BE58 00008E58  4E 80 00 20 */	blr
.endfn OSSetCurrentContext
