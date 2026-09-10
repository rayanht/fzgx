#include "types.h"

struct fn_80025440_Arg0 {
    u8 pad_0[0x24];
    u8 unk_24;
    u8 pad_25[0x33];
    u32 unk_58;
    u32 unk_5c;
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u8 pad_6c[0x24];
    u32 unk_90;
    u32 unk_94;
    u32 unk_98;
};

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);

#pragma peephole off
u32 fn_80025440(struct fn_80025440_Arg0 *arg0) {
    u32 t0;

    t0 = OSDisableInterrupts();
    arg0->unk_5c = 0x140 - ((arg0->unk_90 - 5) * 32);
    arg0->unk_58 = 0;
    arg0->unk_5c = (arg0->unk_5c + ((arg0->unk_24 - 1) * 160)) % 480;
    arg0->unk_68 = (((arg0->unk_98 / 5) + 1) & ~1);
    arg0->unk_64 = arg0->unk_68 / 2;
    arg0->unk_60 = (arg0->unk_94 << 16) / (arg0->unk_68 * 5);
    OSRestoreInterrupts(t0);
    return 1;
}
#pragma peephole reset

