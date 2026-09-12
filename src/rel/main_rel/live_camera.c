#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/live_camera.h"

extern void OSPanic(u8 *file, int line, u8 *message, ...);
extern u32 fn_80008E30(u32);
extern u8 lbl_1_bss_17B4[12];
extern void fn_80083DB0(Obj_1_bss_3B30 *, void *);
extern u32 *fn_1_1304C(Obj_1_bss_3B30 *, u32);
extern u8 lbl_1_bss_1810[8984];
extern void fn_8000659C(void);
extern u32 OSIsThreadTerminated(u8 *);

extern void fn_1_6DD0(void *);
extern u32 *fn_1_1289C(u32 *);
extern s32 fn_1_4C10(void);
extern s32 fn_1_40BB4(void);
extern s32 fn_1_F2F34(void);
extern u32 fn_1_F45A4(void);
extern u32 fn_1_F4594(void);
extern f32 lbl_1_rodata_4E0[5];
extern f32 lbl_1_bss_1160[403];
extern void fn_1_5370(s32, s16);
extern f32 lbl_1_rodata_4F4[19];
extern const f64 lbl_1_rodata_548[2];
extern u32 lbl_801A63C0;
extern void fn_1_8636C(s16, void *);
extern void fn_1_862A8(s16, void *);
extern void lbl_8006DC6C(void *);
extern void lbl_8006E1B0(void *, void *);
extern s32 lbl_8006D24C(f32, f32);
extern int sprintf(char *, const char *, ...);

/* fzgx:begin fn_1_DA34 */
// Reports the camera source location and message used by this routine.
void fn_1_DA34(void) {
    OSPanic(lbl_1_data_4420, 0x34, lbl_1_data_4430);
}
/* fzgx:end fn_1_DA34 */

/* fzgx:begin fn_1_DE14 noprologue */
#include "types.h"
#include "rel/main_rel/live_camera.h"

extern s32 fn_1_4C10(void);
extern s32 fn_1_40BB4(void);
extern s32 fn_1_F2F34(void);
extern u32 fn_1_F45A4(void);
extern u32 fn_1_F4594(void);
extern f32 lbl_1_rodata_4E0[5];
extern f32 lbl_1_bss_1160[403];
extern void fn_1_5370(s32, s16);
extern void fn_1_6DD0(u32);

typedef struct {
    u8 unk_0;
    u8 unk_1;
    u8 pad_2[4];
    s16 unk_6;
    u8 pad_8[4];
    u32 unk_C;
    u8 pad_10[0x54];
    u16 unk_64;
} Fn1DE14State;

void fn_1_DE14(Fn1DE14State *state) {
    u8 enabled;

    if (lbl_1_bss_115C == 0) {
        return;
    }
    if (fn_1_4C10() != 0) {
        return;
    }
    if (fn_1_40BB4() != 0) {
        return;
    }
    if (fn_1_F2F34() == 0) {
        return;
    }
    if (fn_1_F4594() >= fn_1_F45A4() - 0x1e) {
        return;
    }

    enabled = 0;
    if ((lbl_1_bss_9F8.unk_8 >> 8) & 1) {
        enabled = 1;
    }
    if (enabled == 0) {
        return;
    }

    lbl_1_bss_1160[0] = lbl_1_rodata_4E0[0];
    if (state->unk_1 == 0) {
        state->unk_0++;
    } else {
        state->unk_1++;
    }
    if (state->unk_0 >= 4) {
        state->unk_0 = 0;
        state->unk_1 = 1;
    }

    switch (state->unk_1) {
    case 1:
        fn_1_5370(0, state->unk_6);
        break;
    case 2:
        fn_1_5370(1, state->unk_6);
        state->unk_1 = 0;
    default:
        fn_1_5370(1, state->unk_6);
    case 0:
        break;
    }

    state->unk_64 = 0;
    state->unk_C &= ~0x00200000;
    fn_1_6DD0(0);
}
/* fzgx:end fn_1_DE14 */

/* fzgx:begin fn_1_EE04 */
typedef struct {
    u8 pad[2];
    s16 state;
} Fn1EE04Context;

typedef void (*Fn1EE04Handler)(Fn1EE04Context *, void *);

// Dispatch the active live-camera handler, then advance camera processing.
void fn_1_EE04(Fn1EE04Context *context) {
    ((Fn1EE04Handler *)lbl_1_data_4440)[context->state](
        context, lbl_1_data_4440);
    fn_1_6DD0(0);
}
/* fzgx:end fn_1_EE04 */

