#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/enemy_ctrl.h"

extern u32 lbl_1_bss_7AC48[5];
extern void *lbl_801A6410;
extern void fn_1_46B4(void *, u32, void *, u32);
extern void fn_1_C489C(void);
extern u32 lbl_1_bss_7AC54[4];
extern u8 lbl_1_bss_7AC90[12];
extern u32 lbl_1_rodata_5D40[7];
extern u32 fn_1_5910(void *);
extern u8 fn_1_86810(void *);
extern u32 fn_1_3F7E0(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(u32);
extern const f32 lbl_1_rodata_5C3C;
extern const f32 lbl_1_rodata_5D18;
extern void fn_1_496FC(f32, f32);
extern void fn_1_495C8(u32);
extern void fn_1_49728(u32);
extern void fn_1_4AE0C(void *, ...);
extern const f32 lbl_1_rodata_5D5C;
extern const f32 lbl_1_rodata_5D60;
extern f32 lbl_1_rodata_26F8[22];
extern const f32 lbl_1_rodata_5D64;
extern const f32 lbl_1_rodata_5D68;
extern void fn_1_51E60(void *);
extern const f32 lbl_1_rodata_5D6C;
extern void fn_1_C8DC0(void);
extern void fn_80008E84(u32);
extern const f32 lbl_1_rodata_5D88;
extern const f32 lbl_1_rodata_5D8C;
extern void fn_1_4955C(f32, f32);
extern const f32 lbl_1_rodata_5CD4;
extern const f32 lbl_1_rodata_5D90;
extern void fn_1_4966C(f32, f32);

/* fzgx:begin fn_1_C47B4 */
void fn_1_C47B4(void) {
    u32 *p = lbl_1_bss_7AC48;

    if (p[0] != 0) {
        fn_1_46B4(lbl_801A6410, p[0], lbl_1_data_3D234, 0x4af);
    }
    fn_1_46B4(lbl_801A6410, p[4], lbl_1_data_3D234, 0x4b0);
    fn_1_46B4(lbl_801A6410, p[3], lbl_1_data_3D234, 0x4b1);
    fn_1_46B4(lbl_801A6410, p[2], lbl_1_data_3D234, 0x4b2);
    p[0] = 0;
    p[4] = 0;
    p[3] = 0;
    p[2] = 0;
}
/* fzgx:end fn_1_C47B4 */

/* fzgx:begin fn_1_C487C */
void fn_1_C487C(void) {
    fn_1_C489C();
}
/* fzgx:end fn_1_C487C */

/* fzgx:begin fn_1_C6ED4 */
typedef struct Fn1C6ED4Data {
    u32 flags;
    f32 value_4;
    f32 value_8;
    f32 value_c;
    f32 value_10;
    f32 value_14;
} Fn1C6ED4Data;

typedef struct Fn1C6ED4Enemy {
    u32 flags;
    u8 pad_4[0x1f0];
    f32 output_1f4;
    f32 output_1f8;
    f32 output_1fc;
    f32 output_200;
    f32 output_204;
    u8 pad_208[0x27c];
    Fn1C6ED4Data *data;
} Fn1C6ED4Enemy;

void fn_1_C6ED4(Fn1C6ED4Enemy *self) {
    Fn1C6ED4Data *data = self->data;

    self->output_1fc = data->value_4;
    self->output_1f4 = data->value_8;
    self->output_200 = data->value_c;
    self->output_204 = data->value_10;
    self->output_1f8 = data->value_14;

    if (data->flags >> 31) {
        self->flags |= 0x40;
        data->flags &= ~((u32)1 << 31);
    }
    if ((data->flags >> 30) & 1) {
        self->flags |= 0x1000;
        data->flags &= ~((u32)1 << 30);
    }
    if ((data->flags >> 20) & 1) {
        self->flags |= 0x8;
        data->flags &= ~((u32)1 << 20);
    }
}
/* fzgx:end fn_1_C6ED4 */

/* fzgx:begin fn_1_C6F70 */
u32 fn_1_C6F70(void) {
    return lbl_1_bss_7AC54[0];
}
/* fzgx:end fn_1_C6F70 */

/* fzgx:begin fn_1_C6F80 */
void fn_1_C6F80(u8 value) {
    lbl_1_bss_7AC90[0] = value;
}
/* fzgx:end fn_1_C6F80 */

/* fzgx:begin fn_1_C7224 noprologue */
#include "types.h"

extern s16 lbl_1_bss_960;
extern s16 fn_1_3F0C8(void);
extern int fn_1_485A8(int);
extern void fn_1_C771C(void);
extern u32 fn_1_58C4(void);
extern void fn_1_C72D4(void);
extern void fn_1_C742C(void);

typedef struct {
    u8 padding[0x94];
    u32 flags;
} Fn1C7224State;

extern Fn1C7224State lbl_1_bss_8B3A0;

void fn_1_C7224(void) {
    if (lbl_1_bss_960 == 2 &&
        (fn_1_3F0C8() == 0x25 || fn_1_3F0C8() == 0x26)) {
        return;
    }

    if (fn_1_485A8(0x94) != 0) {
        if (lbl_1_bss_8B3A0.flags & 0x40000000) {
            fn_1_C771C();
        } else if (fn_1_58C4() == 1) {
            if (!(lbl_1_bss_8B3A0.flags & 0x40000000)) {
                fn_1_C72D4();
            } else {
                fn_1_C771C();
            }
        } else {
            fn_1_C742C();
        }
    }
}
/* fzgx:end fn_1_C7224 */

/* fzgx:begin fn_1_C771C noprologue */
#include "types.h"

typedef struct EnemyCtrl {
    u8 pad_000[0x118];
    int field_118;
    u8 pad_11c[0xd0];
    u8 field_1ec;
    u8 field_1ed;
    u16 field_1ee;
} EnemyCtrl;

extern s16 camera_get_mode(void);
extern EnemyCtrl *fn_1_8627C(int);
extern u32 fn_1_58C4(void);
extern void fn_1_52070(int);
extern void fn_1_CA690(int, int, int);
extern void fn_1_52088(void);
extern void fn_1_CD51C(int);
extern void fn_1_CD7BC(int);
extern void fn_1_C8DC0(int);
extern void fn_1_CADC4(int);
extern u32 fn_1_3F114(void);
extern void fn_1_CC280(int, int, int, u32);
extern u32 fn_1_CFA0C(int, int);
extern void fn_1_CBC24(int, int, u8, u8, u16);
extern int fn_1_5910(void);
extern void fn_1_CB424(int, int, int);
extern void fn_1_CB028(int, int);
extern void fn_1_CAB38(int, int, int);

void fn_1_C771C(void) {
    int mode;
    EnemyCtrl *ctrl;
    int value;

    mode = camera_get_mode();
    if (mode == -1 || mode < 0) {
        return;
    }
    ctrl = fn_1_8627C(mode);
    if (ctrl == 0) {
        return;
    }
    if (fn_1_58C4() == 1) {
        fn_1_52070(0x60);
    }
    fn_1_CA690(mode, 0x18, 0x19c);
    fn_1_52088();
    if (fn_1_58C4() == 1) {
        fn_1_52070(0x140);
    }
    fn_1_CD51C(mode);
    fn_1_CD7BC(mode);
    fn_1_52088();
    if (fn_1_58C4() == 1) {
        fn_1_52070(0x220);
    }
    value = 0;
    fn_1_C8DC0(mode);
    fn_1_CADC4(mode);
    fn_1_CC280(0x19a, 0x18, ctrl->field_118 + 1, fn_1_3F114() & 0xff);
    if ((fn_1_CFA0C(0x268, 0x43) & 0xff) != 0) {
        value = 0x25;
    }
    fn_1_CBC24(0x1bc, value + 0x43, ctrl->field_1ec,
               ctrl->field_1ed, ctrl->field_1ee);
    fn_1_CB424(0x269, value + 0x6e, fn_1_5910());
    fn_1_CB028(0x269, value + 0x96);
    fn_1_CAB38(mode, 0x268, value);
    fn_1_52088();
}
/* fzgx:end fn_1_C771C */

/* fzgx:begin fn_1_CA218 */
typedef struct EnemyCtrl_CA218 {
    u32 value;
    u8 pad4[2];
    s16 state;
    u32 action;
} EnemyCtrl_CA218;

void fn_1_CA218(EnemyCtrl_CA218 *self) {
    u32 actions[7];

    actions[0] = lbl_1_rodata_5D40[0];
    actions[1] = lbl_1_rodata_5D40[1];
    actions[2] = lbl_1_rodata_5D40[2];
    actions[3] = lbl_1_rodata_5D40[3];
    actions[4] = lbl_1_rodata_5D40[4];
    actions[5] = lbl_1_rodata_5D40[5];
    actions[6] = lbl_1_rodata_5D40[6];

    if (self->state < 14) {
        self->action = actions[self->state / 2];
        self->state = self->state + 1;
    } else {
        self->value = 0;
    }
}
/* fzgx:end fn_1_CA218 */

/* fzgx:begin fn_1_CA2A4 */
typedef struct {
    u32 x[22];
} fn_1_CA2A4_LocalData;

void fn_1_CA2A4(void *self) {
    fn_1_CA2A4_LocalData local;
    s32 count;
    s32 max;

    if (((((u32 *)&lbl_1_data_3D544)[fn_1_5910(self)] >> 29) & 1) == 0) {
        return;
    }
    count = (u8)fn_1_86810(self) + 1;
    max = fn_1_3F7E0();
    if (count > max) {
        return;
    }
    fn_1_49410();
    fn_1_494DC(0xc);
    fn_1_496FC(lbl_1_rodata_5C3C, lbl_1_rodata_5D18);
    fn_1_495C8(1);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, count);
    fn_1_49410();
    fn_1_494DC(0xd);
    fn_1_496FC(lbl_1_rodata_5D5C, lbl_1_rodata_5D60);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, max);
    local = *(fn_1_CA2A4_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9429;
    ((f32 *)local.x)[1] = lbl_1_rodata_5D64;
    ((f32 *)local.x)[2] = lbl_1_rodata_5D68;
    fn_1_51E60(&local.x[0]);
    local = *(fn_1_CA2A4_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9405;
    ((f32 *)local.x)[1] = lbl_1_rodata_5D6C;
    ((f32 *)local.x)[2] = lbl_1_rodata_5D68;
    fn_1_51E60(&local.x[0]);
}
/* fzgx:end fn_1_CA2A4 */

/* fzgx:begin fn_1_CA690 */
extern u32 fn_1_5910(void *);
extern u8 fn_1_86810(void *);
extern u32 fn_1_3F7E0(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(u32);
extern void fn_1_496FC(f32, f32);
extern void fn_1_49728(u32);
extern void fn_1_4AE0C(void *, ...);
extern f32 lbl_1_rodata_26F8[22];
extern void fn_1_51E60(void *);

typedef struct {
    u32 x[22];
} fn_1_CA690_LocalData;

void fn_1_CA690(void *self, s32 arg1, s32 arg2) {
    fn_1_CA690_LocalData local;
    s32 count;
    s32 max;

    if (((((u32 *)&lbl_1_data_3D544)[fn_1_5910(self)] >> 29) & 1) == 0) {
        return;
    }
    count = (u8)fn_1_86810(self) + 1;
    fn_1_49410();
    fn_1_494DC(0xc);
    fn_1_496FC(arg1, arg2);
    fn_1_4955C(lbl_1_rodata_5D88, lbl_1_rodata_5D8C);
    fn_1_4966C(lbl_1_rodata_5CD4, lbl_1_rodata_5D90);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, count);
    max = fn_1_3F7E0();
    fn_1_49410();
    fn_1_494DC(0xd);
    fn_1_496FC(arg1 + 0x5c, arg2 + 0x1a);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, max);
    local = *(fn_1_CA690_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9429;
    ((f32 *)local.x)[1] = arg1 + 0x4e;
    ((f32 *)local.x)[2] = arg2 + 0x1a;
    fn_1_51E60(&local.x[0]);
    local = *(fn_1_CA690_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9405;
    ((f32 *)local.x)[1] = arg1 + 0x4e;
    ((f32 *)local.x)[2] = arg2 + 0xd;
    fn_1_51E60(&local.x[0]);
}
/* fzgx:end fn_1_CA690 */

/* fzgx:begin fn_1_CADC4 noprologue */
#include "types.h"

struct fn_1_CADC4_Copy88 { u32 a[22]; };
struct fn_1_CADC4_lbl_1_data_3D544 {
    u32 unk_0[1];
};
extern f32 lbl_1_rodata_5CD4;
extern f32 lbl_1_rodata_5D1C;
extern f32 lbl_1_rodata_5D90;
extern f32 lbl_1_rodata_5DDC;
extern f32 lbl_1_rodata_5DE0;
extern f32 lbl_1_rodata_5DE4;
extern struct fn_1_CADC4_lbl_1_data_3D544 lbl_1_data_3D544;
extern u32 lbl_1_data_3D57C;
extern u32 lbl_1_rodata_26F8;
extern f32 fn_1_8652C(int);
extern u32 fn_1_5910(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(s16);
extern void fn_1_496FC(f32, f32);
extern void fn_1_4966C(f32, f32);
extern void fn_1_49728(u8);
extern void fn_1_4AE0C(const char *, ...);
extern void fn_1_51E60(u32);

struct FzgxCopy_88 { u32 words[22]; };
void fn_1_CADC4(s32 arg0) {
    struct FzgxCopy_88 loc_8;
    s32 sp4;
    s32 temp_r31;

    temp_r31 = (s32) fn_1_8652C((s32)(arg0));
    if (((*(u32 *)&((&lbl_1_data_3D544)[fn_1_5910()])) >> 0x1BU) & 1) {
        fn_1_49410();
        fn_1_494DC((s16)(0xF));
        fn_1_496FC((f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5D1C) + 0)), (f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5DDC) + 0)));
        fn_1_4966C((f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5CD4) + 0)), (f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5D90) + 0)));
        fn_1_49728((u8)(1U));
        fn_1_4AE0C((const char *)((s8 *) &lbl_1_data_3D57C), temp_r31);
        loc_8 = *(const struct FzgxCopy_88 *)((((s32)(((u8 *)(&lbl_1_rodata_26F8) + -4))) + 4));
        loc_8.words[0] = 0x9401;
        (*(f32 *)((u8 *)(&loc_8) + 4)) = *(f32 *)((u8 *)(&lbl_1_rodata_5DE0) + 0);
        (*(f32 *)((u8 *)(&loc_8) + 8)) = *(f32 *)((u8 *)(&lbl_1_rodata_5DE4) + 0);
        fn_1_51E60((u32)((u32)(&loc_8)));
    }
}
/* fzgx:end fn_1_CADC4 */

