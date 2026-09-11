#include "types.h"

/* fzgx:begin _prolog */
extern struct _prolog_lbl_801A6410 lbl_801A6410;
extern struct _prolog_lbl_8_bss_0 lbl_8_bss_0;
extern struct _prolog_lbl_1_bss_58 lbl_1_bss_58;
extern struct _prolog_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern struct _prolog_lbl_1_bss_960 lbl_1_bss_960;
extern u16 lbl_1_bss_968;
extern u16 lbl_1_bss_96A;
extern u32 lbl_1_bss_7167C;
extern u32 lbl_1_bss_71680;
extern u32 lbl_1_bss_71684;
extern s16 lbl_1_bss_964;
extern u32 lbl_8_data_434;

extern u32 fn_1_45D0(u32, u32, void *, u32);
extern u32 fn_1_3CF0(u32, u32);
extern u32 fn_1_479F0(u32);
extern u32 fn_8_954(void);
extern void fn_8_AA8(void);
extern void fn_8_B7C(void);
extern void fn_1_A8F78(void);

struct _prolog_lbl_8_bss_0 {
    u8 pad_0[0x234];
    u32 unk_234;
    u32 unk_238;
    u8 unk_23C;
    u8 unk_23D;
};
struct _prolog_lbl_801A6410 {
    u32 unk_0;
};
struct _prolog_lbl_1_bss_960 {
    s16 unk_0;
};
struct _prolog_lbl_1_bss_58 {
    u8 pad_0[0x1C];
    u32 unk_1C;
};
struct _prolog_lbl_1_bss_8B3A0 {
    u8 pad_0[0x9E];
    u8 unk_9E;
};

void _prolog(void) {
    struct _prolog_lbl_8_bss_0 *p_lbl_8_bss_0;
    s32 t0;
    s32 t1;
    p_lbl_8_bss_0 = (struct _prolog_lbl_8_bss_0 *)&lbl_8_bss_0;
    t0 = fn_1_45D0(lbl_801A6410.unk_0, 0x173c, &lbl_8_data_434, 0x2f1);
    p_lbl_8_bss_0->unk_234 = t0;
    t1 = fn_1_45D0(lbl_801A6410.unk_0, 0x173c, &lbl_8_data_434, 0x2f2);
    p_lbl_8_bss_0->unk_238 = t1;
    fn_1_3CF0(p_lbl_8_bss_0->unk_234, 0x80);
    fn_1_3CF0(p_lbl_8_bss_0->unk_238, 0x80);
    fn_1_479F0(lbl_1_bss_960.unk_0);
    lbl_1_bss_7167C = (u32)fn_8_954;
    lbl_1_bss_71680 = (u32)fn_8_AA8;
    lbl_1_bss_71684 = (u32)fn_8_B7C;
    p_lbl_8_bss_0->unk_23C = 0;
    if (lbl_1_bss_964 == 8 && (s32)lbl_1_bss_58.unk_1C != 0) {
    lbl_1_bss_8B3A0.unk_9E = 0;
    lbl_1_bss_968 = 1;
    } else {
    lbl_1_bss_96A = 158;
    }
    p_lbl_8_bss_0->unk_23D = 0;
    fn_1_A8F78();
}
/* fzgx:end _prolog */

/* fzgx:begin fn_8_AA8 */
extern struct fn_8_AA8_lbl_8_bss_234 lbl_8_bss_234;
extern struct fn_8_AA8_lbl_8_bss_238 lbl_8_bss_238;
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_435C(u32);

struct fn_8_AA8_lbl_8_bss_234 {
    u32 unk_0;
};
struct fn_8_AA8_lbl_8_bss_238 {
    u32 unk_0;
};

void fn_8_AA8(void) {
    u32 t0, t1, t3;
    t0 = fn_1_435C(lbl_8_bss_234.unk_0);
    t1 = fn_1_407C(t0);
    fn_1_3CC4(t1);
    t3 = fn_1_435C(lbl_8_bss_238.unk_0);
    fn_1_407C(t3);
}
/* fzgx:end fn_8_AA8 */

/* fzgx:begin _epilog */
extern u8 lbl_801A66B9;
extern u32 lbl_8_bss_234;
extern u32 lbl_8_bss_238;
extern s16 lbl_1_bss_960;

