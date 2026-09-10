#include "types.h"

struct fn_80073620_entry {
    u8 pad_0[0x6B0];
    s32 unk_6B0[1];
};

extern struct fn_80073620_entry *lbl_801A6D38;
extern void GXSetTevKAlphaSel(s32, s32);

void fn_80073620(s32 index, s32 value) {
    if (lbl_801A6D38->unk_6B0[index] != value) {
        GXSetTevKAlphaSel(index, value);
        lbl_801A6D38->unk_6B0[index] = value;
    }
}
