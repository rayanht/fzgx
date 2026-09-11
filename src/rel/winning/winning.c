#include "types.h"

/* fzgx:begin _prolog */
struct _prolog_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
};
struct _prolog_lbl_801A6410 {
    u32 unk_0;
};
struct _prolog_lbl_1_bss_96A {
    u16 unk_0;
};

extern u32 fn_1_45D0(u32, u32, void *, u32);
extern struct _prolog_lbl_15_bss_0 lbl_15_bss_0;
extern struct _prolog_lbl_1_bss_96A lbl_1_bss_96A;
extern struct _prolog_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_3CF0(void *, u32);
extern u32 fn_1_479F0(u32);
extern u32 fn_1_47F74(u32);
extern u32 fn_1_4A00(u32, u32, void *);
extern u32 lbl_15_data_A4;
extern u32 lbl_1_bss_7167C;
extern u32 lbl_1_bss_71680;
extern u32 lbl_1_bss_71684;
extern void fn_15_1F4(void);
extern void fn_15_260(void);
extern void fn_15_350(void);
extern void fn_1_C2454(void);

void _prolog(void) {
    struct _prolog_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 zero;
    s32 t0;
    s32 t1;
    p_lbl_15_bss_0 = (struct _prolog_lbl_15_bss_0 *)&lbl_15_bss_0;
    t0 = fn_1_45D0(lbl_801A6410.unk_0, 5948, &lbl_15_data_A4, 0x158);
    p_lbl_15_bss_0->unk_C = t0;
    t1 = fn_1_45D0(lbl_801A6410.unk_0, 5948, &lbl_15_data_A4, 0x159);
    p_lbl_15_bss_0->unk_10 = t1;
    fn_1_3CF0((void *)p_lbl_15_bss_0->unk_C, 128);
    fn_1_3CF0((void *)p_lbl_15_bss_0->unk_10, 128);
    fn_1_479F0(14);
    fn_1_47F74(140);
    fn_1_47F74(187);
    p_lbl_15_bss_0->unk_14 = 0;
    p_lbl_15_bss_0->unk_14 = p_lbl_15_bss_0->unk_14 | 0x40000000;
    v0 = p_lbl_15_bss_0->unk_10;
    p_lbl_15_bss_0->unk_18 = 0;
    p_lbl_15_bss_0->unk_1C = 30;
    p_lbl_15_bss_0->unk_20 = 1;
    p_lbl_15_bss_0->unk_21 = 0;
    p_lbl_15_bss_0->unk_22 = 0;
    p_lbl_15_bss_0->unk_23 = 0;
    lbl_1_bss_96A.unk_0 = 183;
    fn_1_4A00(1, 30, (void *)v0);
    fn_1_C2454();
    lbl_1_bss_7167C = (u32)(fn_15_1F4);
    lbl_1_bss_71680 = (u32)(fn_15_260);
    lbl_1_bss_71684 = (u32)(fn_15_350);
}
/* fzgx:end _prolog */

/* fzgx:begin _epilog */
extern f32 lbl_15_rodata_0[25];
extern u32 lbl_15_bss_C;
extern u32 lbl_15_bss_10;
extern u32 lbl_1_bss_6EAB4;
extern u8 lbl_15_data_A4[176];
extern u32 lbl_801A6410;

extern void fn_8006CE1C(f32);
extern void fn_1_435C(u32);
extern void fn_1_41A8(void);
extern void fn_1_47A60(u32);
extern void fn_1_48140(u32);
extern void fn_1_46B4(u32, u32, u8 *, u32);

void _epilog(void) {
    fn_8006CE1C(lbl_15_rodata_0[0]);
    lbl_1_bss_6EAB4 &= (u32)-0x29;
    fn_1_435C(lbl_15_bss_C);
    fn_1_41A8();
    fn_1_435C(lbl_15_bss_10);
    fn_1_41A8();
    fn_1_47A60(0xe);
    fn_1_48140(0x8c);
    fn_1_48140(0xbb);
    fn_1_46B4(lbl_801A6410, lbl_15_bss_C, lbl_15_data_A4, 0x192);
    fn_1_46B4(lbl_801A6410, lbl_15_bss_10, lbl_15_data_A4, 0x193);
}
/* fzgx:end _epilog */

/* fzgx:begin fn_15_1F4 */
extern s32 lbl_15_bss_14;
extern s32 lbl_15_bss_1C;
extern void fn_15_B90(void);

void fn_15_1F4(void) {
    if ((lbl_15_bss_14 & 0x10000000) != 0) {
        if (lbl_15_bss_1C != 0) {
            lbl_15_bss_1C -= 1;
        }
        if (lbl_15_bss_1C == 0) {
            lbl_15_bss_14 &= ~0x10000000;
            fn_15_B90();
        }
    }
}
/* fzgx:end fn_15_1F4 */

/* fzgx:begin fn_15_260 */
extern struct fn_15_260_lbl_15_bss_0 lbl_15_bss_0;
extern u32 fn_1_435C(u32);
extern void fn_1_407C(void);
extern void fn_1_3CC4(void);
extern s32 fn_1_8DB94(void);
extern void fn_1_86254(u32);
extern void fn_1_106EB0(void);
extern s32 camera_get_flags(void);
extern void camera_update(void);
extern u32 fn_1_58C4(void);
extern void fn_1_5948(s32);
extern void fn_1_9A770(void);
extern void fn_1_627C(s32);

struct fn_15_260_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u8 pad_14[0xD];
    u8 unk_21;
    u8 pad_22[2];
    u32 unk_24;
    u32 unk_28;
};

void fn_15_260(void) {
    struct fn_15_260_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 count;
    s32 i;
    s16 index;

    p_lbl_15_bss_0 = (struct fn_15_260_lbl_15_bss_0 *)&lbl_15_bss_0;
    if (p_lbl_15_bss_0->unk_21 != 0) {
        fn_1_435C(p_lbl_15_bss_0->unk_24);
        fn_1_407C();
    }
    fn_1_435C(p_lbl_15_bss_0->unk_C);
    fn_1_407C();
    fn_1_3CC4();
    if (fn_1_8DB94() != 0) {
        fn_1_86254(0);
        fn_1_106EB0();
    }
    if (camera_get_flags() != 0) {
        camera_update();
    }
    count = fn_1_58C4();
    i = 0;
    while ((s16)i < count) {
        index = (s16)i;
        fn_1_5948(index);
        fn_1_9A770();
        if (p_lbl_15_bss_0->unk_21 != 0) {
            fn_1_435C(p_lbl_15_bss_0->unk_28);
            fn_1_407C();
        }
        fn_1_435C(p_lbl_15_bss_0->unk_10);
        fn_1_407C();
        fn_1_627C(index);
        i++;
    }
}
/* fzgx:end fn_15_260 */

