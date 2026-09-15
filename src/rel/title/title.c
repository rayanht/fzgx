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

/* fzgx:begin fn_8_BE4 */
struct TitleState {
    u8 unk0[0x2];
    u8 unk2;
    u8 unk3[0x221];
    s16 unk224;
    u8 unk226[0x18];
    u16 unk23e;
    u8 unk240;
};

struct Prng {
    u32 unk0;
};

struct Bss58 {
    u8 unk0[0x15];
    u8 unk15;
};

extern u8 lbl_8_bss_0;
extern char lbl_8_data_0[4];
extern u16 jumptable_8_data_494[15];
extern f32 lbl_8_rodata_C[85];
extern s16 lbl_1_bss_966;
extern u8 lbl_801A66BA;
extern struct Prng lbl_801A63C0;
extern struct Bss58 lbl_1_bss_58;

extern void fn_1_47F74(s32);
extern u32 fn_1_4706C(void);
extern void fn_1_46A60(void);
extern u32 fn_1_47E54(u32);
extern void fn_1_7B084(s16, s32);
extern void fn_1_9A958(s16, s32);
extern void fn_1_7FFF0(void);
extern void fn_1_8001C(void);
extern void *fn_1_7F518(s16, void *, s32);
extern int sprintf(char *, const char *, ...);
extern s32 fn_1_465D0(char *, s32);
extern void fn_1_4100C(void);
extern void fn_1_41104(s32);
extern void fn_8006CE1C(f32);
extern void fn_1_A1340(void);

void fn_8_BE4(void) {
    struct TitleState *state = (struct TitleState *)&lbl_8_bss_0;
    char *data = lbl_8_data_0;
    s32 i;
    int v;

    if (lbl_1_bss_966 != 0xa1) {
        fn_1_47F74(0x8e);
    }

    state->unk23e = 0x1e;

    if (lbl_801A66BA == 0) {
        state->unk2 = 1;
        state->unk240 = 0;
    } else {
        state->unk240 = 1;
    }

    {
        u32 tmp = lbl_801A63C0.unk0 * 0x676a4b6b + 0x33cb;
        s32 t;
        s32 c;
        s32 q;
        s32 idx;

        lbl_801A63C0.unk0 = tmp;
        t = (tmp >> 16) & 0x7fff;
        c = t >> 8;
        q = c / 14;
        idx = c - q * 14;
        switch (idx) {
        case 0: state->unk224 = 1; break;
        case 1: state->unk224 = 16; break;
        case 2: state->unk224 = 8; break;
        case 3: state->unk224 = 26; break;
        case 4: state->unk224 = 5; break;
        case 5: state->unk224 = 14; break;
        case 6: state->unk224 = 7; break;
        case 7: state->unk224 = 11; break;
        case 8: state->unk224 = 13; break;
        case 9: state->unk224 = 3; break;
        case 10: state->unk224 = 15; break;
        case 11: state->unk224 = 10; break;
        case 12: state->unk224 = 29; break;
        case 13: state->unk224 = 9; break;
        case 14: state->unk224 = 27; break;
        default: state->unk224 = 1; break;
        }
    }

    v = lbl_1_bss_58.unk15;
    if ((s8)v == 0 || (s8)v == 2) {
        char buf[0x20];
        s8 i;
        fn_1_4706C();
        fn_1_46A60();
        fn_1_47E54(1);
        fn_1_47E54(3);
        fn_1_7B084(state->unk224, 0);
        fn_1_9A958(state->unk224, 0);
        fn_1_7FFF0();
        fn_1_8001C();
        for (i = 0; i < 41; i++) {
            char tmp[0x20];
            sprintf(buf, data + 0x43c, fn_1_7F518(i, tmp, 0));
            fn_1_465D0(buf, 1);
        }
        fn_1_4100C();
        fn_1_41104(2);
    } else {
        fn_1_4706C();
        fn_1_47E54(1);
        fn_1_47E54(0x87);
        fn_1_465D0(data + 0x450, 1);
        fn_1_465D0(data + 0x464, 1);
        fn_1_465D0(data + 0x478, 1);
        fn_1_41104(1);
        fn_1_47E54(0x9a);
        fn_1_47E54(0x9b);
        fn_1_47E54(0x9d);
        fn_1_47E54(0xa1);
        fn_1_47E54(0x9c);
        fn_1_47E54(0xa2);
    }

    fn_8006CE1C(lbl_8_rodata_C[0]);
    fn_1_A1340();
}
/* fzgx:end fn_8_BE4 */

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

/* fzgx:begin fn_8_1344 */
struct fn_8_1344_lbl_8_bss_4 {
    f32 unk_0;
};
extern struct fn_8_1344_lbl_8_bss_4 lbl_8_bss_4;
extern u8 lbl_8_bss_242;
extern u32 fn_1_47F74(u32);

