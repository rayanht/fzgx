#include "types.h"

typedef struct Fn12_2BE3C_Stream Fn12_2BE3C_Stream;

typedef struct Fn12_2BE3C_StreamVtbl {
    u8 pad_0[0x24];
    s32 (*getNumData)(Fn12_2BE3C_Stream *stream, s32 channel);
} Fn12_2BE3C_StreamVtbl;

struct Fn12_2BE3C_Stream {
    Fn12_2BE3C_StreamVtbl *vtbl;
};

typedef struct Fn12_2BE3C_Buffer {
    u8 pad_0[0x4];
    Fn12_2BE3C_Stream *stream;
    u8 pad_8[0x4];
    s32 size;
    u8 pad_10[0x64];
} Fn12_2BE3C_Buffer;

typedef struct Fn12_2BE3C_Ply {
    u8 pad_0[0x48];
    s32 stat;
    u8 pad_4C[0x4];
    s32 error;
    u8 pad_54[0x918];
    s32 unk_96C;
    u8 pad_970[0x590];
    s32 time;
    s32 time_unit;
    u8 pad_F08[0x248];
    Fn12_2BE3C_Buffer buffers[21];
    u8 pad_1AD4[0x64];
    s32 cur;
} Fn12_2BE3C_Ply;

extern s32 fn_12_2D73C(Fn12_2BE3C_Ply *ply, s32 param);
extern s32 fn_12_2F1D0(Fn12_2BE3C_Ply *ply, s32 index);
extern s32 fn_12_21D30(Fn12_2BE3C_Ply *ply, s32 index);
extern s32 fn_12_21C00(Fn12_2BE3C_Ply *ply, s32 index);
extern s32 fn_12_2F1B4(Fn12_2BE3C_Ply *ply, s32 index);
extern void fn_12_2E714(Fn12_2BE3C_Ply *ply, s32 *a, s32 *b);
extern s32 UTY_MulDiv(s32 a, s32 b, s32 c);
extern s32 fn_12_2E42C(s32, s32, s32, s32);

static inline BOOL fn_12_2BE3C_isBusy(Fn12_2BE3C_Ply *ply) {
    s32 i;

    if (fn_12_2D73C(ply, 5) && fn_12_2F1D0(ply, 6)) {
        return TRUE;
    }
    if (fn_12_2D73C(ply, 6) && fn_12_2F1D0(ply, 7)) {
        return TRUE;
    }
    for (i = 0; i < 8; i++) {
        if (fn_12_21D30(ply, i)) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline BOOL fn_12_2BE3C_isFull(Fn12_2BE3C_Ply *ply) {
    Fn12_2BE3C_Buffer *buffer;
    s32 amount;

    buffer = &ply->buffers[ply->cur];
    amount = buffer->stream->vtbl->getNumData(buffer->stream, 1);
    if (amount >= buffer->size * 80 / 100 || amount >= fn_12_2D73C(ply, 0x46)) {
        return TRUE;
    }
    return FALSE;
}

s32 fn_12_2BE3C(Fn12_2BE3C_Ply *ply) {
    s32 a;
    s32 b;
    s32 time;
    s32 unit;

    if (fn_12_2D73C(ply, 0x43) == 0) {
        return 0;
    }
    if (fn_12_2D73C(ply, 0xF) == 0) {
        return 0;
    }
    if (ply->error != 0) {
        return 0;
    }
    if (ply->stat != 4) {
        return 0;
    }
    if (fn_12_2BE3C_isBusy(ply)) {
        return 0;
    }
    if (fn_12_2D73C(ply, 5) == 1 && ply->unk_96C == 0) {
        return 0;
    }
    if (fn_12_2D73C(ply, 6) == 1 && fn_12_21C00(ply, 2) > 0) {
        return 0;
    }
    if (fn_12_2F1B4(ply, 1) && fn_12_21C00(ply, 0) > 0) {
        return 0;
    }
    if (fn_12_2D73C(ply, 5) == 1 && fn_12_2BE3C_isFull(ply)) {
        return 0;
    }
    fn_12_2E714(ply, &a, &b);
    time = ply->time;
    unit = ply->time_unit;
    time -= UTY_MulDiv(fn_12_2D73C(ply, 0x44), unit, 1000000);
    if (a <= 0 || time <= 0) {
        return 0;
    }
    return fn_12_2E42C(a, b, time, unit) == 0;
}
