#include "sdk_addresses.h"
#include <dolphin/os.h>
#include <dolphin/os/OSTime.h>
#pragma peephole off

OSTime OSGetTime(void);

asm OSTime OSGetTime(void);

OSTime __OSGetSystemTime(void) {
    BOOL enabled;
    OSTime *timeAdjustAddr = (OSTime *)FZGX_ADDR___OSTimeAdjust;
    OSTime result;
    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + OSGetTime();
    OSRestoreInterrupts(enabled);
    return result;
}
