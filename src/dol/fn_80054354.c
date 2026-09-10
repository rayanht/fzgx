#include "types.h"

struct fn_80054354_object {
    u32 unk_0;
    u8 unk_4;
    u8 unk_5;
    u8 count;
    u8 unk_7;
    u32 unk_8;
    u32 unk_c;
    u32 data[10];
    u32 unk_38;
    u32 unk_3c;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    u32 unk_4c;
};

extern u32 lbl_801873EC[];
extern u32 memset(u32, u32, u32);
extern u32 fn_800504EC(u32);
extern u32 fn_800517C0(u32, u32);

u32 fn_80054354(u32 arg0, s32 arg1, u32 *arg2, u32 *arg3, u32 arg4) {
    s32 index;
    struct fn_80054354_object *obj;
    s32 i;

    for (index = 0; index < 16; index++) {
        if (lbl_801873EC[index] == 0) {
            break;
        }
    }
    if (index == 16) {
        return 0;
    }

    memset((u32)arg3, 0, arg4);
    {
        u32 *table;
        table = lbl_801873EC;
        table[index] = (u32)arg3;
        obj = (struct fn_80054354_object *)table[index];
    }
    obj->unk_38 = index;
    obj->unk_8 = fn_800504EC(arg0);
    if (obj->unk_8 == 0) {
        return 0;
    }
    obj->unk_0 = fn_800517C0((u32)&obj->unk_4c, 0x2bcc);
    if (obj->unk_0 == 0) {
        return 0;
    }

    obj->count = (u8)arg1;
    obj->unk_c = arg0;
    for (i = 0; i < arg1; i++) {
        obj->data[i] = arg2[i];
    }
    obj->unk_5 = 0;
    obj->data[2] = 0;
    obj->data[3] = 0;
    obj->data[4] = 0;
    obj->data[5] = 0;
    obj->data[6] = 0x7fffffff;
    obj->data[7] = 0xffffffff;
    obj->data[8] = 0;
    obj->data[9] = 0;
    obj->unk_7 = 0;
    obj->unk_3c = 0;
    obj->unk_40 = 0;
    obj->unk_44 = 0;
    obj->unk_48 = 0;
    obj->unk_4 = 1;
    return (u32)obj;
}
