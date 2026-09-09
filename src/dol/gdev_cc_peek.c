#include "types.h"

extern s32 fn_8008F748(void);
extern s32 fn_8008F6BC(void *buf, s32 value);
extern u8 lbl_801A6378[32];
extern void fn_8008E21C(void *table, void *buf, s32 value);

s32 gdev_cc_peek(void) {
    u8 buf[0x500];
    s32 value;

    value = fn_8008F748();
    if (value <= 0) {
        return 0;
    }
    if (fn_8008F6BC(buf, value) == 0) {
        fn_8008E21C(lbl_801A6378, buf, value);
    } else {
        return -0x2719;
    }
    return value;
}

