#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/replay.h"

extern u32 OSGetTick(void);

/* fzgx:begin fn_1_F2780 pool noprologue */
#include "types.h"

#define lbl_1_bss_7EFD0 fzgx_header_lbl_1_bss_7EFD0
#define lbl_1_bss_7EFD4 fzgx_header_lbl_1_bss_7EFD4
#define lbl_1_bss_7EFD8 fzgx_header_lbl_1_bss_7EFD8
#define lbl_1_bss_7F01C fzgx_header_lbl_1_bss_7F01C
#undef lbl_1_bss_7EFD0
#undef lbl_1_bss_7EFD4
#undef lbl_1_bss_7EFD8
#undef lbl_1_bss_7F01C

typedef struct State {
    u8 pad0[0x19];
    u8 byte19;
    u8 byte1a;
    u8 byte1b;
    u8 byte1c;
    u8 byte1d;
    u8 byte1e;
    u8 byte1f;
    u8 byte20;
    u8 byte21;
    u8 byte22;
    u8 byte23;
    u8 pad24[0x1c];
    void *object;
} State;

typedef struct Global {
    u8 pad0[4];
    u8 byte4;
    u8 pad5[3];
    State state;
} Global;

typedef struct Object {
    u8 pad0[0xa0];
    u16 halfa0;
} Object;

extern u32 lbl_801A6410;
extern char lbl_1_data_3E8C8[9];
extern Object *fn_1_4630(u32 arg0, u32 arg1, char *arg2, u32 arg3);

typedef struct lbl_1_bss_7F01C_t {
    u8 fzgx_byte_4C;
    u8 pad_1[0x1];
} lbl_1_bss_7F01C_t;

/* file-scope objects of the retail TU, in retail order: MWCC addresses them off one section base */
u16 lbl_1_bss_7EFD0;
u16 lbl_1_bss_7EFD0_gap_7EFD2;
u8 lbl_1_bss_7EFD4;
u8 lbl_1_bss_7EFD0_gap_7EFD5;
u16 lbl_1_bss_7EFD0_gap_7EFD5_fill_7EFD6;
State lbl_1_bss_7EFD8;
lbl_1_bss_7F01C_t lbl_1_bss_7F01C;

#pragma section code_type ".fzgxpool"
static void fzgx_bss_layout(void) {
    volatile u8 s;  /* fzgx-allow: S2 layout primer sink: MWCC emits .bss objects in first-access order */
    s = *(u8 *)&lbl_1_bss_7EFD0;
    s = *(u8 *)&lbl_1_bss_7EFD0_gap_7EFD2;
    s = *(u8 *)&lbl_1_bss_7EFD4;
    s = *(u8 *)&lbl_1_bss_7EFD0_gap_7EFD5;
    s = *(u8 *)&lbl_1_bss_7EFD0_gap_7EFD5_fill_7EFD6;
    s = *(u8 *)&lbl_1_bss_7EFD8;
    s = *(u8 *)&lbl_1_bss_7F01C;
}
#pragma section code_type ".text"

void fn_1_F2780(void) {
    Object *object;
    State *state;

    
    state = &lbl_1_bss_7EFD8;
    object = fn_1_4630(lbl_801A6410, (1 << 16) + 0x14c, lbl_1_data_3E8C8, 0x75);
    state->object = object;
    *(u16 *)((u8 *)&lbl_1_bss_7F01C.fzgx_byte_4C) = 0;
    object->halfa0 = 0;
    lbl_1_bss_7EFD4 = 0x29;
    state->byte19 = 0;
    state->byte1a = 1;
    state->byte1c = 0;
    state->byte20 = 0;
    state->byte1d = 0;
    state->byte21 = 0;
    state->byte1e = 0;
    state->byte22 = 0;
    state->byte1f = 0;
    state->byte23 = 0;
    *(u32 *)((u8 *)state + 0xc) = 0;
    state->byte1b = 0;
}
/* fzgx:end fn_1_F2780 */

