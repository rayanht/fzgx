#include "types.h"
#include "dol/globals.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} Entry;

typedef struct {
    u8 pad_00[0x20];
    u16 unk_20;
    u16 unk_22;
} Sub;

extern void GXSetIndTexOrder(s32, s32, s32);

void fn_800738E0(s32 arg0, s32 arg1, s32 arg2) {
    Entry *entry = (Entry *)(lbl_801A6D38 + arg0 * 12 + 0x844);

    if (arg2 >= 8) {
        if (entry->unk_00 != arg0 || entry->unk_04 != arg2) {
            GXSetIndTexOrder(arg0, arg1, arg2);
            entry->unk_00 = arg1;
            entry->unk_04 = arg2;
            entry->unk_08 = 0;
            entry->unk_0A = 0;
        }
    } else {
        Sub *sub = (Sub *)(lbl_801A6D38 + arg2 * 36 + 0x720);

        if (entry->unk_00 != arg0 || entry->unk_04 != arg2 ||
            entry->unk_08 != sub->unk_20 || entry->unk_0A != sub->unk_22) {
            GXSetIndTexOrder(arg0, arg1, arg2);
            entry->unk_00 = arg1;
            entry->unk_04 = arg2;
            entry->unk_08 = sub->unk_20;
            entry->unk_0A = sub->unk_22;
        }
    }
}
