#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_win.h"

extern u32 lbl_1_bss_8FD60[2];
extern int fn_1_15BCDC(void *);
extern void fn_1_4060(void);

extern u32 lbl_1_bss_8FE80[8];

extern void *fn_1_435C(void *);
extern void fn_1_15E220(u8 *value);
extern void fn_1_3F8C(void *, void *, u8 *, s32);
extern u32 lbl_1_bss_8FEA0;
extern u8 lbl_1_bss_8FE7C;
extern u32 strlen(const char *str);
extern s32 fn_8006FC1C(const char *a, const char *b);
extern void fn_1_15E1E8(u8 *value);

/* fzgx:begin fn_1_15B970 */
typedef struct {
    u8 pad_0[0x8];
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
} WinObject;

static inline u32 swap32(u32 value) {
    u32 temp;

    temp = value;
    return __lwbrx(&temp, 0);
}

void fn_1_15B970(WinObject *obj) {
    u32 offset;
    u32 count;

    lbl_1_bss_8F8D0.unk_0 = (u32)obj;
    if (obj != 0) {
        obj->unk_8 = swap32(obj->unk_8);
        obj->unk_C = swap32(obj->unk_C);
        obj->unk_10 = swap32(obj->unk_10);
        obj->unk_14 = swap32(obj->unk_14);
        obj->unk_18 = swap32(obj->unk_18);

        count = 0;
        offset = 0;
        while (count < obj->unk_8) {
            u32 *a = (u32 *)((u8 *)obj + obj->unk_C + offset);
            u32 *b = (u32 *)((u8 *)obj + obj->unk_10 + offset);

            a[1] = swap32(a[1]);
            a[0] = swap32(a[0]);
            b[1] = swap32(b[1]);
            b[0] = swap32(b[0]);

            offset += 8;
            count++;
        }
    }
}
/* fzgx:end fn_1_15B970 */

/* fzgx:begin fn_1_15BA78 */
#include "types.h"

typedef struct {
    u8 pad_00[0x08];
    u32 count;
    u32 entries_offset;
    u32 results_offset;
} StringTable;

