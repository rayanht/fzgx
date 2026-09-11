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
extern s16 lbl_1_bss_962;
extern struct fn_4_9B0_lbl_4_data_1260 lbl_4_data_1260;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_426C(u32);
extern void fn_4_AB90(void);

/* fzgx:begin fn_4_800 */
extern u8 lbl_4_bss_2;
extern u32 lbl_4_bss_8;
extern s32 lbl_1_bss_970;
extern u16 lbl_1_bss_968;
extern u32 fn_1_4A00(u32, u32, u32);
extern int fn_1_4C10(void);

void fn_4_800(void) {
    u8 value;

    value = lbl_4_bss_2;
    lbl_4_bss_2 = value + 1;

    switch (lbl_1_bss_970) {
    case 0:
        break;
    case 1:
        fn_1_4A00(0, 15, lbl_4_bss_8);
        lbl_1_bss_970 = 2;
        break;
    case 2:
        if (fn_1_4C10() == 0) {
            lbl_1_bss_968 = 1;
        }
        break;
    default:
        break;
    }
}
/* fzgx:end fn_4_800 */

/* fzgx:begin fn_4_894 */
extern u32 fn_1_435C(u32);

// Initializes both option subsystems in sequence.
void fn_4_894(void) {
    u32 first_state;
    u32 second_state;

    first_state = fn_1_435C(lbl_4_bss_4);
    first_state = fn_1_407C(first_state);
    fn_1_3CC4(first_state);

    second_state = fn_1_435C(lbl_4_bss_8);
    fn_1_407C(second_state);
}
/* fzgx:end fn_4_894 */

/* fzgx:begin _epilog noprologue */
#include "types.h"

extern const f32 lbl_4_rodata_4C[45];
extern struct option_epilog_lbl_4_bss_4 lbl_4_bss_4;
extern struct option_epilog_lbl_4_bss_8 lbl_4_bss_8;
extern struct option_epilog_lbl_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern void fn_8006CE1C(f32);
extern void fn_1_1596DC(u32);
extern void fn_1_484CC(u32);
extern void fn_1_47A60(u32);
extern void fn_1_412A0(u32);
extern void fn_1_3C78(void);
extern void fn_1_435C(u32);
extern void fn_1_41A8(void);
extern void fn_8004BF0C(u32, s32);
extern void ADXT_Stop(u32);

struct option_epilog_lbl_4_bss_4 {
    u32 unk_0;
};
struct option_epilog_lbl_4_bss_8 {
    u32 unk_0;
};
struct option_epilog_lbl_1_bss_6EAD0 {
    u32 unk_0;
};
struct option_epilog_object {
    u32 unk_0;
    u32 unk_4;
};

void _epilog(void) {
    fn_8006CE1C(lbl_4_rodata_4C[0]);
    fn_1_1596DC(2);
    fn_1_484CC(2);
    fn_1_47A60(3);
    fn_1_412A0(1);
    fn_1_3C78();
    fn_1_435C(lbl_4_bss_4.unk_0);
    fn_1_41A8();
    fn_1_435C(lbl_4_bss_8.unk_0);
    fn_1_41A8();
    if (lbl_1_bss_6EAD0.unk_0 != 0) {
        fn_8004BF0C(((struct option_epilog_object *)lbl_1_bss_6EAD0.unk_0)->unk_0, -999);
        fn_8004BF0C(((struct option_epilog_object *)lbl_1_bss_6EAD0.unk_0)->unk_4, -999);
        ADXT_Stop(((struct option_epilog_object *)lbl_1_bss_6EAD0.unk_0)->unk_0);
        ADXT_Stop(((struct option_epilog_object *)lbl_1_bss_6EAD0.unk_0)->unk_4);
    }
}
/* fzgx:end _epilog */

/* fzgx:begin fn_4_9B0 noprologue */
#include "types.h"

extern s16 lbl_1_bss_962;
extern struct fn_4_9B0_lbl_4_data_1260 lbl_4_data_1260;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

typedef u32 (*fn_4_9B0_Fn0)(void);
struct fn_4_9B0_lbl_4_data_1260_0_E44 {
    u8 pad_0[0x20];
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};
struct fn_4_9B0_lbl_4_data_1260 {
    struct fn_4_9B0_lbl_4_data_1260_0_E44 unk_0[1];
};

