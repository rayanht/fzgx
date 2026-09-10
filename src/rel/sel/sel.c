#include "types.h"

/* fzgx:begin fn_10_1F28 */
extern s32 lbl_10_bss_51740;
extern s32 lbl_10_bss_49388;
extern s16 lbl_1_bss_8B3A0;

extern void fn_1_435C(s32 value);
extern void fn_1_426C(s32 value);
extern void fn_10_BD64(void *value);
extern void fn_10_C594(void);

void fn_10_1F28(void) {
    s16 *state;

    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    state = &lbl_1_bss_8B3A0;
    fn_10_BD64(state);
    fn_10_C594();
    state[1] = state[0];
}
/* fzgx:end fn_10_1F28 */

/* fzgx:begin fn_10_3268 */
extern u8 lbl_10_bss_51748[6];
extern void fn_1_1596DC(s32);
extern u8 lbl_1_bss_8B3A0[];
extern void fn_10_C594(void);
extern void fn_1_EC910(void);
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;
extern void fn_1_435C(u32);
extern void fn_1_426C(s32);
extern void fn_1_7B4C0(void);
extern void fn_10_BEF0(u8 *);

void fn_10_3268(void) {
    if (*(s32 *)lbl_10_bss_51748 == 1) {
        *(s32 *)lbl_10_bss_51748 = 0;
        *(s16 *)lbl_1_bss_8B3A0 = -1;
    }
    if (*(s16 *)lbl_1_bss_8B3A0 != 1) {
        fn_1_1596DC(3);
    }
    fn_10_C594();
    fn_1_EC910();
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    {
        u8 *state = lbl_1_bss_8B3A0;
        if ((*(u32 *)(state + 0x94) & (1u << 31)) == 0) {
            fn_1_7B4C0();
        }
        fn_10_BEF0(lbl_1_bss_8B3A0);
        if (*(u32 *)(state + 0x94) & (1u << 30)) {
            *(s16 *)(lbl_1_bss_8B3A0 + 0xe) = 6;
        }
    }
}
/* fzgx:end fn_10_3268 */

/* fzgx:begin fn_10_3D64 */
extern int lbl_1_bss_7180C;
extern int fn_1_B7E98(int);

s16 fn_10_3D64(void) {
    s16 result = 0;

    if (lbl_1_bss_7180C == 1 && fn_1_B7E98(0) == 1) {
        result |= 1;
    }
    if (lbl_1_bss_7180C == 1 && fn_1_B7E98(1) == 1) {
        result |= 2;
    }
    return result;
}
/* fzgx:end fn_10_3D64 */

/* fzgx:begin fn_10_4600 */
extern s32 lbl_10_bss_14;
extern s16 lbl_10_bss_4938C;
extern u32 lbl_10_bss_49388;
extern u32 lbl_10_bss_51744;
extern u32 lbl_801A66C0;
extern u16 lbl_1_bss_96A;
extern u8 lbl_1_bss_8B3A0[];
struct S9F8 {
    u8 pad0[8];
    u16 f8;
    u8 pad1[0x14 - 0xa];
};
extern struct S9F8 lbl_1_bss_9F8[];

extern s32 fn_1_4C10(void);
extern s32 fn_1_467F4(void);
extern void fn_1_4A00(s32, u8, u32);
extern void fn_1_12F17C(void);

void fn_10_4600(void) {
    s32 ready;
    u32 flags;

    if (lbl_10_bss_14 == -1) {
        fn_1_4C10();
    }

    flags = *(u32 *)(lbl_1_bss_8B3A0 + 0x140);
    if ((flags & 0x80000000) != 0 &&
        (flags & 0x40000000) == 0 &&
        (*(u32 *)(lbl_1_bss_8B3A0 + 0x94) & 8) == 0) {
        ready = 1;
    } else {
        if (fn_1_4C10() != 0) {
            ready = 1;
        } else {
            ready = 0;
        }
    }

    if (ready != 0) {
        return;
    }

    if (lbl_10_bss_14 != -1) {
        s32 value = lbl_10_bss_14;
        lbl_10_bss_14 = -1;
        lbl_1_bss_96A = (u16)value;
        return;
    }

    if (lbl_801A66C0 <= 0x12c &&
        ((lbl_1_bss_9F8[*(u8 *)(lbl_1_bss_8B3A0 + 0x9e)].f8 >> 8) & 1) == 0) {
        return;
    }

    if (fn_1_467F4() != 0) {
        return;
    }

    *(u32 *)(lbl_1_bss_8B3A0 + 0x94) |= 0x08000000;
    fn_1_4A00(0, (u8)lbl_10_bss_4938C, lbl_10_bss_49388);
    lbl_10_bss_51744 = 0;
    fn_1_12F17C();
}
/* fzgx:end fn_10_4600 */

/* fzgx:begin fn_10_472C */
extern void fn_10_C594(void);
extern void fn_1_48140(u32);
extern void fn_1_435C(u32);
extern void fn_1_426C(u32);
extern u32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