/* fzgx:begin fn_1_CAEBC noprologue */
#include "types.h"
#include "font.h"

struct fn_1_CAEBC_Copy88 { u32 a[22]; };
struct fn_1_CAEBC_lbl_1_data_3D544 {
    u32 unk_0[1];
};
extern f32 lbl_1_rodata_5CFC;
extern f32 lbl_1_rodata_5D90;
extern f32 lbl_1_rodata_5DE8;
extern f32 lbl_1_rodata_5DEC;
extern f64 lbl_1_rodata_5C00;
extern struct fn_1_CAEBC_lbl_1_data_3D544 lbl_1_data_3D544;
extern u32 lbl_1_data_3D57C;
extern u32 lbl_1_rodata_26F8;
extern f32 fn_1_8652C(int);
extern u32 fn_1_5910(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(s16);
extern void fn_1_496FC(f32, f32);
extern void fn_1_4955C(f32, f32);
extern void fn_1_4966C(f32, f32);
extern void fn_1_4AE0C(const char *, ...);
extern int fn_1_4F734(FontDrawPacket *);

struct FzgxCopy_88 { u32 words[22]; };
void fn_1_CAEBC(s32 arg0, s32 arg1, s32 arg2) {
    FontDrawPacket loc_8;
    s32 sp4;
    s32 temp_r31;

    temp_r31 = (s32) fn_1_8652C((s32)(arg0));
    if (((*(u32 *)&((&lbl_1_data_3D544)[fn_1_5910()])) >> 0x1BU) & 1) {
        fn_1_49410();
        fn_1_494DC((s16)(0xF));
        fn_1_496FC((f32)((f32) arg1), (f32)((f32) arg2));
        fn_1_4955C((f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5DE8) + 0)), (f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5DEC) + 0)));
        fn_1_4966C((f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5CFC) + 0)), (f32)(*(f32 *)((u8 *)(&lbl_1_rodata_5D90) + 0)));
        fn_1_4AE0C((const char *)((s8 *) &lbl_1_data_3D57C), temp_r31);
        loc_8 = *(const FontDrawPacket *)((((s32)(((u8 *)(&lbl_1_rodata_26F8) + -4))) + 4));
        loc_8.image = 0x9401;
        loc_8.x = (f32) (arg1 + 0x45);
        loc_8.y = (f32) (arg2 + 0xA);
        fn_1_4F734((FontDrawPacket *)(&loc_8));
    }
}
/* fzgx:end fn_1_CAEBC */

