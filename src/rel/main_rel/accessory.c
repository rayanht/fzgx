#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/accessory.h"
extern void *fn_80077B14(void *);
extern void lbl_8006DBAC(void *);
extern void fn_8006E250(void *, void *);
extern void fn_1_10846C(void);
extern f32 lbl_1_rodata_7B1C;
extern f32 lbl_1_rodata_7B20;
extern s32 fn_1_14D670(void);
extern u32 lbl_801A66A0;
extern s32 fn_1_86678(s32 arg);
extern u32 lbl_1_bss_897AC[1741];
extern u32 lbl_1_bss_897A4;
extern u32 lbl_1_bss_897A8;

/* fzgx:begin fn_1_108870 */
#include "rel/main_rel/accessory.h"

typedef struct {
    u8 pad_0[0xc];
    u32 unk_c;
    u8 pad_10[0x58];
} AccessoryEntry;

AccessoryEntry *fn_1_108870(void) {
    u32 i;

    for (i = 0; i < 0x46; i++) {
        if (((AccessoryEntry *)&lbl_1_bss_86ED0)[i].unk_c == 0) {
            return &((AccessoryEntry *)&lbl_1_bss_86ED0)[i];
        }
    }
    return 0;
}
/* fzgx:end fn_1_108870 */

/* fzgx:begin fn_1_1088B8 */
extern void fn_1_108920(void *arg);

typedef struct {
    u8 pad_0[0xc];
    u32 unk_c;
    u8 pad_10[0x58];
} AccessoryEntry;

void fn_1_1088B8(void *arg) {
    u32 i;

    for (i = 0; i < 0x46; i++) {
        AccessoryEntry *entry = ((AccessoryEntry *)&lbl_1_bss_86ED0) + i;
        if (entry->unk_c == (u32)arg) {
            fn_1_108920(entry);
        }
    }
}
/* fzgx:end fn_1_1088B8 */

/* fzgx:begin fn_1_108920 noprologue */
#include "types.h"

struct Sig_fn_80077B64_fn_80077B64_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
};

struct Sig_fn_80077B14_fn_80077B14_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x18];
    u32 unk_20;
};


struct fn_1_108920_Copy12 { u32 a[3]; };
struct fn_1_108920_lbl_801A6410 {
    u32 unk_0;
};

extern s32 fn_80077B14(struct Sig_fn_80077B14_fn_80077B14_Arg0 *);
extern struct fn_1_108920_lbl_801A6410 lbl_801A6410;
extern u32 lbl_1_data_40530;
extern void * fn_80077B64(struct Sig_fn_80077B64_fn_80077B64_Arg0 *);
extern void fn_1_46B4(u32, u32, const char *, int);
extern void fn_80008BEC(u32, u32, u32);

void fn_1_108920(u32 accessory) {
    u32 resource;
    s32 matrix_address;
    s32 source_offset;
    s32 entry_index;
    u32 source_address;
    u32 positions;
    u32 entries;
    u32 indices;
    u32 extra_data;
    void * entry_count;
    s32 matrix_base;
    if (accessory != 0) {
        resource = *(u32 *)((u8 *)accessory + 16);
        if (resource != 0) {
            entry_count = (void *)(fn_80077B64((struct Sig_fn_80077B64_fn_80077B64_Arg0 *)resource));
            matrix_base = fn_80077B14((struct Sig_fn_80077B14_fn_80077B14_Arg0 *)resource);
            matrix_address = matrix_base;
            entry_index = 0;
            source_offset = 0;
            while ((u32)entry_index < *(u32 *)((u8 *)entry_count + 0)) {
                entry_index++;
                source_address = (*(u32 *)((u8 *)accessory + 100) + source_offset);
                *(struct fn_1_108920_Copy12 *)matrix_address = *(struct fn_1_108920_Copy12 *)source_address;
                source_offset += 12;
                matrix_address += 64;
            }
        }
    }
    positions = *(u32 *)((u8 *)accessory + 100);
    if (positions != 0) {
        fn_1_46B4(lbl_801A6410.unk_0, positions, (const char *)&lbl_1_data_40530, 1154);
        *(u32 *)((u8 *)accessory + 100) = 0;
    }
    entries = *(u32 *)((u8 *)accessory + 36);
    if (entries != 0) {
        fn_1_46B4(lbl_801A6410.unk_0, entries, (const char *)&lbl_1_data_40530, 1157);
        *(u32 *)((u8 *)accessory + 36) = 0;
    }
    indices = *(u32 *)((u8 *)accessory + 40);
    if (indices != 0) {
        fn_1_46B4(lbl_801A6410.unk_0, indices, (const char *)&lbl_1_data_40530, 1158);
        *(u32 *)((u8 *)accessory + 40) = 0;
    }
    extra_data = *(u32 *)((u8 *)accessory + 44);
    if (extra_data != 0) {
        fn_1_46B4(lbl_801A6410.unk_0, extra_data, (const char *)&lbl_1_data_40530, 1159);
        *(u32 *)((u8 *)accessory + 44) = 0;
    }
    fn_80008BEC(accessory, 0, 104);
}
/* fzgx:end fn_1_108920 */

