#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/si.h>

typedef struct PADStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

extern void __DVDAudioBufferConfig(struct DVDCommandBlock *block, unsigned long enable,
                                   unsigned long size,
                                   void (*callback)(long, struct DVDCommandBlock *));

void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context);

extern u32 lbl_801A697C;

extern u32 lbl_801A6988;

extern u32 lbl_801A698C;

extern u32 lbl_801A6990;

extern PADStatus lbl_8015D0C0[4];

static void PADDisable(s32 chan);

extern u32 lbl_801A64C8;

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

void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context);

void PADReceiveCheckCallback(s32 chan, u32 type) {
    u32 error;
    u32 chanBit;
    chanBit = 0x80000000 >> chan;
    if (lbl_801A697C & chanBit) {
        error = type & 0xFF;
        type &= ~0xFF;
        lbl_801A6988 &= ~chanBit;
        lbl_801A698C &= ~chanBit;
        if (!(error & (0x0001 | 0x0002 | 0x0008 | 0x0004)) && (type & 0x80000000) &&
            (type & 0x00100000) && (type & 0x40000000) && !(type & 0x04000000) &&
            (type & 0x00080000) == 0x00000000 && !(type & 0x00040000)) {
            SITransfer(chan, &lbl_801A64C8, 1, &lbl_8015D0C0[chan], 10, PADOriginUpdateCallback, 0);
        } else {
            PADDisable(chan);
        }
    }
}
