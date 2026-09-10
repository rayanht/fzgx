#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/spline.h"

extern void mathutil_quat_mult(f32 *, f32 *, f32 *);
extern void fn_1_F56F8(f32 *out, f32 *in);
extern const f32 lbl_1_rodata_6D78;
extern void fn_1_F57A8(f32 *out, f32 *in);
extern const f32 lbl_1_rodata_6D70;
extern f64 fn_80088538(f32);
extern f64 fn_800883E8(f32);
extern f32 lbl_8006D0B4(f32);
extern f64 fn_80087E80(f32);
extern void fn_8006E8DC(void *);
extern void fn_1_9A508(Obj_1_data_2A7E0 *arg0);
extern void fn_1_F5B88(Obj_1_data_2A7E0_At3C *arg0);
extern void fn_1_9AD88(void);
extern void fn_1_F65A0(Obj_1_data_2A7E0_At3C *);
extern void fn_1_F7578(void);
extern void fn_8001D32C(u32 *);
extern void fn_80008BEC(void *dst, s32 value, u32 size);
extern void fn_1_F75D8(void *, int, int, int);
extern void fn_1_F8918(u8 *, u8 *);
extern s32 fn_8008023C(u8 *, Obj_1_bss_7F0C0 *, u32);
extern void fn_1_F85A0(Obj_1_bss_7F0C0 *, u8 *);
extern u16 lbl_1_data_414[36];
extern int fn_1_8D5F0(s16 value);
extern void fn_1_F7CAC(s16);
extern s32 fn_1_F7BE4(s16);
extern void fn_1_F7F48(s16 value);
extern int fn_1_14D6D8(s16 value);
extern void fn_1_F83F0(s16 value);
extern void fn_1_F8214(s16 value);
extern void fn_1_F8A04(void);
extern void fn_1_F8A90(void);
extern void fn_1_F8A7C(void);
extern void fn_1_F8AFC(u32 value);
extern void fn_1_F8B64(void);
extern void fn_1_F8BA8(void);
extern void fn_1_F8B7C(void);
extern void fn_1_F8BD4(void);
extern void fn_1_F8C28(s32 value);
extern void fn_1_F8CCC(s32 value);
extern void fn_1_F8CA0(s32 value);
extern struct Table lbl_1_rodata_6FF0;
extern void fn_80083DB0(void *arg0, u32 arg1);
extern void fn_1_F9D04(u8 index);
extern void fn_1_F9D90(void);
extern void fn_1_F9E38(void);
extern void fn_1_F9EE4(s32 value);
extern u8 fn_1_FA69C(s32 index);
extern void fn_1_3EF14(void *);
extern s32 fn_1_58C4(void);
extern void fn_1_FA89C(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_76BF8(void);
extern void fn_1_72648(void);
extern void fn_1_FB0B4(Obj_1_bss_84428 *data);
extern void fn_1_FB180(int *value);
extern void fn_1_9AD54(void);
extern void fn_1_FB18C(void);

extern void fn_1_F8918(u8 *, u8 *);
extern u16 lbl_1_data_414[36];
extern void fn_8001D3E4(int index, int value);
extern u32 lbl_801A66A0;

/* fzgx:begin fn_1_F55C4 */
void fn_1_F55C4(f32 *out, f32 *arg1, f32 *in, f32 *arg3) {
    f32 temp[4];

    temp[0] = -in[0];
    temp[1] = -in[1];
    temp[2] = -in[2];
    temp[3] = in[3];
    mathutil_quat_mult(out, temp, arg1);
    mathutil_quat_mult(temp, temp, arg3);
    fn_1_F56F8(out, out);
    fn_1_F56F8(temp, temp);
    out[0] += temp[0];
    out[1] += temp[1];
    out[2] += temp[2];
    out[3] += temp[3];
    out[0] /= lbl_1_rodata_6D78;
    out[1] /= lbl_1_rodata_6D78;
    out[2] /= lbl_1_rodata_6D78;
    out[3] /= lbl_1_rodata_6D78;
    fn_1_F57A8(out, out);
    mathutil_quat_mult(out, in, out);
}
/* fzgx:end fn_1_F55C4 */

/* fzgx:begin fn_1_F56F8 */
void fn_1_F56F8(f32 *out, f32 *in) {
    f32 value;
    f32 scale;
    f32 zero;

    value = fn_80088538(in[3]);
    scale = fn_800883E8(value);
    zero = lbl_1_rodata_6D70;
    out[3] = zero;
    if (scale > zero) {
        out[0] = value * in[0] / scale;
        out[1] = value * in[1] / scale;
        out[2] = value * in[2] / scale;
    } else {
        out[2] = zero;
        out[1] = zero;
        out[0] = zero;
    }
}
/* fzgx:end fn_1_F56F8 */

/* fzgx:begin fn_1_F57A8 */
void fn_1_F57A8(f32 *out, f32 *in) {
    f32 length;
    f32 scale;
    f32 angle;

    length = lbl_8006D0B4(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
    scale = fn_800883E8(length);
    angle = fn_80087E80(length);
    out[3] = angle;
    if (length > lbl_1_rodata_6D70) {
        out[0] = scale * in[0] / length;
        out[1] = scale * in[1] / length;
        out[2] = scale * in[2] / length;
    } else {
        out[2] = lbl_1_rodata_6D70;
        out[1] = lbl_1_rodata_6D70;
        out[0] = lbl_1_rodata_6D70;
    }
}
/* fzgx:end fn_1_F57A8 */

/* fzgx:begin fn_1_F5A2C */
typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

void fn_1_F5A2C(Vec4 *dst, const Vec4 *a, const Vec4 *b, f32 t) {
    f32 delta;
    f32 product;
    f32 start;

    start = a->x;
    delta = b->x - start;
    product = t * delta;
    dst->x = start + product;
    start = a->y;
    delta = b->y - start;
    product = t * delta;
    dst->y = start + product;
    start = a->z;
    delta = b->z - start;
    product = t * delta;
    dst->z = start + product;
    start = a->w;
    delta = b->w - start;
    product = t * delta;
    dst->w = start + product;
    fn_8006E8DC(dst);
}
/* fzgx:end fn_1_F5A2C */

/* fzgx:begin fn_1_F5AAC */
// fn_1_F5AAC: empty in retail (single blr).
void fn_1_F5AAC(void) {
}
/* fzgx:end fn_1_F5AAC */

/* fzgx:begin fn_1_F5AB0 */
void fn_1_F5AB0(void) {
    Obj_1_data_2A7E0_At3C *arg0 = lbl_1_data_2A7E0.unk_3C;
    fn_1_9A508(&lbl_1_data_2A7E0);
    fn_1_F5B88(arg0);
}
/* fzgx:end fn_1_F5AB0 */

/* fzgx:begin fn_1_F5AEC */
// fn_1_F5AEC: empty in retail (single blr).
void fn_1_F5AEC(void) {
}
/* fzgx:end fn_1_F5AEC */

/* fzgx:begin fn_1_F5AF0 */
// Update the spline state after refreshing the shared data.
void fn_1_F5AF0(void) {
    Obj_1_data_2A7E0_At3C *state;

    state = lbl_1_data_2A7E0.unk_3C;
    fn_1_9AD54();
    if ((s32)state->unk_10 != 0) {
        fn_1_F5D94(state);
    }
}
/* fzgx:end fn_1_F5AF0 */

/* fzgx:begin fn_1_F5B38 */
// fn_1_F5B38: empty in retail (single blr).
void fn_1_F5B38(void) {
}
/* fzgx:end fn_1_F5B38 */

/* fzgx:begin fn_1_F5B3C */
void fn_1_F5B3C(void) {
    Obj_1_data_2A7E0_At3C *obj = lbl_1_data_2A7E0.unk_3C;

    fn_1_9AD88();
    if ((s32)obj->unk_10 != 0) {
        fn_1_F65A0(obj);
    }
}
/* fzgx:end fn_1_F5B3C */

/* fzgx:begin fn_1_F5B84 */
// fn_1_F5B84: empty in retail (single blr).
void fn_1_F5B84(void) {
}
/* fzgx:end fn_1_F5B84 */

/* fzgx:begin fn_1_F70C0 */
// fn_1_F70C0: returns a constant.
int fn_1_F70C0(void) {
    return 1;
}
/* fzgx:end fn_1_F70C0 */

/* fzgx:begin fn_1_F70C8 */
// fn_1_F70C8: returns a constant.
int fn_1_F70C8(void) {
    return 1;
}
/* fzgx:end fn_1_F70C8 */

/* fzgx:begin fn_1_F70D0 */
// Clear the spline state buffers and mark the state as initialized.
void fn_1_F70D0(void) {
    u32 *state = (u32 *)&lbl_1_bss_7F028;

    fn_80008BEC((u8 *)state + 4, 0, 0x10);
    fn_80008BEC((u8 *)state + 0x14, 0, 0x10);
    *(u8 *)state |= 1;
}
/* fzgx:end fn_1_F70D0 */

/* fzgx:begin fn_1_F7128 */
void fn_1_F7128(void) {
    int i;
    Obj_1_bss_7F03C *dst;
    Obj_1_bss_7F02C *src;

    dst = &lbl_1_bss_7F03C;
    src = &lbl_1_bss_7F02C;
    for (i = 0; i < 4; i++) {
        if (src->unk_0 != 0) {
            dst->unk_0 = src->unk_0;
            if (src->unk_0 == 6 || src->unk_0 == 5) {
                dst->unk_2 = 0;
            } else if ((u8)(src->unk_0 - 1) <= 2 || src->unk_0 == 4) {
                fn_8001D3E4(i, 1);
                dst->unk_2 = src->unk_2;
            }
            src->unk_0 = 0;
        }
        dst = (Obj_1_bss_7F03C *)((u8 *)dst + 4);
        src = (Obj_1_bss_7F02C *)((u8 *)src + 4);
    }

    dst = &lbl_1_bss_7F03C;
    for (i = 0; i < 4; i++) {
        if (dst->unk_0 == 6) {
            fn_8001D3E4(i, 0);
            dst->unk_0 = 0;
        } else if (dst->unk_0 == 5) {
            fn_8001D3E4(i, 2);
            dst->unk_0 = 0;
        } else {
            if (dst->unk_0 == 3) {
                if (lbl_801A66A0 & 1) {
                    fn_8001D3E4(i, 0);
                } else {
                    fn_8001D3E4(i, 1);
                }
            }
            if (dst->unk_0 == 4) {
                if (lbl_801A66A0 & 1) {
                    fn_8001D3E4(i, 2);
                } else {
                    fn_8001D3E4(i, 1);
                }
            }
            if (dst->unk_2 != 0) {
                dst->unk_2--;
            }
            if (dst->unk_2 == 1) {
                fn_8001D3E4(i, dst->unk_0 == 1 ? 2 : 0);
                dst->unk_0 = 0;
                dst->unk_2 = 0;
            }
        }
        dst = (Obj_1_bss_7F03C *)((u8 *)dst + 4);
    }
}
/* fzgx:end fn_1_F7128 */

/* fzgx:begin fn_1_F7308 */
void fn_1_F7308(void) {
    fn_1_F7578();
    lbl_1_bss_7F028 &= 0xFE;
}
/* fzgx:end fn_1_F7308 */

/* fzgx:begin fn_1_F7338 */
extern int fn_1_866B4(s8);
extern int fn_1_864FC(s8);
extern void fn_1_F73A8(int, void *, void *);

void fn_1_F7338(int arg0, void *arg1, void *arg2) {
    s8 value;

    value = (s8)fn_1_866B4((s8)arg0);
    if (value >= 0) {
        switch (fn_1_864FC(value) & 0x10) {
        case 0:
            fn_1_F73A8(arg0, arg1, arg2);
            break;
        default:
            break;
        }
    }
}
/* fzgx:end fn_1_F7338 */

/* fzgx:begin fn_1_F755C */
void fn_1_F755C(u8 value) {
    lbl_1_data_3E8F0 = value;
}
/* fzgx:end fn_1_F755C */

/* fzgx:begin fn_1_F7568 */
u8 fn_1_F7568(void) {
    return lbl_1_data_3E8F0;
}
/* fzgx:end fn_1_F7568 */

/* fzgx:begin fn_1_F7578 */
// Initialize the spline work buffers to their default values.

void fn_1_F7578(void) {
    u32 values[4];

    values[0] = 2;
    values[1] = 2;
    values[2] = 2;
    values[3] = 2;
    fn_8001D32C(values);
    fn_80008BEC(&lbl_1_bss_7F02C, 0, 0x10);
    fn_80008BEC(&lbl_1_bss_7F03C, 0, 0x10);
}
/* fzgx:end fn_1_F7578 */

/* fzgx:begin fn_1_F7870 */
void fn_1_F7870(u32 value) {
    u32 values[2];

    values[0] = value;
    values[1] = 0;
    fn_1_F75D8(values, 0, 1, 0);
}
/* fzgx:end fn_1_F7870 */

/* fzgx:begin fn_1_F78AC */
void fn_1_F78AC(void *arg0) {
    fn_1_F75D8(arg0, 1, 0, 0);
}
/* fzgx:end fn_1_F78AC */

/* fzgx:begin fn_1_F78D8 */
void fn_1_F78D8(void *arg0) {
    fn_1_F75D8(arg0, 1, 0, 1);
}
/* fzgx:end fn_1_F78D8 */

/* fzgx:begin fn_1_F7904 */
// Builds the spline workspace and reports whether its serialized data is valid.
s32 fn_1_F7904(void) {
    u8 buffer[0x5360];

    fn_1_F8918(&lbl_1_bss_718E0.pad_1A2[0x1e], buffer);
    return fn_8008023C(buffer, &lbl_1_bss_7F0C0, 0x5360) != 0;
}
/* fzgx:end fn_1_F7904 */

/* fzgx:begin fn_1_F7954 */
s32 fn_1_F7954(void) {
    u8 buffer[0x5360];
    u8 *workspace;

    workspace = (u8 *)&lbl_1_bss_718E0 + 0x1c0;
    fn_1_F8918(workspace, buffer);
    if (fn_8008023C(buffer, &lbl_1_bss_7F0C0, 0x5360) == 0) {
        return 0;
    }
    fn_1_F85A0(&lbl_1_bss_7F0C0, workspace);
    return 1;
}
/* fzgx:end fn_1_F7954 */

/* fzgx:begin fn_1_F79C8 */
// Initialize spline data and publish the active spline region.
void fn_1_F79C8(void) {
    fn_1_F8918(&lbl_1_bss_718E0.pad_1A2[0x1e], (u8 *)&lbl_1_bss_7F0C0);
    lbl_1_bss_84420 = (u32)((u8 *)&lbl_1_bss_7F0C0 + 0x4b5c);
    lbl_1_data_414[0] = 0xffff;
}
/* fzgx:end fn_1_F79C8 */

/* fzgx:begin fn_1_F7B2C */
void fn_1_F7B2C(void) {
    s16 i;

    for (i = 0; i < 0x29; i++) {
        if (fn_1_8D5F0(i) & (1u << 31)) {
            fn_1_F7CAC(i);
        }
    }
}
/* fzgx:end fn_1_F7B2C */

/* fzgx:begin fn_1_F7B80 */
s16 fn_1_F7B80(void) {
    s16 i;
    s16 count;

    count = 0;
    for (i = 0; i < 0x29; i++) {
        if (fn_1_F7BE4(i) != 0) {
            count++;
        }
    }
    return count;
}
/* fzgx:end fn_1_F7B80 */

/* fzgx:begin fn_1_F7D18 */
void fn_1_F7D18(void) {
    s16 i;

    for (i = 0; i < 41; i++) {
        if (!(fn_1_8D5F0(i) & 0x10000000)) {
            fn_1_F7F48(i);
        }
    }
}
/* fzgx:end fn_1_F7D18 */

/* fzgx:begin fn_1_F7D6C */
void fn_1_F7D6C(void) {
    s16 i;

    for (i = 0; i < 41; i++) {
        if (fn_1_8D5F0(i) & 0x10000000) {
            fn_1_F7F48(i);
        }
    }
}
/* fzgx:end fn_1_F7D6C */

/* fzgx:begin fn_1_F7DC0 */
enum {
    SIGN_BIT = (u32)1 << 31
};

void fn_1_F7DC0(void) {
    s16 i;

    for (i = 0; i < 75; i++) {
        if (!(fn_1_14D6D8(i) & SIGN_BIT) &&
            !(fn_1_14D6D8(i) & 0x10000000)) {
            fn_1_F83F0(i);
        }
    }
}
/* fzgx:end fn_1_F7DC0 */

/* fzgx:begin fn_1_F7E24 */
void fn_1_F7E24(void) {
    s16 i;

    for (i = 0; i < 75; i++) {
        if (fn_1_14D6D8(i) & ((u32)1 << 31)) {
            if (!(fn_1_14D6D8(i) & 0x10000000)) {
                fn_1_F83F0(i);
            }
        }
    }
}
/* fzgx:end fn_1_F7E24 */

/* fzgx:begin fn_1_F7E88 */
void fn_1_F7E88(void) {
    s16 i;

    for (i = 0; i < 41; i++) {
        if (fn_1_8D5F0(i) & 0x20000000) {
            fn_1_F7F48(i);
        }
    }
}
/* fzgx:end fn_1_F7E88 */

/* fzgx:begin fn_1_F8030 */
// Clears the spline state counters.
void fn_1_F8030(void) {
    lbl_1_bss_7F0C0.unk_4C = 0;
    lbl_1_bss_7F0C0.unk_48 = 0;
}
/* fzgx:end fn_1_F8030 */

/* fzgx:begin fn_1_F8048 */
void fn_1_F8048(void) {
    s16 i;

    for (i = 0; i < 75; i++) {
        if (fn_1_14D6D8(i) & 0x40000000) {
            fn_1_F8214(i);
        }
    }
}
/* fzgx:end fn_1_F8048 */

/* fzgx:begin fn_1_F82E0 */
void fn_1_F82E0(void) {
    s16 i;

    for (i = 0; i < 75; i++) {
        if (fn_1_14D6D8(i) & 0x20000000) {
            fn_1_F83F0(i);
        }
    }
}
/* fzgx:end fn_1_F82E0 */

/* fzgx:begin fn_1_F8580 */
void fn_1_F8580(void) {
    lbl_1_bss_7F0C0.unk_5C = 0;
    lbl_1_bss_7F0C0.unk_58 = 0;
    lbl_1_bss_7F0C0.unk_54 = 0;
    lbl_1_bss_7F0C0.unk_50 = 0;
}
/* fzgx:end fn_1_F8580 */

/* fzgx:begin fn_1_F89C0 */
void fn_1_F89C0(void) {
    fn_1_F8A04();
    fn_1_F8A90();
}
/* fzgx:end fn_1_F89C0 */

/* fzgx:begin fn_1_F89E4 */
// Returns the selected bit from the rolling flag mask.
u32 fn_1_F89E4(u8 value) {
    return __rlwnm(((u32 *)&lbl_1_bss_7F0C0)[4672], (value + 1) & 0x1f, 31, 31);
}
/* fzgx:end fn_1_F89E4 */

/* fzgx:begin fn_1_F8A04 */
// Clears the spline object's reset flag.
void fn_1_F8A04(void) {
    ((u32 *)&lbl_1_bss_7F0C0)[4672] = 0;
}
/* fzgx:end fn_1_F8A04 */

/* fzgx:begin fn_1_F8A18 */
void fn_1_F8A18(void) {
    fn_1_F8A7C();
}
/* fzgx:end fn_1_F8A18 */

/* fzgx:begin fn_1_F8A38 */
// Tests the spline flag selected by the low byte of the input.
u32 fn_1_F8A38(u32 value) {
    return __rlwnm(((u32 *)&lbl_1_bss_7F0C0)[4673], ((value & 0xff) + 1) & 0x1f, 31, 31);
}
/* fzgx:end fn_1_F8A38 */

/* fzgx:begin fn_1_F8A58 */
// Sets the spline flag selected by the low byte of the input.
void fn_1_F8A58(u32 value) {
    ((u32 *)&lbl_1_bss_7F0C0)[4673] |= 0x80000000u >> (value & 0xff);
}
/* fzgx:end fn_1_F8A58 */

/* fzgx:begin fn_1_F8A7C */
// Clears the spline object's state field.
void fn_1_F8A7C(void) {
    ((u32 *)&lbl_1_bss_7F0C0)[4673] = 0;
}
/* fzgx:end fn_1_F8A7C */

/* fzgx:begin fn_1_F8A90 */
void fn_1_F8A90(void) {
    u32 i;

    for (i = 0; (i & 0xff) < 6; i++) {
        fn_1_F8AFC(i);
    }
}
/* fzgx:end fn_1_F8A90 */

/* fzgx:begin fn_1_F8AD4 */
// Sets the spline state bit selected by the caller.
void fn_1_F8AD4(u32 value) {
    u32* state_word = (u32*)((u8*)&lbl_1_bss_7F0C0 + 0x4900);

    *state_word |= 0x80000000u >> ((value & 0xff) + 0x10);
}
/* fzgx:end fn_1_F8AD4 */

/* fzgx:begin fn_1_F8AFC noprologue */
#include "types.h"

struct fn_1_F8AFC_lbl_1_bss_7F0C0 {
    u8 pad_0[0x4900];
    u32 unk_4900;
};

extern struct fn_1_F8AFC_lbl_1_bss_7F0C0 lbl_1_bss_7F0C0;

void fn_1_F8AFC(u32 arg0) {
    u32 v0;
    v0 = lbl_1_bss_7F0C0.unk_4900;
    lbl_1_bss_7F0C0.unk_4900 = (v0 & ~((u32)0x80000000 >> ((arg0 & 0xFF) + 16)));
}
/* fzgx:end fn_1_F8AFC */

/* fzgx:begin fn_1_F8B24 */
void fn_1_F8B24(void) {
    fn_1_F8B64();
    fn_1_F8BA8();
    fn_1_F8B7C();
    fn_1_F8BD4();
}
/* fzgx:end fn_1_F8B24 */

/* fzgx:begin fn_1_F8B50 */
// Mark the spline state as initialized.
void fn_1_F8B50(void) {
    *(u32 *)((u8 *)&lbl_1_bss_7F0C0 + 0x4910) = 1;
}
/* fzgx:end fn_1_F8B50 */

/* fzgx:begin fn_1_F8B64 */
// Clear the spline state counters.
void fn_1_F8B64(void) {
    ((u32 *)&lbl_1_bss_7F0C0)[4676] = 0;
    ((u32 *)&lbl_1_bss_7F0C0)[4677] = 0;
}
/* fzgx:end fn_1_F8B64 */

/* fzgx:begin fn_1_F8B7C */
void fn_1_F8B7C(void) {
    fn_1_F8C28(0x80000000u);
    fn_1_F8C28(0x40000000u);
}
/* fzgx:end fn_1_F8B7C */

/* fzgx:begin fn_1_F8BA8 */
void fn_1_F8BA8(void) {
    fn_1_F8CCC(0x80000000u);
    fn_1_F8CCC(0x40000000u);
}
/* fzgx:end fn_1_F8BA8 */

/* fzgx:begin fn_1_F8BD4 */
void fn_1_F8BD4(void) {
    fn_1_F8CA0(0);
    fn_1_F8CA0(1);
}
/* fzgx:end fn_1_F8BD4 */

/* fzgx:begin fn_1_F8C00 */
// Sets the bit corresponding to the spline index.
void fn_1_F8C00(s32 value) {
    value *= 2;
    (&lbl_1_bss_7F0C0.unk_104)[4676 - 65] |= (((u32)1 << 31) >> (31 - value));
}
/* fzgx:end fn_1_F8C00 */

/* fzgx:begin fn_1_F8C28 */
// Clears the bit corresponding to the spline index.
void fn_1_F8C28(s32 value) {
    value *= 2;
    (&lbl_1_bss_7F0C0.unk_104)[4676 - 65] &= ~(((u32)1 << 31) >> (31 - value));
}
/* fzgx:end fn_1_F8C28 */

/* fzgx:begin fn_1_F8C50 noprologue */
#include "types.h"

struct fn_1_F8C50_lbl_1_bss_7F0C0 {
    u8 pad_0[0x4910];
    u32 unk_4910;
};

extern struct fn_1_F8C50_lbl_1_bss_7F0C0 lbl_1_bss_7F0C0;

u8 fn_1_F8C50(s32 arg0) {
    u32 shift = 32 - (arg0 * 2);
    u32 value = lbl_1_bss_7F0C0.unk_4910;
    shift &= 31;
    return (u8)__rlwnm(value, shift, 31, 31);
}
/* fzgx:end fn_1_F8C50 */

/* fzgx:begin fn_1_F8C74 */
// Sets the bit corresponding to the supplied spline index.
void fn_1_F8C74(s32 value) {
    value *= 2;
    *((u32*)((u8*)&lbl_1_bss_7F0C0 + 0x4910)) |= (((u32)1 << 31) >> (31 - (value + 1)));
}
/* fzgx:end fn_1_F8C74 */

/* fzgx:begin fn_1_F8CA0 */
// Clears the bit corresponding to the spline index.
void fn_1_F8CA0(s32 value) {
    value *= 2;
    ((u32 *)&lbl_1_bss_7F0C0)[4676] &= ~(((u32)1 << 31) >> (31 - (value + 1)));
}
/* fzgx:end fn_1_F8CA0 */

/* fzgx:begin fn_1_F8CCC */
// Clears the bit selected by value from the spline state mask.
void fn_1_F8CCC(s32 value) {
    ((u32 *)&lbl_1_bss_7F0C0)[4677] &= ~(((u32)1 << 31) >> (31 - value));
}
/* fzgx:end fn_1_F8CCC */

/* fzgx:begin fn_1_F8D10 */
// Clamps the spline counter to its maximum permitted value.
u32 fn_1_F8D10(void) {
    u32 value = 99999;

    if (((u32 *)&lbl_1_bss_7F0C0)[4670] > value) {
        ((u32 *)&lbl_1_bss_7F0C0)[4670] = value;
    }
    return ((u32 *)&lbl_1_bss_7F0C0)[4670];
}
/* fzgx:end fn_1_F8D10 */

/* fzgx:begin fn_1_F8D38 */
// Clamps the spline limit and stores it in the shared spline state.
void fn_1_F8D38(u32 value) {
    if (value > 0x1869F) {
        value = 0x1869F;
    }
    ((u32 *)&lbl_1_bss_7F0C0)[4670] = value;
}
/* fzgx:end fn_1_F8D38 */

/* fzgx:begin fn_1_F8D5C */
struct fn_1_F8D5C_Copy440 { u32 a[110]; };

extern u32 lbl_1_rodata_6E38;
extern void fn_80008BA8(u32, u32, u32);

void fn_1_F8D5C(u32 arg0, u32 arg1) {
    struct fn_1_F8D5C_Copy440 loc_8;
    /* frame */
    loc_8 = *(struct fn_1_F8D5C_Copy440 *)&lbl_1_rodata_6E38;
    fn_80008BA8(arg1, (u32)((u8 *)&loc_8 + ((s16)arg0 * 10)), 10);
}
/* fzgx:end fn_1_F8D5C */

/* fzgx:begin fn_1_F8DC4 */
struct Table {
    u32 values[4][6];
};

void fn_1_F8DC4(s16 index0, s16 index1, void *arg0) {
    struct Table table;

    table = lbl_1_rodata_6FF0;
    fn_80083DB0(arg0, table.values[index0][index1]);
}
/* fzgx:end fn_1_F8DC4 */

/* fzgx:begin fn_1_F9C6C */
void fn_1_F9C6C(void) {
    fn_1_F9D04(0);
    fn_1_F9D04(1);
    fn_1_F9D04(2);
}
/* fzgx:end fn_1_F9C6C */

/* fzgx:begin fn_1_F9CA0 noprologue */
#include "types.h"

extern struct fn_1_F9CA0_lbl_1_bss_7F0C0 lbl_1_bss_7F0C0;

struct fn_1_F9CA0_lbl_1_bss_7F0C0_60_E48 {
    u8 pad_0[0x4];
    u16 unk_4;
    u8 pad_6[0x2A];
};
struct fn_1_F9CA0_lbl_1_bss_7F0C0 {
    u8 pad_0[0x60];
    struct fn_1_F9CA0_lbl_1_bss_7F0C0_60_E48 unk_60[1];
};

u32 fn_1_F9CA0(u32 arg0, u32 arg1) {
    return (lbl_1_bss_7F0C0.unk_60[(arg0 & 0xFF)].unk_4 & ((s32)(0x10000 + -32768) >> (arg1 & 0xFF)));
}
/* fzgx:end fn_1_F9CA0 */

/* fzgx:begin fn_1_F9CD0 */
// Sets the requested flag in an indexed spline record.
void fn_1_F9CD0(u8 index, u8 shift) {
    u16 *flags = &lbl_1_bss_7F0C0.unk_64;
    flags[index * 0x18] |= 0x8000 >> shift;
}
/* fzgx:end fn_1_F9CD0 */

/* fzgx:begin fn_1_F9D04 */
// Clear the selected spline entry's status field.
void fn_1_F9D04(u8 index) {
    (&lbl_1_bss_7F0C0.unk_64)[index * 0x18] = 0;
}
/* fzgx:end fn_1_F9D04 */

/* fzgx:begin fn_1_F9D24 */
void fn_1_F9D24(void) {
    fn_1_F9D90();
}
/* fzgx:end fn_1_F9D24 */

/* fzgx:begin fn_1_F9D44 */
// Tests the requested spline flag.
u32 fn_1_F9D44(u32 arg) {
    return lbl_1_bss_7F0C0.unk_68 & (0x8000 >> (arg & 0xff));
}
/* fzgx:end fn_1_F9D44 */

/* fzgx:begin fn_1_F9D68 */
void fn_1_F9D68(u32 arg) {
    lbl_1_bss_7F0C0.unk_68 |= 0x8000 >> (arg & 0xff);
}
/* fzgx:end fn_1_F9D68 */

/* fzgx:begin fn_1_F9D90 */
// Clear the spline object's active flags.
void fn_1_F9D90(void) {
    lbl_1_bss_7F0C0.unk_68 = 0;
}
/* fzgx:end fn_1_F9D90 */

/* fzgx:begin fn_1_F9DA4 */
void fn_1_F9DA4(void) {
    fn_1_F9E38();
}
/* fzgx:end fn_1_F9DA4 */

/* fzgx:begin fn_1_F9DC4 */
// Return the bit selected by the low byte of the requested flag index.
u32 fn_1_F9DC4(u32 arg) {
    return lbl_1_bss_7F0C0.unk_6A & (0x8000 >> (arg & 0xff));
}
/* fzgx:end fn_1_F9DC4 */

/* fzgx:begin fn_1_F9DE8 */
void fn_1_F9DE8(u32 param) {
    lbl_1_bss_7F0C0.unk_6A |= 0x8000 >> (param & 0xFF);
}
/* fzgx:end fn_1_F9DE8 */

/* fzgx:begin fn_1_F9E10 */
// Clear the bit selected by the low byte of the shift amount.
void fn_1_F9E10(u32 param) {
    lbl_1_bss_7F0C0.unk_6A &= ~(0x8000 >> (param & 0xFF));
}
/* fzgx:end fn_1_F9E10 */

/* fzgx:begin fn_1_F9E38 */
// Clear the spline object's status field.
void fn_1_F9E38(void) {
    lbl_1_bss_7F0C0.unk_6A = 0;
}
/* fzgx:end fn_1_F9E38 */

/* fzgx:begin fn_1_F9E4C */
void fn_1_F9E4C(void) {
    fn_1_F9EE4(0);
    fn_1_F9EE4(1);
    fn_1_F9EE4(2);
}
/* fzgx:end fn_1_F9E4C */

/* fzgx:begin fn_1_F9E80 noprologue */
#include "types.h"

extern struct fn_1_F9E80_lbl_1_bss_7F0C0 lbl_1_bss_7F0C0;

struct fn_1_F9E80_lbl_1_bss_7F0C0_60_E48 {
    u8 pad_0[0x6];
    u16 unk_6;
    u8 pad_8[0x28];
};
struct fn_1_F9E80_lbl_1_bss_7F0C0 {
    u8 pad_0[0x60];
    struct fn_1_F9E80_lbl_1_bss_7F0C0_60_E48 unk_60[1];
};

u32 fn_1_F9E80(u32 arg0, u32 arg1) {
    return (lbl_1_bss_7F0C0.unk_60[(arg0 & 0xFF)].unk_6 & ((s32)(0x10000 + -32768) >> (arg1 & 0xFF)));
}
/* fzgx:end fn_1_F9E80 */

/* fzgx:begin fn_1_F9EB0 noprologue */
#include "types.h"

extern struct fn_1_F9EB0_lbl_1_bss_7F0C0 lbl_1_bss_7F0C0;

struct fn_1_F9EB0_lbl_1_bss_7F0C0_60_E48 {
    u8 pad_0[0x6];
    u16 unk_6;
    u8 pad_8[0x28];
};
struct fn_1_F9EB0_lbl_1_bss_7F0C0 {
    u8 pad_0[0x60];
    struct fn_1_F9EB0_lbl_1_bss_7F0C0_60_E48 unk_60[1];
};

u32 fn_1_F9EB0(u32 arg0, u32 arg1) {
    u32 v0;
    v0 = (0x10000 + -32768);
    lbl_1_bss_7F0C0.unk_60[(arg0 & 0xFF)].unk_6 = (lbl_1_bss_7F0C0.unk_60[(arg0 & 0xFF)].unk_6 | ((s32)v0 >> (arg1 & 0xFF)));
    return v0;
}
/* fzgx:end fn_1_F9EB0 */

/* fzgx:begin fn_1_F9EE4 */
// Reset one spline slot and clear its working buffer.
void fn_1_F9EE4(s32 arg0) {
    *(u16 *)((u8 *)&lbl_1_bss_7F0C0 + ((arg0 & 0xFF) * 0x30) + 0x66) = 0;
    fn_80008BEC((u8 *)&lbl_1_bss_7F0C0 + ((arg0 & 0xFF) * 0x30) + 0x6C, 0, 0x28);
}
/* fzgx:end fn_1_F9EE4 */

/* fzgx:begin fn_1_F9FB4 */
void fn_1_F9FB4(void) {
    u32 ptr = lbl_1_bss_84420;

    if ((*(u8 *)(ptr + 0x1) & 1) == 0) {
        *(u8 *)(ptr + 0x1) |= 2;
    }

    ptr = lbl_1_bss_84420;
    *(u8 *)(ptr + 0x1) |= 1;
}
/* fzgx:end fn_1_F9FB4 */

/* fzgx:begin fn_1_F9FEC */
// Returns the low flag bit stored in the spline state.
u32 fn_1_F9FEC(void) {
    u32 ptr = lbl_1_bss_84420;
    return (*(u8 *)(ptr + 0x1)) & 1;
}
/* fzgx:end fn_1_F9FEC */

/* fzgx:begin fn_1_FA004 */
// Reads the second status byte and returns its bit-mask value.
u32 fn_1_FA004(void) {
    u32 ptr = lbl_1_bss_84420;
    return (*(u8 *)(ptr + 0x1)) & 2;
}
/* fzgx:end fn_1_FA004 */

/* fzgx:begin fn_1_FA01C noprologue */
#include "types.h"

extern struct fn_1_FA01C_lbl_1_bss_84420 lbl_1_bss_84420;

struct fn_1_FA01C_lbl_1_bss_84420 {
    u32 unk_0;
};

u32 fn_1_FA01C(void) {
    u32 v0;
    v0 = lbl_1_bss_84420.unk_0;
    *(u8 *)((u8 *)v0 + 1) = (*(u8 *)((u8 *)v0 + 1) & 0xFFFFFFFD);
    return v0;
}
/* fzgx:end fn_1_FA01C */

/* fzgx:begin fn_1_FA038 */
void fn_1_FA038(void) {
    u32 ptr = lbl_1_bss_84420;

    if ((*(u8 *)(ptr + 2) & 1) == 0) {
        *(u8 *)(ptr + 2) |= 2;
    }

    ptr = lbl_1_bss_84420;
    *(u8 *)(ptr + 2) |= 1;
}
/* fzgx:end fn_1_FA038 */

/* fzgx:begin fn_1_FA070 */
u32 fn_1_FA070(void) {
    u32 ptr = lbl_1_bss_84420;
    // Test the object's low flag bit.
    return (*(u8 *)(ptr + 2)) & 1;
}
/* fzgx:end fn_1_FA070 */

/* fzgx:begin fn_1_FA088 */
u32 fn_1_FA088(void) {
    u32 ptr = lbl_1_bss_84420;
    return (*(u8 *)(ptr + 2)) & 2;
}
/* fzgx:end fn_1_FA088 */

/* fzgx:begin fn_1_FA0A0 noprologue */
#include "types.h"

extern struct fn_1_FA0A0_lbl_1_bss_84420 lbl_1_bss_84420;

struct fn_1_FA0A0_lbl_1_bss_84420 {
    u32 unk_0;
};

u32 fn_1_FA0A0(void) {
    u32 v0;
    v0 = lbl_1_bss_84420.unk_0;
    *(u8 *)((u8 *)v0 + 2) = (*(u8 *)((u8 *)v0 + 2) & 0xFFFFFFFD);
    return v0;
}
/* fzgx:end fn_1_FA0A0 */

/* fzgx:begin fn_1_FA0BC noprologue */
#include "types.h"

typedef struct {
    u8 pad_0[0x4900];
    u32 flags;
} SplineGlobalState;

extern SplineGlobalState lbl_1_bss_7F0C0;

u32 fn_1_FA0BC(s32 mode) {
    if (mode == 1) {
        u32 flags = lbl_1_bss_7F0C0.flags;
        s16 i;

        for (i = 1; i < 6; i++) {
            if (__rlwnm(flags, ((((u8)i) + 1) & 0x1f), 31, 31) == 0) {
                return 0;
            }
        }
        return 1;
    } else {
        u32 flags = lbl_1_bss_7F0C0.flags;
        s16 i;

        for (i = 0; i < 6; i++) {
            if (__rlwnm(flags, ((((u8)i) + 1) & 0x1f), 31, 31) != 0) {
                return 1;
            }
        }
        return 0;
    }
}
/* fzgx:end fn_1_FA0BC */

/* fzgx:begin fn_1_FA154 */
void fn_1_FA154(u32 byte_index, u32 bit_index) {
    u32 index;
    u32 ptr;
    u32 bit;
    u32 addr;
    index = byte_index & 0xff;
    ptr = lbl_1_bss_84420;
    bit = bit_index & 0xff;
    addr = ptr;
    addr = addr + index;
    *(u8 *)(3 + addr) |= 1 << bit;
}
/* fzgx:end fn_1_FA154 */

/* fzgx:begin fn_1_FA1A8 noprologue */
#include "types.h"

extern u32 fn_1_FA69C(u32);

u32 fn_1_FA1A8(u32 arg0) {
    u32 t0;
    t0 = fn_1_FA69C((s16)arg0);
    return ((u32)((-t0) | t0) >> 31);
}
/* fzgx:end fn_1_FA1A8 */

/* fzgx:begin fn_1_FA450 */
// Store the value when initialization permits the update.
void fn_1_FA450(u8 value) {
    u8 local[0x14c0];

    if (*(s16 *)&lbl_1_bss_960 == 2) {
        fn_1_3EF14(local);
        if ((*(u32 *)local & 0x800) == 0) {
            *(u8 *)(*(u32 *)&lbl_1_bss_84420 + 8) = value;
        }
    } else {
        *(u8 *)(*(u32 *)&lbl_1_bss_84420 + 8) = value;
    }
}
/* fzgx:end fn_1_FA450 */

/* fzgx:begin fn_1_FA4C0 */
// Return the byte at offset 0x8 from the spline object referenced by the global.
u8 fn_1_FA4C0(void) {
    return *(u8 *)(lbl_1_bss_84420 + 0x8);
}
/* fzgx:end fn_1_FA4C0 */

/* fzgx:begin fn_1_FA5A8 */
extern u32 lbl_1_bss_84420;

void fn_1_FA5A8(s16 index, u8 bit) {
    u32 base;
    u16 value;

    if (index >= 0x29) {
        return;
    }

    base = lbl_1_bss_84420;
    base += index << 1;
    value = *(u16 *)((u8 *)base + 0xa);
    *(u16 *)((u8 *)base + 0xa) = value | (1 << bit);
}
/* fzgx:end fn_1_FA5A8 */

/* fzgx:begin fn_1_FA5E0 */
extern u32 lbl_1_bss_84420;

u32 fn_1_FA5E0(u32 arg0, u32 arg1) {
    s16 v0;
    u32 v1;
    u32 v2;
    v0 = (s16)arg0;
    v1 = arg0;
    if (v0 >= 41) {
    v1 = 0;
    return v1;
    }
    v1 = 1;
    v2 = (v1 << (arg1 & 0xFF));
    v1 = (lbl_1_bss_84420 + (v0 << 1));
    v1 = *(u16 *)((u8 *)v1 + 10);
    v1 = (v1 & v2);
    return v1;
}
/* fzgx:end fn_1_FA5E0 */

/* fzgx:begin fn_1_FA61C */
// Clears the low flag bit in the spline state.
void fn_1_FA61C(void) {
    ((u8 *)lbl_1_bss_84420)[0x85] &= 0xfe;
}
/* fzgx:end fn_1_FA61C */

/* fzgx:begin fn_1_FA638 */
// Returns whether the spline state flag is enabled.
u8 fn_1_FA638(void) {
    return ((u8*)lbl_1_bss_84420)[0x85] & 1;
}
/* fzgx:end fn_1_FA638 */

/* fzgx:begin fn_1_FA650 */
// Toggle the enabled bit in the spline state.
void fn_1_FA650(void) {
    u8* state = (u8*)lbl_1_bss_84420;

    if (state[0x85] & 1) {
        state[0x85] &= 0xfe;
    } else {
        state[0x85] |= 1;
    }
}
/* fzgx:end fn_1_FA650 */

/* fzgx:begin fn_1_FA67C */
extern u32 lbl_1_bss_84420;

void fn_1_FA67C(s32 index) {
    u8 *base;

    if (index >= 0x29) {
        return;
    }
    base = (u8 *)lbl_1_bss_84420;
    base[index + 0x5c] = 1;
}
/* fzgx:end fn_1_FA67C */

/* fzgx:begin fn_1_FA69C */
// Return the spline entry value for an in-range index.
u8 fn_1_FA69C(s32 index) {
    u8 *base;

    if (index >= 0x29) {
        return 0;
    }
    base = (u8 *)lbl_1_bss_84420;
    return base[index + 0x5c];
}
/* fzgx:end fn_1_FA69C */

/* fzgx:begin fn_1_FA75C */
extern s32 fn_1_58C4(void);
extern void fn_80008BEC(void *dst, s32 value, u32 size);
extern void fn_1_FA89C(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_76BF8(void);
extern void fn_1_72648(void);
extern void fn_1_9A508(Obj_1_data_2A7E0 *arg0);
extern void fn_1_FB0B4(Obj_1_bss_84428 *data);
extern void fn_1_FB180(int *value);

// Reset spline state while preserving the active spline entry.
void fn_1_FA75C(void) {
    s32 spline_index;
    Obj_1_data_2A7E0_At3C *obj;
    u8 *status;
    u32 saved_entry;

    spline_index = fn_1_58C4();
    obj = lbl_1_data_2A7E0.unk_3C;
    status = (u8 *)&obj->unk_4;
    saved_entry = obj->unk_170;
    fn_80008BEC(obj, 0, 0x174);
    obj->unk_170 = saved_entry;

    if (obj->unk_170 != 0 && spline_index <= 1) {
        fn_1_FA89C(obj);
    } else {
        fn_1_76BF8();
        fn_1_72648();
        *status = 0;
    }

    obj->unk_0 = -1;
    {
        extern void fn_1_9A508(void);
        fn_1_9A508();
    }
    fn_1_FB0B4(&lbl_1_bss_84428);
    fn_1_FB180((int *)&lbl_1_bss_84428);

    if (*status == 0) {
        fn_1_76BF8();
        fn_1_72648();
        *status = 0;
    }
}
/* fzgx:end fn_1_FA75C */

/* fzgx:begin fn_1_FA82C */
// fn_1_FA82C: empty in retail (single blr).
void fn_1_FA82C(void) {
}
/* fzgx:end fn_1_FA82C */

/* fzgx:begin fn_1_FA830 */
void fn_1_FA830(void) {
    fn_1_9AD54();
    fn_1_FB18C();
}
/* fzgx:end fn_1_FA830 */

/* fzgx:begin fn_1_FA854 */
void fn_1_FA854(void) {
    fn_1_76BF8();
    fn_1_72648();
}
/* fzgx:end fn_1_FA854 */

/* fzgx:begin fn_1_FA878 */
void fn_1_FA878(void) {
    fn_1_9AD88();
}
/* fzgx:end fn_1_FA878 */

/* fzgx:begin fn_1_FA898 */
// fn_1_FA898: empty in retail (single blr).
void fn_1_FA898(void) {
}
/* fzgx:end fn_1_FA898 */

/* fzgx:begin fn_1_FB0A8 */
Obj_1_bss_84428 *fn_1_FB0A8(void) {
    return &lbl_1_bss_84428;
}
/* fzgx:end fn_1_FB0A8 */

/* fzgx:begin fn_1_FB180 */
// Set the destination value to one.
void fn_1_FB180(int *value) {
    *value = 1;
}
/* fzgx:end fn_1_FB180 */

/* fzgx:begin fn_1_FB770 */
int fn_1_FB770(int flag, u32 *value) {
    Obj_1_data_2A7E0_At3C *object = lbl_1_data_2A7E0.unk_3C;

    switch (flag) {
    case 0:
        object->unk_170 = *value;
        break;
    default:
        break;
    }

    return 1;
    return 1;
}
/* fzgx:end fn_1_FB770 */
