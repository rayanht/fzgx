#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/driver.h"

extern void *lbl_801A6410;
extern void fn_80071718(void *value);
extern void fn_800711A8(void *value);
extern void fn_1_46B4(void *arg0, void *arg1, void *arg2, s32 arg3);
extern void fn_1_A7E60(s32 arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void lbl_8006DAEC(void);
extern void lbl_8006DBAC(void *arg0);
extern void lbl_8006E0A4(void *arg0);
extern void fn_8006F6A8(void *arg0);
extern void lbl_8006DB30(void);
extern void fn_1_A861C(void *arg0, void *arg1);
extern void fn_1_A8834(void *arg0, void *arg1);
extern void fn_1_A89B0(void *arg0, void *arg1, s32 arg2);
extern void fn_1_3920(void);
extern void fn_1_A8D4C(void);
extern void fn_1_A8D64(void);
extern void fn_8001A78C(void (*func)(void));
extern void fn_8001A7D0(void (*func)(void));
extern void fn_1_A9420(u8 value);
extern void fn_1_A948C(int);
extern void fn_1_A943C(int, int);
extern void fn_1_A9464(u16 arg0, u16 arg1);
extern void fn_1_A942C(u8 value);
extern void fn_1_A96BC(void);
extern void (*lbl_1_bss_7167C)(void);
extern void fn_1_A5C98(void *);
extern u8 lbl_1_bss_716C8[320];

extern void (*lbl_1_bss_71680)(void);

extern void (*lbl_1_bss_7167C)(void);
extern void fn_1_A9420(u8 value);
extern void fn_1_A9464(u16 arg0, u16 arg1);
extern u32 fn_1_451C(void);
extern void sprintf(void *buffer, char *format, ...);
extern void fn_1_A5AA0(void *buffer, void *destination);
extern u32 lbl_1_bss_71670;

extern void (*lbl_1_bss_71684)(void);

extern void (*lbl_1_bss_71688)(void);

extern void (*lbl_1_bss_7168C)(void);
extern void fn_1_A8528(void *arg0, void *arg1);
extern u32 fn_1_A7024(f32, f32, f32, f32);
extern u32 fn_80074918(u32, u32, u32);

/* fzgx:begin fn_1_A7728 */
typedef struct FnA7728Resource {
    u8 pad_104[0x104];
    void *field_104;
    void *field_108;
} FnA7728Resource;

typedef struct FnA7728Object {
    u8 pad_394[0x394];
    FnA7728Resource *field_394;
} FnA7728Object;

void fn_1_A7728(FnA7728Object *objects) {
    u8 *object;
    s32 index;

    object = (u8 *)objects;
    index = 0;
    for (;;) {
        if (((FnA7728Object *)object)->field_394 != 0) {
            if (((FnA7728Object *)object)->field_394->field_108 != 0) {
                fn_80071718(((FnA7728Object *)object)->field_394->field_108);
                ((FnA7728Object *)object)->field_394->field_108 = 0;
            }
            if (((FnA7728Object *)object)->field_394->field_104 != 0) {
                fn_800711A8(((FnA7728Object *)object)->field_394->field_104);
                ((FnA7728Object *)object)->field_394->field_104 = 0;
            }
            fn_1_46B4(lbl_801A6410, ((FnA7728Object *)object)->field_394,
                      lbl_1_data_34354, 0x115);
            ((FnA7728Object *)object)->field_394 = 0;
        }
        index++;
        object += 4;
        if (index >= 3) {
            break;
        }
    }
}
/* fzgx:end fn_1_A7728 */

/* fzgx:begin fn_1_A77DC */
typedef struct FnA77DCObject {
    u8 pad_32c[0x32c];
    void *field_32c;
    u8 pad_330[0x64];
    void *field_394[3];
    u8 pad_3a0[0x1a];
    s16 field_3ba;
} FnA77DCObject;

void fn_1_A77DC(FnA77DCObject *object) {
    s32 index;

    if (object->field_3ba == 0 || object->field_3ba == 1) {
        for (index = 0; index < 3; index++) {
            if (object->field_394[index] != 0) {
                fn_1_A8528(object->field_394[index], object->field_32c);
            }
        }
    }
}
/* fzgx:end fn_1_A77DC */

/* fzgx:begin fn_1_A7854 */
typedef struct FnA7854Object {
    u8 pad_394[0x394];
    void *item;
    u8 pad_398[0x22];
    s16 field_3ba;
} FnA7854Object;

extern void fn_1_A8270(void *arg0, void *arg1);

void fn_1_A7854(FnA7854Object *object, void *arg1) {
    FnA7854Object *cursor;
    s32 index;

    if (object->field_3ba == 0 || object->field_3ba == 1) {
        index = 0;
        cursor = object;
        do {
            if (cursor->item != 0) {
                fn_1_A8270(cursor->item, arg1);
            }
            index++;
            cursor = (FnA7854Object *)((u8 *)cursor + 4);
        } while (index < 3);
    }
}
/* fzgx:end fn_1_A7854 */

/* fzgx:begin fn_1_A78CC */
extern u8 lbl_1_data_34354[72];
extern void *lbl_801A6410;
extern void *fn_1_4630(void *arg0, s32 arg1, void *arg2, s32 arg3);

void fn_1_A78CC(void) {
    u32 **table;
    s32 offset;
    s32 index;

    lbl_1_bss_6F638 = (u32)fn_1_4630(lbl_801A6410, 0xb0, lbl_1_data_34354, 0x145);
    table = (u32 **)&lbl_1_bss_6F638;
    index = 0;
    offset = 0;
    do {
        *(u32 *)((u8 *)*table + offset) =
            (u32)fn_1_4630(lbl_801A6410, 0x30c, lbl_1_data_34354, 0x147);
        index++;
        offset += 4;
    } while (index < 0x2c);
}
/* fzgx:end fn_1_A78CC */

/* fzgx:begin fn_1_A7968 */
void fn_1_A7968(void) {
    s32 **table;
    s32 offset;
    s32 index;

    table = (s32 **)&lbl_1_bss_6F638;
    offset = 0;
    index = 0;
    do {
        fn_1_A7E60(41, (s8)index, *(s32 *)((u8 *)*table + offset), -1, 0);
        index++;
        offset += 4;
    } while (index < 44);
}
/* fzgx:end fn_1_A7968 */

/* fzgx:begin fn_1_A7A70 */
void fn_1_A7A70(void) {
    s32 index;
    u32 *entries;

    for (index = 0; index < 0x2c; index++) {
        entries = (u32 *)lbl_1_bss_6F638;
        if (entries[index] != 0) {
            fn_1_46B4(lbl_801A6410, (void *)entries[index],
                      lbl_1_data_34354, 0x168);
            entries = (u32 *)lbl_1_bss_6F638;
            entries[index] = 0;
        }
    }

    if (lbl_1_bss_6F638 != 0) {
        fn_1_46B4(lbl_801A6410, (void *)lbl_1_bss_6F638,
                  lbl_1_data_34354, 0x169);
        lbl_1_bss_6F638 = 0;
    }
}
/* fzgx:end fn_1_A7A70 */

/* fzgx:begin fn_1_A7B30 noprologue */
#include "types.h"

typedef struct FnA7B30Vector {
    s32 x;
    s32 y;
    s32 z;
} FnA7B30Vector;

extern FnA7B30Vector lbl_1_data_35864[];

void fn_1_A7B30(s32 index, FnA7B30Vector *out) {
    *out = lbl_1_data_35864[index - 25];
}
/* fzgx:end fn_1_A7B30 */

/* fzgx:begin fn_1_A7F84 noprologue */
#include "types.h"

struct fn_1_A7F84_lbl_1_rodata_4A28 {
    f32 unk_0;
};
struct fn_1_A7F84_lbl_801A6D00 {
    u32 unk_0;
};
extern struct fn_1_A7F84_lbl_1_rodata_4A28 lbl_1_rodata_4A28;
extern struct fn_1_A7F84_lbl_801A6D00 lbl_801A6D00;
extern u32 jumptable_1_data_3439C;
extern u32 lbl_8006D91C(u32);
extern u32 mathutil_mtxA_rotate_y(u32);
extern void mathutil_mtxA_rotate_x(u32);
extern u32 lbl_8006D998(u32);


void fn_1_A7F84(void *arg0, u32 arg1) {
    switch (arg1) {
    case 0:
        lbl_8006D91C(0U);
        mathutil_mtxA_rotate_y(0U);
        mathutil_mtxA_rotate_x((u32) (*(s16 *)((u8 *)(arg0) + 0)));
        return;
    case 1:
        lbl_8006D91C(0x4000U);
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 2)));
        mathutil_mtxA_rotate_x(0x4000U);
        return;
    case 2:
        lbl_8006D998(0x4000U);
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 4)));
        mathutil_mtxA_rotate_x(0U);
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) lbl_1_rodata_4A28.unk_0;
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 28));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 32));
        return;
    case 3:
        lbl_8006D998((u32) (*(s16 *)((u8 *)(arg0) + 10)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 8)));
        mathutil_mtxA_rotate_x((u32) (*(s16 *)((u8 *)(arg0) + 6)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) (*(f32 *)((u8 *)(arg0) + 36));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 40));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 44));
        return;
    case 4:
        lbl_8006D998((u32) (*(s16 *)((u8 *)(arg0) + 16)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 14)));
        mathutil_mtxA_rotate_x((u32) (*(s16 *)((u8 *)(arg0) + 12)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) (*(f32 *)((u8 *)(arg0) + 48));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 52));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 56));
        return;
    case 5:
        lbl_8006D998((u32) (s16) (-0x4000 - ((*(s16 *)((u8 *)(arg0) + 10)) + 0x4000)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 8)));
        mathutil_mtxA_rotate_x((u32) (s16) (-0x4000 - ((*(s16 *)((u8 *)(arg0) + 6)) + 0x4000)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) -(*(f32 *)((u8 *)(arg0) + 36));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 40));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 44));
        return;
    case 6:
        lbl_8006D998((u32) (s16) (0x4000 - ((*(s16 *)((u8 *)(arg0) + 16)) - 0x4000)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 14)));
        mathutil_mtxA_rotate_x((u32) (s16) (0x4000 - ((*(s16 *)((u8 *)(arg0) + 12)) - 0x4000)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) -(*(f32 *)((u8 *)(arg0) + 48));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 52));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 56));
        return;
    case 7:
        lbl_8006D91C(-0x4000U);
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 18)));
        mathutil_mtxA_rotate_x(-0x4000U);
        return;
    case 8:
        lbl_8006D998((u32) (s16) (0x4000 - ((*(s16 *)((u8 *)(arg0) + 24)) - 0x4000)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 22)));
        mathutil_mtxA_rotate_x((u32) (s16) (0x4000 - ((*(s16 *)((u8 *)(arg0) + 20)) - 0x4000)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) -(*(f32 *)((u8 *)(arg0) + 60));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 64));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 68));
        return;
    case 9:
        lbl_8006D998((u32) (*(s16 *)((u8 *)(arg0) + 24)));
        mathutil_mtxA_rotate_y((u32) (*(s16 *)((u8 *)(arg0) + 22)));
        mathutil_mtxA_rotate_x((u32) (*(s16 *)((u8 *)(arg0) + 20)));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 12)) = (f32) (*(f32 *)((u8 *)(arg0) + 60));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 28)) = (f32) (*(f32 *)((u8 *)(arg0) + 64));
        (*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 44)) = (f32) (*(f32 *)((u8 *)(arg0) + 68));
        /* fallthrough */
    default:
        return;
    }
}
/* fzgx:end fn_1_A7F84 */

