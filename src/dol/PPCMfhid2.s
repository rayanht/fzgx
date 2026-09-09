.include "macros.inc"
.file "PPCMfhid2.c"

# 0x8000A0A8..0x8000A0B0 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A0A8 | size: 0x8
.fn PPCMfhid2, global
/* 8000A0A8 000070A8  7C 78 E2 A6 */	mfspr r3, HID2
/* 8000A0AC 000070AC  4E 80 00 20 */	blr
.endfn PPCMfhid2
