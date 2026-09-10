#include <dolphin/card/CARDPriv.h>

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

void OSSleepThread(OSThreadQueue *queue);

extern CARDControl lbl_80177960[2];

static inline s32 CARDGetResultCode(s32 chan) {
    CARDControl *card;
    if (chan < 0 || chan >= 2) {
        return -128;
    }
    card = &lbl_80177960[chan];
    return card->result;
}

s32 __CARDSync(s32 channel) {
    CARDControl *card;
    s32 result;
    BOOL enabled;
    card = &lbl_80177960[channel];
    enabled = OSDisableInterrupts();
    while ((result = CARDGetResultCode(channel)) == -1) {
        OSSleepThread(&card->threadQueue);
    }
    OSRestoreInterrupts(enabled);
    return result;
}
