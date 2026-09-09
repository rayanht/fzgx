#include "types.h"

extern u32 lbl_12_bss_10[300];

typedef void (*Fn12Callback)(u32, u32);

void fn_12_309C(u32 a, u32 b, u32 c) {
    Fn12Callback callback;
    u32 count;
    u32 value;

    callback = (Fn12Callback)lbl_12_bss_10[2];
    count = lbl_12_bss_10[4];
    value = lbl_12_bss_10[3];
    lbl_12_bss_10[4] = count + 1;
    if (callback != 0) {
        callback(value, c);
    }
}

