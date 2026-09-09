.include "macros.inc"
.file "__DBExceptionDestination.c"

# 0x80015AA8..0x80015AB8 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x80015AA8 | size: 0x10
.fn __DBExceptionDestination, global
/* 80015AA8 00012AA8  7C 60 00 A6 */	mfmsr r3
/* 80015AAC 00012AAC  60 63 00 30 */	ori r3, r3, 0x30
/* 80015AB0 00012AB0  7C 60 01 24 */	mtmsr r3
/* 80015AB4 00012AB4  4B FF FF AC */	b __DBExceptionDestinationAux
.endfn __DBExceptionDestination