#pragma opt_common_subs off
char *fn_1_15BA78(char *name) {
    struct { StringTable * value; } table;
    u32 index;
    struct { u32 value; } entry_offset;
    struct { u32 value; } name_length;

    { StringTable * __reg_value_table = (*(StringTable * *)&lbl_1_bss_8F8D0); table.value = __reg_value_table; }
    if (table.value == 0) {
        return name;
    }

    name_length.value = strlen(name);
    index = 0;
    entry_offset.value = 0;
    while (index < table.value->count) {
        u8 *entry = ((((entry_offset.value)) + ((((u8 *)table.value)) + ((table.value->entries_offset)))));
        if (name_length.value == *(u32 *)entry &&
            fn_8006FC1C((char *)table.value + *(u32 *)(entry + 4), name) != 0) {
            u32 result_offset = *(u32 *)((u8 *)table.value + table.value->results_offset + index * 8 + 4);
            return (char *)table.value + result_offset;
        }
        entry_offset.value += 8;
        index++;
    }
    return name;
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_15BA78 */

/* fzgx:begin fn_1_15BE38 */
typedef struct {
    u32 count;
    void **items;
} ItemList;

u32 fn_1_15BE38(void) {
    u32 offset;
    u32 index;

    offset = 0;
    index = 0;
    while (index < (*(ItemList **)&lbl_1_bss_8FD60)->count) {
        if (fn_1_15BCDC((*(ItemList **)&lbl_1_bss_8FD60)->items[offset >> 2]) != 0) {
            return index & 0xffff;
        }
        offset += 4;
        index++;
    }
    return 0xffff;
}
/* fzgx:end fn_1_15BE38 */

/* fzgx:begin fn_1_15BEBC */
typedef struct {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
    u16 unk_4;
    u16 unk_6;
} Entry;

void fn_1_15BEBC(u16 mask, Obj_1_bss_8F8E0 *state) {
    Entry *p;
    u32 max;
    u32 sel;
    u32 cnt;
    Entry *first;
    u32 i;

    p = (Entry *)&lbl_1_bss_8F8E0;
    max = 0;
    sel = 0;
    cnt = 0;
    first = 0;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & mask) {
            if (first == 0) {
                first = p;
            }
            if (p->unk_4 == 0) {
                cnt++;
            } else {
                if (sel == 0) {
                    sel = p->unk_4;
                } else if (sel != p->unk_4) {
                    sel = 0x8000;
                    break;
                }
                if (max < p->unk_1) {
                    max = p->unk_1;
                }
            }
        }
        p++;
    }

    if (sel != 0x8000) {
        if (sel == 0) {
            state->pad_3[0] = 0;
        } else if (cnt != 0) {
            u32 cur = state->pad_3[0];
            if (cur < 10) {
                sel = 0;
            } else {
                sel = 0x8000;
            }
            if (cur == 0) {
                state->pad_3[0] = 1;
            } else {
                state->pad_3[0] = cur + ((cur - 0x78) >> 31);
            }
        } else if (max < 10) {
            state->pad_3[0] = 0;
        } else {
            if (state->unk_4 == 0x8000) {
                sel = 0x8000;
            }
            if (state->pad_3[0] != 0) {
                u32 v = state->pad_3[0];
                state->pad_3[0] = v + ((v - 0x78) >> 31);
            }
        }
    }

    if (sel != state->unk_4) {
        state->unk_6 = state->unk_4;
        state->unk_4 = sel;
        state->unk_1 = 0;
        state->unk_2 = 0;
    } else {
        u32 t = state->unk_1;
        state->unk_1 = t + 1;
        t = state->unk_2;
        state->unk_2 = t + 1;
    }
}
/* fzgx:end fn_1_15BEBC */

/* fzgx:begin fn_1_15C0AC */
typedef struct {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
    u16 unk_4;
    u16 unk_6;
} WinEntry;

#pragma opt_loop_invariants off
void fn_1_15C0AC(void) {
    u8 *in;
    struct { WinEntry * value; } out;
    u16 a;
    u16 b;
    u32 i;

    { WinEntry * __reg_value_out = (WinEntry *)&lbl_1_bss_8F8E0; out.value = __reg_value_out; }
    in = (u8 *)&lbl_1_bss_9F8;
    for (i = 0; i < 4; i++) {
        a = 0;
        b = 0;
        if (((1) & ((*(volatile u16 *)(in + 8) >> 4)))) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 1;
        }
        if ((*(volatile u16 *)(in + 8) >> 10) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 2;
        }
        if ((*(volatile u16 *)(in + 8) >> 11) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 4;
        }
        if (*(volatile u16 *)(in + 8) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 8;
        }
        if ((*(volatile u16 *)(in + 8) >> 1) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x10;
        }
        if ((*(volatile u16 *)(in + 8) >> 8) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x20;
        }
        if ((*(volatile u16 *)(in + 10) >> 7) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x100;
        }
        if ((*(volatile u16 *)(in + 10) >> 6) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x200;
        }
        if ((*(volatile u16 *)(in + 10) >> 4) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x400;
        }
        if ((*(volatile u16 *)(in + 10) >> 5) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x800;
        }
        if ((*(volatile u16 *)(in + 8) >> 6) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x40;
        }
        if ((*(volatile u16 *)(in + 8) >> 5) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            a |= 0x80;
        }
        if ((*(volatile u16 *)(in + 0) >> 4) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 1;
        }
        if ((*(volatile u16 *)(in + 0) >> 10) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 2;
        }
        if ((*(volatile u16 *)(in + 0) >> 11) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 4;
        }
        if (*(volatile u16 *)(in + 0) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 8;
        }
        if ((*(volatile u16 *)(in + 0) >> 1) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x10;
        }
        if ((*(volatile u16 *)(in + 0) >> 8) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x20;
        }
        if ((*(volatile u16 *)(in + 2) >> 7) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x100;
        }
        if ((*(volatile u16 *)(in + 2) >> 6) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x200;
        }
        if ((*(volatile u16 *)(in + 2) >> 4) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x400;
        }
        if ((*(volatile u16 *)(in + 2) >> 5) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x800;
        }
        if ((*(volatile u16 *)(in + 0) >> 6) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x40;
        }
        if ((*(volatile u16 *)(in + 0) >> 5) & 1) {  /* fzgx-allow: S2 memory-mapped register */
            b |= 0x80;
        }
        if ((a ^ b) != 0 && ((a & out.value->unk_4) == 0 || out.value->unk_1 >= 0xa)) {
            a = 0;
        }
        if (a != 0) {
            out.value->unk_0 = out.value->unk_2;
            out.value->unk_2 = 0;
            out.value->unk_1 = 0;
        } else {
            u8 t = out.value->unk_2;
            out.value->unk_2 = t + (((u32)t - 0x78) >> 31);
            if (b != 0) {
                u8 t2 = out.value->unk_1;
                out.value->unk_1 = t2 + (((u32)t2 - 0x78) >> 31);
            } else {
                out.value->unk_1 = 0;
            }
        }
        {
            u16 t3 = out.value->unk_4;
            if (t3 != b) {
                out.value->unk_6 = t3;
                out.value->unk_4 = b;
            }
        }
        out.value++;
        in += 0x14;
    } while (--i);
}
#pragma opt_loop_invariants reset
/* fzgx:end fn_1_15C0AC */

