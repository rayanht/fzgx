#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDDelete.h"

s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    if (fileNo < 0 || 127 <= fileNo) {
        return -128;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    dir = fn_8002C4BC(card);
    ent = &dir[fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    if (fn_8002EDA0(card, fileNo)) {
        return __CARDPutControlBlock(card, -1);
    }
    card->startBlock = ent->startBlock;
    memset(ent, 0xff, sizeof(CARDDir));
    card->apiCallback = callback ? callback : fn_80029824;
    result = __CARDUpdateDir(chan, DeleteCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}