#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDCheck.h"

s32 __CARDVerify(CARDControl *card) {
    s32 result;
    int errors;
    result = VerifyID(card);
    if (result < 0) {
        return result;
    }
    errors = VerifyDir(card, ((void *)0));
    errors += VerifyFAT(card, ((void *)0));
    switch (errors) {
    case 0:
        return 0;
    case 1:
        return -6;
    default:
        return -6;
    }
}