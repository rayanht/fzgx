#include "types.h"

extern volatile u32 __DSPRegs[]; /* hardware register block */

void AIStartDMA(void) {
    ((volatile u16 *)__DSPRegs)[0x36 / 2] |= 0x8000; /* hardware register access */
}
