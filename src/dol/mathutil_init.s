.include "macros.inc"
.file "mathutil_init.c"

# 0x8006CFF8..0x8006D044 | size: 0x4C
.text
.balign 4

# .text:0x0 | 0x8006CFF8 | size: 0x4C
.fn mathutil_init, global
/* 8006CFF8 00069FF8  38 60 00 00 */	li r3, 0x0
/* 8006CFFC 00069FFC  7C 70 E3 A6 */	mtspr GQR0, r3
/* 8006D000 0006A000  38 60 00 04 */	li r3, 0x4
/* 8006D004 0006A004  64 63 00 04 */	oris r3, r3, 0x4
/* 8006D008 0006A008  7C 72 E3 A6 */	mtspr GQR2, r3
/* 8006D00C 0006A00C  38 60 00 05 */	li r3, 0x5
/* 8006D010 0006A010  64 63 00 05 */	oris r3, r3, 0x5
/* 8006D014 0006A014  7C 73 E3 A6 */	mtspr GQR3, r3
/* 8006D018 0006A018  38 60 00 06 */	li r3, 0x6
/* 8006D01C 0006A01C  64 63 00 06 */	oris r3, r3, 0x6
/* 8006D020 0006A020  7C 74 E3 A6 */	mtspr GQR4, r3
/* 8006D024 0006A024  38 60 00 07 */	li r3, 0x7
/* 8006D028 0006A028  64 63 00 07 */	oris r3, r3, 0x7
/* 8006D02C 0006A02C  7C 75 E3 A6 */	mtspr GQR5, r3
/* 8006D030 0006A030  38 60 00 00 */	li r3, 0x0
/* 8006D034 0006A034  7C 76 E3 A6 */	mtspr GQR6, r3
/* 8006D038 0006A038  38 60 00 00 */	li r3, 0x0
/* 8006D03C 0006A03C  7C 77 E3 A6 */	mtspr GQR7, r3
/* 8006D040 0006A040  4E 80 00 20 */	blr
.endfn mathutil_init
