#include "types.h"

struct fn_80043FA4_Arg0 {
    u8 pad_0[0x9A];
    s16 unk_9A;
};

extern u32 ADXB_ExecOneAuUlaw(u32);
extern u32 fn_800443AC(u32);
extern u32 fn_800446E4(u32);

void fn_80043FA4(struct fn_80043FA4_Arg0 *arg0) {
    if (arg0->unk_9A == 2) {
    ADXB_ExecOneAuUlaw((u32)arg0);
    } else {
    if (arg0->unk_9A == 1) {
    fn_800443AC((u32)arg0);
    } else {
    fn_800446E4((u32)arg0);
    }
    }
}
