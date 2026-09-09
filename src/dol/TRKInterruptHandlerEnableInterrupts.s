.include "macros.inc"
.file "TRKInterruptHandlerEnableInterrupts.c"

# 0x8008B420..0x8008B474 | size: 0x54
.text
.balign 4

# .text:0x0 | 0x8008B420 | size: 0x54
.fn TRKInterruptHandlerEnableInterrupts, global
/* 8008B420 00088420  3C 40 80 1A */	lis r2, gTRKState@h
/* 8008B424 00088424  60 42 50 BC */	ori r2, r2, gTRKState@l
/* 8008B428 00088428  80 02 00 8C */	lwz r0, 0x8c(r2)
/* 8008B42C 0008842C  7C 00 04 AC */	sync
/* 8008B430 00088430  7C 00 01 24 */	mtmsr r0
/* 8008B434 00088434  7C 00 04 AC */	sync
/* 8008B438 00088438  80 02 00 80 */	lwz r0, 0x80(r2)
/* 8008B43C 0008843C  7C 08 03 A6 */	mtlr r0
/* 8008B440 00088440  80 02 00 84 */	lwz r0, 0x84(r2)
/* 8008B444 00088444  7C 09 03 A6 */	mtctr r0
/* 8008B448 00088448  80 02 00 88 */	lwz r0, 0x88(r2)
/* 8008B44C 0008844C  7C 01 03 A6 */	mtxer r0
/* 8008B450 00088450  80 02 00 94 */	lwz r0, 0x94(r2)
/* 8008B454 00088454  7C 12 03 A6 */	mtdsisr r0
/* 8008B458 00088458  80 02 00 90 */	lwz r0, 0x90(r2)
/* 8008B45C 0008845C  7C 13 03 A6 */	mtdar r0
/* 8008B460 00088460  B8 62 00 0C */	lmw r3, 0xc(r2)
/* 8008B464 00088464  80 02 00 00 */	lwz r0, 0x0(r2)
/* 8008B468 00088468  80 22 00 04 */	lwz r1, 0x4(r2)
/* 8008B46C 0008846C  80 42 00 08 */	lwz r2, 0x8(r2)
/* 8008B470 00088470  48 00 06 60 */	b TRKPostInterruptEvent
.endfn TRKInterruptHandlerEnableInterrupts
