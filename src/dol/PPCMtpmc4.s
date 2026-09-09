.include "macros.inc"
.file "PPCMtpmc4.c"

# 0x8000A058..0x8000A060 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A058 | size: 0x8
.fn PPCMtpmc4, global
/* 8000A058 00007058  7C 7E EB A6 */	mtspr PMC4, r3
/* 8000A05C 0000705C  4E 80 00 20 */	blr
.endfn PPCMtpmc4
