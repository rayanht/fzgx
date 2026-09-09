#include <dolphin/card/CARDPriv.h>

void WriteCallback_CARDDir(s32 chan, s32 result);

void EraseCallback_CARDDir(s32 chan, s32 result);

extern CARDControl lbl_80177960[2];

static inline CARDDir *__CARDGetDirBlock(CARDControl *card) { return card->currentDir; }

void EraseCallback_CARDDir(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    CARDDir *dir;
    u32 tmp[2];
    u32 addr;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    dir = __CARDGetDirBlock(card);
    addr = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
    result = __CARDWrite(chan, addr, 0x2000, dir, WriteCallback_CARDDir);
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
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