/* fzgx:begin fn_15_350 */
typedef void (*fn_15_350_Fn0)(void);
struct fn_15_350_lbl_15_data_70_0_E16 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};

extern s16 lbl_1_bss_962;
extern u8 lbl_15_data_70[32];
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_15_350(void) {
    u32 v0;
    struct fn_15_350_lbl_15_data_70_0_E16 *p;
    p = (struct fn_15_350_lbl_15_data_70_0_E16 *)&lbl_15_data_70;
    p += lbl_1_bss_962 - 183;
    lbl_1_bss_71688 = p->unk_8;
    v0 = p->unk_C;
    lbl_1_bss_7168C = v0;
    ((fn_15_350_Fn0)p->unk_4)();
}
/* fzgx:end fn_15_350 */

/* fzgx:begin fn_15_B8C */
// fn_15_B8C: empty in retail (single blr).
void fn_15_B8C(void) {
}
/* fzgx:end fn_15_B8C */

/* fzgx:begin fn_15_B90 */
struct fn_15_B90_Copy160 { u32 a[40]; };
struct fn_15_B90_lbl_15_bss_0 {
    u8 pad_0[0x10];
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x10];
    u32 unk_2C;
    u8 pad_30[0xE];
    u8 unk_3E;
    u8 pad_3F[0x1];
    u16 unk_40;
};
struct fn_15_B90_lbl_15_rodata_0 {
    u8 pad_0[0x10];
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    u32 unk_54;
};

extern struct fn_15_B90_lbl_15_rodata_0 lbl_15_rodata_0;
extern struct fn_15_B90_lbl_15_bss_0 lbl_15_bss_0;
extern u32 lbl_1_bss_6EAB4;
extern u16 lbl_1_bss_968;
extern u16 lbl_1_bss_96A;
extern u32 lbl_15_data_90[5];
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_1_5370(u32, u32);
extern void fn_1_DCF54(void *, void *, void *);
extern void camera_disable_flags(void);

void fn_15_B90(void) {
    struct fn_15_B90_lbl_15_rodata_0 *p_lbl_15_rodata_0;
    struct fn_15_B90_lbl_15_bss_0 *p_lbl_15_bss_0;
    struct fn_15_B90_Copy160 loc_50;
    u32 loc_44[3];
    u32 loc_38[3];
    u32 loc_2C[3];
    u32 loc_20[3];
    u32 loc_14[3];
    u32 loc_8[3];
    u32 v0;
    u32 v3;

    p_lbl_15_rodata_0 = (struct fn_15_B90_lbl_15_rodata_0 *)&lbl_15_rodata_0;
    p_lbl_15_bss_0 = (struct fn_15_B90_lbl_15_bss_0 *)&lbl_15_bss_0;
    v0 = p_lbl_15_bss_0->unk_14;
    lbl_1_bss_6EAB4 = lbl_1_bss_6EAB4 & 0xFFFFFFD7u;
    if ((v0 & 0x20000000) == 0) {
        if ((v0 & 0x80) != 0) {
            lbl_1_bss_968 = *(u8 *)((u8 *)p_lbl_15_bss_0->unk_2C + 0x190);
        } else {
            v3 = p_lbl_15_bss_0->unk_2C;
            loc_50 = *(struct fn_15_B90_Copy160 *)((u8 *)v3 + 0xF0);
            if (((u8 *)&loc_50)[8] == 0 && p_lbl_15_bss_0->unk_3E == 0) {
                lbl_1_bss_968 = 0x10;
            } else {
                if (p_lbl_15_bss_0->unk_40 < 1) {
                    p_lbl_15_bss_0->unk_40 = 1;
                    p_lbl_15_bss_0->unk_18 = lbl_15_data_90[1];
                    camera_disable_flags();
                    fn_1_5370(3, 0);
                    loc_44[0] = p_lbl_15_rodata_0->unk_10;
                    loc_44[1] = p_lbl_15_rodata_0->unk_14;
                    loc_44[2] = p_lbl_15_rodata_0->unk_18;
                    loc_38[0] = p_lbl_15_rodata_0->unk_1C;
                    loc_38[1] = p_lbl_15_rodata_0->unk_20;
                    loc_38[2] = p_lbl_15_rodata_0->unk_24;
                    loc_2C[0] = p_lbl_15_rodata_0->unk_28;
                    loc_2C[1] = p_lbl_15_rodata_0->unk_2C;
                    loc_2C[2] = p_lbl_15_rodata_0->unk_30;
                    fn_1_DCF54(loc_44, loc_38, loc_2C);
                    fn_1_4A00(1, 30, p_lbl_15_bss_0->unk_10);
                } else {
                    lbl_1_bss_968 = *(u8 *)((u8 *)v3 + 0x190);
                }
            }
        }
    } else {
        if ((v0 & 0x80) != 0) {
            lbl_1_bss_96A = 183;
        } else {
            if (p_lbl_15_bss_0->unk_40 < 1) {
                p_lbl_15_bss_0->unk_40 = 1;
                p_lbl_15_bss_0->unk_18 = lbl_15_data_90[1];
                camera_disable_flags();
                fn_1_5370(3, 0);
                loc_20[0] = p_lbl_15_rodata_0->unk_34;
                loc_20[1] = p_lbl_15_rodata_0->unk_38;
                loc_20[2] = p_lbl_15_rodata_0->unk_3C;
                loc_14[0] = p_lbl_15_rodata_0->unk_40;
                loc_14[1] = p_lbl_15_rodata_0->unk_44;
                loc_14[2] = p_lbl_15_rodata_0->unk_48;
                loc_8[0] = p_lbl_15_rodata_0->unk_4C;
                loc_8[1] = p_lbl_15_rodata_0->unk_50;
                loc_8[2] = p_lbl_15_rodata_0->unk_54;
                fn_1_DCF54(loc_20, loc_14, loc_8);
                fn_1_4A00(1, 30, p_lbl_15_bss_0->unk_10);
            } else {
                lbl_1_bss_96A = 183;
            }
        }
    }
}
/* fzgx:end fn_15_B90 */

/* fzgx:begin fn_15_DD8 */
struct fn_15_DD8_Copy160 { u32 a[40]; };

struct fn_15_DD8_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x2];
    u8 unk_22;
    u8 unk_23;
    u8 pad_24[0x8];
    u32 unk_2C;
    u8 pad_30[0x4];
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 pad_37[0x7];
    u8 unk_3E;
    u8 pad_3F[0x1];
    u16 unk_40;
};

extern int fn_1_4C10(void);
extern s32 fn_1_C24A4(void);
extern struct fn_15_DD8_lbl_15_bss_0 lbl_15_bss_0;
extern u32 lbl_1_bss_6EAB4;
extern u8 lbl_1_bss_5138[];
extern u32 fn_1_4A00(u32, u32, void *);
extern u32 fn_1_A2A70(u32, s16);
extern u8 fn_1_B7C00(void);
extern void fn_1_3FDA8(void *, void *);

