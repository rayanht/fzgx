#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/replay.h"

extern u32 OSGetTick(void);

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

/* fzgx:begin fn_1_F2EB8 noprologue */
#include "types.h"

struct fn_1_F2EB8_lbl_1_bss_7EFD4 {
    s8 unk_0;
};

extern struct fn_1_F2EB8_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

void fn_1_F2EB8(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((v0 & 0x1) == 0) { return; }
    lbl_1_bss_7EFD4.unk_0 = (v0 & -41);
}
/* fzgx:end fn_1_F2EB8 */

/* fzgx:begin fn_1_F2EDC noprologue */
#include "types.h"

struct fn_1_F2EDC_lbl_1_bss_7EFD4 {
    s8 unk_0;
};

extern struct fn_1_F2EDC_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

void fn_1_F2EDC(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((v0 & 0x1) == 0) { return; }
    lbl_1_bss_7EFD4.unk_0 = (v0 | 8);
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

/* fzgx:begin fn_1_F2F34 noprologue */
#include "types.h"

extern struct fn_1_F2F34_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

struct fn_1_F2F34_lbl_1_bss_7EFD4 {
    u8 unk_0;
};

u32 fn_1_F2F34(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((lbl_1_bss_7EFD4.unk_0 & 0x1) == 0) {
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

/* fzgx:begin fn_1_F37F4 noprologue */
#include "types.h"

extern u32 lbl_1_bss_7EFD8[17];
extern u8 lbl_1_bss_3C30[5308];

extern s8 fn_1_86678(s32 index);
extern u32 fn_1_864E8(s32 index);
extern u32 fn_1_86810(s32 index);
extern void fn_1_F3574(void *state, u8 index, u8 value, s32 kind, u32 result);

void fn_1_F37F4(void) {
    s32 index;

    if (*(u16 *)((u8 *)lbl_1_bss_7EFD8[16] + 0xfef0) == 0) {
        return;
    }

    for (index = 0; index < 4; index++) {
        if (index < lbl_1_bss_3C30[9] &&
            fn_1_86678(index) != -1 &&
            ((u8 *)lbl_1_bss_7EFD8)[index + 0x24] == 0 &&
            (fn_1_864E8(index) & 0x10000) != 0) {
            fn_1_F3574(lbl_1_bss_7EFD8, (u8)index, (u8)index, 6, fn_1_86810(index));
        }
    }
}
/* fzgx:end fn_1_F37F4 */

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
