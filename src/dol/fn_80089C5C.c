#include "types.h"

struct fn_80089C5C_Buffer {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

typedef struct fn_80089C5C_Msg {
    u8 pad_0[0x18];
    u8 options;
    u8 pad_19[0x3];
    u16 first;
    u8 pad_1E[0x2];
    u16 last;
} fn_80089C5C_Msg;

extern u8 lbl_800958F0[31];
extern u8 lbl_80095910[348];
extern u32 MWTRACE(u32, ...);
extern void *memset(void *, s32, u32);
extern void fn_8008D398(void *data, u32 size);
extern s32 fn_80089144(fn_80089C5C_Msg *msg, u32 pos);
extern u32 fn_80089174(fn_80089C5C_Msg *msg, u32 pos);
extern s32 TRKTargetAccessDefault(u32 first, u32 last, fn_80089C5C_Msg *msg, u32 *size, BOOL read);
extern s32 fn_8008C124(u32 first, u32 last, fn_80089C5C_Msg *msg, u32 *size, BOOL read);
extern s32 fn_8008BFB4(u32 first, u32 last, fn_80089C5C_Msg *msg, u32 *size, BOOL read);
extern s32 fn_8008BB7C(u32 first, u32 last, fn_80089C5C_Msg *msg, u32 *size, BOOL read);
extern s32 TRKAppendBuffer(fn_80089C5C_Msg *msg, const void *data, u32 size);
extern s32 fn_80088B00(fn_80089C5C_Msg *msg);

s32 fn_80089C5C(fn_80089C5C_Msg *msg) {
    struct fn_80089C5C_Buffer ack;
    struct fn_80089C5C_Buffer nak;
    struct fn_80089C5C_Buffer reply;
    u32 size;
    s32 error;
    u8 options;
    u16 first;
    u16 last;

    options = msg->options;
    first = msg->first;
    last = msg->last;
    fn_80089144(msg, 0);
    if (first > last) {
        memset(&nak, 0, 0x40);
        nak.unk_4 = 0x80;
        nak.unk_0 = 0x40;
        nak.unk_8 = 0x14;
        fn_8008D398(&nak, 0x40);
        return 0;
    }

    fn_80089144(msg, 0x40);
    switch (options) {
    case 0:
        error = TRKTargetAccessDefault(first, last, msg, &size, FALSE);
        break;
    case 1:
        error = fn_8008C124(first, last, msg, &size, FALSE);
        break;
    case 2:
        error = fn_8008BFB4(first, last, msg, &size, FALSE);
        break;
    case 3:
        error = fn_8008BB7C(first, last, msg, &size, FALSE);
        break;
    default:
        error = 0x703;
        break;
    }

    fn_80089174(msg, 0);
    if (error == 0) {
        memset(&ack, 0, 0x40);
        ack.unk_0 = 0x40;
        ack.unk_4 = 0x80;
        ack.unk_8 = error;
        error = TRKAppendBuffer(msg, &ack, 0x40);
    }

    if (error != 0) {
        switch (error) {
        case 0x703:
            error = 0x12;
            break;
        case 0x701:
            error = 0x14;
            break;
        case 0x302:
            error = 2;
            break;
        case 0x702:
            error = 0x15;
            break;
        case 0x704:
            error = 0x21;
            break;
        case 0x705:
            error = 0x22;
            break;
        case 0x706:
            error = 0x20;
            break;
        default:
            error = 3;
            break;
        }
        memset(&reply, 0, 0x40);
        reply.unk_4 = 0x80;
        reply.unk_0 = 0x40;
        reply.unk_8 = error;
        fn_8008D398(&reply, 0x40);
        return 0;
    }

    MWTRACE(1, lbl_800958F0);
    error = fn_80088B00(msg);
    MWTRACE(1, lbl_80095910, error);
    return error;
}