/* fzgx:begin fn_1_A8528 */
typedef struct FnA8528Object {
    u8 pad_ea[0xea];
    s16 unk_ea;
    s16 unk_ec;
    s16 unk_ee;
    f32 unk_f0;
    f32 unk_f4;
    f32 unk_f8;
    u8 pad_fc[0x18];
    u8 unk_114[0xc];
    u8 unk_120[0x4];
} FnA8528Object;

typedef struct FnA8528Config {
    u8 pad_0c[0x0c];
    f32 unk_0c;
    u8 pad_10[0x0c];
    f32 unk_1c;
    u8 pad_20[0x0c];
    f32 unk_2c;
} FnA8528Config;

extern FnA8528Config *lbl_801A6D00;

// Initializes the driver's state from the active configuration and shared systems.
void fn_1_A8528(void *arg0, void *arg1) {
    s16 orientation[3];
    void *driver_data;

    if (arg1 != 0) {
        driver_data = (u8 *)arg1 + 0x14c;
    } else {
        driver_data = lbl_801A6D00;
    }

    lbl_8006DAEC();
    lbl_8006DBAC(driver_data);
    lbl_8006E0A4(((FnA8528Object *)arg0)->unk_114);
    lbl_8006E0A4(((FnA8528Object *)arg0)->unk_120);
    fn_8006F6A8(orientation);

    ((FnA8528Object *)arg0)->unk_f0 = lbl_801A6D00->unk_0c;
    ((FnA8528Object *)arg0)->unk_f4 = lbl_801A6D00->unk_1c;
    ((FnA8528Object *)arg0)->unk_f8 = lbl_801A6D00->unk_2c;
    ((FnA8528Object *)arg0)->unk_ec = orientation[0];
    ((FnA8528Object *)arg0)->unk_ea = orientation[1];
    ((FnA8528Object *)arg0)->unk_ee = orientation[2];

    fn_1_A861C(arg0, arg1);
    fn_1_A8834(arg0, arg1);
    fn_1_A89B0(arg0, arg1, 1);
    fn_1_A89B0(arg0, arg1, 0);
    lbl_8006DB30();
}
/* fzgx:end fn_1_A8528 */

