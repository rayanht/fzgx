.include "macros.inc"
.file "LCDisable.c"

# 0x8000B83C..0x8000B864 | size: 0x28
.text
.balign 4

# .text:0x0 | 0x8000B83C | size: 0x28
.fn LCDisable, global
/* 8000B83C 0000883C  3C 60 E0 00 */	lis r3, 0xe000
/* 8000B840 00008840  38 80 02 00 */	li r4, 0x200
/* 8000B844 00008844  7C 89 03 A6 */	mtctr r4
.L_8000B848:
/* 8000B848 00008848  7C 00 1B AC */	dcbi r0, r3
/* 8000B84C 0000884C  38 63 00 20 */	addi r3, r3, 0x20
/* 8000B850 00008850  42 00 FF F8 */	bdnz .L_8000B848
/* 8000B854 00008854  7C 98 E2 A6 */	mfspr r4, HID2
/* 8000B858 00008858  54 84 01 04 */	rlwinm r4, r4, 0, 4, 2
/* 8000B85C 0000885C  7C 98 E3 A6 */	mtspr HID2, r4
/* 8000B860 00008860  4E 80 00 20 */	blr
.endfn LCDisable
