#include "types.h"

/* fzgx:begin fn_8_67F8 */
struct fn_8_67F8_lbl_8_bss_2B8 {
    u32 unk_0;
};
struct fn_8_67F8_lbl_8_bss_2BC {
    u32 unk_0;
};

extern struct fn_8_67F8_lbl_8_bss_2B8 lbl_8_bss_2B8;
extern struct fn_8_67F8_lbl_8_bss_2BC lbl_8_bss_2BC;
extern u32 fn_1_3F8C0(void);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_80008E84(u32);
extern u32 fn_8_8C80(u32);
extern u32 lbl_801A6410;
extern u32 lbl_8_data_8AD4;
extern void fn_1_14DBCC(void *);
extern void fn_1_48140(int);

void fn_8_67F8(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;
    u32 v7;
    u32 v8;
    s32 v9;
    u32 t0, t1, t4, t6, t7;
    t0 = fn_1_3F8C0();
    t1 = fn_80008E84(t0);
    fn_1_48140(148);
    v0 = lbl_8_bss_2B8.unk_0;
    v1 = arg1;
    v2 = v0;
    v3 = arg2;
    v4 = arg3;
    if (v0 != 0) {
    fn_1_14DBCC((void *)v2);
    v3 = (u32)&lbl_801A6410;
    v4 = (u32)&lbl_8_bss_2B8;
    v2 = *(u32 *)((u8 *)v3 + 0);
    v3 = (u32)&lbl_8_data_8AD4;
    v1 = *(u32 *)((u8 *)v4 + 0);
    v4 = 1035;
    t4 = fn_1_46B4(v2, v1, (u32)v3, v4);
    v2 = t4;
    lbl_8_bss_2B8.unk_0 = 0;
    }
    v5 = lbl_8_bss_2BC.unk_0;
    v6 = v1;
    v7 = v5;
    v8 = v3;
    v9 = v4;
    if (v5 != 0) {
    fn_1_14DBCC((void *)v7);
    v8 = (u32)&lbl_801A6410;
    v9 = (u32)&lbl_8_bss_2BC;
    v7 = *(u32 *)((u8 *)v8 + 0);
    v8 = (u32)&lbl_8_data_8AD4;
    v6 = *(u32 *)((u8 *)v9 + 0);
    v9 = 1040;
    t6 = fn_1_46B4(v7, v6, (u32)v8, v9);
    v7 = t6;
    lbl_8_bss_2BC.unk_0 = 0;
    }
    t7 = fn_80008E84(t1);
    fn_8_8C80(t7);
}
/* fzgx:end fn_8_67F8 */

/* fzgx:begin fn_8_68D8 */
extern u32 lbl_8_bss_2A8;
extern u32 lbl_8_bss_2C0;

void fn_8_68D8(void) {
    lbl_8_bss_2C0 = 4;
    lbl_8_bss_2A8 = 0;
}
/* fzgx:end fn_8_68D8 */

