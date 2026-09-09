.include "macros.inc"
.file "LCLoadBlocks.c"

# 0x8000B864..0x8000B888 | size: 0x24
.text
.balign 4

# .text:0x0 | 0x8000B864 | size: 0x24
.fn LCLoadBlocks, global
/* 8000B864 00008864  54 A6 F6 FE */	extrwi r6, r5, 5, 25
/* 8000B868 00008868  54 84 01 3E */	clrlwi r4, r4, 4
/* 8000B86C 0000886C  7C C6 23 78 */	or r6, r6, r4
/* 8000B870 00008870  7C DA E3 A6 */	mtspr DMA_U, r6
/* 8000B874 00008874  54 A6 17 3A */	clrlslwi r6, r5, 30, 2
/* 8000B878 00008878  7C C6 1B 78 */	or r6, r6, r3
/* 8000B87C 0000887C  60 C6 00 12 */	ori r6, r6, 0x12
/* 8000B880 00008880  7C DB E3 A6 */	mtspr DMA_L, r6
/* 8000B884 00008884  4E 80 00 20 */	blr
.endfn LCLoadBlocks
