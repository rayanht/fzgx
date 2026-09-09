#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern SIControl Si_80123B94;

u32 SIDisablePolling(u32 poll) {
    BOOL enabled;
    if (poll == 0) {
        return Si_80123B94.poll;
    }
    enabled = OSDisableInterrupts();
    poll >>= (31 - 7);
    poll &= 0xf0;
    poll = Si_80123B94.poll & ~poll;
    __SIRegs[12] = poll;
    Si_80123B94.poll = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}
