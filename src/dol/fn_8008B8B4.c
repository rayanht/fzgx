#include "types.h"

struct fn_8008B8B4_packet {
    u32 length;
    u8 type;
    u8 pad_5[3];
    u32 state;
    u32 header;
    u32 cpu;
    u8 rest[0x30];
};

extern u8 gTRKCPUState[1072];
extern void *memset(void *, s32, u32);
extern s32 fn_8008C6E4(void *, u32);
extern void TRKAppendBuffer_ui8(u32, void *, u32);

void fn_8008B8B4(u32 arg0) {
    struct fn_8008B8B4_packet data;
    u32 header;

    memset(&data, 0, 0x40);
    data.length = 0x40;
    data.type = 0x90;
    data.state = *(u32 *)(gTRKCPUState + 0x80);
    fn_8008C6E4(&header, *(u32 *)(gTRKCPUState + 0x80));
    data.header = header;
    data.cpu = *(u32 *)(gTRKCPUState + 0x2f8) & 0xffff;
    TRKAppendBuffer_ui8(arg0, &data, 0x40);
}
