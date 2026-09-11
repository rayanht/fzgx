#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_aur.h"

extern int fn_8003BE1C(void *arg0, void *arg1);
extern int fn_8003C1A4(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4);
extern void fn_8003CE74(void *arg0, void *arg1, int arg2);
extern void fn_8003CBB0(void *arg0, void *arg1, void *arg2, void *arg3);
extern void fn_8003C6D0(void *arg0, void *arg1, void *arg2, void *arg3);
extern u16 lbl_1_bss_8ED8C;
extern u16 lbl_1_bss_8ED8E;
extern void fn_1_151C9C(void);
extern void fn_80074A7C(void (*callback)(void));
extern void fn_1_153AF8(u32 *entries);
extern void fn_1_153D48(void *background);
extern void fn_1_9A508(void);
extern int fn_1_58C4(void);
extern void fn_1_5948(int);
extern void fn_1_627C(int);
extern void fn_1_9D260(void);
extern void fn_1_9AD54(void);
extern void fn_1_153D74(void *);
extern void fn_1_153B24(void *);
extern void fn_1_153C60(Obj_1_data_2A7E0_At3C *value);
extern void fn_1_1540B0(Obj_1_data_2A7E0_At3C *value);
extern void fn_1_9AD88(void);
extern void fn_80008BEC(void *arg0, u32 arg1, u32 arg2);

extern void fn_1_153AF8(u32 *entries);
extern void fn_1_153D48(void *background);
extern void fn_1_9A508(void);

/* fzgx:begin fn_1_151AF0 */
int fn_1_151AF0(void *arg0, int mode, void *arg2, void *arg3, void *arg4, void *arg5) {
    u8 local_8[4];
    u8 local_c[8];
    u8 local_14[12];

    if (fn_8003BE1C(arg0, local_c) == 0) {
        return 0;
    }
    if (fn_8003C1A4(local_14, local_8, arg5, arg0, local_c) == 0) {
        return 0;
    }
    switch (mode) {
    case 0:
        fn_8003CE74(local_14, arg2, 0xff);
        break;
    case 1:
        fn_8003CBB0(local_14, arg2, arg3, arg4);
        break;
    case 2:
        fn_8003C6D0(local_14, arg2, arg3, arg4);
        break;
    }
    return 1;
}
/* fzgx:end fn_1_151AF0 */

/* fzgx:begin fn_1_151BDC */
void fn_1_151BDC(u32 value) {
    lbl_1_bss_8ED88 = value;
}
/* fzgx:end fn_1_151BDC */

/* fzgx:begin fn_1_151BE8 */
struct fn_1_151BE8_Copy1200 { u32 a[75][4]; };

extern u8 lbl_1_rodata_D048[1200];

u32 fn_1_151BE8(s16 arg0, s16 arg1) {
    struct fn_1_151BE8_Copy1200 loc_8;
    loc_8 = *(struct fn_1_151BE8_Copy1200 *)&lbl_1_rodata_D048;
    {
        s16 row = arg0;
        s16 col = arg1;
        return loc_8.a[row][col];
    }
}
/* fzgx:end fn_1_151BE8 */

/* fzgx:begin fn_1_151C3C */
void fn_1_151C3C(u16 value1, u16 value2) {
    lbl_1_bss_8ED8C = value1;
    lbl_1_bss_8ED8E = value2;
    fn_80074A7C(fn_1_151C9C);
}
/* fzgx:end fn_1_151C3C */

/* fzgx:begin fn_1_151C78 */
void fn_1_151C78(void) {
    fn_80074A7C(0);
}
/* fzgx:end fn_1_151C78 */

/* fzgx:begin fn_1_151C9C noprologue */
#include "types.h"

struct fn_1_151C9C_lbl_1_bss_8ED88 {
    u32 unk_0;
    s16 unk_4;
    s16 unk_6;
};
struct fn_1_151C9C_lbl_1_rodata_D500 {
    f64 unk_0;
};
struct fn_1_151C9C_lbl_1_rodata_D4F8 {
    f32 unk_0;
};
extern struct fn_1_151C9C_lbl_1_bss_8ED88 lbl_1_bss_8ED88;
extern struct fn_1_151C9C_lbl_1_rodata_D4F8 lbl_1_rodata_D4F8;
extern struct fn_1_151C9C_lbl_1_rodata_D500 lbl_1_rodata_D500;
extern u32 fn_1_151BE8(s16, s16);
extern void fn_80008BA8(void *, void *, u32);

