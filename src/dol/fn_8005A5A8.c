#include "types.h"

// The retail code performs this read even though its value is discarded.
extern volatile u32 lbl_80092528[36];
extern u8 lbl_801324F0[104];

u8 *fn_8005A5A8(void) {
    lbl_80092528[0];
    return lbl_801324F0;
}
