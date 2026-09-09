#include "types.h"

extern s32 fn_8008EED8(void);
extern s32 fn_8008EFE0(void *data, s32 value);
extern u8 lbl_801A5E58[32];
extern void fn_8008E21C(u8 *table, void *data, s32 value);

s32 ddh_cc_peek(void) {
    u8 data[0x800];
    s32 value;
    
    value = fn_8008EED8();
    if (value <= 0) {
        return 0;
    }
    if (fn_8008EFE0(data, value) == 0) {
        fn_8008E21C(lbl_801A5E58, data, value);
    } else {
        return -0x2719;
    }
    return value;
}