/* fzgx:begin fn_1_A8D4C */
void fn_1_A8D4C(void) {
    lbl_1_bss_6F640 += 1;
}
/* fzgx:end fn_1_A8D4C */

/* fzgx:begin fn_1_A8D64 */
void fn_1_A8D64(void) {
    fn_1_3920();
}
/* fzgx:end fn_1_A8D64 */

/* fzgx:begin fn_1_A8D84 */
void fn_1_A8D84(void) {
    lbl_1_bss_6F640 = 0;
    fn_8001A78C(fn_1_A8D4C);
    fn_8001A7D0(fn_1_A8D64);
}
/* fzgx:end fn_1_A8D84 */

/* fzgx:begin fn_1_A8DC4 */
// Returns the current driver state handle.
u32 fn_1_A8DC4(void) {
    return lbl_1_bss_6F640;
}
/* fzgx:end fn_1_A8DC4 */

/* fzgx:begin fn_1_A8E78 */
// fn_1_A8E78: Take an argument, call fn_1_A9420(0), then fn_1_A948C with original arg.

void fn_1_A8E78(int arg) {
    fn_1_A9420(0);
    fn_1_A948C(arg);
}
/* fzgx:end fn_1_A8E78 */

/* fzgx:begin fn_1_A8EB0 */
void fn_1_A8EB0(int arg0, int arg1) {
    fn_1_A9420(0);
    fn_1_A943C(arg0, arg1);
}
/* fzgx:end fn_1_A8EB0 */

