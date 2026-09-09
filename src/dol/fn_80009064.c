#include "types.h"

extern u32 fn_8000951C(u32);
extern u32 fn_800095A4(void);
extern u32 lbl_801A6744;

void fn_80009064(u32 arg0) {
    s32 v0;
    fn_8000951C(arg0);
    v0 = (arg0 * 12);
    *(u32 *)((u8 *)lbl_801A6744 + v0) = -1;
    fn_800095A4();
}