void fn_15_DD8(void) {
    s32 v4;
    struct fn_15_DD8_lbl_15_bss_0 *p;
    u32 v1;
    u32 v2;
    struct fn_15_DD8_Copy160 loc;

    p = &lbl_15_bss_0;
    if (fn_1_4C10() != 0) {
        return;
    }
    v1 = p->unk_14;
    v2 = v1 & 0x10000000;
    if (v2 == 0 && ((v1 & 1) == 0 || p->unk_18 >= 60)) {
        if ((p->unk_34 != 0 || p->unk_35 != 0) && p->unk_36 != 0 && p->unk_40 >= 1) {
            return;
        }
        loc = *(struct fn_15_DD8_Copy160 *)((u8 *)p->unk_2C + 0xF0);
        v4 = (p->unk_23 != 0) ? 480 : 30;
        if ((((u8 *)&loc)[8] == 0 && p->unk_3E == 0) || p->unk_40 < 1 || (v1 & 0x80) != 0) {
            if (v2 == 0) {
                p->unk_1C = (s16)v4;
                p->unk_14 |= 0x10000000;
            }
            lbl_1_bss_6EAB4 |= 0xAC;
            fn_1_A2A70(12, (s16)v4);
            fn_1_4A00(0, v4 & 0xFF, (void *)p->unk_10);
        } else {
            if (p->unk_22 == 0) {
                fn_1_3FDA8((void *)p->unk_C, (void *)p->unk_10);
            }
            p->unk_22 = 1;
            if ((s32)lbl_1_bss_5138[0xE2] == 0 && fn_1_C24A4() == 0 && (fn_1_B7C00() & 0xFF) == 0) {
                if ((p->unk_14 & 0x10000000) == 0) {
                    p->unk_1C = (s16)v4;
                    p->unk_14 |= 0x10000000;
                }
                p->unk_14 |= 0x10000000;
                lbl_1_bss_6EAB4 |= 0xAC;
                fn_1_A2A70(12, (s16)v4);
                fn_1_4A00(0, v4 & 0xFF, (void *)p->unk_10);
                p->unk_22 = 0;
            }
        }
    }
}
/* fzgx:end fn_15_DD8 */

/* fzgx:begin fn_15_FCC */
typedef struct Sig_fn_1_22E8C_Fn_1_22E8CInput {
    u8 pad[0xB4];
} Sig_fn_1_22E8C_Fn_1_22E8CInput;

typedef struct Sig_fn_1_22E8C_Fn_1_22E8COutput {
    u32 flags;
    u8 pad04[0x8];
    f32 field0c;
    u8 pad10[0xCC];
    f32 fielddc;
    u8 pade0[0x120];
    f32 field200;
    u8 pad204[0x280];
    void *field484;
} Sig_fn_1_22E8C_Fn_1_22E8COutput;

struct fn_15_FCC_lbl_15_rodata_0 {
    f32 unk_0;
    u8 pad_4[0x54];
    f32 unk_58;
    f32 unk_5C;
};
struct fn_15_FCC_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x1E];
    s16 unk_3A;
    u8 pad_3C[0x4];
    u16 unk_40;
    u8 pad_42[0x2];
    f32 unk_44;
    f32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    u32 unk_54;
    u32 unk_58;
    u32 unk_5C;
};

typedef struct Obj_1_bss_6EAD0_At0 {
    void *unk_0;
} Obj_1_bss_6EAD0_At0;

typedef struct Obj_1_bss_6EAD0 {
    Obj_1_bss_6EAD0_At0 *unk_0;
    u8 pad_4[0x704];
} Obj_1_bss_6EAD0;

extern struct fn_15_FCC_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_FCC_lbl_15_rodata_0 lbl_15_rodata_0;
extern Obj_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern u32 lbl_15_data_154;
extern u32 lbl_15_data_164;
extern u8 lbl_1_data_28060[];
extern void camera_enable_flags(void);
extern void fn_80008BA8(void *, void *, u32);
extern void fn_1_22E8C(Sig_fn_1_22E8C_Fn_1_22E8COutput *, Sig_fn_1_22E8C_Fn_1_22E8CInput *);
extern f32 fn_1_1577D0(u32, u32, f32);
extern u32 fn_1_435C(u32);
extern s32 fn_1_3F8C(u32, u32, void *, u32);
extern s32 fn_1_5370(s32, s32);
extern void fn_15_4568(void);
extern void fn_1_15B610(void);
extern void ADXT_Pause(void *, s32);
extern s32 fn_80067898(u32);

extern s32 fn_1_157820;
extern s32 fn_1_1578C4;

void fn_15_FCC(void) {
    Sig_fn_1_22E8C_Fn_1_22E8CInput sp8;
    u8 *p_src;
    s16 i;
    Sig_fn_1_22E8C_Fn_1_22E8COutput *p_obj;
    struct fn_15_FCC_lbl_15_rodata_0 *p_rodata;
    struct fn_15_FCC_lbl_15_bss_0 *p_bss;
    f32 val0;
    f32 val200;
    u32 temp_r0;
    u32 v;
    u8 *p_aux;

    p_rodata = &lbl_15_rodata_0;
    p_bss = (struct fn_15_FCC_lbl_15_bss_0 *)&lbl_15_bss_0;
    p_bss->unk_18 = 0;
    p_bss->unk_40 = 0;
    p_bss->unk_44 = p_rodata->unk_0;
    p_bss->unk_48 = p_rodata->unk_0;
    camera_enable_flags();
    temp_r0 = p_bss->unk_14;
    if (temp_r0 & 6) {
        p_obj = (Sig_fn_1_22E8C_Fn_1_22E8COutput *)p_bss->unk_4C;
        val200 = p_rodata->unk_58;
        val0 = p_rodata->unk_0;
        p_src = lbl_1_data_28060 + 0x438;
        i = 0;
        while ((s32)i < p_bss->unk_3A) {
            fn_80008BA8(&sp8, p_src, 0xB4U);
            fn_1_22E8C(p_obj, &sp8);
            p_aux = (u8 *)p_obj->field484;
            i += 1;
            p_obj->field0c = val200;
            p_obj->field200 = val0;
            *(f32 *)(p_aux + 0xC) = val0;
            p_obj->fielddc = val0;
            p_obj->flags = p_obj->flags | 0x100000 | 0x8001;
            p_obj = (Sig_fn_1_22E8C_Fn_1_22E8COutput *)((u8 *)p_obj + 0x620);
        }
    }
    if (p_bss->unk_14 & 2) {
        fn_1_1577D0(1U, 1U, p_rodata->unk_5C);
        fn_1_435C(p_bss->unk_C);
        fn_1_3F8C((u32)&lbl_15_data_154, (u32)&fn_1_157820, 0, 2U);
        fn_1_435C(p_bss->unk_10);
        fn_1_3F8C((u32)&lbl_15_data_164, (u32)&fn_1_1578C4, 0, 2U);
    }
    v = p_bss->unk_14;
    p_bss->unk_50 = 0;
    p_bss->unk_54 = 0;
    p_bss->unk_58 = 0;
    p_bss->unk_5C = 0;
    if (v & 0x78) {
        temp_r0 = p_bss->unk_14 & 0xFBFFFFFF;
        p_bss->unk_14 = temp_r0;
        p_bss->unk_14 = temp_r0 | 0x40000000;
        fn_1_5370(0, 0);
    } else if (v & 0x80) {
        p_bss->unk_14 = v | 0x04000000;
        fn_1_5370(4, 0);
    } else {
        p_bss->unk_14 = v & 0xBBFFFFFF;
        fn_1_5370(0, 0);
    }
    fn_15_4568();
    fn_1_15B610();
    ADXT_Pause(lbl_1_bss_6EAD0.unk_0->unk_0, 0);
    fn_80067898(0xA91A0000U);
    fn_80067898(0xA91A0200U);
}
/* fzgx:end fn_15_FCC */

