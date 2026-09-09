#include "types.h"

extern u8 *lbl_801A6680;
extern void (*lbl_801A6E20)(u32);

void fn_8008EDB0(void) {
    *lbl_801A6680 = 1;
    if (lbl_801A6E20 != 0) {
        lbl_801A6E20(0);
    }
}
