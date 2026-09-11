#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_for.h"

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
