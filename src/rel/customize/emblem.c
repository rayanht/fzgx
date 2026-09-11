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

/* fzgx:begin fn_3_13EA4 noprologue */
#include "types.h"

extern u8 lbl_3_data_3574[60];
extern void *lbl_801A6410;
extern s32 fn_1_45730(void *, void *);
extern u32 fn_1_45B2C(void *);
extern s32 fn_1_F7BE4(u32);
extern void *fn_1_45D0(void *, u32, void *, u32);
extern void fn_80008BEC(void *, u32, u32);
extern void fn_1_458A0(void *, void *, u32, u32);
extern void fn_80008BA8(void *, void *, u32);
extern void fn_1_45850(void *);

u32 fn_3_13EA4(void *arg, u32 *output) {
    u8 header[0x60];
    u8 buffer[0x2000] __attribute__((aligned(32)));
    u32 *out;
    u8 i;
    u32 count;
    u32 limit;
    u32 size;

    out = output;
    count = 0;
    if (fn_1_45730(arg, header) != 0) {
        size = fn_1_45B2C(header);
        limit = size >> 13;
        if (limit >= 0x2c) {
            limit = 0x2c;
        }
        if (size != 0) {
            for (i = 0; i < limit; i++) {
                if ((i == limit - 3 && fn_1_F7BE4(0x15) != 0) ||
                    (i == limit - 2 && fn_1_F7BE4(0x21) != 0) ||
                    (i == limit - 1 && fn_1_F7BE4(0x21) != 0) ||
                    (fn_1_F7BE4(i) != 0)) {
                    out[(u8)count] = (u32)fn_1_45D0(lbl_801A6410, 0x2000,
                                                   lbl_3_data_3574, 0x27b);
                    fn_80008BEC((void *)out[(u8)count], 0, 0x2000);
                    fn_1_458A0(header, buffer, 0x2000,
                               ((i << 13) + 0x1f) & ~0x1f);
                    fn_80008BA8((void *)out[(u8)count], buffer, 0x2000);
                    count++;
                }
            }
        }
        fn_1_45850(header);
    }
    return (u8)count;
}
/* fzgx:end fn_3_13EA4 */

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

/* fzgx:begin fn_3_14080 */
extern u8 lbl_3_data_3574[60];
extern u32 lbl_801A6410;

typedef struct EmblemEntry {
    u8 unk00[6];
    u8 unk06;
    u8 unk07;
    void *unk08;
    u32 unk0c;
    u32 unk10;
    void *unk14;
} EmblemEntry;

typedef struct EmblemState {
    u8 unk00[8];
    void **allocs;
    void **sizes;
    u8 unk14[0x5c];
    EmblemEntry entries[0x80];
} EmblemState;

extern EmblemState lbl_3_bss_A1768;
extern void *fn_1_45D0(u32, u32, void *, u32);
extern void fn_80008BEC(void *, u32, u32);
extern void *fn_3_17820(void);

#pragma opt_propagation off
void fn_3_14080(void) {
    u8 i;
    EmblemState *state;
    EmblemEntry *entry;

    state = &lbl_3_bss_A1768;
    i = 0;
    state->allocs = fn_1_45D0(lbl_801A6410, 0x200, lbl_3_data_3574, 0x2d1);
    state->sizes = fn_1_45D0(lbl_801A6410, 0x200, lbl_3_data_3574, 0x2d2);
    for (; i < 0x80; i++) {
        state->allocs[i] = fn_1_45D0(lbl_801A6410, 0x2000, lbl_3_data_3574, 0x2d6);
        state->sizes[i] = 0;
        fn_80008BEC(state->allocs[i], 0, 0x2000);
        entry = state->entries;
        entry += i;
        fn_80008BEC(entry, 0, 0x18);
        entry->unk14 = state->allocs[i];
        entry->unk06 = 0x1f;
        entry->unk07 = 0x1f;
        entry->unk08 = fn_3_17820();
        entry->unk10 = 0;
    }
}
#pragma opt_propagation reset
/* fzgx:end fn_3_14080 */

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

/* fzgx:begin fn_3_146C0 */
extern u16 lbl_3_bss_A23D8;
extern u16 lbl_3_bss_A23DA[3];
extern void fn_3_14BBC(void *, s16, s16, s16, u32 *);

void fn_3_146C0(void *arg0, s16 x, s16 y, s16 delta, u32 *arg4) {
    s32 offset;
    u32 value;
    s16 adjusted_delta;

    if (x <= 0) {
        adjusted_delta = delta;
        if (x + adjusted_delta <= 0) {
            return;
        }
        offset = x - 1;
        offset = ((offset >> 31) ^ offset) - (offset >> 31);
        delta = adjusted_delta - offset;
        x = 1;
    } else {
        if (x + delta >= lbl_3_bss_A23D8 - 1) {
            delta = lbl_3_bss_A23D8 - 1 - x;
        }
    }

    if (y <= 0 || y >= lbl_3_bss_A23DA[0] - 1) {
        return;
    }
    value = *arg4;
    fn_3_14BBC(arg0, x, y, delta, &value);
}
/* fzgx:end fn_3_146C0 */

/* fzgx:begin fn_3_15240 */
extern void fn_3_14E18(void *, s16, void *, s16, void *);

void fn_3_15240(void *arg0, s16 arg1, void *arg2, u16 arg3, s16 arg4, void *arg5) {
    s32 i;
    s32 j;
    s32 n;
    s16 k;

    i = arg4;
    j = arg1;
    n = arg3;
    k = 0;
    while (k < n) {
        fn_3_14E18(arg0, j, arg2, i, arg5);
        i++;
        j++;
        k++;
    }
}
/* fzgx:end fn_3_15240 */
