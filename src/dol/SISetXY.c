#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern SIControl Si_80123B94;

u32 SISetXY(u32 x, u32 y) {
    u32 poll;
    BOOL enabled;
    poll = x << 16;
    poll |= y << 8;
    enabled = OSDisableInterrupts();
    Si_80123B94.poll &= ~(0x03ff0000 | 0x0000ff00);
    Si_80123B94.poll |= poll;
    poll = Si_80123B94.poll;
    __SIRegs[12] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}