/* fzgx:begin fn_1_FA84 noprologue */
#include "types.h"

struct fn_1_FA84_lbl_1_bss_1148 {
    u8 pad_0[0x67C];
    u32 unk_67C;
    u32 unk_680;
    u32 unk_684;
};
struct fn_1_FA84_lbl_1_data_43B8 {
    u8 pad_0[0x13C];
    u32 unk_13C;
    u32 unk_140;
    u32 unk_144;
};

extern struct fn_1_FA84_lbl_1_bss_1148 lbl_1_bss_1148;
extern struct fn_1_FA84_lbl_1_data_43B8 lbl_1_data_43B8;
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 lbl_801A6410;

void fn_1_FA84(void) {
    struct fn_1_FA84_lbl_1_data_43B8 *p_lbl_1_data_43B8;
    struct fn_1_FA84_lbl_1_bss_1148 *p_lbl_1_bss_1148;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;
    s32 v7;
    u32 v8;
    u32 t0, t1, t2;
    p_lbl_1_data_43B8 = (struct fn_1_FA84_lbl_1_data_43B8 *)&lbl_1_data_43B8;
    p_lbl_1_bss_1148 = (struct fn_1_FA84_lbl_1_bss_1148 *)&lbl_1_bss_1148;
    v1 = 0;
    v3 = 0;
    if ((s32)p_lbl_1_data_43B8->unk_13C > 0) {
    v0 = (u32)&lbl_801A6410;
    p_lbl_1_data_43B8->unk_13C = -1;
    v0 = *(u32 *)((u8 *)v0 + 0);
    v1 = (u32)((u8 *)(u32)p_lbl_1_data_43B8 + 104);
    v2 = p_lbl_1_bss_1148->unk_67C;
    v3 = 1472;
    t0 = fn_1_46B4(v0, v2, (u32)v1, v3);
    v0 = t0;
    }
    v4 = v0;
    v5 = v1;
    v6 = v2;
    v7 = v3;
    if ((s32)p_lbl_1_data_43B8->unk_140 > 0) {
    v4 = (u32)&lbl_801A6410;
    p_lbl_1_data_43B8->unk_140 = -1;
    v4 = *(u32 *)((u8 *)v4 + 0);
    v5 = (u32)((u8 *)(u32)p_lbl_1_data_43B8 + 104);
    v6 = p_lbl_1_bss_1148->unk_680;
    v7 = 1473;
    t1 = fn_1_46B4(v4, v6, (u32)v5, v7);
    v4 = t1;
    }
    v8 = v4;
    if ((s32)p_lbl_1_data_43B8->unk_144 > 0) {
    v8 = (u32)&lbl_801A6410;
    p_lbl_1_data_43B8->unk_144 = -1;
    v8 = *(u32 *)((u8 *)v8 + 0);
    t2 = fn_1_46B4(v8, p_lbl_1_bss_1148->unk_684, (u32)((u8 *)(u32)p_lbl_1_data_43B8 + 104), 1474);
    v8 = t2;
    }
}
/* fzgx:end fn_1_FA84 */

/* fzgx:begin fn_1_10138 */
void fn_1_10138(void) {
    Obj_1_bss_17C4_At0 *obj;
    u32 i;
    u32 count;

    lbl_1_bss_17B0 = 0;
    count = lbl_1_data_44F4.unk_0;
    obj = lbl_1_bss_17C4.unk_0;
    i = 0;
    while (i < count) {
        lbl_1_bss_17B0 += fn_80008E30(obj->unk_0);
        i++;
        obj++;
    }
}
/* fzgx:end fn_1_10138 */

/* fzgx:begin fn_1_101C0 */
u32 fn_1_101C0(void) {
    return lbl_1_bss_17B0;
}
/* fzgx:end fn_1_101C0 */

/* fzgx:begin fn_1_101D0 */
typedef struct {
    u8 pad_0[0x6];
    u16 unk_6;
    u8 pad_8[0x8];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u32 unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
} Fn_1_101D0_State;

extern u32 fn_80008E30(u32);