/* fzgx:begin fn_1_CB404 */
// Set the state flag for the selected enemy-control entry.
void fn_1_CB404(u8 value) {
    (&lbl_1_bss_7ACA0.unk_8)[value * 0xc] = 0xf;
}
/* fzgx:end fn_1_CB404 */

/* fzgx:begin fn_1_CC27C */
// fn_1_CC27C: empty in retail (single blr).
void fn_1_CC27C(void) {
}
/* fzgx:end fn_1_CC27C */

/* fzgx:begin fn_1_CD51C */
extern u32 fn_1_5910(void *object);
extern void *fn_1_8627C(void *object);
extern void *fn_1_4DF60(void);
extern const f32 lbl_1_rodata_5C3C;
extern const f32 lbl_1_rodata_5C40;
extern const f32 lbl_1_rodata_5F18;
extern u32 fn_1_58C4(void);
extern const f32 lbl_1_rodata_5CFC;
extern const f32 lbl_1_rodata_5E0C;
extern u32 lbl_1_rodata_5F14;
extern const f64 lbl_1_rodata_5C00;
extern void fn_1_CD6C0(void);
extern f32 fn_1_519FC(f32 value);
extern f32 fn_1_51AC0(f32 value);

extern Obj_1_data_3D544 lbl_1_data_3D544;

