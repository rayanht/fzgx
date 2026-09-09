.include "macros.inc"
.file "ICInvalidateRange.c"

# 0x8000B6E0..0x8000B714 | size: 0x34
.text
.balign 4

# .text:0x0 | 0x8000B6E0 | size: 0x34
.fn ICInvalidateRange, global
/* 8000B6E0 000086E0  28 04 00 00 */	cmplwi r4, 0x0
/* 8000B6E4 000086E4  4C 81 00 20 */	blelr
/* 8000B6E8 000086E8  54 65 06 FE */	clrlwi r5, r3, 27
/* 8000B6EC 000086EC  7C 84 2A 14 */	add r4, r4, r5
/* 8000B6F0 000086F0  38 84 00 1F */	addi r4, r4, 0x1f
/* 8000B6F4 000086F4  54 84 D9 7E */	srwi r4, r4, 5
/* 8000B6F8 000086F8  7C 89 03 A6 */	mtctr r4
.L_8000B6FC:
/* 8000B6FC 000086FC  7C 00 1F AC */	icbi r0, r3
/* 8000B700 00008700  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B704 00008704  42 00 FF F8 */	bdnz .L_8000B6FC
/* 8000B708 00008708  7C 00 04 AC */	sync
/* 8000B70C 0000870C  4C 00 01 2C */	isync
/* 8000B710 00008710  4E 80 00 20 */	blr
.endfn ICInvalidateRange
