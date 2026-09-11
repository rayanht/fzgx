#include "types.h"

struct fn_8008A3C0_Arg0 {
    u8 pad_0[0x14];
    u8 unk_14;
    u8 pad_15[3];
    u8 unk_18;
    u8 pad_19[3];
    u16 unk_1c;
    u32 unk_20;
};

struct fn_8008A3C0_Buf {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

struct fn_8008A3C0_Msg {
    u8 a[2052];
};

typedef int Sig_TRKAppendBuffer_DSError;
typedef struct Sig_TRKAppendBuffer_TRKBuffer {
    u32 mutex;
    BOOL isInUse;
    u32 length;
    u32 position;
    u8 data[(0x800 + 0x80)];
} Sig_TRKAppendBuffer_TRKBuffer;

extern u8 lbl_80095890[52];
struct fn_8008A3C0_Rodata {
    u8 pad_0[0x1e0];
};
extern struct fn_8008A3C0_Rodata lbl_80095890_ro;
extern void MWTRACE(u32, ...);
extern void *memset(void *, s32, u32);
extern u32 fn_8008D398(u32, u32);
extern u32 fn_8008C730(u32, u32, u32 *, u32, u32);
extern u32 fn_80089174(u32, u32);
extern u32 fn_80088B00(u32);
extern Sig_TRKAppendBuffer_DSError TRKAppendBuffer(Sig_TRKAppendBuffer_TRKBuffer *, const void *, size_t);

#pragma opt_common_subs off
s32 fn_8008A3C0(struct fn_8008A3C0_Arg0 *arg0) {
    u8 *base;
    s32 v4 = 0;
    s32 code;
    u8 v2;
    u16 v1;
    u32 v0;
    struct fn_8008A3C0_Msg bufD;
    struct fn_8008A3C0_Buf bufB;
    struct fn_8008A3C0_Buf bufA;
    struct fn_8008A3C0_Buf bufC;
    u32 loc_8;

    base = lbl_80095890;
    v0 = arg0->unk_20;
    v1 = arg0->unk_1c;
    v2 = arg0->unk_18;
    MWTRACE(1, (u32)(base + 0x1b0), arg0->unk_14, v0, v1, v2);

    if ((v2 & 0x2) != 0) {        memset(&bufA, 0, 0x40);
        bufA.unk_4 = 0x80;
        bufA.unk_0 = 0x40;
        bufA.unk_8 = 0x12;
        fn_8008D398((u32)&bufA, 0x40);
        return 0;
    }

    loc_8 = v1;
    v4 = fn_8008C730((u32)&bufD, v0, &loc_8, ((((u32)v2) >> 3) & 1) ^ 1, 1);
    fn_80089174((u32)arg0, 0);

    if (v4 == 0) {
        memset(&bufB, 0, 0x40);
        bufB.unk_8 = v4;
        bufB.unk_0 = loc_8 + 0x40;
        bufB.unk_4 = 0x80;
        TRKAppendBuffer((Sig_TRKAppendBuffer_TRKBuffer *)arg0, &bufB, 0x40);
        v4 = TRKAppendBuffer((Sig_TRKAppendBuffer_TRKBuffer *)arg0, &bufD, loc_8);
    }

    if (v4 != 0) {
        switch (v4 - 0x700) {
        case 2:
            code = 0x15;
            break;
        case 0:
            code = 0x13;
            break;
        case 4:
            code = 0x21;
            break;
        case 5:
            code = 0x22;
            break;
        case 6:
            code = 0x20;
            break;
        default:
            code = 3;
            break;
        }
        memset(&bufC, 0, 0x40);
        bufC.unk_4 = 0x80;
        bufC.unk_0 = 0x40;
        bufC.unk_8 = code;
        fn_8008D398((u32)&bufC, 0x40);
        return 0;
    }

    MWTRACE(1, (u32)(base + 0x60));
    v4 = fn_80088B00((u32)arg0);
    MWTRACE(1, (u32)(base + 0x80), v4);
    return v4;
}
#pragma opt_common_subs reset

