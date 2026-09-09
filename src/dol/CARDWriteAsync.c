#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDWrite.h"

s32 CARDWriteAsync(CARDFileInfo *fileInfo, const void *buf, s32 length, s32 offset,
                   CARDCallback callback) {
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;
    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }
    if ((((u32)(offset)) & ((card->sectorSize) - 1)) != 0 ||
        (((u32)(length)) & ((card->sectorSize) - 1)) != 0) {
        return __CARDPutControlBlock(card, -128);
    }
    dir = fn_8002C4BC(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    DCStoreRange((void *)buf, (u32)length);
    card->apiCallback = callback ? callback : fn_80029824;
    card->buffer = (void *)buf;
    result = __CARDEraseSector(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock,
                               EraseCallback_CARDWrite);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}