#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/effect_car.h"

extern void fn_1_6F90C(void *arg0, void *arg1);
extern s16 fn_1_72318(void);
extern void fn_1_71D0C(void *arg0, void *arg1);

extern void *lbl_801A6410;
extern void fn_1_46B4(u32 value, void *field, u8 *data, s32 code);

/* fzgx:begin fn_1_680F8 */
extern u32 fn_1_4630(u32 value, u32 size, u8 *data, s32 code);
extern void fn_1_862D4(s16 value, void *result);
extern void fn_1_58E3C(void *entry);
extern u32 fn_1_58C4(void);
extern u8 *memset(u8 *dst, int value, u32 size);
extern void *lbl_801A6410;
extern s8 lbl_1_bss_6C878[];

typedef struct Fn1_680F8Arg {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1a;
    u8 pad_1c[0x18];
    u32 unk_34;
    u8 *unk_38;
    u8 unk_3c[4];
} Fn1_680F8Arg;

typedef struct Fn1_680F8Entry {
    u8 pad_00[0x0c];
    u16 unk_0c;
    u8 pad_0e[0x0a];
    s16 unk_18;
    u8 pad_1a[0x1e];
    u8 *unk_38;
    u8 pad_3c[0xac];
} Fn1_680F8Entry;

void fn_1_680F8(Fn1_680F8Arg *arg) {
    u8 *p;
    Fn1_680F8Entry entry;
    u32 n;
    s32 i;

    arg->unk_1a = 0xffff;
{
    u8 *base;
    base = arg->unk_38;
    arg->unk_34 = fn_1_4630((u32)lbl_801A6410, 0x300, lbl_1_data_1D8A8, 0xc7);
    fn_1_862D4(arg->unk_18, arg->unk_3c);
    memset((u8 *)&entry, 0, 0xe8);
    entry.unk_18 = arg->unk_18;
    entry.unk_0c = 4;
    p = base;
}
    for (i = 0; i < 4; i++) {
        entry.unk_38 = p + 0x3b4;
        fn_1_58E3C(&entry);
        p += 0x30;
    }
    n = fn_1_58C4();
    for (i = 0; i < n; i++) {
        lbl_1_bss_6C878[i * 24] = -1;
    }
}
/* fzgx:end fn_1_680F8 */

/* fzgx:begin fn_1_68248 */
typedef struct Fn1_68248Arg {
    u8 pad0[0x34];
    void *unk_34;
} Fn1_68248Arg;

// Register the effect resource with the shared effect manager.
void fn_1_68248(Fn1_68248Arg *arg) {
    fn_1_46B4((u32)lbl_801A6410, arg->unk_34, lbl_1_data_1D8A8, 0xe2);
}
/* fzgx:end fn_1_68248 */

/* fzgx:begin fn_1_68B68 */
// Stub function that immediately returns.
void fn_1_68B68(void) {
}
/* fzgx:end fn_1_68B68 */

/* fzgx:begin fn_1_69BBC */
typedef struct EffectCar {
    u8 pad_00[0x1a];
    u16 field_1a;
} EffectCar;

void fn_1_69BBC(EffectCar *car) {
    car->field_1a = 0xffff;
}
/* fzgx:end fn_1_69BBC */

/* fzgx:begin fn_1_6F404 */
struct fn_1_6F404_lbl_1_rodata_2D70 {
    f32 unk_0;
    u8 pad_4[0x14];
    f32 unk_18;
    f32 unk_1C;
    u8 pad_20[0x8];
    f32 unk_28;
    u8 pad_2C[0x48];
    f32 unk_74;
    u8 pad_78[0x4];
    f32 unk_7C;
    u8 pad_80[0x10];
    f32 unk_90;
    u8 pad_94[0x18];
    f32 unk_AC;
    f32 unk_B0;
    u8 pad_B4[0x24];
    f32 unk_D8;
    u8 pad_DC[0x1BC];
    f32 unk_298;
    u8 pad_29C[0x74];
    u32 unk_310;
    u32 unk_314;
    u32 unk_318;
    f32 unk_31C;
    f32 unk_320;
};
extern struct fn_1_6F404_lbl_1_rodata_2D70 lbl_1_rodata_2D70;
extern void * fn_1_868C0(s8);
extern u32 fn_1_71024(void *, void *, u32, f32);
extern u32 fn_1_7099C(void *, void *, u32, f32, f32);
extern u32 fn_1_71768(void *, void *);
extern u32 fn_1_702A0(void *, void *, u32, u32);
extern u32 fn_80008C20(void *, void *, void *);
extern u32 lbl_8006E1C0(void *, void *);
extern u32 fn_1_584AC(void);
extern u32 fn_1_6FD58(void *, void *, f32, f32);
extern u32 fn_1_A33F0(u32, f32);
extern u32 fn_1_6D7BC(void *, void *, f32);
extern u32 fn_1_A5594(u32, void *);
extern u32 fn_1_714A8(void *, void *, u32, f32);


