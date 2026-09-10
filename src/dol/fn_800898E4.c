#include "types.h"

struct fn_800898E4_Buffer {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

extern s32 fn_8008B484(void);
extern void *memset(void *, s32, u32);
extern void fn_8008D398(void *data, u32 size);

s32 fn_800898E4(void) {
    struct fn_800898E4_Buffer buffer;
    s32 type;

    type = fn_8008B484();
    switch (type) {
    case 0:
        type = 0;
        break;
    case 0x704:
        type = 0x21;
        break;
    case 0x705:
        type = 0x22;
        break;
    case 0x706:
        type = 0x20;
        break;
    default:
        type = 1;
        break;
    }

    memset(&buffer, 0, 0x40);
    buffer.unk_4 = 0x80;
    buffer.unk_0 = 0x40;
    buffer.unk_8 = type;
    fn_8008D398(&buffer, 0x40);
    return 0;
}
