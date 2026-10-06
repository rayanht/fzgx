#include "types.h"
#include "sdk_addresses.h"

typedef struct Fn80005B10_Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Fn80005B10_Color;

typedef f32 Fn80005B10_Mtx44[4][4];

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8 s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

// Hardware or OS state can change asynchronously.
volatile PPCWGPipe
    GXFIFO : FZGX_ADDR_GXFIFO; // fzgx-allow: S2 SDK asynchronous state

extern void *lbl_801A6D00;
extern const Fn80005B10_Color lbl_801A7908; /* zero fog colour (.sbss2) */
extern void fn_800723F8(void);
extern void fn_8007245C(s32);
extern void fn_80074788(s32);
extern void fn_80074660(s32);
extern void fn_80073678(s32);
extern void fn_80073898(s32);
extern void fn_80073C6C(s32);
extern void fn_80072EDC(s32, s32);
extern void fn_800745A4(s32, s32, s32, s32, s32, s32);
extern void fn_800734A8(s32, s32, s32, s32);
extern void fn_80072AB0(s32, s32, s32);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern void fn_80072D64(s32, s32, s32, s32, s32, s32);
extern void fn_80072CC4(s32, s32, s32, s32, s32);
extern void fn_80072E20(s32, s32, s32, s32, s32, s32);
extern void fn_800747D0(s32, s32, s32, s32, s32, s32, s32);
extern void fn_800371F8(s32, Fn80005B10_Color);
extern void fn_80074918(s32, s32, s32);
extern void fn_800728A8(s32, s32, s32, s32);
extern void fn_800377F8(s32, f32, f32, f32, f32, Fn80005B10_Color);
extern void fn_80072864(s32);
extern void lbl_8006D758(void);
extern void GXLoadPosMtxImm(void *, s32);
extern void fn_80015EE8(Fn80005B10_Mtx44, f32, f32, f32, f32, f32, f32);
extern void fn_800737E4(Fn80005B10_Mtx44, s32);
extern void fn_80073778(void *, s32);
extern void fn_8003462C(s32, s32, s32);

static inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}

static inline void GXTexCoord2f32(f32 s, f32 t) {
    GXFIFO.f32 = s;
    GXFIFO.f32 = t;
}

void fn_80005B10(void *texture) {
    Fn80005B10_Color color = {0x00, 0xFF, 0x00, 0xFF};
    Fn80005B10_Mtx44 projection;
    f32 x;
    f32 y;

    fn_800723F8();
    fn_8007245C(0x2200);
    fn_800723F8();
    fn_80074788(0);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(0);
    fn_80073C6C(0);
    fn_80072EDC(0, 0);
    fn_800745A4(0, 1, 4, 0x3C, 0, 0x7D);
    fn_800734A8(0, 0, 0, 0xFF);
    fn_80072AB0(0, 0, 0);
    fn_80072C24(0, 0xF, 2, 8, 4);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 1, 4, 2);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_800747D0(4, 0, 0, 0, 0, 2, 2);
    fn_800371F8(1, color);
    fn_80074918(1, 1, 1);
    fn_800728A8(1, 4, 5, 0);
    fn_800377F8(0, 0.0f, 100.0f, 0.0f, 100.0f, lbl_801A7908);
    fn_80072864(2);
    lbl_8006D758();
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    fn_80015EE8(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 20000.0f);
    fn_800737E4(projection, 1);
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = 0xFF;
    fn_800371F8(1, color);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
    fn_800371F8(2, color);
    fn_80073778(texture, 0);

    fn_8003462C(0x80, 7, 4);
    x = 320.0f;
    y = 240.0f;
    GXPosition3f32(x - 320.0, y - 240.0, -0.5f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + 320.0, y - 240.0, -0.5f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(x + 320.0, y + 240.0, -0.5f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(x - 320.0, y + 240.0, -0.5f);
    GXTexCoord2f32(0.0f, 1.0f);
}
