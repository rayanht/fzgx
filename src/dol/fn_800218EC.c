#include "types.h"

extern u32 lbl_8015FF00[];
extern u32 lbl_801A6AF8;
extern u32 lbl_801A6AFC;
extern u32 lbl_801A6B04;
extern u32 lbl_801A6B08;

void fn_800218EC(void) {
    lbl_801A6B08 = 0;
    lbl_801A6AF8 = 0;
    lbl_801A6AFC = (u32)&lbl_8015FF00;
    lbl_801A6B04 = 1;
}
