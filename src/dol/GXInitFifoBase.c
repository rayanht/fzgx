#include "types.h"

struct GXInitFifoBase_Arg0 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0x10];
    u32 unk_1C;
};

extern void fn_80031D60(struct GXInitFifoBase_Arg0 *, u32, u32);
extern void GXInitFifoPtrs(struct GXInitFifoBase_Arg0 *, u32, u32);

void GXInitFifoBase(struct GXInitFifoBase_Arg0 *arg0, u32 arg1, u32 arg2) {
    u32 v0;
    u32 lab_t1;

    v0 = arg2 - 4;
    v0 = arg1 + v0;
    arg0->unk_0 = arg1;
    arg0->unk_4 = v0;
    arg0->unk_8 = arg2;
    arg0->unk_1C = 0;
    lab_t1 = arg2 - 0x4000;
    fn_80031D60(arg0, lab_t1, __rlwinm(arg2, 31, 1, 26));
    GXInitFifoPtrs(arg0, arg1, arg1);
}
