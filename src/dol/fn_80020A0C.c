#include "types.h"

extern u32 lbl_801A6AB8;

u32 fn_80020A0C(u32 arg0) {
    u32 ptr;

    ptr = lbl_801A6AB8;
    if (ptr == 0) {
        return ptr;
    }
    lbl_801A6AB8 = *(u32 *)(ptr + 8);
    return ptr;
}
