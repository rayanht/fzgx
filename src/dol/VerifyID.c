#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDCheck.h"

extern CARDControl lbl_80177960[2];

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

s32 VerifyID(CARDControl *card) {
    CARDID *id;
    u16 checksum;
    u16 checksumInv;
    OSSramEx *sramEx;
    OSTime rand;
    int i;
    id = card->workArea;
    if (id->deviceID != 0 || id->size != card->size) {
        return -6;
    }
    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &checksum, &checksumInv);
    if (id->checkSum != checksum || id->checkSumInv != checksumInv) {
        return -6;
    }
    rand = *(OSTime *)&id->serial[12];
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        if (id->serial[i] != (u8)(sramEx->flashID[card - lbl_80177960][i] + rand)) {
            __OSUnlockSramEx(0);
            return -6;
        }
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(0);
    if (id->encode != fn_8002A744()) {
        return -13;
    }
    return 0;
}