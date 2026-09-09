.include "macros.inc"
.file "OSEnableInterrupts.c"

# 0x8000D508..0x8000D51C | size: 0x14
.text
.balign 4

# .text:0x0 | 0x8000D508 | size: 0x14
.fn OSEnableInterrupts, global
/* 8000D508 0000A508  7C 60 00 A6 */	mfmsr r3
/* 8000D50C 0000A50C  60 64 80 00 */	ori r4, r3, 0x8000
/* 8000D510 0000A510  7C 80 01 24 */	mtmsr r4
/* 8000D514 0000A514  54 63 8F FE */	extrwi r3, r3, 1, 16
/* 8000D518 0000A518  4E 80 00 20 */	blr
.endfn OSEnableInterrupts