typedef struct {
    u8 pad_0[0x6];
    u16 unk_6;
    u32 unk_8;
    f32 unk_c;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1c;
    u8 pad_20[0x18];
    u32 unk_38;
    f32 unk_3c;
    u32 unk_40;
    u8 pad_44[0x1c];
    void *unk_60;
    u8 pad_64[0x14];
    void (*unk_78)(void);
} Fn1Cd51cObject;

void fn_1_CD51C(void *object) {
    u32 index;
    void *actor;
    Fn1Cd51cObject *state;
    f32 factor;

    index = fn_1_5910(object);
    if (((((u32 *)&lbl_1_data_3D544)[index] >> 19) & 1) == 0) {
        return;
    }

    actor = fn_1_8627C(object);
    if (actor == 0) {
        return;
    }
    if (*(s32 *)((u8 *)actor + 0x10c) == 0) {
        return;
    }
    if (*(s32 *)((u8 *)actor + 0x110) == 0) {
        return;
    }

    state = fn_1_4DF60();
    if (state == 0) {
        return;
    }

    state->unk_8 = 0x9435;
    state->unk_c = lbl_1_rodata_5C3C;
    state->unk_10 = lbl_1_rodata_5C40;
    state->unk_14 = lbl_1_rodata_5F18;

    if (fn_1_58C4() == 1) {
        factor = lbl_1_rodata_5CFC;
    } else {
        factor = lbl_1_rodata_5E0C;
    }
    state->unk_18 *= factor;

    if (fn_1_58C4() == 1) {
        factor = lbl_1_rodata_5CFC;
    } else {
        factor = lbl_1_rodata_5E0C;
    }
    state->unk_1c *= factor;

    state->unk_38 = 10;
    state->unk_40 = lbl_1_rodata_5F14;

    if (fn_1_58C4() == 1 && (s32)lbl_1_bss_4E6A8 != 0) {
        u32 value = state->unk_38 | 0x8000000;
        state->unk_38 = value;
        state->unk_3c = (f32)(s32)lbl_1_bss_4E6AC;
    }

    state->unk_6 = 0;
    state->unk_78 = fn_1_CD6C0;
    state->unk_60 = object;
    state->unk_c = fn_1_519FC(state->unk_c);
    state->unk_10 = fn_1_51AC0(state->unk_10);
}
/* fzgx:end fn_1_CD51C */

