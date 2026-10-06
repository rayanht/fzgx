#include "types.h"

typedef struct Fn80076238_Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Fn80076238_Color;

typedef struct Fn80076238_Ctx {
    s32 stage;
    s32 coord;
    s32 unk_8;
    s32 map;
} Fn80076238_Ctx;

typedef struct Fn80076238_Params {
    u8 pad_0[0x8];
    s32 color_in;
    s32 alpha_in;
} Fn80076238_Params;

typedef struct Fn80076238_State {
    u8 pad_0[0x3C];
    s32 base_mtx_ready;
    s32 env_mtx_ready;
    u8 pad_44[0xC];
    u8 unk_50[0x10];
} Fn80076238_State;

extern Fn80076238_State lbl_801A3220;
extern u8 lbl_8015AD1C[12];
extern f32 (*lbl_801A6D00)[4];
extern void fn_80073C6C(s32);
extern void fn_80072AB0(s32, s32, s32);
extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);
extern void GXLoadTexMtxImm(f32 (*)[4], s32, s32);
extern void fn_8006F120(void *, void *);
extern void lbl_8006E14C(f32);
extern void fn_800734A8(s32, s32, s32, s32);
extern void fn_800736C0(s32, Fn80076238_Color);
extern void fn_800735C8(s32, s32);
extern void fn_800745A4(s32, s32, s32, s32, s32, s32);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern void fn_80072D64(s32, s32, s32, s32, s32, s32);
extern void fn_80072CC4(s32, s32, s32, s32, s32);
extern void fn_80072E20(s32, s32, s32, s32, s32, s32);

void fn_80076238(Fn80076238_Ctx *ctx, Fn80076238_Params *params, u8 alpha, s32 add) {
    Fn80076238_Color color;

    fn_80073C6C(ctx->stage);
    fn_80072AB0(ctx->stage, 0, 0);
    if (lbl_801A3220.base_mtx_ready == 0) {
        lbl_8006DAEC();
        lbl_801A6D00[0][3] = 0.0f;
        lbl_801A6D00[1][3] = 0.0f;
        lbl_801A6D00[2][3] = 0.0f;
        GXLoadTexMtxImm(lbl_801A6D00, 30, 0);
        lbl_8006DB30();
        lbl_801A3220.base_mtx_ready = 1;
    }
    if (lbl_801A3220.env_mtx_ready == 0) {
        lbl_8006DAEC();
        fn_8006F120(lbl_8015AD1C, lbl_801A3220.unk_50);
        lbl_801A6D00[0][3] = 0.5f;
        lbl_801A6D00[1][0] *= -1.0f;
        lbl_801A6D00[1][1] *= -1.0f;
        lbl_801A6D00[1][2] *= -1.0f;
        lbl_801A6D00[1][3] = 0.5f;
        lbl_801A6D00[2][0] = 0.0f;
        lbl_801A6D00[2][1] = 0.0f;
        lbl_801A6D00[2][2] = 0.0f;
        lbl_801A6D00[2][3] = 1.0f;
        lbl_8006E14C(0.5f);
        GXLoadTexMtxImm(lbl_801A6D00, 0x40, 0);
        lbl_8006DB30();
        lbl_801A3220.env_mtx_ready = 1;
    }
    color.r = alpha;
    color.g = alpha;
    color.b = alpha;
    color.a = alpha;
    fn_800734A8(ctx->stage, ctx->coord, ctx->map, 4);
    fn_800736C0(0, color);
    fn_800735C8(ctx->stage, 12);
    fn_800745A4(ctx->coord, 0, 1, 30, 1, 0x40);
    if (add) {
        fn_80072C24(ctx->stage, 15, 8, params->color_in, 15);
    } else {
        fn_80072C24(ctx->stage, 15, 8, 14, params->color_in);
    }
    fn_80072D64(ctx->stage, 0, 0, 0, 1, 0);
    fn_80072CC4(ctx->stage, 7, 7, 7, params->alpha_in);
    fn_80072E20(ctx->stage, 0, 0, 0, 1, 0);
    ctx->stage++;
    ctx->coord++;
}
