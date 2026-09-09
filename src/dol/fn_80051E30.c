#include "types.h"

typedef u32 (*fn_80051E30_Fn0)(u32);

extern u32 lbl_8017E58C[];

void fn_80051E30(u32 arg0) {
    if (lbl_8017E58C[0] != 0) {
        ((fn_80051E30_Fn0)lbl_8017E58C[0])(arg0);
    }
}