void fn_8_1344(void) {
    lbl_8_bss_242 = 0;
    lbl_8_bss_4.unk_0 = 0.0f;
    fn_1_47F74(1);
    fn_1_47F74(3);
}
/* fzgx:end fn_8_1344 */

/* fzgx:begin fn_8_1394 */
#include "font.h"

#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 320.0f;
    s = 362.0f;
    s = 1.0f;
    s = 0.0f;
    s = 0.4000000059604645f;
    s = 3.5f;
    s = 0.6700000166893005f;
    s = 120.0f;
    s = 2.0f;
    s = 0.75f;
    s = 3.0f;
    s = 16.0f;
    s = 464.0f;
    s = 0.009999999776482582f;
    s = 0.10000000149011612f;
    s = 360.0f;
    s = 240.0f;
    s = 200.0f;
}
static const u32 fzgx_pool_table2[17] = {0xFFFFFFFE, 0x00000000, 0xFFFFFFFE, 0x00000000, 0x00008E00, 0x06000063, 0x00008E01, 0x06000100, 0x00008E03, 0x0A0000F0, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 30.0f;
    d = 4503599627370496.0;
    d = 4503601774854144.0;
    s = 60.0f;
    s = 180.0f;
    s = 10860.0f;
    s = 1020.0f;
}
#pragma section code_type ".text"

struct fn_8_1394_Copy88 { u32 a[22]; };
struct fn_8_1394_lbl_8_bss_0 {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 pad_3[0x1];
    f32 unk_4;
    u8 pad_8[0x218];
    f32 unk_220;
    u8 pad_224[0x4];
    u32 unk_228;
    u8 pad_22C[0x16];
    u8 unk_242;
};
extern f32 fn_1_52070(u32);
extern int fn_1_3F038(void);
extern int fn_1_4C10(void);
extern int fn_1_4F734(FontDrawPacket *);
extern s32 fn_1_465D0(s32, s32);
extern u16 fn_1_48690(u32);
extern u16 fn_1_486C4(u32);
extern u16 lbl_1_bss_96A;
extern u32 fn_1_47E54(u32);
extern u32 fn_1_52088(void);
extern u32 fn_1_5370(s8, u32);
extern u32 fn_8_0();
extern u32 lbl_1_rodata_26F8;
extern u32 lbl_801A66A0;
extern int fn_1_3FC38(void);
extern void fn_1_3EF14(void *);
extern void fn_1_3FC68(s32);
extern void fn_1_41104(void *);
extern void fn_1_51678(FontDrawPacket *, u32, s16, s16, s16, s16);

/* file-scope objects of the retail TU, in retail order: MWCC addresses them off one section base */
u8 fzgx_obj_lbl_8_bss_0;
u8 fzgx_pool_lbl_8_bss_0_gap_1;
u8 fzgx_obj_lbl_8_bss_2;
u8 fzgx_pool_lbl_8_bss_0_gap_3;
f32 lbl_8_bss_4;
u32 lbl_8_bss_4__fzgx_offset_4;
u32 lbl_8_bss_C[5];
u32 lbl_8_bss_20__fzgx_offset_0[128];
f32 lbl_8_bss_20__fzgx_offset_200;
u16 lbl_8_bss_224;
u16 fzgx_pool_lbl_8_bss_0_gap_226;
u32 lbl_8_bss_228;
u32 lbl_8_bss_22C;
u8 lbl_8_bss_230;
u8 fzgx_pool_lbl_8_bss_0_gap_231;
u16 fzgx_pool_lbl_8_bss_0_gap_231_fill_232;
u32 fzgx_obj_lbl_8_bss_234;
u32 fzgx_obj_lbl_8_bss_238;
u8 lbl_8_bss_238__fzgx_offset_4;
u8 fzgx_obj_lbl_8_bss_23D;
u16 fzgx_pool_lbl_8_bss_0_gap_23E;
u8 fzgx_pool_lbl_8_bss_0_gap_23E_fill_240;
u8 lbl_8_bss_241;
u8 fzgx_obj_lbl_8_bss_242;
u8 lbl_8_bss_242__fzgx_offset_1;
u32 lbl_8_bss_242__fzgx_offset_2[25];

