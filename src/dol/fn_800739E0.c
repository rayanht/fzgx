#include "types.h"
#include "dol/globals.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
} Entry;

extern void GXSetIndTexCoordScale(s32, s32, s32);

void fn_800739E0(s32 index, s32 arg1, s32 arg2) {
    Entry *entry;

    entry = (Entry *)(lbl_801A6D38 + (index << 3) + 0x874);
    if (entry->unk_00 != arg1 || entry->unk_04 != arg2) {
        GXSetIndTexCoordScale(index, arg1, arg2);
        entry->unk_00 = arg1;
        entry->unk_04 = arg2;
    }
}