/* fzgx:begin fn_1_F2CD8 */
void fn_1_F2CD8(u8 *value, u8 **cursor, u32 index) {
    s32 target;
    Obj_1_bss_7EFD8_At40 *entries_end;
    u8 *entry;

    // Move backward through replay entries until the requested flag or boundary is found.
    target = (index | 4) & 0xff;
    entries_end = lbl_1_bss_7EFD8.unk_40 + 1;
    *cursor = value;

    while (*cursor >= (u8 *)entries_end) {
        entry = *cursor;
        if ((entry[0] & 7) == target) {
            break;
        }
        *cursor -= 7;
    }

    if (*cursor < (u8 *)entries_end) {
        *cursor = value;
    }
}
/* fzgx:end fn_1_F2CD8 */

/* fzgx:begin fn_1_F2D30 */
u8 fn_1_F2D30(u8 *value, u8 **cursor, u32 index) {
    u8 target;
    u32 step;
    Obj_1_bss_7EFD8_At40 *entries_end;
    u8 raw;
    u8 flags;

    target = (index | 4) & 0xff;
    entries_end = lbl_1_bss_7EFD8.unk_40 + 1;

    if (lbl_1_bss_7EFD8.unk_1A != 0) {
        lbl_1_bss_7EFD8.unk_1A = 0;
        step = 0;
    } else {
        step = 1;
    }
    *cursor = value + step * 7;

    while (*cursor < (u8 *)entries_end + lbl_1_bss_7EFD8.unk_14 * 7) {
        raw = (*cursor)[0];
        flags = raw & 7;
        if ((raw & 4) == 0 || flags == target) {
            break;
        }
        *cursor += 7;
    }

    return *cursor != (u8 *)entries_end + lbl_1_bss_7EFD8.unk_14 * 7;
}
/* fzgx:end fn_1_F2D30 */

/* fzgx:begin fn_1_F2EB8 */
#include "types.h"

struct fn_1_F2EB8_lbl_1_bss_7EFD4 {
    s8 unk_0;
};