void fn_1_101D0(Fn_1_101D0_State *self) {
    Obj_1_bss_17C4_At0 *base;
    u32 count;
    u32 off;

    count = lbl_1_data_44F4.unk_0;
    base = lbl_1_bss_17C4.unk_0;

    if (self->unk_64 == 0) {
        self->unk_10++;
        off = self->unk_10 * 0x54;
        if (self->unk_10 < count) {
            self->unk_64 = fn_80008E30(*(u32 *)((u8 *)base + off));
            self->unk_12 = 5;
            self->unk_14 = self->unk_10;
            self->unk_6 = 0;
            self->unk_18 = 1;
        }
        return;
    }
    self->unk_18 = 0;
}
/* fzgx:end fn_1_101D0 */

/* fzgx:begin fn_1_10268 */
extern u32 fn_80008E30(u32);

typedef struct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
    f32 unk_10;
    f32 unk_14;
} Bss_1_17D0;

typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    f32 unk_1C;
    s16 unk_20;
} Copy_1_10268;

typedef struct {
    u8 pad_0[4];
    s16 unk_4;
    u8 pad_6[0x16];
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 pad_28[0x24];
    u32 unk_4C;
    u32 unk_50;
    u32 unk_54;
    f32 unk_58;
    s16 unk_5C;
    u8 pad_5E[0x6];
    s16 unk_64;
} Camera_1_10268;

void fn_1_10268(Camera_1_10268 *arg) {
    Obj_1_bss_17C4_At0 *e;
    Copy_1_10268 t;
    u32 n;
    u32 m;
    f32 a;
    f32 b;

    e = &lbl_1_bss_17C4.unk_0[arg->unk_4];
    t = *(Copy_1_10268 *)((u8 *)e + 8);

    n = fn_80008E30(e->unk_0);

    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_0 = lbl_1_rodata_4F4[0];
    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_4 = lbl_1_rodata_4E0[0];
    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_10 = lbl_1_rodata_4F4[0];
    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_14 = lbl_1_rodata_4E0[0] / (f32)((n * n) >> 2);
    a = (f32)n;
    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_C = a;
    ((Bss_1_17D0 *)&lbl_1_bss_17D0)->unk_8 = a;

    arg->unk_64 = fn_80008E30(e->unk_0);

    arg->unk_1C = t.unk_4;
    arg->unk_20 = t.unk_8;
    arg->unk_24 = t.unk_C;
    arg->unk_4C = t.unk_10;
    arg->unk_50 = t.unk_14;
    arg->unk_54 = t.unk_18;
    arg->unk_5C = t.unk_20;
    arg->unk_58 = t.unk_1C;
}
/* fzgx:end fn_1_10268 */

/* fzgx:begin fn_1_11ABC */
#include "dolphin/hw_regs.h"
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct {
    Vec3 v;              /* 0x00 */
    u8 pad_C[0x14];
} CameraData;            /* 32 bytes */

typedef struct {
    u8 unk_0;
    u8 unk_1;
    u8 pad_2[2];
    s16 unk_4;
    s16 unk_6;
    u8 pad_8[0xC];
    s16 unk_14;
    u8 pad_16[6];
    f32 unk_1C;
    u8 pad_20[0x14];
    Vec3 unk_34;
    u8 pad_40[0xC];
    Vec3 unk_4C;
    f32 unk_58;
    s16 unk_5C;
    u8 pad_5E[0x12];
    f32 unk_70;
    u8 pad_74[8];
    f32 unk_7C;
} LiveCamera;

extern void fn_1_862D4(s16, Vec3 *);
extern void fn_8006E2B0(void *, Vec3 *);

