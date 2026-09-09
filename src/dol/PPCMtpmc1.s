.include "macros.inc"
.file "PPCMtpmc1.c"

# 0x8000A028..0x8000A030 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A028 | size: 0x8
.fn PPCMtpmc1, global
/* 8000A028 00007028  7C 79 EB A6 */	mtspr PMC1, r3
/* 8000A02C 0000702C  4E 80 00 20 */	blr
.endfn PPCMtpmc1