#pragma section code_type ".fzgxpool"
static void fzgx_bss_layout(void) {
    volatile u8 s;  /* fzgx-allow: S2 layout primer sink: MWCC emits .bss objects in first-access order */
    s = *(u8 *)&fzgx_obj_lbl_8_bss_0;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_1;
    s = *(u8 *)&fzgx_obj_lbl_8_bss_2;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_3;
    s = *(u8 *)&lbl_8_bss_4;
    s = *(u8 *)&lbl_8_bss_4__fzgx_offset_4;
    s = *(u8 *)&lbl_8_bss_C;
    s = *(u8 *)&lbl_8_bss_20__fzgx_offset_0;
    s = *(u8 *)&lbl_8_bss_20__fzgx_offset_200;
    s = *(u8 *)&lbl_8_bss_224;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_226;
    s = *(u8 *)&lbl_8_bss_228;
    s = *(u8 *)&lbl_8_bss_22C;
    s = *(u8 *)&lbl_8_bss_230;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_231;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_231_fill_232;
    s = *(u8 *)&fzgx_obj_lbl_8_bss_234;
    s = *(u8 *)&fzgx_obj_lbl_8_bss_238;
    s = *(u8 *)&lbl_8_bss_238__fzgx_offset_4;
    s = *(u8 *)&fzgx_obj_lbl_8_bss_23D;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_23E;
    s = *(u8 *)&fzgx_pool_lbl_8_bss_0_gap_23E_fill_240;
    s = *(u8 *)&lbl_8_bss_241;
    s = *(u8 *)&fzgx_obj_lbl_8_bss_242;
    s = *(u8 *)&lbl_8_bss_242__fzgx_offset_1;
    s = *(u8 *)&lbl_8_bss_242__fzgx_offset_2;
}
#pragma section code_type ".text"

extern void OSReport(const char *, ...);
#pragma section code_type ".fzgxpool"
static void fzgx_string_layout(void) {
    /* fzgx-allow: S2 layout primer: MWCC emits string literals in first-use order; the section is dropped at integration */
    OSReport("vehicle/vehicle_sel.arc.lz");
}
#pragma section code_type ".text"

