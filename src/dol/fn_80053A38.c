#include "types.h"

extern void *memset(void *dst, int value, u32 size);
extern u32 lbl_80187380[16];

struct fn_80053A38_Arg0 {
    u8 pad_0[1];
    s8 unk_1;
};

void fn_80053A38(struct fn_80053A38_Arg0 *arg0) {
    s32 index;
    index = arg0->unk_1;
    memset(arg0, 0, 0x2014);
    lbl_80187380[index] = 0;
}
