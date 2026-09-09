.include "macros.inc"
.file "fn_8000A040.c"

# 0x8000A040..0x8000A048 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A040 | size: 0x8
.fn fn_8000A040, global
/* 8000A040 00007040  7C 7D EA A6 */	mfspr r3, PMC3
/* 8000A044 00007044  4E 80 00 20 */	blr
.endfn fn_8000A040
