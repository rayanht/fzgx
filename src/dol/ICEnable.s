.include "macros.inc"
.file "ICEnable.c"

# 0x8000B724..0x8000B738 | size: 0x14
.text
.balign 4

# .text:0x0 | 0x8000B724 | size: 0x14
.fn ICEnable, global
/* 8000B724 00008724  4C 00 01 2C */	isync
/* 8000B728 00008728  7C 70 FA A6 */	mfspr r3, HID0
/* 8000B72C 0000872C  60 63 80 00 */	ori r3, r3, 0x8000
/* 8000B730 00008730  7C 70 FB A6 */	mtspr HID0, r3
/* 8000B734 00008734  4E 80 00 20 */	blr
.endfn ICEnable
