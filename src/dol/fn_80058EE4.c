#include "types.h"

extern u32 lbl_8018FF70[];

void fn_80058EE4(u32 arg0, u32 arg1) {
    u32 *p;
    p = lbl_8018FF70;
    *p++ = arg0;
    *p = arg1;
}
