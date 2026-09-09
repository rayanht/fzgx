#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDCheck.h"

static inline void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv) {
    u16 *p;
    int i;
    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++) {
        *checksum += *p;
        *checksumInv += ~*p;
    }
    if (*checksum == 0xffff) {
        *checksum = 0;
    }
    if (*checksumInv == 0xffff) {
        *checksumInv = 0;
    }
}

s32 CARDCheckExAsync(s32 chan, s32 *xferBytes, CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir[2];
    u16 *fat[2];
    u16 *map;
    s32 result;
    int errors;
    int currentFat;
    int currentDir;
    s32 fileNo;
    u16 iBlock;
    u16 cBlock;
    u16 cFree;
    BOOL updateFat = 0;
    BOOL updateDir = 0;
    BOOL updateOrphan = 0;
    if (xferBytes) {
        *xferBytes = 0;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    result = VerifyID(card);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    errors = VerifyDir(card, &currentDir);
    errors += VerifyFAT(card, &currentFat);
    if (1 < errors) {
        return __CARDPutControlBlock(card, -6);
    }
    dir[0] = (CARDDir *)((u8 *)card->workArea + (1 + 0) * (8 * 1024));
    dir[1] = (CARDDir *)((u8 *)card->workArea + (1 + 1) * (8 * 1024));
    fat[0] = (u16 *)((u8 *)card->workArea + (3 + 0) * (8 * 1024));
    fat[1] = (u16 *)((u8 *)card->workArea + (3 + 1) * (8 * 1024));
    switch (errors) {
    case 0:
        break;
    case 1:
        if (!card->currentDir) {
            card->currentDir = dir[currentDir];
            memcpy(dir[currentDir], dir[currentDir ^ 1], (8 * 1024));
            updateDir = 1;
        } else {
            card->currentFat = fat[currentFat];
            memcpy(fat[currentFat], fat[currentFat ^ 1], (8 * 1024));
            updateFat = 1;
        }
        break;
    }
    map = fat[currentFat ^ 1];
    memset(map, 0, (8 * 1024));
    for (fileNo = 0; fileNo < 127; fileNo++) {
        CARDDir *ent;
        ent = &card->currentDir[fileNo];
        if (ent->gameName[0] == 0xff) {
            continue;
        }
        for (iBlock = ent->startBlock, cBlock = 0; iBlock != 0xFFFF && cBlock < ent->length;
             iBlock = card->currentFat[iBlock], ++cBlock) {
            if (!(5 <= (iBlock) && (iBlock) < (card)->cBlock) || 1 < ++map[iBlock]) {
                return __CARDPutControlBlock(card, -6);
            }
        }
        if (cBlock != ent->length || iBlock != 0xFFFF) {
            return __CARDPutControlBlock(card, -6);
        }
    }
    cFree = 0;
    for (iBlock = 5; iBlock < card->cBlock; iBlock++) {
        u16 nextBlock;
        nextBlock = card->currentFat[iBlock];
        if (map[iBlock] == 0) {
            if (nextBlock != 0x0000u) {
                card->currentFat[iBlock] = 0x0000u;
                updateOrphan = 1;
            }
            cFree++;
        } else if (!(5 <= (nextBlock) && (nextBlock) < (card)->cBlock) && nextBlock != 0xFFFF) {
            return __CARDPutControlBlock(card, -6);
        }
    }
    if (cFree != card->currentFat[0x0003u]) {
        card->currentFat[0x0003u] = cFree;
        updateOrphan = 1;
    }
    if (updateOrphan) {
        __CARDCheckSum(&card->currentFat[0x0002u], (8 * 1024) - sizeof(u32),
                       &card->currentFat[0x0000u], &card->currentFat[0x0001u]);
    }
    memcpy(fat[currentFat ^ 1], fat[currentFat], (8 * 1024));
    if (updateDir) {
        if (xferBytes) {
            *xferBytes = (8 * 1024);
        }
        return __CARDUpdateDir(chan, callback);
    }
    if (updateFat | updateOrphan) {
        if (xferBytes) {
            *xferBytes = (8 * 1024);
        }
        return __CARDUpdateFatBlock(chan, card->currentFat, callback);
    }
    __CARDPutControlBlock(card, 0);
    if (callback) {
        BOOL enabled = OSDisableInterrupts();
        callback(chan, 0);
        OSRestoreInterrupts(enabled);
    }
    return 0;
}