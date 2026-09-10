#include "types.h"

extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 lbl_800921F4[];

typedef struct {
    u8 pad20[0x20];
    u32 offset;
    u32 count;
    u8 pad2c[0x10];
    u32 values[1];
} Fn80056B50Data;

s32 fn_80056B50(Fn80056B50Data *arg0, s32 arg1) {
    if (arg0 == 0) {
        fn_800565FC((u32)&lbl_80092188);
        return -1;
    }
    if (arg1 < 0 || arg1 >= (s32)arg0->count) {
        fn_800565FC((u32)&lbl_800921F4);
        return -1;
    }
    arg1 = arg0->offset + arg1;
    arg0 = (Fn80056B50Data *)((u8 *)arg0 + (arg1 % 16) * 32);
    return arg0->values[0];
}
