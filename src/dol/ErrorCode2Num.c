#include <types.h>

extern u32 lbl_80124110[18];

u8 ErrorCode2Num(u32 errorCode) {
    u32 i;
    for (i = 0; i < 18; i++) {
        if (errorCode == lbl_80124110[i]) {
            (void)0;
            return i;
        }
    }
    if (errorCode >= 0x100000 && errorCode <= 0x100008) {
        return 17;
    }
    return 29;
}