/* fzgx:begin fn_8_68F4 */
extern struct fn_8_68F4_lbl_8_bss_2C0 lbl_8_bss_2C0;
extern u32 fn_1_411A4(u32);
extern u32 fn_1_4630(u32, u32, u32, u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_8_8C48(void);
extern u32 fn_8_8E00(void);
extern u32 fn_8_988C(void);
extern u32 fn_8_9B04(void);
extern u32 lbl_801A6410;
extern u32 lbl_801A66B4;
extern u32 lbl_8_bss_2B0;
extern u32 lbl_8_data_8AD4;

struct fn_8_68F4_lbl_8_bss_2C0 {
    u32 unk_0;
};

u32 fn_8_68F4(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t0, t1, t2, t3, t4, t5, t6, t7;
    v0 = lbl_8_bss_2C0.unk_0;
    if ((s32)lbl_8_bss_2C0.unk_0 == 1) {
    v1 = arg2;
    v2 = arg3;
    if (lbl_8_bss_2B0 != 0) {
    v2 = (u32)&lbl_801A6410;
    v1 = (u32)&lbl_8_data_8AD4;
    v0 = *(u32 *)((u8 *)v2 + 0);
    v2 = 1152;
    t0 = fn_1_46B4(v0, lbl_8_bss_2B0, (u32)v1, v2);
    v0 = t0;
    }
    v2 = (u32)&lbl_801A6410;
    v1 = (u32)&lbl_8_data_8AD4;
    v0 = *(u32 *)((u8 *)v2 + 0);
    v2 = 1154;
    t1 = fn_1_4630(v0, (0x90000 - 16384), (u32)v1, v2);
    v0 = t1;
    lbl_8_bss_2B0 = v0;
    if ((s32)lbl_801A66B4 == 5) {
    v0 = 4;
    t2 = fn_1_411A4(v0);
    v0 = t2;
    } else {
    v0 = 5;
    t3 = fn_1_411A4(v0);
    v0 = t3;
    }
    t4 = fn_8_988C();
    v0 = t4;
    t5 = fn_8_9B04();
    v0 = t5;
    t6 = fn_8_8C48();
    v0 = t6;
    v3 = lbl_8_bss_2C0.unk_0;
    v0 = v3;
    lbl_8_bss_2C0.unk_0 = (v0 - 1);
    } else {
    lbl_8_bss_2C0.unk_0 = (v0 - 1);
    if ((s32)v0 <= 0) {
    t7 = fn_8_8E00();
    v0 = t7;
    }
    }
    return v0;
}
/* fzgx:end fn_8_68F4 */

/* fzgx:begin fn_8_69D8 */
extern struct fn_8_69D8_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_412A0(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 lbl_801A66B4;
extern u32 lbl_8_bss_2B0;
extern u32 lbl_8_data_8AD4;

struct fn_8_69D8_lbl_801A6410 {
    u32 unk_0;
};

void fn_8_69D8(void) {
    if ((s32)lbl_801A66B4 == 5) {
    fn_1_412A0(4);
    } else {
    fn_1_412A0(5);
    }
    if (lbl_8_bss_2B0 != 0) {
    fn_1_46B4(lbl_801A6410.unk_0, lbl_8_bss_2B0, (u32)&lbl_8_data_8AD4, 1199);
    lbl_8_bss_2B0 = 0;
    }
}
/* fzgx:end fn_8_69D8 */

/* fzgx:begin fn_8_6A50 */
struct fn_8_6A50_lbl_8_bss_2A8 {
    u32 unk_0;
    u8 pad_4[0x14];
    u32 unk_18;
    u32 unk_1C;
};

extern struct fn_8_6A50_lbl_8_bss_2A8 lbl_8_bss_2A8;

void fn_8_6A50(void) {
    struct fn_8_6A50_lbl_8_bss_2A8 *p_lbl_8_bss_2A8;
    p_lbl_8_bss_2A8 = (struct fn_8_6A50_lbl_8_bss_2A8 *)&lbl_8_bss_2A8;
    p_lbl_8_bss_2A8->unk_1C = 0;
    p_lbl_8_bss_2A8->unk_18 = 4;
    p_lbl_8_bss_2A8->unk_0 = 0;
}
/* fzgx:end fn_8_6A50 */

/* fzgx:begin fn_8_6A70 */
struct fn_8_6A70_lbl_8_bss_2A8 {
    u8 pad_0[0x18];
    u32 unk_18;
    u8 pad_1C[0x4];
    u32 unk_20;
    u8 pad_24[0xF0];
    u32 unk_114;
    u32 unk_118;
    u32 unk_11C;
    u32 unk_120;
};

struct fn_8_6A70_lbl_801A63C0 {
    u32 unk_0;
};

extern struct fn_8_6A70_lbl_801A63C0 lbl_801A63C0;
extern struct fn_8_6A70_lbl_8_bss_2A8 lbl_8_bss_2A8;
extern u32 lbl_801A66B4;
extern u32 fn_1_3EB78(u32, u32, u32, u32);
extern u32 fn_1_3ED8C(u32, u32, u32, u32, u32, u32, u32);
extern u32 fn_8_BD08(void);
extern void fn_8_663C(void);
extern void fn_8_67F8(u32, u32, u32, u32);
extern void fn_1_3EF08(u8);
extern void fn_1_3EF8C(u8);
extern void fn_1_3EFF0(u32, u8);
extern void fn_1_3F02C(u32);
extern void fn_1_411A4(u32);
extern void fn_80008BEC(void *, int, u32);

void fn_8_6A70(void) {
    struct fn_8_6A70_lbl_8_bss_2A8 *p_lbl_8_bss_2A8;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    s32 v4;
    s32 v5;
    u32 v6;
    u32 v7;

    p_lbl_8_bss_2A8 = (struct fn_8_6A70_lbl_8_bss_2A8 *)&lbl_8_bss_2A8;
    v0 = p_lbl_8_bss_2A8->unk_18;
    if ((s32)v0 == 1) {
        v0 = 0x2AAB0000;
        v1 = lbl_801A63C0.unk_0;
        v2 = (v0 - 21845);
        v0 = (v1 * (0x676A0000 + 19307));
        v3 = (v0 + 13259);
        v0 = ((v3 >> 16) & 0x7FFF);
        lbl_801A63C0.unk_0 = v3;
        v4 = ((s32)v0 >> 8);
        v5 = v4 % 6;
        switch (v5) {
        case 0:
            v6 = 31;
            break;
        case 1:
            v6 = 32;
            break;
        case 2:
            v6 = 33;
            break;
        case 3:
            v6 = 34;
            break;
        case 4:
            v6 = 35;
            break;
        default:
            v6 = 36;
        }
        v0 = 6;
        fn_1_3EF8C(v0);
        v0 = 0;
        fn_1_3ED8C(v0, 3, 1, (v6 & 0xFF), 10, 15, 0);
        v0 = 0;
        fn_1_3EB78(v0, 0, 0, 0);
        v0 = (u32)&fn_8_663C;
        fn_1_3EFF0(v0, 1);
        v0 = (u32)&fn_8_67F8;
        fn_1_3F02C(v0);
        v0 = 0;
        fn_1_3EF08(v0);
        p_lbl_8_bss_2A8->unk_20 = 0;
        if ((s32)lbl_801A66B4 == 5) {
            v0 = 4;
            fn_1_411A4(v0);
        } else {
            v0 = 5;
            fn_1_411A4(v0);
        }
        v7 = p_lbl_8_bss_2A8->unk_18;
        p_lbl_8_bss_2A8->unk_18 = (v7 - 1);
        fn_80008BEC((void *)((u8 *)p_lbl_8_bss_2A8 + 36), 0, 60);
        v0 = (u32)((u8 *)p_lbl_8_bss_2A8 + 96);
        fn_80008BEC((void *)v0, 0, 60);
        v0 = (u32)((u8 *)p_lbl_8_bss_2A8 + 156);
        fn_80008BEC((void *)v0, 0, 60);
        v0 = (u32)((u8 *)p_lbl_8_bss_2A8 + 216);
        fn_80008BEC((void *)v0, 0, 60);
        p_lbl_8_bss_2A8->unk_114 = 0;
        p_lbl_8_bss_2A8->unk_118 = 0;
        p_lbl_8_bss_2A8->unk_11C = 0;
        p_lbl_8_bss_2A8->unk_120 = 0;
    } else {
        p_lbl_8_bss_2A8->unk_18 = (v0 - 1);
        if ((s32)v0 <= 0) {
            fn_8_BD08();
        }
    }
}
/* fzgx:end fn_8_6A70 */

/* fzgx:begin fn_8_6C50 */
extern u32 fn_1_412A0(u32);
extern u32 lbl_801A66B4;

void fn_8_6C50(void) {
    if ((s32)lbl_801A66B4 == 5) {
    fn_1_412A0(4);
    } else {
    fn_1_412A0(5);
    }
}
/* fzgx:end fn_8_6C50 */

/* fzgx:begin fn_8_8C44 */
// fn_8_8C44: empty in retail (single blr).
void fn_8_8C44(void) {
}
/* fzgx:end fn_8_8C44 */

/* fzgx:begin fn_8_8C48 */
struct fn_8_8C48_lbl_8_bss_2A8 {
    u8 pad_0[0x124];
    u32 unk_124;
    u8 pad_128[0x4];
    u32 unk_12C;
    u32 unk_130;
    u32 unk_134;
    u32 unk_138;
};

extern struct fn_8_8C48_lbl_8_bss_2A8 lbl_8_bss_2A8;
extern u32 lbl_1_bss_26C60;
extern void fn_8_5FD4(void);

void fn_8_8C48(void) {
    struct fn_8_8C48_lbl_8_bss_2A8 *p_lbl_8_bss_2A8;
    p_lbl_8_bss_2A8 = (struct fn_8_8C48_lbl_8_bss_2A8 *)&lbl_8_bss_2A8;
    lbl_1_bss_26C60 = (u32)fn_8_5FD4;
    p_lbl_8_bss_2A8->unk_12C = 0;
    p_lbl_8_bss_2A8->unk_124 = 0;
    p_lbl_8_bss_2A8->unk_130 = 0;
    p_lbl_8_bss_2A8->unk_134 = -1;
    p_lbl_8_bss_2A8->unk_138 = 0;
}
/* fzgx:end fn_8_8C48 */

/* fzgx:begin fn_8_8C80 */
struct fn_8_8C80_ctx {
    u8 pad_0[0x13c];
    u32 unk_13C[9];
    u32 unk_160[9];
    u32 unk_184[9];
    u32 unk_1A8[9];
    u32 unk_1CC[9][4];
};

struct fn_8_8C80_lbl_801A6410 {
    u32 unk_0;
};

extern struct fn_8_8C80_ctx lbl_8_bss_2A8;
extern struct fn_8_8C80_lbl_801A6410 lbl_801A6410;
extern u8 lbl_8_data_8AD4[];
extern void fn_1_469BC(void);
extern u32 fn_1_46EE8(void);
extern void fn_1_46B4(u32, u32, const char *, int);

void fn_8_8C80(void) {
    u32 base;
    u32 *v0;
    u32 *v1;
    u32 *v2;
    u32 *v3;
    u32 (*v4)[4];
    s32 v5;
    s32 v6;
    u32 v7;

    base = (u32)&lbl_8_bss_2A8;
    fn_1_469BC();
    fn_1_46EE8();
    v0 = (u32 *)(base + 0x13c);
    v1 = (u32 *)(base + 0x160);
    v2 = (u32 *)(base + 0x184);
    v3 = (u32 *)(base + 0x1a8);
    v4 = (u32 (*)[4])(base + 0x1cc);
    for (v5 = 0; v5 < 9; v5++) {
        if (v0[0] != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, v0[0], (const char *)&lbl_8_data_8AD4, 1975);
            v0[0] = 0;
        }
        if (v1[0] != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, v1[0], (const char *)&lbl_8_data_8AD4, 1979);
            v1[0] = 0;
        }
        if (v2[0] != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, v2[0], (const char *)&lbl_8_data_8AD4, 1983);
            v2[0] = 0;
        }
        if (v3[0] != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, v3[0], (const char *)&lbl_8_data_8AD4, 1987);
            v3[0] = 0;
        }
        v7 = 0;
        for (v6 = 0; v6 < 4; v6++) {
            if (v4[0][v6] != 0) {
                fn_1_46B4(lbl_801A6410.unk_0, v4[0][v6], (const char *)&lbl_8_data_8AD4, 1992);
                v4[0][v6] = v7;
            }
        }
        v0++;
        v1++;
        v2++;
        v3++;
        v4++;
    }
}
/* fzgx:end fn_8_8C80 */

