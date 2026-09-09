.include "macros.inc"
.file "DCFlushRange.c"

# 0x8000B654..0x8000B684 | size: 0x30
.text
.balign 4

# .text:0x0 | 0x8000B654 | size: 0x30
.fn DCFlushRange, global
/* 8000B654 00008654  28 04 00 00 */	cmplwi r4, 0x0
/* 8000B658 00008658  4C 81 00 20 */	blelr
/* 8000B65C 0000865C  54 65 06 FE */	clrlwi r5, r3, 27
/* 8000B660 00008660  7C 84 2A 14 */	add r4, r4, r5
/* 8000B664 00008664  38 84 00 1F */	addi r4, r4, 0x1f
/* 8000B668 00008668  54 84 D9 7E */	srwi r4, r4, 5
/* 8000B66C 0000866C  7C 89 03 A6 */	mtctr r4
.L_8000B670:
/* 8000B670 00008670  7C 00 18 AC */	dcbf r0, r3
/* 8000B674 00008674  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B678 00008678  42 00 FF F8 */	bdnz .L_8000B670
/* 8000B67C 0000867C  44 00 00 02 */	sc
/* 8000B680 00008680  4E 80 00 20 */	blr
.endfn DCFlushRange
