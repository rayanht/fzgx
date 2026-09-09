#include "types.h"
extern u16 lbl_801A6CC4;

s32 fn_8003401C(u16);                           /* extern */

u16 fn_8006FFDC(void) {
    u16 temp_r31;

    temp_r31 = *(u16 *)((u8 *)(&lbl_801A6CC4) + 0);
    fn_8003401C(*(u16 *)((u8 *)(&lbl_801A6CC4) + 0));
    (*(u16 *)((u8 *)(&lbl_801A6CC4) + 0)) += 1;
    return temp_r31;
}
