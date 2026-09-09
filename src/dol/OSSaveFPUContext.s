.include "macros.inc"
.file "OSSaveFPUContext.c"

# 0x8000BDF8..0x8000BE00 | size: 0x8
.text
.balign 4

# .text:0x0 | 0x8000BDF8 | size: 0x8
.fn OSSaveFPUContext, global
/* 8000BDF8 00008DF8  38 A3 00 00 */	addi r5, r3, 0x0
/* 8000BDFC 00008DFC  4B FF FE D4 */	b __OSSaveFPUContext_8000BCD0
.endfn OSSaveFPUContext