void fn_10_472C(void) {
    fn_10_C594();
    fn_1_48140(0x8b);
    if ((s32)lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
}
/* fzgx:end fn_10_472C */

/* fzgx:begin fn_10_4A84 */
extern s32 lbl_10_bss_51740;
extern s32 lbl_10_bss_49388;
extern void fn_1_435C(s32 value);
extern void fn_1_426C(s32 value);
extern void fn_10_260D4(void);

void fn_10_4A84(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    fn_10_260D4();
}
/* fzgx:end fn_10_4A84 */

/* fzgx:begin fn_10_5148 */
extern u8 lbl_10_bss_0[];
extern char lbl_10_data_6A4[11];
extern void fn_10_13D64(void);
extern void *fn_1_435C(void *);
extern void *fn_1_3F8C(void *, void *, u32, u32);
extern void fn_1_4A00(u32, u32, void *);

void fn_10_5148(void) {
    u8 *base = (u8 *)lbl_10_bss_0 + 0x50000;
    void *value;
    s16 flag;

    value = fn_1_435C(*(void **)(base - 0x6c78));
    value = fn_1_3F8C(lbl_10_data_6A4, fn_10_13D64, 0, 8);
    flag = *(s16 *)(base - 0x6c74);
    *(void **)(base + 0x1740) = value;
    fn_1_4A00(1, (u8)flag, *(void **)(base - 0x6c78));
    *(u32 *)(base + 0x1744) = 0;
}
/* fzgx:end fn_10_5148 */

/* fzgx:begin fn_10_51BC */
extern u16 lbl_1_bss_96A;

void fn_10_51BC(void) {
    lbl_1_bss_96A = 0x12;
}
/* fzgx:end fn_10_51BC */

/* fzgx:begin fn_10_51CC */
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;
extern u8 lbl_1_bss_8B3A0;

extern void fn_1_435C(u32 value);
extern void fn_1_426C(u32 value);
extern void fn_10_BEF8(void *value);

void fn_10_51CC(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    fn_10_BEF8(&lbl_1_bss_8B3A0);
}
/* fzgx:end fn_10_51CC */

/* fzgx:begin fn_10_5780 */
struct Fn105780 {
    u8 pad[0x92];
    u16 value;
};

void fn_10_5780(struct Fn105780 *obj) {
    obj->value = 8;
}
/* fzgx:end fn_10_5780 */

/* fzgx:begin fn_10_757C */
// Volatile preserves the retail's repeated reads of the shared sentinel.
extern volatile s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;
extern void fn_1_435C(u32 value);
extern void fn_1_426C(s32 value);

void fn_10_757C(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
}
/* fzgx:end fn_10_757C */

/* fzgx:begin fn_10_82BC */
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

extern void fn_1_435C(u32 value);
extern void fn_1_426C(s32 value);

void fn_10_82BC(void) {
    s32 state = lbl_10_bss_51740;

    if (state != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
}
/* fzgx:end fn_10_82BC */

/* fzgx:begin fn_10_83C0 */
typedef struct SelState {
    u8 pad_0[0x94];
    u32 flags_94;
    u8 pad_98[0x91];
    u8 field_129;
    u8 pad_12A[0x16];
    u32 field_140;
} SelState;

extern s32 lbl_10_bss_14;
extern SelState lbl_1_bss_8B3A0;
extern u16 lbl_1_bss_96A;
extern s16 lbl_10_bss_4938C;
extern u32 lbl_10_bss_49388;
extern u32 lbl_10_bss_51744;

extern s32 fn_1_4C10(void);
extern s32 fn_1_12F228(void);
extern void fn_1_12F1E8(s32 value);
extern void fn_1_4A00(s32 value, u32 arg1, u32 arg2);
extern void fn_10_25CB0(void);
extern s32 fn_10_25888(void);

void fn_10_83C0(void) {
    s32 ready;

    if (lbl_10_bss_14 == -1) {
        fn_1_4C10();
    }

    if ((lbl_1_bss_8B3A0.field_140 & ((u32)1 << 31)) != 0 &&
        (lbl_1_bss_8B3A0.field_140 & 0x40000000) == 0 &&
        (lbl_1_bss_8B3A0.flags_94 & 0x8) == 0) {
        ready = 1;
    } else if (fn_1_4C10() != 0) {
        ready = 1;
    } else {
        ready = 0;
    }

    if (ready == 0) {
        if (lbl_10_bss_14 != -1) {
            s32 state = lbl_10_bss_14;
            lbl_10_bss_14 = -1;
            lbl_1_bss_96A = (u16)state;
        } else {
            if (fn_1_12F228() != 0) {
                fn_1_12F1E8(0);
                fn_10_25CB0();
            }
            if (fn_10_25888() != 0) {
                lbl_1_bss_8B3A0.field_129 = 0;
                fn_1_12F1E8(0);
                fn_1_4A00(0, (u32)(u8)lbl_10_bss_4938C, lbl_10_bss_49388);
                lbl_10_bss_51744 = 0;
                lbl_10_bss_14 = 0x19;
            }
        }
    }
}
/* fzgx:end fn_10_83C0 */

/* fzgx:begin fn_10_84DC */
extern void fn_10_25BC8(void);
extern void fn_1_435C(u32 value);
extern void fn_1_426C(u32 value);
extern u32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

void fn_10_84DC(void) {
    fn_10_25BC8();
    if ((s32)lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = (u32)-1;
    }
}
/* fzgx:end fn_10_84DC */

/* fzgx:begin fn_10_8538 */
typedef struct {
    u8 pad[0xa4];
    u8 *ptr;
} BssObject;

extern u8 lbl_10_bss_0[];
extern char lbl_10_data_76C[25];
extern void fn_10_1B684(void);
extern BssObject lbl_1_bss_8B3A0;
extern void *lbl_1_bss_6EAD0;

extern void fn_1_435C(u32 value);
extern void *fn_1_3F8C(void *arg0, void *arg1, u32 arg2, u32 arg3);
extern void fn_1_4A00(u32 arg0, u32 arg1, u32 arg2);
extern void *fn_1_12F1E8(u32 size);
extern void fn_1_A176C(void *arg0, u32 arg1);

#pragma opt_propagation off
void fn_10_8538(void) {
    u8 *work = lbl_10_bss_0 + 0x50000;
    u8 *base = lbl_10_bss_0;
    u32 value;

    fn_1_435C(((u32 *)work)[(-0x6c78) / 4]);
    value = (u32)fn_1_3F8C(lbl_10_data_76C, fn_10_1B684, 0, 8);
    ((u32 *)work)[0x1740 / 4] = value;
    fn_1_4A00(1, (u8)((s16 *)work)[(-0x6c74) / 2], ((u32 *)work)[(-0x6c78) / 4]);
    ((u32 *)work)[0x1744 / 4] = 0;
    fn_1_12F1E8(0x384);
    lbl_1_bss_8B3A0.ptr[0x19] = 0;
    ((u32 *)base)[0x14 / 4] = (u32)-1;
    fn_1_A176C(*(void **)lbl_1_bss_6EAD0, 0x1f);
    work[0x5600] = 0xb4;
    work[0x5601] = 0;
}
#pragma opt_propagation reset
/* fzgx:end fn_10_8538 */

/* fzgx:begin fn_10_8780 */
extern u8 lbl_10_bss_55601[7];
extern u8 lbl_10_bss_55600;
extern int fn_1_4C10(void);
extern u8 fn_1_D66A8(void);
extern u8 fn_1_D66A0(int);

u8 fn_10_8780(void) {
    if (fn_1_4C10() != 0) {
        return 1;
    }
    if (lbl_10_bss_55601[0] == 0) {
        return 0;
    }
    if (fn_1_D66A8() == 0) {
        if (fn_1_D66A0(0x10) == 0) {
            /* Retail converges both failure paths here. */
            goto fail;
        }
    }
    if (lbl_10_bss_55600 == 0) {
        /* Retail places the success block after the failure block. */
        goto success;
    }
fail:
    return 0;
success:
    return 1;
}
/* fzgx:end fn_10_8780 */

/* fzgx:begin fn_10_8800 */
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;
extern u32 *lbl_1_bss_6EAD0;

extern void fn_1_435C(u32 value);
extern void fn_1_426C(s32 value);
extern void fn_1_A176C(u32 value, int arg);

void fn_10_8800(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    fn_1_A176C(*lbl_1_bss_6EAD0, 0x2d);
}
/* fzgx:end fn_10_8800 */

/* fzgx:begin fn_10_8930 */
typedef struct SelState {
    s16 state;
    u8 pad2[0x92];
    u32 flags;
    u8 pad98[6];
    u8 mode;
    u8 pad9f[0xa1];
    u32 unk140;
} SelState;

typedef struct SelEntry {
    u8 pad0[8];
    u16 flags;
    u8 pad0a[0xa];
} SelEntry;

extern s32 lbl_10_bss_14;
extern SelState lbl_1_bss_8B3A0;
extern SelEntry lbl_1_bss_9F8[];
extern s16 lbl_1_bss_96A;
extern s16 lbl_10_bss_4938C;
extern u32 lbl_10_bss_49388;
extern u32 lbl_10_bss_51744;
extern u32 lbl_1_bss_6EAB4;

extern s32 fn_1_4C10(void);
extern void fn_10_BD64(void *value);
extern s32 fn_1_12F228(void);
extern s32 fn_1_D66A0(u32 arg);
extern void fn_1_4A00(u32 arg0, u32 arg1, u32 arg2);

void fn_10_8930(void) {
    s32 ready;
    u32 flags;
    SelState *st;

    if (lbl_10_bss_14 == -1) {
        fn_1_4C10();
    }

    flags = lbl_1_bss_8B3A0.unk140;
    if ((flags & 0x80000000) != 0 &&
        (flags & 0x40000000) == 0 &&
        (lbl_1_bss_8B3A0.flags & 8) == 0) {
        ready = 1;
    } else {
        if (fn_1_4C10() != 0) {
            ready = 1;
        } else {
            ready = 0;
        }
    }

    if (ready != 0) {
        return;
    }

    if (lbl_10_bss_14 != -1) {
        s32 value = lbl_10_bss_14;
        lbl_10_bss_14 = -1;
        lbl_1_bss_96A = (s16)value;
        return;
    }

    st = &lbl_1_bss_8B3A0;
    if (((lbl_1_bss_9F8[*(u8 *)((u8 *)st + 0x9e)].flags >> 12) & 1) != 0) {
        st->state = 9;
        fn_10_BD64(st);
        lbl_10_bss_14 = 0x1a;
        fn_1_4A00(0, (u32)(lbl_10_bss_4938C & 0xff), lbl_10_bss_49388);
        lbl_10_bss_51744 = 0;
        if (lbl_10_bss_14 != 0x15) {
            lbl_1_bss_6EAB4 |= 0x24;
        }
    } else if (fn_1_12F228() != 0 &&
               ((u8)fn_1_D66A0(0xd)) == 0 &&
               ((u8)fn_1_D66A0(0xf)) == 0) {
        lbl_1_bss_8B3A0.flags |= 0x4000000;
    }
}
/* fzgx:end fn_10_8930 */

/* fzgx:begin fn_10_8AAC */
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

extern void fn_1_48140(s32 arg0);
extern void fn_1_435C(u32 arg0);
extern void fn_1_426C(s32 arg0);

void fn_10_8AAC(void) {
    fn_1_48140(2);
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
}
/* fzgx:end fn_10_8AAC */

/* fzgx:begin fn_10_8D90 */
extern s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

extern void fn_1_435C(u32 value);
extern void fn_1_426C(s32 value);

typedef struct {
    u8 pad[0x94];
    u32 flags;
} SelGlobal;

extern SelGlobal lbl_1_bss_8B3A0;

void fn_10_8D90(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    lbl_1_bss_8B3A0.flags &= ~0x00000800;
}
/* fzgx:end fn_10_8D90 */

/* fzgx:begin fn_10_9154 */
extern s32 lbl_10_bss_51740;
extern s32 lbl_10_bss_49388;
extern s32 lbl_10_data_7B0[15];
extern s32 lbl_10_bss_49384;

extern void fn_1_435C(s32 value);
extern void fn_1_426C(s32 value);

void fn_10_9154(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
    if (lbl_10_data_7B0[0] != -1) {
        fn_1_435C(lbl_10_bss_49384);
        fn_1_426C(lbl_10_data_7B0[0]);
        lbl_10_data_7B0[0] = -1;
    }
}
/* fzgx:end fn_10_9154 */

/* fzgx:begin fn_10_91E8 */
extern u32 lbl_1_bss_980[];

int fn_10_91E8(void) {
    int count = 0;
    u32 value;
    s16 i = 0;

    while (i < 4) {
        value = lbl_1_bss_980[i];

        if (value == 0x09000000 ||
            value == 0x88000000 ||
            value == 0x8B100000 ||
            value == 0x08000000) {
            count++;
        }
        i++;
    }

    return count;
}
/* fzgx:end fn_10_91E8 */

/* fzgx:begin fn_10_95A0 */
extern u32 lbl_10_data_564[];
extern void fn_1_12A2B8(s32 value);
extern void fn_1_12A2D0(s32 value);
extern void fn_1_12C5E4(void *value);
extern void fn_1_12A734(s32 value);
extern void fn_80071718(void *value);

typedef struct {
    u8 pad[0x94];
    u32 flags;
} SelGlobal;

extern SelGlobal lbl_1_bss_8B3A0;
extern void *lbl_1_bss_6D82C;

typedef struct {
    u8 pad[0x324];
    u32 a;
    u8 pad0[0x43c];
    u32 b;
    u8 pad1[0x43c];
    u32 c;
    u8 pad2[0x43c];
    u32 d;
    u8 pad3[0x43c];
    u32 e;
    u8 pad4[0x43c];
    u32 f;
    u8 pad5[0x43c];
    u32 g;
    u8 pad6[0x43c];
    u32 h;
    u8 tail[0x11c];
} SelBlock;

void fn_10_95A0(SelBlock *data) {
    s16 i;
    SelBlock *block;
    s32 value = lbl_10_data_564[0];

    if (((u32)lbl_1_bss_8B3A0.flags & ((u32)1 << 31)) == 0) {
        if (value != -1) {
            fn_1_12A2B8(1);
            fn_1_12A2D0(value);
        } else {
            fn_1_12A2B8(0);
        }

        fn_1_12C5E4(data);
        fn_1_12A2B8(0);

        if (lbl_1_bss_6D82C != 0) {
            fn_80071718(lbl_1_bss_6D82C);
            lbl_1_bss_6D82C = 0;
        }

        if (value != -1) {
            fn_1_12A734(value);
            lbl_10_data_564[0] = -1;
        }

        block = data;
        i = 0;
        while (i < 0x21) {
            block->a = lbl_10_data_564[0];
            block->b = lbl_10_data_564[0];
            block->c = lbl_10_data_564[0];
            block->d = lbl_10_data_564[0];
            block->e = lbl_10_data_564[0];
            block->f = lbl_10_data_564[0];
            block->g = lbl_10_data_564[0];
            block->h = lbl_10_data_564[0];
            i += 8;
            block = (SelBlock *)((u8 *)block + 0x2200);
        }

        block = (SelBlock *)((u8 *)data + i * 0x440);
        while (i < 0x29) {
            block->a = lbl_10_data_564[0];
            i++;
            block = (SelBlock *)((u8 *)block + 0x440);
        }
    }
}
/* fzgx:end fn_10_95A0 */

/* fzgx:begin fn_10_96F8 */
extern void fn_1_14DBCC(void *);

void fn_10_96F8(void *first, void *second) {
    s16 i;
    u8 *ptr;

    ptr = (u8 *)first;
    for (i = 0; i < 9U; i++) {
        fn_1_14DBCC(ptr);
        ptr += 0xa20;
    }

    if (second != 0) {
        ptr = (u8 *)second;
        i = 0;
        for (; i < 4; i++) {
            fn_1_14DBCC(ptr);
            ptr += 0xa20;
        }
    }
}
/* fzgx:end fn_10_96F8 */

/* fzgx:begin fn_10_A7DC */
extern int fn_1_FA070(void);
extern int fn_1_FA0BC(int);

struct SelState {
    s16 value;
    u8 padding[0x90];
    u32 flags;
};

extern struct SelState lbl_1_bss_8B3A0;

int fn_10_A7DC(s16 mode) {
    if ((lbl_1_bss_8B3A0.flags & 0x200) != 0) {
        if (mode == 0) {
            return 1;
        }
        if (mode >= 1 && mode <= 3) {
            return 1;
        }
        if (mode == 4) {
            if (fn_1_FA070() != 0) {
                return 1;
            }
        }
        if (mode == 5) {
            if (fn_1_FA0BC(lbl_1_bss_8B3A0.value == 1) != 0) {
                return 1;
            }
        }
    } else {
        if (mode >= 1 && mode <= 3) {
            return 1;
        }
        if (mode == 4) {
            if (fn_1_FA070() != 0) {
                return 1;
            }
        }
        if (mode == 5) {
            if (fn_1_FA0BC(lbl_1_bss_8B3A0.value == 1) != 0) {
                return 1;
            }
        }
    }

    return 0;
}
/* fzgx:end fn_10_A7DC */

/* fzgx:begin fn_10_BD64 */
#define SEL_MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct Fn10BD64 {
    s16 unk0;
    s16 unk2;
    s16 value4;
    s16 value6;
    s16 unk8;
    u8 padA[0x8A];
    u32 flags94;
} Fn10BD64;

typedef struct {
    u8 pad0[0x94];
    u32 flags;
} SelGlobal;

extern u8 lbl_10_bss_4938E;
extern SelGlobal lbl_1_bss_8B3A0;

void fn_10_BD64(Fn10BD64 *self) {
    s32 value;

    switch (self->unk0) {
    case 0:
        self->value4 = 1;
        value = 30;
        if (self->flags94 & 0x2) {
            value = *(s8 *)&lbl_10_bss_4938E;
        }
        self->value6 = value;
        break;
    case 1:
        if (lbl_1_bss_8B3A0.flags & 0x200) {
            self->value6 = SEL_MAX(1, SEL_MAX(self->value6, SEL_MAX(self->value4, 1)));
        } else {
            self->value6 = self->value4;
        }
        break;
    case 2:
        self->value4 = 1;
        self->value6 = 1;
        break;
    case 3:
        self->value4 = 1;
        self->value6 = 1;
        break;
    case 4:
        self->value6 = 30;
        self->value4 = 1;
        self->unk8 = 1;
        break;
    case 5:
        self->value4 = 1;
        self->value6 = 1;
        self->unk8 = 1;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    default:
        break;
    }

    if (self->value4 <= 1) {
        self->flags94 |= 0x20000000;
        return;
    }
    self->flags94 &= 0xDFFFFFFF;
    if (self->value4 == 2) {
        self->flags94 |= 0x00040000;
        return;
    }
    self->flags94 &= ~0x00040000;
}
/* fzgx:end fn_10_BD64 */

/* fzgx:begin fn_10_BEF0 */
// fn_10_BEF0: empty in retail (single blr).
void fn_10_BEF0(void) {
}
/* fzgx:end fn_10_BEF0 */

/* fzgx:begin fn_10_BEF4 */
// fn_10_BEF4: empty in retail (single blr).
void fn_10_BEF4(void) {
}
/* fzgx:end fn_10_BEF4 */

/* fzgx:begin fn_10_BEF8 */
#define SEL_MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    s16 unk0;
    u8 pad2[2];
    s16 field4;
    s16 field6;
    s16 field8;
    u8 padA[0x8A];
    u32 flags;
} SelState;

