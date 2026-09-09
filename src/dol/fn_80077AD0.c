#include "types.h"

struct fn_80077AD0_Arg0 {
    u8 pad_0[0x1E];
    u8 unk_1E;
};

extern u32 lbl_801A6DA4;

u32 fn_80077AD0(struct fn_80077AD0_Arg0 *arg0, u32 arg1) {
    u32 v0;
    s32 v1;
    s32 v2;

    v0 = arg1;
    v2 = 0;
    v1 = 0;
    while (v2 < (s32)arg0->unk_1E) {
        v2++;
        *(u32 *)((u8 *)lbl_801A6DA4 + v1) = v0;
        v0 += 48;
        v1 += 4;
    }
    return arg0->unk_1E;
}