struct FzgxCopy_4 { u32 words[1]; };
#pragma opt_propagation off
void fn_1_151C9C(void *arg0, s32 arg_sp0) {
    struct FzgxCopy_4 loc_8;
    void *temp_r7;
    u32 var_r3;
    s32 temp_r3;
    void *var_r30;
    u32 temp_r29;
    s16 var_r28;

    var_r28 = 0;
    temp_r29 = lbl_1_bss_8ED88.unk_0;
    var_r30 = (void *)(temp_r29 + (lbl_1_bss_8ED88.unk_4 * 8));
    while (var_r28 < 1) {
        if ((temp_r29 == 0) || (temp_r3 = *(s32 *)((u8 *)(temp_r29) + 0), (((temp_r3 & 0x80000000) == 0) != 0)) || !(temp_r3 & 0x40000000)) {
            var_r3 = fn_1_151BE8((s16)(lbl_1_bss_8ED88.unk_6), var_r28);
        } else {
            var_r3 = *(u32 *)((u8 *)(var_r30) + 33192);
        }
        temp_r7 = (void *)(*(void **)((u8 *)(arg0) + 4));
        if ((u8) (*(u8 *)((u8 *)(temp_r7) + 21)) == (u8) var_r3) {
            (*(s8 *)((u8 *)(&loc_8) + 0)) = (s8) (var_r3 >> 0x18U);
            (*(u8 *)((u8 *)(&loc_8) + 1)) = (u8) (var_r3 >> 0x10U);
            (*(u8 *)((u8 *)(&loc_8) + 2)) = (u8) (var_r3 >> 8U);
            (*(u8 *)((u8 *)(&loc_8) + 3)) = 0xFF;
            fn_80008BA8((void *)((u8 *)(temp_r7) + 8), (void *)(&loc_8), (u32)(4U));
            (*(s8 *)((u8 *)(&loc_8) + 0)) = (s8) ((f32) (*(u8 *)((u8 *)(&loc_8) + 0)) * lbl_1_rodata_D4F8.unk_0);
            (*(s8 *)((u8 *)(&loc_8) + 1)) = (s8) ((f32) (*(u8 *)((u8 *)(&loc_8) + 1)) * lbl_1_rodata_D4F8.unk_0);
            (*(s8 *)((u8 *)(&loc_8) + 2)) = (s8) ((f32) (*(u8 *)((u8 *)(&loc_8) + 2)) * lbl_1_rodata_D4F8.unk_0);
            fn_80008BA8((void *)((u8 *)((*(void **)((u8 *)(arg0) + 4))) + 4), (void *)(&loc_8), (u32)(4U));
        }
        var_r30 = (void *)((u8 *)(var_r30) + 4);
        var_r28 += 1;
            }
}
#pragma opt_propagation reset
/* fzgx:end fn_1_151C9C */

/* fzgx:begin fn_1_151E20 */
u32 fn_1_151E20(u32 value, s16 index) {
    u32 result = (u32)-1;

    switch (index) {
    case 0:
        result = value >> 24;
        break;
    case 1:
        result = (value >> 16) & 0xff;
        break;
    case 2:
        result = (value >> 8) & 0xff;
        break;
    case 3:
        result = value & 0xff;
        break;
    }

    return result;
}
/* fzgx:end fn_1_151E20 */

/* fzgx:begin fn_1_151E74 */
void fn_1_151E74(u32 *value, s16 index, int byte) {
    switch (index) {
    case 0:
        *value = (*value & 0x00FFFFFF) | ((u32)byte << 24);
        break;
    case 1:
        *value = (*value & 0xFF00FFFF) | ((u32)byte << 16);
        break;
    case 2:
        *value = (*value & 0xFFFF00FF) | ((u32)byte << 8);
        break;
    case 3:
        *value = (*value & 0xFFFFFF00) | byte;
        break;
    default:
        break;
    }
}
/* fzgx:end fn_1_151E74 */

