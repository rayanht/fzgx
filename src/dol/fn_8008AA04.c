#include "types.h"

extern void *memset(void *dst, s32 value, u32 size);
extern u32 strlen(const char *str);
extern void fn_80089244(u32 *arg0, u32 *arg1);
extern void *TRKAppendBuffer_ui8(void *arg0, void *arg1, u32 arg2);
extern u32 fn_8008AB20(void *arg0, u32 *arg1, u32 arg2, u32 arg3, u32 arg4);
extern void *TRKGetBuffer(u32 arg0);
extern void fn_800891B4(void *arg0);

struct Request {
    u32 length;
    u8 type;
    u8 unk_5[3];
    u8 arg;
    u8 unk_9[3];
    u16 string_length;
    u8 unk_E[0x32];
};

u32 fn_8008AA04(const char *name, u8 type, u32 *status, u32 *length, void *buffer) {
    u32 local_10;
    u32 local_c;
    u32 local_8;
    struct Request request;
    s32 result;
    void *buf;

    memset(&request, 0, 0x40);
    *status = 0;
    request.type = 0xd2;
    request.length = strlen(name) + 0x41;
    request.arg = type;
    request.string_length = strlen(name) + 1;
    fn_80089244(&local_c, &local_8);
    result = (u32)TRKAppendBuffer_ui8((void *)local_8, &request, 0x40);
    if (!result) {
        result = strlen(name);
        result = (u32)TRKAppendBuffer_ui8((void *)local_8, (void *)name, result + 1);
    }
    if (!result) {
        *length = 0;
        result = fn_8008AB20((void *)local_8, &local_10, 7, 3, 0);
        if (!result) {
            buf = (void *)TRKGetBuffer(local_10);
        }
        *length = *(u32 *)((u8 *)buf + 0x20);
        *status = *(u32 *)((u8 *)buf + 0x18);
        fn_800891B4((void *)local_10);
    }
    fn_800891B4((void *)local_c);
    return result;
}