/* fzgx:begin fn_1_A8EF8 */
// Reset the current selection before applying the two provided values.
void fn_1_A8EF8(u16 arg0, u16 arg1) {
    fn_1_A9420(0);
    fn_1_A9464(arg0, arg1);
}
/* fzgx:end fn_1_A8EF8 */

/* fzgx:begin fn_1_A8F40 */
// Reset the mode before forwarding the supplied value.
void fn_1_A8F40(u8 arg0) {
    fn_1_A9420(0);
    fn_1_A942C(arg0);
}
/* fzgx:end fn_1_A8F40 */

/* fzgx:begin fn_1_A8F78 */
void fn_1_A8F78(void) {
    fn_1_A9420(0);
    fn_1_A96BC();
}
/* fzgx:end fn_1_A8F78 */

/* fzgx:begin fn_1_A9250 noprologue */
#include "types.h"

extern void fn_1_49410(void);
extern u32 lbl_1_data_35990[3];
extern void fn_1_494DC(s16);
extern void fn_1_520A0(void);
extern void fn_1_52088(void);
extern u32 lbl_1_bss_71658[6];
extern const f64 lbl_1_rodata_4A98;
extern void fn_1_49714(f32, f32, f32);
extern void fn_1_49680(f32, f32);
extern void fn_1_A93C4(u8);
extern void fn_1_4A0D8(void *);
extern void fn_1_520CC(void);

