.include "macros.inc"
.file "ICFlashInvalidate.c"

# 0x8000B714..0x8000B724 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x8000B714 | size: 0x10
.fn ICFlashInvalidate, global
/* 8000B714 00008714  7C 70 FA A6 */	mfspr r3, HID0
/* 8000B718 00008718  60 63 08 00 */	ori r3, r3, 0x800
/* 8000B71C 0000871C  7C 70 FB A6 */	mtspr HID0, r3
/* 8000B720 00008720  4E 80 00 20 */	blr
.endfn ICFlashInvalidate
