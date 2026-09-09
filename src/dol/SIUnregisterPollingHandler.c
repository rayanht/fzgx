#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>

extern __OSInterruptHandler lbl_8015CBB0[4];

BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;
    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; ++i) {
        if (lbl_8015CBB0[i] == handler) {
            lbl_8015CBB0[i] = 0;
            for (i = 0; i < 4; ++i) {
                if (lbl_8015CBB0[i]) {
                    break;
                }
            }
            if (i == 4) {
                SIEnablePollingInterrupt(0);
            }
            OSRestoreInterrupts(enabled);
            return 1;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}