typedef struct {
    u8 kind;
    u8 callback;
    u8 flags;
    u8 pad3;
    s16 x;
    s16 y;
    s16 z;
    s16 padA;
    void *data;
} Fn1A9250Entry;

extern Fn1A9250Entry lbl_1_bss_70658[];

void fn_1_A9250(int arg) {
    int i;

    fn_1_49410();
    fn_1_494DC((s16)lbl_1_data_35990[(u8)arg]);
    fn_1_520A0();
    fn_1_52088();

    for (i = 0; i < (int)lbl_1_bss_71658[0]; i++) {
        if ((u8)arg == lbl_1_bss_70658[i].kind) {
            if (((lbl_1_bss_70658[i].flags >> 1) & 1) != 0) {
                fn_1_49714(
                    (f32)(lbl_1_bss_70658[i].x + lbl_1_bss_70658[i].z),
                    (f32)lbl_1_bss_70658[i].y,
                    (f32)lbl_1_bss_70658[i].x);
            } else {
                fn_1_49680(
                    (f32)(lbl_1_bss_70658[i].x + lbl_1_bss_70658[i].z),
                    (f32)lbl_1_bss_70658[i].y);
            }
            fn_1_A93C4(lbl_1_bss_70658[i].callback);
            fn_1_4A0D8(lbl_1_bss_70658[i].data);
        }
    }

    fn_1_49410();
    fn_1_520CC();
}
/* fzgx:end fn_1_A9250 */

/* fzgx:begin fn_1_A93C4 */
extern void fn_1_49514(u32 *);

void fn_1_A93C4(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 v2;
    s8 loc_8[8];
    v0 = ((arg0 & 0xC0) | 63);
    v1 = (((arg0 << 2) & 0xC0) | 63);
    v2 = (((arg0 << 4) & 0xC0) | 63);
    loc_8[4] = v0;
    loc_8[5] = v1;
    loc_8[6] = v2;
    loc_8[7] = (((arg0 & 0x3) << 6) | 63);
    *(u32 *)&loc_8[0] = *(u32 *)&loc_8[4];
    fn_1_49514((u32 *)loc_8);
}
/* fzgx:end fn_1_A93C4 */

/* fzgx:begin fn_1_A9420 */
// Stores the current value in the driver's status byte.
void fn_1_A9420(u8 value) {
    lbl_1_bss_6F648.unk_0 = value;
}
/* fzgx:end fn_1_A9420 */

/* fzgx:begin fn_1_A942C */
// Stores the value in the driver's secondary byte-sized state field.
void fn_1_A942C(u8 value) {
    lbl_1_bss_6F648.unk_1 = value;
}
/* fzgx:end fn_1_A942C */

/* fzgx:begin fn_1_A943C noprologue */
#include "types.h"

extern void (*lbl_1_bss_7168C)(void);

extern struct fn_1_A943C_lbl_1_bss_6F648 lbl_1_bss_6F648;

struct fn_1_A943C_lbl_1_bss_6F648 {
    u8 pad_0[0x2];
    u8 unk_2;
    u8 pad_3[0x1];
    u16 unk_4;
    u16 unk_6;
    u16 unk_8;
};

void fn_1_A943C(u32 arg0, u32 arg1) {
    u8 v0;
    v0 = lbl_1_bss_6F648.unk_2;
    lbl_1_bss_6F648.unk_4 = arg0;
    lbl_1_bss_6F648.unk_6 = arg1;
    lbl_1_bss_6F648.unk_8 = 0;
    lbl_1_bss_6F648.unk_2 = (v0 & 0xFFFFFFFD);
}
/* fzgx:end fn_1_A943C */