typedef struct {
    u8 pad0[0x94];
    u32 flags;
} SelGlobal;

extern u8 lbl_10_bss_4938E;
extern SelGlobal lbl_1_bss_8B3A0;

void fn_10_BEF8(SelState *state) {
    s32 value;

    switch (state->unk0) {
    case 0:
        state->field4 = 1;
        value = 30;
        if (state->flags & 0x2) {
            value = *(s8 *)&lbl_10_bss_4938E;
        }
        state->field6 = value;
        break;
    case 1:
        if (lbl_1_bss_8B3A0.flags & 0x200) {
            state->field6 = SEL_MAX(1, SEL_MAX(state->field6, SEL_MAX(state->field4, 1)));
        } else {
            state->field6 = state->field4;
        }
        break;
    case 2:
        state->field4 = 1;
        state->field6 = 1;
        break;
    case 3:
        state->field4 = 1;
        state->field6 = 1;
        break;
    case 4:
        state->field6 = 30;
        state->field4 = 1;
        state->field8 = 1;
        break;
    case 5:
        state->field4 = 1;
        state->field6 = 1;
        state->field8 = 1;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    default:
        break;
    }

    if (state->field4 <= 1) {
        state->flags |= 0x20000000;
        return;
    }
    state->flags &= 0xDFFFFFFF;
    if (state->field4 == 2) {
        state->flags |= 0x00040000;
        return;
    }
    state->flags &= ~0x00040000;
}
/* fzgx:end fn_10_BEF8 */

