#include "sdk_addresses.h"
#include <dolphin/os.h>
#include <dolphin/os/OSTime.h>
#pragma peephole off

OSTime __OSTimeToSystemTime(OSTime time) {
    BOOL enabled;
    OSTime *timeAdjustAddr = (OSTime *)FZGX_ADDR___OSTimeAdjust;
    OSTime result;
    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + time;
    OSRestoreInterrupts(enabled);
    return result;
}
