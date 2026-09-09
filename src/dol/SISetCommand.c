#include "types.h"

extern volatile u32 SIRegs[];  /* fzgx-allow: S2 memory-mapped register */

void SISetCommand(u32 chan, u32 command) {
    SIRegs[chan * 3] = command;
}
