#include "types.h"

extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 lbl_800921D0[];

u32 fn_80056A50(s32 *arg0, s32 arg1) {
    s32 i;

    if (arg0 == 0) {
        fn_800565FC((u32)&lbl_80092188);
        return 0;
    }

    for (i = 0; i < 16; i++) {
        s32 v = arg0[i * 8 + 14];
        if (v == arg1) {
            break;
        }
    }

    if (i == 16) {
        fn_800565FC((u32)&lbl_800921D0);
        return 0;
    }

    return (u32)arg0[i * 8 + 15];
}
