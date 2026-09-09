#include <dolphin/card/CARDPriv.h>

void DoUnmount(s32 chan, s32 result);
s32 fn_8002D8F8(s32 chan);

extern CARDControl lbl_80177960[2];

void __CARDMountCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    switch (result) {
    case 0:
        if (++card->mountStep < (5 + 2)) {
            result = fn_8002D8F8(chan);
            if (0 <= result) {
                return;
            }
        } else {
            result = __CARDVerify(card);
        }
        break;
    case 1:
        card->unlockCallback = __CARDMountCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            return;
        }
        card->unlockCallback = 0;
        result = fn_8002D8F8(chan);
        if (0 <= result) {
            return;
        }
        break;
    case -5:
    case -3:
        DoUnmount(chan, result);
        break;
    }
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}
