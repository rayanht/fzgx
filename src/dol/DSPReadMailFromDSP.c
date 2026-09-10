#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

u32 DSPReadMailFromDSP() {
    u16 reg1;
    u16 reg2;
    reg1 = __DSPRegs[2];
    reg2 = __DSPRegs[3];
    return reg1 << 16 | reg2;
}
