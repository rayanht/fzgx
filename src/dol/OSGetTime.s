.include "macros.inc"
.file "OSGetTime.c"

# 0x8001140C..0x80011424 | size: 0x18
.text
.balign 4

# .text:0x0 | 0x8001140C | size: 0x18
.fn OSGetTime, global
/* 8001140C 0000E40C  7C 6D 42 E6 */	mftb r3, 269
/* 80011410 0000E410  7C 8C 42 E6 */	mftb r4, 268
/* 80011414 0000E414  7C AD 42 E6 */	mftb r5, 269
/* 80011418 0000E418  7C 03 28 00 */	cmpw r3, r5
/* 8001141C 0000E41C  40 82 FF F0 */	bne OSGetTime
/* 80011420 0000E420  4E 80 00 20 */	blr
.endfn OSGetTime
