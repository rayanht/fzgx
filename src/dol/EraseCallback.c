#include <dolphin/card/CARDPriv.h>

void WriteCallback(s32 chan, s32 result);

void EraseCallback(s32 chan, s32 result);

extern CARDControl lbl_80177960[2];

static inline u16 *__CARDGetFatBlock(CARDControl *card) { return card->currentFat; }

void EraseCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    u32 temp[2];
    u16 *fat;
    u32 addr;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    fat = __CARDGetFatBlock(card);
    addr = ((u32)fat - (u32)card->workArea) / (8 * 1024) * card->sectorSize;
    result = __CARDWrite(chan, addr, (8 * 1024), fat, WriteCallback);
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
error:
    if (card->apiCallback == ((void *)0)) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = ((void *)0);
        callback(chan, result);
    }
}