/* fzgx:begin fn_10_C210 */
typedef struct SelOwner {
    unsigned char pad_00A4[0xA4];
    void *entries;
} SelOwner;

typedef struct SelEntry {
    unsigned char pad_0014[0x14];
    short value;
    unsigned char pad_0024[0x0E];
    unsigned char pad_0032[0x70];
} SelEntry;

extern void fn_80008BEC(void *dst, int value, int size);

void fn_10_C210(SelOwner *owner, int index) {
    SelEntry *entry = (SelEntry *)owner->entries + (short)(index - 0xE);
    entry->value = 0;
    fn_80008BEC((unsigned char *)entry + 0x24, 0, 0x70);
}
/* fzgx:end fn_10_C210 */

/* fzgx:begin fn_10_C258 */
typedef struct SelContext {
    u8 pad[0xa4];
    u8 *entries;
} SelContext;

s16 fn_10_C258(SelContext *self, s32 index) {
    return *(s16 *)(self->entries + (s16)(index - 14) * 0x94 + 0x14);
}
/* fzgx:end fn_10_C258 */

/* fzgx:begin fn_10_C274 */
typedef struct {
    u8 _pad_00[0xa4];
    u8 *entries;
} SelObject;

void fn_10_C274(SelObject *object, int index) {
    index = (s16)(index - 0xe);
    *(s16 *)(object->entries + index * 0x94 + 0x14) += 1;
}
/* fzgx:end fn_10_C274 */

/* fzgx:begin fn_10_C298 */
typedef struct SelObject {
    u8 _pad_a4[0xa4];
    u8 *entries;
} SelObject;

void fn_10_C298(SelObject *self, int index) {
    s16 *value = (s16 *)(self->entries + (s16)(index - 0xe) * 0x94 + 0x14);
    (*value)--;
}
/* fzgx:end fn_10_C298 */

/* fzgx:begin fn_10_C2BC */
extern u8 lbl_10_data_57C[32];
extern u32 lbl_10_bss_49388;
extern u32 lbl_10_bss_5565C[2];
extern u32 lbl_10_bss_49384;
extern u32 lbl_10_bss_14;
extern u32 lbl_801A6410;

extern u32 fn_1_4630(u32, u32, u8 *, u32);
extern void fn_1_130EE8(u32, u32);

void fn_10_C2BC(void) {
    u32 value;

    value = fn_1_4630(lbl_801A6410, 0x20700, lbl_10_data_57C, 0x1766);
    lbl_10_bss_5565C[0] = value;
    fn_1_130EE8(lbl_10_bss_49384, lbl_10_bss_49388);
    lbl_10_bss_14 = -1;
}
/* fzgx:end fn_10_C2BC */

/* fzgx:begin fn_10_C49C */
extern u32 lbl_10_bss_5565C[2];
extern u32 lbl_10_bss_3C0[74736];
extern u8 lbl_10_bss_4938F;
extern u8 lbl_10_bss_49390[16];
extern u8 lbl_10_data_57C[32];
extern u32 lbl_801A6410;

extern int fn_1_1317B4(void);
extern int fn_1_B7C5C(void);
extern void fn_80008BA8(void *, u32, u32);
extern void fn_1_131004(void);
extern void fn_1_46B4(u32, u32, void *, u32);

void fn_10_C49C(void) {
    if (fn_1_1317B4() == 0) {
        if (fn_1_B7C5C() == 0) {
            fn_80008BA8(lbl_10_bss_3C0, lbl_10_bss_5565C[0], 0x20700);
            lbl_10_bss_4938F = 1;
        } else {
            lbl_10_bss_4938F = 0;
        }
    }
    if (fn_1_1317B4() == 1) {
        if (fn_1_B7C5C() == 0) {
            fn_80008BA8(lbl_10_bss_3C0 + 0x81c0, lbl_10_bss_5565C[0], 0x20700);
            lbl_10_bss_49390[0] = 1;
        } else {
            lbl_10_bss_49390[0] = 0;
        }
    }
    fn_1_131004();
    fn_1_46B4(lbl_801A6410, lbl_10_bss_5565C[0], lbl_10_data_57C, 0x17a0);
}
/* fzgx:end fn_10_C49C */

/* fzgx:begin fn_10_C594 */
extern void fn_1_451E4(void);
extern void fn_1_3308(void);
extern void fn_1_D3214(void);
extern void fn_8001AF64(void);
extern s32 fn_1_467F4(void);
extern s32 fn_1_13018(void);
extern void fn_8006FDEC(void);

void fn_10_C594(void) {
    // The retail loop checks its continuation conditions before entering the body.
    goto check;
body:
    fn_1_451E4();
    fn_1_3308();
    fn_1_D3214();
    fn_8001AF64();
check:
    if (fn_1_467F4() != 0) {
        goto body; // Continue the irreducible retail loop.
    }
    if (fn_1_13018() != 0) {
        goto body; // Continue the irreducible retail loop.
    }
    fn_8006FDEC();
}
/* fzgx:end fn_10_C594 */

/* fzgx:begin fn_10_C5E0 */
extern u8 lbl_10_data_57C[32];
extern u32 lbl_801A6410;

extern u32 fn_1_4404(void *obj);
extern void fn_1_46B4(u32, u32, void *, u32);
extern void fn_80008E84(u32);

struct Fn10C5E0 {
    u32 field_0;
};

