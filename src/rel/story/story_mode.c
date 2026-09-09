#include "types.h"

/* fzgx:begin fn_7_244 */
extern struct fn_7_244_lbl_7_bss_C lbl_7_bss_C;

struct fn_7_244_lbl_7_bss_C {
    u32 unk_0;
};

u32 fn_7_244(void) {
    u32 v0;
    v0 = lbl_7_bss_C.unk_0;
    lbl_7_bss_C.unk_0 = (v0 + 1);
    return v0;
}
/* fzgx:end fn_7_244 */

/* fzgx:begin fn_7_25C */
extern struct fn_7_25C_lbl_7_bss_0 lbl_7_bss_0;
extern u32 camera_get_state(u32);
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_5948(u32);
extern u32 fn_1_627C(u32);
extern u32 fn_1_9A770(u32);
extern u32 fn_1_B7C00(void);
extern u32 fn_1_C6F8C(u32);
extern u32 fn_1_C7224(u32);

struct fn_7_25C_lbl_7_bss_0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0xC];
    u32 unk_18;
    u32 unk_1C;
    u8 pad_20[0x4];
    u32 unk_24;
};

void fn_7_25C(void) {
    struct fn_7_25C_lbl_7_bss_0 *p_lbl_7_bss_0;
    u32 v0;
    u32 v1;
    u32 t0, t1, t4, t5, t7, t8, t9, t11;
    p_lbl_7_bss_0 = (struct fn_7_25C_lbl_7_bss_0 *)&lbl_7_bss_0;
    if ((s32)p_lbl_7_bss_0->unk_24 == 0) {
    t0 = fn_1_B7C00();
    if ((t0 & 0xFF) == 0) {
    t1 = fn_1_435C(p_lbl_7_bss_0->unk_18);
    fn_1_407C(t1);
    v0 = p_lbl_7_bss_0->unk_4;
    if ((s32)v0 > 0) {
    p_lbl_7_bss_0->unk_4 = (v0 - 1);
    }
    }
    }
    v1 = p_lbl_7_bss_0->unk_8;
    if ((s32)v1 > 0) {
    p_lbl_7_bss_0->unk_8 = (v1 - 1);
    }
    fn_1_3CC4(v1);
    t4 = fn_1_435C(p_lbl_7_bss_0->unk_1C);
    t5 = camera_get_state(t4);
    if ((s8)t5 == -1) {
    fn_1_407C(t5);
    } else {
    t7 = fn_1_5948(0);
    t8 = fn_1_9A770(t7);
    t9 = fn_1_C7224(t8);
    fn_1_407C(t9);
    t11 = fn_1_627C(0);
    fn_1_C6F8C(t11);
    }
}
/* fzgx:end fn_7_25C */

/* fzgx:begin fn_7_50C */
extern u16 lbl_1_bss_96A;

void fn_7_50C(void) {
    lbl_1_bss_96A = 135;
}
/* fzgx:end fn_7_50C */

/* fzgx:begin fn_7_51C */
// fn_7_51C: empty in retail (single blr).
void fn_7_51C(void) {
}
/* fzgx:end fn_7_51C */

/* fzgx:begin fn_7_E50 */
extern struct fn_7_E50_lbl_7_bss_1C lbl_7_bss_1C;
extern u32 fn_1_4A00(u32, u32, u32);

struct fn_7_E50_lbl_7_bss_1C {
    u32 unk_0;
};

void fn_7_E50(void) {
    fn_1_4A00(1, 30, lbl_7_bss_1C.unk_0);
}
/* fzgx:end fn_7_E50 */

/* fzgx:begin fn_7_FB0 */
// fn_7_FB0: empty in retail (single blr).
void fn_7_FB0(void) {
}
/* fzgx:end fn_7_FB0 */

/* fzgx:begin fn_7_1398 */
extern u32 fn_1_12F10C(u32);
extern u32 fn_7_4050(void);
extern u32 lbl_7_bss_4;

void fn_7_1398(void) {
    fn_7_4050();
    fn_1_12F10C(0);
    lbl_7_bss_4 = 0;
}
/* fzgx:end fn_7_1398 */

