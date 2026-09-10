#include <types.h>
#include <dolphin/os/OSInterrupt.h>
#include "sdk_addresses.h"

extern u8 __gUnknown800030E3 : FZGX_ADDR___gUnknown800030E3;

BOOL __PADDisableRecalibration(BOOL disable) {
    BOOL enabled;
    BOOL prev;
    enabled = OSDisableInterrupts();
    prev = (__gUnknown800030E3 & 0x40) ? 1 : 0;
    __gUnknown800030E3 &= (u8)~0x40;
    if (disable) {
        __gUnknown800030E3 |= 0x40;
    }
    OSRestoreInterrupts(enabled);
    return prev;
}
