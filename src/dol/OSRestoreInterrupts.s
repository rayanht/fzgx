.include "macros.inc"
.file "OSRestoreInterrupts.c"

# 0x8000D51C..0x8000D540 | size: 0x24
.text
.balign 4

# .text:0x0 | 0x8000D51C | size: 0x24
.fn OSRestoreInterrupts, global
/* 8000D51C 0000A51C  2C 03 00 00 */	cmpwi r3, 0x0
/* 8000D520 0000A520  7C 80 00 A6 */	mfmsr r4
/* 8000D524 0000A524  41 82 00 0C */	beq .L_8000D530
/* 8000D528 0000A528  60 85 80 00 */	ori r5, r4, 0x8000
/* 8000D52C 0000A52C  48 00 00 08 */	b .L_8000D534
.L_8000D530:
/* 8000D530 0000A530  54 85 04 5E */	rlwinm r5, r4, 0, 17, 15
.L_8000D534:
/* 8000D534 0000A534  7C A0 01 24 */	mtmsr r5
/* 8000D538 0000A538  54 83 8F FE */	extrwi r3, r4, 1, 16
/* 8000D53C 0000A53C  4E 80 00 20 */	blr
.endfn OSRestoreInterrupts
