#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/mdlload.h"

extern void fn_80071484(void);
extern void fn_80071678(void);
extern void *OSGetArenaHi(void);
extern void fn_1_D3BE8(void);
extern u8 lbl_1_bss_7AD58[8];
extern void fn_1_9A508(void);
extern void fn_1_D3F24(void *base);
extern void fn_1_D3F88(void *base);
extern f32 lbl_1_rodata_6168[112];
extern u32 fn_1_5910(void);
extern void fn_1_9AD88(Obj_1_data_2A7E0 *obj);
extern u32 fn_1_9D260(void);
extern s32 fn_1_D3E90(void);
extern void fn_1_1067A8(void *obj, f32 value, f32 limit);
extern void fn_1_D4174(void *base, void *arg);
extern s16 camera_get_mode(void);
extern s32 fn_1_6EC0(u8 value);
extern u32 fn_1_864E8(s32 value);
extern s32 fn_1_7000(void);
extern void fn_1_681C(u8 value, void *out);
extern s32 fn_1_1FB80(void *value, s32 mode);
extern void fn_1_103090(void *ptr);
extern void fn_1_1030A4(void *ptr);
extern void fn_1_103264(void *item, void *arg);
extern s16 fn_1_3F0C8(void);
extern void fn_1_D6748(void *obj, u32 *arg1, s16 arg2);
extern u32 lbl_801A63C0;
extern void fn_1_D550C(void *);

extern int fn_1_45730(void *owner, void *buffer);
extern int fn_1_458A0(void *buffer, void *work, int size, int mode);
extern u32 lbl_801A6410;
extern void *fn_1_45D0(u32 allocator, u32 size, const unsigned char *name, int mode);
extern int fn_1_45850(void *buffer);
extern void fn_1_12F78(void *owner, void *data);
extern void DCFlushRange(void *address, u32 length);
extern void *fn_80071100(void *data, void *size, void *user);
extern void fn_1_D3BE8(void);
extern void fn_80071484(void);
extern void fn_80071678(void);
extern void *OSGetArenaHi(void);
extern u8 lbl_1_bss_7AD58[8];
extern void fn_1_9A508(void);
extern void fn_1_D3F24(void *base);
extern void fn_1_D3F88(void *base);
extern f32 lbl_1_rodata_6168[112];
extern u32 fn_1_5910(void);
extern void fn_1_9AD88(Obj_1_data_2A7E0 *obj);
extern u32 fn_1_9D260(void);
extern s32 fn_1_D3E90(void);
extern void fn_1_1067A8(void *obj, f32 value, f32 limit);
extern void fn_1_D4174(void *base, void *arg);
extern s16 camera_get_mode(void);
extern s32 fn_1_6EC0(u8 value);
extern u32 fn_1_864E8(s32 value);
extern s32 fn_1_7000(void);
extern void fn_1_681C(u8 value, void *out);
extern s32 fn_1_1FB80(void *value, s32 mode);
extern void fn_1_103090(void *ptr);
extern void fn_1_1030A4(void *ptr);
extern void fn_1_103264(void *item, void *arg);
extern s16 fn_1_3F0C8(void);
extern void fn_1_D6748(void *obj, u32 *arg1, s16 arg2);
extern u32 lbl_801A63C0;
extern void fn_1_D550C(void *);

extern void fn_1_D3BE8(void);

extern void fn_1_D3BE8(void);

extern void fn_1_D3BE8(void);

extern void fn_1_D3BE8(void);

extern void fn_1_D3BE8(void);
extern int fn_1_D3B6C(void);

/* fzgx:begin fn_1_D35D4 noprologue */
#include "types.h"

extern int fn_1_45730(void *arg0, void *arg1);
extern u8 lbl_1_bss_3BC0[32];
extern int fn_1_458A0(void *arg0, void *arg1, u32 arg2, u32 arg3);
extern char lbl_1_data_3DBD8[10];
extern void *lbl_801A6410[1];
extern void *fn_1_45D0(void *arg0, u32 arg1, void *arg2, u32 arg3);
extern int fn_1_45850(void *arg);
extern void fn_1_12860(void *arg0, void *arg1);
extern void fn_1_46B4(void *arg0, void *arg1, void *arg2, u32 arg3);
extern void *fn_80071100(void *arg0, void *arg1, void *arg2);
extern int fn_1_D3B6C(void);
extern void DCFlushRange(void *address, u32 length);

