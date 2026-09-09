.include "macros.inc"
.file "OSDisableInterrupts.c"

# 0x8000D4F4..0x8000D508 | size: 0x14
.text
.balign 4

# .text:0x0 | 0x8000D4F4 | size: 0x14
.fn OSDisableInterrupts, global
/* 8000D4F4 0000A4F4  7C 60 00 A6 */	mfmsr r3
/* 8000D4F8 0000A4F8  54 64 04 5E */	rlwinm r4, r3, 0, 17, 15
/* 8000D4FC 0000A4FC  7C 80 01 24 */	mtmsr r4
/* 8000D500 0000A500  54 63 8F FE */	extrwi r3, r3, 1, 16
/* 8000D504 0000A504  4E 80 00 20 */	blr
.endfn OSDisableInterrupts
