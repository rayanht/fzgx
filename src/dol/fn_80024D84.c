#include "types.h"

struct fn_80024D84_Arg0 {
    u8 pad_0[0x13C];
    u8 unk_13C;
    f32 unk_140;
    f32 unk_144;
    f32 unk_148;
    f32 unk_14C;
    f32 unk_150;
};

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern u32 fn_800244C8(u32, f32, f32, f32, f32, f32);

#pragma peephole off
u32 fn_80024D84(struct fn_80024D84_Arg0 *arg0) {
    u32 v0;
    u32 t0;

    t0 = OSDisableInterrupts();
    arg0->unk_13C = 0;
    v0 = fn_800244C8((u32)arg0, arg0->unk_140, arg0->unk_148, arg0->unk_144, arg0->unk_14C, arg0->unk_150);
    OSRestoreInterrupts(t0);
    return v0;
}