/* fzgx:begin fn_1_109114 */
#include "rel/main_rel/accessory.h"

typedef struct {
    u8 pad_0[0x150];
    struct {
        u8 pad_0[8];
        u8 *unk_8;
    } *unk_150;
} AccessoryData;

typedef struct {
    u8 pad_0[0x8];
    u32 unk_8;
    AccessoryData *unk_C;
    void *unk_10;
    u8 pad_14[4];
    u32 unk_18;
    u8 pad_1C[8];
    u8 *unk_24;
} AccessoryObject;

void fn_1_109114(AccessoryObject *self) {
    void *base;
    u16 *item;
    int entry_index;
    int item_index;
    u8 *entry;
    
    base = fn_80077B14(self->unk_10);
    lbl_8006DBAC((u8 *)self->unk_C->unk_150->unk_8 +
                 ((u32 *)&lbl_1_data_3FFBC)[self->unk_8] * 0x18c + 0x88);
    entry = self->unk_24;
    entry_index = 0;
    while (entry_index < self->unk_18) {
        item = (u16 *)entry;
        item_index = 0;
        while (item_index < entry[2]) {
            fn_8006E250(entry + 0x10, (u8 *)base + item[2] * 0x40);
            item++;
            item_index++;
        }
        entry_index++;
        entry += 0x44;
    }
}
/* fzgx:end fn_1_109114 */

/* fzgx:begin fn_1_10B7D8 */
// Initializes accessory data only when an accessory object is present.
void fn_1_10B7D8(void *accessory) {
    if (accessory != 0) {
        fn_1_10846C();
    }
}
/* fzgx:end fn_1_10B7D8 */

/* fzgx:begin fn_1_10C7B4 */
extern void *fn_80077B14(void *);
extern void lbl_8006DBAC(void *);
extern void lbl_8006DAEC(void);
extern void lbl_8006DBE4(void);
extern void lbl_8006E1B0(void *, void *);
extern void lbl_8006DC20(void);
extern void fn_8006E250(void *, void *);
extern const f64 lbl_1_rodata_7BF8;

typedef struct {
    u8 pad_0[0x150];
    struct {
        u8 pad_0[8];
        u8 *unk_8;
    } *unk_150;
} AccessoryData;

typedef struct {
    u8 unk_0;
    u8 pad_1[7];
    u32 unk_8;
    AccessoryData *unk_C;
    void *unk_10;
    u8 pad_14[4];
    u32 unk_18;
    u8 pad_1C[8];
    u8 *unk_24;
} AccessoryObject;

typedef union {
    u32 raw;
    f32 value;
} FloatVal;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Fn1_10C7B4_Triple;

typedef struct {
    u8 pad_0[0x10];
    FloatVal unk_10;
    FloatVal unk_14;
    FloatVal unk_18;
    FloatVal unk_1C;
    FloatVal unk_20;
    FloatVal unk_24;
    u8 pad_28[0xC];
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
} AccessoryItem;

