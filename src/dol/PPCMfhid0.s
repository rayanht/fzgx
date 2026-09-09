.include "macros.inc"
.file "PPCMfhid0.c"

# 0x80009FCC..0x80009FD4 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FCC | size: 0x8
.fn PPCMfhid0, global
/* 80009FCC 00006FCC  7C 70 FA A6 */	mfspr r3, HID0
/* 80009FD0 00006FD0  4E 80 00 20 */	blr
.endfn PPCMfhid0
