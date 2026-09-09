#include "types.h"

typedef void (*fn_800474E4_Fn0)(u32, u32);
struct fn_800474E4_lbl_8017B030 {
    u32 unk_0;
    u32 unk_4;
    u8 unk_8[32];
    u8 unk_28[256];
};

extern struct fn_800474E4_lbl_8017B030 lbl_8017B030[];
extern u32 fn_800595FC(u32, ...);
extern void strncpy(void *, void *, int);

void fn_800474E4(u32 arg0) {
    struct fn_800474E4_lbl_8017B030 *p_lbl_8017B030;
    p_lbl_8017B030 = (struct fn_800474E4_lbl_8017B030 *)&lbl_8017B030;
    strncpy(p_lbl_8017B030->unk_28, (void *)arg0, 255);
    if (p_lbl_8017B030->unk_0 != 0) {
        ((fn_800474E4_Fn0)p_lbl_8017B030->unk_0)(
            p_lbl_8017B030->unk_4,
            (u32)&p_lbl_8017B030->unk_28[0]);
    }
    fn_800595FC((u32)((u8 *)p_lbl_8017B030 + 40));
}
