#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDStat.h"
#include "sdk_addresses.h"

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat *stat, CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    if (fileNo < 0 || 127 <= fileNo || (stat->iconAddr != 0xffffffff && 512 <= stat->iconAddr) ||
        (stat->commentAddr != 0xffffffff && (8 * 1024) - 64 < stat->commentAddr % (8 * 1024))) {
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
    ent->bannerFormat = stat->bannerFormat;
    ent->iconAddr = stat->iconAddr;
    ent->iconFormat = stat->iconFormat;
    ent->iconSpeed = stat->iconSpeed;
    ent->commentAddr = stat->commentAddr;
    UpdateIconOffsets(ent, stat);
    if (ent->iconAddr == 0xffffffff) {
        ((ent)->iconSpeed = (u16)(((ent)->iconSpeed & ~(3 << (2 * (0)))) | ((1) << (2 * (0)))));
    }
    ent->time = (u32)((OSGetTime()) / ((u32)__OSBusClock / 4));
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}