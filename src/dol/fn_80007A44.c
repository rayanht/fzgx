#include "types.h"

extern u32 fn_800744F8(void *, u32);
extern u32 fn_80008204(void *);
extern u32 lbl_801A6408;
extern u32 lbl_801A6F00;
extern u32 lbl_801A6728;

void fn_80007A44(void) {
    u32 loc_8[2];

    loc_8[1] = lbl_801A6F00;
    ((u8 *)&lbl_801A6408)[0] = ((u8 *)&loc_8[1])[0];
    ((u8 *)&lbl_801A6408)[1] = ((u8 *)&loc_8[1])[1];
    ((u8 *)&lbl_801A6408)[2] = ((u8 *)&loc_8[1])[2];
    ((u8 *)&lbl_801A6408)[3] = ((u8 *)&loc_8[1])[3];
    loc_8[0] = lbl_801A6408;
    fn_800744F8(loc_8, 0x00ffffff);
    fn_80008204(&lbl_801A6408);
    lbl_801A6728 = 0;
}
