#include "types.h"
#include "rel/option/globals.h"

extern struct fn_4_347C_lbl_1_bss_9C8 lbl_1_bss_9C8;
extern u32 lbl_1_data_2AC0;
extern u32 lbl_1_data_2B40;
extern u32 lbl_1_data_2B50;
extern u32 lbl_1_data_2B58;
extern u32 lbl_4_data_14D0;
extern void fn_4_3128(void);
extern u32 fn_80008BA8(u32, u32, u32);
extern u32 fn_1_F7308(void);
extern u32 lbl_1_bss_AA0;
extern u32 lbl_1_data_2B60;
extern u32 lbl_4_data_2AE8;
extern u32 memcpy(u32, u32, u32);
extern void fn_4_63D4(void);
extern int fn_1_4C10(void);
extern u16 lbl_1_bss_96A;
extern u32 fn_4_0(u32, u32, u32, u32, u32);
extern u32 lbl_1_bss_9F8;
extern u8 lbl_4_data_2C58[84];
extern void fn_1_1280(u32);
extern void fn_1_A2D84(u32);
extern u32 fn_4_ABB0(void);
extern u32 fn_1_1380F0(u32);
extern u32 fn_1_13ABA8(u32);
extern u32 lbl_4_data_1A4;
extern s32 lbl_801A66B4;
extern u8 lbl_4_bss_5618;
extern u32 fn_1_B7E98(u32);
extern u32 fn_1_B800C(u32);
extern u32 fn_1_B80F0(u32);
extern u32 fn_1_B8170(u32);
extern u32 lbl_4_data_2DB4;
extern void fn_4_9AD0(void);
extern u8 *fn_4_A82C(u8 *);
extern void fn_80083DB0(u8 *, u32);
extern u32 fn_1_B9C0C(void);
extern s8 fn_1_BA144(u32 *);
extern u32 lbl_4_bss_5678;
extern u32 fn_1_B7C00(void);
extern u32 fn_1_BC310(void *);
extern u32 fn_1_C0510(u32);
extern u32 fn_1_C1394(void *);

/* fzgx:begin fn_4_894 noprologue */
#include "types.h"

extern struct fn_4_894_lbl_4_bss_4 lbl_4_bss_4;
extern struct fn_4_894_lbl_4_bss_8 lbl_4_bss_8;
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_435C(u32);

struct fn_4_894_lbl_4_bss_4 {
    u32 unk_0;
};
struct fn_4_894_lbl_4_bss_8 {
    u32 unk_0;
};

void fn_4_894(void) {
    u32 t0, t1, t3;
    t0 = fn_1_435C(lbl_4_bss_4.unk_0);
    t1 = fn_1_407C(t0);
    fn_1_3CC4(t1);
    t3 = fn_1_435C(lbl_4_bss_8.unk_0);
    fn_1_407C(t3);
}
/* fzgx:end fn_4_894 */

/* fzgx:begin fn_4_D10 noprologue */
#include "types.h"

extern struct fn_4_D10_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_4_data_14A0;
extern void fn_4_A0C(void);

struct fn_4_D10_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
};

void fn_4_D10(void) {
    struct fn_4_D10_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_D10_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_14A0, (u32)fn_4_A0C, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_D10 */

/* fzgx:begin fn_4_EA0 noprologue */
#include "types.h"

struct fn_4_EA0_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_EA0_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_EA0(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_EA0 */

/* fzgx:begin fn_4_347C noprologue */
#include "types.h"

extern struct fn_4_347C_lbl_1_bss_9C8 lbl_1_bss_9C8;
extern u32 lbl_1_data_2AC0;
extern u32 lbl_1_data_2B40;
extern u32 lbl_1_data_2B50;
extern u32 lbl_1_data_2B58;
extern u32 lbl_4_data_14D0;
extern void fn_4_3128(void);
extern u32 fn_80008BA8(u32, u32, u32);

struct fn_4_347C_lbl_1_bss_9C8_0_E12 {
    u8 pad_0[0x2];
    u8 unk_2;
    u8 unk_3;
    u8 pad_4[0x8];
};
struct fn_4_347C_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
    u8 pad_12[0x46];
    u8 unk_58;
    u8 unk_59;
    u8 unk_5A;
    u8 unk_5B;
    u8 unk_5C;
    u8 unk_5D;
};
struct fn_4_347C_lbl_1_bss_9C8 {
    struct fn_4_347C_lbl_1_bss_9C8_0_E12 unk_0[1];
};

extern s32 fn_1_3F8C(u32, u32, u32, u32);
extern struct fn_4_347C_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);

