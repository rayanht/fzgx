#include "types.h"

extern f64 lbl_801A6650[];
extern f64 lbl_801A6658[];
extern f64 lbl_801A74F8;
extern f64 fn_80083F10(u32, u32, void *, void *, void *);
extern u32 lbl_801A6DE0[2];
extern void fn_800829EC(void);

void fn_80083E84(u32 arg0) {
    struct {
        u32 a[2];
    } loc_10;
    u32 loc_C;
    u32 loc_8;
    f64 value;
    f64 abs_value;

    loc_10.a[0] = arg0;
    loc_10.a[1] = 0;
    value = fn_80083F10((0x80000000 - 1), (u32)fn_800829EC, (void *)&loc_10, (void *)&loc_8, (void *)&loc_C);
    abs_value = __fabs(value);
    if ((s32)loc_C != 0 || (lbl_801A74F8 != value && (abs_value < lbl_801A6650[0] || abs_value > lbl_801A6658[0]))) {
        lbl_801A6DE0[0] = 34;
    }
}
