#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern SIControl Si_80123B94;

static inline void SITransferCommands(void) { __SIRegs[14] = 0x80000000; }

u32 SIEnablePolling(u32 poll) {
    BOOL enabled;
    u32 en;
    if (poll == 0) {
        return Si_80123B94.poll;
    }
    enabled = OSDisableInterrupts();
    poll >>= (31 - 7);
    en = poll & 0xf0;
    poll &= (en >> 4) | 0x03fffff0;
    poll &= ~0x03ffff00;
    Si_80123B94.poll &= ~(en >> 4);
    Si_80123B94.poll |= poll;
    poll = Si_80123B94.poll;
    SITransferCommands();
    __SIRegs[12] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}
