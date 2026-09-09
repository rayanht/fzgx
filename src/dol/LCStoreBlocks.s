.include "macros.inc"
.file "LCStoreBlocks.c"

# 0x8000B888..0x8000B8AC | size: 0x24
.text
.balign 4

# .text:0x0 | 0x8000B888 | size: 0x24
.fn LCStoreBlocks, global
/* 8000B888 00008888  54 A6 F6 FE */	extrwi r6, r5, 5, 25
/* 8000B88C 0000888C  54 63 01 3E */	clrlwi r3, r3, 4
/* 8000B890 00008890  7C C6 1B 78 */	or r6, r6, r3
/* 8000B894 00008894  7C DA E3 A6 */	mtspr DMA_U, r6
/* 8000B898 00008898  54 A6 17 3A */	clrlslwi r6, r5, 30, 2
/* 8000B89C 0000889C  7C C6 23 78 */	or r6, r6, r4
/* 8000B8A0 000088A0  60 C6 00 02 */	ori r6, r6, 0x2
/* 8000B8A4 000088A4  7C DB E3 A6 */	mtspr DMA_L, r6
/* 8000B8A8 000088A8  4E 80 00 20 */	blr
.endfn LCStoreBlocks