#pragma opt_common_subs off
u32 fn_8_1394(void) {
    f32 fn_8_1394_zero;
    u32 v1;
    f32 v3;
    f32 v4;
    f32 v5;
    f32 v6;
    f32 v8;
    u32 v9;
    f32 v10;
    f32 v11;
    f32 v14;
    u32 v15;
    u32 v16;
    f32 v18;
    f32 v19;
    f32 v20;
    f32 v21;
    f32 v22;
    f32 v24;
    u32 v25;
    u32 v26;
    f32 v28;
    f32 v29;
    f32 v30;
    f32 v31;
    f32 v33;
    u32 v34;
    f32 v35;
    f32 v36;
    u32 v40;
    u32 v41;
    s16 v50;
    s16 v49;
    s32 v51;
    f32 v52;
    f32 unk_4;
    f32 unk_1;
    struct { u32 a[1326]; } loc_270;
    FontDrawPacket loc_218;
    FontDrawPacket loc_1C0;
    FontDrawPacket loc_168;
    FontDrawPacket loc_110;
    FontDrawPacket loc_B8;
    struct fn_8_1394_Copy88 loc_60;
    struct fn_8_1394_Copy88 loc_8;
    /* frame */
    int t25;
    u32 t26;
    f32 t27;
    int t29;
    u32 t30;
    f32 t31;
    u32 t32;
    f32 t33;
    u16 t34;
    u16 t35;
    u16 t36;
    int t38;
    u32 t39;
    int t40;
    u32 t41;
    s32 t42;
    u32 t44;
    u32 v45;
    f32 v46;
    f32 v47;

    
    v1 = lbl_8_bss_228;
    lbl_8_bss_20__fzgx_offset_200 = 1.0f;
    if ((s32)v1 > 10980 && (s32)v1 <= 11040) {
    v3 = (f32)(s32)(11040 - v1);
    v4 = (v3 / 60.0f);
    fn_1_52070(320);
    loc_218 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v5 = 320.0f;
    v6 = 120.0f;
    loc_218.image = 768;
    loc_218.x = v5;
    loc_218.y = v6;
    loc_218.z = 2.0f;
    loc_218.flags = 6;
    loc_218.color[0] = 255;
    loc_218.color[1] = 255;
    loc_218.color[2] = 255;
    loc_218.alpha = v4;
    loc_218.flags = loc_218.flags | 0x4000000;
    loc_218.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_218);
    v8 = (0.75f * v4);
    v9 = (loc_218.flags & 0xFBFFFFFF);
    loc_218.image = 770;
    loc_218.flags = v9;
    loc_218.alpha = v8;
    loc_218.z = 3.0f;
    fn_1_4F734((FontDrawPacket *)&loc_218);
    lbl_8_bss_20__fzgx_offset_200 = (1.0f - v4);
    fn_1_52088();
    }
    if ((s32)lbl_8_bss_228 > 10680 && (s32)lbl_8_bss_228 <= 10980) {
    fn_1_52070(320);
    loc_1C0 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v10 = 320.0f;
    v11 = 120.0f;
    loc_1C0.image = 768;
    loc_1C0.x = v10;
    loc_1C0.y = v11;
    loc_1C0.z = 2.0f;
    loc_1C0.flags = 6;
    loc_1C0.color[0] = 255;
    loc_1C0.color[1] = 255;
    loc_1C0.color[2] = 255;
    loc_1C0.alpha = 1.0f;
    loc_1C0.flags = loc_1C0.flags | 0x4000000;
    loc_1C0.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_1C0);
    v14 = 0.75f;
    v15 = (loc_1C0.flags & 0xFBFFFFFF);
    loc_1C0.flags = v15;
    loc_1C0.image = 770;
    loc_1C0.alpha = v14;
    loc_1C0.z = 3.0f;
    fn_1_4F734((FontDrawPacket *)&loc_1C0);
    lbl_8_bss_20__fzgx_offset_200 = 0.0f;
    fn_1_52088();
    }
    v16 = lbl_8_bss_228;
    if ((s32)v16 > 10620 && (s32)v16 <= 10680) {
    v18 = 1.0f;
    v19 = (f32)(s32)(10680 - v16);
    v20 = (v18 - (v19 / 60.0f));
    fn_1_52070(320);
    loc_168 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v21 = 320.0f;
    v22 = 120.0f;
    loc_168.image = 768;
    loc_168.x = v21;
    loc_168.y = v22;
    loc_168.z = 2.0f;
    loc_168.flags = 6;
    loc_168.color[0] = 255;
    loc_168.color[1] = 255;
    loc_168.color[2] = 255;
    loc_168.alpha = v20;
    loc_168.flags = loc_168.flags | 0x4000000;
    loc_168.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_168);
    v24 = (0.75f * v20);
    v25 = (loc_168.flags & 0xFBFFFFFF);
    loc_168.image = 770;
    loc_168.flags = v25;
    loc_168.alpha = v24;
    loc_168.z = 3.0f;
    fn_1_4F734((FontDrawPacket *)&loc_168);
    lbl_8_bss_20__fzgx_offset_200 = (1.0f - v20);
    fn_1_52088();
    }
    if ((s32)fn_1_3FC38() != 0 && (s32)lbl_8_bss_228 == 1200) {
    fn_1_5370(4, 0);
    fn_1_3FC68(0);
    }
    v26 = lbl_8_bss_228;
    if ((s32)v26 > 1020 && (s32)v26 <= 1200) {
    v28 = (f32)(s32)(1200 - v26);
    v29 = (v28 / 180.0f);
    fn_1_52070(320);
    loc_110 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v30 = 320.0f;
    v31 = 120.0f;
    loc_110.image = 768;
    loc_110.x = v30;
    loc_110.y = v31;
    loc_110.z = 2.0f;
    loc_110.flags = 6;
    loc_110.color[0] = 255;
    loc_110.color[1] = 255;
    loc_110.color[2] = 255;
    loc_110.alpha = v29;
    loc_110.flags = loc_110.flags | 0x4000000;
    loc_110.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_110);
    v33 = (0.75f * v29);
    v34 = (loc_110.flags & 0xFBFFFFFF);
    loc_110.image = 770;
    loc_110.flags = v34;
    loc_110.alpha = v33;
    loc_110.z = 3.0f;
    fn_1_4F734((FontDrawPacket *)&loc_110);
    lbl_8_bss_20__fzgx_offset_200 = (1.0f - v29);
    fn_1_52088();
    }
    if ((s32)lbl_8_bss_228 <= 1020) {
    fn_1_52070(320);
    loc_B8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v35 = 320.0f;
    v36 = 120.0f;
    loc_B8.image = 768;
    loc_B8.x = v35;
    loc_B8.y = v36;
    loc_B8.z = 2.0f;
    loc_B8.flags = 6;
    loc_B8.color[0] = 255;
    loc_B8.color[1] = 255;
    loc_B8.color[2] = 255;
    loc_B8.alpha = 1.0f;
    loc_B8.flags = loc_B8.flags | 0x4000000;
    loc_B8.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_B8);
    v40 = (loc_B8.flags & 0xFBFFFFFF);
    loc_B8.flags = v40;
    loc_B8.image = 770;
    loc_B8.alpha = 0.75f;
    loc_B8.z = 3.0f;
    fn_1_4F734((FontDrawPacket *)&loc_B8);
    lbl_8_bss_20__fzgx_offset_200 = 0.0f;
    fn_1_52088();
    }
    fn_1_3EF14((void *)&loc_270);
    v41 = lbl_8_bss_228;
    if (10860.0f <= (f32)(s32)v41) {
    fzgx_obj_lbl_8_bss_2 = 0;
    loc_270.a[0] = (loc_270.a[0] & 0xFFFFFFFB);
    } else {
    if (1020.0f <= (f32)(s32)v41 && (s32)v41 <= 1200) {
    fzgx_obj_lbl_8_bss_2 = 0;
    loc_270.a[0] = (loc_270.a[0] & 0xFFFFFFFB);
    } else {
    fzgx_obj_lbl_8_bss_2 = 1;
    loc_270.a[0] = (loc_270.a[0] | 4);
    }
    }
    if ((s32)v41 == 15 && (s32)fn_1_4C10() == 0) {
    fzgx_obj_lbl_8_bss_242 = 1;
    }
    if (fzgx_obj_lbl_8_bss_242 != 0) {
    t25 = fn_1_3F038();
    v45 = t25;
    if ((s32)v45 != 0) {
    if (fzgx_obj_lbl_8_bss_0 != 0) {
    fzgx_pool_lbl_8_bss_0_gap_1 = 1;
    fzgx_obj_lbl_8_bss_0 = 0;
    } else {
    lbl_1_bss_96A = 158;
    }
    }
    t26 = fn_1_52088();
    v45 = t26;
    } else {
    t27 = fn_1_52070(96);
    v46 = t27;
    loc_60 = *(struct fn_8_1394_Copy88 *)&lbl_1_rodata_26F8;
    v47 = 16.0f;
    v46 = 464.0f;
    loc_60.a[0] = 256;
    *(f32 *)((u8 *)&loc_60 + 4) = v47;
    *(f32 *)((u8 *)&loc_60 + 8) = v46;
    *(f32 *)((u8 *)&loc_60 + 12) = 0.01f;
    loc_60.a[12] = 13;
    fn_1_51678((FontDrawPacket *)&loc_60, 256, 0, 0, 250, 34);
    t29 = fn_1_4F734((FontDrawPacket *)&loc_60);
    v45 = t29;
    t30 = fn_1_52088();
    v45 = t30;
    t31 = fn_1_52070(544);
    v46 = t31;
    lbl_8_bss_20__fzgx_offset_200 = 1.0f;
    t32 = fn_1_52088();
    v45 = t32;
    t33 = fn_1_52070(320);
    v46 = t33;
    if (fzgx_obj_lbl_8_bss_2 != 0 && (lbl_801A66A0 & 0x18) != 0) {
    loc_8 = *(struct fn_8_1394_Copy88 *)&lbl_1_rodata_26F8;
    loc_8.a[0] = 258;
    v49 = (s16)((fn_1_486C4(loc_8.a[0]) >> 2) & 0x3FFF);
    v50 = (s16)fn_1_48690(loc_8.a[0]);
    v51 = (s16)(((fn_1_486C4(loc_8.a[0]) >> 2) & 0x3FFF) * 3);
    fn_1_51678((FontDrawPacket *)&loc_8, loc_8.a[0], 0, (s16)v51, v50, v49);
    v52 = 320.0f;
    v46 = 362.0f;
    *(f32 *)((u8 *)&loc_8 + 4) = v52;
    *(f32 *)((u8 *)&loc_8 + 8) = v46;
    *(f32 *)((u8 *)&loc_8 + 12) = 1.0f;
    loc_8.a[12] = 6;
    t38 = fn_1_4F734((FontDrawPacket *)&loc_8);
    v45 = t38;
    }
    t39 = fn_1_52088();
    v45 = t39;
    t40 = fn_1_3F038();
    v45 = t40;
    if ((s32)v45 != 0) {
    if (fzgx_obj_lbl_8_bss_0 != 0) {
    fzgx_pool_lbl_8_bss_0_gap_1 = 1;
    fzgx_obj_lbl_8_bss_0 = 0;
    } else {
    lbl_1_bss_96A = 155;
    }
    }
    t41 = fn_1_52088();
    v45 = t41;
    unk_4 = lbl_8_bss_4;
    if ((fn_8_1394_zero = 0.0f, unk_4 == fn_8_1394_zero)) {
    t42 = fn_1_465D0((s32)(u8 *)"vehicle/vehicle_sel.arc.lz", 1);
    v45 = t42;
    fn_1_41104((void *)1);
    fn_1_47E54(154);
    fn_1_47E54(155);
    fn_1_47E54(157);
    fn_1_47E54(161);
    v45 = fn_1_47E54(156);
    v45 = fn_1_47E54(162);
    lbl_8_bss_4 = 1.0f;
    }
    }
    return v45;
}
#pragma opt_common_subs reset
/* fzgx:end fn_8_1394 */

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

