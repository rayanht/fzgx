#include "types.h"

struct fn_8006C6E8_Arg0 {
    u8 pad_0[0x24];
    u32 unk_24;
    u8 pad_28[0x10];
    u32 unk_38;
    u32 unk_3C;
};

struct fn_8006C6E8_Arg1 {
    u8 pad_0[0x2];
    u8 unk_2;
    u8 unk_3;
    s16 unk_4;
    s16 unk_6;
};

s32 fn_8006C6E8(struct fn_8006C6E8_Arg0 *arg0, struct fn_8006C6E8_Arg1 *arg1) {
    s32 count;
    s32 current;
    s32 value;
    s32 delta;

    count = arg0->unk_38;
    current = *(s32 *)((u8 *)arg0->unk_24 + 0xc);
    if (current < count) {
        delta = current - count;
        value = delta * arg1->unk_4 / 0x20000;
        if (-(s32)arg1->unk_2 > value) {
            value = -(s32)arg1->unk_2;
        }
        if ((s32)arg1->unk_2 < value) {
            value = arg1->unk_2;
        }
        return -value;
    }

    count = arg0->unk_3C;
    if (current > count) {
        delta = current - count;
        value = delta * arg1->unk_6 / 0x20000;
        if (-((s32)arg1->unk_3) > value) {
            value = -((s32)arg1->unk_3);
        }
        if ((s32)arg1->unk_3 < value) {
            value = arg1->unk_3;
        }
        return -value;
    }
    return 0;
}
