#include "types.h"

typedef void (*fn_8005ACF0_Fn)(void *obj, u32 one, void *arg);

struct fn_8005ACF0_Rec {
    u8 pad_0[0x3];
    s8 unk_3;
    u8 pad_4[0x34];
    u8 *unk_38[2];
    u8 pad_40[0x10];
    u8 unk_50[0x20];
    s32 unk_70[2];
    u32 unk_78;
    u32 unk_7C;
    u8 pad_80[0x68];
};

struct fn_8005ACF0_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
};

extern u8 lbl_80191D4C[3716];

void fn_8005ACF0(struct fn_8005ACF0_Arg0 *arg0) {
    u32 v;
    s32 a;
    struct fn_8005ACF0_Rec *rec;
    s32 idx;
    s32 k;

    v = arg0->unk_4;
    a = v & 0x7FFFFFFF;
    k = a / 2;
    rec = (struct fn_8005ACF0_Rec *)(lbl_80191D4C + k * 232);
    idx = a % 2;
    if (rec->unk_70[idx] == 1) {
        u8 *obj = rec->unk_38[idx];
        (*(fn_8005ACF0_Fn *)(*(u32 *)obj + 0x20))(obj, 1, &rec->unk_50[idx * 8]);
        rec->unk_70[idx] = 0;
        if (idx == rec->unk_3 - 1) {
            rec->unk_7C += rec->unk_78;
        }
    }
}
