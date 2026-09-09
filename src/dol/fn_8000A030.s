.include "macros.inc"
.file "fn_8000A030.c"

# 0x8000A030..0x8000A038 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A030 | size: 0x8
.fn fn_8000A030, global
/* 8000A030 00007030  7C 7A EA A6 */	mfspr r3, PMC2
/* 8000A034 00007034  4E 80 00 20 */	blr
.endfn fn_8000A030
