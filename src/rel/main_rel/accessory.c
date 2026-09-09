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
