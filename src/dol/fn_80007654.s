.include "macros.inc"
.file "fn_80007654.c"

# 0x80007654..0x80007664 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x80007654 | size: 0x10
.fn fn_80007654, global
/* 80007654 00004654  54 63 00 06 */	clrrwi r3, r3, 28
/* 80007658 00004658  7C 60 1D 26 */	mfsrin r3, r3
/* 8000765C 0000465C  54 63 02 3E */	clrlwi r3, r3, 8
/* 80007660 00004660  4E 80 00 20 */	blr
.endfn fn_80007654
