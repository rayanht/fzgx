.include "macros.inc"
.file "PPCMtpmc2.c"

# 0x8000A038..0x8000A040 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A038 | size: 0x8
.fn PPCMtpmc2, global
/* 8000A038 00007038  7C 7A EB A6 */	mtspr PMC2, r3
/* 8000A03C 0000703C  4E 80 00 20 */	blr
.endfn PPCMtpmc2
