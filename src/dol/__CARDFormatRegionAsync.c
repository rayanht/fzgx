#include <dolphin/card/CARDPriv.h>

OSTime OSGetTime(void);
void DCStoreRange(void *addr, u32 nBytes);
void fn_80029824(s32 chan, s32 result);

OSSram *__OSLockSram();
OSSramEx *__OSLockSramEx();
void FormatCallback(s32 chan, s32 result);
#include "sdk_addresses.h"

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback) {
    CARDControl *card;
    CARDID *id;
    CARDDir *dir;
    u16 *fat;
    s16 i;
    s32 result;
    OSSram *sram;
    OSSramEx *sramEx;
    u16 viDTVStatus;
    OSTime time;
    OSTime rand;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    id = (CARDID *)card->workArea;
    memset(id, 0xff, (8 * 1024));
    viDTVStatus = __VIRegs[55];
    id->encode = encode;
    sram = __OSLockSram();
    *(u32 *)&id->serial[20] = sram->counterBias;
    *(u32 *)&id->serial[24] = sram->language;
    __OSUnlockSram(0);
    rand = time = OSGetTime();
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        id->serial[i] = (u8)(sramEx->flashID[chan][i] + rand);
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(0);
    *(u32 *)&id->serial[28] = viDTVStatus;
    *(OSTime *)&id->serial[12] = time;
    id->deviceID = 0;
    id->size = card->size;
    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &id->checkSum, &id->checkSumInv);
    for (i = 0; i < 2; i++) {
        CARDDirCheck *check;
        dir = (CARDDir *)((u8 *)card->workArea + (1 + i) * (8 * 1024));
        memset(dir, 0xff, (8 * 1024));
        check = ((CARDDirCheck *)&(dir)[127]);
        check->checkCode = i;
        __CARDCheckSum(dir, (8 * 1024) - sizeof(u32), &check->checkSum, &check->checkSumInv);
    }
    for (i = 0; i < 2; i++) {
        fat = (u16 *)((u8 *)card->workArea + (3 + i) * (8 * 1024));
        memset(fat, 0x00, (8 * 1024));
        fat[0x0002u] = (u16)i;
        fat[0x0003u] = (u16)(card->cBlock - 5);
        fat[0x0004u] = 5 - 1;
        __CARDCheckSum(&fat[0x0002u], (8 * 1024) - sizeof(u32), &fat[0x0000u], &fat[0x0001u]);
    }
    card->apiCallback = callback ? callback : fn_80029824;
    DCStoreRange(card->workArea, (5 * 8 * 1024));
    card->formatStep = 0;
    result = __CARDEraseSector(chan, (u32)card->sectorSize * card->formatStep, FormatCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