/* fzgx:begin fn_8_9B04 */
extern struct fn_8_9B04_lbl_8_bss_2A8 lbl_8_bss_2A8;
extern u32 fn_80008BA8(u32, u32, u32);
extern u32 fn_8_5C54(u32);

struct fn_8_9B04_lbl_8_bss_2A8 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x130];
    u32 unk_13C;
    u8 pad_140[0x11C];
    u32 unk_25C;
};

void fn_8_9B04(void) {
    fn_80008BA8(lbl_8_bss_2A8.unk_8, lbl_8_bss_2A8.unk_13C, lbl_8_bss_2A8.unk_25C);
    fn_8_5C54(1);
}
/* fzgx:end fn_8_9B04 */

/* fzgx:begin fn_8_9B40 */
// fn_8_9B40: empty in retail (single blr).
void fn_8_9B40(void) {
}
/* fzgx:end fn_8_9B40 */

/* fzgx:begin fn_8_BC04 noprologue */
#include "types.h"

struct fn_8_BC04_lbl_8_bss_2A8 {
    u8 pad_0[0x124];
    s32 unk_124;
    s32 unk_128;
};

extern f32 lbl_8_rodata_198[89];
extern struct fn_8_BC04_lbl_8_bss_2A8 lbl_8_bss_2A8;
extern u32 fn_1_5370(s8, u32);
extern void fn_80008BEC(void *, int, u32);
extern void fn_8006CE1C(f32);

