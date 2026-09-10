#include "types.h"

struct fn_80057EC4_Arg2 {
    u8 pad_0[0x4];
    u32 unk_4;
};

extern u32 fn_800576DC(void);
extern u32 fn_80057728(void);

u32 fn_80057EC4(u8 *arg0, s32 arg1, struct fn_80057EC4_Arg2 *arg2) {
    s32 (*temp_r12)(s32, s32);
    s32 t;
    s32 a;
    s32 b;

    if ((s32)arg2->unk_4 > 0) {
        if (*(u32 *)((u8 *)arg2 + 0) == 0) {
            return (u32)arg0;
        }
        fn_80057728();
        if (arg1 == 0) {
            t = *(s32 *)(arg0 + 0x20);
            a = *(s32 *)(arg0 + 0x14) + t - (s32)arg2->unk_4;
            b = (s32)*(u32 *)((u8 *)arg2 + 0) - *(s32 *)(arg0 + 0x1c);
            if (a % t == b % t) {
                *(s32 *)(arg0 + 0x14) = a % t;
                *(u32 *)(arg0 + 0x10) += arg2->unk_4;
            } else {
                temp_r12 = (s32 (*)(s32, s32))(*(s32 (**)(s32, s32))((u8 *)arg0 + 0x38));
                if (temp_r12 != NULL) {
                    temp_r12(*(s32 *)(arg0 + 0x3c), -3);
                }
            }
            *(u32 *)(arg0 + 0x28) -= arg2->unk_4;
        } else if (arg1 == 1) {
            t = *(s32 *)(arg0 + 0x20);
            a = *(s32 *)(arg0 + 0x18) + t - (s32)arg2->unk_4;
            b = (s32)*(u32 *)((u8 *)arg2 + 0) - *(s32 *)(arg0 + 0x1c);
            if (a % t == b % t) {
                *(s32 *)(arg0 + 0x18) = a % t;
                *(u32 *)(arg0 + 0xc) += arg2->unk_4;
            } else {
                temp_r12 = (s32 (*)(s32, s32))(*(s32 (**)(s32, s32))((u8 *)arg0 + 0x38));
                if (temp_r12 != NULL) {
                    temp_r12(*(s32 *)(arg0 + 0x3c), -3);
                }
            }
            *(u32 *)(arg0 + 0x30) -= arg2->unk_4;
        } else {
            arg2->unk_4 = 0;
            *(u32 *)((u8 *)arg2 + 0) = 0;
            temp_r12 = (s32 (*)(s32, s32))(*(s32 (**)(s32, s32))((u8 *)arg0 + 0x38));
            if (temp_r12 != NULL) {
                temp_r12(*(s32 *)(arg0 + 0x3c), -3);
            }
        }
        return fn_800576DC();
    }
    return (u32)arg0;
}
