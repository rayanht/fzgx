#include "types.h"

typedef u32 (*fn_80071718_Fn0)(u32);
struct fn_80071718_Arg0 {
    u8 pad_0[0xC];
    u32 unk_C;
};

extern u32 lbl_801A6D08;

void fn_80071718(struct fn_80071718_Arg0 *arg0) {
    if ((arg0->unk_C & 0x1) == 0) {
        ((fn_80071718_Fn0)lbl_801A6D08)((u32)arg0);
    }
}
