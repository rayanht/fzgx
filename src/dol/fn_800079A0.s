.include "macros.inc"
.file "fn_800079A0.c"

# 0x800079A0..0x800079C4 | size: 0x24
.text
.balign 4

# .text:0x0 | 0x800079A0 | size: 0x24
.fn fn_800079A0, global
/* 800079A0 000049A0  7C 99 02 A6 */	mfsdr1 r4
/* 800079A4 000049A4  54 80 80 1E */	slwi r0, r4, 16
/* 800079A8 000049A8  54 84 00 1E */	clrrwi r4, r4, 16
/* 800079AC 000049AC  60 00 FF FF */	ori r0, r0, 0xffff
/* 800079B0 000049B0  7C 00 18 38 */	and r0, r0, r3
/* 800079B4 000049B4  64 00 80 00 */	oris r0, r0, 0x8000
/* 800079B8 000049B8  7C 84 03 78 */	or r4, r4, r0
/* 800079BC 000049BC  7C 83 23 78 */	mr r3, r4
/* 800079C0 000049C0  4E 80 00 20 */	blr
.endfn fn_800079A0