/* fzgx:begin fn_1_15C35C */
s32 fn_1_15C35C(s32 a, s32 b, s32 c, s32 d) {
    return a * b - c + d;
}
/* fzgx:end fn_1_15C35C */

/* fzgx:begin fn_1_15DFD4 noprologue */
#include "types.h"

extern f32 lbl_1_rodata_DD6C[11];
extern f32 lbl_1_rodata_DE50[39];
extern void fn_1_496FC(f32, f32);
extern void fn_1_49410(void);
extern void fn_1_49728(int);
extern void fn_1_495FC(void);
extern void fn_1_495C8(int);
extern void fn_1_15DD7C(u16);
extern void fn_1_15C6C0(u16, int);
extern void fn_1_49614(void);
extern void fn_1_A4C9C(int, u8);

extern u8 lbl_1_bss_26B18;
extern u8 lbl_1_bss_26B1A;
extern u8 lbl_1_bss_26B19;
extern u8 lbl_1_bss_26B1E;
extern u32 lbl_1_bss_3C30;

typedef struct {
    u8 pad_0[0xB];
    u8 unk_B;
    u8 pad_C[0x28];
} BgWin38;

extern BgWin38 lbl_1_bss_8FDA8[];
extern u16 lbl_1_bss_50EC[];

void fn_1_15DFD4(int index, int flags) {
    int state;

    flags &= 0xff;
    if (lbl_1_bss_26B18 & flags) {
        state = 4;
    } else if (lbl_1_bss_26B1A & flags) {
        state = 2;
    } else if (lbl_1_bss_26B19 & flags) {
        state = 1;
    } else if (lbl_1_bss_26B1E & flags) {
        state = 3;
    } else {
        return;
    }

    if (lbl_1_bss_3C30 & 0x1000) {
        lbl_1_bss_8FDA8[index].unk_B = 0;
    } else {
        lbl_1_bss_8FDA8[index].unk_B = 1;
    }

    fn_1_496FC(lbl_1_rodata_DD6C[0], lbl_1_rodata_DE50[0]);
    fn_1_49410();
    fn_1_49728(1);
    fn_1_495FC();
    fn_1_495C8(9);

    switch (state) {
    case 1: {
        u16 v = lbl_1_bss_50EC[index];
        if (lbl_1_bss_8FDA8[index].unk_B != 0) {
            fn_1_15DD7C(v);
        }
        break;
    }
    case 2: {
        u16 v = lbl_1_bss_50EC[index];
        if (lbl_1_bss_8FDA8[index].unk_B != 0) {
            fn_1_15DD7C(v);
        }
        break;
    }
    case 3:
        fn_1_15C6C0(lbl_1_bss_50EC[index], index);
        break;
    case 4: {
        u16 v = lbl_1_bss_50EC[index];
        if (lbl_1_bss_8FDA8[index].unk_B != 0) {
            fn_1_15DD7C(v);
        }
        break;
    }
    }

    fn_1_49614();
    fn_1_49728(0);
    fn_1_A4C9C(index, state);
}
/* fzgx:end fn_1_15DFD4 */

