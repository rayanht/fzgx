#include "types.h"

extern u8 lbl_8019E140[16];

s32 fn_8007048C(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 16; i++) {
        if (lbl_8019E140[i] != 0) {
            count++;
        }
    }
    return 16 - count;
}
