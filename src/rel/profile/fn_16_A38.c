#include "types.h"

struct fn_16_A38_lbl_1_bss_8B614 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x44];
    u32 unk_4C;
};

extern u32 lbl_16_bss_21C;
extern struct fn_16_A38_lbl_1_bss_8B614 lbl_1_bss_8B614;
extern u32 fn_1_4C10(void);

u32 fn_16_A38(void) {
    u32 flags;
    if ((s32)lbl_16_bss_21C == -1) {
        fn_1_4C10();
    }
    flags = lbl_1_bss_8B614.unk_4C;
    if ((flags & 0x80000000) != 0 &&
        (flags & 0x1) == 0 &&
        (lbl_1_bss_8B614.unk_4 & 0x10000000) == 0) {
        return 1;
    }
    return fn_1_4C10() != 0;
}
