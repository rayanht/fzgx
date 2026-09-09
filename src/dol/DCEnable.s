.include "macros.inc"
.file "DCEnable.c"

# 0x8000B614..0x8000B628 | size: 0x14
.text
.balign 4

# .text:0x0 | 0x8000B614 | size: 0x14
.fn DCEnable, global
/* 8000B614 00008614  7C 00 04 AC */	sync
/* 8000B618 00008618  7C 70 FA A6 */	mfspr r3, HID0
/* 8000B61C 0000861C  60 63 40 00 */	ori r3, r3, 0x4000
/* 8000B620 00008620  7C 70 FB A6 */	mtspr HID0, r3
/* 8000B624 00008624  4E 80 00 20 */	blr
.endfn DCEnable
