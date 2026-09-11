#include "types.h"

extern void fn_800647F0(void);
extern void *fn_80020B3C(u32 arg0, void (*callback)(void), u32 value);
extern void fn_80020ABC(u32 arg0);

extern struct fn_8006496C_lbl_801A6C80_T *lbl_801A6C80;

struct fn_8006496C_Entry {
    u8 unk_0;
    u8 pad_1[0x23];
    u32 unk_24;
    u32 unk_28;
    u32 unk_2c;
    u8 pad_30[0xe8];
};

struct fn_8006496C_lbl_801A6C80_T {
    u8 pad_0[0x44c];
    u32 unk_44c;
    u8 pad_450[0xfb8];
    struct fn_8006496C_Entry entries[0x40];
};

s32 fn_8006496C(u32 arg0) {
    s32 result_index;
    u8 i;
    void *result;

    result_index = -1;
    result = fn_80020B3C(arg0 & 0xff, fn_800647F0, lbl_801A6C80->unk_44c);
    if (result != 0) {
        for (i = 0; i < 0x40; i++) {
            if (lbl_801A6C80->entries[i].unk_0 == 0xff) {
                result_index = i;
                lbl_801A6C80->entries[i].unk_2c = (u32)result;
                lbl_801A6C80->entries[i].unk_24 = lbl_801A6C80->unk_44c;
                break;
            }
        }
    }
    lbl_801A6C80->unk_44c++;
    if (result != 0 && result_index == -1) {
        fn_80020ABC((u32)result);
    }
    return result_index;
}
