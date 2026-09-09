.include "macros.inc"
.file "DCFlushRangeNoSync.c"

# 0x8000B6B4..0x8000B6E0 | size: 0x2C
.text
.balign 4

# .text:0x0 | 0x8000B6B4 | size: 0x2C
.fn DCFlushRangeNoSync, global
/* 8000B6B4 000086B4  28 04 00 00 */	cmplwi r4, 0x0
/* 8000B6B8 000086B8  4C 81 00 20 */	blelr
/* 8000B6BC 000086BC  54 65 06 FE */	clrlwi r5, r3, 27
/* 8000B6C0 000086C0  7C 84 2A 14 */	add r4, r4, r5
/* 8000B6C4 000086C4  38 84 00 1F */	addi r4, r4, 0x1f
/* 8000B6C8 000086C8  54 84 D9 7E */	srwi r4, r4, 5
/* 8000B6CC 000086CC  7C 89 03 A6 */	mtctr r4
.L_8000B6D0:
/* 8000B6D0 000086D0  7C 00 18 AC */	dcbf r0, r3
/* 8000B6D4 000086D4  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B6D8 000086D8  42 00 FF F8 */	bdnz .L_8000B6D0
/* 8000B6DC 000086DC  4E 80 00 20 */	blr
.endfn DCFlushRangeNoSync