void fn_1_10C7B4(AccessoryObject *self) {
    if (self != 0) {
        if (self->unk_10 != 0) {
            fn_80077B14(self->unk_10);
            if (self->unk_0 & 2) {
                AccessoryItem *item;
                u32 i;

                self->unk_0 &= ~2;
                lbl_8006DBAC(self->unk_C->unk_150->unk_8 +
                    ((u32 *)&lbl_1_data_3FFBC)[self->unk_8] * 0x18c + 0x88);
                lbl_8006DAEC();
                item = (AccessoryItem *)self->unk_24;
                i = 0;
                while (i < self->unk_18) {
                    lbl_8006DBE4();
                    lbl_8006E1B0((u8 *)item + 0x28, (u8 *)item + 0x10);
                    i++;
                    item = (AccessoryItem *)((u8 *)item + 0x44);
                }
                lbl_8006DC20();
            }

            {
                Fn1_10C7B4_Triple *src;
                u32 j;
                AccessoryItem *dst = (AccessoryItem *)self->unk_24;
                j = 0;
                src = (Fn1_10C7B4_Triple *)&lbl_1_bss_88B50;
                while (j < self->unk_18) {
                    *(Fn1_10C7B4_Triple *)&dst->unk_10 = src[j];
                    dst->unk_14.value = dst->unk_14.value - lbl_1_rodata_7BF8;
                    j++;
                    dst = (AccessoryItem *)((u8 *)dst + 0x44);
                }
            }

            {
                u32 k;
                AccessoryItem *dst = (AccessoryItem *)self->unk_24;
                for (k = 0; k < self->unk_18; k++) {
                    dst->unk_34 = dst->unk_10.value - dst->unk_1C.value;
                    dst->unk_38 = dst->unk_14.value - dst->unk_20.value;
                    dst->unk_3C = dst->unk_18.value - dst->unk_24.value;
                    dst = (AccessoryItem *)((u8 *)dst + 0x44);
                }
            }

            {
                u8 *base = (u8 *)fn_80077B14(self->unk_10);
                u8 *entry;
                int m;
                u32 n;
                u8 *p;

                lbl_8006DBAC(self->unk_C->unk_150->unk_8 +
                    ((u32 *)&lbl_1_data_3FFBC)[self->unk_8] * 0x18c + 0x88);
                entry = self->unk_24;
                n = 0;
                while (n < self->unk_18) {
                    p = entry;
                    for (m = 0; m < entry[2]; m++) {
                        fn_8006E250(entry + 0x10, base + *(u16 *)(p + 4) * 0x40);
                        p += 2;
                    }
                    n++;
                    entry += 0x44;
                }
            }
        }
    }
}
/* fzgx:end fn_1_10C7B4 */

/* fzgx:begin fn_1_1154D0 */
typedef struct {
    u8 active;
    u8 _pad01[0x33];
    f32 field34;
    u8 _pad38[4];
    f32 field3c;
    f32 field40;
} Fn1154D0Entry;

typedef struct {
    u8 _pad00[0x18];
    u32 count;
    u8 _pad1c[8];
    Fn1154D0Entry *entries;
} Fn1154D0Object;

void fn_1_1154D0(Fn1154D0Object *obj) {
    f32 inactive_value;
    f32 active_value;
    u32 i;
    Fn1154D0Entry *entry;

    if (obj != 0) {
        fn_1_10846C();
        active_value = lbl_1_rodata_7B1C;
        inactive_value = lbl_1_rodata_7B20;
        entry = obj->entries;
        for (i = 0; i < obj->count; i++, entry++) {
            if ((entry->active & 1) != 0) {
                entry->active = 0;
                entry->field40 = active_value;
            } else {
                entry->active = 1;
                entry->field40 = inactive_value;
                entry->field34 = inactive_value;
                entry->field3c = inactive_value;
            }
        }
    }
}
/* fzgx:end fn_1_1154D0 */

/* fzgx:begin fn_1_115B58 */
typedef struct {
    u8 active;
    u8 _pad01[0x33];
    f32 field34;
    u8 _pad38[4];
    f32 field3c;
    f32 field40;
} Fn115B58Entry;

typedef struct {
    u8 _pad00[0x18];
    u32 count;
    u8 _pad1c[8];
    Fn115B58Entry *entries;
} Fn115B58Object;

void fn_1_115B58(Fn115B58Object *obj) {
    f32 inactive_value;
    f32 active_value;
    u32 i;
    Fn115B58Entry *entry;

    if (obj != 0) {
        fn_1_10846C();
        active_value = lbl_1_rodata_7B1C;
        inactive_value = lbl_1_rodata_7B20;
        entry = obj->entries;
        for (i = 0; i < obj->count; i++, entry++) {
            if ((entry->active & 1) != 0) {
                entry->active = 1;
                entry->field40 = active_value;
            } else {
                entry->active = 0;
                entry->field40 = inactive_value;
                entry->field34 = inactive_value;
                entry->field3c = inactive_value;
            }
        }
    }
}
/* fzgx:end fn_1_115B58 */

/* fzgx:begin fn_1_1166EC */
typedef struct {
    u8 active;
    u8 _pad01[0x33];
    f32 field34;
    u8 _pad38[4];
    f32 field3c;
    f32 field40;
} Fn1166ECEntry;

typedef struct {
    u8 _pad00[0x18];
    u32 count;
    u8 _pad1c[8];
    Fn1166ECEntry *entries;
} Fn1166ECObject;