/* fzgx:begin fn_1_CD6C0 */
extern const f32 lbl_1_rodata_5CFC;
extern const f32 lbl_1_rodata_5D90;
extern u16 fn_1_8664C(void *object);
extern void *fn_1_8627C(void *object);
extern u32 fn_1_864E8(void *object);

typedef struct fn_1_CD6C0_object {
    s32 flags;
    u16 pad4;
    s16 state;
    u8 pad8[0x2c];
    f32 value;
    u8 pad38[0x28];
    void *controller;
} fn_1_CD6C0_object;

typedef struct fn_1_CD6C0_target {
    u8 pad0[0x10c];
    s32 flags;
} fn_1_CD6C0_target;

#pragma opt_propagation off
void fn_1_CD6C0(fn_1_CD6C0_object *object) {
    s32 state;
    s32 out;
    void *controller;
    fn_1_CD6C0_target *target;

    state = object->state;
    if (state + 1 > 0x3b) {
        out = 0;
    } else {
        state++;
        out = 0x3b;
        if (state >= 0) {
            out = state;
        }
    }
    object->state = out;
    if (object->state < 0x1e) {
        object->value = lbl_1_rodata_5CFC;
    } else {
        object->value = lbl_1_rodata_5D90;
    }
    if (fn_1_8664C(object->controller) != 0) {
        object->value = lbl_1_rodata_5D90;
        object->flags = 0;
    }
    if (object->state == 0x1e) {
        controller = object->controller;
        target = fn_1_8627C(controller);
        if (target != 0) {
            if (target->flags == 0) {
                object->flags = 0;
            }
            if ((fn_1_864E8(controller) & 0x10010880) != 0) {
                object->flags = 0;
            }
        }
    }
}
#pragma opt_propagation reset
/* fzgx:end fn_1_CD6C0 */