int fn_1_D35D4(void *unused, void *arg) {
    u8 local[0x58];
    u32 size1;
    u32 size0;
    struct { void * value; } buffer1;
    u8 *data;
    void *buffer0;
    void *object;

    if (fn_1_45730(unused, local) == 0) {
        return 0;
    }
    if (fn_1_458A0(local, lbl_1_bss_3BC0, 32, 0) < 0) {
        return 0;
    }

    size0 = (__lwbrx((u32 *)lbl_1_bss_3BC0, 0) + 39) & ~31;
    size1 = (__lwbrx((u32 *)lbl_1_bss_3BC0, 4) + 31) & ~31;

    buffer0 = fn_1_45D0(lbl_801A6410[0], ((size1 + 31) & ~31) + 32,
                         lbl_1_data_3DBD8, 0x7a);
    data = (u8 *)buffer0 + 32;
    if (data == 0) {
        return 0;
    }
    buffer1.value = fn_1_45D0(lbl_801A6410[0], size0,
                         lbl_1_data_3DBD8, 0x80);
    if (buffer1.value == 0) {
        return 0;
    }
    if (fn_1_458A0(local, buffer1.value, size0, 0) < 0) {
        return 0;
    }
    if (fn_1_45850(local) == 0) {
        return 0;
    }
    fn_1_12860(buffer1.value, (u8 *)buffer0 + 32);
    fn_1_46B4(lbl_801A6410[0], buffer1.value, lbl_1_data_3DBD8, 0x8e);
    DCFlushRange((u8 *)buffer0 + 32, size1);
    object = fn_80071100((u8 *)buffer0 + 32, buffer0, arg);
    *(u32 *)((u8 *)object + 0x10) &= ~1;
    return fn_1_D3B6C();
}
/* fzgx:end fn_1_D35D4 */

/* fzgx:begin fn_1_D3768 */
typedef struct {
    u8 _pad[0x10];
    u32 flags;
} Fn80071100Result;

// Loads, prepares, and submits the owner's model payload.
int fn_1_D3768(void *owner, void *user) {
    u8 buffer[0x58];
    u32 data_size;
    Fn80071100Result *result;
    u32 aligned_size;
    void *data;

    if (fn_1_45730(owner, buffer) == 0) {
        return 0;
    }
    if (fn_1_458A0(buffer, lbl_1_bss_3BC0, 32, 0) < 0) {
        return 0;
    }

    (void)__lwbrx(lbl_1_bss_3BC0, 0);
    data_size = __lwbrx(lbl_1_bss_3BC0, 4);
    aligned_size = (data_size + 0x1f) & ~0x1f;
    data = fn_1_45D0(lbl_801A6410,
                     ((aligned_size + 0x1f) & ~0x1f) + 0x20,
                     lbl_1_data_3DBD8, 0x7a);
    result = (Fn80071100Result *)((u8 *)data + 0x20);
    if (result == 0) {
        return 0;
    }
    if (fn_1_45850(buffer) == 0) {
        return 0;
    }

    fn_1_12F78(owner, result);
    DCFlushRange(result, aligned_size);
    result = (Fn80071100Result *)fn_80071100(result, data, user);
    result->flags &= ~1;
    return fn_1_D3B6C();
}
/* fzgx:end fn_1_D3768 */

/* fzgx:begin fn_1_D3884 */
void fn_1_D3884(void) {
    fn_80071484();
}
/* fzgx:end fn_1_D3884 */

/* fzgx:begin fn_1_D38A4 */
void fn_1_D38A4(void) {
    fn_80071678();
}
/* fzgx:end fn_1_D38A4 */

/* fzgx:begin fn_1_D38C4 noprologue */
#include "types.h"

extern int fn_1_45730(void *arg, void *path);
extern u8 lbl_1_bss_3BC0[32];
extern int fn_1_458A0(void *path, void *data, int size, int offset);
extern char lbl_1_data_3DBD8[10];
extern void *lbl_801A6410;
extern void *fn_1_45D0(void *base, int offset, void *source, int size);
extern int fn_1_45850(void *path);
extern void fn_1_12860(void *data, int size);
extern void fn_1_46B4(void *base, int offset, void *source, int size);
extern void DCFlushRange(void *address, u32 size);
extern void *fn_80071678(void *address, u32 size);

