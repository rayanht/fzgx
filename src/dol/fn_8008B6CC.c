#include "types.h"

struct fn_8008B6CC_lbl_8015B884 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_c;
    u32 unk_10;
};
struct fn_8008B6CC_gTRKCPUState {
    u8 pad_0[0x1f8];
    u32 unk_1f8;
};
struct fn_8008B6CC_gTRKState {
    u8 pad_0[0x98];
    u32 unk_98;
};

extern struct fn_8008B6CC_lbl_8015B884 lbl_8015B884;
extern struct fn_8008B6CC_gTRKCPUState gTRKCPUState;
extern struct fn_8008B6CC_gTRKState gTRKState;
extern u32 lbl_80095BA8[];
extern u32 MWTRACE(u32, ...);

s32 fn_8008B6CC(u32 arg0, u32 arg1, u32 arg2) {
    struct fn_8008B6CC_lbl_8015B884 *p_lbl_8015B884;
    u32 v0;
    u32 v1;
    u32 t0;

    v0 = arg0;
    if ((s32)arg2 != 0) {
        v0 = 1795;
    } else {
        p_lbl_8015B884 = (struct fn_8008B6CC_lbl_8015B884 *)&lbl_8015B884;
        p_lbl_8015B884->unk_c = v0;
        v0 = 1;
        p_lbl_8015B884->unk_10 = arg1;
        p_lbl_8015B884->unk_4 = 1;
        p_lbl_8015B884->unk_0 = 1;
        t0 = MWTRACE(v0, (u32)&lbl_80095BA8);
        v0 = t0;
        v1 = p_lbl_8015B884->unk_4;
        gTRKCPUState.unk_1f8 = gTRKCPUState.unk_1f8 | 1024;
        if ((s32)v1 == 0 || (s32)v1 == 16) {
            struct fn_8008B6CC_lbl_8015B884 *p_lbl_8015B884_2;
            p_lbl_8015B884_2 = (struct fn_8008B6CC_lbl_8015B884 *)&lbl_8015B884;
            v0 = p_lbl_8015B884_2->unk_8;
            p_lbl_8015B884_2->unk_8 = v0 - 1;
        }
        gTRKState.unk_98 = 0;
        v0 = 0;
    }
    return v0;
}