/* fzgx:begin fn_1_CFA4C noprologue */
#include "types.h"
#include "font.h"

struct fn_1_CFA4C_Copy88 { u32 a[22]; };

extern f32 lbl_1_rodata_6010;
extern f64 lbl_1_rodata_5C00;
extern int fn_1_4F734(FontDrawPacket *);
extern u32 lbl_1_rodata_26F8;
extern void fn_1_52070(u32);
extern void fn_1_520A0(void);
extern void fn_1_520CC(void);

void fn_1_CFA4C(u32 arg0, u32 arg1) {
    f32 v0;
    u32 v1;
    f32 v2;
    FontDrawPacket loc_8;
    /* frame */
    fn_1_520A0();
    fn_1_52070(640);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v0 = (f32)(s32)(arg0 + 304);
    v1 = (0x10000 - 27620);
    loc_8.image = v1;
    v2 = (f32)(s32)(arg1 - 11);
    loc_8.x = v0;
    loc_8.y = v2;
    loc_8.z = lbl_1_rodata_6010;
    loc_8.flags = 7;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    fn_1_520CC();
}
/* fzgx:end fn_1_CFA4C */

/* fzgx:begin fn_1_D0728 */
#pragma opt_propagation off
void fn_1_D0728(u32 arg0, u32 arg1) {
    u32 *data;
    u32 *state;
    u32 value;

    value = 0xfffb8004;
    data = (u32 *)&lbl_1_data_3D544;
    state = (u32 *)&lbl_1_bss_7ACA0;

    data[0] = value;
    state[0] = 0;
    state[1] = 0;
    ((u8 *)state)[0x8] = 0;
    ((u8 *)state)[0x9] = 0;
    data[1] = value;
    state[3] = 0;
    state[4] = 0;
    ((u8 *)state)[0x14] = 0;
    ((u8 *)state)[0x15] = 0;
    data[2] = value;
    state[6] = 0;
    state[7] = 0;
    ((u8 *)state)[0x20] = 0;
    ((u8 *)state)[0x21] = 0;
    data[3] = value;
    state[9] = 0;
    state[10] = 0;
    ((u8 *)state)[0x2c] = 0;
    ((u8 *)state)[0x2d] = 0;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_D0728 */

/* fzgx:begin fn_1_D0790 */
void fn_1_D0790(void) {
    u32 *p = (u32 *)&lbl_1_data_3D544;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
}
/* fzgx:end fn_1_D0790 */

/* fzgx:begin fn_1_D07AC */
// Stores a value in the indexed enemy-control slot.
void fn_1_D07AC(u32 index, u32 value) {
    u32* slots = &lbl_1_bss_7ACA0.unk_0;
    slots[(index & 0xff) * 3] = value;
}
/* fzgx:end fn_1_D07AC */

/* fzgx:begin fn_1_D07C4 noprologue */
#include "types.h"

struct fn_1_D07C4_lbl_1_bss_7ACA0_0_E12 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x4];
};
struct fn_1_D07C4_lbl_1_bss_7ACA0 {
    struct fn_1_D07C4_lbl_1_bss_7ACA0_0_E12 unk_0[1];
};