void fn_4_347C(void) {
    struct fn_4_347C_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 v0;
    u8 v1;
    u8 v2;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_347C_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_14D0, (u32)fn_4_3128, 0, 20);
    p_lbl_4_bss_0->unk_0 = t1;
    fn_80008BA8((u32)((u8 *)(u32)p_lbl_4_bss_0 + 96), (u32)&lbl_1_data_2AC0, 64);
    fn_80008BA8((u32)((u8 *)(u32)p_lbl_4_bss_0 + 160), (u32)&lbl_1_data_2B40, 8);
    fn_80008BA8((u32)((u8 *)(u32)p_lbl_4_bss_0 + 168), (u32)&lbl_1_data_2B50, 8);
    fn_80008BA8((u32)((u8 *)(u32)p_lbl_4_bss_0 + 176), (u32)&lbl_1_data_2B58, 8);
    v0 = p_lbl_4_bss_0->unk_8;
    p_lbl_4_bss_0->unk_5A = 0;
    p_lbl_4_bss_0->unk_5C = 0;
    p_lbl_4_bss_0->unk_5B = 0;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, v0);
    v1 = lbl_1_bss_9C8.unk_0[p_lbl_4_bss_0->unk_5D].unk_2;
    p_lbl_4_bss_0->unk_58 = v1;
    p_lbl_4_bss_0->unk_59 = (lbl_1_bss_9C8.unk_0[p_lbl_4_bss_0->unk_5D].unk_3);
}
/* fzgx:end fn_4_347C */

/* fzgx:begin fn_4_406C noprologue */
#include "types.h"

struct fn_4_406C_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_406C_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_406C(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_406C */

/* fzgx:begin fn_4_4784 noprologue */
#include "types.h"

extern struct fn_4_4784_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_1_F70D0(u32);
extern u32 fn_1_F7568(void);
extern u32 lbl_4_data_1500;
extern u32 lbl_4_data_150C;
extern void fn_1_F7128(void);
extern void fn_4_467C(void);

struct fn_4_4784_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x2];
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
    u8 pad_12[0xA8];
    u8 unk_BA;
    u8 unk_BB;
    u8 pad_BC[0x1];
    u8 unk_BD;
    u8 unk_BE;
    u8 pad_BF[0x1];
    u16 unk_C0;
};

void fn_4_4784(void) {
    struct fn_4_4784_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t0, t1, t3, t5;
    p_lbl_4_bss_0 = (struct fn_4_4784_lbl_4_bss_0 *)&lbl_4_bss_0;
    t0 = fn_1_F7568();
    p_lbl_4_bss_0->unk_BE = t0;
    p_lbl_4_bss_0->unk_BA = t0;
    p_lbl_4_bss_0->unk_BD = 0;
    p_lbl_4_bss_0->unk_BB = 0;
    t1 = fn_1_435C(p_lbl_4_bss_0->unk_4);
    fn_1_F70D0(t1);
    t3 = fn_1_3F8C((u32)&lbl_4_data_1500, (u32)fn_1_F7128, 0, 10);
    p_lbl_4_bss_0->unk_C0 = t3;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t5 = fn_1_3F8C((u32)&lbl_4_data_150C, (u32)fn_4_467C, 0, 5);
    p_lbl_4_bss_0->unk_0 = t5;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_4784 */

/* fzgx:begin fn_4_4B10 noprologue */
#include "types.h"

extern u32 fn_1_F7308(void);

extern struct fn_4_4B10_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);

struct fn_4_4B10_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x2];
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0xB4];
    u16 unk_C0;
};