/* fzgx:begin fn_8_1C18 */
struct fn_8_1C18_lbl_8_bss_0 {
    u8 pad_0[0x2];
    u8 unk_2;
    u8 pad_3[0x221];
    s16 unk_224;
    u8 pad_226[0x12];
    u32 unk_238;
};

extern f32 lbl_8_rodata_C;
extern struct fn_8_1C18_lbl_8_bss_0 lbl_8_bss_0;
extern u32 fn_1_4706C(void);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_1_9A958(u32, u32);
extern u32 lbl_1_bss_970;
extern void fn_1_7B084(void *, int);
extern void fn_8006CE1C(f32);

#pragma opt_loop_invariants off
void fn_8_1C18(void) {
    struct fn_8_1C18_lbl_8_bss_0 *p_lbl_8_bss_0;
    p_lbl_8_bss_0 = (struct fn_8_1C18_lbl_8_bss_0 *)&lbl_8_bss_0;
    fn_8006CE1C((0.0f));
    fn_1_4A00(1, 15, p_lbl_8_bss_0->unk_238);
    lbl_1_bss_970 = 600;
    fn_1_4706C();
    fn_1_7B084((void *)p_lbl_8_bss_0->unk_224, 0);
    fn_1_9A958(p_lbl_8_bss_0->unk_224, 0);
    p_lbl_8_bss_0->unk_2 = 1;
}
#pragma opt_loop_invariants reset
/* fzgx:end fn_8_1C18 */