extern struct fn_1_D07C4_lbl_1_bss_7ACA0 lbl_1_bss_7ACA0;

void fn_1_D07C4(u32 arg0, u32 arg1) {
    lbl_1_bss_7ACA0.unk_0[(arg0 & 0xFF)].unk_4 = arg1;
}
/* fzgx:end fn_1_D07C4 */

/* fzgx:begin fn_1_D0D68 */
void fn_1_D0D68(void) {
    fn_1_C8DC0();
}
/* fzgx:end fn_1_D0D68 */

/* fzgx:begin fn_1_D0D88 */
u32 fn_1_D0D88(void) {
    return lbl_1_data_3D648.unk_0;
}
/* fzgx:end fn_1_D0D88 */

/* fzgx:begin fn_1_D0D98 */
u16* fn_1_D0D98(void) {
    return &lbl_1_data_3D648.unk_4;
}
/* fzgx:end fn_1_D0D98 */

/* fzgx:begin fn_1_D0DA8 */
// Return the address of the object's 16-bit field at offset 0x6.
u8* fn_1_D0DA8(void) {
    return (u8*)&lbl_1_data_3D648.unk_6;
}
/* fzgx:end fn_1_D0DA8 */

/* fzgx:begin fn_1_D0DB8 */
// Returns the byte address of the object's field at offset 0x8.
u8* fn_1_D0DB8(void) {
    return (u8*)&lbl_1_data_3D648.unk_8;
}
/* fzgx:end fn_1_D0DB8 */

/* fzgx:begin fn_1_D0DC8 */
u8* fn_1_D0DC8(void) {
    return (u8*)&lbl_1_data_3D648 + 0xc;
}
/* fzgx:end fn_1_D0DC8 */

/* fzgx:begin fn_1_D0DD8 */
// Return the address of the enemy-control value at offset 0x10.
u8* fn_1_D0DD8(void) {
    return (u8*)&lbl_1_data_3D648.unk_10;
}
/* fzgx:end fn_1_D0DD8 */

/* fzgx:begin fn_1_D0DE8 */
// Return the address of the object's field at offset 0x12.
u8* fn_1_D0DE8(void) {
    return (u8*)&lbl_1_data_3D648.unk_12;
}
/* fzgx:end fn_1_D0DE8 */

/* fzgx:begin fn_1_D0DF8 */
// Return the enemy-control field at offset 0x14.
u16* fn_1_D0DF8(void) {
    return &lbl_1_data_3D648.unk_14;
}
/* fzgx:end fn_1_D0DF8 */

/* fzgx:begin fn_1_D0E08 */
// Return the address of the enemy-control field at offset 0x16.
u8* fn_1_D0E08(void) {
    return (u8*)&lbl_1_data_3D648.unk_16;
}
/* fzgx:end fn_1_D0E08 */

/* fzgx:begin fn_1_D0E18 */
// Return the address of the enemy-control field at offset 0x18.
u16* fn_1_D0E18(void) {
    return &lbl_1_data_3D648.unk_18;
}
/* fzgx:end fn_1_D0E18 */

/* fzgx:begin fn_1_D0E28 */
// Return the enemy-control data block.
Obj_1_data_3D648* fn_1_D0E28(void) {
    return &lbl_1_data_3D648;
}
/* fzgx:end fn_1_D0E28 */

/* fzgx:begin fn_1_D0E34 */
// Returns the status-byte array beginning at the shared enemy data block.
u8* fn_1_D0E34(void) {
    return &lbl_1_data_3D648.unk_20;
}
/* fzgx:end fn_1_D0E34 */

