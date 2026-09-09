#include "types.h"

extern u32 lbl_801A50B0[];

extern void *memset(void *, int, u32);
extern void fn_8008D398(void *, u32);

struct fn_8008A6E4_local {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

s32 fn_8008A6E4(void) {
    struct fn_8008A6E4_local local;
    u32 size = 0x40;

    lbl_801A50B0[0] = 1;
    memset(&local, 0, size);
    local.unk_4 = 0x80;
    local.unk_0 = size;
    local.unk_8 = 0;
    fn_8008D398(&local, size);
    return 0;
}
