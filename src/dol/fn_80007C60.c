#include "types.h"

extern u32 fn_800744F8(void *, u32);
extern s32 lbl_801A6728;
extern u32 lbl_801A6F08;
extern u32 lbl_801A6408;

void fn_80007C60(s32 arg0) {
    u32 loc_8[2];

    if (arg0 || !lbl_801A6728) {
        loc_8[1] = lbl_801A6F08;
        ((u8 *)&lbl_801A6408)[0] = ((u8 *)&loc_8[1])[0];
        ((u8 *)&lbl_801A6408)[1] = ((u8 *)&loc_8[1])[1];
        ((u8 *)&lbl_801A6408)[2] = ((u8 *)&loc_8[1])[2];
        ((u8 *)&lbl_801A6408)[3] = ((u8 *)&loc_8[1])[3];
        loc_8[0] = lbl_801A6408;
        fn_800744F8(loc_8, (0x1000000 - 1));
    }
    lbl_801A6728 = 0;
}
