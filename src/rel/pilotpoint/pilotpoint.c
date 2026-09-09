#include "types.h"

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
