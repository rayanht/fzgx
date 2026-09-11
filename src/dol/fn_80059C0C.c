#include "types.h"

typedef void (*fn_80059C0C_Fn0)(u32, void *, u32);

struct fn_80059C0C_Data {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x9D4];
};

extern struct fn_80059C0C_Data lbl_8019017C[];
extern u32 lbl_8009264C[];
extern fn_80059C0C_Fn0 lbl_80190178[];

void fn_80059C0C(struct fn_80059C0C_Data *arg0, s32 arg1) {
    struct { s32 value; } v2;
    s32 t;
    fn_80059C0C_Fn0 callback;

    if (arg0 == 0) {
        callback = lbl_80190178[0];
        if (callback != 0) {
            callback(lbl_8019017C[0].unk_0, &lbl_8009264C, 0);
        }
    } else {
        t = arg0->unk_10 * arg0->unk_4;
        arg0->unk_4 = arg1;
        v2.value = arg0->unk_4 + arg0->unk_8;
        v2.value = v2.value - 1;
        arg0->unk_C = v2.value / arg0->unk_4;
        arg0->unk_10 = t / arg0->unk_4;
        arg0->unk_14 = arg0->unk_18 * arg1;
    }
}
