#include "types.h"

struct fn_12_13D0_Arg1 {
    u8 pad_0[0x48];
    u32 unk_48;
};

extern u32 fn_12_132C(u32, u32, u32);
extern u32 fn_12_68C(u32, u32);
extern u32 fn_12_6B8(u32, u32);
extern void fn_12_8B4(void *, void *, void *);

void fn_12_13D0(u32 arg0, struct fn_12_13D0_Arg1 *arg1, u32 arg2) {
    u32 v0;
    u32 v1;
    s32 v2;
    u32 loc_C[1];
    u32 loc_8[1];

    v0 = arg1->unk_48;
    fn_12_8B4((void *)arg0, (void *)&loc_C, (void *)loc_8);
    v1 = *(u32 *)((u8 *)(u32)arg1 + 72);
    v2 = ((s32)(((u32)v0 >> 31) + v0) >> 1);
    *(u32 *)((u8 *)(u32)arg1 + 72) = ((s32)(((u32)v1 >> 31) + v1) >> 1);
    fn_12_68C((u32)arg1, v2);
    fn_12_132C(arg0, (u32)arg1, arg2);
    fn_12_68C((u32)arg1, v0);
    fn_12_6B8((u32)arg1, v2);
    fn_12_132C(arg0, (u32)arg1, (arg2 + (loc_C[0] << 1)));
}
