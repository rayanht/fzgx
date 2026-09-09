.include "macros.inc"
.file "PPCMtmmcr1.c"

# 0x8000A018..0x8000A020 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A018 | size: 0x8
.fn PPCMtmmcr1, global
/* 8000A018 00007018  7C 7C EB A6 */	mtspr MMCR1, r3
/* 8000A01C 0000701C  4E 80 00 20 */	blr
.endfn PPCMtmmcr1
