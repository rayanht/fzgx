#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"

extern CARDControl lbl_80177960[2];

void TimeoutHandler(OSAlarm *alarm, OSContext *context) {
    s32 chan;
    CARDControl *card;
    CARDCallback callback;
    for (chan = 0; chan < 2; ++chan) {
        card = &lbl_80177960[chan];
        if (alarm == &card->alarm) {
            break;
        }
    }
    if (!card->attached) {
        return;
    }
    EXISetExiCallback(chan, ((void *)0));
    callback = card->exiCallback;
    if (callback) {
        card->exiCallback = 0;
        callback(chan, -5);
    }
}