extern void fn_1_4FEC(void);
extern void fn_1_C3378(void);
extern void fn_1_F7A20(void);
extern s32 fn_1_3FC38(void);
extern void fn_1_37E98(void);
extern void fn_1_435C(u32);
extern void fn_1_41A8(void);
extern void fn_1_47A60(s16);

#pragma opt_dead_assignments off
void _epilog(void) {
    if (!lbl_801A66B9) {
        fn_1_4FEC();
        fn_1_C3378();
        fn_1_F7A20();
        lbl_801A66B9 = 1;
    }
    if (fn_1_3FC38()) {
        fn_1_37E98();
    }
    fn_1_435C(lbl_8_bss_234);
    fn_1_41A8();
    fn_1_435C(lbl_8_bss_238);
    fn_1_41A8();
    fn_1_47A60(lbl_1_bss_960);
}
#pragma opt_dead_assignments reset
/* fzgx:end _epilog */

/* fzgx:begin fn_8_B7C */
typedef u32 (*fn_8_B7C_Fn0)(void);
struct fn_8_B7C_lbl_8_data_318_0_E16 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};
struct fn_8_B7C_lbl_8_data_318 {
    struct fn_8_B7C_lbl_8_data_318_0_E16 unk_0[1];
};

extern s16 lbl_1_bss_962;
extern struct fn_8_B7C_lbl_8_data_318 lbl_8_data_318;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_8_B7C(void) {
    struct fn_8_B7C_lbl_8_data_318_0_E16 *p;
    s16 idx;
    p = (struct fn_8_B7C_lbl_8_data_318_0_E16 *)&lbl_8_data_318;
    idx = lbl_1_bss_962;
    p += idx - 153;
    lbl_1_bss_71688 = p->unk_8;
    lbl_1_bss_7168C = p->unk_C;
    ((fn_8_B7C_Fn0)p->unk_4)();
}
/* fzgx:end fn_8_B7C */

/* fzgx:begin fn_8_BD8 */
// fn_8_BD8: empty in retail (single blr).
void fn_8_BD8(void) {
}
/* fzgx:end fn_8_BD8 */

/* fzgx:begin fn_8_BDC */
// fn_8_BDC: empty in retail (single blr).
void fn_8_BDC(void) {
}
/* fzgx:end fn_8_BDC */

/* fzgx:begin fn_8_BE0 */
// fn_8_BE0: empty in retail (single blr).
void fn_8_BE0(void) {
}
/* fzgx:end fn_8_BE0 */

/* fzgx:begin fn_8_1304 */
extern u32 fn_1_48140(u32);
extern u32 fn_1_A1364(u32);
extern u32 fn_1_A8F78(void);
extern u8 lbl_8_bss_241;
extern u8 lbl_8_bss_2;

void fn_8_1304(void) {
    u32 t1;
    lbl_8_bss_2 = 0;
    lbl_8_bss_241 = 0;
    fn_1_A8F78();
    t1 = fn_1_48140(142);
    fn_1_A1364(t1);
}
/* fzgx:end fn_8_1304 */

/* fzgx:begin fn_8_1C08 */
// fn_8_1C08: empty in retail (single blr).
void fn_8_1C08(void) {
}
/* fzgx:end fn_8_1C08 */

/* fzgx:begin fn_8_1C0C */
// fn_8_1C0C: empty in retail (single blr).
void fn_8_1C0C(void) {
}
/* fzgx:end fn_8_1C0C */

/* fzgx:begin fn_8_1C10 */
// fn_8_1C10: empty in retail (single blr).
void fn_8_1C10(void) {
}
/* fzgx:end fn_8_1C10 */

/* fzgx:begin fn_8_1C14 */
// fn_8_1C14: empty in retail (single blr).
void fn_8_1C14(void) {
}
/* fzgx:end fn_8_1C14 */

/* fzgx:begin fn_8_1F64 */
extern u8 lbl_8_bss_2;

void fn_8_1F64(void) {
    lbl_8_bss_2 = 0;
}
/* fzgx:end fn_8_1F64 */

/* fzgx:begin fn_8_1F74 */
extern f32 lbl_8_rodata_C;
extern u32 fn_1_A5EFC(void);
extern u32 fn_8006CE1C(f32);
extern u8 lbl_801A66B8;

void fn_8_1F74(void) {
    fn_8006CE1C(lbl_8_rodata_C);
    if (lbl_801A66B8 == 0) {
    fn_1_A5EFC();
    }
}
/* fzgx:end fn_8_1F74 */

