#include "types.h"

typedef void (*fn_80055580_Fn0)(u32);

extern u32 lbl_80187430[];
extern u32 lbl_80187434[];

void fn_80055580(void) {
    if (lbl_80187430[0] != 0) {
        ((fn_80055580_Fn0)lbl_80187430[0])(lbl_80187434[0]);
    }
}
