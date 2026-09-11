#include "types.h"

typedef struct GXContext {
    u8 pad_0[0x2];
    u16 field_2;
} GXContext;

extern GXContext* gx;

// The write-gather pipe is a memory-mapped hardware register.
#define GX_FIFO_U8 (*(volatile u8 *)0xCC008000u) // fzgx-allow: A2 hardware register
#define GX_FIFO_U32 (*(volatile u32 *)0xCC008000u) // fzgx-allow: A2 hardware register

void fn_80035960(s32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, s32 arg6) {
    u32 idx = arg0 & 3;
    u32 b1;
    u32 b2;
    u32 v;

    v = ((arg1 & 0xFF) << 1) | arg3;
    v = (v & 0xFFFFFFBF) | (arg2 << 6);
    if (arg6 == 0) {
        arg5 = 0;
    }
    b1 = (arg6 != 2);
    b2 = (arg6 != 0);
    v = (v & 0xFFFFFE7F) | (arg5 << 7);
    v = (v & 0xFFFFFDFF) | (b1 << 9);
    v = (v & 0xFFFFFBFF) | (b2 << 10);
    v = (v & 0xFFFFFFC3) | ((arg4 << 2) & 0x3C);
    v = (v & 0xFFFF87FF) | ((arg4 << 7) & 0x7800);
    GX_FIFO_U8 = 0x10;
    GX_FIFO_U32 = idx + 0x100E;
    GX_FIFO_U32 = v;
    if (arg0 == 4) {
        GX_FIFO_U8 = 0x10;
        GX_FIFO_U32 = 0x1010;
        GX_FIFO_U32 = v;
    } else if (arg0 == 5) {
        GX_FIFO_U8 = 0x10;
        GX_FIFO_U32 = 0x1011;
        GX_FIFO_U32 = v;
    }
    gx->field_2 = 1;
}