/* fzgx:begin fn_1_152840 */
typedef struct Entry {
    s16 id;
    u8 pad[2];
    u32 flags;
} Entry;

int fn_1_152840(s16 id, Entry *entries, s16 outer_count, s16 inner_count) {
    s16 count;
    s16 i;
    s16 j;

    if (id == -1) {
        return 0;
    }

    count = inner_count;
    for (i = 0; i < outer_count; i++) {
        for (j = 0; j < count; j++) {
            if ((entries[(i * count) + j].flags & (3u << 30)) == 0 &&
                id == entries[(i * count) + j].id) {
                return 1;
            }
        }
    }

    return 0;
}
/* fzgx:end fn_1_152840 */

/* fzgx:begin fn_1_1528D0 */
typedef struct Cell {
    s16 id;
    u8 pad[2];
    u32 flags;
} Cell;

s32 fn_1_1528D0(s16 x, s16 y, Cell *table, s16 unused, s16 multiplier) {
    s32 value;

    if (lbl_1_bss_8B3A0.unk_94 & 0x00020000) {
        if (table[(x * multiplier) + y].flags & ~0x3FFFFFFF)
            return -1;
    } else {
        if (table[(x * multiplier) + y].flags & 0x40000000)
            return -1;
    }

    value = table[(x * multiplier) + y].id;
    if (value != -1)
        return value;
    return -1;
}
/* fzgx:end fn_1_1528D0 */

/* fzgx:begin fn_1_152970 */
typedef struct {
    s16 key;
    u16 pad;
    u32 mask;
} Fn152970Entry;

s32 fn_1_152970(s16 *out_group, s16 *out_entry, s16 key, u32 mask,
                 Fn152970Entry *entries, s16 group_count, s16 entry_count) {
    s16 count;
    s16 group;
    s16 entry;

    if (key == -1) {
        return 0;
    }

    count = entry_count;
    for (group = 0; group < group_count; group++) {
        for (entry = 0; entry < count; entry++) {
            if ((entries[(group * count) + entry].mask & mask) == 0 &&
                key == entries[(group * count) + entry].key) {
                *out_group = group;
                *out_entry = entry;
                return 1;
            }
        }
    }
    return 0;
}
/* fzgx:end fn_1_152970 */

/* fzgx:begin fn_1_153988 */
// fn_1_153988: empty in retail (single blr).
void fn_1_153988(void) {
}
/* fzgx:end fn_1_153988 */

/* fzgx:begin fn_1_15398C */
// Prepares the shared background object and advances the background system.
void fn_1_15398C(void) {
    Obj_1_data_2A7E0_At3C *background = lbl_1_data_2A7E0.unk_3C;

    fn_1_153AF8(&background->unk_0);
    fn_1_153D48(background);
    fn_1_9A508();
}
/* fzgx:end fn_1_15398C */

/* fzgx:begin fn_1_1539D0 */
// Calls initialization, then loops calling two functions for each item
void fn_1_1539D0(void) {
    int count = fn_1_58C4();
    int i;
    for (i = 0; i < count; i++) {
        fn_1_5948(i);
        fn_1_627C(i);
    }
}
/* fzgx:end fn_1_1539D0 */

/* fzgx:begin fn_1_153A28 */
void fn_1_153A28(void) {
    Obj_1_data_2A7E0_At3C *obj;
    int count;
    int i;

    obj = lbl_1_data_2A7E0.unk_3C;
    fn_1_9D260();
    fn_1_9AD54();
    count = fn_1_58C4();
    for (i = 0; i < count; i++) {
        fn_1_5948(i);
        fn_1_153D74(obj);
        fn_1_627C(i);
    }
    fn_1_153B24(obj);
}
/* fzgx:end fn_1_153A28 */

/* fzgx:begin fn_1_153AAC */
// fn_1_153AAC: empty in retail (single blr).
void fn_1_153AAC(void) {
}
/* fzgx:end fn_1_153AAC */

/* fzgx:begin fn_1_153AB0 */
// Initializes the background Aurora object.
void fn_1_153AB0(void) {
    Obj_1_data_2A7E0_At3C *object = lbl_1_data_2A7E0.unk_3C;

    fn_1_153C60(object);
    fn_1_1540B0(object);
    fn_1_9AD88();
}
/* fzgx:end fn_1_153AB0 */

