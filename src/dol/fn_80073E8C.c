#include "types.h"

typedef struct Fn80073E8C_IndMtx {
    f32 mtx[2][3];
    s8 scale_exp;
    u8 pad_19[0x3];
} Fn80073E8C_IndMtx;

typedef struct Fn80073E8C_TevInd {
    s32 ind_stage;
    s32 format;
    s32 bias_sel;
    s32 matrix_sel;
    s32 wrap_s;
    s32 wrap_t;
    u8 add_prev;
    u8 utc_lod;
    u8 pad_1A[0x2];
    s32 alpha_sel;
} Fn80073E8C_TevInd;

typedef struct Fn80073E8C_Cache {
    u8 pad_0[0x894];
    Fn80073E8C_IndMtx ind_mtx[3];
    Fn80073E8C_TevInd tev_ind[16];
} Fn80073E8C_Cache;

extern Fn80073E8C_Cache *lbl_801A6D38;
extern s32 fn_8008023C(const void *, const void *, u32);
extern void fn_80036AC4(s32 mtx_id, f32 offset[2][3], s8 scale_exp);
extern void *fn_800794F0(void *, const void *, u32);
extern void GXSetTevIndirect(s32 tev_stage, s32 ind_stage, s32 format, s32 bias_sel, s32 matrix_sel, s32 wrap_s,
                             s32 wrap_t, BOOL add_prev, BOOL utc_lod, s32 alpha_sel);


void fn_80073E8C(s32 tev_stage, s32 ind_stage, u16 wrap_s, u16 wrap_t, u16 scale_s, u16 scale_t, s32 format,
                 s32 matrix_sel, s32 bias_sel, s32 alpha_sel) {
    f32 mtx[2][3];
    Fn80073E8C_IndMtx *ind;
    Fn80073E8C_TevInd *tev;
    s32 ws;
    s32 wt;

    switch (wrap_s) {
    case 0x100:
        ws = 1;
        break;
    case 0x80:
        ws = 2;
        break;
    case 0x40:
        ws = 3;
        break;
    case 0x20:
        ws = 4;
        break;
    case 0x10:
        ws = 5;
        break;
    default:
        ws = 0;
        break;
    }
    switch (wrap_t) {
    case 0x100:
        wt = 1;
        break;
    case 0x80:
        wt = 2;
        break;
    case 0x40:
        wt = 3;
        break;
    case 0x20:
        wt = 4;
        break;
    case 0x10:
        wt = 5;
        break;
    default:
        wt = 0;
        break;
    }
    mtx[0][0] = scale_s / 1024.0f;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][1] = scale_t / 1024.0f;
    mtx[1][2] = 0.0f;
    if (matrix_sel != 0) {
        if (matrix_sel <= 3) {
            ind = &lbl_801A6D38->ind_mtx[matrix_sel - 1];
        } else if (matrix_sel <= 7) {
            ind = &lbl_801A6D38->ind_mtx[matrix_sel - 5];
        } else if (matrix_sel <= 11) {
            ind = &lbl_801A6D38->ind_mtx[matrix_sel - 9];
        }
        if (ind->scale_exp != 10 || fn_8008023C(ind, mtx, sizeof(mtx)) != 0) {
            fn_80036AC4(matrix_sel, mtx, 10);
            fn_800794F0(ind, mtx, sizeof(mtx));
            ind->scale_exp = 10;
        }
    }
    tev = &lbl_801A6D38->tev_ind[tev_stage];
    if (tev->ind_stage != ind_stage || tev->format != format || tev->bias_sel != bias_sel ||
        tev->matrix_sel != matrix_sel || tev->wrap_s != ws || tev->wrap_t != wt || tev->add_prev != 0 ||
        tev->utc_lod != 1 || tev->alpha_sel != alpha_sel) {
        GXSetTevIndirect(tev_stage, ind_stage, format, bias_sel, matrix_sel, ws, wt, FALSE, TRUE, alpha_sel);
        tev->ind_stage = ind_stage;
        tev->format = format;
        tev->bias_sel = bias_sel;
        tev->matrix_sel = matrix_sel;
        tev->wrap_s = ws;
        tev->wrap_t = wt;
        tev->add_prev = 0;
        tev->utc_lod = 1;
        tev->alpha_sel = alpha_sel;
    }
}
