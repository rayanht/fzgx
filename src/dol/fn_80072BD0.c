#include "types.h"
#include "dol/globals.h"

extern void fn_80037BF4(u32);

void fn_80072BD0(u32 arg0) {
    u8 value;

    value = *(u8 *)(lbl_801A6D38 + 0xee);
    if (value == 0xff || value != (u8)arg0) {
        fn_80037BF4(arg0);
        *(u8 *)(lbl_801A6D38 + 0xee) = arg0;
    }
}
