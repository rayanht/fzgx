#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDDelete.h"

s32 CARDDeleteAsync(s32 chan, const char *fileName, CARDCallback callback) {
    CARDControl *card;
    s32 fileNo;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    if (fn_8002EDA0(card, fileNo)) {
        return __CARDPutControlBlock(card, -1);
    }
    dir = fn_8002C4BC(card);
    ent = &dir[fileNo];
    card->startBlock = ent->startBlock;
    memset(ent, 0xff, sizeof(CARDDir));
    card->apiCallback = callback ? callback : fn_80029824;
    result = __CARDUpdateDir(chan, DeleteCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}