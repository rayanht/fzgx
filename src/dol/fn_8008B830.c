#include "types.h"

struct fn_8008B830_TRKExceptionStatus {
    u32 unk_0;
    u8 pad_4[4];
    u16 unk_8;
};

struct fn_8008B830_buffer {
    u32 unk_0;
    u32 unk_4;
    u8 unk_8;
    u8 pad_9[3];
    u32 unk_c;
    u32 unk_10;
    u32 unk_14;
    u8 pad_20[0x24];
    u8 pad_44[0x10];
};

extern u32 gTRKExceptionStatus[4];
extern void *memset(void *, s32, u32);
extern s32 fn_8008C6E4(struct fn_8008B830_header *, u32);
extern void TRKAppendBuffer_ui8(u32, void *, u32);

struct fn_8008B830_header {
    u32 unk_0;
};

struct fn_8008B830_packet {
    u32 length;
    u8 type;
    u8 pad_5[3];
    u32 status;
    u32 header;
    u32 exception;
    u8 rest[0x2c];
};

void fn_8008B830(u32 arg0) {
    struct fn_8008B830_header header;
    struct fn_8008B830_packet data;
    u32 status;
    u32 saved_arg;

    saved_arg = arg0;
    memset(&data, 0, 0x40);
    data.length = 0x40;
    data.type = 0x91;
    status = gTRKExceptionStatus[0];
    data.status = status;
    fn_8008C6E4(&header, status);
    data.header = header.unk_0;
    data.exception = *(u16 *)((u8 *)gTRKExceptionStatus + 8);
    TRKAppendBuffer_ui8(saved_arg, &data, 0x40);
}
