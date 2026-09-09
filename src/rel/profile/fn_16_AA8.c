#include "types.h"

struct fn_16_AA8_lbl_1_bss_8B614 {
    u8 pad_0[0x4C];
    u32 unk_4C;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
};

extern struct fn_16_AA8_lbl_1_bss_8B614 lbl_1_bss_8B614;

void fn_16_AA8(void) {
    s16 delta;
    s16 value;
    struct fn_16_AA8_lbl_1_bss_8B614 *p = &lbl_1_bss_8B614;

    if (!(p->unk_4C & 0x80000000)) {
        return;
    }
    delta = p->unk_50;
    value = p->unk_52;
    value += delta;
    p->unk_52 = value;
    if (delta <= 0 || value < p->unk_54) {
        if (delta >= 0) {
            return;
        }
        if (p->unk_52 > lbl_1_bss_8B614.unk_54) {
            return;
        }
    }
    p->unk_4C = 0;
}
