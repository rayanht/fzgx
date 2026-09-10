#include "types.h"
extern u8 lbl_3_bss_A17A0[44];
extern s16 lbl_3_bss_A17CC;
extern u32 lbl_3_bss_A176C;
extern u32 *lbl_3_bss_A1770;
extern u32 *lbl_3_bss_A1774;
extern u8 lbl_3_data_3574[60];
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32, u32, u8 *, s32);

/* fzgx:begin fn_3_1349C noprologue */
#include "types.h"

extern void fn_1_4CC0(void);
extern u32 lbl_3_bss_A17A0;
extern s16 lbl_3_bss_A17D2;
extern u16 lbl_1_bss_96A;

void fn_3_1349C(void) {
    fn_1_4CC0();
    if ((lbl_3_bss_A17A0 & 0x20000000) != 0) {
        if (lbl_3_bss_A17D2 > 0) {
            lbl_3_bss_A17D2--;
            if (lbl_3_bss_A17D2 == 0) {
                lbl_1_bss_96A = 0x5c;
                lbl_3_bss_A17A0 &= ~0x20000000;
            }
        }
    }
}
/* fzgx:end fn_3_1349C */

/* fzgx:begin fn_3_14008 */
void fn_3_14008(void) {
    u32 *value = (u32 *)lbl_3_bss_A17A0;
    *value |= 0x40000000;
}
/* fzgx:end fn_3_14008 */

/* fzgx:begin fn_3_1401C */
u32 fn_3_1401C(void) {
    return *(u32 *)(lbl_3_bss_A17A0 + 0x20);
}
/* fzgx:end fn_3_1401C */

/* fzgx:begin fn_3_1402C */
u32 fn_3_1402C(u8 index) {
    if (lbl_3_bss_A17CC <= index) {
        return 0;
    }
    return ((u32 *)lbl_3_bss_A176C)[index];
}
/* fzgx:end fn_3_1402C */

/* fzgx:begin fn_3_14064 */
u32 fn_3_14064(void) {
    return lbl_3_bss_A17CC & 0xff;
}
/* fzgx:end fn_3_14064 */

/* fzgx:begin fn_3_14074 */
u8 *fn_3_14074(void) {
    return lbl_3_bss_A17A0;
}
/* fzgx:end fn_3_14074 */

/* fzgx:begin fn_3_141A8 noprologue */
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 width;
    s16 height;
    u8 pad14[0x6];
    s16 index;
    u8 pad1c[0x4];
    void *data;
} EmblemState;

typedef struct {
    u32 flags;
    u8 pad4[0x2];
    u8 width;
    u8 height;
    u32 unk8;
    u8 pad0c[0x8];
    void *resource;
} EmblemEntry;

extern EmblemState lbl_3_bss_A17A0;
extern EmblemEntry lbl_3_bss_A17D4[128];
extern void fn_80008BA8(void *, void *, u32);
extern void fn_3_17830(void);
extern void fn_3_177AC(u32 *);

void fn_3_141A8(u32 flags) {
    u32 value;

    if ((flags & ~0x3fffffffU) == 0) {
        return;
    }
    if (flags & 0x40000000U) {
        flags = 0; /* directions are exclusive: consume the mask */
        if (lbl_3_bss_A17A0.index + 1 == 0x80) {
            lbl_3_bss_A17A0.index = 0;
        } else {
            lbl_3_bss_A17A0.index += 1;
        }
    }
    if (flags & 0x80000000U) {
        if (lbl_3_bss_A17A0.index - 1 < 0) {
            lbl_3_bss_A17A0.index = 0x7f;
        } else {
            lbl_3_bss_A17A0.index -= 1;
        }
    }
    if (lbl_3_bss_A17D4[lbl_3_bss_A17A0.index].flags & 0x20000000U) {
        return;
    }
    fn_80008BA8(lbl_3_bss_A17A0.data,
                lbl_3_bss_A17D4[lbl_3_bss_A17A0.index].resource, 0x2000);
    lbl_3_bss_A17A0.width = lbl_3_bss_A17D4[lbl_3_bss_A17A0.index].width;
    lbl_3_bss_A17A0.height = lbl_3_bss_A17D4[lbl_3_bss_A17A0.index].height;
    fn_3_17830();
    value = lbl_3_bss_A17D4[lbl_3_bss_A17A0.index].unk8;
    fn_3_177AC(&value);
}
/* fzgx:end fn_3_141A8 */