/* fzgx:begin fn_15_1D7C */
extern struct fn_15_1D7C_lbl_15_bss_0 lbl_15_bss_0;
extern u32 fn_15_1F28(u32, u32);
extern u32 fn_15_FCC(void);
extern u32 fn_1_4A00(u32, u32, u32);

struct fn_15_1D7C_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
};

u32 fn_15_1D7C(u32 arg0, u32 arg1, u32 arg2) {
    struct fn_15_1D7C_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 t0, t1, t2, t3;
    p_lbl_15_bss_0 = (struct fn_15_1D7C_lbl_15_bss_0 *)&lbl_15_bss_0;
    v0 = arg2;
    v1 = arg0;
    v2 = arg1;
    if ((p_lbl_15_bss_0->unk_14 & 0x78) == 0) {
    v0 = p_lbl_15_bss_0->unk_10;
    v1 = 1;
    v2 = 30;
    t0 = fn_1_4A00(v1, v2, v0);
    v1 = t0;
    } else {
    v0 = p_lbl_15_bss_0->unk_10;
    v1 = 0;
    v2 = 0;
    t1 = fn_1_4A00(v1, v2, v0);
    v1 = t1;
    }
    v1 = p_lbl_15_bss_0->unk_C;
    v2 = p_lbl_15_bss_0->unk_10;
    t2 = fn_15_1F28(v1, v2);
    v1 = t2;
    if ((p_lbl_15_bss_0->unk_14 & 0x1) != 0) {
    t3 = fn_15_FCC();
    v1 = t3;
    }
    return v1;
}
/* fzgx:end fn_15_1D7C */

/* fzgx:begin fn_15_1DF4 */
extern struct fn_15_1DF4_lbl_15_bss_0 lbl_15_bss_0;
extern u8 lbl_1_bss_25E98;
extern u8 lbl_1_bss_9F8;
extern struct fn_15_1DF4_lbl_1_bss_5138 lbl_1_bss_5138;
extern void fn_15_11DC(void);
extern u32 fn_1_B7C00(void);
extern void fn_15_DD8(void);

struct fn_15_1DF4_lbl_15_bss_0 {
    u8 pad_0[0x14];
    u32 unk_14;
    u8 pad_18[0x8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
};

struct fn_15_1DF4_lbl_1_bss_5138 {
    u8 pad_0[0xE0];
    u8 unk_E0;
    u8 unk_E1;
    u8 unk_E2;
};

void fn_15_1DF4(void) {
    struct fn_15_1DF4_lbl_15_bss_0 *p;
    struct fn_15_1DF4_lbl_1_bss_5138 *q;
    u8 *table;
    u32 idx;
    u16 val;
    s32 e2;
    s32 bit;

    p = (struct fn_15_1DF4_lbl_15_bss_0 *)&lbl_15_bss_0;
    if ((p->unk_14 & 0x1) != 0) {
        fn_15_11DC();
    }

    table = (u8 *)&lbl_1_bss_9F8 + 0x8;
    idx = (u32)lbl_1_bss_25E98 * 0x14;
    val = *(u16 *)(table + idx);
    if ((((val >> 8) & 1) != 0 || ((val >> 12) & 1) != 0) &&
        (fn_1_B7C00() & 0xFF) == 0 && p->unk_20 != 0 || p->unk_22 != 0) {
        fn_15_DD8();
    }

    q = (struct fn_15_1DF4_lbl_1_bss_5138 *)&lbl_1_bss_5138;
    e2 = q->unk_E2;
    if (e2 != 0) {
        bit = (*(u16 *)(table + (u32)lbl_1_bss_25E98 * 0x14) >> 8) & 1;
        if (q->unk_E2 != 0 && bit != 0 && q->unk_E0 >= 0xF && q->unk_E0 <= 0x78) {
            q->unk_E0 = 0x78;
        }
    }
}
/* fzgx:end fn_15_1DF4 */

/* fzgx:begin fn_15_1EE0 */
extern struct fn_15_1EE0_lbl_15_bss_0 lbl_15_bss_0;
extern u32 camera_enable_flags(u32);
extern u32 fn_15_236C(u32, u32);

struct fn_15_1EE0_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
};

void fn_15_1EE0(void) {
    struct fn_15_1EE0_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 t0;
    p_lbl_15_bss_0 = (struct fn_15_1EE0_lbl_15_bss_0 *)&lbl_15_bss_0;
    t0 = fn_15_236C(p_lbl_15_bss_0->unk_C, p_lbl_15_bss_0->unk_10);
    if ((p_lbl_15_bss_0->unk_14 & 0x1) != 0) {
    camera_enable_flags(t0);
    }
}
/* fzgx:end fn_15_1EE0 */

/* fzgx:begin fn_15_1F28 */
struct fn_15_1F28_bss {
    u8 pad_0[0x8];
    void *unk_8;
    u8 pad_C[0x8];
    u32 unk_14;
    u8 pad_18[0x26];
    u8 unk_3E;
    u8 pad_3F[0x25];
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    u32 unk_80;
    u32 unk_84;
    u32 unk_88;
    u32 unk_8C;
    u32 unk_90;
    s16 unk_94;
    s16 unk_96;
    u16 unk_98;
};

struct fn_15_1F28_ro3 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

struct fn_15_1F28_snd {
    u32 unk_0;
    u32 unk_4;
    u8 pad_8[0x8];
    u8 unk_10[0x4A248];
    u8 unk_4A258[0x4A248];
    u8 unk_944A0[0x3000];
};