void fn_1_F2EB8(void) {
    u8 v0;
    v0 = (*(struct fn_1_F2EB8_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0;
    if ((v0 & 0x1) == 0) { return; }
    (*(struct fn_1_F2EB8_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0 = (v0 & -41);
}
/* fzgx:end fn_1_F2EB8 */

/* fzgx:begin fn_1_F2EDC */
#include "types.h"

struct fn_1_F2EDC_lbl_1_bss_7EFD4 {
    s8 unk_0;
};



void fn_1_F2EDC(void) {
    u8 v0;
    v0 = (*(struct fn_1_F2EDC_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0;
    if ((v0 & 0x1) == 0) { return; }
    (*(struct fn_1_F2EDC_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0 = (v0 | 8);
}
/* fzgx:end fn_1_F2EDC */

/* fzgx:begin fn_1_F2EFC */
// Clears the active replay flag and marks the replay entry as ready.
void fn_1_F2EFC(void) {
    u8 flags = lbl_1_bss_7EFD4;

    if ((flags & 1) == 0) {
        return;
    }
    if (((flags >> 5) & 1) != 0) {
        return;
    }

    lbl_1_bss_7EFD4 = flags & ~8;
    lbl_1_bss_7EFD8.unk_19 = 1;
}
/* fzgx:end fn_1_F2EFC */

/* fzgx:begin fn_1_F2F34 */
#include "types.h"



struct fn_1_F2F34_lbl_1_bss_7EFD4 {
    u8 unk_0;
};

u32 fn_1_F2F34(void) {
    u8 v0;
    v0 = (*(struct fn_1_F2F34_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0;
    if (((*(struct fn_1_F2F34_lbl_1_bss_7EFD4 *)&lbl_1_bss_7EFD4).unk_0 & 0x1) == 0) {
    v0 = 0;
    return v0;
    }
    v0 = ((v0 >> 2) & 0x1);
    return v0;
}
/* fzgx:end fn_1_F2F34 */

/* fzgx:begin fn_1_F2F58 */
u32 fn_1_F2F58(void) {
    u8 flags = lbl_1_bss_7EFD4;

    if ((flags & 1) == 0) {
        return 0;
    }
    return (u32)__cntlzw((u32)((flags >> 2) & 1)) >> 5;
}
/* fzgx:end fn_1_F2F58 */

/* fzgx:begin fn_1_F37F4 */
#include "types.h"





extern s8 fn_1_86678(s32 index);
extern u32 fn_1_864E8(s32 index);
extern u32 fn_1_86810(s32 index);
extern void fn_1_F3574(void *state, u8 index, u8 value, s32 kind, u32 result);

void fn_1_F37F4(void) {
    s32 index;

    if (*(u16 *)((u8 *)(*(u32 (*)[17])&lbl_1_bss_7EFD8)[16] + 0xfef0) == 0) {
        return;
    }

    for (index = 0; index < 4; index++) {
        if (index < (*(u8 (*)[5308])&lbl_1_bss_3C30)[9] &&
            fn_1_86678(index) != -1 &&
            ((u8 *)(*(u32 (*)[17])&lbl_1_bss_7EFD8))[index + 0x24] == 0 &&
            (fn_1_864E8(index) & 0x10000) != 0) {
            fn_1_F3574((*(u32 (*)[17])&lbl_1_bss_7EFD8), (u8)index, (u8)index, 6, fn_1_86810(index));
        }
    }
}
/* fzgx:end fn_1_F37F4 */

/* fzgx:begin fn_1_F3AB0 */
extern s32 fn_1_F45CC(u16 value, void *out);
extern void fn_1_862D4(s32 value, f32 *out);

typedef struct {
    u16 unk_0;
    u8 pad_2[0xA];
    f32 unk_C;
    f32 unk_10;
    f32 unk_14;
} ReplayEntry_F3AB0;

void fn_1_F3AB0(Obj_1_bss_7EFD8 *obj) {
    f32 values[3];
    // The retail routine reserves this volatile scratch area for replay records.
    volatile u8 data[0xf80];
    ReplayEntry_F3AB0 *entry;
    s32 count;
    s32 i;
    u8 flags;
    s32 ok;

    flags = lbl_1_bss_7EFD4;
    if ((flags & 1) == 0) {
        ok = 0;
    } else if (((flags >> 2) & 1) == 0) {
        ok = 0;
    } else if (((flags >> 3) & 1) != 0) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }

    obj->unk_4++;
    count = fn_1_F45CC((u16)obj->unk_4, (void *)data);
    if (count <= 0) {
        return;
    }

    fn_1_862D4(0, values);
    entry = (ReplayEntry_F3AB0 *)data;
    for (i = 0; i < count; i++) {
        if (obj->unk_4 == entry->unk_0 &&
            (values[0] != entry->unk_C ||
             values[1] != entry->unk_10 ||
             values[2] != entry->unk_14)) {
            lbl_1_bss_7EFD8.unk_1B = 1;
        }
        entry = (ReplayEntry_F3AB0 *)((u8 *)entry + 0x84);
    }
}
/* fzgx:end fn_1_F3AB0 */

/* fzgx:begin fn_1_F43F0 */
void fn_1_F43F0(u8 *bits, u32 *position, u32 mask, u32 count, u32 limit) {
    u32 value;
    u32 index;
    u32 bit;

    while (count != 0) {
        value = *position;
        index = value >> 3;
        if (index >= limit) {
            return;
        }
        bit = value & 7;
        if ((mask & (1 << (count - 1))) != 0) {
            bits[index] |= 1 << bit;
        }
        value = *position;
        count--;
        *position = value + 1;
    }
}
/* fzgx:end fn_1_F43F0 */

/* fzgx:begin fn_1_F444C */
extern void fn_80008BA8(u32 *, f32 *, int, f32);

void fn_1_F444C(u8 *out, u32 *pos, u32 limit, f32 value) {
    u32 mask;
    f32 input;
    u32 v;
    u32 bit;
    u32 index;
    u32 m;
    u32 count;

    input = value;
    fn_80008BA8(&mask, &input, 4, value);
    m = mask;
    count = 32;
    while (count != 0) {
        v = *pos;
        index = v >> 3;
        if (index >= limit) {
            return;
        }
        bit = v & 7;
        if ((m & (1u << (count - 1))) != 0) {
            out[index] |= 1u << bit;
        }
        v = *pos;
        count--;
        *pos = v + 1;
    }
}
/* fzgx:end fn_1_F444C */

/* fzgx:begin fn_1_F453C */
struct fn_1_F453C_Arg0 {
    u8 unk_0[1];
};
struct fn_1_F453C_Arg1 {
    u32 unk_0;
};

u32 fn_1_F453C(struct fn_1_F453C_Arg0 *arg0, struct fn_1_F453C_Arg1 *arg1, u32 arg2) {
    u32 v0;
    u32 v1;
    s32 v2;
    u32 v3;

    v1 = arg2;
    v2 = 0;
    while (v1 != 0) {
        v3 = arg1->unk_0;
        if (((1 << (v3 & 0x7)) & arg0->unk_0[((u32)v3 >> 3)]) != 0) {
            v2 = v2 | (1 << (v1 - 1));
        }
        v1--;
        arg1->unk_0++;
    }
    return v2;
}
/* fzgx:end fn_1_F453C */

/* fzgx:begin fn_1_F4594 */
u32 fn_1_F4594(void) {
    return lbl_1_bss_7EFD8.unk_4;
}
/* fzgx:end fn_1_F4594 */

/* fzgx:begin fn_1_F45A4 */
u32 fn_1_F45A4(void) {
    return lbl_1_bss_7EFD8.unk_8;
}
/* fzgx:end fn_1_F45A4 */

/* fzgx:begin fn_1_F45B4 */
u32 fn_1_F45B4(void) {
    return ((__cntlzw(((lbl_1_bss_7EFD4 >> 4) & 0x1)) >> 5) & 0xFF);
}
/* fzgx:end fn_1_F45B4 */

/* fzgx:begin fn_1_F45CC */
typedef struct { u8 raw[0x80]; } ReplayEntry;
typedef struct { u8 raw[0x84]; } ReplayOutput;
typedef struct { u32 w[3]; } CopyChunk;

s32 fn_1_F45CC(u32 key, ReplayOutput *out) {
    s32 out_count;
    Obj_1_bss_7EFD8 *global;
    ReplayOutput *dst;
    s32 i;
    ReplayEntry *entry;

    key &= 0xffff;
    if (key > 0x7fff) {
        return 0;
    }
    out_count = 0;
    global = &lbl_1_bss_7EFD8;
    i = 0;
    entry = (ReplayEntry *)((u8 *)global->unk_40 + 0xff4c);
    while (i < (s32)*(u16 *)((u8 *)global->unk_40 + 0xfef0)) {
        u16 first;
        u16 last;

        first = (*(u16 *)(entry->raw + 0) >> 1) & 0x7fff;
        if (key >= first) {
            last = (*(u16 *)(entry->raw + 4) >> 1) & 0x7fff;
            if (key <= last) {
                if (out_count < 0x1e) {
                } else {
                    out_count = 0x1d;
                }
                dst = (ReplayOutput *)((u8 *)out + out_count * 0x84);
                out_count++;
                *(u16 *)(dst->raw + 0) = first;
                *(u16 *)(dst->raw + 2) = (*(u16 *)(entry->raw + 4) >> 1) & 0x7fff;
                dst->raw[4] = (*(u32 *)(entry->raw + 0) >> 14) & 7;
                dst->raw[5] = (entry->raw[2] >> 1) & 0x1f;
                dst->raw[6] = (*(u32 *)(entry->raw + 4) >> 12) & 0x1f;
                dst->raw[7] = (*(u16 *)(entry->raw + 6) >> 7) & 0x1f;
                dst->raw[8] = (entry->raw[7] >> 2) & 0x1f;
                *(CopyChunk *)(dst->raw + 0x0c) = *(CopyChunk *)(entry->raw + 0x08);
                *(CopyChunk *)(dst->raw + 0x3c) = *(CopyChunk *)(entry->raw + 0x38);
                *(CopyChunk *)(dst->raw + 0x18) = *(CopyChunk *)(entry->raw + 0x14);
                *(CopyChunk *)(dst->raw + 0x48) = *(CopyChunk *)(entry->raw + 0x44);
                *(CopyChunk *)(dst->raw + 0x24) = *(CopyChunk *)(entry->raw + 0x20);
                *(CopyChunk *)(dst->raw + 0x54) = *(CopyChunk *)(entry->raw + 0x50);
                *(CopyChunk *)(dst->raw + 0x30) = *(CopyChunk *)(entry->raw + 0x2c);
                *(CopyChunk *)(dst->raw + 0x60) = *(CopyChunk *)(entry->raw + 0x5c);
                *(CopyChunk *)(dst->raw + 0x6c) = *(CopyChunk *)(entry->raw + 0x68);
                *(CopyChunk *)(dst->raw + 0x78) = *(CopyChunk *)(entry->raw + 0x74);
            }
        }
        i++;
        entry++;
    }
    return out_count;
}
/* fzgx:end fn_1_F45CC */

/* fzgx:begin fn_1_F4794 */
void fn_1_F4794(u16 value) {
    lbl_1_bss_7F01C = value;
}
/* fzgx:end fn_1_F4794 */

/* fzgx:begin fn_1_F47A0 */
void fn_1_F47A0(u32 value) {
    lbl_1_bss_7F020 = value;
}
/* fzgx:end fn_1_F47A0 */

/* fzgx:begin fn_1_F47AC */
u32 fn_1_F47AC(void) {
    u32 tick;
    u8 flags;

    tick = OSGetTick();
    flags = lbl_1_bss_7EFD4;
    if ((flags & 1) == 0) {
        return tick;
    }
    if (((flags >> 1) & 1) != 0) {
        lbl_1_bss_7F020 = tick;
    } else if (((flags >> 2) & 1) != 0) {
        tick = lbl_1_bss_7F020;
    }
    return tick;
}
/* fzgx:end fn_1_F47AC */

/* fzgx:begin fn_1_F4E3C */
extern const f32 lbl_1_rodata_6D6C;
extern const f32 lbl_1_rodata_6D68;

f32 fn_1_F4E3C(s32 count, f32 *x, f32 *z, f32 *y, f32 value) {
    s32 lo;
    s32 hi;
    s32 mid;
    f32 x0;
    f32 y0;
    f32 y1;
    f32 x1;
    f32 z0;
    f32 z1;
    f32 t;
    f32 two;
    f32 dy;
    f32 dx;
    f32 thr;
    f32 tdy;
    f32 dz;
    f32 u;
    f32 s;
    f32 v;
    f32 w;
    f32 s2;
    f32 w2;
    f32 r;
    f32 sum;

    hi = count - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (x[mid] < value) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo > 0) {
        lo--;
    }

    x0 = x[lo];
    y0 = y[lo];
    y1 = y[lo + 1];
    x1 = x[lo + 1];
    z0 = z[lo];
    z1 = z[lo + 1];

    t = value - x0;
    two = lbl_1_rodata_6D6C * y0;
    dy = y1 - y0;
    dx = x1 - x0;
    tdy = t * dy;
    thr = lbl_1_rodata_6D68 * y0;
    dz = z1 - z0;
    u = tdy / dx;
    s = two + y1;
    v = dz / dx;
    w = thr + u;
    s2 = dx * s;
    w2 = t * w;
    r = v - s2;
    sum = w2 + r;
    sum = t * sum;
    return z0 + sum;
}
/* fzgx:end fn_1_F4E3C */
