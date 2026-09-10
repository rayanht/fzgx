#include "types.h"

extern u32 lbl_801A6D38;
extern u32 fn_80035960(u32, u32, u32, u32, u32, u32, u32);

typedef struct {
    u8 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} fn_800747D0_Entry;

void fn_800747D0(u32 arg0, u32 arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, s32 arg6) {
    fn_800747D0_Entry *entry;
    u32 id;

    id = arg0;
    switch (arg0) {
    case 0:
        entry = (fn_800747D0_Entry *)(lbl_801A6D38 + 3120);
        break;
    case 1:
        entry = (fn_800747D0_Entry *)(lbl_801A6D38 + 3144);
        break;
    case 2:
        entry = (fn_800747D0_Entry *)(lbl_801A6D38 + 3168);
        break;
    case 3:
        break;
    case 4:
        fn_800747D0(0, arg1, arg2, arg3, arg4, arg5, arg6);
        id = 2;
        entry = (fn_800747D0_Entry *)(lbl_801A6D38 + 3168);
        break;
    case 5:
        fn_800747D0(1, arg1, arg2, arg3, arg4, arg5, arg6);
        id = 3;
        entry = (fn_800747D0_Entry *)(lbl_801A6D38 + 3192);
        break;
    }
    if (entry->unk_00 != (arg1 & 0xFF) || entry->unk_04 != arg2 || entry->unk_08 != arg3 || entry->unk_0C != arg4 || entry->unk_10 != arg5 || entry->unk_14 != arg6) {
        fn_80035960(id, arg1, arg2, arg3, arg4, arg5, arg6);
        entry->unk_00 = arg1;
        entry->unk_04 = arg2;
        entry->unk_08 = arg3;
        entry->unk_0C = arg4;
        entry->unk_10 = arg5;
        entry->unk_14 = arg6;
    }
}