struct fn_15_1F28_bss6EAD0 {
    struct fn_15_1F28_snd *unk_0;
};

struct fn_15_1F28_6410 {
    u32 unk_0;
};

extern struct fn_15_1F28_bss lbl_15_bss_0;
extern struct fn_15_1F28_ro3 lbl_15_rodata_98;
extern struct fn_15_1F28_bss6EAD0 lbl_1_bss_6EAD0;
extern struct fn_15_1F28_6410 lbl_801A6410;
extern f32 lbl_15_rodata_A4[];
extern u8 lbl_15_data_0[];

extern u32 fn_1_A0680(void);
extern void fn_1_41048(void);
extern u32 fn_15_2AE4(void);
extern u32 fn_15_2E8C(void);
extern u32 fn_1_7BA08(u32, u32, u32);
extern u32 fn_1_45D0(u32, u32, u32, u32);
extern void *fn_1_435C(void *);
extern s32 fn_1_3F8C(u32, u32, void *, u32);
extern u32 fn_1_7BA48(u32);
extern void fn_15_3A14(void);
extern void lbl_8006D758(void);
extern void mathutil_mtxA_rotate_y(u32);
extern void mathutil_mtxA_rotate_x(u32);
extern void lbl_8006E1B0(void *, void *);
extern void fn_80074CF4(f32, f32, f32);
extern u32 fn_8004CD70(u32, u32, u32);
extern void fn_80051E64(void *, void *, u32);
extern u32 fn_1_A1588(void *, u32);
extern void ADXT_Pause(void *, s32);
extern u32 fn_8004BF0C(void *, u32);
extern void camera_set_state_flag(u8);
extern void fn_1_5124(void *, void *);
extern u32 fn_1_5370(u32, u32);
extern void fn_1_9A578(void);
extern u32 fn_15_3B24(void);

extern s32 fn_15_2228;
extern s32 fn_15_2274;
extern s32 fn_15_537C;
extern s32 fn_15_545C;
extern s32 fn_1_7BAF8;

void fn_15_1F28(u32 arg0, u32 arg1) {
    u8 *d;
    struct fn_15_1F28_bss *p;
    f32 f0;
    u32 buf;

    d = (u8 *)&lbl_15_data_0;
    p = (struct fn_15_1F28_bss *)&lbl_15_bss_0;

    p->unk_64 = 0;
    p->unk_68 = 0;
    p->unk_6C = 0;
    p->unk_70 = 0;
    p->unk_3E = 0;
    fn_1_A0680();
    fn_1_41048();
    p->unk_74 = arg0;
    p->unk_78 = arg1;
    fn_15_2AE4();
    if (!(p->unk_14 & 0x80)) {
        fn_15_2E8C();
    }
    p->unk_8 = (void *)fn_1_45D0(lbl_801A6410.unk_0, fn_1_7BA08(0x20U, 0x20U, 0x40U), (u32)(d + 0xa4), 0x647U);
    fn_1_435C((void *)arg0);
    fn_1_3F8C((u32)(d + 0x174), (u32)(&fn_15_2228), NULL, 5U);
    fn_1_435C((void *)arg1);
    fn_1_7BA48((u32)p->unk_8);
    fn_1_3F8C((u32)(d + 0x180), (u32)(&fn_1_7BAF8), (void *)(p->unk_8), 3U);
    fn_1_3F8C((u32)(d + 0x18C), (u32)(&fn_15_537C), NULL, 5U);
    fn_1_3F8C((u32)(d + 0x19C), (u32)(&fn_15_2274), NULL, 0xAU);
    fn_1_3F8C((u32)(d + 0x1A8), (u32)(&fn_15_545C), NULL, 0xBU);
    fn_15_3A14();

    p->unk_88 = lbl_15_rodata_98.unk_0;
    p->unk_8C = lbl_15_rodata_98.unk_4;
    p->unk_90 = lbl_15_rodata_98.unk_8;
    p->unk_7C = lbl_15_rodata_98.unk_0;
    p->unk_80 = lbl_15_rodata_98.unk_4;
    p->unk_84 = lbl_15_rodata_98.unk_8;
    p->unk_94 = -0x2000;
    p->unk_96 = 0x2000;
    lbl_8006D758();
    mathutil_mtxA_rotate_y((u32)p->unk_96);
    mathutil_mtxA_rotate_x((u32)p->unk_94);
    lbl_8006E1B0(&p->unk_7C, &p->unk_88);
    f0 = lbl_15_rodata_A4[0];
    fn_80074CF4(f0, f0, f0);

    if (lbl_1_bss_6EAD0.unk_0->unk_0 == 0) {
        lbl_1_bss_6EAD0.unk_0->unk_0 = fn_8004CD70(2U, (u32)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0x10), 0x4A248U);
    }
    if (lbl_1_bss_6EAD0.unk_0->unk_4 == 0) {
        lbl_1_bss_6EAD0.unk_0->unk_4 = fn_8004CD70(2U, (u32)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0x4A258), 0x4A248U);
    }
    fn_80051E64((void *)lbl_1_bss_6EAD0.unk_0->unk_4, (void *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0x944A0), 0x3000U);
    fn_1_A1588((void *)lbl_1_bss_6EAD0.unk_0->unk_0, 0x35U);
    ADXT_Pause((void *)lbl_1_bss_6EAD0.unk_0->unk_0, 1);
    p->unk_98 = 0;
    fn_8004BF0C((void *)lbl_1_bss_6EAD0.unk_0->unk_0, -0x50U);
    fn_8004BF0C((void *)lbl_1_bss_6EAD0.unk_0->unk_4, -0x50U);
    camera_set_state_flag(1U);
    fn_1_5124((void *)arg0, (void *)arg1);
    if (!(p->unk_14 & 1)) {
        fn_1_5370(4U, 0U);
    }
    fn_1_9A578();
    if (!(p->unk_14 & 0x80)) {
        fn_15_3B24();
    }
}
/* fzgx:end fn_15_1F28 */

/* fzgx:begin fn_15_2228 */
extern u32 fn_15_2CEC(void);
extern u32 fn_15_3AFC(void);
extern u32 fn_15_401C(void);
extern u32 fn_15_4124(void);
extern u32 lbl_15_bss_14;
extern u8 lbl_15_bss_21;

void fn_15_2228(void) {
    if ((lbl_15_bss_14 & ~0x7FFFFFFF) != 0) {
    fn_15_4124();
    }
    fn_15_2CEC();
    fn_15_3AFC();
    if (lbl_15_bss_21 != 0) {
    fn_15_401C();
    }
}
/* fzgx:end fn_15_2228 */

/* fzgx:begin fn_15_2274 */
struct fn_15_2274_lbl_15_bss_0 {
    u8 pad_0[0x14];
    u32 unk_14;
    u8 pad_18[0x9];
    u8 unk_21;
    u8 pad_22[0x4E];
    u32 unk_70;
};