void fn_10_C5E0(struct Fn10C5E0 *self) {
    u32 result;
    result = fn_1_4404(self);
    if (self->field_0 + 0x10000 != 0xffff) {
        fn_1_46B4(lbl_801A6410, self->field_0, lbl_10_data_57C, 0x181e);
        self->field_0 = 0xffffffff;
    }
    fn_80008E84(result);
}
/* fzgx:end fn_10_C5E0 */

/* fzgx:begin fn_10_C654 */
extern u32 fn_1_46C60(void);

void fn_10_C654(u32 *value) {
    *value = fn_1_46C60();
}
/* fzgx:end fn_10_C654 */

/* fzgx:begin fn_10_C684 */
extern u32 lbl_10_bss_55668;

u32 fn_10_C684(void) {
    return lbl_10_bss_55668;
}
/* fzgx:end fn_10_C684 */

/* fzgx:begin fn_10_C694 */
extern u8 lbl_10_bss_5566C;

u8 fn_10_C694(void) {
    return lbl_10_bss_5566C;
}
/* fzgx:end fn_10_C694 */

/* fzgx:begin fn_10_C8A8 */
extern u32 lbl_10_bss_49388;
extern void fn_1_4A00(u32, u32, u32);
extern void fn_1_12F1E8(u32);

void fn_10_C8A8(void) {
    fn_1_4A00(1, 0xf, lbl_10_bss_49388);
    fn_1_12F1E8(0x1e0);
}
/* fzgx:end fn_10_C8A8 */

/* fzgx:begin fn_10_C8E4 */
extern s32 lbl_1_bss_7180C;
extern u32 lbl_10_bss_55670[4];
extern s16 lbl_1_bss_96A;
extern void fn_10_CEC4(u32 arg0);
extern int fn_1_B7E98(int arg0);

void fn_10_C8E4(void) {
    if (lbl_1_bss_7180C == 0) {
        fn_10_CEC4(lbl_10_bss_55670[0]);
    } else if (fn_1_B7E98(1) == 0) {
        fn_10_CEC4(lbl_10_bss_55670[0]);
    } else {
        lbl_1_bss_96A = 0x1c;
    }
}
/* fzgx:end fn_10_C8E4 */

/* fzgx:begin fn_10_C954 */
// fn_10_C954: empty in retail (single blr).
void fn_10_C954(void) {
}
/* fzgx:end fn_10_C954 */

/* fzgx:begin fn_10_C958 */
extern void fn_80008BEC(void *dst, int value, int size);
extern void fn_1_AA6D8(int arg0, int arg1, void *data);
extern u8 lbl_1_bss_718E0;

typedef struct Fn10C958Data {
    u8 unk00;
    u8 unk01[3];
    u32 unk04;
    u8 unk08[4];
    void *unk0c;
    u8 unk10[20];
} Fn10C958Data;

void fn_10_C958(void) {
    Fn10C958Data data;

    fn_80008BEC(&data, 0, 0x24);
    data.unk00 = 1;
    data.unk04 = 0x2004;
    data.unk0c = &lbl_1_bss_718E0;
    fn_1_AA6D8(2, 4, &data);
}
/* fzgx:end fn_10_C958 */

/* fzgx:begin fn_10_C9B0 */
extern u8 fn_1_B7C00(void);
extern int fn_1_B7C5C(void);
extern void fn_1_F79C8(void);
extern s16 lbl_1_bss_96A;

void fn_10_C9B0(void) {
    if (!fn_1_B7C00()) {
        if (!fn_1_B7C5C()) {
            fn_1_F79C8();
        }
        lbl_1_bss_96A = 0x1d;
    }
}
/* fzgx:end fn_10_C9B0 */

/* fzgx:begin fn_10_C9F4 */
// fn_10_C9F4: empty in retail (single blr).
void fn_10_C9F4(void) {
}
/* fzgx:end fn_10_C9F4 */

/* fzgx:begin fn_10_C9F8 */
extern u32 lbl_10_bss_3C0[74736];
extern void fn_80008BEC(void *dst, int value, u32 size);
extern void fn_1_AA6D8(int arg0, int arg1, void *arg2);

void fn_10_C9F8(void) {
    struct {
        u8 kind;
        u8 pad[3];
        u32 value;
        u8 pad2[4];
        u32 buffer;
        u8 tail[0x18];
    } local;

    fn_80008BEC(&local, 0, 0x24);
    local.kind = 3;
    local.value = 0x2004;
    local.buffer = (u32)((u8 *)lbl_10_bss_3C0 + 0x20700);
    fn_1_AA6D8(2, 1, &local);
}
/* fzgx:end fn_10_C9F8 */

/* fzgx:begin fn_10_CA58 */
extern u32 lbl_10_bss_55670[4];
extern u8 fn_1_B7C00(void);
extern void fn_10_CEC4(u32);

void fn_10_CA58(void) {
    if (!fn_1_B7C00()) {
        fn_10_CEC4(lbl_10_bss_55670[0]);
    }
}
/* fzgx:end fn_10_CA58 */

/* fzgx:begin fn_10_CA90 */
// fn_10_CA90: empty in retail (single blr).
void fn_10_CA90(void) {
}
/* fzgx:end fn_10_CA90 */

/* fzgx:begin fn_10_CD90 */
struct fn_10_CD90_lbl_10_bss_51740 {
    u32 unk_0;
};

extern struct fn_10_CD90_lbl_10_bss_51740 lbl_10_bss_51740;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_10_bss_49388;

void fn_10_CD90(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if ((s32)lbl_10_bss_51740.unk_0 != -1) {
    v0 = (u32)&lbl_10_bss_49388;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t0 = fn_1_435C(v0);
    v0 = t0;
    v0 = (u32)&lbl_10_bss_51740;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t1 = fn_1_426C(v0);
    v0 = t1;
    lbl_10_bss_51740.unk_0 = -1;
    }
}
/* fzgx:end fn_10_CD90 */

/* fzgx:begin fn_10_CDE8 */
extern u8 lbl_10_bss_0[];
extern char lbl_10_data_8F4[19];
extern void fn_10_13E18(void);

extern void fn_1_435C(void *resource);
extern void *fn_1_3F8C(char *data, void (*handler)(void), int arg2, int arg3);
extern void fn_1_4A00(int arg0, int arg1, void *resource);

void fn_10_CDE8(void) {
    u8 *state = (u8 *)lbl_10_bss_0 + 0x50000;
    void *registration;
    s16 mode;

    fn_1_435C(*(void **)(state - 0x6c78));
    registration = fn_1_3F8C(lbl_10_data_8F4, fn_10_13E18, 0, 8);
    mode = *(s16 *)(state - 0x6c74);
    *(void **)(state + 0x1740) = registration;
    fn_1_4A00(1, (u8)mode, *(void **)(state - 0x6c78));
    *(u32 *)(state + 0x1744) = 0;
}
/* fzgx:end fn_10_CDE8 */

/* fzgx:begin fn_10_CE5C */
extern u16 lbl_1_bss_96A;

void fn_10_CE5C(void) {
    lbl_1_bss_96A = 0xf;
}
/* fzgx:end fn_10_CE5C */

/* fzgx:begin fn_10_CE6C */
// Volatile preserves the retail's repeated sentinel accesses across calls.
extern volatile s32 lbl_10_bss_51740;
extern u32 lbl_10_bss_49388;

void fn_10_CE6C(void) {
    if (lbl_10_bss_51740 != -1) {
        fn_1_435C(lbl_10_bss_49388);
        fn_1_426C(lbl_10_bss_51740);
        lbl_10_bss_51740 = -1;
    }
}
/* fzgx:end fn_10_CE6C */

/* fzgx:begin fn_10_CEC4 */
extern u16 lbl_1_bss_96A;

