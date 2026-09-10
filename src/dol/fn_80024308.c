#include "types.h"

struct fn_80024308_Arg0 {
    u8 pad_0[0x1C4];
    u8 unk_1C4;
    f32 unk_1C8;
    f32 unk_1CC;
    f32 unk_1D0;
    f32 unk_1D4;
    f32 unk_1D8;
    f32 unk_1DC;
};

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern u32 fn_80023684(struct fn_80024308_Arg0 *, f32, f32, f32, f32, f32, f32);

#pragma peephole off
u32 fn_80024308(struct fn_80024308_Arg0 *arg0) {
    u32 v1;
    u32 v0;

    v0 = OSDisableInterrupts();
    arg0->unk_1C4 = 0;
    v1 = fn_80023684(arg0, arg0->unk_1C8, arg0->unk_1D0, arg0->unk_1CC, arg0->unk_1D4, arg0->unk_1D8, arg0->unk_1DC);
    OSRestoreInterrupts(v0);
    return v1;
}
#pragma peephole reset
