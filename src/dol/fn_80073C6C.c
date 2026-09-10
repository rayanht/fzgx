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

void fn_80073C6C(s32 index) {

{
    Entry *entry;
    entry = (Entry *)(lbl_801A6D38 + (index << 5) + 0x8E8);
    if (entry->unk_00 != 0 ||
        entry->unk_04 != 0 ||
        entry->unk_08 != 0 ||
        entry->unk_0C != 0 ||
        entry->unk_10 != 0 ||
        entry->unk_14 != 0 ||
        entry->unk_18 != 0 ||
        entry->unk_19 != 0 ||
        entry->unk_1C != 0) {
        GXSetTevIndirect(index, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        entry->unk_00 = 0;
        entry->unk_04 = 0;
        entry->unk_08 = 0;
        entry->unk_0C = 0;
        entry->unk_10 = 0;
        entry->unk_14 = 0;
        entry->unk_18 = 0;
        entry->unk_19 = 0;
        entry->unk_1C = 0;
}
    }
}
