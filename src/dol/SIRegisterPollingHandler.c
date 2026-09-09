#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>

extern __OSInterruptHandler lbl_8015CBB0[4];

BOOL SIRegisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;
    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; ++i) {
        if (lbl_8015CBB0[i] == handler) {
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }
    for (i = 0; i < 4; ++i) {
        if (lbl_8015CBB0[i] == 0) {
            lbl_8015CBB0[i] = handler;
            SIEnablePollingInterrupt(1);
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}
