#include <types.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>

extern u32 lbl_801A697C;

extern u32 lbl_801A6988;

extern u32 lbl_801A698C;

extern u32 lbl_801A64BC;

void PADSetAnalogMode(u32 mode) {
    BOOL enabled;
    u32 mask;
    enabled = OSDisableInterrupts();
    lbl_801A64BC = mode << 8;
    mask = lbl_801A697C;
    lbl_801A697C &= ~mask;
    lbl_801A6988 &= ~mask;
    lbl_801A698C &= ~mask;
    SIDisablePolling(mask);
    OSRestoreInterrupts(enabled);
}
