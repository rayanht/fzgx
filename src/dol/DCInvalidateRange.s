.include "macros.inc"
.file "DCInvalidateRange.c"

# 0x8000B628..0x8000B654 | size: 0x2C
.text
.balign 4

# .text:0x0 | 0x8000B628 | size: 0x2C
.fn DCInvalidateRange, global
/* 8000B628 00008628  28 04 00 00 */	cmplwi r4, 0x0
/* 8000B62C 0000862C  4C 81 00 20 */	blelr
/* 8000B630 00008630  54 65 06 FE */	clrlwi r5, r3, 27
/* 8000B634 00008634  7C 84 2A 14 */	add r4, r4, r5
/* 8000B638 00008638  38 84 00 1F */	addi r4, r4, 0x1f
/* 8000B63C 0000863C  54 84 D9 7E */	srwi r4, r4, 5
/* 8000B640 00008640  7C 89 03 A6 */	mtctr r4
.L_8000B644:
/* 8000B644 00008644  7C 00 1B AC */	dcbi r0, r3
/* 8000B648 00008648  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B64C 0000864C  42 00 FF F8 */	bdnz .L_8000B644
/* 8000B650 00008650  4E 80 00 20 */	blr
.endfn DCInvalidateRange