/* fzgx:begin fn_1_D0E44 */
// Return the address of the enemy controller's status byte.
u8* fn_1_D0E44(void) {
    return &lbl_1_data_3D648.unk_21;
}
/* fzgx:end fn_1_D0E44 */

/* fzgx:begin fn_1_D0E54 */
// Returns the address of this object's byte flag.
u8* fn_1_D0E54(void) {
    return &lbl_1_data_3D648.unk_22;
}
/* fzgx:end fn_1_D0E54 */

/* fzgx:begin fn_1_D0E64 */
// Returns the address of the enemy-control byte at offset 0x23.
u8* fn_1_D0E64(void) {
    return &lbl_1_data_3D648.unk_23;
}
/* fzgx:end fn_1_D0E64 */

/* fzgx:begin fn_1_D0E74 noprologue */
#include "types.h"

struct Sig_fn_8003432C_fn_8003432C_Arg2 {
    u32 unk_0;
};

struct Sig_GXPeekZ_GXPeekZ_Arg2 {
    u32 unk_0;
};

struct fn_1_D0E74_lbl_1_data_3D648 {
    u8 pad_0[0x4];
    u16 unk_4;
    u16 unk_6;
    u16 unk_8;
    u8 pad_A[0x16];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
};
struct fn_1_D0E74_lbl_1_rodata_6080 {
    f64 unk_0;
};
extern f32 lbl_1_rodata_6078;
extern struct fn_1_D0E74_lbl_1_data_3D648 lbl_1_data_3D648;
extern struct fn_1_D0E74_lbl_1_rodata_6080 lbl_1_rodata_6080;
extern void fn_80034200(u32);
extern u32 fn_8003432C(u32, u32, struct Sig_fn_8003432C_fn_8003432C_Arg2 *);
extern u32 GXPeekZ(u32, u32, struct Sig_GXPeekZ_GXPeekZ_Arg2 *);
extern u16 fn_1_A5DB0(void);


void fn_1_D0E74(void) {
    fn_80034200((u32)(2U));
    fn_8003432C((u32)((u32) lbl_1_data_3D648.unk_4), (u32)((u32) lbl_1_data_3D648.unk_6), (struct Sig_fn_8003432C_fn_8003432C_Arg2 *)((struct Sig_fn_8003432C_fn_8003432C_Arg2 *) ((u8 *)((u8 *)(&lbl_1_data_3D648) + 28))));
    lbl_1_data_3D648.unk_20 = (u8) ((u32) (*(u32 *)((u8 *)(&lbl_1_data_3D648) + 28)) >> 0x18U);
    lbl_1_data_3D648.unk_21 = (u8) ((u32) (*(u32 *)((u8 *)(&lbl_1_data_3D648) + 28)) >> 0x10U);
    lbl_1_data_3D648.unk_22 = (u8) ((u32) (*(u32 *)((u8 *)(&lbl_1_data_3D648) + 28)) >> 8U);
    lbl_1_data_3D648.unk_23 = (u8) (*(u32 *)((u8 *)(&lbl_1_data_3D648) + 28));
    GXPeekZ((u32)((u32) lbl_1_data_3D648.unk_4), (u32)((u32) lbl_1_data_3D648.unk_6), (struct Sig_GXPeekZ_GXPeekZ_Arg2 *)((struct Sig_GXPeekZ_GXPeekZ_Arg2 *) ((u8 *)((u8 *)(&lbl_1_data_3D648) + 12))));
    lbl_1_data_3D648.unk_8 = (u16) (s32) (((*(f32 *)((u8 *)(&lbl_1_rodata_6078) + 0)) * (f32) lbl_1_data_3D648.unk_6) / (f32) fn_1_A5DB0());
}
/* fzgx:end fn_1_D0E74 */

/* fzgx:begin fn_1_D2F50 */
// Stores the initialized enemy-control handle for later subsystem updates.
void fn_1_D2F50(void) {
    u32 fn_80008E84(u32);

    lbl_1_data_3D928.unk_0 = fn_80008E84(lbl_1_data_3D924);
}
/* fzgx:end fn_1_D2F50 */

/* fzgx:begin fn_1_D2F84 */
void fn_1_D2F84(void) {
    fn_80008E84(lbl_1_data_3D928.unk_0);
}
/* fzgx:end fn_1_D2F84 */
