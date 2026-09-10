#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>

extern u32 lbl_801A697C;

extern u32 lbl_801A6988;

extern u32 lbl_801A698C;

extern u32 lbl_801A6990;

static void PADDisable(s32 chan);

void UpdateOrigin(s32 chan);

static inline void PADDisable(s32 chan) {
    BOOL enabled;
    u32 chanBit;
    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    lbl_801A697C &= ~chanBit;
    lbl_801A6988 &= ~chanBit;
    lbl_801A698C &= ~chanBit;
    lbl_801A6990 &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

void UpdateOrigin(s32 chan);

void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context) {
    (void)0;
    if (!(lbl_801A697C & (0x80000000 >> chan)))
        return;
    if (!(error & (0x0001 | 0x0002 | 0x0008 | 0x0004)))
        UpdateOrigin(chan);
    if (error & 0x0008) {
        PADDisable(chan);
    }
}