struct fn_15_2274_lbl_15_rodata_0 {
    u8 pad_0[0xA8];
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u32 unk_B4;
    u32 unk_B8;
};

extern struct fn_15_2274_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_2274_lbl_15_rodata_0 lbl_15_rodata_0;
extern void fn_15_435C(void);
extern void fn_15_405C(void);
extern void fn_15_2D74(void);
extern void fn_80007AB4(void *);

void fn_15_2274(void) {
    struct fn_15_2274_lbl_15_rodata_0 *p_lbl_15_rodata_0;
    struct fn_15_2274_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    p_lbl_15_rodata_0 = &lbl_15_rodata_0;
    p_lbl_15_bss_0 = &lbl_15_bss_0;
    if ((p_lbl_15_bss_0->unk_14 & 0x80000000) != 0) {
        fn_15_435C();
    }
    v0 = p_lbl_15_bss_0->unk_70;
    switch (v0) {
    case 0: {
        u32 local0;
        local0 = p_lbl_15_rodata_0->unk_A8;
        fn_80007AB4(&local0);
        break;
    }
    case 1: {
        u32 local1;
        local1 = p_lbl_15_rodata_0->unk_AC;
        fn_80007AB4(&local1);
        break;
    }
    case 2: {
        u32 local2;
        local2 = p_lbl_15_rodata_0->unk_B0;
        fn_80007AB4(&local2);
        break;
    }
    case 3: {
        u32 local3;
        local3 = p_lbl_15_rodata_0->unk_B4;
        fn_80007AB4(&local3);
        break;
    }
    default: {
        u32 local4;
        local4 = p_lbl_15_rodata_0->unk_B8;
        fn_80007AB4(&local4);
        break;
    }
    }
    if (p_lbl_15_bss_0->unk_21 != 0) {
        fn_15_405C();
    }
    if ((p_lbl_15_bss_0->unk_14 & 0x80) != 0) {
        fn_15_2D74();
    }
}
/* fzgx:end fn_15_2274 */

/* fzgx:begin fn_15_236C */
struct fn_15_236C_lbl_15_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x8];
    u32 unk_14;
    u8 pad_18[0x9];
    u8 unk_21;
};
struct fn_15_236C_lbl_1_bss_6EAD0 {
    u32 unk_0;
};

extern struct fn_15_236C_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_236C_lbl_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern u32 fn_15_2CF0(u32);
extern u32 fn_15_38FC(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_1_A0AA4(u32);
extern u32 ADXT_Stop(u32);
extern u32 lbl_15_data_A4;
extern u32 lbl_801A6410;
extern void fn_15_3B00(void);
extern void fn_15_4060(void);
extern void fn_1_410A0(void);
extern void fn_1_41A8(void);
extern void fn_1_469BC(void);
extern void fn_1_6400(void);

void fn_15_236C(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    struct fn_15_236C_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t2, t3, t4, t8;
    p_lbl_15_bss_0 = (struct fn_15_236C_lbl_15_bss_0 *)&lbl_15_bss_0;
    fn_1_469BC();
    ADXT_Stop(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0));
    t2 = ADXT_Stop(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 4));
    t3 = fn_1_A0AA4(t2);
    t4 = fn_15_2CF0(t3);
    if ((p_lbl_15_bss_0->unk_14 & 0x80) == 0) {
    fn_15_38FC(t4);
    }
    fn_15_3B00();
    if (p_lbl_15_bss_0->unk_21 != 0) {
    fn_15_4060();
    }
    v0 = p_lbl_15_bss_0->unk_8;
    v3 = arg3;
    if (v0 != 0) {
    v3 = (u32)&lbl_801A6410;
    v1 = (u32)&lbl_15_data_A4;
    v2 = *(u32 *)((u8 *)v3 + 0);
    v3 = 1768;
    t8 = fn_1_46B4(v2, v0, (u32)v1, v3);
    v2 = t8;
    p_lbl_15_bss_0->unk_8 = 0;
    }
    fn_1_435C(arg0);
    fn_1_41A8();
    fn_1_435C(arg1);
    fn_1_41A8();
    fn_1_410A0();
    fn_1_6400();
}
/* fzgx:end fn_15_236C */

/* fzgx:begin fn_15_2620 */
struct fn_15_2620_Arg0 {
    u8 pad_0[0x18];
    u32 unk_18;
    u8 pad_1C[0x6C];
    u32 unk_88;
    u32 unk_8C;
    u8 pad_90[0x8];
    u8 unk_98;
    u8 pad_99[0x42B];
    u8 unk_4C4;
};
struct fn_15_2620_Entry {
    u8 pad_0[6];
    u8 unk_6;
    u8 pad_7;
};
struct fn_15_2620_lbl_15_bss_0 {
    u8 pad_0[0x14];
    u32 unk_14;
    u8 pad_18[0x14];
    struct fn_15_2620_Entry *unk_2C;
    u8 pad_30[0x20];
    u32 unk_50;
    u32 unk_54;
    u32 unk_58;
};

extern struct fn_15_2620_lbl_15_bss_0 lbl_15_bss_0;
extern u32 fn_1_8E728(void *, u32);

void fn_15_2620(struct fn_15_2620_Arg0 *arg0) {
    struct fn_15_2620_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    p_lbl_15_bss_0 = &lbl_15_bss_0;
    v0 = arg0->unk_88;
    switch ((s32)v0) {
    case 33:
    case 42:
    case 43:
        if ((s32)p_lbl_15_bss_0->unk_54 != 0 && (s32)arg0->unk_4C4 == (s32)p_lbl_15_bss_0->unk_50) {
            arg0->unk_8C = 2;
        } else {
            arg0->unk_8C = 3;
        }
        break;
    case 21:
    case 41:
        if ((s32)p_lbl_15_bss_0->unk_54 != 0 && (s32)arg0->unk_4C4 == (s32)p_lbl_15_bss_0->unk_50) {
            arg0->unk_8C = 2;
        } else {
            arg0->unk_8C = 3;
        }
        break;
    default:
        v1 = p_lbl_15_bss_0->unk_14;
        if ((v1 & 0x4000000) != 0 && (v1 & 0x80) == 0) {
            if ((s32)p_lbl_15_bss_0->unk_54 != 0 && (s32)arg0->unk_4C4 == (s32)p_lbl_15_bss_0->unk_50) {
                arg0->unk_8C = 1;
            } else {
                arg0->unk_8C = 2;
            }
        } else {
            arg0->unk_8C = 1;
        }
        break;
    }
    if ((s32)p_lbl_15_bss_0->unk_58 != 0) {
        arg0->unk_18 = (arg0->unk_18 & 0xDFFFFFFF);
    } else {
        arg0->unk_18 = (arg0->unk_18 | 0x20000000);
    }
    v2 = ((31 - __cntlzw(p_lbl_15_bss_0->unk_2C[arg0->unk_4C4].unk_6)) & 0x3);
    v3 = (u32)(p_lbl_15_bss_0->unk_2C + arg0->unk_4C4);
    switch ((s32)v2) {
    case 0:
        v3 = 0;
        break;
    case 1:
        v3 = 1;
        break;
    case 2:
        v3 = 2;
        break;
    case 3:
        v3 = 3;
        break;
    default:
        v3 = 0;
        break;
    }
    if (arg0->unk_98 != (u32)v3) {
        fn_1_8E728((void *)(u32)arg0, (v3 & 0xFF));
    }
}
/* fzgx:end fn_15_2620 */

