#include "types.h"

struct fn_16_23A8_lbl_1_bss_8B614 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x44];
    u32 unk_4C;
};

extern struct fn_16_23A8_lbl_1_bss_8B614 lbl_1_bss_8B614;
extern u32 lbl_16_bss_21C;
extern u32 lbl_16_bss_150;
extern u32 lbl_16_bss_B0B4;
extern u16 lbl_1_bss_96A;
extern int fn_1_4C10(void);
extern s32 fn_16_24FC(void);
extern u32 fn_1_4A00(u32, u32, u32);

#pragma opt_common_subs off
void fn_16_23A8(void) {
    u32 v0;
    s32 r;

    if ((s32)lbl_16_bss_21C == -1) {
        fn_1_4C10();
    }
    v0 = lbl_1_bss_8B614.unk_4C;
    if ((v0 & 0x80000000) != 0 && (v0 & 0x1) == 0
        && (lbl_1_bss_8B614.unk_4 & 0x10000000) == 0) {
        r = 1;
    } else {
        if (fn_1_4C10()) {
            r = 1;
        } else {
            r = 0;
        }
    }
    if (!r) {
        if ((s32)lbl_16_bss_21C != -1) {
            u32 t = lbl_16_bss_21C;
            lbl_16_bss_21C = -1;
            lbl_1_bss_96A = t;
        } else {
            r = fn_16_24FC();
            if ((s16)r != 0) {
                fn_1_4A00(0, 15, lbl_16_bss_150);
                lbl_16_bss_B0B4 = 0;
            }
            if ((s16)r == -1) {
                lbl_16_bss_21C = 192;
            }
        }
    }
}
#pragma opt_common_subs reset