void fn_10_CEC4(u32 flags) {
    u32 shift;
    u16 value;

    shift = 1;
    if (__rlwnm(flags, shift, 31, 31)) {
        value = 0x17;
    } else {
        shift = 2;
        if (__rlwnm(flags, shift, 31, 31)) {
            value = 0x19;
        } else {
            shift = 3;
            if (__rlwnm(flags, shift, 31, 31)) {
                value = 0x15;
            } else {
                shift = 4;
                if (__rlwnm(flags, shift, 31, 31) ||
                    (shift = 5, __rlwnm(flags, shift, 31, 31))) {
                    value = 0x0e;
                } else {
                    value = 0x17;
                }
            }
        }
    }
    lbl_1_bss_96A = value;
}
/* fzgx:end fn_10_CEC4 */

/* fzgx:begin fn_10_CF30 */
extern u32 lbl_10_bss_55670[4];

void fn_10_CF30(u32 shift) {
    lbl_10_bss_55670[0] |= (1u << 31) >> shift;
}
/* fzgx:end fn_10_CF30 */

/* fzgx:begin fn_10_CF50 */
extern u8 lbl_10_data_908[1016];
extern s16 lbl_1_bss_962;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

typedef void (*SelCallback)(void);

typedef struct SelEntry {
    u8 pad[0x20];
    SelCallback callback;
    u32 value_24;
    u32 value_28;
} SelEntry;

void fn_10_CF50(void) {
    SelEntry *entry;
    s32 index;

    entry = (SelEntry *)lbl_10_data_908;
    index = (s32)lbl_1_bss_962 - 0xd;
    entry += index;
    lbl_1_bss_71688 = entry->value_24;
    lbl_1_bss_7168C = entry->value_28;
    entry->callback();
}
/* fzgx:end fn_10_CF50 */

/* fzgx:begin fn_10_FF08 */
typedef struct SelState {
    u8 pad_0[0x94];
    u32 flags;
} SelState;

extern SelState lbl_1_bss_8B3A0;
extern s16 lbl_1_bss_8CA26;
extern void fn_10_FF54(void);
extern void fn_10_10168(void);

void fn_10_FF08(void) {
    if ((lbl_1_bss_8B3A0.flags & 0x40000000) != 0 &&
        lbl_1_bss_8CA26 == 0) {
        fn_10_FF54();
    } else {
        fn_10_10168();
    }
}
/* fzgx:end fn_10_FF08 */

/* fzgx:begin fn_10_10D2C */
typedef struct {
    u32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    u8 pad_10[0x20];
    u32 unk_30;
    u8 pad_34[0x24];
} SelFontPacket;

typedef struct {
    u8 pad_000[0x174];
    f32 unk_174;
    u8 pad_178[0x180];
    f32 unk_2F8;
    f32 unk_2FC;
} SelFloatPool;

extern SelFontPacket lbl_1_rodata_26F8;
extern SelFloatPool lbl_10_rodata_158;
extern int fn_1_4F734(SelFontPacket *);

#pragma opt_propagation off
void fn_10_10D2C(void) {
    SelFloatPool *pool = &lbl_10_rodata_158;
    SelFontPacket local = lbl_1_rodata_26F8;

    local.unk_00 = 0x9A11;
    local.unk_04 = pool->unk_2F8;
    local.unk_08 = pool->unk_2FC;
    local.unk_0C = pool->unk_174;
    local.unk_30 = 0xA;
    fn_1_4F734(&local);
}
#pragma opt_propagation reset
/* fzgx:end fn_10_10D2C */

/* fzgx:begin fn_10_13D64 */
extern struct fn_10_13D64_lbl_10_rodata_158 lbl_10_rodata_158;
extern u32 fn_1_49410(void);
extern u32 fn_1_4955C(f32, f32);
extern u32 fn_1_495B0(u32);
extern u32 fn_1_495C8(u32);
extern u32 fn_1_496FC(f32, f32);
extern u32 fn_1_53C9C(u32, u32, f32, f32, f32, f32, f32);
extern u32 lbl_10_data_5EC0;
extern u32 lbl_10_data_5EE0;
extern u32 lbl_801A66B4;

struct fn_10_13D64_lbl_10_rodata_158 {
    u8 pad_0[0x58];
    f32 unk_58;
    u8 pad_5C[0x134];
    f32 unk_190;
    u8 pad_194[0xC4];
    f32 unk_258;
    u8 pad_25C[0x34];
    f32 unk_290;
    u8 pad_294[0x208];
    f32 unk_49C;
};

u32 fn_10_13D64(u32 arg0, f32 arg1) {
    struct fn_10_13D64_lbl_10_rodata_158 *p_lbl_10_rodata_158;
    f32 v0;
    u32 v1;
    f32 v2;
    u32 t5, t6;
    p_lbl_10_rodata_158 = (struct fn_10_13D64_lbl_10_rodata_158 *)&lbl_10_rodata_158;
    fn_1_49410();
    fn_1_495B0(0x80000000);
    fn_1_495C8(9);
    v0 = p_lbl_10_rodata_158->unk_49C;
    fn_1_4955C(v0, v0);
    fn_1_496FC(p_lbl_10_rodata_158->unk_58, p_lbl_10_rodata_158->unk_258);
    v1 = arg0;
    v2 = arg1;
    if ((s32)lbl_801A66B4 == 5) {
    v2 = p_lbl_10_rodata_158->unk_58;
    v1 = 0;
    t5 = fn_1_53C9C(v1, (u32)&lbl_10_data_5EC0, v2, p_lbl_10_rodata_158->unk_258, p_lbl_10_rodata_158->unk_290, p_lbl_10_rodata_158->unk_190, p_lbl_10_rodata_158->unk_49C);
    v1 = t5;
    } else {
    v2 = p_lbl_10_rodata_158->unk_58;
    v1 = 0;
    t6 = fn_1_53C9C(v1, (u32)&lbl_10_data_5EE0, v2, p_lbl_10_rodata_158->unk_258, p_lbl_10_rodata_158->unk_290, p_lbl_10_rodata_158->unk_190, p_lbl_10_rodata_158->unk_49C);
    v1 = t6;
    }
    return v1;
}
/* fzgx:end fn_10_13D64 */

/* fzgx:begin fn_10_13E18 */
extern struct fn_10_13E18_lbl_10_rodata_158 lbl_10_rodata_158;
extern u32 fn_1_49410(void);
extern u32 fn_1_4955C(f32, f32);
extern u32 fn_1_495B0(u32);
extern u32 fn_1_495C8(u32);
extern u32 fn_1_496FC(f32, f32);
extern u32 fn_1_53C9C(u32, u32, f32, f32, f32, f32, f32);
extern u32 lbl_10_data_5F00;
extern u32 lbl_10_data_5F1C;
extern u32 lbl_801A66B4;

struct fn_10_13E18_lbl_10_rodata_158 {
    u8 pad_0[0x58];
    f32 unk_58;
    u8 pad_5C[0x134];
    f32 unk_190;
    u8 pad_194[0xC4];
    f32 unk_258;
    u8 pad_25C[0x34];
    f32 unk_290;
    u8 pad_294[0x208];
    f32 unk_49C;
};

u32 fn_10_13E18(u32 arg0, f32 arg1) {
    struct fn_10_13E18_lbl_10_rodata_158 *p_lbl_10_rodata_158;
    f32 v0;
    u32 v1;
    f32 v2;
    u32 t5, t6;
    p_lbl_10_rodata_158 = (struct fn_10_13E18_lbl_10_rodata_158 *)&lbl_10_rodata_158;
    fn_1_49410();
    fn_1_495B0(0x80000000);
    fn_1_495C8(9);
    v0 = p_lbl_10_rodata_158->unk_49C;
    fn_1_4955C(v0, v0);
    fn_1_496FC(p_lbl_10_rodata_158->unk_58, p_lbl_10_rodata_158->unk_258);
    v1 = arg0;
    v2 = arg1;
    if ((s32)lbl_801A66B4 == 5) {
    v2 = p_lbl_10_rodata_158->unk_58;
    v1 = 0;
    t5 = fn_1_53C9C(v1, (u32)&lbl_10_data_5F00, v2, p_lbl_10_rodata_158->unk_258, p_lbl_10_rodata_158->unk_290, p_lbl_10_rodata_158->unk_190, p_lbl_10_rodata_158->unk_49C);
    v1 = t5;
    } else {
    v2 = p_lbl_10_rodata_158->unk_58;
    v1 = 0;
    t6 = fn_1_53C9C(v1, (u32)&lbl_10_data_5F1C, v2, p_lbl_10_rodata_158->unk_258, p_lbl_10_rodata_158->unk_290, p_lbl_10_rodata_158->unk_190, p_lbl_10_rodata_158->unk_49C);
    v1 = t6;
    }
    return v1;
}
/* fzgx:end fn_10_13E18 */

