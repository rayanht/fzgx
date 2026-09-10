#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

void AIStopDMA(void) { __DSPRegs[27] &= ~0x8000; }