void fn_1_6F404(void *arg0, void *arg1) {
    struct fn_1_6F404_lbl_1_rodata_2D70 *tbl;
    u32 sp[3];
    u16 rnd;
    f32 var_f31;
    f32 temp_f0;
    f32 temp_f1;
    void *temp_r30;
    void *temp_r27;
    void *unused;

    unused = arg1;
    tbl = &lbl_1_rodata_2D70;
    temp_r30 = (void *)(*(void **)((u8 *)(arg0) + 56));
    temp_r27 = (void *)(fn_1_868C0((s8)((s8) (*(s16 *)((u8 *)(arg0) + 24)))));
    if ((s16) (*(s16 *)((u8 *)(arg0) + 92)) == 0xA) {
        fn_1_71024((void *)(arg0), (void *)(arg1), (u32)(0x37U), (f32)(tbl->unk_31C));
        fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(0U), (f32)(tbl->unk_18), (f32)(tbl->unk_320));
    }
    if ((s16) (*(s16 *)((u8 *)(arg0) + 92)) == 5) {
        fn_1_71024((void *)(arg0), (void *)(arg1), (u32)(0x37U), (f32)(tbl->unk_31C));
        fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(0U), (f32)(tbl->unk_18), (f32)(tbl->unk_320));
        fn_1_71768((void *)(arg0), (void *)(arg1));
        fn_1_702A0((void *)(arg0), (void *)(arg1), (u32)(0x14U), (u32)(1U));
    }
    if (!((*(s32 *)((u8 *)(temp_r27) + 912)) & 0x01000000) && !((*(s32 *)((u8 *)(temp_r30) + 1420)) & 0x10)) {
        if (!((*(s32 *)((u8 *)(temp_r30) + 0)) & 2)) {
            temp_f1 = *(f32 *)((u8 *)(temp_r30) + 380);
            if (temp_f1 > tbl->unk_320) {
                temp_f0 = temp_f1 / tbl->unk_298;
                sp[0] = tbl->unk_310;
                sp[1] = tbl->unk_314;
                sp[2] = tbl->unk_318;
                var_f31 = tbl->unk_0;
                if (temp_f0 < var_f31) {
                    var_f31 = tbl->unk_0;
                } else if (temp_f0 > tbl->unk_74) {
                    var_f31 = tbl->unk_74;
                } else {
                    var_f31 = temp_f0;
                }
                fn_80008C20((void *)((u8 *)(temp_r30) + 0x7C), (void *)(arg1), (void *)((u8 *)(arg0) + 0x48));
                lbl_8006E1C0((void *)(sp), (void *)(sp));
                rnd = (s32)(u16) fn_1_584AC();
                if ((rnd % 6) == 0) {
                    fn_1_6FD58((void *)(arg0), (void *)(sp), (f32)(var_f31), (f32)(tbl->unk_1C));
                }
                fn_1_A33F0((u32)((u32) (*(s16 *)((u8 *)(temp_r30) + 4))), (f32)(tbl->unk_1C * var_f31));
                if (((u16) (*(u16 *)((u8 *)(temp_r30) + 1248)) < 0x32U)) {
                    rnd = (s32) fn_1_584AC();
                    if ((rnd % 10) == 0) {
                        fn_1_702A0((void *)(arg0), (void *)(sp), (u32)(1U), (u32)(0U));
                    }
                }
            }
        }
        if ((*(s32 *)((u8 *)(temp_r30) + 1420)) & 0x80) {
            rnd = (s32) fn_1_584AC();
            if ((rnd % 5) == 0) {
                fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(1U), (f32)(tbl->unk_7C), (f32)(tbl->unk_28));
            }
            rnd = (s32) fn_1_584AC();
            if ((rnd % 80) == 0) {
                fn_1_6D7BC((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_AC));
                fn_1_6D7BC((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_AC));
                fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(1U), (f32)(tbl->unk_7C), (f32)(tbl->unk_28));
                fn_1_6FD58((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_D8), (f32)(tbl->unk_90));
                if ((s8) (*(u8 *)((u8 *)(temp_r30) + 1141)) >= 0) {
                    fn_1_A5594((u32)(0xA9092A00U), (void *)((u8 *)(arg0) + 0x3C));
                }
            }
        } else if ((s8) (*(u8 *)((u8 *)(temp_r30) + 1141)) != -1) {
            rnd = (s32) fn_1_584AC();
            if ((rnd % 5) == 0) {
                if ((s8) (*(u8 *)((u8 *)(temp_r30) + 1141)) >= 0) {
                    fn_1_A5594((u32)(0xA9092A00U), (void *)((u8 *)(arg0) + 0x3C));
                }
                fn_1_6D7BC((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_AC));
            }
            rnd = (s32) fn_1_584AC();
            if ((rnd % 5) == 0) {
                fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(1U), (f32)(tbl->unk_7C), (f32)(tbl->unk_28));
            }
            rnd = (s32) fn_1_584AC();
            if ((rnd % 5) == 0) {
                fn_1_714A8((void *)(arg0), (void *)(arg1), (u32)(0x16U), (f32)(tbl->unk_B0));
            }
        } else {
            rnd = (s32) fn_1_584AC();
            if ((rnd % 10) == 0) {
                fn_1_6D7BC((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_AC));
                fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(1U), (f32)(tbl->unk_7C), (f32)(tbl->unk_28));
            }
            rnd = (s32) fn_1_584AC();
            if ((rnd % 5) == 0) {
                fn_1_7099C((void *)(arg0), (void *)(arg1), (u32)(1U), (f32)(tbl->unk_7C), (f32)(tbl->unk_28));
            }
            rnd = (s32) fn_1_584AC();
            if ((rnd % 20) == 0) {
                fn_1_6FD58((void *)(arg0), (void *)(arg1), (f32)(tbl->unk_D8), (f32)(tbl->unk_90));
            }
        }
    }
}
/* fzgx:end fn_1_6F404 */