void fn_8_BC04(void) {
    struct fn_8_BC04_lbl_8_bss_2A8 *p;

    p = &lbl_8_bss_2A8;
    if (p->unk_124 == p->unk_128 / 2) {
        fn_80008BEC((u8 *)p + 36, 0, 60);
        fn_80008BEC((u8 *)p + 96, 0, 60);
        fn_80008BEC((u8 *)p + 156, 0, 60);
        fn_80008BEC((u8 *)p + 216, 0, 60);
        fn_1_5370(1, 0);
    }
    fn_8006CE1C(lbl_8_rodata_198[0] - (f32)__fabs((f32)(p->unk_124 - p->unk_128 / 2)) / (f32)(p->unk_128 / 2));
}
/* fzgx:end fn_8_BC04 */

/* fzgx:begin fn_8_C7B0 */
extern f32 lbl_8_rodata_2FC[27];
extern u32 fn_800371F8(u32, void *);
extern void fn_8003462C(u32, u32, u32);
extern void fn_8007245C(u32);
extern void fn_80072864(u32);
extern void fn_800728A8(s32, s32, s32, s32);
extern void fn_80072AB0(s32, s32, s32);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern void fn_80072CC4(u32, u32, u32, u32, u32);
extern void fn_80072D64(u32, u32, u32, u32, u32, u32);
extern void fn_80072E20(s32, s32, s32, s32, u8, s32);
extern void fn_800734A8(u32, s32, s32, s32);
extern void fn_80073678(u32);
extern void fn_80073C6C(s32);
extern void fn_80074660(u32);
extern void fn_80074788(u32);
extern void fn_800747D0(u32, u32, u32, u32, u32, u32, u32);
extern void fn_80074918(u8, s32, u8);