/* fzgx:begin fn_7_13CC */
extern struct fn_7_13CC_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern struct fn_7_13CC_lbl_7_bss_10_T *lbl_7_bss_10;
extern u16 lbl_1_bss_968;

struct fn_7_13CC_lbl_1_bss_8B3A0 {
    u8 pad_0[0x94];
    u32 unk_94;
};
struct fn_7_13CC_lbl_7_bss_10_T {
    u8 pad_0[0x8];
    u32 unk_8;
};

void fn_7_13CC(void) {
    lbl_1_bss_8B3A0.unk_94 = 0x2000000;
    lbl_7_bss_10->unk_8 = 139;
    lbl_1_bss_968 = 1;
}
/* fzgx:end fn_7_13CC */

/* fzgx:begin fn_7_13FC */
// fn_7_13FC: empty in retail (single blr).
void fn_7_13FC(void) {
}
/* fzgx:end fn_7_13FC */

/* fzgx:begin fn_7_1538 */
// fn_7_1538: empty in retail (single blr).
void fn_7_1538(void) {
}
/* fzgx:end fn_7_1538 */

/* fzgx:begin fn_7_153C */
// fn_7_153C: empty in retail (single blr).
void fn_7_153C(void) {
}
/* fzgx:end fn_7_153C */

/* fzgx:begin fn_7_1540 */
// fn_7_1540: empty in retail (single blr).
void fn_7_1540(void) {
}
/* fzgx:end fn_7_1540 */

/* fzgx:begin fn_7_1544 */
extern u16 lbl_1_bss_96A;
extern u32 fn_1_3F038(void);
extern u32 fn_1_3F0C8(void);

void fn_7_1544(void) {
    u32 v0;
    s16 v1;
    u32 t0, t1;
    t0 = fn_1_3F038();
    v0 = t0;
    if ((s32)t0 != 0) {
    t1 = fn_1_3F0C8();
    v0 = t1;
    v1 = (s16)v0;
    switch (v1) {
    case 42:
    lbl_1_bss_96A = 141;
    break;
    case 43:
    lbl_1_bss_96A = 149;
    break;
    default:
    lbl_1_bss_96A = 135;
    }
    }
}
/* fzgx:end fn_7_1544 */

/* fzgx:begin fn_7_15B8 */
// fn_7_15B8: empty in retail (single blr).
void fn_7_15B8(void) {
}
/* fzgx:end fn_7_15B8 */

/* fzgx:begin fn_7_16FC */
extern u16 lbl_1_bss_96A;

void fn_7_16FC(void) {
    lbl_1_bss_96A = 144;
}
/* fzgx:end fn_7_16FC */

/* fzgx:begin fn_7_170C */
// fn_7_170C: empty in retail (single blr).
void fn_7_170C(void) {
}
/* fzgx:end fn_7_170C */

/* fzgx:begin fn_7_1C0C */
extern u32 fn_1_48140(u32);

void fn_7_1C0C(void) {
    fn_1_48140(186);
}
/* fzgx:end fn_7_1C0C */

/* fzgx:begin fn_7_1DB4 */
// fn_7_1DB4: empty in retail (single blr).
void fn_7_1DB4(void) {
}
/* fzgx:end fn_7_1DB4 */

/* fzgx:begin fn_7_1DB8 */
// fn_7_1DB8: empty in retail (single blr).
void fn_7_1DB8(void) {
}
/* fzgx:end fn_7_1DB8 */

/* fzgx:begin fn_7_20DC */
// fn_7_20DC: empty in retail (single blr).
void fn_7_20DC(void) {
}
/* fzgx:end fn_7_20DC */

/* fzgx:begin fn_7_20E0 */
// fn_7_20E0: empty in retail (single blr).
void fn_7_20E0(void) {
}
/* fzgx:end fn_7_20E0 */

/* fzgx:begin fn_7_20E4 */
extern u16 lbl_1_bss_96A;

