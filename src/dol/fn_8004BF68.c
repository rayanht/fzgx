#include "types.h"

extern u32 lbl_80090E84[];
extern void fn_800474E4(u32);

s16 fn_8004BF68(u32 arg0, u32 arg1) {
    if (arg0 == 0) {
        fn_800474E4((u32)&lbl_80090E84);
        return 0;
    }
    arg0 = arg0 + (arg1 << 1);
    return *(s16 *)((u8 *)arg0 + 66);
}
