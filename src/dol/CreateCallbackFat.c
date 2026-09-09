#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDCreate.h"
#include "sdk_addresses.h"

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

extern CARDControl lbl_80177960[2];

void CreateCallbackFat(s32 chan, s32 result) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    callback = card->apiCallback;
    card->apiCallback = 0;
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    dir = fn_8002C4BC(card);
    ent = &dir[card->freeNo];
    memcpy(ent->gameName, card->diskID->gameName, sizeof(ent->gameName));
    memcpy(ent->company, card->diskID->company, sizeof(ent->company));
    ent->permission = 0x04u;
    ent->copyTimes = 0;
    ent->startBlock = card->startBlock;
    ent->bannerFormat = 0;
    ent->iconAddr = 0xffffffff;
    ent->iconFormat = 0;
    ent->iconSpeed = 0;
    ent->commentAddr = 0xffffffff;
    ((ent)->iconSpeed = (u16)(((ent)->iconSpeed & ~(3 << (2 * (0)))) | ((1) << (2 * (0)))));
    card->fileInfo->offset = 0;
    card->fileInfo->iBlock = ent->startBlock;
    ent->time = (u32)((OSGetTime()) / ((u32)__OSBusClock / 4));
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
error:
    __CARDPutControlBlock(card, result);
    if (callback) {
        callback(chan, result);
    }
}