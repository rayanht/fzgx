#include "types.h"

typedef struct Fn8006B628Data {
    u8 pad_0[4];
    struct {
        u8 flag7 : 1;
        u8 flag6 : 1;
        u8 rest : 6;
    } flags;
    u8 pad_5[3];
    u32 unk_8;
    u8 pad_C[0x44];
    u8 data[1];
} Fn8006B628Data;

extern u8 lbl_80199670[18720];
extern void fn_8006BC50(void *data);
extern s32 fn_8006BB30(void *data, u32 value, u32 param);

s32 fn_8006B628(u32 value, u32 param) {
    u32 index;
    Fn8006B628Data *entry;
    u32 enabled;

    index = value >> 16;
    if (index >= 4) {
        return -2;
    }
    entry = (Fn8006B628Data *)(lbl_80199670 + index * 0x1248);
    enabled = entry->flags.flag7;
    if (enabled == 0) {
        return -2;
    }
    if (param == 0) {
        return -2;
    }
    if (entry->flags.flag6) {
        if (entry != 0 && (u32)entry + 0x10000 != 0xffff && enabled != 0) {
            entry->flags.flag7 = 0;
            entry->flags.flag6 = 0;
            fn_8006BC50(&entry->data[0]);
            entry->unk_8 = -1;
        }
        return -2;
    }
    return fn_8006BB30(&entry->data[0], value, param);
}
