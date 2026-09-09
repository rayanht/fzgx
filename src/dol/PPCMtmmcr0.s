.include "macros.inc"
.file "PPCMtmmcr0.c"

# 0x8000A010..0x8000A018 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A010 | size: 0x8
.fn PPCMtmmcr0, global
/* 8000A010 00007010  7C 78 EB A6 */	mtspr MMCR0, r3
/* 8000A014 00007014  4E 80 00 20 */	blr
.endfn PPCMtmmcr0