/* fzgx:begin fn_3_142C4 */
void fn_3_142C4(void) {
    u8 i;

    for (i = 0; i < 0x80; i++) {
        if (lbl_3_bss_A1770[i] != 0) {
            fn_1_46B4(lbl_801A6410, lbl_3_bss_A1770[i],
                       lbl_3_data_3574, 0x321);
            lbl_3_bss_A1770[i] = 0;
        }

        if (lbl_3_bss_A1774[i] != 0) {
            fn_1_46B4(lbl_801A6410, lbl_3_bss_A1774[i],
                       lbl_3_data_3574, 0x326);
            lbl_3_bss_A1774[i] = 0;
        }
    }

    if (lbl_3_bss_A1774 != 0) {
        fn_1_46B4(lbl_801A6410, (u32)lbl_3_bss_A1774,
                   lbl_3_data_3574, 0x32e);
        lbl_3_bss_A1774 = 0;
    }

    if (lbl_3_bss_A1770 != 0) {
        fn_1_46B4(lbl_801A6410, (u32)lbl_3_bss_A1770,
                   lbl_3_data_3574, 0x334);
        lbl_3_bss_A1770 = 0;
    }
}
/* fzgx:end fn_3_142C4 */

/* fzgx:begin fn_3_1441C */
typedef struct fn_3_1441C_EmblemState {
    u8 pad[0x18];
    s16 field_18;
    s16 field_1a;
} fn_3_1441C_EmblemState;

u8 fn_3_1441C(void) {
    fn_3_1441C_EmblemState *state = (fn_3_1441C_EmblemState *)lbl_3_bss_A17A0;
    return state->field_1a == state->field_18;
}
/* fzgx:end fn_3_1441C */

/* fzgx:begin fn_3_1443C */
typedef struct {
    u8 pad16[0x16];
    s16 value16;
    u8 pad18[2];
    s16 value1a;
} fn_3_1443C_EmblemState;

u8 fn_3_1443C(void) {
    fn_3_1443C_EmblemState *state = (fn_3_1443C_EmblemState *)lbl_3_bss_A17A0;
    return state->value1a == state->value16;
}
/* fzgx:end fn_3_1443C */

/* fzgx:begin fn_3_14600 noprologue */
#include "types.h"

struct fn_3_14600_lbl_3_bss_A17D4_0_E24 {
    u8 pad_0[0x4];
    u8 unk_4;
    u8 pad_5[0x1];
    u8 unk_6;
    u8 unk_7;
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 pad_C[0xC];
};
struct fn_3_14600_lbl_3_bss_A17A0 {
    u8 pad_0[0x8];
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 pad_C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x6];
    s16 unk_1A;
    u8 unk_1C;
};
struct fn_3_14600_lbl_3_bss_A17D4 {
    struct fn_3_14600_lbl_3_bss_A17D4_0_E24 unk_0[1];
};

extern struct fn_3_14600_lbl_3_bss_A17A0 lbl_3_bss_A17A0;
extern struct fn_3_14600_lbl_3_bss_A17D4 lbl_3_bss_A17D4;

s32 fn_3_14600(void) {
    u8 v0;
    u32 v1;
    u8 v2;
    v0 = lbl_3_bss_A17A0.unk_1C;
    if (v0 == 11 || v0 == 16 || v0 == 15) {
    v1 = 0;
    return v1;
    }
    v2 = lbl_3_bss_A17A0.unk_B;
    if (lbl_3_bss_A17A0.unk_10 == (s32)lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_6 && lbl_3_bss_A17A0.unk_12 == (s32)lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_7 && lbl_3_bss_A17A0.unk_8 == lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_8 && lbl_3_bss_A17A0.unk_9 == lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_9 && lbl_3_bss_A17A0.unk_A == lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_A && lbl_3_bss_A17A0.unk_B == lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_B && v0 == lbl_3_bss_A17D4.unk_0[lbl_3_bss_A17A0.unk_1A].unk_4) {
    v2 = 1;
    return v2;
    }
    return 0;
}
/* fzgx:end fn_3_14600 */

/* fzgx:begin fn_3_146BC */
// fn_3_146BC: empty in retail (single blr).
void fn_3_146BC(void) {
}
/* fzgx:end fn_3_146BC */
