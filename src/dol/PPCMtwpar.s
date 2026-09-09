.include "macros.inc"
.file "PPCMtwpar.c"

# 0x8000A0C4..0x8000A0CC | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A0C4 | size: 0x8
.fn PPCMtwpar, global
/* 8000A0C4 000070C4  7C 79 E3 A6 */	mtspr WPAR, r3
/* 8000A0C8 000070C8  4E 80 00 20 */	blr
.endfn PPCMtwpar
