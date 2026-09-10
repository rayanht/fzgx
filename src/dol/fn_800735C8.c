#include "types.h"

struct fn_800735C8_entry {
    u8 pad_0[0x670];
    s32 unk_670[1];
};

extern struct fn_800735C8_entry *lbl_801A6D38;
extern void GXSetTevKColorSel(s32, s32);

void fn_800735C8(s32 index, s32 value) {
    if (lbl_801A6D38->unk_670[index] != value) {
        GXSetTevKColorSel(index, value);
        lbl_801A6D38->unk_670[index] = value;
    }
}
