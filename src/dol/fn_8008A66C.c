#include "types.h"

extern u32 lbl_801A50B0[];
extern void *memset(void *dest, int value, u32 size);
extern void fn_8008D398(void *data, u32 size);
extern void fn_80088764(void *value, s32 arg);
extern void TRKPostEvent(void *value);

struct fn_8008A66C_Data {
    u32 size;
    u8 type;
    u8 padding0[3];
    u8 flag;
    u8 padding1[0x3b];
};

s32 fn_8008A66C(void) {
    struct fn_8008A66C_Data data;
    u32 value[3];

    lbl_801A50B0[0] = 0;
    memset(&data, 0, 0x40);
    data.type = 0x80;
    data.size = 0x40;
    data.flag = 0;
    fn_8008D398(&data, 0x40);
    fn_80088764(value, 1);
    TRKPostEvent(value);
    return 0;
}