/* fzgx:begin fn_8_1C90 */
#include "font.h"

struct fn_8_1C90_Copy88 { u32 a[22]; };
struct fn_8_1C90_lbl_8_rodata_0 {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
    u8 pad_10[0xC];
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
};
struct fn_8_1C90_lbl_8_bss_0 {
    u8 pad_0[0x2];
    u8 unk_2;
    u8 pad_3[0x21D];
    f32 unk_220;
    u8 pad_224[0x14];
    u32 unk_238;
};
struct fn_8_1C90_lbl_1_bss_970 {
    s32 unk_0;
};

extern int fn_1_4C10(void);
extern int fn_1_4F734(FontDrawPacket *);
extern struct fn_8_1C90_lbl_1_bss_970 lbl_1_bss_970;
extern struct fn_8_1C90_lbl_8_bss_0 lbl_8_bss_0;
extern struct fn_8_1C90_lbl_8_rodata_0 lbl_8_rodata_0;
extern u16 fn_1_48690(u32);
extern u16 fn_1_486C4(u32);
extern u16 lbl_1_bss_96A;
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_8_0();
extern u32 lbl_1_rodata_26F8;
extern u32 lbl_801A66A0;
extern void fn_1_51678(FontDrawPacket *, u32, s16, s16, s16, s16);
extern void fn_1_52070(u32);
extern void fn_1_52088(void);

void fn_8_1C90(void) {
    struct fn_8_1C90_lbl_8_bss_0 *p_lbl_8_bss_0;
    struct fn_8_1C90_lbl_8_rodata_0 *p_lbl_8_rodata_0;
    struct fn_8_1C90_lbl_1_bss_970 *p_bss_970;
    f32 v1;
    f32 v0;
    s16 v3;
    s16 v2;
    f32 v5;
    f32 v4;
    f32 v7;
    f32 v6;
    f32 v8;
    u32 v9;
    f32 v10;
    u16 t7;
    u16 t8;
    u16 t9;
    u32 v11;
    s32 v12;
    s32 v13;
    FontDrawPacket loc_B8;
    FontDrawPacket loc_60;
    FontDrawPacket loc_8;
    p_lbl_8_bss_0 = (struct fn_8_1C90_lbl_8_bss_0 *)&lbl_8_bss_0;
    p_lbl_8_rodata_0 = (struct fn_8_1C90_lbl_8_rodata_0 *)&lbl_8_rodata_0;
    fn_1_52070(96);
    loc_B8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v0 = p_lbl_8_rodata_0->unk_2C;
    v1 = p_lbl_8_rodata_0->unk_30;
    loc_B8.image = 256;
    loc_B8.x = v0;
    loc_B8.y = v1;
    loc_B8.z = p_lbl_8_rodata_0->unk_34;
    loc_B8.flags = 13;
    fn_1_51678((FontDrawPacket *)&loc_B8, 256, 0, 0, 250, 34);
    fn_1_4F734((FontDrawPacket *)&loc_B8);
    fn_1_52088();
    fn_1_52070(544);
    p_lbl_8_bss_0->unk_220 = p_lbl_8_rodata_0->unk_8;
    fn_1_52088();
    fn_1_52070(320);
    if (p_lbl_8_bss_0->unk_2 != 0 && (lbl_801A66A0 & 0x18) != 0) {
        loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
        loc_8.image = 258;
        v2 = (s16)((fn_1_486C4((u32)loc_8.image) >> 2) & 0x3FFF);
        v3 = (s16)fn_1_48690((u32)loc_8.image);
        fn_1_51678((FontDrawPacket *)&loc_8, (u32)loc_8.image, 0,
                   (s16)(((fn_1_486C4((u32)loc_8.image) >> 2) & 0x3FFF) * 3),
                   v3, v2);
        loc_8.x = p_lbl_8_rodata_0->unk_0;
        loc_8.y = p_lbl_8_rodata_0->unk_4;
        loc_8.z = p_lbl_8_rodata_0->unk_8;
        loc_8.flags = 6;
        fn_1_4F734((FontDrawPacket *)&loc_8);
    }
    fn_1_52088();
    fn_1_52070(320);
    loc_60 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v6 = p_lbl_8_rodata_0->unk_0;
    v7 = p_lbl_8_rodata_0->unk_1C;
    v8 = p_lbl_8_rodata_0->unk_20;
    loc_60.image = 768;
    loc_60.flags = 6;
    loc_60.x = p_lbl_8_rodata_0->unk_0;
    loc_60.y = p_lbl_8_rodata_0->unk_1C;
    loc_60.z = p_lbl_8_rodata_0->unk_20;
    loc_60.color[0] = 255;
    loc_60.color[1] = 255;
    loc_60.color[2] = 255;
    loc_60.alpha = p_lbl_8_rodata_0->unk_8;
    loc_60.flags |= 0x4000000;
    loc_60.vertex_callback = (void (*)(FontDrawPacket* packet, FontVertex* vertices))(fn_8_0);
    fn_1_4F734((FontDrawPacket *)&loc_60);
    v10 = p_lbl_8_rodata_0->unk_24;
    v11 = (loc_60.flags & 0xFBFFFFFF);
    loc_60.flags = v11;
    loc_60.image = 770;
    loc_60.alpha = v10;
    loc_60.z = p_lbl_8_rodata_0->unk_28;
    fn_1_4F734((FontDrawPacket *)&loc_60);
    p_lbl_8_bss_0->unk_220 = p_lbl_8_rodata_0->unk_C;
    fn_1_52088();
    p_bss_970 = &lbl_1_bss_970;
    if (p_bss_970->unk_0 != 0) {
        v13 = --p_bss_970->unk_0;
        if (v13 == 15 && fn_1_4C10() == 0) {
            fn_1_4A00(0, 15, p_lbl_8_bss_0->unk_238);
        }
    } else {
        if (fn_1_4C10() == 0) {
            lbl_1_bss_96A = 158;
        }
    }
}
/* fzgx:end fn_8_1C90 */

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

