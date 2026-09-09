#include <dolphin/si/SIPriv.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

void SITransferCommands(void) { __SIRegs[14] = 0x80000000; }
