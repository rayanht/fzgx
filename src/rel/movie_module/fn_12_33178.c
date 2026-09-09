#include "types.h"

extern s32 lbl_12_bss_1B758;
extern u32 lbl_12_bss_1B75C[5];

void fn_12_33178(u32 arg0) {
    if (--lbl_12_bss_1B758 > 0) {
        return;
    }
    lbl_12_bss_1B75C[0] = 0;
    lbl_12_bss_1B75C[1] = 0;
    lbl_12_bss_1B75C[2] = 0;
}
