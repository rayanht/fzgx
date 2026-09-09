.include "macros.inc"
.file "fn_8000A020.c"

# 0x8000A020..0x8000A028 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A020 | size: 0x8
.fn fn_8000A020, global
/* 8000A020 00007020  7C 79 EA A6 */	mfspr r3, PMC1
/* 8000A024 00007024  4E 80 00 20 */	blr
.endfn fn_8000A020