void fn_4_4B10(void) {
    struct fn_4_4B10_lbl_4_bss_0 *p_lbl_4_bss_0;
    p_lbl_4_bss_0 = (struct fn_4_4B10_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_F7308();
    fn_1_435C(p_lbl_4_bss_0->unk_4);
    fn_1_426C(p_lbl_4_bss_0->unk_C0);
    if (p_lbl_4_bss_0->unk_0 != 0) {
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    fn_1_426C(p_lbl_4_bss_0->unk_0);
    p_lbl_4_bss_0->unk_0 = 0;
    }
}
/* fzgx:end fn_4_4B10 */

/* fzgx:begin fn_4_6678 noprologue */
#include "types.h"

extern u32 fn_80008BA8(u32, u32, u32);
extern u32 lbl_1_bss_AA0;
extern u32 lbl_1_data_2B60;
extern u32 lbl_4_data_2AE8;
extern u32 memcpy(u32, u32, u32);
extern void fn_4_63D4(void);

extern struct fn_4_6678_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);

struct fn_4_6678_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
    u8 pad_12[0x106];
    u8 unk_118;
    u8 pad_119[0x2];
    u8 unk_11B;
    u8 pad_11C[0x2];
    u8 unk_11E;
    u8 pad_11F[0x155];
    u8 unk_274;
};

