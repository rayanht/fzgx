#include "types.h"
#include "dolphin/sdk/tww/card/CARDStat.h"

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat *stat) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    (void)0;
    (void)0;
    if (fileNo < 0 || 127 <= fileNo)
        return -128;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;
    dir = fn_8002C4BC(card);
    ent = &dir[fileNo];
    result = __CARDAccess(card, ent);
    if (result == -10) {
        result = __CARDIsPublic(ent);
    }
    if (result >= 0) {
        memcpy(stat->gameName, ent->gameName, sizeof(stat->gameName));
        memcpy(stat->company, ent->company, sizeof(stat->company));
        stat->length = (u32)ent->length * card->sectorSize;
        memcpy(stat->fileName, ent->fileName, 32);
        stat->time = ent->time;
        stat->bannerFormat = ent->bannerFormat;
        stat->iconAddr = ent->iconAddr;
        stat->iconFormat = ent->iconFormat;
        stat->iconSpeed = ent->iconSpeed;
        stat->commentAddr = ent->commentAddr;
        UpdateIconOffsets(ent, stat);
    }
    return __CARDPutControlBlock(card, result);
}