void fn_8_C7B0(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u32 loc_8;

    fn_80074918(1, 7, 1);
    fn_80074788(1);
    fn_80074660(0);
    fn_80073678(1);
    fn_80073C6C(0);
    fn_800747D0(4, 0, 0, 0, 0, 2, 2);
    fn_80072AB0(0, 0, 0);
    fn_800734A8(0, 255, 255, 4);
    fn_80072C24(0, 15, 15, 15, 2);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 7, 7, 1);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_800728A8(1, 4, 5, 0);
    fn_80072864(2);
    fn_8007245C(512);
    loc_8 = *(u32 *)((u8 *)arg0 + 0);
    fn_800371F8(1, (void *)&loc_8);
    fn_8003462C(128, 7, 4);
    *(f32 *)((u8 *)0xCC008000) = arg3;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg1;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = lbl_8_rodata_2FC[0];  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg4;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg1;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = lbl_8_rodata_2FC[0];  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg4;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg2;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = lbl_8_rodata_2FC[0];  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg3;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = arg2;  /* fzgx-allow: A1,A2 GX FIFO write port */
    *(f32 *)((u8 *)0xCC008000) = lbl_8_rodata_2FC[0];  /* fzgx-allow: A1,A2 GX FIFO write port */
    fn_80074918(1, 3, 1);
}
/* fzgx:end fn_8_C7B0 */

