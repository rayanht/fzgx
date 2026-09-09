.include "macros.inc"
.file "PPCMtpmc3.c"

# 0x8000A048..0x8000A050 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000A048 | size: 0x8
.fn PPCMtpmc3, global
/* 8000A048 00007048  7C 7D EB A6 */	mtspr PMC3, r3
/* 8000A04C 0000704C  4E 80 00 20 */	blr
.endfn PPCMtpmc3
