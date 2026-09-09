#include "types.h"

struct fn_80046AC0_Arg0 {
    u16 unk_0;
    s16 unk_2;
    u8 unk_4[0xE];
    u8 unk_12;
};

s32 fn_80046AC0(struct fn_80046AC0_Arg0 *arg0, s32 arg1, u16 *arg2, u16 *arg3) {
    u8 v1;
    s32 v0;

    if (arg1 < 20) {
        v0 = -1;
    } else {
        if (arg0->unk_0 != 32768) {
            v0 = -2;
        } else {
            if (arg0->unk_2 < 16) {
                v0 = -1;
            } else {
                v1 = arg0->unk_12;
                v0 = 0;
            }
        }
    }
    if (v0 != 0) {
        return -1;
    }
    if (v1 >= 4) {
        if (arg1 < 32) {
            return -1;
        }
        if (arg0->unk_0 != 32768) {
            return -2;
        }
        if (arg0->unk_2 < 28) {
            return -1;
        }
        arg2[0] = *(u16 *)((u8 *)arg0 + 0x18);
        arg3[0] = *(u16 *)((u8 *)arg0 + 0x1A);
        arg2[1] = *(u16 *)((u8 *)arg0 + 0x1C);
        arg3[1] = *(u16 *)((u8 *)arg0 + 0x1E);
    } else {
        arg3[1] = 0;
        arg2[1] = 0;
        arg3[0] = 0;
        arg2[0] = 0;
    }
    return 0;
}
