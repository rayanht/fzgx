#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/car_test.h"

extern void fn_1_5634C(u32 arg0);
extern void fn_1_7ECB8(u32 arg0, u32 arg1, u32 arg2);
extern void *lbl_801A6410;
extern const f64 lbl_1_rodata_3588;
extern void fn_1_12AB38(const char *);
extern void *fn_1_45D0(void *, s32, const char *, s32);
extern void fn_80008BEC(void *, s32, s32);
extern void fn_1_80F80(void *, u8, void *);
extern void fn_1_1502BC(void *, void *, void *);

extern void fn_80083DB0(void* arg0, u32 arg1);
extern void fn_1_801F8(s16 arg0, void* arg1);
extern const f32 lbl_1_rodata_33AC;
extern void *fn_1_4630(void *arg0, u32 arg1, void *arg2, u32 arg3);
extern const f32 lbl_1_rodata_33B0[84];
extern void *memset(void *dst, int value, u32 size);
extern void fn_1_46B4(void *arg0, void *arg1, u8 *arg2, s32 arg3);
extern void fn_1_7F954(void *arg0, s32 arg1);
extern void fn_1_49614(void);
extern const f32 lbl_1_rodata_33A8;
extern void fn_80071ED4(s32 arg0, f32 arg1, f32 arg2);
extern void fn_80072014(void *arg0);
extern void fn_800720B0(s32 arg0);

/* fzgx:begin fn_1_7C13C */
#include "types.h"

typedef struct {
    u8 pad_32c[0x32c];
    void *field_32c;
    u8 pad_330[0x110];
} Fn17C13CEntry;

typedef struct {
    u8 pad_4[4];
    u16 field_4;
    u16 field_6;
    u8 pad_8[0x17c];
    f32 field_184;
} Fn17C13CObject;

void fn_1_7C13C(Fn17C13CEntry *arg0) {
    f32 value;
    Fn17C13CEntry *p;
    int i;

    value = 100.0f;
    p = arg0;
    for (i = 0; i < 0x29; i++) {
        p->field_32c = fn_1_4630((*(u8 * *)&lbl_801A6410), 0x620, (*(u8 (*)[128])&lbl_1_data_1EF5C), 0x58);
        ((Fn17C13CObject *)p->field_32c)->field_6 = (u16)i;
        ((Fn17C13CObject *)p->field_32c)->field_4 = (u16)i;
        ((Fn17C13CObject *)p->field_32c)->field_184 = value;
        p++;
    }
}
/* fzgx:end fn_1_7C13C */

/* fzgx:begin fn_1_7C1E8 */
void fn_1_7C1E8(void *out) {
    u8 *p;
    s8 i;

    p = (u8 *)out;
    for (i = 0; i < 2; i++) {
        *(u32 *)p = (u32)fn_1_4630(lbl_801A6410, 4, (*(u8 (*)[128])&lbl_1_data_1EF5C), 0x68);
        memset(*(void **)p, 0xff, 4);
        *(f32 *)(p + 4) = lbl_1_rodata_33B0[0];
        *(u16 *)(p + 8) = 0xE000;
        *(s16 *)(p + 10) = 0x2000;
        p += 0xc;
    }
}
/* fzgx:end fn_1_7C1E8 */

/* fzgx:begin fn_1_7D694 */
typedef struct {
    u8 _pad4[4];
    s16 value;
} Entry;

typedef struct {
    u8 _pad32c[0x32c];
    Entry *entry;
} Object;

typedef struct {
    u8 _pad7[7];
    s8 value;
} GlobalEntry;

// Compares the object's entry selector with the active global selector.
void fn_1_7D694(Object *obj) {
    Entry *entry = obj->entry;
    GlobalEntry *active = *(GlobalEntry **)&lbl_1_bss_6D7E8;

    if (entry->value == active->value) {
        return;
    }
}
/* fzgx:end fn_1_7D694 */

/* fzgx:begin fn_1_7E7A4 */
typedef struct Fn1_7E7A4Data {
    void *field_0;
    u8 pad_4[8];
    void *field_c;
    u8 pad_10[8];
    void *field_18;
    void *field_1c;
} Fn1_7E7A4Data;

void fn_1_7E7A4(Fn1_7E7A4Data *arg0) {
    s8 i;
    u32 offset;

    for (i = 0, offset = 0; i < 0x29; offset += 0x440, i++) {
        fn_1_46B4(
            lbl_801A6410,
            *(void **)(((((((0x32c) + ((u8 *)arg0->field_0)))) + ((offset))))),
            (*(u8 (*)[128])&lbl_1_data_1EF5C),
            0x313);
    }

    fn_1_7F954(arg0->field_0, 0x29);

    for (i = 0; i < 2; i++) {
        fn_1_46B4(
            lbl_801A6410,
            *(void **)((u8 *)arg0->field_1c + i * 0xc),
            (*(u8 (*)[128])&lbl_1_data_1EF5C),
            0x321);
    }

    fn_1_46B4(lbl_801A6410, arg0->field_18, (*(u8 (*)[128])&lbl_1_data_1EF5C), 0x324);
    fn_1_46B4(lbl_801A6410, arg0->field_c, (*(u8 (*)[128])&lbl_1_data_1EF5C), 0x325);
    fn_1_46B4(lbl_801A6410, arg0, (*(u8 (*)[128])&lbl_1_data_1EF5C), 0x326);
    fn_1_49614();
    fn_80074D68(lbl_1_rodata_33A8, lbl_1_rodata_33A8, lbl_1_rodata_33A8);
    fn_80074D78(1);
}
/* fzgx:end fn_1_7E7A4 */