void fn_1_1166EC(Fn1166ECObject *obj) {
    f32 inactive_value;
    f32 active_value;
    u32 i;
    Fn1166ECEntry *entry;

    if (obj != 0) {
        fn_1_10846C();
        active_value = lbl_1_rodata_7B1C;
        inactive_value = lbl_1_rodata_7B20;
        entry = obj->entries;
        for (i = 0; i < obj->count; i++, entry++) {
            if ((entry->active & 1) != 0) {
                entry->active = 1;
                entry->field40 = active_value;
            } else {
                entry->active = 0;
                entry->field40 = inactive_value;
                entry->field34 = inactive_value;
                entry->field3c = inactive_value;
            }
        }
    }
}
/* fzgx:end fn_1_1166EC */

/* fzgx:begin fn_1_125CE8 noprologue */
#include "types.h"

extern f32 lbl_1_rodata_7AB8[];
extern void fn_1_10846C(void *);

typedef struct {
    u8 active;
    u8 pad_1[0x0f];
    f32 value;
    u8 pad_14[0x2c];
    f32 result;
} AccessoryEntry;

typedef struct {
    u8 pad_0[0x18];
    u32 count;
    u8 pad_1c[0x08];
    AccessoryEntry *entries;
} AccessoryData;

void fn_1_125CE8(AccessoryData *data) {
    f32 *constants;
    u32 i;
    AccessoryEntry *entry;
    f32 min_value;
    f32 max_value;
    f32 range;
    f32 value_off;
    f32 value_on;

    constants = lbl_1_rodata_7AB8;
    if (data != 0) {
        fn_1_10846C(data);

        i = 0;
        entry = data->entries;
        value_on = constants[25];
        value_off = constants[26];
        while (i < data->count) {
            if ((entry->active & 1) != 0) {
                entry->result = value_on;
                entry->active = 0;
            } else {
                entry->result = value_off;
                entry->active = 1;
            }
            i++;
            entry++;
        }

        entry = data->entries;
        min_value = constants[329];
        max_value = constants[330];
        i = 0;
        while (i < data->count) {
            if (entry->value < min_value) {
                min_value = entry->value;
            }
            if (entry->value > max_value) {
                max_value = entry->value;
            }
            i++;
            entry++;
        }

        range = max_value - min_value;
        value_on = constants[25];
        entry = data->entries;
        i = 0;
        while (i < data->count) {
            entry->result = value_on +
                (entry->value - min_value) / range;
            i++;
            entry++;
        }
    }
}
/* fzgx:end fn_1_125CE8 */

/* fzgx:begin fn_1_127FB8 */
extern void fn_1_10846C(void);
extern f32 lbl_1_rodata_7B20;

typedef struct {
    u8 active;
    u8 _pad01[0x3f];
    f32 value;
} Fn127FB8Entry;

typedef struct {
    u8 _pad00[0x18];
    u32 count;
    u8 _pad1c[8];
    Fn127FB8Entry *entries;
} Fn127FB8Object;

void fn_1_127FB8(Fn127FB8Object *obj) {
    f32 value;
    u32 i;
    Fn127FB8Entry *entry;

    if (obj != 0) {
        fn_1_10846C();
        entry = obj->entries;
        value = lbl_1_rodata_7B20;
        i = 0;
        while (i < obj->count) {
            if ((entry->active & 1) != 0) {
                entry->active = 0;
                entry->value = value;
            } else {
                entry->active = 1;
                entry->value = value;
            }
            i++;
            entry++;
        }
    }
}
/* fzgx:end fn_1_127FB8 */

/* fzgx:begin fn_1_128884 */
extern void fn_80008BA8(void *dst, void *src, int size);
extern void *fn_1_45D0(void *manager, int type, void *data, int code);
extern void fn_1_46B4(void *manager, void *object, void *data, int code);
extern void *lbl_801A6410;

void fn_1_128884(void *arg0, void *arg1, int type) {
    u8 tmp1[0x44];
    u8 tmp2[0x0c];
    void *object;

    switch (type) {
    case 0x44: {
        u32 size = type;
        fn_80008BA8(tmp1, arg0, size);
        fn_80008BA8(arg0, arg1, size);
        fn_80008BA8(arg1, tmp1, size);
        break;
    }
    case 0x0c: {
        u32 size = type;
        fn_80008BA8(tmp2, arg0, size);
        fn_80008BA8(arg0, arg1, size);
        fn_80008BA8(arg1, tmp2, size);
        break;
    }
    default:
        object = fn_1_45D0(lbl_801A6410, type, &lbl_1_data_40530, 0x308d);
        fn_80008BA8(object, arg0, type);
        fn_80008BA8(arg0, arg1, type);
        fn_80008BA8(arg1, object, type);
        fn_1_46B4(lbl_801A6410, object, &lbl_1_data_40530, 0x3091);
        break;
    }
}
/* fzgx:end fn_1_128884 */

