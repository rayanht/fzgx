#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"

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
        fn_800110A8(&card->threadQueue);
    }
    OSRestoreInterrupts(enabled);
    return result;
}