/* fzgx:begin fn_8_1FB0 */
extern const f32 lbl_8_rodata_8;

extern s32 fn_1_A66FC(s32);
extern void fn_1_4FEC(void);
extern u32 fn_1_C3378(void);
extern u32 fn_1_F7A20(void);
extern void fn_1_3EF8C(u8);
extern u32 fn_1_3ED8C(u32, u32, u32, u32, u32, u32, u32);
extern u32 fn_1_3EB78(u32, u32, u32, u32);
extern void fn_1_3EFF0(void (*)(u32), u8);
extern void fn_8006CE1C(f32);
extern void fn_1_3EF08(u8);
extern void fn_8_784(u32);

extern u8 lbl_801A66B8;
extern u8 lbl_801A66B9;
extern s32 lbl_1_bss_7180C;
extern s16 lbl_1_bss_96A;

struct fn_8_1FB0_lbl_1_bss_58 {
    u8 pad_0[0x15];
    s8 unk_15;
};
extern struct fn_8_1FB0_lbl_1_bss_58 lbl_1_bss_58;

struct fn_8_1FB0_lbl_8_bss_224 {
    s16 unk_0;
};
extern struct fn_8_1FB0_lbl_8_bss_224 lbl_8_bss_224;

struct fn_8_1FB0_lbl_8_bss_238 {
    u32 unk_0;
};
extern struct fn_8_1FB0_lbl_8_bss_238 lbl_8_bss_238;

f32 fn_8_1FB0(f32 arg0) {
    s32 v2;

    if (lbl_801A66B8 != 0 || fn_1_A66FC(lbl_8_bss_238.unk_0) != 0) {
        if (lbl_1_bss_7180C == 0) {
            if (lbl_801A66B9 == 0) {
                fn_1_4FEC();
                fn_1_C3378();
                fn_1_F7A20();
                lbl_801A66B9 = 1;
            }
            v2 = lbl_1_bss_58.unk_15;
            switch (v2) {
            case 1:
            case 3:
                lbl_1_bss_96A = 0xa4;
                break;
            case 0:
            case 2:
            default:
                lbl_1_bss_96A = 0x9c;
                break;
            }
            lbl_1_bss_58.unk_15 = (v2 + 1) & 3;
            if (lbl_1_bss_96A == 0x9c) {
                fn_1_3EF8C(6);
                fn_1_3ED8C(0, 3, 1, lbl_8_bss_224.unk_0 & 0xff, 10, 30, 0);
                fn_1_3EB78(0, 0, 0, 0);
                fn_1_3EFF0(&fn_8_784, 1);
                fn_8006CE1C(lbl_8_rodata_8);
                fn_1_3EF08(1);
            }
        } else {
            lbl_1_bss_96A = 0x9a;
        }
        lbl_801A66B8 = 1;
    }
}
/* fzgx:end fn_8_1FB0 */

/* fzgx:begin fn_8_2120 */
// fn_8_2120: empty in retail (single blr).
void fn_8_2120(void) {
}
/* fzgx:end fn_8_2120 */

/* fzgx:begin fn_8_25F8 */
struct fn_8_25F8_lbl_8_bss_0 {
    u8 pad_0[0x244];
    u32 unk_244;
    u8 unk_248;
    u8 pad_249[0x3];
    u32 unk_24C;
};

extern struct fn_8_25F8_lbl_8_bss_0 lbl_8_bss_0;
extern u32 fn_1_4FEC(void);
extern u32 fn_1_C3378(void);
extern u32 fn_1_F7A20(void);
extern u8 lbl_801A66B9;

void fn_8_25F8(void) {
    struct fn_8_25F8_lbl_8_bss_0 *p_lbl_8_bss_0;
    u32 v0;
    u32 t0, t1, t2;
    p_lbl_8_bss_0 = (struct fn_8_25F8_lbl_8_bss_0 *)&lbl_8_bss_0;
    if (lbl_801A66B9 == 0) {
    t0 = fn_1_4FEC();
    v0 = t0;
    t1 = fn_1_C3378();
    v0 = t1;
    t2 = fn_1_F7A20();
    v0 = t2;
    lbl_801A66B9 = 1;
    }
    p_lbl_8_bss_0->unk_244 = 0;
    p_lbl_8_bss_0->unk_248 = 255;
    p_lbl_8_bss_0->unk_24C = 0;
}
/* fzgx:end fn_8_25F8 */

