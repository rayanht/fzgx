#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/shadowmap.h"

extern void fn_800746A8(u32, u32);
extern void fn_8007245C(u32);
extern void fn_800728A8(u32, u32, u32, u32);
extern void fn_800720B0(u32);
extern void fn_800747D0(u32, u32, u32, u32, u32, u32, u32);
extern void fn_800734A8(u32, u32, u32, u32);
extern void fn_80072EDC(u32, u32);
extern void fn_80073C6C(u32);
extern void fn_80073678(u32);
extern void fn_80074660(u32);
extern void fn_80073898(u32);
extern void fn_80074788(u32);

extern void *lbl_801A6410;
extern void fn_1_46B4(void *, void *, unsigned char *, int);

/* fzgx:begin fn_1_56858 */
typedef struct ShadowMapEntry {
    char pad_00[0x3c];
    void *unk_3c;
    void *unk_40;
    char pad_44[0x08];
} ShadowMapEntry;

// Register each entry's resources, then clear it for reuse.
void fn_1_56858(ShadowMapEntry *entries, u32 count) {
    u32 index;
    ShadowMapEntry *current_entry;

    for (index = 0, current_entry = entries; index < count;
         index++, current_entry++) {
        fn_1_46B4(lbl_801A6410, current_entry->unk_3c, lbl_1_data_1C660, 0x87);
        fn_1_46B4(lbl_801A6410, current_entry->unk_40, lbl_1_data_1C660, 0x88);
        memset(current_entry, 0, 0x4c);
    }
}
/* fzgx:end fn_1_56858 */

/* fzgx:begin fn_1_568EC */
typedef struct ShadowMap {
    u8 pad44[0x44];
    u32 field44;
    u32 field48;
} ShadowMap;

void fn_1_568EC(ShadowMap *map, u32 value0, u32 value1) {
    map->field48 = value0;
    map->field44 = value1;
}
/* fzgx:end fn_1_568EC */

/* fzgx:begin fn_1_57714 */
// Updates the shadow-map enable flag.
void fn_1_57714(u8 value) {
    lbl_1_data_1C670.unk_0 = value;
}
/* fzgx:end fn_1_57714 */

/* fzgx:begin fn_1_57720 */
void fn_1_57720(u32 value_1, u32 value_2, u32 value_3, u32 value_4) {
    lbl_1_data_1C670.unk_4 = value_1;
    lbl_1_data_1C670.unk_8 = value_2;
    lbl_1_data_1C670.unk_C = value_3;
    lbl_1_data_1C670.unk_10 = value_4;
}
/* fzgx:end fn_1_57720 */

/* fzgx:begin fn_1_57BBC */
typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
} Fn1_57BBC_ArgBlock;

typedef struct {
    u32 unk_0;
    void (*unk_4)(void);
    u8 pad_8[0x30];
    u32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    void *unk_40;
    Obj_1_data_1C670 unk_44;
} Fn1_57BBC_Object;

typedef struct {
    Fn1_57BBC_ArgBlock unk_0;
    Fn1_57BBC_ArgBlock unk_10;
} Fn1_57BBC_Data;

extern void *fn_1_548AC(u32 size);
extern void *fn_1_5448C(void *arg);
extern void fn_1_57E84(void);
extern void fn_1_5489C(void *arg0, void *arg1);
extern void lbl_8006DB74(void *arg);

void fn_1_57BBC(Fn1_57BBC_ArgBlock *arg0, Fn1_57BBC_ArgBlock *arg1) {
    Fn1_57BBC_Object *object;
    Fn1_57BBC_Data *data;
    void *value;

    object = fn_1_548AC(0x60);
    if (object == 0) {
        return;
    }

    data = fn_1_548AC(0x20);
    if (data == 0) {
        return;
    }

    value = fn_1_5448C(arg0);
    object->unk_4 = fn_1_57E84;
    object->unk_38 = 0xA8;
    object->unk_3C = 2;
    object->unk_44 = lbl_1_data_1C670;
    data->unk_0 = *arg0;
    data->unk_10 = *arg1;
    object->unk_40 = data;
    lbl_8006DB74(object->pad_8);
    fn_1_5489C(value, object);
}
/* fzgx:end fn_1_57BBC */

/* fzgx:begin fn_1_57DC0 */
void fn_1_57DC0(void) {
    fn_800746A8(lbl_1_data_1C670.unk_0, lbl_1_data_1C670.unk_14);
    fn_8007245C(0xa00);
    fn_800728A8(lbl_1_data_1C670.unk_4, lbl_1_data_1C670.unk_8,
                lbl_1_data_1C670.unk_C, lbl_1_data_1C670.unk_10);
    fn_800720B0(0);
    fn_800747D0(4, 0, 1, 1, 0, 2, 1);
    fn_800734A8(0, 0xff, 0xff, 4);
    fn_80072EDC(0, 4);
    fn_80073C6C(0);
    fn_80073678(1);
    fn_80074660(0);
    fn_80073898(0);
    fn_80074788(1);
}
/* fzgx:end fn_1_57DC0 */
