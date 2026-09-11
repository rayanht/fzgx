#include "types.h"

extern void *memset(void *dest, int value, u32 size);
extern s32 fn_80089244(void *arg0, void *arg1);
extern void *TRKAppendBuffer_ui8(void *buffer, const void *data, u32 length);
extern s32 fn_8008AB20(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void *TRKGetBuffer(u32 handle);
extern void fn_800891B4(void *arg0);

struct fn_8008A91C_buffer {
    u32 unk_0;
    u8 unk_4;
    u8 unk_5[3];
    void *unk_8;
    u8 unk_c[0x34];
};

s32 fn_8008A91C(void *arg0, u32 *arg1) {
    u32 unk_10;
    u32 unk_c;
    u32 unk_8;
    struct fn_8008A91C_buffer buffer;
    s32 result;
    void *buffer_ptr;

    memset(&buffer, 0, 0x40);
    buffer.unk_4 = 0xd3;
    buffer.unk_0 = 0x40;
    buffer.unk_8 = arg0;
    result = fn_80089244(&unk_c, &unk_8);
    if (!result) {
        result = (s32)TRKAppendBuffer_ui8((void *)unk_8, &buffer, 0x40);
    }
    if (!result) {
        *arg1 = 0;
        result = fn_8008AB20((void *)unk_8, &unk_10, 3, 3, 0);
        if (!result) {
            buffer_ptr = (void *)TRKGetBuffer(unk_10);
        }
        if (!result) {
            *arg1 = *(u32 *)((u8 *)buffer_ptr + 0x20);
        }
        fn_800891B4((void *)unk_10);
    }
    fn_800891B4((void *)unk_c);
    return result;
}