/* fzgx:begin fn_1_15E1D0 noprologue */
#include "types.h"

struct fn_1_15E1D0_lbl_1_bss_8FDA8_0_E52 {
    u8 pad_0[0x30];
    f32 unk_30;
};
struct fn_1_15E1D0_lbl_1_bss_8FDA8 {
    struct fn_1_15E1D0_lbl_1_bss_8FDA8_0_E52 unk_0[1];
};

extern struct fn_1_15E1D0_lbl_1_bss_8FDA8 lbl_1_bss_8FDA8;

f32 fn_1_15E1D0(u32 arg0) {
    return lbl_1_bss_8FDA8.unk_0[arg0].unk_30;
}
/* fzgx:end fn_1_15E1D0 */

/* fzgx:begin fn_1_15E1E8 */
void fn_1_15E1E8(u8 *value) {
    u8 state = *value;

    if (state == 0) {
        fn_1_4060();
    } else {
        *value = state - 1;
    }
}
/* fzgx:end fn_1_15E1E8 */

/* fzgx:begin fn_1_15E220 */
void fn_1_15E220(u8 *value) {
    u8 state = *value;

    if (state == 0) {
        fn_1_4060();
    } else if (state != 0xff) {
        *value = state - 1;
    }
}
/* fzgx:end fn_1_15E220 */

