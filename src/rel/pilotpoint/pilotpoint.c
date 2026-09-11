#include "types.h"

/* fzgx:begin _epilog */
struct _epilog_lbl_14_bss_0 {
    u8 pad_0[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u32 unk_20;
};
struct _epilog_lbl_801A6410 {
    u32 unk_0;
};

extern struct _epilog_lbl_14_bss_0 lbl_14_bss_0;
extern struct _epilog_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_1596DC(u32);
extern u32 fn_1_412A0(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_A0AA4(void);
extern u32 lbl_14_data_2FB0;
extern void fn_1_41A8(void);
extern void fn_1_46B4(u32, u32, const char *, int);
extern void fn_1_47A60(s16);
extern void fn_1_484CC(s32);

void _epilog(void) {
    struct _epilog_lbl_14_bss_0 *p_lbl_14_bss_0;
    p_lbl_14_bss_0 = (struct _epilog_lbl_14_bss_0 *)&lbl_14_bss_0;
    fn_1_435C(p_lbl_14_bss_0->unk_1C);
    fn_1_41A8();
    fn_1_435C(p_lbl_14_bss_0->unk_20);
    fn_1_41A8();
    fn_1_1596DC(2);
    fn_1_47A60(1);
    fn_1_47A60(13);
    fn_1_484CC(2);
    fn_1_412A0(1);
    fn_1_A0AA4();
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_14_bss_0->unk_14, (const char *)&lbl_14_data_2FB0, 860);
    p_lbl_14_bss_0->unk_14 = 0;
}
/* fzgx:end _epilog */

/* fzgx:begin fn_14_220 */
extern struct fn_14_220_lbl_14_bss_1C lbl_14_bss_1C;
extern struct fn_14_220_lbl_14_bss_20 lbl_14_bss_20;
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_435C(u32);

struct fn_14_220_lbl_14_bss_1C {
    u32 unk_0;
};
struct fn_14_220_lbl_14_bss_20 {
    u32 unk_0;
};

void fn_14_220(void) {
    u32 t0, t1, t3;
    t0 = fn_1_435C(lbl_14_bss_1C.unk_0);
    t1 = fn_1_407C(t0);
    fn_1_3CC4(t1);
    t3 = fn_1_435C(lbl_14_bss_20.unk_0);
    fn_1_407C(t3);
}
/* fzgx:end fn_14_220 */

/* fzgx:begin fn_14_268 */
struct fn_14_268_lbl_1_bss_8B3A0 {
    u8 pad_0[0x124];
    u32 unk_124;
};

struct fn_14_268_lbl_14_bss_0 {
    u32 unk_0;
};

extern struct fn_14_268_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern struct fn_14_268_lbl_14_bss_0 lbl_14_bss_0;

u32 fn_14_268(void) {
    u32 v0;

    lbl_14_bss_0.unk_0--;
    v0 = lbl_1_bss_8B3A0.unk_124;
    if (v0 + 0x10000 != 0xffff) {
        lbl_1_bss_8B3A0.unk_124 = v0 - 1;
    }
    return (u32)v0;
}
/* fzgx:end fn_14_268 */

/* fzgx:begin fn_14_2A0 */
typedef u32 (*fn_14_2A0_Fn0)(void);
struct fn_14_2A0_Entry {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};

extern s16 lbl_1_bss_962;
extern u8 lbl_14_data_308[128];
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_14_2A0(void) {
    struct fn_14_2A0_Entry *entry;
    s32 index;
    entry = (struct fn_14_2A0_Entry *)lbl_14_data_308;
    index = lbl_1_bss_962;
    entry += index - 172;
    lbl_1_bss_71688 = entry->unk_8;
    lbl_1_bss_7168C = entry->unk_C;
    ((fn_14_2A0_Fn0)entry->unk_4)();
}
/* fzgx:end fn_14_2A0 */

/* fzgx:begin fn_14_2FC */
struct fn_14_2FC_lbl_1_bss_8B3A0 {
    u8 pad_0[0x94];
    u32 unk_94;
};
struct fn_14_2FC_lbl_14_bss_0 {
    u32 unk_0;
    u8 pad_4[0x20];
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
};

extern struct fn_14_2FC_lbl_14_bss_0 lbl_14_bss_0;
extern struct fn_14_2FC_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern u32 fn_1_12F1E8(u32);
extern u32 fn_1_A2D84(u32);

void fn_14_2FC(void) {
    u32 v0;
    struct fn_14_2FC_lbl_1_bss_8B3A0 *p_lbl_1_bss_8B3A0;
    p_lbl_1_bss_8B3A0 = &lbl_1_bss_8B3A0;
    lbl_14_bss_0.unk_0 = 60;
    v0 = p_lbl_1_bss_8B3A0->unk_94;
    lbl_14_bss_0.unk_24 = 24;
    lbl_14_bss_0.unk_28 = 24;
    lbl_14_bss_0.unk_2C = 16;
    lbl_14_bss_0.unk_30 = 16;
    lbl_14_bss_0.unk_34 = 12;
    p_lbl_1_bss_8B3A0->unk_94 = (v0 | 0x40000000);
    fn_1_12F1E8(539);
    p_lbl_1_bss_8B3A0->unk_94 = v0;
    fn_1_A2D84(0xA9110000);
}
/* fzgx:end fn_14_2FC */

/* fzgx:begin fn_14_900 */
// fn_14_900: empty in retail (single blr).
void fn_14_900(void) {
}
/* fzgx:end fn_14_900 */

/* fzgx:begin fn_14_258C */
// fn_14_258C: empty in retail (single blr).
void fn_14_258C(void) {
}
/* fzgx:end fn_14_258C */

/* fzgx:begin fn_14_2AFC */
struct PilotPoint {
    s16 unk0;
    u8 pad_2[0x35E];
    s16 unk360;
    u8 pad_362[0x35E];
    s16 unk6C0;
    u8 pad_6C2[0x35E];
};

extern s16 fn_14_32DC(s16 *);
extern s16 fn_14_3384(s16 *);
extern struct PilotPoint * lbl_14_bss_8340;
extern u32 fn_14_3334(s16 *);
extern u32 fn_14_33DC(s16 *);
extern u32 fn_14_342C(void);
extern u32 fn_14_34A8(void);
extern u32 fn_14_DC2C(void);
extern u8 * fn_1_36AD0(void);
extern void * fn_14_316C(void *, void *, void *);
extern void * fn_14_3230(void *, void *, void *);

void fn_14_2AFC(void) {
    struct PilotPoint *v0;
    s32 v5;
    s16 loc_10[6];
    s16 loc_C[2];
    s16 loc_A;
    s16 loc_8;
    u8 * t9;
    fn_14_316C((void *)loc_C, (void *)&loc_A, (void *)&loc_8);
    v0 = lbl_14_bss_8340;
    loc_C[0] = v0[loc_C[0]].unk0;
    loc_A = v0[loc_A].unk360;
    loc_8 = v0[loc_8].unk6C0;
    fn_14_342C();
    fn_14_3230((void *)loc_C, (void *)&loc_A, (void *)&loc_8);
    if (loc_C[0] != 15) {
        loc_C[0] = lbl_14_bss_8340[loc_C[0]].unk0;
    }
    if (loc_A != 15) {
        loc_A = lbl_14_bss_8340[loc_A].unk360;
    }
    if (loc_8 != 15) {
        loc_8 = lbl_14_bss_8340[loc_8].unk6C0;
    }
    fn_14_34A8();
    loc_10[0] = 75;
    loc_10[1] = 75;
    loc_10[2] = 75;
    fn_14_32DC(loc_10);
    loc_10[0] = 75;
    loc_10[1] = 75;
    loc_10[2] = 75;
    loc_10[3] = 75;
    loc_10[4] = 75;
    loc_10[5] = 75;
    fn_14_3334(loc_10);
    loc_10[0] = 41;
    fn_14_3384(loc_10);
    loc_10[0] = 41;
    fn_14_33DC(loc_10);
    v5 = (fn_14_DC2C() & 0xFF) * (0x10000 - 32320);
    t9 = (u8 *)(fn_1_36AD0());
    *(u32 *)((u8 *)t9 + v5) = (*(u32 *)((u8 *)t9 + v5) | 0xC0000000); /* fzgx-allow: A1 bit-set mask, not an address */
}
/* fzgx:end fn_14_2AFC */

/* fzgx:begin fn_14_315C */
extern struct fn_14_315C_lbl_14_bss_110 lbl_14_bss_110;

struct fn_14_315C_lbl_14_bss_110 {
    u8 pad_0[0x4C];
    u32 unk_4C;
};

void fn_14_315C(u32 arg0) {
    lbl_14_bss_110.unk_4C = arg0;
}
/* fzgx:end fn_14_315C */

/* fzgx:begin fn_14_3230 */
struct PilotPointEntry {
    u32 raw[2];
};

extern struct PilotPointEntry lbl_14_bss_110[10];
extern s16 lbl_14_bss_160[16];

void fn_14_3230(u16 *arg0, u16 *arg1, u16 *arg2) {
    s16 count;
    s16 index;

    index = 0;
    count = 0;

    *arg2 = 15;
    *arg1 = 15;
    *arg0 = 15;

    while ((u32)(s16)count < 8) {
        if ((((u32 *)&lbl_14_bss_110[count])[3] & 0x8) &&
            (((u32 *)&lbl_14_bss_110[count])[3] & 0x40)) {
            s16 quotient = index / lbl_14_bss_160[0];
            switch (quotient) {
            case 0:
                *arg0 = 0;
                break;
            case 1:
                *arg1 = 0;
                break;
            case 2:
                *arg2 = 0;
                break;
            }
        }
        index++, count++;
    }
}
/* fzgx:end fn_14_3230 */

/* fzgx:begin fn_14_32DC */
struct PilotPointEntry {
    u32 raw[2];
};

extern struct PilotPointEntry lbl_14_bss_110[10];

s16 fn_14_32DC(s16 *out) {
    s16 i;
    s16 count;

    count = 0;
    i = 0;
    while ((u32)(s16)i < 8) {
        if ((((u32 *)&lbl_14_bss_110[i])[3] & 0x8) &&
            (((u32 *)&lbl_14_bss_110[i])[3] & 0x40)) {
            out[(s16)count] = ((s16 *)&lbl_14_bss_110[i])[4];
            count++;
        }
        i++;
    }
    return count;
}
/* fzgx:end fn_14_32DC */

/* fzgx:begin fn_14_3334 */
extern u32 lbl_14_bss_110[20];

s16 fn_14_3334(s16 *out) {
    s16 i;
    s16 count;
    count = 0;
    i = 0;

    while ((u32)i < 8) {
        if (((u32 *)&lbl_14_bss_110[i * 2])[3] & 0x8) {
            out[count++] = ((s16 *)&lbl_14_bss_110[i * 2])[4];
        }
        i++;
    }

    return count;
}
/* fzgx:end fn_14_3334 */

/* fzgx:begin fn_14_3384 */
extern u32 lbl_14_bss_110[20];

s16 fn_14_3384(s16 *out) {
    s16 i;
    s16 count;
    u32 flags;
    count = 0;
    i = 0;

    while ((u32)i < 8) {
        flags = ((u32 *)&lbl_14_bss_110[i * 2])[3];
        if ((flags & 0x10) && (flags & 0x40)) {
            out[count++] = ((s16 *)&lbl_14_bss_110[i * 2])[4];
        }
        i++;
    }

    return count;
}
/* fzgx:end fn_14_3384 */

/* fzgx:begin fn_14_33DC */
extern u32 lbl_14_bss_110[20];

s16 fn_14_33DC(s16 *out) {
    s16 i;
    s16 count;
    count = 0;
    i = 0;

    while ((u32)i < 8) {
        if (((u32 *)&lbl_14_bss_110[i * 2])[3] & 0x10) {
            out[count++] = ((s16 *)&lbl_14_bss_110[i * 2])[4];
        }
        i++;
    }

    return count;
}
/* fzgx:end fn_14_33DC */

/* fzgx:begin fn_14_34A8 */
extern u32 lbl_14_bss_110[20];
extern u32 lbl_14_bss_8350;
extern f32 lbl_14_bss_8354[936];

u32 fn_14_34A8(void) {
    u32 result;
    u32 flags;
    s16 i;

    result = lbl_14_bss_8350;
    i = 0;
    while ((u32)i < 8) {
        flags = ((u32 *)&lbl_14_bss_110[i * 2])[3];
        if ((flags & 0x10) && (flags & 0x40)) {
            result = (u32)&lbl_14_bss_8354;
            break;
        }
        i++;
    }
    return result;
}
/* fzgx:end fn_14_34A8 */

/* fzgx:begin fn_14_600C */
extern struct fn_14_600C_lbl_14_bss_92E8 lbl_14_bss_92E8;
extern u32 fn_80074188(u32, u32, u32, u32);

struct fn_14_600C_lbl_14_bss_92E8 {
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
    s16 unk_6;
};

void fn_14_600C(void) {
    fn_80074188(lbl_14_bss_92E8.unk_0, lbl_14_bss_92E8.unk_2, lbl_14_bss_92E8.unk_4, lbl_14_bss_92E8.unk_6);
}
/* fzgx:end fn_14_600C */

/* fzgx:begin fn_14_645C */
extern struct fn_14_645C_lbl_14_bss_92F0 lbl_14_bss_92F0;
extern u32 fn_80074188(u32, u32, u32, u32);

struct fn_14_645C_lbl_14_bss_92F0 {
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
    s16 unk_6;
};

void fn_14_645C(void) {
    fn_80074188(lbl_14_bss_92F0.unk_0, lbl_14_bss_92F0.unk_2, lbl_14_bss_92F0.unk_4, lbl_14_bss_92F0.unk_6);
}
/* fzgx:end fn_14_645C */

/* fzgx:begin fn_14_7E04 */
extern struct fn_14_7E04_lbl_14_bss_20 lbl_14_bss_20;
extern struct fn_14_7E04_lbl_14_bss_92C0 lbl_14_bss_92C0;
extern struct fn_14_7E04_lbl_1_bss_6EAD0_T *lbl_1_bss_6EAD0;
extern u32 fn_14_2590(void);
extern u32 fn_14_2C80(void);
extern u32 fn_1_12F1E8(u32);
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_A1588(u32, u32);
extern u32 fn_1_A2D84(u32);
extern u32 lbl_14_bss_92BC;
extern u32 lbl_14_bss_92F8;
extern u32 lbl_14_data_2F48;
extern u32 lbl_14_data_3048;
extern void fn_14_7584(void);

struct fn_14_7E04_lbl_14_bss_20 {
    u32 unk_0;
};
struct fn_14_7E04_lbl_14_bss_92C0 {
    u32 unk_0;
};
struct fn_14_7E04_lbl_1_bss_6EAD0_T {
    u32 unk_0;
};

void fn_14_7E04(void) {
    u32 t4;
    fn_14_2590();
    fn_14_2C80();
    fn_1_12F1E8(2400);
    fn_1_435C(lbl_14_bss_20.unk_0);
    t4 = fn_1_3F8C((u32)&lbl_14_data_3048, (u32)fn_14_7584, 0, 8);
    lbl_14_data_2F48 = t4;
    lbl_14_bss_92F8 = -1;
    fn_1_A1588(lbl_1_bss_6EAD0->unk_0, 15);
    lbl_14_bss_92C0.unk_0 = 1;
    lbl_14_bss_92BC = 0;
    fn_1_A2D84((0xA9070000 + 10752));
}
/* fzgx:end fn_14_7E04 */

/* fzgx:begin fn_14_A1F4 */
extern u32 fn_1_412A0(u32);
extern u32 fn_1_48140(u32);
extern u32 lbl_801A66B4;

void fn_14_A1F4(void) {
    fn_1_48140(151);
    fn_1_48140(141);
    if ((s32)lbl_801A66B4 == 5) {
    fn_1_412A0(4);
    } else {
    fn_1_412A0(5);
    }
}
/* fzgx:end fn_14_A1F4 */

/* fzgx:begin fn_14_A244 */
extern struct fn_14_A244_lbl_14_bss_20 lbl_14_bss_20;
extern u16 lbl_14_bss_9452;
extern u32 fn_1_12F1E8(u32);
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_47F74(u32);
extern u32 lbl_14_data_30D4;
extern void fn_14_A3DC(void);

struct fn_14_A244_lbl_14_bss_20 {
    u32 unk_0;
};

void fn_14_A244(void) {
    u32 t3;
    fn_1_47F74(151);
    fn_1_12F1E8(4800);
    fn_1_435C(lbl_14_bss_20.unk_0);
    t3 = fn_1_3F8C((u32)&lbl_14_data_30D4, (u32)fn_14_A3DC, 0, 8);
    lbl_14_bss_9452 = t3;
}
/* fzgx:end fn_14_A244 */

/* fzgx:begin fn_14_A398 */
extern struct fn_14_A398_lbl_14_bss_20 lbl_14_bss_20;
extern struct fn_14_A398_lbl_14_bss_9452 lbl_14_bss_9452;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_48140(u32);

struct fn_14_A398_lbl_14_bss_20 {
    u32 unk_0;
};
struct fn_14_A398_lbl_14_bss_9452 {
    s16 unk_0;
};

void fn_14_A398(void) {
    fn_1_48140(151);
    fn_1_435C(lbl_14_bss_20.unk_0);
    fn_1_426C(lbl_14_bss_9452.unk_0);
}
/* fzgx:end fn_14_A398 */

/* fzgx:begin fn_14_B398 */
extern struct fn_14_B398_lbl_14_bss_9460 lbl_14_bss_9460;
extern struct fn_14_B398_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern u32 fn_1_128DD8(u32);
extern u32 fn_1_128E8C(u32, u32);
extern u32 fn_1_159AE0(void);
extern u32 fn_1_A2D84(u32);
extern u32 lbl_14_bss_0;
extern u32 lbl_14_bss_9464;

struct fn_14_B398_lbl_1_bss_8B3A0 {
    u8 pad_0[0x90];
    s16 unk_90;
};
struct fn_14_B398_lbl_14_bss_9460 {
    u32 unk_0;
};

void fn_14_B398(void) {
    u32 t0;
    lbl_14_bss_9460.unk_0 = 0;
    lbl_14_bss_0 = 480;
    t0 = fn_1_128DD8((lbl_1_bss_8B3A0.unk_90 & 0xFF));
    fn_1_128E8C(t0, (u32)&lbl_14_bss_9464);
    fn_1_159AE0();
    fn_1_A2D84((0xA9120000 + 10240));
}
/* fzgx:end fn_14_B398 */

/* fzgx:begin fn_14_B400 */
struct fn_14_B400_lbl_1_bss_D58 {
    u8 pad_0[0x8];
    u16 unk_8;
};
struct fn_14_B400_lbl_1_bss_6EAB4 {
    u32 unk_0;
};

extern f32 lbl_14_rodata_30;
extern struct fn_14_B400_lbl_1_bss_6EAB4 lbl_1_bss_6EAB4;
extern struct fn_14_B400_lbl_1_bss_D58 lbl_1_bss_D58;
extern u16 lbl_1_bss_96A;
extern u32 fn_14_B484(void);
extern u32 fn_14_DC90(f32);
extern u32 fn_1_13DC54(void);
extern u32 lbl_14_bss_0;
extern void fn_1_133DBC(void *);

void fn_14_B400(void) {
    fn_1_133DBC((void *)0);
    fn_1_13DC54();
    fn_14_B484();
    fn_14_DC90(lbl_14_rodata_30);
    if ((s32)lbl_14_bss_0 < 420 && (((lbl_1_bss_D58.unk_8 >> 8) & 0x1) != 0 || (s32)lbl_14_bss_0 < 0)) {
    lbl_1_bss_96A = 178;
    lbl_1_bss_6EAB4.unk_0 = (lbl_1_bss_6EAB4.unk_0 | 44);
    }
}
/* fzgx:end fn_14_B400 */

/* fzgx:begin fn_14_B480 */
// fn_14_B480: empty in retail (single blr).
void fn_14_B480(void) {
}
/* fzgx:end fn_14_B480 */

/* fzgx:begin fn_14_BCDC */
extern u32 lbl_14_bss_0;
extern u32 lbl_14_bss_9460;

void fn_14_BCDC(void) {
    lbl_14_bss_9460 = 0;
    lbl_14_bss_0 = 366;
}
/* fzgx:end fn_14_BCDC */

/* fzgx:begin fn_14_C4F4 */
// fn_14_C4F4: empty in retail (single blr).
void fn_14_C4F4(void) {
}
/* fzgx:end fn_14_C4F4 */

/* fzgx:begin fn_14_C4F8 */
struct fn_14_C4F8_lbl_1_bss_6EAB4 {
    u32 unk_0;
};

extern struct fn_14_C4F8_lbl_1_bss_6EAB4 lbl_1_bss_6EAB4;
extern u32 lbl_14_bss_0;

u32 fn_14_C4F8(void) {
    lbl_14_bss_0 = 60;
    lbl_1_bss_6EAB4.unk_0 = (lbl_1_bss_6EAB4.unk_0 | 44);
    return (u32)&lbl_1_bss_6EAB4;
}
/* fzgx:end fn_14_C4F8 */

/* fzgx:begin fn_14_C698 */
// fn_14_C698: empty in retail (single blr).
void fn_14_C698(void) {
}
/* fzgx:end fn_14_C698 */

/* fzgx:begin fn_14_C69C */
struct fn_14_C69C_Arg0 {
    char **unk_0;
    u32 unk_4;
    s32 unk_8;
};

extern char *strncpy(char *, const char *, size_t);
extern int sprintf(char *, const char *, ...);
extern size_t strlen(const char *);
extern u32 __cvt_fp2unsigned(f32);
extern void fn_1_4AE0C(const char *, ...);
extern f32 lbl_14_rodata_30;
extern f32 lbl_14_rodata_364;
extern const f64 lbl_14_rodata_110;
extern char lbl_14_data_300C[];
extern char lbl_14_data_3244[];
extern u32 lbl_801A66A0;
extern u32 lbl_801A66B4;

void fn_14_C69C(struct fn_14_C69C_Arg0 *arg0, f32 arg1) {
    char buf[256];

    if (arg0->unk_8 != 0 || lbl_14_rodata_30 == arg1) {
        sprintf(buf, lbl_14_data_300C, arg0->unk_0[lbl_801A66B4]);
        fn_1_4AE0C(buf);
        return;
    }
    if (arg1 < lbl_14_rodata_364) {
        f32 lenf = (f32)strlen(arg0->unk_0[lbl_801A66B4]);
        u32 n = __cvt_fp2unsigned(lenf * arg1);
        strncpy(buf, arg0->unk_0[lbl_801A66B4], n);
        if ((lbl_801A66A0 & 3) < 2) {
            buf[n] = '_';
            buf[n + 1] = 0;
        } else {
            buf[n] = 0;
        }
    } else if ((lbl_801A66A0 & 3) < 2) {
        sprintf(buf, lbl_14_data_3244, arg0->unk_0[lbl_801A66B4]);
    } else {
        sprintf(buf, lbl_14_data_300C, arg0->unk_0[lbl_801A66B4]);
    }
    fn_1_4AE0C(buf);
}
/* fzgx:end fn_14_C69C */

/* fzgx:begin fn_14_DC28 */
// fn_14_DC28: empty in retail (single blr).
void fn_14_DC28(void) {
}
/* fzgx:end fn_14_DC28 */

/* fzgx:begin fn_14_DC2C */
typedef struct LocalData {
    u8 data[0x1471];
    u8 field_1479;
    u8 field_147a;
    u8 tail[0x38];
} LocalData;

extern void fn_1_3EF14(void *);

u32 fn_14_DC2C(void) {
    LocalData local;
    u8 result;
    fn_1_3EF14(&local);
    if (local.field_147a != 0) {
        result = 0;
    } else {
        result = local.field_1479;
    }
    return result;
}
/* fzgx:end fn_14_DC2C */

/* fzgx:begin fn_14_DC6C */
extern u32 lbl_14_data_6C8;

u32 fn_14_DC6C(u32 arg0, u32 arg1) {
    return *(u32 *)((u8 *)((u8 *)&lbl_14_data_6C8 + ((s16)arg0 * 24)) + ((s16)arg1 << 2));
}
/* fzgx:end fn_14_DC6C */

/* fzgx:begin fn_14_DF70 */
extern s16 lbl_1_bss_8B3A0;
extern u8 fn_1_128DD8(u8);
extern void fn_1_128E8C(u8, void *);

s32 fn_14_DF70(void) {
    u8 buffer[40];
    s16 *p = &lbl_1_bss_8B3A0;

    if (*p++ == 9) {
        return 0;
    }

    fn_1_128E8C(fn_1_128DD8((u8)(p[0x47] & 0xFF)), buffer);

    if (buffer[0] == 8 && buffer[1] == 44 && *(u16 *)&buffer[2] == 287) {
        return 0;
    }

    return 1;
}
/* fzgx:end fn_14_DF70 */