void fn_4_6678(void) {
    struct fn_4_6678_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_6678_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2AE8, (u32)fn_4_63D4, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    fn_80008BA8((u32)((u8 *)p_lbl_4_bss_0 + 288), (u32)&lbl_1_bss_AA0, 336);
    memcpy((u32)((u8 *)p_lbl_4_bss_0 + 624), (u32)&lbl_1_data_2B60, 4);
    p_lbl_4_bss_0->unk_11B = 0;
    p_lbl_4_bss_0->unk_274 = 255;
    p_lbl_4_bss_0->unk_118 = 0;
    p_lbl_4_bss_0->unk_11E = 0;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_6678 */

/* fzgx:begin fn_4_78E0 noprologue */
#include "types.h"

struct fn_4_78E0_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_78E0_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_78E0(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_78E0 */

/* fzgx:begin fn_4_7C38 noprologue */
#include "types.h"

extern struct fn_4_7C38_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_4_data_2CAC;
extern void fn_4_7938(void);

struct fn_4_7C38_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
};

void fn_4_7C38(void) {
    struct fn_4_7C38_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_7C38_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2CAC, (u32)fn_4_7938, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_7C38 */

/* fzgx:begin fn_4_7CA4 noprologue */
#include "types.h"

extern int fn_1_4C10(void);
extern u16 lbl_1_bss_96A;
extern u32 fn_4_0(u32, u32, u32, u32, u32);
extern u32 lbl_1_bss_9F8;
extern u8 lbl_4_data_2C58[84];
extern void fn_1_1280(u32);
extern void fn_1_A2D84(u32);

struct fn_4_7CA4_lbl_4_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 unk_C;
    u8 pad_D[0x3];
    u16 unk_10;
};

extern struct fn_4_7CA4_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_4A00(u32, u32, u32);

void fn_4_7CA4(void) {
    struct fn_4_7CA4_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 v0;
    u32 t0, t2, t5;

    p_lbl_4_bss_0 = (struct fn_4_7CA4_lbl_4_bss_0 *)&lbl_4_bss_0;
    if (p_lbl_4_bss_0->unk_10 != 0) {
        t0 = fn_1_4C10();
        v0 = t0;
        if ((s32)v0 != 0) {
            return;
        }
        v0 = 1;
        fn_1_1280(v0);
        lbl_1_bss_96A = p_lbl_4_bss_0->unk_10;
        p_lbl_4_bss_0->unk_10 = 0;
        return;
    }
    v0 = p_lbl_4_bss_0->unk_C;
    t2 = fn_4_0(v0, 0, 2, -1, 0);
    v0 = t2;
    p_lbl_4_bss_0->unk_C = v0;
    v0 = (u32)&lbl_1_bss_9F8;
    v0 = *(u16 *)((u8 *)v0 + 8);
    if (((v0 >> 9) & 0x1) != 0) {
        v0 = 0xA9010000;
        v0 += 512;
        fn_1_A2D84(v0);
        p_lbl_4_bss_0->unk_10 = 75;
    } else {
        if (((v0 >> 8) & 0x1) != 0) {
            v0 = 0xA9010000;
            v0 += 256;
            fn_1_A2D84(v0);
            v0 = (u32)&lbl_4_data_2C58;
            p_lbl_4_bss_0->unk_10 = *(s16 *)((u8 *)v0 + (p_lbl_4_bss_0->unk_C * 28));
        } else {
            return;
        }
    }
    v0 = 0;
    t5 = fn_1_4A00(v0, 15, p_lbl_4_bss_0->unk_8);
    v0 = t5;
}
/* fzgx:end fn_4_7CA4 */

/* fzgx:begin fn_4_7D94 noprologue */
#include "types.h"

struct fn_4_7D94_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_7D94_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_7D94(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_7D94 */

/* fzgx:begin fn_4_80EC noprologue */
#include "types.h"

extern struct fn_4_80EC_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_4_data_2D5C;
extern void fn_4_7DEC(void);

struct fn_4_80EC_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
};

void fn_4_80EC(void) {
    struct fn_4_80EC_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_80EC_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2D5C, (u32)fn_4_7DEC, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_80EC */

/* fzgx:begin fn_4_8248 noprologue */
#include "types.h"

struct fn_4_8248_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_8248_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_8248(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_8248 */

/* fzgx:begin fn_4_869C noprologue */
#include "types.h"

extern struct fn_4_869C_lbl_1_bss_718E0 lbl_1_bss_718E0;
extern struct fn_4_869C_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_4_data_2D78;
extern void fn_4_82A0(void);

struct fn_4_869C_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
    u8 pad_12[0x26E];
    u8 unk_280;
    u8 pad_281[0x1];
    u8 unk_282;
    u8 unk_283;
};
struct fn_4_869C_lbl_1_bss_718E0 {
    u8 pad_0[0x3];
    u8 unk_3;
};

void fn_4_869C(void) {
    struct fn_4_869C_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_869C_lbl_4_bss_0 *)&lbl_4_bss_0;
    p_lbl_4_bss_0->unk_283 = lbl_1_bss_718E0.unk_3;
    p_lbl_4_bss_0->unk_282 = lbl_1_bss_718E0.unk_3;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2D78, (u32)fn_4_82A0, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_280 = 0;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_869C */

/* fzgx:begin fn_4_898C noprologue */
#include "types.h"

struct fn_4_898C_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_898C_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_898C(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_898C */

/* fzgx:begin fn_4_89E4 noprologue */
#include "types.h"

extern struct fn_4_89E4_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_4_AB30(void);
extern u32 lbl_4_data_2D8C;
extern void fn_4_AC58(void);

struct fn_4_89E4_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
};

void fn_4_89E4(void) {
    struct fn_4_89E4_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t2;
    p_lbl_4_bss_0 = (struct fn_4_89E4_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_4_AB30();
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t2 = fn_1_3F8C((u32)&lbl_4_data_2D8C, (u32)fn_4_AC58, 0, 5);
    p_lbl_4_bss_0->unk_0 = t2;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_89E4 */

/* fzgx:begin fn_4_8A54 noprologue */
#include "types.h"

extern int fn_1_4C10(void);
extern u16 lbl_1_bss_96A;
extern void fn_1_1280(u32);
extern u16 lbl_4_bss_10[90];
extern u32 fn_4_ABB0(void);

extern u32 lbl_4_bss_8;
extern u32 fn_1_4A00(u32, u32, u32);

void fn_4_8A54(void) {
    u16 value;

    if (lbl_4_bss_10[0] != 0) {
        if (fn_1_4C10() == 0) {
            fn_1_1280(1);
            value = lbl_4_bss_10[0];
            lbl_1_bss_96A = value;
            lbl_4_bss_10[0] = 0;
        }
    } else {
        value = fn_4_ABB0();
        lbl_4_bss_10[0] = value;
        if (value != 0) {
            fn_1_4A00(0, 15, lbl_4_bss_8);
        }
    }
}
/* fzgx:end fn_4_8A54 */

/* fzgx:begin fn_4_8AE0 noprologue */
#include "types.h"

struct fn_4_8AE0_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_8AE0_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_4_AB90(void);
extern u32 lbl_4_bss_8;

void fn_4_8AE0(u32 arg0) {
    u32 v0;
    u32 t1, t2;
    fn_4_AB90();
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t1 = fn_1_435C(v0);
    v0 = t1;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t2 = fn_1_426C(v0);
    v0 = t2;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_8AE0 */

/* fzgx:begin fn_4_8DC0 noprologue */
#include "types.h"

extern struct fn_4_8DC0_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_4_data_2D9C;
extern void fn_4_8B3C(void);

struct fn_4_8DC0_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x4];
    u16 unk_10;
    u8 pad_12[0x273];
    u8 unk_285;
    u8 unk_286;
};

void fn_4_8DC0(void) {
    struct fn_4_8DC0_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 t1;
    p_lbl_4_bss_0 = (struct fn_4_8DC0_lbl_4_bss_0 *)&lbl_4_bss_0;
    p_lbl_4_bss_0->unk_286 = 0;
    p_lbl_4_bss_0->unk_285 = 0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2D9C, (u32)fn_4_8B3C, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_10 = 0;
    fn_1_4A00(1, 15, p_lbl_4_bss_0->unk_8);
}
/* fzgx:end fn_4_8DC0 */

/* fzgx:begin fn_4_9A78 noprologue */
#include "types.h"

struct fn_4_9A78_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_9A78_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_9A78(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_9A78 */

/* fzgx:begin fn_4_9AD0 */
void fn_4_9AD0(void) {
    if (lbl_4_bss_5618 != 0) {
    fn_1_1380F0(*(u32 *)((u8 *)&lbl_4_data_1A4 + (lbl_801A66B4 << 2)));
    fn_1_13ABA8(0);
    }
}
/* fzgx:end fn_4_9AD0 */

/* fzgx:begin fn_4_9B20 noprologue */
#include "types.h"

extern u32 fn_1_B7E98(u32);
extern u32 fn_1_B800C(u32);
extern u32 fn_1_B80F0(u32);
extern u32 fn_1_B8170(u32);
extern u32 lbl_4_data_2DB4;
extern void fn_4_9AD0(void);

struct fn_4_9B20_lbl_4_bss_0 {
    u16 unk_0;
    u8 pad_2[0x6];
    u32 unk_8;
    u8 pad_C[0x285];
    u8 unk_291;
    u8 pad_292[0x2];
    u8 unk_294;
    u8 pad_295[0x5383];
    u8 unk_5618;
    u8 unk_5619;
    u8 unk_561A;
    u8 unk_561B;
    u32 unk_561C;
    u8 unk_5620;
    u8 unk_5621;
    u8 unk_5622;
};

extern struct fn_4_9B20_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);

s32 fn_4_9B20(void) {
    struct fn_4_9B20_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 v0;
    u32 t1, t2, t3, t4, t5;
    p_lbl_4_bss_0 = (struct fn_4_9B20_lbl_4_bss_0 *)&lbl_4_bss_0;
    fn_1_435C(p_lbl_4_bss_0->unk_8);
    t1 = fn_1_3F8C((u32)&lbl_4_data_2DB4, (u32)fn_4_9AD0, 0, 5);
    p_lbl_4_bss_0->unk_0 = t1;
    p_lbl_4_bss_0->unk_5618 = 1;
    p_lbl_4_bss_0->unk_5619 = 0;
    p_lbl_4_bss_0->unk_561A = 0;
    p_lbl_4_bss_0->unk_561B = 0;
    p_lbl_4_bss_0->unk_294 = 0;
    p_lbl_4_bss_0->unk_561C = 0;
    t2 = fn_1_B7E98(0);
    v0 = t2;
    if ((s32)t2 != 0) {
    v0 = 0;
    v0 = (fn_1_B800C(v0));
    if ((s32)v0 == 0) {
    v0 = 0;
    t4 = fn_1_B8170(v0);
    v0 = t4;
    if ((v0 & 0x2) == 0) {
    v0 = 1;
    p_lbl_4_bss_0->unk_561B = v0;
    p_lbl_4_bss_0->unk_561C = 120;
    p_lbl_4_bss_0->unk_5619 = v0;
    p_lbl_4_bss_0->unk_291 = v0;
    p_lbl_4_bss_0->unk_561A = v0;
    }
    }
    v0 = 0;
    t5 = fn_1_B80F0(v0);
    v0 = t5;
    v0 = 1;
    p_lbl_4_bss_0->unk_5620 = v0;
    p_lbl_4_bss_0->unk_5621 = v0;
    p_lbl_4_bss_0->unk_5622 = 0;
    } else {
    v0 = 0;
    p_lbl_4_bss_0->unk_5620 = v0;
    p_lbl_4_bss_0->unk_5621 = v0;
    p_lbl_4_bss_0->unk_5622 = 120;
    }
    return v0;
}
/* fzgx:end fn_4_9B20 */

/* fzgx:begin fn_4_A734 noprologue */
#include "types.h"

struct fn_4_A734_lbl_4_bss_0 {
    u16 unk_0;
};

extern struct fn_4_A734_lbl_4_bss_0 lbl_4_bss_0;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_4_bss_8;

void fn_4_A734(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if (lbl_4_bss_0.unk_0 != 0) {
    v0 = (u32)&lbl_4_bss_8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_4_bss_0;
    v0 = *(u16 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_4_bss_0.unk_0 = 0;
    }
}
/* fzgx:end fn_4_A734 */

/* fzgx:begin fn_4_A78C */
void fn_4_A78C(u32 arg0) {
    u8 loc_8[32];
    u8 *p;
    u8 *out;

    if (lbl_801A66B4 != 5) {
        fn_80083DB0(loc_8, arg0);
        p = loc_8;
        out = (u8 *)arg0;
        while (*p != 0) {
            if (*p < 0x80) {
                *out = *p;
                p++;
                out++;
            } else {
                u8 *q = fn_4_A82C(p);
                if (q != 0) {
                    *out = *q;
                    out++;
                }
                p += 2;
            }
        }
        *out = 0;
    }
}
/* fzgx:end fn_4_A78C */

/* fzgx:begin fn_4_AB90 */
void fn_4_AB90(void) {
    fn_1_B9C0C();
}
/* fzgx:end fn_4_AB90 */

/* fzgx:begin fn_4_ACF0 */
void fn_4_ACF0(void) {
    u32 v0;
    u32 t0;
    t0 = fn_1_BA144((u32 *)(u32)&lbl_4_bss_5630);
    v0 = t0;
    if ((s8)t0 == 0) {
    lbl_4_data_2F1C = 1;
    } else {
    if ((s8)t0 == 1) {
    lbl_4_bss_5678 = 78;
    }
    }
}
/* fzgx:end fn_4_ACF0 */

/* fzgx:begin fn_4_AD44 */
void fn_4_AD44(void) {
    u32 t0;
    t0 = fn_1_B7C00();
    if ((t0 & 0xFF) == 0) {
    fn_1_BC310(&lbl_4_bss_5630);
    }
}
/* fzgx:end fn_4_AD44 */

/* fzgx:begin fn_4_AD78 */
void fn_4_AD78(void) {
    fn_1_C0510((u32)&lbl_4_bss_5630);
    lbl_4_data_2F1C = 2;
}
/* fzgx:end fn_4_AD78 */

/* fzgx:begin fn_4_ADAC */
// fn_4_ADAC: empty in retail (single blr).
void fn_4_ADAC(void) {
}
/* fzgx:end fn_4_ADAC */

/* fzgx:begin fn_4_ADB0 */
void fn_4_ADB0(void) {
    u32 t0;
    t0 = fn_1_B7C00();
    if ((t0 & 0xFF) == 0) {
    lbl_4_data_2F1C = 0;
    fn_1_C1394(&lbl_4_bss_5630);
    }
}
/* fzgx:end fn_4_ADB0 */

/* fzgx:begin fn_4_ADF0 */
// fn_4_ADF0: empty in retail (single blr).
void fn_4_ADF0(void) {
}
/* fzgx:end fn_4_ADF0 */
