#include "types.h"

struct fn_8008998C_Buffer {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

struct fn_8008998C_Message {
    u8 pad_0[0x18];
    u8 options;
    u8 pad_19[3];
    u8 count;
    u8 pad_1D[3];
    u32 range_start;
    u32 range_end;
};

extern s32 fn_80089144(struct fn_8008998C_Message *msg, u32 position);
extern void *memset(void *, s32, u32);
extern u32 fn_8008D398(void *data, u32 size);
extern u32 fn_8008B6BC(void);
extern s32 TRKTargetStopped(void);
extern s32 fn_8008B784(u8 count, s32 over);
extern s32 fn_8008B6CC(u32 range_start, u32 range_end, s32 over);

static inline void fn_8008998C_reply(u8 error) {
    struct fn_8008998C_Buffer buffer;

    memset(&buffer, 0, 0x40);
    buffer.unk_4 = 0x80;
    buffer.unk_0 = 0x40;
    buffer.unk_8 = error;
    fn_8008D398(&buffer, 0x40);
}

s32 fn_8008998C(struct fn_8008998C_Message *msg) {
    s32 result;
    u8 options;
    u8 count;
    u32 range_start;
    u32 range_end;
    u32 pc;

    fn_80089144(msg, 0);
    options = msg->options;
    range_start = msg->range_start;
    range_end = msg->range_end;

    switch (options) {
    case 0:
    case 0x10:
        count = msg->count;
        if (count < 1) {
            fn_8008998C_reply(0x11);
            return 0;
        }
        break;
    case 1:
    case 0x11:
        pc = fn_8008B6BC();
        if (pc < range_start || pc > range_end) {
            fn_8008998C_reply(0x11);
            return 0;
        }
        break;
    default:
        fn_8008998C_reply(0x12);
        return 0;
    }

    if (!TRKTargetStopped()) {
        fn_8008998C_reply(0x16);
        return 0;
    }

    fn_8008998C_reply(0);
    result = 0;
    switch (options) {
    case 0:
    case 0x10:
        result = fn_8008B784(count, options == 0x10);
        break;
    case 1:
    case 0x11:
        result = fn_8008B6CC(range_start, range_end, options == 0x11);
        break;
    }
    return result;
}
