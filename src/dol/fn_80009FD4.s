.include "macros.inc"
.file "fn_80009FD4.c"

# 0x80009FD4..0x80009FDC | size: 0x8
.text
.balign 4

# .text:0x0 | 0x80009FD4 | size: 0x8
.fn fn_80009FD4, global
/* 80009FD4 00006FD4  7C 70 FB A6 */	mtspr HID0, r3
/* 80009FD8 00006FD8  4E 80 00 20 */	blr
.endfn fn_80009FD4
