.include "macros.inc"
.file "PPCMthid2.c"

# 0x8000A0B0..0x8000A0B8 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A0B0 | size: 0x8
.fn PPCMthid2, global
/* 8000A0B0 000070B0  7C 78 E3 A6 */	mtspr HID2, r3
/* 8000A0B4 000070B4  4E 80 00 20 */	blr
.endfn PPCMthid2
