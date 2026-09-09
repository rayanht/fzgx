.include "macros.inc"
.file "PPCHalt.c"

# 0x80009FFC..0x8000A010 | size: 0x14
.text
.balign 4

# .text:0x0 | 0x80009FFC | size: 0x14
.fn PPCHalt, weak
/* 80009FFC 00006FFC  7C 00 04 AC */	sync
.L_8000A000:
/* 8000A000 00007000  60 00 00 00 */	nop
/* 8000A004 00007004  38 60 00 00 */	li r3, 0x0
/* 8000A008 00007008  60 00 00 00 */	nop
/* 8000A00C 0000700C  4B FF FF F4 */	b .L_8000A000
.endfn PPCHalt