/* fzgx:begin fn_1_6F8D0 */
void fn_1_6F8D0(void *arg0, void *arg1) {
    struct EffectData {
        u8 pad_000[0x58c];
        u32 field_58c;
    };
    struct EffectCar {
        u8 pad_00[0x38];
        struct EffectData *field_38;
        u8 pad_3c[0x76];
        u16 field_b2;
    };
    struct EffectCar *self = (struct EffectCar *)arg0;

    if ((self->field_38->field_58c & 0x10) != 0 && self->field_b2 == 0) {
        fn_1_6F90C(arg0, arg1);
    }
}
/* fzgx:end fn_1_6F8D0 */

/* fzgx:begin fn_1_71CA0 */
void fn_1_71CA0(void *arg0, void *arg1, u16 arg2) {
    if (arg2 == 0xb4) {
        ((struct {
            u8 pad[0x58];
            s16 field_58;
        } *)arg0)->field_58 = fn_1_72318();
    }
    if (arg2 == 0xaa) {
        fn_1_71D0C(arg0, arg1);
    }
}
/* fzgx:end fn_1_71CA0 */

/* fzgx:begin fn_1_72318 noprologue */
#include "dolphin/hw_regs.h"
#include "types.h"

extern void fn_1_867CC(s16 arg0, void *arg1);
extern u32 lbl_1_rodata_314C[13];
extern void lbl_8006DC6C(void *arg0, u32 arg1);
extern void lbl_8006E1B0(void *arg0, void *arg1);
extern s16 fn_1_59078(void *arg0);
extern void *memset(void *dest, int value, u32 size);

struct EffectCar {
    u8 pad_18[0x18];
    s16 field_18;
    u8 pad_1a[0x1e];
    u32 field_38;
    u8 pad_3c[0x7c];
    u8 field_b8;
};

struct EffectWorkData {
    u8 pad_00[0xc];
    s16 field_0c;
    u8 pad_0e[0xa];
    s16 field_18;
    u16 field_1a;
    u8 pad_1c[0x1c];
    u32 field_38;
    u32 field_3c;
    u32 field_40;
    u32 field_44;
    u8 pad_48[0x14];
    s16 field_5c;
    u8 pad_5e[0x8a];
};

#pragma opt_propagation off
s16 fn_1_72318(struct EffectCar *arg0) {
    f32 vec[3];
    struct EffectWorkData data;
    u32 lab_t0;
    f32 v0, v1, v2;

    lab_t0 = arg0->field_18;

    fn_1_867CC(lab_t0, vec);
    memset(&data, 0, sizeof(data));

    data.field_18 = arg0->field_18;
    data.field_0c = 0x25;
    data.field_38 = arg0->field_38;
    data.field_1a = 0xffff;
    lbl_8006DC6C(&arg0->field_b8, data.field_38);

    v2 = vec[0];
    v1 = vec[1];
    v0 = vec[2];

    // These are effect-engine scratch registers used to pass the generated vector.
    // fzgx-allow: A2 hardware scratch register addresses are encoded by the target.
    *(volatile f32 *)(LC_BASE + 0xC) = v2;
    // fzgx-allow: A2 hardware scratch register addresses are encoded by the target.
    *(volatile f32 *)(LC_BASE + 0x1C) = v1;
    // fzgx-allow: A2 hardware scratch register addresses are encoded by the target.
    *(volatile f32 *)(LC_BASE + 0x2C) = v0;

    data.field_3c = lbl_1_rodata_314C[0];
    data.field_40 = lbl_1_rodata_314C[1];
    data.field_44 = lbl_1_rodata_314C[2];
    lbl_8006E1B0(&data.field_3c, &data.field_3c);

    data.field_5c = 0x100;
    return fn_1_59078(&data);
}
#pragma opt_propagation reset
/* fzgx:end fn_1_72318 */
