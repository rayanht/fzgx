#include "types.h"

extern struct fn_800647B8_lbl_801A6C80_T *lbl_801A6C80;
extern void fn_80064A30(u32 arg0, u32 arg1);

struct fn_800647B8_lbl_801A6C80_T {
    u8 pad_0[0x444];
    u32 unk_444;
};

void fn_800647B8(u32 arg0) {
    u32 value;

    value = ((lbl_801A6C80->unk_444 >> 4) & 1) ? 0 : 15;
    fn_80064A30(arg0, value);
}