/* fzgx:begin fn_15_2CEC */
// fn_15_2CEC: empty in retail (single blr).
void fn_15_2CEC(void) {
}
/* fzgx:end fn_15_2CEC */

/* fzgx:begin fn_15_2CF0 */
extern u32 lbl_15_bss_9C[13];
extern u8 lbl_15_data_A4[176];
extern u32 lbl_801A6410;
extern void fn_1_8F494(void *);
extern u32 fn_1_46B4(u32, u32, const u8 *, int);

void fn_15_2CF0(void) {
    u32 *p;
    s32 i;

    p = lbl_15_bss_9C;
    for (i = 0; i < 12; i++) {
        if (p[i] != 0) {
            fn_1_8F494((void *)p[i]);
            fn_1_46B4(lbl_801A6410, p[i], lbl_15_data_A4, 0x8cf);
            p[i] = 0;
        }
    }
}
/* fzgx:end fn_15_2CF0 */

/* fzgx:begin fn_15_2D74 */
struct fn_15_2D74_D0 {
    u32 unk_0;
    u32 unk_4;
};

struct fn_15_2D74_D8 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

struct fn_15_2D74_bss0 {
    u8 pad_0[0x2C];
    u8 *unk_2C;
    u8 pad_30[0x8];
    s16 unk_38;
};

struct fn_15_2D74_rec {
    u32 unk_0;
    u32 unk_4;
};

struct fn_15_2D74_bss1 {
    u8 pad_0[0x8];
    struct fn_15_2D74_rec *unk_8;
};

struct fn_15_2D74_root {
    struct fn_15_2D74_bss1 *unk_0;
};

extern f32 fn_1_A71AC(void);
extern struct fn_15_2D74_D0 lbl_15_rodata_D0;
extern struct fn_15_2D74_D8 lbl_15_rodata_D8;
extern struct fn_15_2D74_bss0 lbl_15_bss_0;
extern struct fn_15_2D74_root lbl_1_bss_38458;
extern u32 fn_1_129D9C(void *, void *, u32, u32, u32, u32, u32, f32);
extern void lbl_8006D7DC(void *);
extern void lbl_8006DB74(void *);
extern void lbl_8006DFC4(void *);

void fn_15_2D74(u32 arg0) {
    u8 *obj;
    u32 *list;
    s16 i;
    u32 tbl[2];
    struct fn_15_2D74_root *q;
    u32 vec[3];
    u32 mtx[13];
    f32 v;
    struct fn_15_2D74_bss0 *p;
    u8 *sub;
    u8 *t;

    p = (struct fn_15_2D74_bss0 *)&lbl_15_bss_0;
    tbl[0] = lbl_15_rodata_D0.unk_0;
    tbl[1] = lbl_15_rodata_D0.unk_4;
    vec[0] = lbl_15_rodata_D8.unk_0;
    vec[1] = lbl_15_rodata_D8.unk_4;
    vec[2] = lbl_15_rodata_D8.unk_8;
    v = fn_1_A71AC();
    list = (u32 *)((u8 *)p + 0x9c);
    i = 0;
    q = (struct fn_15_2D74_root *)&lbl_1_bss_38458;
    while (i < p->unk_38) {
        obj = (u8 *)*list;
        sub = *(u8 **)(obj + 0x150);
        t = *(u8 **)(sub + 8);
        lbl_8006D7DC(obj + 0xa8);
        lbl_8006DFC4(t + 0x214);
        lbl_8006DB74(mtx);
        fn_1_129D9C(mtx, vec, 0,
                    q->unk_0->unk_8[((s16 *)tbl)[p->unk_2C[0x194 + i]]].unk_0,
                    0, 0, 1, v);
        list++;
        i++;
    }
}
/* fzgx:end fn_15_2D74 */

/* fzgx:begin fn_15_30E8 */
extern struct fn_15_30E8_lbl_15_bss_0 lbl_15_bss_0;
extern void fn_15_3368(s16);

struct fn_15_30E8_entry {
    u32 unk_0;
    u8 unk_4;
    u8 value;
    u8 unk_6[2];
};

struct fn_15_30E8_object {
    u8 unk_0[0x81a0];
    u8 value;
};

struct fn_15_30E8_lbl_15_bss_0 {
    u8 unk_0[0x2c];
    struct fn_15_30E8_entry *entries;
    u8 unk_30[8];
    s16 entry_offset;
    u8 unk_3a[0x112];
    s16 entry_count;
};

void fn_15_30E8(void) {
    struct fn_15_30E8_lbl_15_bss_0 *state;
    struct fn_15_30E8_entry *entry;
    s32 i;
    s16 value;

    state = &lbl_15_bss_0;
    entry = state->entries;
    i = 0;
    while (i < state->entry_count) {
        value = entry[i + state->entry_offset].value;
        if ((s16)value >= 0x29) {
            value = ((struct fn_15_30E8_object *)entry[i + state->entry_offset].unk_0)->value;
        }
        fn_15_3368((s16)value);
        i++;
    }
}
/* fzgx:end fn_15_30E8 */

/* fzgx:begin fn_15_398C */
struct fn_15_398C_entry {
    u8 pad_0[0x18];
    u32 flags;
};

struct fn_15_398C_state {
    u8 pad_0[0x14];
    u32 flags;
    u8 pad_18[0x84];
    struct fn_15_398C_entry *entries_9c[0xd4 / 4 - 0x9c / 4];
    struct fn_15_398C_entry *entries_d4[0x1d];
};

extern struct fn_15_398C_state lbl_15_bss_0;

void fn_15_398C(void) {
    struct fn_15_398C_state *s;
    struct fn_15_398C_entry **p;
    struct fn_15_398C_entry *entry;
    s16 i;

    s = &lbl_15_bss_0;
    s->flags |= 0x04000000;
    p = &s->entries_9c[0];
    for (i = 0; i < 0xc; i++) {
        entry = *p;
        if (entry != 0) {
            entry->flags &= 0x3FFFFFFF;
        }
        p++;
    }
    p = &s->entries_d4[0];
    for (i = 0; i < 0x1d; i++) {
        entry = *p;
        if (entry != 0) {
            entry->flags &= 0x3FFFFFFF;
        }
        p++;
    }
}
/* fzgx:end fn_15_398C */

