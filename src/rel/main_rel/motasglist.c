#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/motasglist.h"

extern void fn_1_41328(void *arg0);
extern void fn_1_43264(void *arg0, f32 arg1);
extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);
extern void lbl_8006D668(void *vector);
extern void lbl_8006DBAC(void *value);
extern void fn_1_449A8(void *vector);
extern void lbl_8006DB74(void *value);
extern u32 lbl_1_bss_384CC;

/* fzgx:begin fn_1_41850 */
struct fn_1_41850_Arg0 {
    u8 pad_0[0x2];
    u16 unk_2;
};
struct fn_1_41850_lbl_801A6410 {
    u32 unk_0;
};
struct fn_1_41850_Node {
    u8 pad_0[0x28];
    void *unk_28;
    u8 pad_2c[0x4];
    void *next;
};
extern struct fn_1_41850_lbl_801A6410 lbl_801A6410;
extern u8 lbl_1_data_6720[];
extern void fn_1_46B4(u32, void *, const char *, int);


void fn_1_41850(void *arg0, s32 arg_sp0) {
    void *temp_r4;
    void *temp_r4_2;
    void *temp_r4_3;
    void *temp_r4_4;
    void *temp_r4_5;
    void *temp_r4_6;
    void *temp_r4_7;
    void *temp_r4_8;
    void *temp_r4_9;
    void *temp_r4_10;
    void *temp_r4_11;
    u16 temp_r3;
    s32 var_r28;
    void *temp_r28;
    s32 var_r27;
    void *var_r27_2;

    temp_r3 = *(u16 *)((u8 *)(arg0) + 2);
    if (temp_r3 & 1) {
        if (!(temp_r3 & 4)) {
            var_r27 = 0;
            var_r28 = 0;
            while (var_r27 < (s32) (*(u16 *)((u8 *)(arg0) + 16))) {
                temp_r4 = (void *)(((struct fn_1_41850_Node *)(*(void **)((u8 *)(arg0) + 12)))[var_r27].unk_28);
                if (temp_r4 != NULL) {
                    fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x123));
                }
                var_r28 += 0x34;
                var_r27 += 1;
                            }
            temp_r4_2 = (void *)(*(void **)((u8 *)(arg0) + 20));
            if (temp_r4_2 != NULL) {
                fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_2), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x125));
            }
            temp_r4_3 = (void *)(*(void **)((u8 *)(arg0) + 32));
            if (temp_r4_3 != NULL) {
                fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_3), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x126));
            }
        }
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(*(void **)((u8 *)(arg0) + 12)), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x128));
    } else {
        var_r27_2 = (void *)(*(void **)((u8 *)(arg0) + 12));
        while (var_r27_2 != NULL) {
            temp_r4_4 = (void *)(*(void **)((u8 *)(var_r27_2) + 40));
            temp_r28 = (void *)(*(void **)((u8 *)(var_r27_2) + 48));
            if (temp_r4_4 != NULL) {
                fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_4), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x12E));
            }
            fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(var_r27_2), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x12F));
            var_r27_2 = (void *)(temp_r28);
                    }
        temp_r4_5 = (void *)(*(void **)((u8 *)(arg0) + 32));
        if (temp_r4_5 != NULL) {
            fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_5), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x131));
        }
    }
    temp_r4_6 = (void *)(*(void **)((u8 *)(arg0) + 40));
    if (temp_r4_6 != NULL) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_6), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x133));
    }
    temp_r4_7 = (void *)(*(void **)((u8 *)(arg0) + 52));
    if (temp_r4_7 != NULL) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_7), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x10B));
    }
    temp_r4_8 = (void *)(*(void **)((u8 *)(arg0) + 56));
    if (temp_r4_8 != NULL) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_8), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x10C));
    }
    temp_r4_9 = (void *)(*(void **)((u8 *)(arg0) + 44));
    if (temp_r4_9 != NULL) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_9), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x10D));
    }
    temp_r4_10 = (void *)(*(void **)((u8 *)(arg0) + 48));
    if (temp_r4_10 != NULL) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_10), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x10E));
    }
    (*(void **)((u8 *)(arg0) + 52)) = (void *)(NULL);
    (*(s8 *)((u8 *)(arg0) + 39)) = 0;
    (*(void **)((u8 *)(arg0) + 56)) = (void *)(NULL);
    (*(s32 *)((u8 *)(arg0) + 60)) = 0;
    (*(s32 *)((u8 *)(arg0) + 64)) = 0;
    (*(s16 *)((u8 *)(arg0) + 72)) = 0;
    (*(s8 *)((u8 *)(arg0) + 76)) = 0;
    temp_r4_11 = (void *)(*(void **)((u8 *)(arg0) + 8));
    if ((temp_r4_11 != NULL) && !((*(u16 *)((u8 *)(arg0) + 2)) & 2)) {
        fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(temp_r4_11), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x137));
    }
    fn_1_46B4((u32)(lbl_801A6410.unk_0), (void *)(arg0), (const char *)((s8 *) lbl_1_data_6720), (s32)(0x138));
}
/* fzgx:end fn_1_41850 */

