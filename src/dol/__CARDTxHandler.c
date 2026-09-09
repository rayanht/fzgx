#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"

extern CARDControl lbl_80177960[2];

void __CARDTxHandler(s32 chan, OSContext *context) {
    CARDControl *card;
    CARDCallback callback;
    BOOL err;
    card = &lbl_80177960[chan];
    err = !EXIDeselect(chan);
    EXIUnlock(chan);
    callback = card->txCallback;
    if (callback) {
        card->txCallback = 0;
        callback(chan, (!err && EXIProbe(chan)) ? 0 : -3);
    }
}