#pragma opt_propagation off
void fn_1_11ABC(LiveCamera *camera) {
    Vec3 first;
    Vec3 second;
    u8 mode = camera->unk_0;

    if (mode == 5 || mode <= 1 || mode == 2) {
        u32 value;
        u32 next = lbl_801A63C0 * 0x676A4B6Bu + 0x33CB;
        s16 result;

        value = (next << 1) >> 17;
        result = (s16)(value % 9);
        lbl_801A63C0 = next;
        camera->unk_14 = result;
        camera->unk_4 = result;
    }

    fn_1_862D4(camera->unk_6, &first);
    fn_1_8636C(camera->unk_6, &camera->unk_7C);
    fn_1_862A8(camera->unk_6, &camera->unk_70);

    camera->unk_34 = (*(CameraData (*)[])&lbl_1_data_4AA0)[camera->unk_4].v;

    {
        f32 m2, m1, m0;
        f32 *mtx = (f32 *)(LC_BASE + 0x0);
        m0 = first.x;
        m1 = first.y;
        m2 = first.z;
        mtx[3] = m0;
        mtx[7] = m1;
        mtx[11] = m2;
    }

    lbl_8006DC6C(&camera->unk_7C);
    lbl_8006E1B0(&camera->unk_34, &camera->unk_1C);
    fn_8006E2B0(&camera->unk_70, &second);

    camera->unk_4C = first;
    camera->unk_5C = (s16)-lbl_8006D24C(second.x, second.y);
    camera->unk_58 = 55.0f;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_11ABC */

/* fzgx:begin fn_1_12620 */
extern void OSPanic(u8 *file, int line, u8 *message, ...);
extern u32 fn_80008E30(u32);
extern u8 lbl_1_bss_17B4[12];
extern void fn_80083DB0(Obj_1_bss_3B30 *, void *);
extern u32 *fn_1_1304C(Obj_1_bss_3B30 *, u32);
extern u8 lbl_1_bss_1810[8984];
extern void fn_8000659C(void);
extern u32 OSIsThreadTerminated(u8 *);

extern void fn_1_6DD0(void *);
extern u32 *fn_1_1289C(u32 *);

// Prints the live-camera status text for the current camera event.
#pragma opt_common_subs off
void fn_1_12620(s32 arg0) {
    u8 *base = lbl_1_data_43B8;
    char buf[0x74];

    fn_80006E10((u32)(base + 0x280));
    if (*(s16 *)&lbl_1_bss_960 == 0xA) {
        sprintf(buf, (const char *)(base + 0x284), arg0);
        if (fn_1_465D0((s32)buf, 1) == -1) {
            sprintf(buf, (const char *)(base + 0x2A0));
            fn_1_465D0((s32)buf, 1);
        }
    } else if (*(s16 *)&lbl_1_bss_960 == 0xE) {
        if (lbl_1_bss_525C.unk_191 & 2) {
            switch (lbl_1_bss_525C.unk_192) {
            case 4:
                sprintf(buf, (const char *)(base + 0x2BC));
                break;
            case 3:
                sprintf(buf, (const char *)(base + 0x2D4));
                break;
            case 2:
                sprintf(buf, (const char *)(base + 0x2EC));
                break;
            default:
                sprintf(buf, (const char *)(base + 0x2EC));
                break;
            }
        } else {
            sprintf(buf, (const char *)(base + 0x304));
        }
        fn_1_465D0((s32)buf, 1);
    } else {
        sprintf(buf, (const char *)(base + 0x324), arg0);
        if (fn_1_465D0((s32)buf, 1) == -1) {
            sprintf(buf, (const char *)(base + 0x33C));
            fn_1_465D0((s32)buf, 1);
        }
    }
    if (arg0 == 0x32) {
        fn_80006E10((u32)(base + 0x350));
        return;
    }
    sprintf(buf, (const char *)(base + 0x354), arg0);
    if (fn_1_465D0((s32)buf, 1) == -1) {
        sprintf(buf, (const char *)(base + 0x364));
        fn_1_465D0((s32)buf, 1);
    }
    sprintf(buf, (const char *)(base + 0x374), arg0);
    if (fn_1_465D0((s32)buf, 1) == -1) {
        sprintf(buf, (const char *)(base + 0x388));
        fn_1_465D0((s32)buf, 1);
    }
    fn_80006E10((u32)(base + 0x350));
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_12620 */

/* fzgx:begin fn_1_12850 */
u8 fn_1_12850(void) {
    return lbl_1_bss_17B4[0];
}
/* fzgx:end fn_1_12850 */

/* fzgx:begin fn_1_12860 */
// Initializes the live-camera state before returning the active camera result.
u32 fn_1_12860(u32 arg0, u32 arg1) {
    u32 *state = (u32 *)lbl_1_bss_1800;

    state[0] = arg0;
    state[1] = arg1;
    state[2] = 0;
    return fn_1_1289C(state)[0];
}
/* fzgx:end fn_1_12860 */

/* fzgx:begin fn_1_12F78 */
u32 fn_1_12F78(void *arg0, u32 arg1) {
    fn_80083DB0(&lbl_1_bss_3B30, arg0);
    lbl_1_bss_3B30.unk_80 = arg1;
    lbl_1_bss_3B30.unk_84 = 0;
    return *fn_1_1304C(&lbl_1_bss_3B30, 0);
}
/* fzgx:end fn_1_12F78 */

/* fzgx:begin fn_1_13018 */
u32 fn_1_13018(void) {
    fn_8000659C();
    return OSIsThreadTerminated(lbl_1_bss_1810) == 0;
}
/* fzgx:end fn_1_13018 */