/* fzgx:begin fn_8_4F64 */
typedef signed short s16;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef float f32;

typedef struct FontDrawPacket FontDrawPacket;
typedef struct FontVertex {
f32 x, y, z;
} FontVertex;
struct FontDrawPacket {
u32 image;
f32 x, y, z;
f32 scale_x, scale_y;
f32 u0, v0, u1, v1;
s16 rotation_z, rotation_y;
f32 alpha;
u32 flags;
f32 depth;
u8 color[4], color_add[4];
u32 format;
u16 width, height;
void* pixels;
FontDrawPacket* secondary;
void (*vertex_callback)(FontDrawPacket* packet, FontVertex* vertices);
u32 unk_54;
};
void fn_1_4A0D8(const char* text);
void fn_1_4AE0C(const char* format, ...);
int fn_1_4F734(FontDrawPacket* packet);
void fn_1_4EDAC(FontDrawPacket* packet, f32 width, f32 height);
void fn_1_51678(FontDrawPacket* packet, u32 image, s16 x, s16 y, s16 width, s16 height);
void fn_1_517EC(FontDrawPacket* packet, s16 x, s16 y, s16 width, s16 height,
s16 texture_width, s16 texture_height);
struct TitleState {
u8 unk0;
u8 unk1;
u8 unk2;
u8 pad3[0x21d];
f32 unk220;
u8 pad224[0x19];
u8 unk23d;
u8 pad23e[4];
u8 unk242;
};
struct TitleRodata {
f32 unk0;
f32 unk4;
f32 unk8;
u8 padC[0x20];
f32 unk2c;
f32 unk30;
f32 unk34;
};
struct FzgxCopy88 { u32 words[22]; };
extern struct TitleState lbl_8_bss_0;
extern struct TitleRodata lbl_8_rodata_0;
extern struct FzgxCopy88 lbl_1_rodata_26F8;
extern u16 lbl_1_bss_96A;
extern u32 lbl_801A66A0;
extern int fn_1_3F038(void);
extern void fn_1_52070(u32);
extern void fn_1_51678(FontDrawPacket *, u32, s16, s16, s16, s16);
extern int fn_1_4F734(FontDrawPacket *);
extern u32 fn_1_52088(void);
extern u16 fn_1_486C4(u32);
extern u16 fn_1_48690(u32);
extern void fn_8_68F4(void);
void fn_8_4F64(void) {
struct TitleState *state = (struct TitleState *) &lbl_8_bss_0;
struct TitleRodata *rodata = (struct TitleRodata *) &lbl_8_rodata_0;
struct FzgxCopy88 loc_60;
struct FzgxCopy88 loc_8;
s16 temp_r30;
s16 temp_r29;
if (state->unk23d != 0) {
fn_1_3F038();
return;
}
if (state->unk242 != 0) {
if (fn_1_3F038() != 0) {
if (state->unk0 != 0) {
state->unk1 = 1;
state->unk0 = 0;
return;
}
lbl_1_bss_96A = 0xA3;
}
return;
}
fn_1_52070(0x60);
loc_60 = lbl_1_rodata_26F8;
loc_60.words[0] = 0x100;
*(f32 *) ((u8 *) &loc_60 + 4) = rodata->unk2c;
*(f32 *) ((u8 *) &loc_60 + 8) = rodata->unk30;
*(f32 *) ((u8 *) &loc_60 + 12) = rodata->unk34;
*(u32 *) ((u8 *) &loc_60 + 0x30) = 0xD;
fn_1_51678((FontDrawPacket *) &loc_60, 0x100, 0, 0, 0xFA, 0x22);
fn_1_4F734((FontDrawPacket *) &loc_60);
fn_1_52088();
fn_1_52070(0x220);
state->unk220 = rodata->unk8;
fn_1_52088();
fn_1_52070(0x140);
if (state->unk2 != 0 && (lbl_801A66A0 & 0x18)) {
loc_8 = lbl_1_rodata_26F8;
loc_8.words[0] = 0x102;
fn_1_51678((FontDrawPacket *) &loc_8, loc_8.words[0], 0,
(s16) (((fn_1_486C4(loc_8.words[0]) >> 2) & 0x3FFF) * 3),
(fn_1_48690(loc_8.words[0])), ((fn_1_486C4(0x102) >> 2) & 0x3FFF));
*(f32 *) ((u8 *) &loc_8 + 4) = rodata->unk0;
*(f32 *) ((u8 *) &loc_8 + 8) = rodata->unk4;
*(f32 *) ((u8 *) &loc_8 + 12) = rodata->unk8;
*(u32 *) ((u8 *) &loc_8 + 0x30) = 6;
fn_1_4F734((FontDrawPacket *) &loc_8);
}
fn_1_52088();
fn_8_68F4();
}
/* fzgx:end fn_8_4F64 */

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

