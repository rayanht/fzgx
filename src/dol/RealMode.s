.include "macros.inc"
.file "RealMode.c"

# 0x8000E954..0x8000E96C | size: 0x18
.text
.balign 4

# .text:0x0 | 0x8000E954 | size: 0x18
.fn RealMode_8000E954, global
/* 8000E954 0000B954  54 63 00 BE */	clrlwi r3, r3, 2
/* 8000E958 0000B958  7C 7A 03 A6 */	mtsrr0 r3
/* 8000E95C 0000B95C  7C 60 00 A6 */	mfmsr r3
/* 8000E960 0000B960  54 63 07 32 */	rlwinm r3, r3, 0, 28, 25
/* 8000E964 0000B964  7C 7B 03 A6 */	mtsrr1 r3
/* 8000E968 0000B968  4C 00 00 64 */	rfi
.endfn RealMode_8000E954
