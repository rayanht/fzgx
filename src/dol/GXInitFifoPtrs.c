#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);

struct GXInitFifoPtrs_Arg0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x8];
    u32 unk_14;
    u32 unk_18;
    s32 unk_1C;
};

void GXInitFifoPtrs(struct GXInitFifoPtrs_Arg0 *arg0, u32 arg1, u32 arg2) {
    u32 state;

    state = OSDisableInterrupts();
    arg0->unk_14 = arg1;
    arg0->unk_18 = arg2;
    arg0->unk_1C = arg2 - arg1;
    if (arg0->unk_1C < 0) {
        arg0->unk_1C += arg0->unk_8;
    }
    OSRestoreInterrupts(state);
}