/* fzgx:begin fn_1_1289BC */
#include "rel/main_rel/cloth.h"

extern void fn_1_105744(void);
extern void fn_1_106DB4(void);
extern void fn_1_9D0EC(u32, u32, void*, void*);
extern void fn_1_103AA8(void);
extern u32 lbl_1_bss_85288[2];
extern void fn_1_103AD4(void);
extern void fn_1_105768(void);
extern void fn_1_9E5B8(void *);
extern struct fn_1_10240C_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_45D0(u32, u32, void *, u32);
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern u32 fn_80008BA8(u32, u32, u32);

typedef struct Point1024C4 {
    u8 pad[0x10];
    f32 v[3];
} Point1024C4;

f32 fn_1_1289BC(const Point1024C4 *a, const Point1024C4 *b) {
    f32 dz = a->v[2] - b->v[2];
    f32 dy = a->v[1] - b->v[1];
    f32 dx = a->v[0] - b->v[0];
    f32 result = dx * dx;
    result += dy * dy;
    result += dz * dz;
    return result;
}
/* fzgx:end fn_1_1289BC */

/* fzgx:begin fn_1_128B00 */
s32 fn_1_128B00(s16 value) {
    switch (value) {
    case 0:
        return 7;
    case 1:
        return 10;
    case 2:
        return 4;
    default:
        return fn_1_14D670();
    }
}
/* fzgx:end fn_1_128B00 */

/* fzgx:begin fn_1_128DD8 */
// Return the table index for a matching accessory value, or the first unused index.
u8 fn_1_128DD8(u8 value) {
    u8 *table;
    u8 index;
    u8 entry;

    table = (u8 *)&lbl_1_data_405C0;
    for (index = 0; index < 6; index++) {
        entry = table[index];
        if (entry == value) {
            return index;
        }
    }

    return index;
}
/* fzgx:end fn_1_128DD8 */

/* fzgx:begin fn_1_128E10 */
extern u8 lbl_1_rodata_8058[16];

#pragma pack(push, 1)
typedef struct {
    u32 word_0;
    u32 word_4;
    u32 word_8;
    u16 half_c;
    u8 byte_e;
} LookupTable;
#pragma pack(pop)

u8 fn_1_128E10(u8 value) {
    LookupTable table = *(LookupTable *)lbl_1_rodata_8058;
    u8 i;
    u8 entry;

    i = 1;
    while (i < 15) {
        entry = ((u8 *)&table)[i];
        if ((s32)entry == (s32)(value & 0xFF)) {
            break;
        }
        i++;
    }
    if (i == 15) {
        i = 0;
    }
    return i;
}
/* fzgx:end fn_1_128E10 */

/* fzgx:begin fn_1_128E8C */
typedef struct {
    u8 field_0;
    u8 field_1;
    u16 field_2;
    u8 field_4;
    u8 pad_5[3];
    u8 field_8;
    u8 field_9;
    u16 field_a;
    u8 field_c[3];
    u8 field_f;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 pad_13;
    u16 field_14;
    u8 pad_16[2];
    u16 field_18;
} FnData;

void fn_1_128E8C(u32 unused, FnData *data) {
    data->field_0 = 1;
    data->field_1 = 2;
    data->field_2 = 3;
    data->field_4 = 0;
    data->field_8 = lbl_801A66A0 % 255;
    data->field_9 = 1;
    data->field_f = 2;
    data->field_a = 1234;
    data->field_11 = 5;
    data->field_12 = 6;
    data->field_14 = 7;
    data->field_10 = 4;
    data->field_18 = 982;
}
/* fzgx:end fn_1_128E8C */

/* fzgx:begin fn_1_12A24C */
s8 fn_1_12A24C(s8 arg) {
    if ((s8)fn_1_86678((s32)arg) == -1) {
        return -1;
    }
    return arg;
}
/* fzgx:end fn_1_12A24C */

/* fzgx:begin fn_1_12A290 */
u32 fn_1_12A290(s32 index) {
    if (index == -1) {
        return 0;
    }
    return lbl_1_bss_897AC[index * 27 + 26];
}
/* fzgx:end fn_1_12A290 */

/* fzgx:begin fn_1_12A2B8 */
void fn_1_12A2B8(u32 value) {
    lbl_1_bss_897A4 = value;
}
/* fzgx:end fn_1_12A2B8 */

/* fzgx:begin fn_1_12A2C4 */
void fn_1_12A2C4(u32 value) {
    lbl_1_bss_897A8 = value;
}
/* fzgx:end fn_1_12A2C4 */