/* fzgx:begin fn_8_4E8C */
// fn_8_4E8C: empty in retail (single blr).
void fn_8_4E8C(void) {
}
/* fzgx:end fn_8_4E8C */

/* fzgx:begin fn_8_4E90 */
extern struct fn_8_4E90_lbl_801A6410 lbl_801A6410;
extern struct fn_8_4E90_lbl_8_bss_0 lbl_8_bss_0;
extern u32 fn_1_3F8C(void *, void *, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_45D0(u32, u32, void *, u32);
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern u32 fn_1_7BA08(u32, u32, u32);
extern u32 fn_1_7BA48(u32);
extern u32 fn_8_68D8(void);
extern u32 lbl_8_data_434;
extern u32 lbl_8_data_7CDC;
extern void fn_1_7BAF8(void);

struct fn_8_4E90_lbl_8_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x22C];
    u32 unk_238;
    u8 pad_23C[0x1];
    u8 unk_23D;
    u8 pad_23E[0x4];
    u8 unk_242;
    u8 pad_243[0x45];
    u32 unk_288;
};
struct fn_8_4E90_lbl_801A6410 {
    u32 unk_0;
};

void fn_8_4E90(void) {
    struct fn_8_4E90_lbl_8_bss_0 *p_lbl_8_bss_0;
    u32 t2, t3, t6;
    p_lbl_8_bss_0 = (struct fn_8_4E90_lbl_8_bss_0 *)&lbl_8_bss_0;
    if (p_lbl_8_bss_0->unk_23D == 0) {
    p_lbl_8_bss_0->unk_242 = 0;
    fn_8_68D8();
    if (p_lbl_8_bss_0->unk_8 != 0) {
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_8_bss_0->unk_8, &lbl_8_data_434, 3359);
    p_lbl_8_bss_0->unk_8 = 0;
    }
    t2 = fn_1_7BA08(32, 32, 64);
    t3 = fn_1_45D0(lbl_801A6410.unk_0, t2, &lbl_8_data_434, 3362);
    p_lbl_8_bss_0->unk_8 = t3;
    fn_1_7BA48(t3);
    fn_1_435C(p_lbl_8_bss_0->unk_238);
    t6 = fn_1_3F8C(&lbl_8_data_7CDC, fn_1_7BAF8, p_lbl_8_bss_0->unk_8, 2);
    p_lbl_8_bss_0->unk_288 = t6;
    }
}
/* fzgx:end fn_8_4E90 */

/* fzgx:begin fn_8_516C */
extern struct fn_8_516C_lbl_1_bss_7C850 lbl_1_bss_7C850;
extern struct fn_8_516C_lbl_801A6410 lbl_801A6410;
extern struct fn_8_516C_lbl_8_bss_0 lbl_8_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_8_69D8(u32, u32);
extern u32 lbl_8_data_434;

struct fn_8_516C_lbl_8_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x22C];
    u32 unk_238;
    u8 pad_23C[0x1];
    u8 unk_23D;
    u8 pad_23E[0x4A];
    u32 unk_288;
};
struct fn_8_516C_lbl_801A6410 {
    u32 unk_0;
};
struct fn_8_516C_lbl_1_bss_7C850 {
    u32 unk_0;
};

void fn_8_516C(void) {
    struct fn_8_516C_lbl_8_bss_0 *p_lbl_8_bss_0;
    u32 v0;
    p_lbl_8_bss_0 = (struct fn_8_516C_lbl_8_bss_0 *)&lbl_8_bss_0;
    fn_1_435C(p_lbl_8_bss_0->unk_238);
    if ((s32)p_lbl_8_bss_0->unk_288 != 0) {
    fn_1_426C(p_lbl_8_bss_0->unk_288);
    p_lbl_8_bss_0->unk_288 = 0;
    }
    if (p_lbl_8_bss_0->unk_8 != 0) {
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_8_bss_0->unk_8, (u32)&lbl_8_data_434, 3405);
    p_lbl_8_bss_0->unk_8 = 0;
    }
    v0 = lbl_1_bss_7C850.unk_0;
    lbl_1_bss_7C850.unk_0 = (v0 + 1);
    if (p_lbl_8_bss_0->unk_23D == 0) {
    fn_8_69D8(v0, (u32)&lbl_1_bss_7C850);
    }
}
/* fzgx:end fn_8_516C */

