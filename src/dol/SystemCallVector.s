.include "macros.inc"
.file "SystemCallVector.c"

# 0x800100BC..0x800100DC | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800100BC | size: 0x20
.fn SystemCallVector, global
# .text:0x0 | 0x800100BC | size: 0x0
.sym __OSSystemCallVectorStart, global
/* 800100BC 0000D0BC  7D 30 FA A6 */	mfspr r9, HID0
/* 800100C0 0000D0C0  61 2A 00 08 */	ori r10, r9, 0x8
/* 800100C4 0000D0C4  7D 50 FB A6 */	mtspr HID0, r10
/* 800100C8 0000D0C8  4C 00 01 2C */	isync
/* 800100CC 0000D0CC  7C 00 04 AC */	sync
/* 800100D0 0000D0D0  7D 30 FB A6 */	mtspr HID0, r9
/* 800100D4 0000D0D4  4C 00 00 64 */	rfi
# .text:0x1C | 0x800100D8 | size: 0x0
.sym __OSSystemCallVectorEnd, global
/* 800100D8 0000D0D8  60 00 00 00 */	nop
.endfn SystemCallVector