void fn_7_20E4(void) {
    lbl_1_bss_96A = 135;
}
/* fzgx:end fn_7_20E4 */

/* fzgx:begin fn_7_20F4 */
// fn_7_20F4: empty in retail (single blr).
void fn_7_20F4(void) {
}
/* fzgx:end fn_7_20F4 */

/* fzgx:begin fn_7_20F8 */
// fn_7_20F8: empty in retail (single blr).
void fn_7_20F8(void) {
}
/* fzgx:end fn_7_20F8 */

/* fzgx:begin fn_7_20FC */
// fn_7_20FC: empty in retail (single blr).
void fn_7_20FC(void) {
}
/* fzgx:end fn_7_20FC */

/* fzgx:begin fn_7_2100 */
extern u16 lbl_1_bss_96A;

void fn_7_2100(void) {
    lbl_1_bss_96A = 135;
}
/* fzgx:end fn_7_2100 */

/* fzgx:begin fn_7_2110 */
// fn_7_2110: empty in retail (single blr).
void fn_7_2110(void) {
}
/* fzgx:end fn_7_2110 */

/* fzgx:begin fn_7_2114 */
struct fn_7_2114_Arg0 {
    u32 unk_0;
    u8 pad_4[0xA8];
    u32 unk_AC;
    u8 pad_B0[0x18];
    u32 unk_C8;
};
struct fn_7_2114_lbl_7_bss_0 {
    u8 pad_0[0x20];
    u32 unk_20;
    u8 pad_24[0x274];
    u32 unk_298;
    u32 unk_29C;
};

extern struct fn_7_2114_lbl_7_bss_0 lbl_7_bss_0;
extern void fn_7_2170(void);
extern void fn_7_21C8(void);

u32 fn_7_2114(struct fn_7_2114_Arg0 *arg0) {
    struct fn_7_2114_lbl_7_bss_0 *p_lbl_7_bss_0;
    p_lbl_7_bss_0 = (struct fn_7_2114_lbl_7_bss_0 *)&lbl_7_bss_0;
    p_lbl_7_bss_0->unk_298 = 0;
    p_lbl_7_bss_0->unk_29C = 0;
    arg0->unk_AC = (u32)fn_7_21C8;
    arg0->unk_C8 = (u32)fn_7_2170;
    arg0->unk_0 = (arg0->unk_0 | 0x100000);
    if ((s32)p_lbl_7_bss_0->unk_20 != 0) {
    p_lbl_7_bss_0->unk_20 = 0;
    return (u32)arg0;
    }
    arg0->unk_0 = (arg0->unk_0 | 512);
}
/* fzgx:end fn_7_2114 */

/* fzgx:begin fn_7_2170 */
extern struct fn_7_2170_lbl_7_bss_14 lbl_7_bss_14;
extern u32 fn_7_4108(void *, u32, u32);
extern u32 fn_7_41FC(void *);
extern u32 lbl_7_bss_48;

struct fn_7_2170_lbl_7_bss_14 {
    u32 unk_0;
};

s32 fn_7_2170(u32 arg0) {
    if (*(u32 *)((u8 *)lbl_7_bss_14.unk_0 + 36) != 0) {
    fn_7_4108(&lbl_7_bss_48, *(u32 *)((u8 *)lbl_7_bss_14.unk_0 + 36), arg0);
    fn_7_41FC(&lbl_7_bss_48);
    }
    return 0;
}
/* fzgx:end fn_7_2170 */

/* fzgx:begin fn_7_2324 */
// fn_7_2324: returns a constant.
int fn_7_2324(void) {
    return 0;
}
/* fzgx:end fn_7_2324 */

/* fzgx:begin fn_7_235C */
extern struct fn_7_235C_lbl_7_bss_48 lbl_7_bss_48;

struct fn_7_235C_lbl_7_bss_48 {
    u8 pad_0[0x244];
    u32 unk_244;
};

