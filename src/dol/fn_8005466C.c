#include "types.h"

extern u32 lbl_80187430[];
extern u32 lbl_80187434[80];

void fn_8005466C(u32 arg0, u32 arg1) {
    if (arg0 == 0) {
        lbl_80187430[0] = 0;
        lbl_80187434[0] = 0;
    } else {
        lbl_80187430[0] = arg0;
        lbl_80187434[0] = arg1;
    }
}
