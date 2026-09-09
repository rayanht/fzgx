#include "types.h"
#include "dolphin/sdk/tww/card/CARDRead.h"

s32 CARDReadAsync(CARDFileInfo *fileInfo, void *buf, s32 length, s32 offset,
                  CARDCallback callback) {
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;
    (void)0;
    (void)0;
    (void)0;
    if ((((u32)(offset) & ((0x200u) - 1))) != 0 || (((u32)(length) & ((0x200u) - 1))) != 0)
        return -128;
    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0)
        return result;
    dir = fn_8002C4BC(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result == -10) {
        result = __CARDIsPublic(ent);
    }
    if (result < 0)
        return __CARDPutControlBlock(card, result);
    DCInvalidateRange(buf, (u32)length);
    card->apiCallback = callback ? callback : fn_80029824;
    offset = (s32)(((u32)(fileInfo->offset) & ((card->sectorSize) - 1)));
    length = (length < card->sectorSize - offset) ? length : card->sectorSize - offset;
    result = __CARDRead(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock + offset, length,
                        buf, ReadCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}