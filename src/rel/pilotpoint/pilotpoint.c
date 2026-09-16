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

/* fzgx:begin fn_14_380 */
#include "font.h"

#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.0f;
    s = 167.0f;
    s = 38.0f;
    s = 90.0f;
    s = 320.0f;
    s = 216.0f;
    s = 8.0f;
    s = 96.0f;
    s = 336.0f;
    s = 380.0f;
    d = 12.0;
    s = 1.0f;
    s = 99.0f;
    s = 30.0f;
    s = 140.0f;
    s = 178.0f;
    s = 254.0f;
    s = 292.0f;
    s = 541.0f;
    s = 575.0f;
    s = 98.0f;
    s = 42.0f;
}
static const u32 fzgx_pool_table2[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 4503601774854144.0;
}
#pragma section code_type ".text"

struct fn_14_380_Copy88 { u32 a[22]; };
struct fn_14_380_lbl_14_bss_0 {
    u32 unk_0;
    u8 pad_4[0x20];
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
};
struct fn_14_380_lbl_14_rodata_0 {
    u8 pad_0[0x4];
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f64 unk_28;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    f32 unk_44;
    f32 unk_48;
    f32 unk_4C;
    f32 unk_50;
    f32 unk_54;
    f32 unk_58;
    u8 pad_5C[0x4];
    f64 unk_60;
};
struct fn_14_380_lbl_14_data_D50 {
    u32 unk_0[1];
};

extern int fn_1_4F734(FontDrawPacket *);
extern struct fn_14_380_lbl_14_bss_0 lbl_14_bss_0;
extern struct fn_14_380_lbl_14_data_D50 lbl_14_data_D50;
extern struct fn_14_380_lbl_14_rodata_0 lbl_14_rodata_0;
extern u16 lbl_1_bss_96A;
extern u32 fn_1_134AD4(void);
extern u32 fn_1_13B328(u32, u32);
extern u32 fn_1_13DC54(void);
extern u32 lbl_1_rodata_26F8;
extern u32 lbl_801A66B4;
extern void fn_1_133DBC(void *);
extern void fn_1_138120(void *);
extern void fn_1_50164(f32, f32, f32, f32, FontDrawPacket *);

