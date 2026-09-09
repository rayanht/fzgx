#include <dolphin/card/CARDPriv.h>

void WriteCallback_CARDDir(s32 chan, s32 result);

extern CARDControl lbl_80177960[2];

void WriteCallback_CARDDir(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    if (0 <= result) {
        CARDDir *dir0 = (CARDDir *)((u8 *)card->workArea + 0x2000);
        CARDDir *dir1 = (CARDDir *)((u8 *)card->workArea + 0x4000);
        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, 0x2000);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, 0x2000);
        }
    }
error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
