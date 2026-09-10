#include "types.h"
#include "dol/globals.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 unk_18;
    u8 unk_19;
    u8 _pad_1A[2];
    s32 unk_1C;
} Entry;

extern void GXSetTevIndirect(s32, s32, s32, s32, s32, s32, s32, u8, u8, s32);

void fn_80073B50(u32 index, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg8, s32 arg9) {
    Entry *entry;

    entry = (Entry *)(lbl_801A6D38 + (index << 5) + 0x8E8);
    if (entry->unk_00 != arg1 ||
        entry->unk_04 != arg2 ||
        entry->unk_08 != arg3 ||
        entry->unk_0C != arg4 ||
        entry->unk_10 != arg5 ||
        entry->unk_14 != arg6 ||
        entry->unk_18 != arg7 ||
        entry->unk_19 != arg8 ||
        entry->unk_1C != arg9) {
        GXSetTevIndirect(index, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        entry->unk_00 = arg1;
        entry->unk_04 = arg2;
        entry->unk_08 = arg3;
        entry->unk_0C = arg4;
        entry->unk_10 = arg5;
        entry->unk_14 = arg6;
        entry->unk_18 = arg7;
        entry->unk_19 = arg8;
        entry->unk_1C = arg9;
    }
}
