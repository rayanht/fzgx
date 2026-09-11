#include "types.h"

struct GXSetMisc_gx_T {
    u16 unk_0;
    u16 unk_2;
    u16 unk_4;
    u8 pad_6[0x4EB];
    u8 unk_4F1;
    u8 unk_4F2;
    u8 pad_4F3[0x1];
    u32 unk_4F4;
};

extern struct GXSetMisc_gx_T *gx;

void GXSetMisc(u32 arg0, u32 arg1) {
    struct GXSetMisc_gx_T *p;

    switch ((s32)arg0) {
    case 0:
        break;
    case 1:
        p = gx;
        p->unk_4 = arg1;
        p->unk_0 = (__cntlzw(p->unk_4) >> 5) & 0xFFFF;
        p->unk_2 = 1;
        if (p->unk_4 != 0) {
            p->unk_4F4 |= 8;
        }
        break;
    case 2:
        gx->unk_4F1 = (arg1 != 0);
        break;
    case 3:
        gx->unk_4F2 = (arg1 != 0);
        break;
    }
}