/* fzgx:begin fn_8_CC2C */
struct OperationValue {
    f32 value;
    u8 unk04[0x08];
    f32 delta;
};

struct OperationState {
    u8 unk00[0x54];
    f32 delta;
};

void fn_8_CC2C(struct OperationState *state, struct OperationValue *value) {
    f32 current;
    f32 delta;

    current = value->value;
    value->value = current + (delta = state->delta);
    value->delta = value->delta + delta;
}
/* fzgx:end fn_8_CC2C */

/* fzgx:begin fn_8_CF58 */
// fn_8_CF58: returns a constant.
int fn_8_CF58(void) {
    return 0;
}
/* fzgx:end fn_8_CF58 */

/* fzgx:begin fn_8_CF60 */
// fn_8_CF60: returns a constant.
int fn_8_CF60(void) {
    return 0;
}
/* fzgx:end fn_8_CF60 */

/* fzgx:begin fn_8_CF68 */
// fn_8_CF68: returns a constant.
int fn_8_CF68(void) {
    return 2;
}
/* fzgx:end fn_8_CF68 */

/* fzgx:begin fn_8_CF70 */
extern u32 fn_1_D0790(void);

s32 fn_8_CF70(void) {
    fn_1_D0790();
    return 0;
}
/* fzgx:end fn_8_CF70 */

/* fzgx:begin fn_8_CF94 */
extern u32 fn_1_5370(u32, u32);
extern void fn_8_CF58(void);
extern void fn_8_CF60(void);
extern void fn_8_CF68(void);
extern void fn_8_CF70(void);

struct fn_8_CF94_Arg0 {
    u32 unk_0;
    u8 pad_4[0xA4];
    u32 unk_A8;
    u32 unk_AC;
    u8 pad_B0[0x14];
    u32 unk_C4;
    u8 pad_C8[0x4];
    u32 unk_CC;
};

void fn_8_CF94(struct fn_8_CF94_Arg0 *arg0) {
    arg0->unk_A8 = (u32)fn_8_CF58;
    arg0->unk_C4 = (u32)fn_8_CF68;
    arg0->unk_CC = (u32)fn_8_CF60;
    arg0->unk_AC = (u32)fn_8_CF70;
    arg0->unk_0 = (arg0->unk_0 | 513);
    arg0->unk_0 = ((arg0->unk_0 | 0x200000) | 256);
    arg0->unk_0 = (arg0->unk_0 | 32768);
    arg0->unk_0 = (arg0->unk_0 | 0x1000000);
    fn_1_5370(1, 0);
}
/* fzgx:end fn_8_CF94 */

/* fzgx:begin fn_8_D020 */
// fn_8_D020: empty in retail (single blr).
void fn_8_D020(void) {
}
/* fzgx:end fn_8_D020 */

/* fzgx:begin fn_8_D024 */
extern u32 lbl_8_bss_544;

void fn_8_D024(void) {
    lbl_8_bss_544 = 4;
}
/* fzgx:end fn_8_D024 */

/* fzgx:begin fn_8_D5F4 */
extern u32 fn_1_14BD74(u32);
extern u32 fn_1_15555C(u32);
extern u32 fn_1_48140(u32);

void fn_8_D5F4(void) {
    u32 t2, t3;
    fn_1_48140(149);
    fn_1_48140(152);
    t2 = fn_1_48140(151);
    t3 = fn_1_15555C(t2);
    fn_1_14BD74(t3);
}
/* fzgx:end fn_8_D5F4 */