/* fzgx:begin fn_1_153AF4 */
// fn_1_153AF4: empty in retail (single blr).
void fn_1_153AF4(void) {
}
/* fzgx:end fn_1_153AF4 */

/* fzgx:begin fn_1_153AF8 */
// Clears the first entry and any following entries selected by its count.
void fn_1_153AF8(u32 *entries) {
    u32 *current = entries;
    int index = 0;

    entries[0] = 0;
    while (index < (int)entries[0]) {
        *++current = 0;
        index++;
    }
}
/* fzgx:end fn_1_153AF8 */

/* fzgx:begin fn_1_153C60 noprologue */
#include "types.h"

extern u32 lbl_1_data_2A7E0[];
extern void lbl_8006DFE8(void *);
extern void lbl_8006E13C(void *);
extern void lbl_8006E0A4(void *);
extern void fn_80072558(void);
extern void lbl_8006D784(void *);
extern void fn_1_560F0(s32, void *);
extern void fn_1_55210(void *);

void fn_1_153C60(u8 *base) {
    u8 *entry;
    u8 *slot;
    s32 i;
    u8 *obj;
    u8 work0[0x30];
    u8 work1[0x30];

    entry = base;
    slot = base;
    i = 0;

    while (i < *(s32 *)base) {
        obj = *(u8 **)(entry + 4);
        {
            u32 value = *(u32 *)(obj + 4);

            if ((value + 0x10000) == 0xffff || (value & lbl_1_data_2A7E0[20]) != 0) {
                lbl_8006DFE8(slot + 0x504);
                lbl_8006E13C(obj + 0x20);
                lbl_8006E0A4((u8 *)*(void **)(base + 0x1104) + 8);
                fn_80072558();
                lbl_8006D784(work0);
                *(f32 *)(work0 + 0xC) = *(f32 *)(entry + 0x204);
                *(f32 *)(work0 + 0x1C) = *(f32 *)(entry + 0x304);
                fn_1_560F0(0, work0);
                lbl_8006D784(work1);
                *(f32 *)(work1 + 0x1C) = *(f32 *)(entry + 0x404);
                fn_1_560F0(1, work1);
                fn_1_55210(*(void **)(base + 0x1104));
            }
        }

        entry += 4;
        slot += 0x30;
        i++;
    }
}
/* fzgx:end fn_1_153C60 */

/* fzgx:begin fn_1_153D48 */
// Clears the Aurora background data region.
void fn_1_153D48(void *background) {
    fn_80008BEC((u8 *)background + 0x1108, 0, 0x5fc);
}
/* fzgx:end fn_1_153D48 */

/* fzgx:begin fn_1_1540B0 noprologue */
#include "types.h"

extern s32 fn_1_5910(void);
extern void fn_1_154164(u32 value, u32 *arg1, u32 *arg2, u32 arg3);
extern u32 lbl_1_rodata_D57C[7];

void fn_1_1540B0(u32 value) {
    u32 *table;
    s32 i;
    u32 *base;
    u32 *entry;
    u32 args[3];

    base = (u32 *)((u8 *)value + 0x1108);
    {
        s32 slot;
        slot = fn_1_5910();
        fn_1_154164(value, (u32 *)((u8 *)base + slot * 0xc + 0x8c),
                    (u32 *)((u8 *)base + slot * 0x30 + 0x23c), 0);
    }

    entry = lbl_1_rodata_D57C;
    table = base;
    i = 0;
    while (i < (s32)base[1]) {
        args[0] = entry[0];
        args[1] = entry[1];
        args[2] = entry[2];
        fn_1_154164(value, args, (u32 *)((u8 *)table + 0x2fc), 1);
        table = (u32 *)((u8 *)table + 0x30);
        i++;
    }
}
/* fzgx:end fn_1_1540B0 */

/* fzgx:begin fn_1_1543E8 */
u32 fn_1_1543E8(s32 value, u32 *source) {
    Obj_1_data_2A7E0_At3C *obj = lbl_1_data_2A7E0.unk_3C;

    switch (value) {
    case 0:
        obj->unk_1104 = *source;
        break;
    default:
        break;
    }

    return 1;
}
/* fzgx:end fn_1_1543E8 */