/* fzgx:begin fn_8_530C */
#include "font.h"

struct TitleState {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3[0x21d];
    f32 unk220;
    u8 pad224[0x19];
    u8 unk23d;
    u8 pad23e[4];
    u8 unk242;
};

struct TitleRodata {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x20];
    f32 unk2c;
    f32 unk30;
    f32 unk34;
};

struct FzgxCopy88 { u32 words[22]; };

extern struct TitleState lbl_8_bss_0;
extern struct TitleRodata lbl_8_rodata_0;
extern struct FzgxCopy88 lbl_1_rodata_26F8;
extern u16 lbl_1_bss_96A;
extern u32 lbl_801A66A0;
extern int fn_1_3F038(void);
extern void fn_1_52070(u32);
extern void fn_1_51678(FontDrawPacket *, u32, s16, s16, s16, s16);
extern int fn_1_4F734(FontDrawPacket *);
extern u32 fn_1_52088(void);
extern u16 fn_1_486C4(u32);
extern u16 fn_1_48690(u32);
extern void fn_8_6A70(void);

void fn_8_530C(void) {
    struct TitleState *state = (struct TitleState *) &lbl_8_bss_0;
    struct TitleRodata *rodata = (struct TitleRodata *) &lbl_8_rodata_0;
    struct FzgxCopy88 loc_60;
    struct FzgxCopy88 loc_8;
    s16 temp_r30;
    s16 temp_r29;

    if (state->unk23d != 0) {
        fn_1_3F038();
        return;
    }
    if (state->unk242 != 0) {
        if (fn_1_3F038() != 0) {
            if (state->unk0 != 0) {
                state->unk1 = 1;
                state->unk0 = 0;
                return;
            }
            lbl_1_bss_96A = 0xA3;
        }
        return;
    }
    fn_1_52070(0x60);
    loc_60 = lbl_1_rodata_26F8;
    loc_60.words[0] = 0x100;
    *(f32 *) ((u8 *) &loc_60 + 4) = rodata->unk2c;
    *(f32 *) ((u8 *) &loc_60 + 8) = rodata->unk30;
    *(f32 *) ((u8 *) &loc_60 + 12) = rodata->unk34;
    *(u32 *) ((u8 *) &loc_60 + 0x30) = 0xD;
    fn_1_51678((FontDrawPacket *) &loc_60, 0x100, 0, 0, 0xFA, 0x22);
    fn_1_4F734((FontDrawPacket *) &loc_60);
    fn_1_52088();
    fn_1_52070(0x220);
    state->unk220 = rodata->unk8;
    fn_1_52088();
    fn_1_52070(0x140);
    if (state->unk2 != 0 && (lbl_801A66A0 & 0x18)) {
        loc_8 = lbl_1_rodata_26F8;
        loc_8.words[0] = 0x102;
        fn_1_51678((FontDrawPacket *) &loc_8, loc_8.words[0], 0,
                   (s16) (((fn_1_486C4(loc_8.words[0]) >> 2) & 0x3FFF) * 3),
                   (fn_1_48690(loc_8.words[0])), ((fn_1_486C4(0x102) >> 2) & 0x3FFF));
        *(f32 *) ((u8 *) &loc_8 + 4) = rodata->unk0;
        *(f32 *) ((u8 *) &loc_8 + 8) = rodata->unk4;
        *(f32 *) ((u8 *) &loc_8 + 12) = rodata->unk8;
        *(u32 *) ((u8 *) &loc_8 + 0x30) = 6;
        fn_1_4F734((FontDrawPacket *) &loc_8);
    }
    fn_1_52088();
    fn_8_6A70();
}
/* fzgx:end fn_8_530C */

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
