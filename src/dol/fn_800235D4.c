#include "types.h"

extern u32 lbl_801A6B70;
extern u32 lbl_801A6B74;
extern u32 lbl_801A6B78;
extern u32 lbl_801A6B7C;

u32 fn_800235D4(void) {
    u32 result;

    if (lbl_801A6B7C != 0) {
        result = lbl_801A6B70 + lbl_801A6B78++ * 56;
        lbl_801A6B78 %= lbl_801A6B74;
        return result;
    }
    return 0;
}