/* fzgx:begin fn_10_160BC */
extern int fn_1_F89E4(int value);

int fn_10_160BC(s16 value) {
    switch (value) {
    case 0x24:
        return fn_1_F89E4(0);
    case 0x1f:
        return fn_1_F89E4(1);
    case 0x20:
        return fn_1_F89E4(2);
    case 0x21:
        return fn_1_F89E4(3);
    case 0x22:
        return fn_1_F89E4(4);
    case 0x23:
        return fn_1_F89E4(5);
    default:
        return 1;
    }
}
/* fzgx:end fn_10_160BC */

/* fzgx:begin fn_10_19290 */
extern void fn_800736C0(int, void *);
extern void fn_80073620(int, int);
extern void fn_80072CC4(int, int, int, int, int);
extern void fn_80072E20(int, int, int, int, int, int);

void fn_10_19290(void) {
    struct {
        u32 a;
        u8 b[4];
    } local;
    local.b[3] = 0xff;
    local.a = *(u32 *)&local.b[0];
    fn_800736C0(3, &local);
    fn_80073620(0, 0x1f);
    fn_80072CC4(0, 4, 7, 6, 7);
    fn_80072E20(0, 0xe, 0, 0, 0, 0);
}
/* fzgx:end fn_10_19290 */

/* fzgx:begin fn_10_1B658 */
// fn_10_1B658: empty in retail (single blr).
void fn_10_1B658(void) {
}
/* fzgx:end fn_10_1B658 */

/* fzgx:begin fn_10_1B65C */
// fn_10_1B65C: empty in retail (single blr).
void fn_10_1B65C(void) {
}
/* fzgx:end fn_10_1B65C */

/* fzgx:begin fn_10_1B660 */
// fn_10_1B660: empty in retail (single blr).
void fn_10_1B660(void) {
}
/* fzgx:end fn_10_1B660 */

/* fzgx:begin fn_10_1B664 */
extern void fn_1_13D02C(void);

void fn_10_1B664(void) {
    fn_1_13D02C();
}
/* fzgx:end fn_10_1B664 */

/* fzgx:begin fn_10_1B684 */
extern void fn_1_13D02C(void);
extern void fn_10_1B6CC(void);

void fn_10_1B684(void) {
    fn_1_13D02C();
    fn_10_1B6CC();
}
/* fzgx:end fn_10_1B684 */

/* fzgx:begin fn_10_1B6A8 */
extern void fn_1_13D02C(void);
extern void fn_10_1B6CC(void);

void fn_10_1B6A8(void) {
    fn_1_13D02C();
    fn_10_1B6CC();
}
/* fzgx:end fn_10_1B6A8 */

/* fzgx:begin fn_10_1BCD0 */
#include "font.h"

struct fn_10_1BCD0_Copy88 { u32 a[22]; };
struct fn_10_1BCD0_lbl_10_rodata_158 {
    u8 pad_0[0x48];
    f32 unk_48;
    f32 unk_4C;
    u8 pad_50[0x8];
    f32 unk_58;
    u8 pad_5C[0xF4];
    f32 unk_150;
    u8 pad_154[0x23C];
    f32 unk_390;
    u8 pad_394[0x10C];
    f32 unk_4A0;
    u8 pad_4A4[0x388];
    f32 unk_82C;
    u8 pad_830[0x7A8];
    u32 unk_FD8;
    u32 unk_FDC;
    u32 unk_FE0;
    u32 unk_FE4;
    f32 unk_FE8;
    f32 unk_FEC;
    f32 unk_FF0;
};

extern int fn_1_4F734(FontDrawPacket *);
extern struct fn_10_1BCD0_lbl_10_rodata_158 lbl_10_rodata_158;
extern u32 lbl_1_rodata_26F8;

void fn_10_1BCD0(void) {
    FontDrawPacket loc_8;
    f32 v21;
    u32 v20;
    f32 v19;
    f32 v18;
    f32 v17;
    u32 v16;
    f32 v15;
    f32 v14;
    f32 v13;
    u32 v12;
    f32 v11;
    f32 v10;
    u32 v9;
    u32 v8;
    f32 v7;
    f32 v6;
    f32 v5;
    f32 v4;
    f32 v3;
    f32 v2;
    f32 v1;
    f32 v0;
    struct fn_10_1BCD0_lbl_10_rodata_158 *p_lbl_10_rodata_158;
    /* frame */
    p_lbl_10_rodata_158 = (struct fn_10_1BCD0_lbl_10_rodata_158 *)&lbl_10_rodata_158;
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v0 = p_lbl_10_rodata_158->unk_4C;
    loc_8.image = (0x10000 - 26107);
    loc_8.x = v0;
    loc_8.y = v0;
    loc_8.z = p_lbl_10_rodata_158->unk_150;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v1 = p_lbl_10_rodata_158->unk_58;
    v2 = p_lbl_10_rodata_158->unk_4C;
    loc_8.image = (0x10000 - 26107);
    loc_8.x = v1;
    loc_8.y = v2;
    loc_8.z = p_lbl_10_rodata_158->unk_390;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v3 = p_lbl_10_rodata_158->unk_4C;
    v4 = p_lbl_10_rodata_158->unk_FE8;
    loc_8.image = (0x10000 - 26111);
    loc_8.x = v3;
    loc_8.y = v4;
    loc_8.z = p_lbl_10_rodata_158->unk_FEC;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v5 = p_lbl_10_rodata_158->unk_58;
    v6 = p_lbl_10_rodata_158->unk_4A0;
    v7 = p_lbl_10_rodata_158->unk_82C;
    v8 = (0x10000 - 26085);
    v9 = (0x100000 + 7);
    loc_8.image = v8;
    loc_8.x = v5;
    loc_8.y = v6;
    loc_8.z = v7;
    loc_8.flags = v9;
    *(u32 *)((u8 *)&loc_8 + 56) = p_lbl_10_rodata_158->unk_FD8;
    loc_8.alpha = p_lbl_10_rodata_158->unk_48;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v10 = p_lbl_10_rodata_158->unk_58;
    v11 = p_lbl_10_rodata_158->unk_4A0;
    v12 = (0x10000 - 26085);
    v13 = p_lbl_10_rodata_158->unk_82C;
    loc_8.image = v12;
    loc_8.x = v10;
    loc_8.y = v11;
    loc_8.z = v13;
    loc_8.flags = 0x180000;
    *(u32 *)((u8 *)&loc_8 + 56) = p_lbl_10_rodata_158->unk_FDC;
    loc_8.alpha = p_lbl_10_rodata_158->unk_48;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v14 = p_lbl_10_rodata_158->unk_58;
    v15 = p_lbl_10_rodata_158->unk_FF0;
    v16 = (0x10000 - 26085);
    v17 = p_lbl_10_rodata_158->unk_82C;
    loc_8.image = v16;
    loc_8.x = v14;
    loc_8.y = v15;
    loc_8.z = v17;
    loc_8.flags = 7;
    *(u32 *)((u8 *)&loc_8 + 56) = p_lbl_10_rodata_158->unk_FE0;
    loc_8.alpha = p_lbl_10_rodata_158->unk_48;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v18 = p_lbl_10_rodata_158->unk_58;
    v19 = p_lbl_10_rodata_158->unk_FF0;
    v20 = (0x10000 - 26085);
    v21 = p_lbl_10_rodata_158->unk_82C;
    loc_8.image = v20;
    loc_8.x = v18;
    loc_8.y = v19;
    loc_8.z = v21;
    loc_8.flags = 0x80000;
    *(u32 *)((u8 *)&loc_8 + 56) = p_lbl_10_rodata_158->unk_FE4;
    loc_8.alpha = p_lbl_10_rodata_158->unk_48;
    fn_1_4F734((FontDrawPacket *)&loc_8);
}
/* fzgx:end fn_10_1BCD0 */

