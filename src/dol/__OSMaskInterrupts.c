#include "sdk_addresses.h"
#include <dolphin/os.h>
#include <dolphin/os/OSInterrupt.h>
#pragma peephole off

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current);

OSInterruptMask __OSMaskInterrupts(OSInterruptMask global) {
    BOOL enabled;
    OSInterruptMask prev;
    OSInterruptMask local;
    OSInterruptMask mask;
    enabled = OSDisableInterrupts();
    prev = *(OSInterruptMask *)FZGX_ADDR___OSGlobalInterruptMask;
    local = *(OSInterruptMask *)FZGX_ADDR___OSLocalInterruptMask;
    mask = ~(prev | local) & global;
    global |= prev;
    *(OSInterruptMask *)FZGX_ADDR___OSGlobalInterruptMask = global;
    while (mask) {
        mask = SetInterruptMask(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}