f32 fn_14_380(void) {
    struct fn_14_380_lbl_14_bss_0 *p_lbl_14_bss_0;
    struct fn_14_380_lbl_14_rodata_0 *p_lbl_14_rodata_0;
    f32 v1;
    f32 v0;
    f32 v18;
    u32 v2;
    u32 v3;
    u32 v4;
    f32 v5;
    f32 v6;
    f32 v7;
    f64 v8;
    f32 v9;
    f32 v10;
    f32 v11;
    f32 v12;
    f32 v13;
    f32 v14;
    f64 v16;
    f32 v17;
    f32 v19;
    f32 v20;
    f32 v21;
    f32 v22;
    f32 v23;
    f32 v24;
    f32 v25;
    f32 v26;
    f32 v27;
    f32 v28;
    f32 v29;
    f32 v30;
    f32 v31;
    f32 v32;
    f32 v33;
    f32 v34;
    f32 v35;
    f32 v36;
    f32 v37;
    f32 v38;
    f32 v39;
    f32 v40;
    f32 v41;
    f32 v42;
    f32 v43;
    f32 v44;
    f32 v45;
    f32 v46;
    f32 v47;
    f32 v48;
    f32 v49;
    u32 v50;
    FontDrawPacket loc_8;
    /* frame */
    p_lbl_14_rodata_0 = (struct fn_14_380_lbl_14_rodata_0 *)&lbl_14_rodata_0;
    p_lbl_14_bss_0 = (struct fn_14_380_lbl_14_bss_0 *)&lbl_14_bss_0;
    fn_1_133DBC((void *)0);
    fn_1_134AD4();
    fn_1_13DC54();
    fn_1_13B328(0x1000000, 1);
    fn_1_138120((void *)lbl_14_data_D50.unk_0[lbl_801A66B4]);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v0 = (167.0f);
    v1 = (38.0f);
    loc_8.image = (0x10000 - 28155);
    loc_8.x = v0;
    loc_8.y = v1;
    loc_8.z = (90.0f);
    loc_8.flags = 10;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    loc_8.image = (0x10000 - 25045);
    loc_8.flags = 10;
    p_lbl_14_bss_0->unk_28 += p_lbl_14_bss_0->unk_30;
    if ((s32)p_lbl_14_bss_0->unk_28 > 190) {
    p_lbl_14_bss_0->unk_28 = 190;
    p_lbl_14_bss_0->unk_24 += p_lbl_14_bss_0->unk_2C;
    }
    if ((s32)p_lbl_14_bss_0->unk_24 > 396) {
    p_lbl_14_bss_0->unk_24 = 396;
    }
    loc_8.x = (320.0f);
    loc_8.y = (216.0f);
    v5 = (8.0f);
    fn_1_50164((f32)(s32)p_lbl_14_bss_0->unk_24, (f32)(s32)p_lbl_14_bss_0->unk_28, v5, v5, (FontDrawPacket *)&loc_8);
    loc_8.x = (320.0f);
    loc_8.y = (96.0f);
    v9 = (8.0f);
    fn_1_50164((f32)(s32)p_lbl_14_bss_0->unk_24, (38.0f), v9, v9, (FontDrawPacket *)&loc_8);
    loc_8.x = (320.0f);
    loc_8.y = (336.0f);
    v11 = (8.0f);
    fn_1_50164((f32)(s32)p_lbl_14_bss_0->unk_24, (38.0f), v11, v11, (FontDrawPacket *)&loc_8);
    loc_8.x = (320.0f);
    loc_8.y = (380.0f);
    v13 = (8.0f);
    fn_1_50164((f32)(s32)p_lbl_14_bss_0->unk_24, (38.0f), v13, v13, (FontDrawPacket *)&loc_8);
    if ((s32)p_lbl_14_bss_0->unk_24 == 396 && (s32)p_lbl_14_bss_0->unk_28 == 190) {
    v16 = (12.0);
    v17 = (1.0f);
    v18 = (f32)(v16 - (f64)(s32)p_lbl_14_bss_0->unk_34);
    v18 /= v16;
    if (v18 > v17) {
    v18 = v17;
    }
    loc_8.alpha = v18;
    loc_8.x = (99.0f);
    loc_8.y = (96.0f);
    v19 = (30.0f);
    fn_1_50164(v19, v19, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (140.0f);
    v21 = (30.0f);
    fn_1_50164(v21, v21, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (178.0f);
    v23 = (30.0f);
    fn_1_50164(v23, v23, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (216.0f);
    v25 = (30.0f);
    fn_1_50164(v25, v25, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (254.0f);
    v27 = (30.0f);
    fn_1_50164(v27, v27, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (292.0f);
    v29 = (30.0f);
    fn_1_50164(v29, v29, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (336.0f);
    v31 = (30.0f);
    fn_1_50164(v31, v31, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (99.0f);
    loc_8.y = (380.0f);
    v33 = (30.0f);
    fn_1_50164(v33, v33, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (96.0f);
    v35 = (30.0f);
    fn_1_50164(v35, v35, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (140.0f);
    v37 = (30.0f);
    fn_1_50164(v37, v37, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (178.0f);
    v39 = (30.0f);
    fn_1_50164(v39, v39, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (216.0f);
    v41 = (30.0f);
    fn_1_50164(v41, v41, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (254.0f);
    v43 = (30.0f);
    fn_1_50164(v43, v43, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (292.0f);
    v45 = (30.0f);
    fn_1_50164(v45, v45, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    loc_8.x = (575.0f);
    loc_8.y = (336.0f);
    v47 = (8.0f);
    fn_1_50164((98.0f), (42.0f), v47, v47, (FontDrawPacket *)&loc_8);
    loc_8.x = (541.0f);
    loc_8.y = (380.0f);
    v49 = (30.0f);
    fn_1_50164(v49, v49, (8.0f), (8.0f), (FontDrawPacket *)&loc_8);
    p_lbl_14_bss_0->unk_34--;
    }
    if ((s32)p_lbl_14_bss_0->unk_0 < 0) {
    lbl_1_bss_96A = 173;
    }
}
/* fzgx:end fn_14_380 */

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

/* fzgx:begin fn_14_316C */
struct fn_14_316C_Arg0 {
    u16 unk_0;
};
struct fn_14_316C_Arg1 {
    u16 unk_0;
};
struct fn_14_316C_Arg2 {
    u16 unk_0;
};
struct fn_14_316C_Ent {
    u32 raw[2];
};

extern struct fn_14_316C_Ent lbl_14_bss_110[10];
extern s16 lbl_14_bss_160[16];

#pragma opt_common_subs off
void fn_14_316C(struct fn_14_316C_Arg0 *arg0, struct fn_14_316C_Arg1 *arg1, struct fn_14_316C_Arg2 *arg2) {
    s16 v8;
    s16 v5;
    s32 v7;
    s16 t;
    u32 flags;
    s16 i;
    s32 v1;
    s16 v0;

    v1 = 0;
    v0 = ((s16 *)lbl_14_bss_110)[2];
    i = 0;
    arg2->unk_0 = 0;
    arg1->unk_0 = 0;
    arg0->unk_0 = 0;

    while ((u32)i < 8) {
        flags = ((u32 *)&lbl_14_bss_110[i])[3];
        if ((flags & 0x8) != 0) {
            if ((flags & 0x40) != 0 || i == v0) {
                t = v1;
                v7 = t / lbl_14_bss_160[0];
                v8 = v7;
                v5 = t % lbl_14_bss_160[0] + 1;
                switch (v8) {
                case 0:
                    arg0->unk_0 = v5;
                    break;
                case 1:
                    arg1->unk_0 = v5;
                    break;
                case 2:
                    arg2->unk_0 = v5;
                    break;
                }
            }
            v1++;
        }
        i++;
    }
}
#pragma opt_common_subs reset
/* fzgx:end fn_14_316C */

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

/* fzgx:begin fn_14_A2A4 */
extern void fn_1_133DBC(void *);
extern u8 fn_1_B7C00(void);
extern s32 fn_1_12F228(void);
extern u8 fn_14_DF70(void);
extern s32 fn_1_B7E98(u32);
extern s32 fn_1_B7C6C(u32);
extern void fn_1_F7954(void);
extern u32 fn_1_B7CE4(u32, void *);
extern u32 fn_1_AA6D8(u32, u32, void *);
extern u8 fn_1_B7CD4(void);
extern u16 lbl_1_bss_96A[];
extern struct fn_14_A2A4_bss_9454 lbl_14_bss_9454;
extern u8 lbl_1_bss_718E0;

struct fn_14_A2A4_bss_9454 {
    s32 unk_0;
};

struct fn_14_A2A4_cfg {
    u8 enabled;
    u8 pad[3];
    u32 fn;
    void *state_ptr;
    void *table;
    u32 extra[4];

    u8 fzgx_tail_padding[8];
};

void fn_14_A2A4(void) {
    struct fn_14_A2A4_cfg cfg;
    u8 state[64];

    fn_1_133DBC(0);
    if (fn_1_B7C00()) {
        return;
    }
    if (fn_1_12F228()) {
        lbl_1_bss_96A[0] = fn_14_DF70() ? 0xaf : 0xb2;
        return;
    }
    if (fn_1_B7E98(1)) {
        if (fn_1_B7C6C(1) == 0 && ((((lbl_14_bss_9454.unk_0)) == ((0))))) {
            fn_1_F7954();
            fn_1_B7CE4(1, state);
            cfg.enabled = 1;
            cfg.state_ptr = state;
            cfg.table = &lbl_1_bss_718E0;
            cfg.fn = 0xA004;
            fn_1_AA6D8(0, 1, &cfg);
            lbl_14_bss_9454.unk_0 = 1;
            return;
        }
    } else {
        lbl_14_bss_9454.unk_0 = 0;
    }
    fn_1_B7CD4();
}
/* fzgx:end fn_14_A2A4 */

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

/* fzgx:begin fn_14_C518 */
#include "font.h"

#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.0f;
    s = 167.0f;
    s = 38.0f;
    s = 90.0f;
    s = 320.0f;
    s = 216.0f;
    s = 8.0f;
    s = 96.0f;
    s = 336.0f;
    s = 380.0f;
    d = 12.0;
    s = 1.0f;
    s = 99.0f;
    s = 30.0f;
    s = 140.0f;
    s = 178.0f;
    s = 254.0f;
    s = 292.0f;
    s = 541.0f;
    s = 575.0f;
    s = 98.0f;
    s = 42.0f;
}
static const u32 fzgx_pool_table2[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 4503601774854144.0;
    d = 60.0;
    d = 25.0;
    d = 29.0;
}
static const u32 fzgx_pool_table4[10] = {0xA0FF00FF, 0xFFFFFF00, 0xA0FF00FF, 0xFFFFFF00, 0xA0FF00FF, 0xFFFFFF00, 0xA0FF00FF, 0xFF8080FF, 0xA0FF00FF, 0xFFFFFF00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep4(void) { const u32 *volatile cp; cp = fzgx_pool_table4; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime5(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 396.0f;
    s = 190.0f;
    s = 0.5f;
}
static const u32 fzgx_pool_table6[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep6(void) { const u32 *volatile cp; cp = fzgx_pool_table6; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime7(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.0;
    d = 1.0;
    d = 18.0;
    s = 136.0f;
    s = 0.550000011920929f;
    s = 108.0f;
    s = 300.0f;
    s = 80.0f;
    s = 400.0f;
    s = 388.0f;
    s = 97.0f;
    s = 0.05000000074505806f;
}
static const u32 fzgx_pool_table8[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep8(void) { const u32 *volatile cp; cp = fzgx_pool_table8; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime9(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 90.0;
    d = 30.0;
    d = 2.0;
    d = 4503599627370496.0;
    s = 193.32176208496094f;
}
static const u32 fzgx_pool_table10[1] = {0x53454C00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep10(void) { const u32 *volatile cp; cp = fzgx_pool_table10; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime11(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 10.0f;
    s = 20.0f;
}
static const u32 fzgx_pool_table12[12] = {0x00000000, 0x40AD2D2D, 0xC04FCFD0, 0x00000000, 0x40A00000, 0xC0400000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep12(void) { const u32 *volatile cp; cp = fzgx_pool_table12; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime13(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.699999988079071f;
    s = 182.04444885253906f;
    d = 0.55;
    s = 0.8299999833106995f;
    s = 0.06666667014360428f;
}
static const u32 fzgx_pool_table14[8] = {0x00000000, 0x41200000, 0xC0A00000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFF00FFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep14(void) { const u32 *volatile cp; cp = fzgx_pool_table14; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime15(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 9.625f;
}
static const u32 fzgx_pool_table16[9] = {0x00FF0000, 0xFFFFFF00, 0xFFFFFF00, 0x00FF0000, 0x00060007, 0x00080000, 0xFFFFFF00, 0x00FF0000, 0xFFFFFF00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep16(void) { const u32 *volatile cp; cp = fzgx_pool_table16; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime17(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.4583333432674408f;
    s = 0.6666666865348816f;
    s = 0.6169934868812561f;
    s = 0.4166666567325592f;
    s = 0.8333333134651184f;
    s = 0.48627451062202454f;
}
static const u32 fzgx_pool_table18[2] = {0xFFFFFFFF, 0x3F3F3F3F};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep18(void) { const u32 *volatile cp; cp = fzgx_pool_table18; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime19(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 480.0f;
    s = 62.0f;
    s = 50.0f;
    s = 5.0f;
    s = 7.0f;
}
static const u32 fzgx_pool_table20[2] = {0x00FF0000, 0xFFFFFF00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep20(void) { const u32 *volatile cp; cp = fzgx_pool_table20; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime21(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.480392187833786f;
}
static const u32 fzgx_pool_table22[2] = {0xFF00FFFF, 0xFFFFFFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep22(void) { const u32 *volatile cp; cp = fzgx_pool_table22; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime23(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 314.0f;
    s = 84.0f;
    s = 321.0f;
    s = 356.0f;
    s = 0.75f;
    s = 51.0f;
    s = 0.30000001192092896f;
    s = 88.0f;
    s = 2.0f;
}
static const u32 fzgx_pool_table24[13] = {0xFFFF0000, 0xFF000000, 0xFFFF0000, 0xFF000000, 0xFFFFFF00, 0xFFFF0000, 0xFF000000, 0xFFFFFF00, 0xFFFF0000, 0xFF000000, 0xFFFFFF00, 0xFFFF0000, 0xFFFFFF00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep24(void) { const u32 *volatile cp; cp = fzgx_pool_table24; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime25(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.9215686321258545f;
    s = 0.4588235318660736f;
}
static const u32 fzgx_pool_table26[2] = {0xFF00FFFF, 0xFFFFFFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep26(void) { const u32 *volatile cp; cp = fzgx_pool_table26; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime27(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 492.0f;
    s = 332.0f;
    s = 40.0f;
    s = 322.0f;
    s = 41.0f;
    s = 238.0f;
    s = 156.0f;
    s = 1.2901960611343384f;
    s = 0.8313725590705872f;
    s = 240.0f;
    s = 0.009999999776482582f;
    s = 8.00100040435791f;
    s = 100.0f;
    s = 0.019999999552965164f;
    s = 9.999999747378752e-05f;
    s = 16.0f;
    s = 24.0f;
    s = 73.0f;
    s = 368.0f;
    s = 193.0f;
    s = 248.0f;
    s = 36.0f;
    s = 376.0f;
    s = 211.0f;
    s = 608.0f;
    s = 257.0f;
    s = 176.0f;
    s = 239.0f;
}
static const u32 fzgx_pool_table28[3] = {0x0000FA00, 0xFAFAFAFF, 0x0000FA00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep28(void) { const u32 *volatile cp; cp = fzgx_pool_table28; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime29(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 65536.0f;
    s = 120.0f;
    s = 0.4000000059604645f;
    s = 9.0f;
    s = 402.0f;
    s = 548.0f;
    s = 134.0f;
    s = 586.0f;
    s = 449.0f;
    s = 329.0f;
    s = 14.210000038146973f;
    s = 3.200000047683716f;
}
static const u32 fzgx_pool_table30[4] = {0x008080FF, 0x3CA3D70A, 0xC10CCCCD, 0xC2700000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep30(void) { const u32 *volatile cp; cp = fzgx_pool_table30; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime31(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.05999999865889549f;
    s = 375.0f;
    s = 0.20000000298023224f;
    s = 0.800000011920929f;
    s = 370.0f;
    s = 358.0f;
    s = 360.0f;
    s = 0.10000000149011612f;
    s = 45.0f;
    s = 0.0010000000474974513f;
    s = 0.23000000417232513f;
    s = -8.800000190734863f;
    s = -60.0f;
    s = 0.029999999329447746f;
    s = 0.09000000357627869f;
    s = 383.0f;
    s = 0.6000000238418579f;
    s = 381.0f;
    s = 324.0f;
    s = 32768.0f;
    s = 0.07000000029802322f;
    s = 0.03999999910593033f;
    s = 340.0f;
    s = 12.75f;
}
static const u32 fzgx_pool_table32[1] = {0xFFFFFFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep32(void) { const u32 *volatile cp; cp = fzgx_pool_table32; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime33(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 215.0f;
    s = 226.0f;
    s = 220.0f;
    s = 227.0f;
    s = 328.0f;
    s = 234.0f;
    s = 317.0f;
    s = 310.0f;
    s = 315.0f;
}
static const u32 fzgx_pool_table34[3] = {0x00FF0000, 0xFF800000, 0xFFFFFF00};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep34(void) { const u32 *volatile cp; cp = fzgx_pool_table34; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime35(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.03333333507180214f;
    s = 640.0f;
    s = 0.15000000596046448f;
    s = 48.0f;
    s = 87.0f;
    s = 0.10100000351667404f;
    s = 153.0f;
    s = 0.0989999994635582f;
    s = 346.0f;
    s = 217.0f;
    s = 228.0f;
    s = 105.0f;
    s = 466.0f;
    s = 286.0f;
    s = 52.0f;
    s = 0.5833333134651184f;
    s = 488.0f;
    s = 28.0f;
    s = 189.0f;
    s = 470.0f;
    s = 280.0f;
    s = 44.0f;
    s = 272.0f;
    s = 151.0f;
    s = 1.25f;
    s = 1.0833333730697632f;
    s = 500.0f;
    s = 422.0f;
    s = 166.0f;
    s = 0.8999999761581421f;
}
static const u32 fzgx_pool_table36[1] = {0xFFFFFFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep36(void) { const u32 *volatile cp; cp = fzgx_pool_table36; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime37(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = -5.0f;
    s = 32767.0f;
}
static const u32 fzgx_pool_table38[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep38(void) { const u32 *volatile cp; cp = fzgx_pool_table38; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime39(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 336.0;
    d = 318.0;
    d = 306.0;
    d = 366.0;
    s = 224.0f;
    s = 448.0f;
    d = 17.0;
    s = 16384.0f;
    s = 204.0f;
    d = 66.0;
    d = 270.0;
    d = 6.0;
}
static const u32 fzgx_pool_table40[1] = {0xFFFFFFFF};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep40(void) { const u32 *volatile cp; cp = fzgx_pool_table40; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime41(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 60.0f;
}
#pragma section code_type ".text"

struct fn_14_C518_lbl_14_rodata_0 {
    u8 pad_0[0x10];
    f32 unk_10;
    u8 pad_14[0x1C];
    f32 unk_30;
    u8 pad_34[0x2C];
    f64 unk_60;
    u8 pad_68[0x2F4];
    f32 unk_35C;
    u8 pad_360[0x100];
    f32 unk_460;
    u8 pad_464[0x2C];
    u32 unk_490;
    f32 unk_494;
};

extern struct fn_14_C518_lbl_14_rodata_0 lbl_14_rodata_0;
extern FontDrawPacket lbl_1_rodata_26F8;
extern u16 lbl_1_bss_968;
extern u32 lbl_14_bss_0;

extern int fn_1_4F734(FontDrawPacket *);
extern u32 fn_1_49410(void);
extern void fn_1_49514(u32 *);
extern void fn_1_495B0(u32);
extern void fn_1_495C8(u8);
extern void fn_1_495FC(void);
extern void fn_8006CE1C(f32);
extern u32 fn_14_DC90(f32);

void fn_14_C518(void) {
    struct fn_14_C518_lbl_14_rodata_0 *p;
    FontDrawPacket pkt;
    u32 val;

    p = (struct fn_14_C518_lbl_14_rodata_0 *)&lbl_14_rodata_0;
    pkt = lbl_1_rodata_26F8;
    pkt.x = (320.0f);
    pkt.y = (224.0f);
    pkt.flags = 14;
    pkt.image = 0x9208;
    fn_1_4F734(&pkt);
    pkt.flags = 6;
    pkt.image = 0x9207;
    fn_1_4F734(&pkt);
    pkt = lbl_1_rodata_26F8;
    pkt.image = 0x9201;
    pkt.x = (320.0f);
    pkt.y = (224.0f);
    pkt.flags = 10;
    pkt.z = (0.0900000036f);
    fn_1_4F734(&pkt);
    fn_1_49410();
    fn_1_495FC();
    fn_1_495C8(9);
    fn_1_495B0(1u << 31);
    val = fzgx_pool_table40[0];
    fn_1_49514(&val);
    fn_14_DC90((1.0f));
    if ((s32)lbl_14_bss_0 > 0) {
        fn_8006CE1C((1.0f) - ((f32)(s32)lbl_14_bss_0 / (60.0f)));
    } else {
        lbl_1_bss_968 = 10;
    }
}
/* fzgx:end fn_14_C518 */

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

/* fzgx:begin fn_14_DC90 */
typedef struct RoData {
    u8 pad_0[0x10];
    f32 unk_10;
    u8 pad_14[0x4];
    f32 unk_18;
    u8 pad_1C[0x1C];
    f32 unk_38;
    u8 pad_3C[0x74];
    f32 unk_B0;
    u8 pad_B4[0x274];
    f32 unk_328;
    u8 pad_32C[0x48];
    f32 unk_374;
    u8 pad_378[0x1A0];
    u32 unk_518;
    u32 unk_51C;
    u8 pad_520[0xC];
    u32 unk_52C;
    u32 unk_530;
    f32 unk_534;
    f32 unk_538;
    f32 unk_53C;
    f32 unk_540;
    f32 unk_544;
    f32 unk_548;
} RoData;

typedef struct Cmd88 {
    u32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
    u8 pad_10[0x1C];
    f32 unk_2C;
    u32 unk_30;
    u8 tail_34[0x24];
} Cmd88;

extern s16 lbl_1_bss_962;
extern f32 lbl_14_data_0;
extern RoData lbl_14_rodata_0;
extern u32 lbl_14_bss_9460;
extern u32 lbl_1_rodata_26F8;
extern u32 lbl_801A66B4;

extern void fn_1_4D0A0(void);
extern void fn_1_50164(f32, f32, f32, f32, void *);
extern u32 fn_1_49410(void);
extern void fn_1_495FC(void);
extern void fn_1_495C8(u8);
extern void fn_1_495B0(u32);
extern void fn_1_49590(f32);
extern void fn_1_4954C(f32);
extern int fn_1_B7E98(int);
extern void fn_1_496FC(f32, f32);
extern void fn_1_4955C(f32, f32);
extern void fn_1_49514(u32 *);
extern void fn_1_4AE0C(const char *, ...);
extern void fn_1_4D10C(void *, f32, f32);

#pragma opt_lifetimes off
#pragma opt_propagation off
void fn_14_DC90(f32 farg0) {
    const char *dpp = (const char *)&lbl_14_data_0;
    RoData *rp = (RoData *)&lbl_14_rodata_0;
    const char **t;
    Cmd88 cmd;
    u32 sp18;
    u32 sp14;
    u32 sp10;
    u32 out;
    u8 bytes[4];

    if (lbl_1_bss_962 != 0xaf) {
        fn_1_4D0A0();
    } else {
        cmd = *(const Cmd88 *)&lbl_1_rodata_26F8;
        cmd.unk_0 = 0x9E2B;
        cmd.unk_4 = rp->unk_10;
        cmd.unk_8 = rp->unk_328;
        cmd.unk_C = rp->unk_534;
        cmd.unk_30 = 0xa;
        cmd.unk_2C = farg0;
        fn_1_50164(rp->unk_538, rp->unk_53C, rp->unk_18, rp->unk_18, &cmd);
        fn_1_49410();
        fn_1_495FC();
        fn_1_495C8(9);
        fn_1_495B0(0x80000000);
    }

    fn_1_49590(rp->unk_B0);
    fn_1_4954C(rp->unk_374);

    if (fn_1_B7E98(1) != 0) {
        if ((s32)lbl_14_bss_9460 != 0) {
            fn_1_496FC(rp->unk_10, rp->unk_540);
            fn_1_4955C(rp->unk_544, rp->unk_544);
            sp18 = rp->unk_518;
            fn_1_49514(&sp18);
            t = (const char **)(dpp + 0x32FC);
            fn_1_4AE0C(t[lbl_801A66B4]);
            t = (const char **)(dpp + 0x3370);
            fn_1_4AE0C(t[lbl_801A66B4]);
            t = (const char **)(dpp + 0x33F0);
            fn_1_4AE0C(t[lbl_801A66B4]);
        } else {
            fn_1_496FC(rp->unk_10, rp->unk_328);
        }
        fn_1_4955C(rp->unk_544, rp->unk_544);
        sp14 = rp->unk_51C;
        fn_1_49514(&sp14);
        t = (const char **)(dpp + 0x34AC);
        fn_1_4AE0C(t[lbl_801A66B4]);
    } else if ((s32)lbl_14_bss_9460 != 0) {
        fn_1_496FC(rp->unk_10, rp->unk_540);
        fn_1_4955C(rp->unk_544, rp->unk_544);
        sp10 = rp->unk_52C;
        fn_1_49514(&sp10);
        t = (const char **)(dpp + 0x32FC);
        fn_1_4AE0C(t[lbl_801A66B4]);
        t = (const char **)(dpp + 0x3370);
        fn_1_4AE0C(t[lbl_801A66B4]);
        t = (const char **)(dpp + 0x33F0);
        fn_1_4AE0C(t[lbl_801A66B4]);
    }

    if (((s32)lbl_14_bss_9460 != 0 || fn_1_B7E98(1) != 0) && lbl_1_bss_962 != 0xaf) {
        *(u32 *)bytes = rp->unk_530;
        bytes[3] = (u8)(rp->unk_548 * farg0);
        out = *(u32 *)bytes;
        fn_1_4D10C(&out, rp->unk_534, rp->unk_38);
    }
}
#pragma opt_propagation reset

#pragma opt_lifetimes reset
/* fzgx:end fn_14_DC90 */

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
