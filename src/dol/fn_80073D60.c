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

extern void GXSetTevIndirect(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#pragma opt_propagation off
void fn_80073D60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Entry *entry;
    s32 v1;
    s32 v0;
    s32 t;

    t = 0;
    if (arg3 & 0xFF) {
        t = 6;
    }
    v0 = t;
    t = 0;
    if (arg2 & 0xFF) {
        t = 7;
    }
    v1 = t;

    entry = (Entry *)(lbl_801A6D38 + (arg0 << 5) + 0x8E8);
    if (entry->unk_00 != arg1 ||
        entry->unk_04 != 0 ||
        entry->unk_08 != v1 ||
        entry->unk_0C != arg4 ||
        entry->unk_10 != v0 ||
        entry->unk_14 != v0 ||
        entry->unk_18 != 0 ||
        entry->unk_19 != 0 ||
        entry->unk_1C != 0) {
        GXSetTevIndirect(arg0, arg1, 0, v1, arg4, v0, v0, 0, 0, 0);
        entry->unk_00 = arg1;
        entry->unk_04 = 0;
        entry->unk_08 = v1;
        entry->unk_0C = arg4;
        entry->unk_10 = v0;
        entry->unk_14 = v0;
        entry->unk_18 = 0;
        entry->unk_19 = 0;
        entry->unk_1C = 0;
    }
}
#pragma opt_propagation reset

