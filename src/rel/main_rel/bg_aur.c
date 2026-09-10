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
