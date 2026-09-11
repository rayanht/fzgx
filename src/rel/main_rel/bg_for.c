#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_for.h"

/* fzgx:begin fn_1_DCBF4 */
extern void OSPanic(const char *, int, const char *, ...);

#pragma opt_dead_assignments off
s32 fn_1_DCBF4(s32 value, s32 data) {
    Obj_1_data_2A7E0_At3C *obj;
    Obj_1_data_2A7E0_At3C *entry;
    u32 n;

    obj = lbl_1_data_2A7E0.unk_3C;
    switch (value) {
    case 0:
        obj->unk_1588 = data;
        break;
    case 1:
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x40000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x10000000;
        n = obj->unk_0;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + n * 0xAC);
        entry->unk_4 = data;
        obj->unk_0 = obj->unk_0 + 1;
        if ((s32)obj->unk_0 >= 0x20) {
            OSPanic((const char *)lbl_1_data_3DC78, 0x21D, (const char *)&lbl_1_data_3DC84);
        }
        break;
    case 2:
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x40000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x20000000;
        n = obj->unk_0;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + n * 0xAC);
        entry->unk_4 = data;
        obj->unk_0 = obj->unk_0 + 1;
        if ((s32)obj->unk_0 >= 0x20) {
            OSPanic((const char *)lbl_1_data_3DC78, 0x224, (const char *)&lbl_1_data_3DC84);
        }
        break;
    case 3:
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x40000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x10000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x08000000;
        n = obj->unk_0;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + n * 0xAC);
        entry->unk_4 = data;
        obj->unk_0 = obj->unk_0 + 1;
        if ((s32)obj->unk_0 >= 0x20) {
            OSPanic((const char *)lbl_1_data_3DC78, 0x22C, (const char *)&lbl_1_data_3DC84);
        }
        break;
    case 4:
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x40000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x20000000;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + obj->unk_0 * 0xAC);
        entry->unk_C |= 0x08000000;
        n = obj->unk_0;
        entry = (Obj_1_data_2A7E0_At3C *)((u8 *)obj + n * 0xAC);
        entry->unk_4 = data;
        obj->unk_0 = obj->unk_0 + 1;
        if ((s32)obj->unk_0 >= 0x20) {
            OSPanic((const char *)lbl_1_data_3DC78, 0x234, (const char *)&lbl_1_data_3DC84);
        }
        break;
    }
    return 1;
}
#pragma opt_dead_assignments reset
/* fzgx:end fn_1_DCBF4 */

/* fzgx:begin fn_1_DCE60 */
struct fn_1_DCE60_Arg0 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
};
struct fn_1_DCE60_Copy24 { u32 a[6]; };
struct fn_1_DCE60_Copy12 { u32 a[3]; };
struct fn_1_DCE60_lbl_1_rodata_6750 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
};

extern struct fn_1_DCE60_lbl_1_rodata_6750 lbl_1_rodata_6750;

#pragma opt_propagation off
f32 fn_1_DCE60(struct fn_1_DCE60_Arg0 *arg0, f32 arg1) {
    u32 v0;
    u32 v4;
    f32 v3;
    f32 v2;
    f32 v1;

    v4 = lbl_1_rodata_6750.unk_0;
    v0 = lbl_1_rodata_6750.unk_4;
    v1 = lbl_1_rodata_6750.unk_24;
    arg0->unk_0 = v4;
    v2 = lbl_1_rodata_6750.unk_28;
    arg0->unk_4 = v0;
    v3 = lbl_1_rodata_6750.unk_2C;
    arg0->unk_8 = lbl_1_rodata_6750.unk_8;
    *(struct fn_1_DCE60_Copy12 *)((u8 *)(u32)arg0 + 24) = *(struct fn_1_DCE60_Copy12 *)((u8 *)&lbl_1_rodata_6750 + 12);
    *(struct fn_1_DCE60_Copy12 *)((u8 *)(u32)arg0 + 36) = *(struct fn_1_DCE60_Copy12 *)((u8 *)&lbl_1_rodata_6750 + 24);
    arg0->unk_30 = v1;
    arg0->unk_34 = arg1;
    arg0->unk_38 = v2;
    arg0->unk_3C = v3;
    return arg1;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_DCE60 */

/* fzgx:begin fn_1_DCED0 */
extern void lbl_8006DAEC(void);
extern void lbl_8006DD14(void *, void *);
extern void fn_1_A7024(f32, f32, f32, f32);
extern void fn_8006F1F0(void *, void *, void *);
extern void lbl_8006DB74(void *);
extern void lbl_8006DCDC(void);
extern void lbl_8006DB30(void);

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct BgForObject {
    Vec3 value00;
    Vec3 value0c;
    u8 unk18[0xc];
    u32 value24;
    u8 unk28[0x8];
    f32 value30;
    f32 value34;
    f32 value38;
    f32 value3c;
    u8 unk40[0x30];
    u8 unk70[1];
} BgForObject;

void fn_1_DCED0(BgForObject *object) {
    lbl_8006DAEC();
    object->value0c = object->value00;
    lbl_8006DD14(&object->unk70, &object->unk40);
    fn_1_A7024(object->value30, object->value34, object->value38, object->value3c);
    fn_8006F1F0(object, &object->value24, &object->unk18);
    lbl_8006DB74(&object->unk70);
    lbl_8006DCDC();
    lbl_8006DB30();
}
/* fzgx:end fn_1_DCED0 */

/* fzgx:begin fn_1_DCF54 */
typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct State {
    Vec3 a;
    u8 pad[12];
    Vec3 b;
    Vec3 c;
} State;

extern State lbl_1_bss_7ADE8;

void fn_1_DCF54(Vec3 *a, Vec3 *b, Vec3 *c) {
    lbl_1_bss_7ADE8.a = *a;
    lbl_1_bss_7ADE8.b = *b;
    lbl_1_bss_7ADE8.c = *c;
}
/* fzgx:end fn_1_DCF54 */

/* fzgx:begin fn_1_E1934 */
extern void fn_1_E1408(void *, void *);

typedef struct {
    u8 pad0[0x8];
    s16 field8;
    s16 fieldA;
    u8 padC[0x12c];
    u64 field138;
    u8 pad140[0x68];
} Fn1E1934Object;

void fn_1_E1934(Fn1E1934Object *obj, Fn1E1934Object *base, s16 limit) {
    s16 index;

    if ((obj->field138 & 0x40) != 0) {
        return;
    }

    if (obj->fieldA != base->fieldA) {
        index = 0;
    } else {
        index = obj->field8 + 1;
    }

    while ((s16)index < limit) {
        fn_1_E1408(obj, &base[index]);
        index++;
    }
}
/* fzgx:end fn_1_E1934 */
