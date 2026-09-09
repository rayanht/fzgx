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

s32 VerifyFAT(CARDControl *card, int *outCurrent) {
    u16 *fat[2];
    u16 *fatp;
    u16 nBlock;
    u16 cFree;
    int i;
    u16 checkSum;
    u16 checkSumInv;
    int errors;
    int current;
    current = errors = 0;
    for (i = 0; i < 2; i++) {
        fatp = fat[i] = (u16 *)((u8 *)card->workArea + (3 + i) * (8 * 1024));
        __CARDCheckSum(&fatp[0x0002u], (8 * 1024) - sizeof(u32), &checkSum, &checkSumInv);
        if (fatp[0x0000u] != checkSum || fatp[0x0001u] != checkSumInv) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }
        cFree = 0;
        for (nBlock = 5; nBlock < card->cBlock; nBlock++) {
            if (fatp[nBlock] == 0x0000u) {
                cFree++;
            }
        }
        if (cFree != fatp[0x0003u]) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }
    }
    if (0 == errors) {
        if (card->currentFat == 0) {
            if (((s16)fat[0][0x0002u] - (s16)fat[1][0x0002u]) < 0) {
                current = 0;
            } else {
                current = 1;
            }
            card->currentFat = fat[current];
            memcpy(fat[current], fat[current ^ 1], (8 * 1024));
        } else {
            current = (card->currentFat == fat[0]) ? 0 : 1;
        }
    }
    if (outCurrent) {
        *outCurrent = current;
    }
    return errors;
}