/* fzgx:begin fn_1_41B18 */
typedef struct Node Node;
struct Node {
    u8 pad[0x30];
    Node *next;
};

typedef struct Object {
    u8 pad[2];
    u16 flags;
    Node *data;
} Object;

extern Object *fn_1_41BDC(Object *obj);

#pragma opt_propagation off
void *fn_1_41B18(Object *obj, s32 unused, s32 index) {
    Object *result;
    Node *node;
    s32 i;

    result = fn_1_41BDC(obj);
    if ((obj->flags & 1) != 0) {
        return (char *)result->data + index * 0x34;
    }

    node = result->data;
    i = 0;
    while (i < index) {
        node = node->next;
        i++;
    }
    return node;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_41B18 */

/* fzgx:begin fn_1_41BDC */
typedef struct MotasglistData {
    u8 pad_00[0x26];
    u8 count;
    u8 pad_27;
    void *entries;
    u8 pad_2c[0x08];
    void *fallback;
    u8 pad_38[0x14];
    u8 fallback_base;
} MotasglistData;

void *fn_1_41BDC(MotasglistData *data, s32 index) {
    if (index < data->count) {
        return (u8 *)data->entries + index * 0xc;
    }

    if (data->fallback == 0) {
        return data;
    }

    return (u8 *)data->fallback + (index - data->fallback_base) * 0xc;
}
/* fzgx:end fn_1_41BDC */

/* fzgx:begin fn_1_41F58 */
typedef u16 (*Fn41F58Callback)(void *arg, void *entry);

typedef struct Fn41F58Entry {
    u8 pad0[6];
    u8 type;
    u8 pad7;
    u32 value;
} Fn41F58Entry;

typedef struct Fn41F58Data {
    u8 pad0[0x14];
    u32 first_base;
    u8 pad18[8];
    u32 first_data;
    u16 first_count;
    u8 pad26[0x16];
    u32 second_data;
    u32 second_base;
    u8 pad44[6];
    u16 second_count;
} Fn41F58Data;

void fn_1_41F58(Fn41F58Data *data, int type, Fn41F58Callback callback, void *arg) {
    Fn41F58Entry *entry;
    int i;

    for (i = 0; i < data->first_count; i++) {
        entry = (Fn41F58Entry *)(data->first_data + i * 0x10);
        if (entry->type == type) {
            entry->value = callback(arg, (void *)(data->first_base + entry->value));
        }
    }

    for (i = 0; i < data->second_count; i++) {
        entry = (Fn41F58Entry *)(data->second_data + i * 0x10);
        if (entry->type == type) {
            entry->value = callback(arg, (void *)(data->second_base + entry->value));
        }
    }
}
/* fzgx:end fn_1_41F58 */

/* fzgx:begin fn_1_42458 */
typedef struct Fn142458Data {
    u16 value0;
    u16 value2;
    s16 value4;
    u16 pad6;
    u32 value8;
} Fn142458Data;

void fn_1_42458(Fn142458Data *dst, const Fn142458Data *src) {
    dst->value0 = src->value0;
    dst->value8 = src->value8;
    dst->value2 = src->value2;
    dst->value4 = src->value4;
}
/* fzgx:end fn_1_42458 */

/* fzgx:begin fn_1_426AC */
typedef struct Fn1426ACObject {
    u16 count;
    u8 pad2[6];
    u8 *entries;
    u8 padC[0x30];
    void *value;
} Fn1426ACObject;

void fn_1_426AC(Fn1426ACObject *object, void *value) {
    u32 offset;
    s32 i;

    object->value = value;
    i = 0;
    offset = 0;
    for (; i < object->count; i++) {
        *(void **)(object->entries + 0xd0 + offset) = value;
        offset += 0x18c;
        value = (u8 *)value + 8;
    }
}
/* fzgx:end fn_1_426AC */

/* fzgx:begin fn_1_426E4 */
typedef struct Fn1426E4Object {
    u8 pad0[0x24];
    void *value;
} Fn1426E4Object;

void fn_1_426E4(Fn1426E4Object *object, void *value) {
    object->value = value;
    fn_1_41328(value);
}
/* fzgx:end fn_1_426E4 */

/* fzgx:begin fn_1_42E74 */
typedef struct Fn142E74Pair {
    u32 a;
    u32 b;
} Fn142E74Pair;

typedef struct Fn142E74Entry {
    u8 pad0[0xB8];
    Fn142E74Pair sourceB8;
    u32 sourceC0;
    Fn142E74Pair sourceC4;
    u32 sourceCC;
    u8 padD0[0xA4];
    Fn142E74Pair value174;
    u32 value17C;
    Fn142E74Pair value180;
    u32 value188;
} Fn142E74Entry;

typedef struct Fn142E74Object {
    u16 count;
    u16 flags;
    u8 pad4[4];
    Fn142E74Entry *entries;
    u8 padC[0x0C];
    f32 value0;
    f32 value1;
    f32 value2;
    u8 pad24[0x1C];
    u16 flags40;
} Fn142E74Object;

extern void lbl_8006DAEC(void);
extern void lbl_8006DBAC(void *);
extern void fn_8006E5FC(void *);
extern void lbl_8006DB30(void);
extern void fn_1_438AC(Fn142E74Object *object, Fn142E74Entry *entry, s32 arg2);
extern void fn_1_433E0(Fn142E74Object *object);
extern void fn_1_4300C(Fn142E74Object *object);

void fn_1_42E74(Fn142E74Object *object) {
    s32 i;
    Fn142E74Entry *entry;

    lbl_8006DAEC();
    if (object->flags & 1) {
        for (i = 0; i < object->count; i++) {
            fn_1_438AC(object, (Fn142E74Entry *)((u8 *)object->entries + i * 0x18c), 1);
        }

        for (i = 0; i < object->count; i++) {
            entry = (Fn142E74Entry *)((u8 *)object->entries + i * 0x18c);
            lbl_8006DBAC((u8 *)entry + 0x88);
            fn_8006E5FC((u8 *)entry + 0x164);
            entry->value174 = entry->sourceB8;
            entry->value17C = entry->sourceC0;
            entry->value180 = entry->sourceC4;
            entry->value188 = entry->sourceCC;
        }
    }

    for (i = 0; i < object->count; i++) {
        fn_1_438AC(object, (Fn142E74Entry *)((u8 *)object->entries + i * 0x18c), 0);
    }
    object->value0 = *(f32 *)((u8 *)object->entries + 0x94);
    object->value1 = *(f32 *)((u8 *)object->entries + 0xa4);
    object->value2 = *(f32 *)((u8 *)object->entries + 0xb4);
    fn_1_433E0(object);
    lbl_8006DB30();
    if (!(object->flags & 0x10)) {
        fn_1_4300C(object);
    }
    if (object->flags40 & 2) {
        object->flags |= 4;
    } else {
        object->flags &= ~4;
    }
    object->flags &= ~0x100;
}
/* fzgx:end fn_1_42E74 */

/* fzgx:begin fn_1_4300C */
typedef struct Fn14300CObject {
    u8 pad0[2];
    u16 flags;
    f32 value;
    u8 pad1[0x38];
} Fn14300CObject;

void fn_1_4300C(Fn14300CObject *object) {
    fn_1_43264((u8 *)object + 0x40, object->value);
    if (object->flags & 1) {
        fn_1_43264((u8 *)object + 0x58, object->value);
    }
}
/* fzgx:end fn_1_4300C */

/* fzgx:begin fn_1_43058 */
typedef struct Fn143058Entry {
    u8 pad0[0x94];
    f32 value0;
    u8 pad98[0x0C];
    f32 value1;
    u8 padA8[0x0C];
    f32 value2;
} Fn143058Entry;

typedef struct Fn143058Object {
    u16 count;
    u16 flags;
    u8 pad4[4];
    u8 *entries;
    u8 padC[0xC];
    f32 value0;
    f32 value1;
    f32 value2;
} Fn143058Object;

extern void fn_1_43E08(Fn143058Object *object, u8 *entry, void *arg2, void *arg3, f32 value);
extern void fn_1_433E0(Fn143058Object *object);

void fn_1_43058(Fn143058Object *object, void *arg2, void *arg3, f32 value) {
    u32 offset;
    s32 i;

    lbl_8006DAEC();
    i = 0;
    offset = 0;
    for (; i < object->count; i++) {
        fn_1_43E08(object, object->entries + offset, arg2, arg3, value);
        offset += 0x18c;
    }
    object->value0 = ((Fn143058Entry *)object->entries)->value0;
    object->value1 = ((Fn143058Entry *)object->entries)->value1;
    object->value2 = ((Fn143058Entry *)object->entries)->value2;
    fn_1_433E0(object);
    lbl_8006DB30();
    object->flags &= ~0x100;
}
/* fzgx:end fn_1_43058 */

/* fzgx:begin fn_1_43120 */
typedef struct Fn143120Entry {
    u8 pad0[0x88];
    u8 value0[8];
    f32 x;
    u8 pad94[0x0c];
    f32 y;
    u8 padA4[0x0c];
    f32 z;
} Fn143120Entry;

typedef struct Fn143120Object {
    u8 pad0[8];
    Fn143120Entry *entries;
} Fn143120Object;

void fn_1_43120(Fn143120Object *object, u32 index, f32 *vector) {
    Fn143120Entry *entry;
    f32 delta[3];

    entry = (Fn143120Entry *)((u8 *)object->entries + (index & 0xffff) * 0x18c);
    lbl_8006DAEC();
    delta[0] = vector[0] - entry->x;
    delta[1] = vector[1] - entry->y;
    delta[2] = vector[2] - entry->z;
    lbl_8006D668(delta);
    lbl_8006DBAC(entry->value0);
    fn_1_449A8(delta);
    lbl_8006DB74(entry->value0);
    lbl_8006DB30();
}
/* fzgx:end fn_1_43120 */

/* fzgx:begin fn_1_431B8 */
typedef enum Fn1431B8Index {
    FN1431B8_INVALID = -1
} Fn1431B8Index;

typedef struct Fn1431B8Object {
    u8 pad0[4];
    u16 flags;
    u16 index;
    u8 pad8[0xD8];
    u16 value0;
    u16 value1;
    u16 value2;
} Fn1431B8Object;

s32 fn_1_431B8(Fn1431B8Object *base, Fn1431B8Object *object) {
    Fn1431B8Object *entry;
    s32 count;

    entry = (Fn1431B8Object *)((u8 *)base + object->index * 0x18c);
    count = 0;
    while (!(entry->flags & 2)) {
        if (count == 2) {
            // The retail loop shares one exit for both termination checks.
            goto done;
        }
        if (entry->index == FN1431B8_INVALID) {
            // The retail loop shares one exit for both termination checks.
            goto done;
        }
        count++;
        if (entry->value0 != 0 || entry->value1 != 0 || entry->value2 != 0) {
            return 1;
        }
        entry = (Fn1431B8Object *)((u8 *)base + entry->index * 0x18c);
    }
done:
    return 0;
}
/* fzgx:end fn_1_431B8 */

/* fzgx:begin fn_1_4322C */
struct fn_1_4322C_Arg0 {
    u16 unk_0;
    u16 unk_2;
    u16 unk_4;
    u16 unk_6;
    f32 unk_8;
    f32 unk_C;
    f32 unk_10;
};

extern const f32 lbl_1_rodata_F50;
extern const f32 lbl_1_rodata_F54;

void fn_1_4322C(struct fn_1_4322C_Arg0 *arg0) {
    const f32 *value;
    f32 v0;
    u16 zero;

    value = &lbl_1_rodata_F50;
    zero = 0;
    arg0->unk_0 = zero;
    v0 = *value;
    arg0->unk_8 = v0;
    arg0->unk_C = lbl_1_rodata_F54;
    arg0->unk_10 = lbl_1_rodata_F54;
    arg0->unk_2 = zero;
    arg0->unk_4 = zero;
    arg0->unk_6 = zero;
}
/* fzgx:end fn_1_4322C */

/* fzgx:begin fn_1_433A4 */
typedef struct Fn1433A4Object {
    u16 value0;
    u16 value1;
    u16 value2;
    u16 value3;
    f32 value4;
    f32 value5;
    f32 value6;
} Fn1433A4Object;

void fn_1_433A4(Fn1433A4Object *dst, Fn1433A4Object *src) {
    dst->value0 = src->value0;
    dst->value5 = src->value5;
    dst->value6 = src->value6;
    dst->value4 = src->value4;
    dst->value1 = src->value1;
    dst->value3 = src->value3;
    dst->value2 = src->value2;
}
/* fzgx:end fn_1_433A4 */

/* fzgx:begin fn_1_451D4 */
void fn_1_451D4(void) {
    lbl_1_bss_384CC = 0;
}
/* fzgx:end fn_1_451D4 */
