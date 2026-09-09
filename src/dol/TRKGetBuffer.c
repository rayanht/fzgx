#include "types.h"

extern u8 lbl_801A36E8[];

u32 TRKGetBuffer(s32 arg0) {
    u32 v0;

    v0 = 0;
    if (arg0 >= 0 && arg0 < 3) {
        v0 = (u32)((u8 *)&lbl_801A36E8 + arg0 * 0x890);
    }
    return v0;
}