typedef struct {
    u8 pad[0xc];
    u32 field_c;
} Fn1D38C4Result;

#pragma opt_propagation off
#pragma opt_common_subs off
void *fn_1_D38C4(void *arg) {
    u8 path[96];
    u32 size2;
    u32 size;
    void *data2;
    void *aligned;
    void *data;
    Fn1D38C4Result *result;

    if (fn_1_45730(arg, path) == 0) {
        return 0;
    }
    if (fn_1_458A0(path, lbl_1_bss_3BC0, 0x20, 0) < 0) {
        return 0;
    }

    size = (__lwbrx((void *)lbl_1_bss_3BC0, 0) + 0x27) & ~0x1f;
    size2 = (__lwbrx((void *)lbl_1_bss_3BC0, 4) + 0x1f) & ~0x1f;

    data = fn_1_45D0(lbl_801A6410, ((size2 + 0x1f) & ~0x1f) + 0x20,
                     lbl_1_data_3DBD8, 0x1d6);
    aligned = (void *)(((u32)data + 0x3f) & ~0x1f);
    if (aligned == 0) {
        return 0;
    }
    data2 = fn_1_45D0(lbl_801A6410, size, lbl_1_data_3DBD8, 0x1dc);
    if (data2 == 0) {
        return 0;
    }
    if (fn_1_458A0(path, data2, size, 0) < 0) {
        return 0;
    }
    if (fn_1_45850(path) == 0) {
        return 0;
    }

    fn_1_12860(data2, (int)aligned);
    fn_1_46B4(lbl_801A6410, (int)data2, lbl_1_data_3DBD8, 0x1ea);
    DCFlushRange(aligned, size2);

    result = (Fn1D38C4Result *)fn_80071678(aligned, (u32)data);
    result->field_c = 0;
    return result;
}
#pragma opt_common_subs reset

#pragma opt_propagation reset
/* fzgx:end fn_1_D38C4 */

/* fzgx:begin fn_1_D3A4C noprologue */
#include "types.h"

extern int fn_1_45730(void *arg, void *buffer);
extern u8 lbl_1_bss_3BC0[32];
extern int fn_1_458A0(void *buffer, void *work, int size, int flags);
extern char lbl_1_data_3DBD8[10];
extern void *lbl_801A6410;
extern void *fn_1_45D0(void *arg0, u32 size, void *data, int count);
extern int fn_1_45850(void *buffer);
extern void fn_1_12F78(void *arg, void *buffer);
extern void DCFlushRange(void *buffer, u32 size);
extern void *fn_80071678(void *buffer, u32 size);

int fn_1_D3A4C(void *arg) {
    u8 buffer[96];
    u32 result;
    u32 size;
    u32 ptr;
    u32 value0;
    u32 value1;

    if (fn_1_45730(arg, buffer) == 0) {
        return 0;
    }
    if (fn_1_458A0(buffer, lbl_1_bss_3BC0, 32, 0) < 0) {
        return 0;
    }

    value0 = __lwbrx((void *)lbl_1_bss_3BC0, 0);
    value1 = __lwbrx((void *)lbl_1_bss_3BC0, 4);
    size = (value1 + 31) & ~31;
    ptr = (u32)fn_1_45D0(lbl_801A6410,
                         (((size + 31) & ~31) + 32),
                         lbl_1_data_3DBD8, 470);
    result = (ptr + 63) & ~31;
    if (result == 0) {
        return 0;
    }
    if (fn_1_45850(buffer) == 0) {
        return 0;
    }

    fn_1_12F78(arg, (void *)result);
    DCFlushRange((void *)result, size);
    ptr = (u32)fn_80071678((void *)result, ptr);
    *(u32 *)((u8 *)ptr + 12) = 0;
    return (int)ptr;
}
/* fzgx:end fn_1_D3A4C */

/* fzgx:begin fn_1_D3B6C noprologue */
#include "types.h"

extern void *OSGetArenaHi(void);