/* fzgx:begin fn_8_520C */
// fn_8_520C: empty in retail (single blr).
void fn_8_520C(void) {
}
/* fzgx:end fn_8_520C */

/* fzgx:begin fn_8_5210 */
// fn_8_5210: empty in retail (single blr).
void fn_8_5210(void) {
}
/* fzgx:end fn_8_5210 */

/* fzgx:begin fn_8_5214 */
// fn_8_5214: empty in retail (single blr).
void fn_8_5214(void) {
}
/* fzgx:end fn_8_5214 */

/* fzgx:begin fn_8_5218 */
extern u8 lbl_8_bss_0;
extern char lbl_8_data_0[4];
extern void *lbl_801A6410;
extern void fn_8_6A50(void);
extern void fn_8_C038(void);
extern void *fn_1_7BA08(u32, u32, u32);
extern void fn_1_7BA48(void);
extern void fn_1_435C(void *);
extern void *fn_1_46B4(void *, void *, void *, u32);
extern void *fn_1_45D0(void *, void *, void *, u32);
extern void *fn_1_3F8C(void *, void *, void *, u32);
extern void fn_1_7BAF8(void);

typedef struct TitleState {
    u8 unk0[0x8];
    void *resource;
    u8 unkC[0x22c];
    void *unk238;
    u8 unk23c[1];
    u8 initialized;
    u8 unk23e[3];
    u8 unk241;
    u8 reset;
    u8 unk243[0x45];
    void *unk288;
    void *unk28c;
} TitleState;

typedef struct TitleData {
    u8 unk0[0x7cdc];
    u8 unk7cdc[0xc];
} TitleData;

void fn_8_5218(void) {
    TitleState *state = (TitleState *)&lbl_8_bss_0;
    TitleData *data = (TitleData *)&lbl_8_data_0;

    if (!state->initialized) {
        state->reset = 0;
        fn_8_6A50();
        if (state->resource != 0) {
            fn_1_46B4(lbl_801A6410, state->resource, &data->unk0[0x434], 0xdb2);
            state->resource = 0;
        }
        state->resource = fn_1_45D0(lbl_801A6410, fn_1_7BA08(0x20, 0x20, 0x40),
                                    &data->unk0[0x434], 0xdb5);
        fn_1_7BA48();
        fn_1_435C(state->unk238);
        state->unk288 = fn_1_3F8C(&data->unk0[0x7cdc], fn_1_7BAF8,
                                  state->resource, 2);
        state->unk28c = fn_1_3F8C(&data->unk0[0x7ce8], fn_8_C038, 0, 0x1c);
    }
}
/* fzgx:end fn_8_5218 */

/* fzgx:begin fn_8_5514 */
extern struct fn_8_5514_lbl_1_bss_7C850 lbl_1_bss_7C850;
extern struct fn_8_5514_lbl_801A6410 lbl_801A6410;
extern struct fn_8_5514_lbl_8_bss_0 lbl_8_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_8_6C50(u32, u32);
extern u32 lbl_8_data_434;

struct fn_8_5514_lbl_8_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x22C];
    u32 unk_238;
    u8 pad_23C[0x1];
    u8 unk_23D;
    u8 pad_23E[0x4A];
    u32 unk_288;
    u32 unk_28C;
};
struct fn_8_5514_lbl_801A6410 {
    u32 unk_0;
};
struct fn_8_5514_lbl_1_bss_7C850 {
    u32 unk_0;
};

void fn_8_5514(void) {
    struct fn_8_5514_lbl_8_bss_0 *p_lbl_8_bss_0;
    u32 v0;
    p_lbl_8_bss_0 = (struct fn_8_5514_lbl_8_bss_0 *)&lbl_8_bss_0;
    fn_1_435C(p_lbl_8_bss_0->unk_238);
    if ((s32)p_lbl_8_bss_0->unk_28C != 0) {
    fn_1_426C(p_lbl_8_bss_0->unk_28C);
    p_lbl_8_bss_0->unk_28C = 0;
    }
    if ((s32)p_lbl_8_bss_0->unk_288 != 0) {
    fn_1_426C(p_lbl_8_bss_0->unk_288);
    p_lbl_8_bss_0->unk_288 = 0;
    }
    if (p_lbl_8_bss_0->unk_8 != 0) {
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_8_bss_0->unk_8, (u32)&lbl_8_data_434, 3560);
    p_lbl_8_bss_0->unk_8 = 0;
    }
    v0 = lbl_1_bss_7C850.unk_0;
    lbl_1_bss_7C850.unk_0 = (v0 + 1);
    if (p_lbl_8_bss_0->unk_23D == 0) {
    fn_8_6C50(v0, (u32)&lbl_1_bss_7C850);
    }
}
/* fzgx:end fn_8_5514 */

