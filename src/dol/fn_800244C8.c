#include "types.h"

typedef struct Fn800244C8_DelayLine {
    s32 in_point;
    s32 out_point;
    s32 length;
    f32 *inputs;
    f32 last_output;
} Fn800244C8_DelayLine;

typedef struct Fn800244C8_ReverbStd {
    Fn800244C8_DelayLine all_pass[6];
    Fn800244C8_DelayLine comb[6];
    f32 all_pass_coef;
    f32 comb_coef[6];
    f32 lp_last_out[3];
    f32 level;
    f32 damping;
    s32 pre_delay_time;
    f32 *pre_delay_line[3];
    f32 *pre_delay_ptr[3];
} Fn800244C8_ReverbStd;

extern void *memset(void *, int, u32);
extern void *(*lbl_801A64F8)(u32);
extern f32 fn_800885B8(f32 x, f32 y);
extern u32 lbl_80128180[4];

static void fn_800244C8_SetDelay(Fn800244C8_DelayLine *dl, s32 lag) {
    dl->out_point = dl->in_point - lag * sizeof(f32);
    while (dl->out_point < 0) {
        dl->out_point += dl->length;
    }
}

static void fn_800244C8_Create(Fn800244C8_DelayLine *dl, s32 len) {
    dl->length = len * sizeof(f32);
    dl->inputs = lbl_801A64F8(len * sizeof(f32));
    memset(dl->inputs, 0, len * sizeof(f32));
    dl->last_output = 0.0f;
    fn_800244C8_SetDelay(dl, len >> 1);
    dl->in_point = 0;
    dl->out_point = 0;
}

BOOL fn_800244C8(Fn800244C8_ReverbStd *rv, f32 coloration, f32 time, f32 mix, f32 damping, f32 predelay) {
    u8 i;
    u8 k;

    if (coloration < 0.0f || coloration > 1.0f || time < 0.01f || time > 10.0f || mix < 0.0f || mix > 1.0f ||
        damping < 0.0f || damping > 1.0f || predelay < 0.0f || predelay > 0.1f) {
        return FALSE;
    }

    memset(rv, 0, sizeof(Fn800244C8_ReverbStd));
    for (k = 0; k < 3; k++) {
        for (i = 0; i < 2; i++) {
            fn_800244C8_Create(&rv->comb[i + k * 2], lbl_80128180[i] + 2);
            fn_800244C8_SetDelay(&rv->comb[i + k * 2], lbl_80128180[i]);
            rv->comb_coef[i + k * 2] = fn_800885B8(10.0f, (s32)(lbl_80128180[i] * -3) / (32000.0f * time));
        }
        for (i = 0; i < 2; i++) {
            fn_800244C8_Create(&rv->all_pass[i + k * 2], lbl_80128180[i + 2] + 2);
            fn_800244C8_SetDelay(&rv->all_pass[i + k * 2], lbl_80128180[i + 2]);
        }
        rv->lp_last_out[k] = 0.0f;
    }

    rv->all_pass_coef = coloration;
    rv->level = mix;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    rv->damping = 1.0f - (0.05f + 0.8f * rv->damping);

    if (predelay != 0.0f) {
        rv->pre_delay_time = 32000.0f * predelay;
        for (k = 0; k < 3; k++) {
            rv->pre_delay_line[k] = lbl_801A64F8(rv->pre_delay_time << 2);
            memset(rv->pre_delay_line[k], 0, rv->pre_delay_time << 2);
            rv->pre_delay_ptr[k] = rv->pre_delay_line[k];
        }
    } else {
        rv->pre_delay_time = 0;
        for (k = 0; k < 3; k++) {
            rv->pre_delay_ptr[k] = NULL;
            rv->pre_delay_line[k] = NULL;
        }
    }
    return TRUE;
}
