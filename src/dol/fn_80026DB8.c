#include "types.h"

struct fn_80026DB8_Arg0 {
    u8 pad_0[0x18];
    u32 unk_18;
};

extern u32 lbl_80176160[];

u32 fn_80026DB8(struct fn_80026DB8_Arg0 *arg0) {
    return *(u32 *)((u8 *)&lbl_80176160 + (arg0->unk_18 * 96) + 8);
}