/* fzgx:begin fn_10_1E67C */
extern struct fn_10_1E67C_lbl_10_rodata_158 lbl_10_rodata_158;
extern u32 fn_1_49410(u32);
extern u32 fn_1_4955C(u32, f32, f32);
extern u32 fn_1_49590(u32, f32);
extern u32 fn_1_495B0(u32);
extern u32 fn_1_495C8(u32);
extern u32 fn_1_496FC(u32, f32, f32);
extern u32 fn_1_4AE0C(u32, ...);

struct fn_10_1E67C_lbl_10_rodata_158 {
    u8 pad_0[0x48];
    f32 unk_48;
    u8 pad_4C[0xC];
    f32 unk_58;
    u8 pad_5C[0xBC];
    f32 unk_118;
    u8 pad_11C[0xEE4];
    f32 unk_1000;
};

void fn_10_1E67C(u32 arg0) {
    struct fn_10_1E67C_lbl_10_rodata_158 *p_lbl_10_rodata_158;
    f32 v0;
    u32 t0, t3, t4;
    p_lbl_10_rodata_158 = (struct fn_10_1E67C_lbl_10_rodata_158 *)&lbl_10_rodata_158;
    t0 = fn_1_49410(arg0);
    fn_1_496FC(t0, p_lbl_10_rodata_158->unk_58, p_lbl_10_rodata_158->unk_1000);
    fn_1_495B0(0x80000000);
    t3 = fn_1_495C8(1);
    v0 = p_lbl_10_rodata_158->unk_118;
    t4 = fn_1_4955C(t3, v0, v0);
    fn_1_49590(t4, p_lbl_10_rodata_158->unk_48);
    fn_1_4AE0C(arg0);
}
/* fzgx:end fn_10_1E67C */

/* fzgx:begin fn_10_1FEF4 */
extern f32 lbl_10_rodata_158[19];
extern u8 jumptable_10_data_67E0[28];
extern u8 lbl_10_data_5C1C[456];
extern u8 lbl_10_data_1038[4];
extern s32 lbl_801A66B4;

extern void fn_1_49410(void);
extern void fn_1_495B0(s32 value);
extern void fn_1_496FC(f32 arg0, f32 arg1);
extern void fn_1_4954C(f32 value);
extern void fn_1_4955C(f32 arg0, f32 arg1);
extern void fn_1_495C8(s32 value);
extern void fn_1_49590(f32 value);
extern void fn_1_4CE48(u8 *arg0, f32 value);
extern f32 fn_1_4B090(u8 *arg0);
extern void fn_1_53B14(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);

void fn_10_1FEF4(s32 arg0) {
    f32 *constants = lbl_10_rodata_158;
    u8 *value;
    s32 index;
    s32 inRange;

    if (arg0 - 12 < 0) {
        index = 0;
    } else {
        index = arg0 - 12 > 6 ? 6 : arg0 - 12;
    }

    switch (index) {
    case 0:
        value = ((u8 **)(lbl_10_data_5C1C + 0x138))[lbl_801A66B4];
        break;
    case 1:
        value = ((u8 **)(lbl_10_data_5C1C + 0x150))[lbl_801A66B4];
        break;
    case 2:
        value = lbl_10_data_1038;
        break;
    case 3:
        value = ((u8 **)(lbl_10_data_5C1C + 0x168))[lbl_801A66B4];
        break;
    case 4:
        value = ((u8 **)(lbl_10_data_5C1C + 0x180))[lbl_801A66B4];
        break;
    case 5:
        value = ((u8 **)(lbl_10_data_5C1C + 0x198))[lbl_801A66B4];
        break;
    case 6:
        value = ((u8 **)(lbl_10_data_5C1C + 0x1b0))[lbl_801A66B4];
        break;
    }

    inRange = arg0 - 12 > 6 ? 0 : !(arg0 - 12 < 0);
    if (inRange) {
        fn_1_49410();
        fn_1_495B0(-2147483648);
        fn_1_496FC(constants[22], constants[1160]);
        fn_1_4954C((f32)((f64)constants[1161] - *(f64 *)(constants + 1162)));
        fn_1_4955C(constants[112], constants[112]);
        fn_1_495C8(9);
        fn_1_49590(constants[18]);
        fn_1_4CE48(value, constants[1164]);
        fn_1_53B14(0, constants[22], constants[1160],
            constants[1134], constants[1165] + fn_1_4B090(value),
            constants[1161]);
    }
}
/* fzgx:end fn_10_1FEF4 */

/* fzgx:begin fn_10_21C20 */
extern u8 lbl_10_data_1E80[816];

u32 fn_10_21C20(s16 row, s16 column) {
    return ((u32 (*)[6])lbl_10_data_1E80)[row][column];
}
/* fzgx:end fn_10_21C20 */

/* fzgx:begin fn_10_21DA8 */
extern f32 lbl_10_rodata_158[];
extern u32 lbl_10_data_5E24[2];
extern s32 lbl_801A66B4;

extern void fn_1_49410(void);
extern void fn_1_495B0(s32 value);
extern void fn_1_53C9C(s32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

void fn_10_21DA8(void) {
    f32 *constants = lbl_10_rodata_158;
    u32 value;

    if (lbl_801A66B4 == 5) {
        value = lbl_10_data_5E24[0];
    } else {
        value = lbl_10_data_5E24[1];
    }

    fn_1_49410();
    fn_1_495B0(-2147483648);
    fn_1_53C9C(0, value,
        constants[22],
        constants[150],
        constants[164],
        constants[735],
        constants[17]);
}
/* fzgx:end fn_10_21DA8 */

/* fzgx:begin fn_10_2228C */
extern u8 lbl_10_bss_55CE0;

typedef struct {
    u8 pad_00[0x22];
    u8 flag;
} SelState;

typedef struct {
    u8 pad_00[0xa4];
    SelState *state;
} SelGlobals;

extern SelGlobals lbl_1_bss_8B3A0;

extern void fn_1_140EE8(u8, int, int);
extern void fn_10_22330(int);
extern void fn_1_52070(int);
extern void fn_1_1461C8(int, u8);
extern void fn_10_2287C(void);
extern void fn_1_52088(void);
extern void fn_1_144F40(int, u8 *);
extern void fn_10_266AC(void);

void fn_10_2228C(void) {
    SelGlobals *globals = &lbl_1_bss_8B3A0;

    fn_1_140EE8(lbl_10_bss_55CE0, 1, 0);
    fn_10_22330(!globals->state->flag);

    if (globals->state->flag) {
        fn_1_52070(0x140);
        fn_1_1461C8(4, lbl_10_bss_55CE0);
        fn_10_2287C();
        fn_1_52088();
    } else {
        fn_1_144F40(6, &lbl_10_bss_55CE0);
        fn_10_266AC();
    }
}
/* fzgx:end fn_10_2228C */

/* fzgx:begin fn_10_2323C */
extern u8 lbl_10_bss_55680;

void fn_10_2323C(void) {
    lbl_10_bss_55680 = 1;
}
/* fzgx:end fn_10_2323C */

/* fzgx:begin fn_10_2324C */
extern u8 lbl_10_bss_55680;

void fn_10_2324C(void) {
    lbl_10_bss_55680 = 0;
}
/* fzgx:end fn_10_2324C */
