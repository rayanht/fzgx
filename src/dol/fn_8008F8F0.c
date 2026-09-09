#include "types.h"

extern u32 lbl_801A6E28;
extern u8 lbl_801A6E3C;

void fn_8008F8F0(void) {
    lbl_801A6E3C = 1;
    if (lbl_801A6E28 != 0) {
        ((void (*)(s32))lbl_801A6E28)(0);
    }
}
