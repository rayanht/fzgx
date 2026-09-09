#include "types.h"

extern u32 lbl_801A6D7C;
extern u32 lbl_801A6D84;

void fn_80074C74(u8 *arg0) {
    if (arg0[0] || arg0[1] || arg0[2] || arg0[3]) {
        lbl_801A6D84 = 1;
        ((u8 *)&lbl_801A6D7C)[0] = arg0[0];
        ((u8 *)&lbl_801A6D7C)[1] = arg0[1];
        ((u8 *)&lbl_801A6D7C)[2] = arg0[2];
        ((u8 *)&lbl_801A6D7C)[3] = arg0[3];
    } else {
        lbl_801A6D84 = 0;
        ((u8 *)&lbl_801A6D7C)[0] = 0;
        ((u8 *)&lbl_801A6D7C)[1] = 0;
        ((u8 *)&lbl_801A6D7C)[2] = 0;
        ((u8 *)&lbl_801A6D7C)[3] = 0;
    }
}
