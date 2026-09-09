.include "macros.inc"
.file "DCStoreRange.c"

# 0x8000B684..0x8000B6B4 | size: 0x30
.text
.balign 4

# .text:0x0 | 0x8000B684 | size: 0x30
.fn DCStoreRange, global
/* 8000B684 00008684  28 04 00 00 */	cmplwi r4, 0x0
/* 8000B688 00008688  4C 81 00 20 */	blelr
/* 8000B68C 0000868C  54 65 06 FE */	clrlwi r5, r3, 27
/* 8000B690 00008690  7C 84 2A 14 */	add r4, r4, r5
/* 8000B694 00008694  38 84 00 1F */	addi r4, r4, 0x1f
/* 8000B698 00008698  54 84 D9 7E */	srwi r4, r4, 5
/* 8000B69C 0000869C  7C 89 03 A6 */	mtctr r4
.L_8000B6A0:
/* 8000B6A0 000086A0  7C 00 18 6C */	dcbst r0, r3
/* 8000B6A4 000086A4  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B6A8 000086A8  42 00 FF F8 */	bdnz .L_8000B6A0
/* 8000B6AC 000086AC  44 00 00 02 */	sc
/* 8000B6B0 000086B0  4E 80 00 20 */	blr
.endfn DCStoreRange