extern void fn_1_D3BE8();

typedef struct {
    u32 unk_00;
    void *resource;
} ModelReleaseEntry;

typedef struct {
    s32 entry_count;
    u8 unk_04[4];
    ModelReleaseEntry *entry_table;
} ModelReleaseList;

// Release the list's resources only when it resides above the arena high-water mark.
void *fn_1_D3B6C(ModelReleaseList *list) {
    s32 index;

    if (list != 0 && list > (ModelReleaseList *)OSGetArenaHi()) {
        for (index = 0; index < list->entry_count; index++) {
            fn_1_D3BE8(list->entry_table[index].resource);
        }
    }

    return list;
}
/* fzgx:end fn_1_D3B6C */

/* fzgx:begin fn_1_D3BE8 */
// Increment the model-loader byte counter.
void fn_1_D3BE8(void) {
    lbl_1_bss_7AD58[0]++;
}
/* fzgx:end fn_1_D3BE8 */

/* fzgx:begin fn_1_D3C00 */
// fn_1_D3C00: empty in retail (single blr).
void fn_1_D3C00(void) {
}
/* fzgx:end fn_1_D3C00 */

/* fzgx:begin fn_1_D3C04 */
void fn_1_D3C04(void) {
    void *state = lbl_1_data_2A7E0.unk_3C;

    *(u32 *)((u8 *)state + 0xE7E0) = 0;
    fn_1_9A508();
    fn_1_D3F24(state);
    *(u32 *)((u8 *)state + 0xFD64) = (u32)-1;
}
/* fzgx:end fn_1_D3C04 */

/* fzgx:begin fn_1_D3C58 */
extern s32 fn_1_58C4(void);
extern void fn_1_5948(s32 index);
extern void fn_1_105AB8(void *base, s32 index);
extern void fn_1_D47D8(void *state, s32 index);
extern void fn_1_627C(s32 index);
extern void fn_1_D5958(void *state);
extern void fn_1_D4360(void *state);
extern void fn_1_D4964(void *state);

// Initializes the model-loader state for every available entry.
void fn_1_D3C58(void) {
    Obj_1_data_2A7E0_At3C *state;
    s32 count;
    s32 index;

    state = lbl_1_data_2A7E0.unk_3C;
    count = fn_1_58C4();
    for (index = 0; index < count; index++) {
        fn_1_5948(index);
        fn_1_105AB8(&state->unk_20, index);
        fn_1_D47D8(state, index);
        fn_1_627C(index);
    }
    fn_1_D5958(state);
    fn_1_D4360(state);
    fn_1_D4964(state);
}
/* fzgx:end fn_1_D3C58 */

/* fzgx:begin fn_1_D3DDC */
void fn_1_D3DDC(void) {
    fn_1_D3F88(lbl_1_data_2A7E0.unk_3C);
}
/* fzgx:end fn_1_D3DDC */

/* fzgx:begin fn_1_D3E08 */
// Refreshes the model state and applies the indexed limit when loading is inactive.
void fn_1_D3E08(void) {
    u32 model_index;
    Obj_1_data_2A7E0_At3C *model;
    void *update_value;

    model_index = fn_1_5910();
    model = lbl_1_data_2A7E0.unk_3C;
    fn_1_9AD88(&lbl_1_data_2A7E0);
    update_value = (void *)fn_1_9D260();

    if (fn_1_D3E90() == 0) {
        fn_1_1067A8(&model->unk_20, ((f32 *)model)[model_index],
                    lbl_1_rodata_6168[0]);
    }

    fn_1_D4174(model, update_value);
}
/* fzgx:end fn_1_D3E08 */

/* fzgx:begin fn_1_D3E8C */
// fn_1_D3E8C: empty in retail (single blr).
void fn_1_D3E8C(void) {
}
/* fzgx:end fn_1_D3E8C */

/* fzgx:begin fn_1_D3E90 */
s32 fn_1_D3E90(void) {
    s16 value;
    u8 data[8];

    value = camera_get_mode();
    if (value != -1 && fn_1_6EC0((u8)fn_1_5910()) != 0 &&
        (fn_1_864E8((s16)value) & 0x20) != 0) {
        return 1;
    }

    if (fn_1_7000() != 0) {
        return 1;
    }

    fn_1_681C((u8)fn_1_5910(), data);
    return fn_1_1FB80(data, 1);
}
/* fzgx:end fn_1_D3E90 */