/* fzgx:begin fn_1_15E260 */
// Marks the indexed background-window entry as active.
void fn_1_15E260(s32 index) {
    (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 4;
}
/* fzgx:end fn_1_15E260 */

/* fzgx:begin fn_1_15E330 */
extern void *fn_1_435C(void *arg);
extern void fn_1_3F8C(void *arg0, void *arg1, u8 *arg2, s32 arg3);

void fn_1_15E330(s32 index, u32 value, void *arg) {
    if (lbl_1_bss_3C30.unk_13F4 - (&lbl_1_bss_8FDA8.unk_8)[index * 0x34] < 4) {
        void *result;

        (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 8;
        (&lbl_1_bss_8FDA8.unk_C)[index * 13] = value;
        result = fn_1_435C(arg);
        fn_1_3F8C(lbl_1_data_4C980, fn_1_15E1E8,
                  &(&lbl_1_bss_8FDA8.unk_9)[index * 0x34], 13);
        (&lbl_1_bss_8FDA8.unk_9)[index * 0x34] = 0x3c;
        fn_1_435C(result);
    }
}
/* fzgx:end fn_1_15E330 */

/* fzgx:begin fn_1_15E3E0 */
// Records the selected window index and updates its value when the index is valid.
void fn_1_15E3E0(s32 index, u32 value) {
    s32 slot = (lbl_1_bss_3C30.unk_13F4 - 1) % 4;

    lbl_1_bss_8FE80[slot] = index;
    if (index != -1) {
        (&lbl_1_bss_8FDA8.unk_C)[index * 13] = value;
    }
}
/* fzgx:end fn_1_15E3E0 */

/* fzgx:begin fn_1_15E434 */
void fn_1_15E434(u32 value) {
    lbl_1_bss_8FE7C = 1;
    lbl_1_bss_8FEA0 = value;
}
/* fzgx:end fn_1_15E434 */

/* fzgx:begin fn_1_15E540 */
// Initializes a background-window entry once, then marks it ready for reuse.
void fn_1_15E540(s32 index, void *arg) {
    if (!((&lbl_1_bss_8FDA8.unk_0)[index * 0x34] & 1)) {
        void *value = fn_1_435C(arg);

        fn_1_3F8C(lbl_1_data_4C994, fn_1_15E220,
                  &lbl_1_bss_8FDA8.unk_1 + index * 0x34, 13);
        (&lbl_1_bss_8FDA8.unk_1)[index * 0x34] = 0xff;
        fn_1_435C(value);
        (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 1;
    }
}
/* fzgx:end fn_1_15E540 */

/* fzgx:begin fn_1_15E5E4 */
extern void *fn_1_435C(void *);
extern void fn_1_15E220(u8 *value);
extern void fn_1_3F8C(void *, void *, u8 *, s32);

// Initializes a background-window entry once, then marks it ready for reuse.
void fn_1_15E5E4(s32 index, void *arg) {
    Obj_1_bss_8FDA8 *obj;
    s32 offset = index * 0x34;

    obj = (Obj_1_bss_8FDA8 *)((u8 *)&lbl_1_bss_8FDA8 + offset);

    if (!(obj->unk_0 & 2)) {
        void *value = fn_1_435C(arg);

        fn_1_3F8C(lbl_1_data_4C994, fn_1_15E220, &obj->unk_2, 13);
        (&lbl_1_bss_8FDA8.unk_2)[offset] = 0xff;
        fn_1_435C(value);
        obj->unk_0 |= 2;
    }
}
/* fzgx:end fn_1_15E5E4 */

/* fzgx:begin fn_1_15E688 */
extern void *fn_1_435C(void *arg);
extern void fn_1_3F8C(void *arg0, void *arg1, u8 *arg2, s32 arg3);

void fn_1_15E688(s32 index, u32 value, u8 state, void *arg) {
    void *obj;
    Obj_1_bss_8FDA8 *entry;

    obj = fn_1_435C(arg);
    fn_1_3F8C(lbl_1_data_4C980, fn_1_15E1E8,
              &(&lbl_1_bss_8FDA8.unk_0)[index * 0x34] + 3, 13);
    (&lbl_1_bss_8FDA8.unk_0)[index * 0x34 + 3] = 0x5a;
    fn_1_435C(obj);
    entry = (Obj_1_bss_8FDA8 *)((u8 *)&lbl_1_bss_8FDA8 + index * 0x34);
    ((u32 *)&entry->unk_10)[(state - 1) % 8] = value;
    entry->unk_4 = value;
    entry->unk_8 = state;
}
/* fzgx:end fn_1_15E688 */

/* fzgx:begin fn_1_15E764 */
extern void *fn_1_435C(void *);
extern void fn_1_15E220(u8 *value);
extern void fn_1_3F8C(void *, void *, u8 *, s32);

// Initializes the entry's 13-byte block, then marks it ready for reuse.
void fn_1_15E764(s32 index, void *arg) {
    void *value = fn_1_435C(arg);

    fn_1_3F8C(lbl_1_data_4C994, fn_1_15E220,
              &lbl_1_bss_8FDA8.unk_A + index * 0x34, 13);
    (&lbl_1_bss_8FDA8.unk_A)[index * 0x34] = 0xff;
    fn_1_435C(value);
    (&lbl_1_bss_8FDA8.unk_A)[index * 0x34] = 0xff;
}
/* fzgx:end fn_1_15E764 */

/* fzgx:begin fn_1_15F618 */
void *fn_1_15F618(s32 index) {
    return (u8 *)&lbl_1_bss_8FDA8 + index * 0x34;
}
/* fzgx:end fn_1_15F618 */
