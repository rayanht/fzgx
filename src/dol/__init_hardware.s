.include "macros.inc"
.file "__init_hardware.c"

# 0x80003400..0x80003424 | size: 0x24
.section .init, "ax"
.balign 4

# .init:0x0 | 0x80003400 | size: 0x24
.fn __init_hardware, global
/* 80003400 00000400  7C 00 00 A6 */	mfmsr r0
/* 80003404 00000404  60 00 20 00 */	ori r0, r0, 0x2000
/* 80003408 00000408  7C 00 01 24 */	mtmsr r0
/* 8000340C 0000040C  7F E8 02 A6 */	mflr r31
/* 80003410 00000410  48 00 77 45 */	bl __OSPSInit
/* 80003414 00000414  48 00 6C E9 */	bl __OSFPRInit
/* 80003418 00000418  48 00 86 A1 */	bl __OSCacheInit
/* 8000341C 0000041C  7F E8 03 A6 */	mtlr r31
/* 80003420 00000420  4E 80 00 20 */	blr
.endfn __init_hardware
