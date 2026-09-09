.include "macros.inc"
.file "fn_12_52E8.c"

# 0x000052E8..0x000052F8 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x52E8 | size: 0x10
.fn fn_12_52E8, global
/* 000052E8 000053D4  38 00 00 07 */	li r0, 0x7
/* 000052EC 000053D8  64 00 00 07 */	oris r0, r0, 0x7
/* 000052F0 000053DC  7C 17 E3 A6 */	mtspr GQR7, r0
/* 000052F4 000053E0  4E 80 00 20 */	blr
.endfn fn_12_52E8