/* fzgx:begin fn_8_55CC */
extern u32 fn_8_D024(void);
extern u8 lbl_8_bss_23D;
extern u8 lbl_8_bss_242;

void fn_8_55CC(void) {
    if (lbl_8_bss_23D == 0) {
    lbl_8_bss_242 = 0;
    fn_8_D024();
    }
}
/* fzgx:end fn_8_55CC */

/* fzgx:begin fn_8_5810 */
extern u32 fn_8_D5F4(void);
extern u8 lbl_8_bss_23D;

void fn_8_5810(void) {
    if (lbl_8_bss_23D == 0) {
    fn_8_D5F4();
    }
}
/* fzgx:end fn_8_5810 */

/* fzgx:begin fn_8_5C4C */
// fn_8_5C4C: empty in retail (single blr).
void fn_8_5C4C(void) {
}
/* fzgx:end fn_8_5C4C */

/* fzgx:begin fn_8_5C50 */
// fn_8_5C50: empty in retail (single blr).
void fn_8_5C50(void) {
}
/* fzgx:end fn_8_5C50 */

/* fzgx:begin fn_8_6558 */
// fn_8_6558: returns a constant.
int fn_8_6558(void) {
    return 0;
}
/* fzgx:end fn_8_6558 */

/* fzgx:begin fn_8_6560 */
// fn_8_6560: returns a constant.
int fn_8_6560(void) {
    return 0;
}
/* fzgx:end fn_8_6560 */

/* fzgx:begin fn_8_6568 */
// fn_8_6568: returns a constant.
int fn_8_6568(void) {
    return 2;
}
/* fzgx:end fn_8_6568 */

/* fzgx:begin fn_8_6570 */
extern u32 fn_1_D0790(void);

s32 fn_8_6570(void) {
    fn_1_D0790();
    return 0;
}
/* fzgx:end fn_8_6570 */

/* fzgx:begin fn_8_6594 */
extern u32 fn_1_3F8C0(void);
extern u32 fn_1_47F74(u32);
extern u32 fn_1_5370(u32, u32);
extern u32 fn_80008E84(u32);
extern u32 lbl_8_bss_2B4;
extern void fn_8_6558(void);
extern void fn_8_6560(void);
extern void fn_8_6568(void);
extern void fn_8_6570(void);

void fn_8_6594(u32 arg0) {
    u32 v0;
    u32 t1, t2;
    *(u32 *)((u8 *)arg0 + 168) = (u32)fn_8_6558;
    *(u32 *)((u8 *)arg0 + 196) = (u32)fn_8_6568;
    *(u32 *)((u8 *)arg0 + 204) = (u32)fn_8_6560;
    *(u32 *)((u8 *)arg0 + 172) = (u32)fn_8_6570;
    fn_1_5370(0, 0);
    *(u32 *)((u8 *)arg0 + 0) = (*(u32 *)((u8 *)arg0 + 0) | 513);
    v0 = (*(u32 *)((u8 *)arg0 + 0) | 0x800000);
    *(u32 *)((u8 *)arg0 + 0) = v0;
    lbl_8_bss_2B4 = 0;
    t1 = fn_1_3F8C0();
    t2 = fn_80008E84(t1);
    fn_1_47F74(148);
    fn_80008E84(t2);
}
/* fzgx:end fn_8_6594 */

/* fzgx:begin fn_8_67B0 */
extern u32 fn_1_3F8C0(void);
extern u32 fn_1_48140(u32);
extern u32 fn_80008E84(u32);
extern u32 fn_8_8C80(u32);

void fn_8_67B0(void) {
    u32 t0, t1, t3;
    t0 = fn_1_3F8C0();
    t1 = fn_80008E84(t0);
    fn_1_48140(148);
    t3 = fn_80008E84(t1);
    fn_8_8C80(t3);
}
/* fzgx:end fn_8_67B0 */