/* fzgx:begin fn_15_3A14 */
extern struct fn_15_3A14_lbl_15_bss_74 lbl_15_bss_74;
extern struct fn_15_3A14_lbl_15_bss_78 lbl_15_bss_78;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_7ACDC(u32);
extern u32 fn_1_7EAE8(void);
extern u8 lbl_15_data_0[];
extern void fn_1_789E8(void);
extern void fn_1_78EBC(void);
extern void fn_1_7E9C4(void);
extern void fn_1_9A5CC(void);
extern void fn_1_9A7BC(void);

struct fn_15_3A14_lbl_15_bss_74 {
    u32 unk_0;
};
struct fn_15_3A14_lbl_15_bss_78 {
    u32 unk_0;
};

void fn_15_3A14(void) {
    u8 *p_lbl_15_data_0;
    p_lbl_15_data_0 = (u8 *)&lbl_15_data_0;
    fn_1_435C(lbl_15_bss_74.unk_0);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 608), (u32)fn_1_789E8, 0, 21);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 620), (u32)fn_1_9A5CC, 0, 23);
    fn_1_435C(lbl_15_bss_78.unk_0);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 636), (u32)fn_1_7E9C4, 0, 4);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 644), (u32)fn_1_7EAE8, 0, 29);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 652), (u32)fn_1_78EBC, 0, 7);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 664), (u32)fn_1_9A7BC, 0, 10);
    fn_1_7EAE8();
    fn_1_7ACDC(50);
}
/* fzgx:end fn_15_3A14 */

/* fzgx:begin fn_15_3AFC */
// fn_15_3AFC: empty in retail (single blr).
void fn_15_3AFC(void) {
}
/* fzgx:end fn_15_3AFC */

/* fzgx:begin fn_15_3B00 */
extern u32 fn_1_79100(void);
extern u32 fn_1_7EAE8(u32);

void fn_15_3B00(void) {
    u32 t0;
    t0 = fn_1_79100();
    fn_1_7EAE8(t0);
}
/* fzgx:end fn_15_3B00 */

/* fzgx:begin fn_15_401C */
extern u32 fn_1_C6F80(u32);
extern u32 lbl_15_bss_14;

u32 fn_15_401C(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if ((lbl_15_bss_14 & 0x40000000) != 0) {
    v0 = 1;
    t0 = fn_1_C6F80(v0);
    v0 = t0;
    } else {
    v0 = 0;
    t1 = fn_1_C6F80(v0);
    v0 = t1;
    }
    return v0;
}
/* fzgx:end fn_15_401C */

/* fzgx:begin fn_15_405C */
// fn_15_405C: empty in retail (single blr).
void fn_15_405C(void) {
}
/* fzgx:end fn_15_405C */

/* fzgx:begin fn_15_4060 */
extern struct fn_15_4060_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_4060_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_41A8(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern u32 fn_1_58854(u32);
extern u32 fn_1_85878(void);
extern u32 fn_1_982C4(u32);
extern u32 fn_1_C47B4(u32);
extern u32 fn_1_C6F80(u32);
extern u32 lbl_15_data_A4;

struct fn_15_4060_lbl_15_bss_0 {
    u8 pad_0[0x21];
    u8 unk_21;
    u8 pad_22[0x2];
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0x124];
    u32 unk_150;
};
struct fn_15_4060_lbl_801A6410 {
    u32 unk_0;
};

void fn_15_4060(void) {
    struct fn_15_4060_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 t0, t1, t2, t6, t8;
    p_lbl_15_bss_0 = (struct fn_15_4060_lbl_15_bss_0 *)&lbl_15_bss_0;
    t0 = fn_1_85878();
    t1 = fn_1_982C4(t0);
    t2 = fn_1_58854(t1);
    fn_1_C47B4(t2);
    fn_1_C6F80(0);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_150, &lbl_15_data_A4, 2849);
    t6 = fn_1_435C(p_lbl_15_bss_0->unk_24);
    fn_1_41A8(t6);
    t8 = fn_1_435C(p_lbl_15_bss_0->unk_28);
    fn_1_41A8(t8);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_24, &lbl_15_data_A4, 2854);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_28, &lbl_15_data_A4, 2855);
    p_lbl_15_bss_0->unk_21 = 0;
}
/* fzgx:end fn_15_4060 */

/* fzgx:begin fn_15_4568 */
extern u16 lbl_15_bss_154;

void fn_15_4568(void) {
    lbl_15_bss_154 = 0;
}
/* fzgx:end fn_15_4568 */

/* fzgx:begin fn_15_537C */
extern f32 lbl_15_bss_88[5];
extern u8 lbl_15_bss_3F8[136];
extern f32 lbl_15_rodata_0[25];
extern u32 lbl_15_rodata_19C[20];

extern void fn_1_7BCCC(void *);
extern void fn_80035680(void *, f32, f32, f32);
extern void fn_80035690(void *, f32, f32, f32);
extern void fn_80035420(void *, u32, f32);
extern void fn_800356AC(void *, void *);
extern void GXInitLightDistAttn(void *, f32, f32, u32);
extern void fn_1_7BB80(void *, u32);
extern void fn_1_7BD6C(u32);

void fn_15_537C(void) {
    u8 *p_lbl_15_bss_3F8;
    u32 local;
    f32 v;
    p_lbl_15_bss_3F8 = &lbl_15_bss_3F8[0];
    fn_1_7BCCC(&lbl_15_bss_88[0]);
    p_lbl_15_bss_3F8 = &lbl_15_bss_3F8[0];
    fn_80035680(p_lbl_15_bss_3F8, lbl_15_bss_88[0], lbl_15_bss_88[1], lbl_15_bss_88[2]);
    fn_80035690(p_lbl_15_bss_3F8, lbl_15_bss_88[0], lbl_15_bss_88[1], lbl_15_bss_88[2]);
    fn_80035420(&lbl_15_bss_3F8[0], 0, lbl_15_rodata_0[0]);
    local = lbl_15_rodata_19C[0];
    fn_800356AC(&lbl_15_bss_3F8[0], &local);
    GXInitLightDistAttn(&lbl_15_bss_3F8[0], 0.0f, 0.0f, 0);
    fn_1_7BB80(&lbl_15_bss_3F8[0], 1);
    fn_1_7BD6C(1);
}
/* fzgx:end fn_15_537C */

/* fzgx:begin fn_15_545C */
// fn_15_545C: empty in retail (single blr).
void fn_15_545C(void) {
}
/* fzgx:end fn_15_545C */