/* fzgx:begin fn_1_A9464 */
// Set the two values and mark the shared state as ready.
void fn_1_A9464(u16 arg0, u16 arg1) {
    u8 flags;

    flags = lbl_1_bss_6F648.unk_2;
    lbl_1_bss_6F648.unk_4 = arg0;
    lbl_1_bss_6F648.unk_6 = arg1;
    lbl_1_bss_6F648.unk_8 = 0;
    lbl_1_bss_6F648.unk_2 = flags | 2;
}
/* fzgx:end fn_1_A9464 */

/* fzgx:begin fn_1_A96DC */
void fn_1_A96DC(void) {
    lbl_1_data_3599C.unk_0 = 1;
}
/* fzgx:end fn_1_A96DC */

/* fzgx:begin fn_1_A96EC */
// Clear the driver's first state field.
void fn_1_A96EC(void) {
    lbl_1_data_3599C.unk_0 = 0;
}
/* fzgx:end fn_1_A96EC */

/* fzgx:begin fn_1_A96FC */
// Initialize the driver state and format its startup data.
void fn_1_A96FC(void) {
    u8 buffer[0x48];

    lbl_1_bss_71670 = fn_1_451C();
    sprintf(buffer, (char *)lbl_1_data_35AB8,
                ((u32 *)lbl_1_data_35A70)[*(s16 *)&lbl_1_bss_960]);
    fn_1_A5AA0(buffer, &lbl_1_bss_71674);
}
/* fzgx:end fn_1_A96FC */

/* fzgx:begin fn_1_A9764 */
void fn_1_A9764(void) {
    lbl_1_bss_7167C();
}
/* fzgx:end fn_1_A9764 */

/* fzgx:begin fn_1_A9790 */
void fn_1_A9790(void) {
    lbl_1_bss_71680();
}
/* fzgx:end fn_1_A9790 */

/* fzgx:begin fn_1_A97BC */
void fn_1_A97BC(void) {
    fn_1_A5C98(&lbl_1_bss_71674);
}
/* fzgx:end fn_1_A97BC */

/* fzgx:begin fn_1_A97E4 */
void fn_1_A97E4(void) {
    lbl_1_bss_71684();
}
/* fzgx:end fn_1_A97E4 */

/* fzgx:begin fn_1_A9810 */
void fn_1_A9810(void) {
    lbl_1_bss_71688();
}
/* fzgx:end fn_1_A9810 */

/* fzgx:begin fn_1_A983C */
void fn_1_A983C(void) {
    lbl_1_bss_7168C();
}
/* fzgx:end fn_1_A983C */

/* fzgx:begin fn_1_AA538 */
// Initialize the shared rendering state and submit the associated configuration.
void fn_1_AA538(void) {
    Obj_1_bss_71690 *state = (Obj_1_bss_71690 *)&lbl_1_bss_71690;

    fn_1_A7024(state->unk_4, state->unk_8, state->unk_C, state->unk_10);
    fn_80074918(1, 3, 1);
    state->unk_0 = 1;
}
/* fzgx:end fn_1_AA538 */

/* fzgx:begin fn_1_AAF18 */
// fn_1_AAF18: empty in retail (single blr).
void fn_1_AAF18(void) {
}
/* fzgx:end fn_1_AAF18 */

/* fzgx:begin fn_1_AB434 */
// fn_1_AB434: empty in retail (single blr).
void fn_1_AB434(void) {
}
/* fzgx:end fn_1_AB434 */

/* fzgx:begin fn_1_AB438 */
typedef struct Fn1AB438Data {
    u8 pad_00[8];
    s16 field_08;
    s16 field_0A;
    u8 pad_0C[0x1e];
    u8 field_2A;
} Fn1AB438Data;

void fn_1_AB438(Fn1AB438Data *data) {
    data->field_08 = 30;
    data->field_0A = 14;
    data->field_2A |= 4;
}
/* fzgx:end fn_1_AB438 */

/* fzgx:begin fn_1_AB458 */
// fn_1_AB458: empty in retail (single blr).
void fn_1_AB458(void) {
}
/* fzgx:end fn_1_AB458 */

/* fzgx:begin fn_1_AB45C */
void fn_1_AB45C(int index) {
    lbl_1_bss_716C8[index * 0xa0 + 7] = 1;
}
/* fzgx:end fn_1_AB45C */