void fn_4_9B0(void) {
    struct fn_4_9B0_lbl_4_data_1260_0_E44 *p;
    s16 idx;
    u32 v0;
    p = (struct fn_4_9B0_lbl_4_data_1260_0_E44 *)&lbl_4_data_1260;
    idx = lbl_1_bss_962;
    p = (struct fn_4_9B0_lbl_4_data_1260_0_E44 *)((u8 *)p + (idx - 75) * 44);
    lbl_1_bss_71688 = p->unk_24;
    lbl_1_bss_7168C = (p->unk_28);
    ((fn_4_9B0_Fn0)p->unk_20)();
}
/* fzgx:end fn_4_9B0 */

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

/* fzgx:begin fn_4_D7C noprologue */
#include "types.h"
#include "rel/option/globals.h"

extern int fn_1_4C10(void);
extern void fn_1_1280(u32);
extern void fn_1_A2D84(u32);
extern u32 fn_4_0(u32, u32, u32, u32, u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u16 lbl_1_bss_96A;

struct fn_4_D7C_lbl_1_bss_970 {
    s32 unk_0;
    u8 unk_4;
};
extern struct fn_4_D7C_lbl_1_bss_970 lbl_1_bss_970;

struct fn_4_D7C_lbl_1_bss_6EAB4 {
    u32 unk_0;
};
extern struct fn_4_D7C_lbl_1_bss_6EAB4 lbl_1_bss_6EAB4;

struct fn_4_D7C_lbl_1_bss_9F8 {
    u8 pad_0[0x8];
    u16 unk_8;
};
extern struct fn_4_D7C_lbl_1_bss_9F8 lbl_1_bss_9F8;

struct fn_4_D7C_lbl_4_data_144C {
    s16 unk_0;
    u8 pad_2[0x1A];
};
extern struct fn_4_D7C_lbl_4_data_144C lbl_4_data_144C[];

void fn_4_D7C(void) {
    struct fn_4_D7C_lbl_1_bss_970 *p;
    u32 v;
    struct fn_4_D7C_lbl_1_bss_6EAB4 *q;

    p = (struct fn_4_D7C_lbl_1_bss_970 *)&lbl_1_bss_970;
    if (p->unk_0 <= 0) {
        if (lbl_4_bss_10.unk_0 != 0) {
            if (fn_1_4C10() == 0) {
                fn_1_1280(1);
                lbl_1_bss_96A = lbl_4_bss_10.unk_0;
                lbl_4_bss_10.unk_0 = 0;
            }
        } else {
            p->unk_4 = fn_4_0(p->unk_4, 0, 2, -1, 0);
            if ((lbl_1_bss_9F8.unk_8 >> 9) & 1) {
                fn_1_A2D84(0xA9010200);
                q = (struct fn_4_D7C_lbl_1_bss_6EAB4 *)&lbl_1_bss_6EAB4;
                v = q->unk_0;
                q->unk_0 = v | 0x2C;
                lbl_1_bss_970.unk_0 = 1;
            } else if ((lbl_1_bss_9F8.unk_8 >> 8) & 1) {
                fn_1_A2D84(0xA9010100);
                lbl_4_bss_10.unk_0 = lbl_4_data_144C[p->unk_4].unk_0;
                fn_1_4A00(0, 15, lbl_4_bss_8);
            }
        }
    }
}
/* fzgx:end fn_4_D7C */

/* fzgx:begin fn_4_EA0 */
// Clear the pending option selection after applying its associated value.
void fn_4_EA0(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_406C */
// Finalizes the pending option callback and clears its handle.
void fn_4_406C(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_4B10 */
extern u16 lbl_4_bss_0;
extern u32 fn_1_F7308(void);
extern u32 fn_1_435C(u32);

struct fn_4_4B10_state {
    u16 unk_0;
    u8 pad_2[0x2];
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0xB4];
    u16 unk_C0;
};

/* Stop active option sounds and clear the pending sound handle. */
void fn_4_4B10(void) {
    struct fn_4_4B10_state *state;

    state = (struct fn_4_4B10_state *)&lbl_4_bss_0;
    fn_1_F7308();
    fn_1_435C(state->unk_4);
    fn_1_426C(state->unk_C0);
    if (state->unk_0 != 0) {
        fn_1_435C(state->unk_8);
        fn_1_426C(state->unk_0);
        state->unk_0 = 0;
    }
}
/* fzgx:end fn_4_4B10 */

/* fzgx:begin fn_4_4B74 noprologue */
#include "types.h"

extern u8 jumptable_4_data_2974[36];

struct fn_4_4B74_obj {
    u16 unk_0;
    u16 unk_2;
    u16 unk_4;
    u16 unk_6;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
};

extern struct fn_4_4B74_obj lbl_4_bss_C4[];

s32 fn_4_4B74(u32 arg0, u32 arg1) {
    u32 idx;
    u32 v;

    switch (arg0) {
    case 0:
    case 4:
    default:
        idx = 0;
        break;
    case 1:
        idx = 0;
        break;
    case 2:
        idx = 1;
        break;
    case 3:
        idx = 2;
        break;
    }

    switch (arg1) {
    case 0:
        v = lbl_4_bss_C4[idx].unk_0;
        break;
    case 1:
        v = lbl_4_bss_C4[idx].unk_2;
        break;
    case 2:
        v = lbl_4_bss_C4[idx].unk_4;
        break;
    case 3:
        v = lbl_4_bss_C4[idx].unk_6;
        break;
    case 4:
        v = lbl_4_bss_C4[idx].unk_8;
        break;
    case 5:
        v = lbl_4_bss_C4[idx].unk_C;
        break;
    case 6:
        v = lbl_4_bss_C4[idx].unk_10;
        break;
    case 7:
        v = lbl_4_bss_C4[idx].unk_14;
        break;
    case 8:
        v = lbl_4_bss_C4[idx].unk_18;
        break;
    }

    return 31 - __cntlzw(v);
}
/* fzgx:end fn_4_4B74 */

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

/* fzgx:begin fn_4_78E0 */
extern u32 fn_1_435C(u32);

/* Clears the pending option state after notifying the option handlers. */
void fn_4_78E0(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_7CA4 */
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

extern u32 fn_1_4A00(u32, u32, u32);

void fn_4_7CA4(void) {
    struct fn_4_7CA4_lbl_4_bss_0 *option_state;
    u32 result;
    u32 availability, selected_mode, notification_result;

    /* Apply pending option changes, then update the active option state. */
    option_state = (struct fn_4_7CA4_lbl_4_bss_0 *)&lbl_4_bss_0;
    if (option_state->unk_10 != 0) {
        availability = fn_1_4C10();
        result = availability;
        if ((s32)result != 0) {
            return;
        }
        result = 1;
        fn_1_1280(result);
        lbl_1_bss_96A = option_state->unk_10;
        option_state->unk_10 = 0;
        return;
    }
    result = option_state->unk_C;
    selected_mode = fn_4_0(result, 0, 2, -1, 0);
    result = selected_mode;
    option_state->unk_C = result;
    result = (u32)&lbl_1_bss_9F8;
    result = *(u16 *)((u8 *)result + 8);
    if (((result >> 9) & 0x1) != 0) {
        result = 0xA9010000;
        result += 512;
        fn_1_A2D84(result);
        option_state->unk_10 = 75;
    } else {
        if (((result >> 8) & 0x1) != 0) {
            result = 0xA9010000;
            result += 256;
            fn_1_A2D84(result);
            result = (u32)&lbl_4_data_2C58;
            option_state->unk_10 = *(s16 *)((u8 *)result + (option_state->unk_C * 28));
        } else {
            return;
        }
    }
    result = 0;
    notification_result = fn_1_4A00(result, 15, option_state->unk_8);
    result = notification_result;
}
/* fzgx:end fn_4_7CA4 */

/* fzgx:begin fn_4_7D94 */
extern u32 fn_1_435C(u32);

// Reset the option subsystem after releasing its active resource.
void fn_4_7D94(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_8158 noprologue */
#include "types.h"

struct fn_4_8158_lbl_4_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x1];
    u8 unk_D;
    u8 pad_E[0x2];
    u16 unk_10;
};

extern int fn_1_4C10(void);
extern struct fn_4_8158_lbl_4_bss_0 lbl_4_bss_0;
extern u16 lbl_1_bss_96A;
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_4_0(u32, u32, u32, u32, u32);
extern u32 lbl_1_bss_9F8;
extern u8 lbl_4_data_2D24[56];
extern void fn_1_1280(u32);
extern void fn_1_A2D84(u32);

void fn_4_8158(void) {
    struct fn_4_8158_lbl_4_bss_0 *p_lbl_4_bss_0;
    u32 v0;
    u32 t0, t2, t5;

    p_lbl_4_bss_0 = (struct fn_4_8158_lbl_4_bss_0 *)&lbl_4_bss_0;
    if (p_lbl_4_bss_0->unk_10 != 0) {
        t0 = fn_1_4C10();
        if ((s32)t0 == 0) {
            fn_1_1280(1);
            lbl_1_bss_96A = p_lbl_4_bss_0->unk_10;
            p_lbl_4_bss_0->unk_10 = 0;
        }
    } else {
        t2 = fn_4_0(p_lbl_4_bss_0->unk_D, 0, 1, -1, 0);
        p_lbl_4_bss_0->unk_D = t2;
        v0 = *(u16 *)((u8 *)&lbl_1_bss_9F8 + 8);
        if (((v0 >> 9) & 1) != 0) {
            fn_1_A2D84(0xA9010200);
            p_lbl_4_bss_0->unk_10 = 75;
        } else if (((v0 >> 8) & 1) != 0) {
            fn_1_A2D84(0xA9010100);
            p_lbl_4_bss_0->unk_10 = *(s16 *)((u8 *)&lbl_4_data_2D24 + p_lbl_4_bss_0->unk_D * 28);
        } else {
            return;
        }
        fn_1_4A00(0, 15, p_lbl_4_bss_0->unk_8);
    }
}
/* fzgx:end fn_4_8158 */

/* fzgx:begin fn_4_8248 */
extern u32 fn_1_435C(u32);

/* Finalize the pending option state and clear its completion flag. */
void fn_4_8248(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_8720 noprologue */
#include "types.h"

struct fn_4_8720_lbl_4_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x2];
    u8 unk_E;
    u8 pad_F[0x1];
    u16 unk_10;
    u8 pad_12[0xA6];
    u16 unk_B8;
    u8 pad_BA[0x1C6];
    u8 unk_280;
    u8 unk_281;
    u8 unk_282;
    u8 unk_283;
};
struct fn_4_8720_lbl_1_bss_9F8 {
    u8 pad_0[0x8];
    u16 unk_8;
    u8 pad_A[0x6];
    u16 unk_10;
    u16 unk_12;
};
struct fn_4_8720_lbl_1_bss_718E0 {
    u8 pad_0[0x3];
    u8 unk_3;
};

extern struct fn_4_8720_lbl_1_bss_9F8 lbl_1_bss_9F8;
extern struct fn_4_8720_lbl_4_bss_0 lbl_4_bss_0;
extern struct fn_4_8720_lbl_1_bss_718E0 lbl_1_bss_718E0;
extern u16 lbl_1_bss_96A;
extern int fn_1_4C10(void);
extern void fn_1_1280(u32);
extern u32 fn_4_0(u32, u32, u32, u32, u32);
extern void fn_1_A2D84(u32);
extern void fn_1_A6840(u32);
extern u32 fn_1_4A00(u32, u32, u32);

void fn_4_8720(void) {
    struct fn_4_8720_lbl_4_bss_0 *p = &lbl_4_bss_0;
    struct fn_4_8720_lbl_1_bss_9F8 *q;
    u16 v;

    if (p->unk_10 != 0) {
        if (fn_1_4C10() == 0) {
            fn_1_1280(1U);
            lbl_1_bss_96A = p->unk_10;
            p->unk_10 = 0;
        }
    } else if (p->unk_280 != 0) {
        p->unk_281 = fn_4_0(p->unk_281, 0U, 1U, -1U, 1U);
        q = &lbl_1_bss_9F8;
        if ((q->unk_8 >> 9U) & 1) {
            fn_1_A2D84(0xA9010200U);
            p->unk_280 = 0;
        } else if ((q->unk_8 >> 8U) & 1) {
            fn_1_A2D84(0xA9010100U);
            if (p->unk_281 == 0) {
                lbl_1_bss_718E0.unk_3 = p->unk_283;
                p->unk_E = 1;
            } else if (lbl_1_bss_718E0.unk_3 != p->unk_283) {
                fn_1_A6840(lbl_1_bss_718E0.unk_3);
            }
            if (p->unk_E != 0) {
                p->unk_B8 = 0x4B;
                p->unk_10 = 0x4C;
            } else {
                p->unk_10 = 0x4B;
                fn_1_4A00(0U, 0xFU, p->unk_8);
            }
        }
    } else {
        q = &lbl_1_bss_9F8;
        if ((((q->unk_10) & 1) || (lbl_1_bss_9F8.unk_12 & 1)) && p->unk_282 == 1) {
            p->unk_282 = 0;
            fn_1_A2D84(0xA9010000U);
        } else if ((((q->unk_10 >> 1U) & 1) || (lbl_1_bss_9F8.unk_12 >> 1U) & 1) && p->unk_282 == 0) {
            p->unk_282 = 1;
            fn_1_A2D84(0xA9010000U);
        }
        q = &lbl_1_bss_9F8;
        if (((q->unk_8 >> 8U) & 1) && p->unk_282 != p->unk_283) {
            fn_1_A2D84(0xA9010100U);
            fn_1_A6840(p->unk_282);
            p->unk_283 = p->unk_282;
        }
        if ((q->unk_8 >> 9U) & 1) {
            fn_1_A2D84(0xA9010200U);
            if (p->unk_283 != lbl_1_bss_718E0.unk_3) {
                p->unk_280 = 1;
                p->unk_281 = 0;
            } else {
                p->unk_10 = 0x4B;
                fn_1_4A00(0U, 0xFU, p->unk_8);
            }
        }
    }
}
/* fzgx:end fn_4_8720 */

/* fzgx:begin fn_4_898C */
extern u32 fn_1_435C(u32);

/* Reset the option state after releasing its active resource. */
void fn_4_898C(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_8A54 */
extern int fn_1_4C10(void);
extern u16 lbl_1_bss_96A;
extern void fn_1_1280(u32);
extern u32 fn_4_ABB0(void);
extern u32 lbl_4_bss_8;
extern u32 fn_1_4A00(u32, u32, u32);

/* Advance the option resource state and clear a completed selection. */
void fn_4_8A54(void) {
    u16 value;

    if (lbl_4_bss_10.unk_0 != 0) {
        if (fn_1_4C10() == 0) {
            fn_1_1280(1);
            value = lbl_4_bss_10.unk_0;
            lbl_1_bss_96A = value;
            lbl_4_bss_10.unk_0 = 0;
        }
    } else {
        value = fn_4_ABB0();
        lbl_4_bss_10.unk_0 = value;
        if (value != 0) {
            fn_1_4A00(0, 15, lbl_4_bss_8);
        }
    }
}
/* fzgx:end fn_4_8A54 */

/* fzgx:begin fn_4_8AE0 */
extern u32 fn_1_435C(u32);

// Completes the pending option callback and clears its handle.
void fn_4_8AE0(void) {
    fn_4_AB90();

    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_9A78 */
extern u32 fn_1_435C(u32);

// Finalizes the pending option callback and clears its handle.
void fn_4_9A78(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_A734 */
// Finalizes the pending option callback and clears its handle.
void fn_4_A734(void) {
    if (lbl_4_bss_0 != 0) {
        fn_1_435C(lbl_4_bss_8);
        fn_1_426C(lbl_4_bss_0);
        lbl_4_bss_0 = 0;
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

/* fzgx:begin fn_4_AB30 */
// Initialize the option state and reset its associated data value.
void fn_4_AB30(void) {
    fn_1_B9BE0();
    fn_1_B9DE8((u32)&lbl_4_bss_5630);
    lbl_4_bss_5630.unk_0 = 4;
    lbl_4_bss_5630.unk_0 |= 0x10;
    lbl_4_bss_5630.unk_0 |= 0x20;
    lbl_4_bss_5630.unk_4 = 0xc;
    lbl_4_data_2F1C = 0;
}
/* fzgx:end fn_4_AB30 */

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