s32 fn_7_235C(void) {
    u32 v0;
    v0 = lbl_7_bss_48.unk_244;
    if ((lbl_7_bss_48.unk_244 & ~0x7FFFFFFF) != 0) {
    v0 = 1;
    return v0;
    }
    v0 = (-((v0 >> 30) & 0x1));
    return v0;
}
/* fzgx:end fn_7_235C */

/* fzgx:begin fn_7_2384 */
extern u32 lbl_7_bss_29C;

struct fn_7_2384_Arg0 {
    u32 unk_0;
};

s32 fn_7_2384(struct fn_7_2384_Arg0 *arg0) {
    if ((s32)lbl_7_bss_29C == 0) {
    arg0->unk_0 = (arg0->unk_0 | 0x80000);
    }
    return 0;
}
/* fzgx:end fn_7_2384 */

/* fzgx:begin fn_7_24D8 */
struct fn_7_24D8_lbl_7_bss_29C {
    u32 unk_0;
};

extern struct fn_7_24D8_lbl_7_bss_29C lbl_7_bss_29C;
extern u32 fn_7_3FCC(void);

s32 fn_7_24D8(void) {
    if ((s32)lbl_7_bss_29C.unk_0 == 0) {
    lbl_7_bss_29C.unk_0 = 1;
    fn_7_3FCC();
    }
    return 2;
}
/* fzgx:end fn_7_24D8 */

/* fzgx:begin fn_7_2514 */
extern u32 fn_7_3FCC(void);

s32 fn_7_2514(void) {
    fn_7_3FCC();
    return 0;
}
/* fzgx:end fn_7_2514 */

/* fzgx:begin fn_7_3FCC */
struct fn_7_3FCC_lbl_7_bss_18 {
    u32 unk_0;
};
struct fn_7_3FCC_lbl_7_data_12E68 {
    u32 unk_0;
};
struct fn_7_3FCC_lbl_7_bss_1C {
    u32 unk_0;
};
struct fn_7_3FCC_lbl_7_data_12E6C {
    u32 unk_0;
};

extern struct fn_7_3FCC_lbl_7_bss_18 lbl_7_bss_18;
extern struct fn_7_3FCC_lbl_7_bss_1C lbl_7_bss_1C;
extern struct fn_7_3FCC_lbl_7_data_12E68 lbl_7_data_12E68;
extern struct fn_7_3FCC_lbl_7_data_12E6C lbl_7_data_12E6C;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);

void fn_7_3FCC(void) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t1, t3;
    fn_1_435C(lbl_7_bss_18.unk_0);
    v0 = lbl_7_data_12E68.unk_0;
    v1 = v0;
    if ((s32)v0 != -1) {
    t1 = fn_1_426C(v1);
    v1 = t1;
    lbl_7_data_12E68.unk_0 = -1;
    }
    fn_1_435C(lbl_7_bss_1C.unk_0);
    v2 = lbl_7_data_12E6C.unk_0;
    v3 = v2;
    if ((s32)v2 != -1) {
    t3 = fn_1_426C(v3);
    v3 = t3;
    lbl_7_data_12E6C.unk_0 = -1;
    }
}
/* fzgx:end fn_7_3FCC */

/* fzgx:begin fn_7_4094 */
extern u32 fn_1_4404(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_80008E84(u32);
extern u32 lbl_7_data_13A3C;
extern u32 lbl_801A6410;

u32 fn_7_4094(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t0, t1, t2;
    t0 = fn_1_4404(arg0);
    v0 = *(u32 *)((u8 *)arg0 + 0);
    v1 = arg2;
    v2 = t0;
    v3 = arg3;
    if ((v0 + 0x10000) != 65535) {
    v3 = (u32)&lbl_801A6410;
    v1 = (u32)&lbl_7_data_13A3C;
    v2 = *(u32 *)((u8 *)v3 + 0);
    v3 = 2443;
    t1 = fn_1_46B4(v2, v0, (u32)v1, v3);
    v2 = t1;
    *(u32 *)((u8 *)arg0 + 0) = -1;
    }
    v2 = t0;
    t2 = fn_80008E84(v2);
    v2 = t2;
    return v2;
}
/* fzgx:end fn_7_4094 */
