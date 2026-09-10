#include "types.h"

/* Hardware register blocks are volatile because reads and writes have device effects. */
/* Hardware register blocks are volatile because reads and writes have device effects. */

struct ExiRegs {
    u32 pad[10];
    u32 csr;
};

extern volatile struct ExiRegs __EXIRegs;  /* fzgx-allow: S2 memory-mapped register */

void fn_8008EB4C(s32 enable_pi, s32 enable_exi) {
    if (enable_pi) {
        /* PI register address is hardware-defined. */
        /* fzgx-allow: A1 hardware register address */
        /* fzgx-allow: A2 hardware register address */
        *(volatile u32 *)0xCC003000 = (*(volatile u32 *)0xCC003000 & 0x1000) | 0x1000;  /* fzgx-allow: A1,A2 unnamed OS/hardware memory */
    }
if (enable_exi) {
        /* fzgx-allow: A1 hardware register address */
        /* fzgx-allow: A2 hardware register address */
        __EXIRegs.csr = (__EXIRegs.csr & 0x7f5) | 0x8;
    }
}