/* fzgx:begin fn_1_D3F24 */
void fn_1_D3F24(void *base) {
    s32 value;
    s32 count;
    char *ptr;

    value = 1;
    ptr = (char *)base + 0x10000;
    count = *(s32 *)(ptr - 0x1820);
    ptr -= 0x181c;

    while (count > 0) {
        *(s32 *)(ptr + 0x68) = value;
        fn_1_103090(ptr);
        count--;
        ptr += 0xac;
    }
}
/* fzgx:end fn_1_D3F24 */

/* fzgx:begin fn_1_D3F88 */
// Iterate through items in a structure, calling fn_1_1030A4 on each.
void fn_1_D3F88(void *base) {
    s32 count;
    char *ptr;
    
    ptr = (char *)base + 0x10000;
    count = *(s32 *)(ptr - 0x1820);
    ptr -= 0x181c;
    
    while (count > 0) {
        fn_1_1030A4(ptr);
        count--;
        ptr += 0xac;
    }
}
/* fzgx:end fn_1_D3F88 */

/* fzgx:begin fn_1_D4174 */
// Process each model-load entry in the caller-provided table.
void fn_1_D4174(void *base, void *arg) {
    s32 remaining;
    char *entry;

    entry = (char *)base + 0x10000;
    remaining = *(s32 *)(entry - 0x1820);
    entry -= 0x181c;

    while (remaining > 0) {
        fn_1_103264(entry, arg);
        remaining--;
        entry += 0xac;
    }
}
/* fzgx:end fn_1_D4174 */

/* fzgx:begin fn_1_D41D8 */
typedef struct {
    u8 pad_0[0xC];
    s16 unk_C;
    s16 unk_E;
    u8 pad_10[0x4];
    u32 unk_14;
    u8 pad_18[0x8];
    u32 unk_20;
} MdlloadItem;

void fn_1_D41D8(void) {
    Obj_1_bss_3BE0_Target **root;
    s32 i;
    MdlloadItem *item;

    if (fn_1_3F0C8() == 0x28) {
        return;
    }

    root = &lbl_1_bss_3BE0;
    i = 0;
    item = (MdlloadItem *)(*root)->unk_A8;
    while (i < (s32)(*root)->unk_A4) {
        if (item->unk_20 & 1) {
            s32 random_value;
            s32 divisor;
            s32 remainder;

            random_value = (s32)(lbl_801A63C0 * 0x676A4B6B + 0x33CB);
            lbl_801A63C0 = (u32)random_value;
            random_value = ((u32)random_value >> 16) & 0x7FFF;
            divisor = (u16)item->unk_C;
            remainder = random_value % divisor;
            if ((remainder >> 7) == 0) {
                fn_1_D6748(item, &item->unk_14, item->unk_E);
            }
        }
        i++;
        item++;
    }
}
/* fzgx:end fn_1_D41D8 */

/* fzgx:begin fn_1_D4360 */
void fn_1_D4360(void *base) {
    *(s32 *)((char *)base + 0xc074) = 200;
}
/* fzgx:end fn_1_D4360 */

/* fzgx:begin fn_1_D47D8 */
struct Entry {
    s8 flag[0x18];
};

struct Base {
    char pad[0xe780];
    struct Entry entries[1];
};

void fn_1_D47D8(struct Base *base, s32 index) {
    base->entries[index].flag[0] = -1;
}
/* fzgx:end fn_1_D47D8 */

/* fzgx:begin fn_1_D5958 */
// fn_1_D5958: iterate through 4 structures, calling fn_1_D550C on each.
void fn_1_D5958(void *arg) {
    void *ptr = arg;
    int i = 0;
    for (; i < 4; i++) {
        fn_1_D550C((char *)ptr + 0xc07c);
        ptr = (char *)ptr + 0x30;
    }
}
/* fzgx:end fn_1_D5958 */

/* fzgx:begin fn_1_D5C68 */
// fn_1_D5C68: returns a constant.
int fn_1_D5C68(void) {
    return 0;
}
/* fzgx:end fn_1_D5C68 */
