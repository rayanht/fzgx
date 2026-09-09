#include "types.h"

extern s32 lbl_12_bss_0;
extern char lbl_12_rodata_0[49];
extern u32 lbl_12_bss_4;

void fn_12_65C(void) {
    if (lbl_12_bss_0 < 1) {
        lbl_12_bss_4 = (u32)&lbl_12_rodata_0;
        lbl_12_bss_0 = lbl_12_bss_0 + 1;
    }
}