/* fzgx:begin fn_1_7EAE8 */
// fn_1_7EAE8: main_rel .text:0x0007EAE8 size 0x24
// Wrapper that calls fn_1_5634C with argument 0.

void fn_1_7EAE8(void) {
    fn_1_5634C(0);
}
/* fzgx:end fn_1_7EAE8 */

/* fzgx:begin fn_1_7EB0C */
typedef struct {
    s8 unk_0;
} SignedByteView;

typedef struct {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
} LocalBytes;

void fn_1_7EB0C(void) {
    LocalBytes local0;
    LocalBytes local1;

    local0.unk_0 = lbl_1_bss_6D7F4.unk_C;
    local0.unk_1 = lbl_1_bss_6D7F4.unk_D;
    local0.unk_2 = lbl_1_bss_6D7F4.unk_E;
    if ((s8)lbl_1_bss_6D7F4.unk_F != 0) {
        fn_80071ED4(((SignedByteView *)&lbl_1_bss_6D7F4)->unk_0 + 0,
                    lbl_1_bss_6D7F4.unk_4,
                    lbl_1_bss_6D7F4.unk_8);
        local1 = local0;
        fn_80072014(&local1);
        fn_800720B0(1);
    } else {
        fn_800720B0(0);
    }
}
/* fzgx:end fn_1_7EB0C */

/* fzgx:begin fn_1_7F1E8 */
void fn_1_7F1E8(u32 arg0, u32 arg1) {
    fn_1_7ECB8(arg0, arg1, 0x80000000); // fzgx-allow: A1 retail sentinel
}
/* fzgx:end fn_1_7F1E8 */

/* fzgx:begin fn_1_7F20C */
void fn_1_7F20C(u32 arg0, u32 arg1) {
    fn_1_7ECB8(arg0, arg1, 0x40000000); // fzgx-allow: A1 retail sentinel
}
/* fzgx:end fn_1_7F20C */

/* fzgx:begin fn_1_7F230 */
void fn_1_7F230(u32 arg0, u32 arg1) {
    fn_1_7ECB8(arg0, arg1, 0);
}
/* fzgx:end fn_1_7F230 */

/* fzgx:begin fn_1_7F254 */
void *fn_1_7F254(void *arg0, void *arg1) {
    u8 kind = ((u8 *)arg0)[5];
    s16 type;
    void *result;
    char *data = (char *)&lbl_1_data_1F1D8;

    if (kind == 4) {
        type = 2;
    } else if (kind == 0x28 || kind >= 0x29) {
        type = 3;
    } else {
        type = 1;
    }

    if ((((u32 *)arg0)[0] & 0x40000000) == 0) {
        fn_1_12AB38(data + 0xe0c);
        result = fn_1_45D0(lbl_801A6410, type * 0x30, data + 0xe18, 0x1d5);
        fn_80008BEC(result, 0, type * 0x30);
        fn_1_80F80(result, ((u8 *)arg0)[0x81a0], arg1);
        fn_1_12AB38(data + 0xe20);
    } else {
        struct {
            u16 a;
            u16 b;
            u16 c;
        } info;
        *(u32 *)&info = ((const u32 *)&lbl_1_rodata_3588)[0];
        info.c = ((const u16 *)&lbl_1_rodata_3588)[2];
        info.a = ((u8 *)arg0)[0x81a4];
        info.b = ((u8 *)arg0)[0x81ac];
        info.c = ((u8 *)arg0)[0x81b4];
        result = fn_1_45D0(lbl_801A6410, 0x90, data + 0xe18, 0x1e2);
        fn_80008BEC(result, 0, 0x90);
        fn_1_1502BC(result, &info, arg1);
    }
    return result;
}
/* fzgx:end fn_1_7F254 */

/* fzgx:begin fn_1_7F518 */
// Initializes the car test entry and optionally performs its follow-up setup.
void* fn_1_7F518(s16 car_type, void* car, s32 initialize) {
    fn_80083DB0(car, ((u32 *)lbl_1_data_1F4FC)[car_type]);
    if (initialize == 1) {
        fn_1_801F8(car_type, car);
    }
    return car;
}
/* fzgx:end fn_1_7F518 */

/* fzgx:begin fn_1_8CA00 */
u32 *fn_1_8CA00(void) {
    return &lbl_1_data_1FFDC;
}
/* fzgx:end fn_1_8CA00 */
