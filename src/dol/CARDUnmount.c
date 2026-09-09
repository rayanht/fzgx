#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDMount.h"

extern CARDControl lbl_80177960[2];

static inline void DoUnmount(s32 chan, s32 result) {
    CARDControl *card;
    BOOL enabled;
    card = &lbl_80177960[chan];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(chan, 0);
        EXIDetach(chan);
        fn_8000AF78(&card->alarm);
        card->attached = 0;
        card->result = result;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
}

s32 CARDUnmount(s32 chan) {
    CARDControl *card;
    s32 result;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    DoUnmount(chan, -3);
    return 0;
}