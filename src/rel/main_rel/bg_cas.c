#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_cas.h"
extern void fn_80008BEC(void *arg0, int arg1, int arg2);
extern void fn_1_FCA10(void);
extern int fn_1_FCF50(void);
extern void *fn_1_563B8(void *);
extern f32 lbl_1_rodata_761C[13];
extern void fn_1_7EB8C(void *, f32);
extern void fn_1_7F20C(void *, s32, f32);
extern void lbl_8006DB74(void *);
extern void lbl_8006DBAC(void *);
extern void fn_1_FD3A8(void);
extern void *memset(void *, int, u32);
extern void fn_1_FE7D8(u8 *, s32);
extern void fn_1_FF420(u8 *);
extern void fn_80074788(int);
extern void fn_80072864(int);
extern void fn_800745A4(int, int, int, int, int, int);
extern void fn_800734A8(int, int, int, int);
extern void fn_80072AB0(int, int, int);
extern void fn_800735C8(int, int);
extern void fn_80073620(int, int);
extern void fn_80073C6C(int);
extern void fn_80072C24(int, int, int, int, int);
extern void fn_80072D64(int, int, int, int, int, int);
extern void fn_80072CC4(int, int, int, int, int);
extern void fn_80072E20(int, int, int, int, int, int);
extern void fn_80073678(int);
extern void fn_80074660(int);
extern void fn_80074918(int, int, int);
extern void fn_800720B0(int);
extern void fn_1_9A508(Obj_1_data_2A7E0 *arg0);
extern void fn_1_9AD54(void);
extern void fn_1_9AD88(void);
extern void fn_1_10069C(Obj_1_data_2A7E0_At3C *);
extern void fn_1_FF038(Obj_1_data_2A7E0_At3C *);
extern const f64 lbl_1_rodata_760C;
extern void OSPanic(const char *, int, const char *, ...);
extern void lbl_8006D758(void);
extern void lbl_8006E13C(void *);
extern void lbl_8006E0A4(void *);
extern void fn_80008BA8(void *, void *, u32);
extern u8 lbl_1_bss_851E0[36];
extern void fn_1_7F230(void *, s32, f32);
extern void fn_1_FFC60(Obj_1_data_2A7E0_At3C *arg0);
extern void fn_1_FEC7C(void *object);
extern const f32 lbl_1_rodata_76A8;

/* fzgx:begin fn_1_FB798 */
int fn_1_FB798(int mode, u32 *value) {
    Obj_1_data_2A7E0_At3C *entry = lbl_1_data_2A7E0.unk_3C;

    switch (mode) {
    case 0: {
        u8 *cursor = (u8 *)lbl_1_bss_3BE0->unk_54;
        entry->unk_0 = 0;
        while (cursor != (u8 *)value) {
            u32 count = entry->unk_0;
            cursor += 0x40;
            entry->unk_0 = count + 1;
        }
        *value |= 0x80000000;
        break;
    }

    case 1: {
        u8 *p = (u8 *)entry + 4;
        ((u32 *)(p + 4))[*(u8 *)p] = (u32)value;
        *(u8 *)p = *(u8 *)p + 1;
        *value |= 0x80000000;
        if (*(u8 *)p >= 0x10) {
            OSPanic((const char *)lbl_1_data_3EF90, 0x2f2, (const char *)lbl_1_data_3EF9C);
        }
        break;
    }
    }

    return 1;
}
/* fzgx:end fn_1_FB798 */

/* fzgx:begin fn_1_FB870 */
u8 *fn_1_FB870(void) {
    return &lbl_1_bss_84450;
}
/* fzgx:end fn_1_FB870 */

/* fzgx:begin fn_1_FB96C */
#include "rel/main_rel/bg_cas.h"

// Initializes the selected background-cas state before running its setup stages.
void fn_1_FB96C(int index) {
    u32 *states = &lbl_1_bss_84454.unk_0;

    states[(index & 0xff) * 0x9c] = 1;
    fn_1_FB9DC(index);
    fn_1_FBA88(index);
    fn_1_FBC5C(index);
}
/* fzgx:end fn_1_FB96C */

/* fzgx:begin fn_1_FB9C0 */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_cas.h"

// Clear the selected CAS state value.
void fn_1_FB9C0(int index) {
    (&lbl_1_bss_84454.unk_0)[(index & 0xff) * 0x9c] = 0;
}
/* fzgx:end fn_1_FB9C0 */

/* fzgx:begin fn_1_FB9DC */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_cas.h"

// Reset the per-slot flags and enable the flags associated with the selected slot.
void fn_1_FB9DC(int index) {
    u32 slot = index & 0xff;
    Obj_1_bss_84454 *state =
        (Obj_1_bss_84454 *)((u8 *)&lbl_1_bss_84454 + slot * 0x270);

    state->unk_14 = 0;
    state->unk_134 = 0;
    state->unk_74 = 0;
    state->unk_194 = 0;
    state->unk_D4 = 0;
    state->unk_1F4 = 0;

    switch (slot) {
    case 0:
        state->unk_14 = 1;
        state->unk_134 = 1;
        break;
    case 1:
        state->unk_134 = 1;
        state->unk_194 = 1;
        break;
    case 2:
        state->unk_134 = 1;
        state->unk_1F4 = 1;
        break;
    case 3:
        state->unk_134 = 1;
        state->unk_1F4 = 1;
        break;
    case 4:
        state->unk_134 = 1;
        state->unk_194 = 1;
        break;
    default:
        break;
    }
}
/* fzgx:end fn_1_FB9DC */

/* fzgx:begin fn_1_FBEA8 */
extern void lbl_8006DB74(void *);

void fn_1_FBEA8(void) {
    Obj_1_bss_84454 *base;
    Obj_1_bss_84454 *entry;
    u8 i;
    s32 j;

    base = &lbl_1_bss_84454;
    for (i = 0; i < 5; i++) {
        Obj_1_bss_84454 *slot =
            (Obj_1_bss_84454 *)((u8 *)base + i * 0x270);
        if ((s32)slot->unk_0 != 0) {
            for (j = 0, entry = slot; j < 3;
                 j++, entry = (Obj_1_bss_84454 *)((u8 *)entry + 0x60)) {
                if ((s32)entry->unk_14 != 0) {
                    entry->unk_18 += entry->unk_24;
                    entry->unk_1C += entry->unk_28;
                    entry->unk_20 += entry->unk_2C;
                    lbl_8006D758();
                    lbl_8006E13C(&entry->unk_30);
                    lbl_8006E0A4(&entry->unk_18);
                    lbl_8006DB74(entry->pad_3C);
                }
                if ((s32)entry->unk_134 != 0) {
                    entry->unk_138 += entry->unk_144;
                    entry->unk_13C += entry->unk_148;
                    entry->unk_140 += entry->unk_14C;
                    lbl_8006D758();
                    lbl_8006E13C(&entry->unk_150);
                    lbl_8006E0A4(&entry->unk_138);
                    lbl_8006DB74(&entry->pad_158[4]);
                }
            }
        }
    }
}
/* fzgx:end fn_1_FBEA8 */

/* fzgx:begin fn_1_FC40C */
// fn_1_FC40C: empty in retail (single blr).
void fn_1_FC40C(void) {
}
/* fzgx:end fn_1_FC40C */

/* fzgx:begin fn_1_FC410 */
// fn_1_FC410: empty in retail (single blr).
void fn_1_FC410(void) {
}
/* fzgx:end fn_1_FC410 */

/* fzgx:begin fn_1_FC4E0 */
void fn_1_FC4E0(void *arg0, int arg1) {
    if (arg0 != 0) {
        fn_80008BEC(arg0, 0, (arg1 & 0xff) * 0x10440);
    }
}
/* fzgx:end fn_1_FC4E0 */

/* fzgx:begin fn_1_FC51C */
extern void fn_1_FC60C(void);
extern void DCFlushRange(void *, u32);
extern void GXInitTexObj(void *, void *, u32, u32, u32, u32, u32, u32);
extern void GXInitTexObjLOD(void *, f32, f32, f32, u32, u32, u32, u32, u32);

#pragma opt_common_subs off
void fn_1_FC51C(void) {
    fn_1_FC60C();

    lbl_1_bss_851E0[0] = 0xff;
    lbl_1_bss_851E0[1] = 0xff;
    lbl_1_bss_851E0[2] = 0;
    lbl_1_bss_851E0[3] = 0;
    lbl_1_bss_851E0[4] = 0;
    lbl_1_bss_851E0[5] = 0;
    lbl_1_bss_851E0[6] = 0;
    lbl_1_bss_851E0[7] = 0;

    fn_80008BA8(lbl_1_bss_851E0 + 8, lbl_1_bss_851E0, 8);
    fn_80008BA8(lbl_1_bss_851E0 + 0x10, lbl_1_bss_851E0, 8);
    fn_80008BA8(lbl_1_bss_851E0 + 0x18, lbl_1_bss_851E0, 8);
    DCFlushRange(lbl_1_bss_851E0, 0x20);

    GXInitTexObj((*(u8 (*)[32])&lbl_1_bss_85204), lbl_1_bss_851E0, 8, 4, 1, 0, 0, 0);
    GXInitTexObjLOD((*(u8 (*)[32])&lbl_1_bss_85204),
                *(const f32 *)&lbl_1_rodata_760C,
                *(const f32 *)&lbl_1_rodata_760C,
                *(const f32 *)&lbl_1_rodata_760C,
                1, 1, 0, 0, 0);
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_FC51C */

/* fzgx:begin fn_1_FC60C */
extern u8 lbl_1_bss_850E0[256];


extern u32 GXGetTexBufferSize(u16, u16, u32, u8, u8);
extern void GXInitTexObj(void *, void *, u16, u16, u32, u32, u32, u8);
extern void GXInitTexObjLOD(void *, u32, u32, f32, f32, f32, u8, u8, u32);
extern void DCFlushRange(void *, u32);

#pragma opt_common_subs off
void fn_1_FC60C(void) {
    u8 *tex;
    u8 *buf;
    u32 size;
    u32 i;

    size = GXGetTexBufferSize(0x10, 0x10, 1, 0, 0);
    tex = lbl_1_bss_85224;
    buf = lbl_1_bss_850E0;

    for (i = 0; i < 0x100; i++) {
        int idx = ((i & 0x80) >> 2) + ((i >> 4) & 7) + ((i & 0xC) << 4) + ((i & 3) << 3);
        if (i >= 0xA) {
            buf[idx] = (u8)i - 0xA;
        } else {
            buf[idx] = 0;
        }
    }

    GXInitTexObj(tex, buf, 0x10, 0x10, 1, 0, 1, 0);
    GXInitTexObjLOD(tex, 0, 0, (*(f32 (*)[2])&lbl_1_rodata_760C)[0], (*(f32 (*)[2])&lbl_1_rodata_760C)[0],
                    (*(f32 (*)[2])&lbl_1_rodata_760C)[0], 0, 0, 0);
    DCFlushRange(buf, size);
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_FC60C */

/* fzgx:begin fn_1_FCF50 */
int fn_1_FCF50(void) {
    fn_1_FCA10();
    return 1;
}
/* fzgx:end fn_1_FCF50 */

/* fzgx:begin fn_1_FCF74 */
void fn_1_FCF74(void) {
    fn_80008BEC(&lbl_1_data_3EFB0, 0, 4);
}
/* fzgx:end fn_1_FCF74 */

/* fzgx:begin fn_1_FD1D4 */
extern void fn_80008BEC(void *arg0, int arg1, int arg2);
extern void fn_1_FCA10(void);
extern int fn_1_FCF50(void);
extern void *fn_1_563B8(void *);
extern f32 lbl_1_rodata_761C[13];
extern void fn_1_7EB8C(void *, f32);
extern void lbl_8006DB74(void *);
extern void lbl_8006DBAC(void *);
extern void fn_1_FD3A8(void);
extern void *memset(void *, int, u32);
extern void fn_1_FE7D8(u8 *, s32);
extern void fn_1_FF420(u8 *);
extern void fn_80074788(int);
extern void fn_80072864(int);
extern void fn_800745A4(int, int, int, int, int, int);
extern void fn_800734A8(int, int, int, int);
extern void fn_80072AB0(int, int, int);
extern void fn_800735C8(int, int);
extern void fn_80073620(int, int);
extern void fn_80073C6C(int);
extern void fn_80072C24(int, int, int, int, int);
extern void fn_80072D64(int, int, int, int, int, int);
extern void fn_80072CC4(int, int, int, int, int);
extern void fn_80072E20(int, int, int, int, int, int);
extern void fn_80073678(int);
extern void fn_80074660(int);
extern void fn_80074918(int, int, int);
extern void fn_800720B0(int);
extern void fn_1_9A508(Obj_1_data_2A7E0 *arg0);
extern void fn_1_9AD54(void);
extern void fn_1_9AD88(void);
extern void fn_1_10069C(Obj_1_data_2A7E0_At3C *);
extern void fn_1_FF038(Obj_1_data_2A7E0_At3C *);

typedef struct {
    void *value;
} fn_1_FD1D4_Fn1FD27CArg0;

typedef struct {
    u8 pad[0x40f0];
    void *value;
} fn_1_FD1D4_Fn1FD27CArg1;

void fn_1_FD1D4(fn_1_FD1D4_Fn1FD27CArg0 *arg0, fn_1_FD1D4_Fn1FD27CArg1 *arg1) {
    fn_1_FD1D4_Fn1FD27CArg1 *persistent;
    void *value;
    void *result;
    s16 mode;
    u8 local[0x30];

    persistent = arg1;
    value = arg0->value;
    lbl_8006DB74(local);
    if (persistent->value != 0 && (*(u32 *)((u8 *)persistent->value + 4) & ~0x7fffffffU) != 0) {
        result = fn_1_563B8((void *)fn_1_FCF50);
        mode = *(s16 *)persistent->value;
        if (mode == 0) {
            fn_1_7EB8C(value, lbl_1_rodata_761C[0]);
        } else {
            fn_1_7F230(value, (s32)mode, lbl_1_rodata_761C[0]);
        }
        lbl_8006DBAC(local);
        fn_1_563B8(result);
    }
}
/* fzgx:end fn_1_FD1D4 */

/* fzgx:begin fn_1_FD27C */
typedef struct {
    void *value;
} fn_1_FD27C_Fn1FD27CArg0;

typedef struct {
    u8 pad[0x40f0];
    void *value;
} fn_1_FD27C_Fn1FD27CArg1;

void fn_1_FD27C(fn_1_FD27C_Fn1FD27CArg0 *arg0, fn_1_FD27C_Fn1FD27CArg1 *arg1) {
    fn_1_FD27C_Fn1FD27CArg1 *persistent;
    void *value;
    void *result;
    s16 mode;
    u8 local[0x30];

    persistent = arg1;
    value = arg0->value;
    lbl_8006DB74(local);
    if (persistent->value != 0 && (*(u32 *)((u8 *)persistent->value + 4) & ~0x7fffffffU) != 0) {
        result = fn_1_563B8((void *)fn_1_FCF50);
        mode = *(s16 *)persistent->value;
        if (mode == 0) {
            fn_1_7EB8C(value, lbl_1_rodata_761C[0]);
        } else {
            fn_1_7F20C(value, (s32)mode, lbl_1_rodata_761C[0]);
        }
        lbl_8006DBAC(local);
        fn_1_563B8(result);
    }
}
/* fzgx:end fn_1_FD27C */

/* fzgx:begin fn_1_FD388 */
void fn_1_FD388(void) {
    fn_1_FD3A8();
}
/* fzgx:end fn_1_FD388 */

/* fzgx:begin fn_1_FDFF4 */
#include "rel/main_rel/bg_cas.h"

// Mark the background-collision object as active.
void fn_1_FDFF4(void) {
    lbl_1_bss_850C6.unk_0 = 1;
}
/* fzgx:end fn_1_FDFF4 */

/* fzgx:begin fn_1_FE004 */
#include "rel/main_rel/bg_cas.h"

void fn_1_FE004(void) {
    lbl_1_bss_850C6.unk_0 = 0;
}
/* fzgx:end fn_1_FE004 */

/* fzgx:begin fn_1_FE5C4 */
#include "rel/main_rel/bg_cas.h"

void fn_1_FE5C4(u8 arg0, u32 arg1, u32 arg2, u8 arg3) {
    lbl_1_bss_850C0.unk_4 = arg3;
    lbl_1_bss_850C0.unk_5 = arg0;
    *(u32 *)((u8 *)&lbl_1_bss_850C0 + 0x8) = arg2;
    *(u32 *)((u8 *)&lbl_1_bss_850C0 + 0xc) = arg1;
}
/* fzgx:end fn_1_FE5C4 */

/* fzgx:begin fn_1_FE5E0 */
// fn_1_FE5E0: No-op return
void fn_1_FE5E0(void) {
    return;
}
/* fzgx:end fn_1_FE5E0 */

/* fzgx:begin fn_1_FE5E4 */
extern void fn_1_9A508(Obj_1_data_2A7E0 *arg0);

typedef struct {
    u8 pad_0[0x1B1E4];
    u16 unk_1B1E4;
} Obj_1_data_2A7E0_At3C_Ext;

void fn_1_FE5E4(void) {
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    fn_1_9A508(&lbl_1_data_2A7E0);
    fn_1_FFC60(obj);
    fn_1_FEC7C(obj);
    ((Obj_1_data_2A7E0_At3C_Ext *)obj)->unk_1B1E4 = 0;
    obj->unk_430 = lbl_1_rodata_76A8;
}
/* fzgx:end fn_1_FE5E4 */

/* fzgx:begin fn_1_FE640 */
// fn_1_FE640: empty in retail (single blr).
void fn_1_FE640(void) {
}
/* fzgx:end fn_1_FE640 */

/* fzgx:begin fn_1_FE780 */
// fn_1_FE780: Empty return
void fn_1_FE780(void) {
}
/* fzgx:end fn_1_FE780 */

/* fzgx:begin fn_1_FE784 */
// Update the background object and process it when its active state is set.
void fn_1_FE784(void) {
    Obj_1_data_2A7E0_At3C *background_object = lbl_1_data_2A7E0.unk_3C;

    fn_1_9AD88();
    if ((s32)background_object->unk_10 != 0) {
        fn_1_10069C(background_object);
    }
    fn_1_FF038(background_object);
}
/* fzgx:end fn_1_FE784 */

/* fzgx:begin fn_1_FE7D4 */
// fn_1_FE7D4: empty in retail (single blr).
void fn_1_FE7D4(void) {
}
/* fzgx:end fn_1_FE7D4 */

/* fzgx:begin fn_1_FEC7C */
#include "rel/main_rel/bg_cas.h"

void fn_1_FEC7C(void *object) {
    s32 count;
    s32 index;
    u8 *entry;

    entry = (u8 *)object + 0x434;
    memset(entry, 0, 0x1ADB0);
    index = 0;
    while (index < (count = (s32)lbl_1_bss_3BE0->unk_A4)) {
        fn_1_FE7D8(entry, 1);
        fn_1_FF420(entry);
        index++;
        entry += 0x44C;
    }
    while (count < 0x64) {
        fn_1_FE7D8(entry, 0);
        fn_1_FF420(entry);
        count++;
        entry += 0x44C;
    }
}
/* fzgx:end fn_1_FEC7C */

/* fzgx:begin fn_1_1011CC */
void fn_1_1011CC(int arg0, int arg1) {
    fn_80074788(0);
    fn_80072864(0);
    fn_800745A4(0, 1, 4, 0x3c, 0, 0x7d);
    fn_800734A8(0, 0, 0, 0xff);
    fn_80072AB0(0, 0, 0);
    fn_800735C8(0, 0xc);
    fn_80073620(0, 0x1c);
    fn_80073C6C(0);
    if (arg0 != 0) {
        fn_80072C24(0, 0xf, 0xe, 8, 0xf);
    } else {
        fn_80072C24(0, 0xf, 0xf, 0xf, 0xe);
    }
    fn_80072D64(0, 0, 0, 0, 1, 0);
    if (arg1 != 0) {
        fn_80072CC4(0, 7, 6, 4, 7);
    } else {
        fn_80072CC4(0, 7, 7, 7, 6);
    }
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_80073678(1);
    fn_80074660(1);
    fn_80074918(1, 3, 0);
    fn_800720B0(0);
}
/* fzgx:end fn_1_1011CC */

/* fzgx:begin fn_1_101348 */
#include "rel/main_rel/bg_cas.h"

int fn_1_101348(int index, u32 *value) {
    Obj_1_data_2A7E0_At3C *obj = lbl_1_data_2A7E0.unk_3C;

    switch (index) {
    case 0:
        obj->unk_424 = *value;
        break;
    case 1:
        obj->unk_428 = *value;
        break;
    case 2:
        obj->unk_42C = *value;
        break;
    default:
        break;
    }

    return 1;
}
/* fzgx:end fn_1_101348 */

/* fzgx:begin fn_1_1013A0 */
struct fn_1_1013A0_Arg1 {
    u32 unk_0;
};

s32 fn_1_1013A0(s32 arg0, struct fn_1_1013A0_Arg1 *arg1) {
    switch (arg0) {
    case 0:
        arg1->unk_0 |= 0x1000000;
        break;
    }

    return 1;
}
/* fzgx:end fn_1_1013A0 */

/* fzgx:begin fn_1_1013C0 */
// fn_1_1013C0: empty in retail (single blr).
void fn_1_1013C0(void) {
}
/* fzgx:end fn_1_1013C0 */

/* fzgx:begin fn_1_1013C4 */
#include "rel/main_rel/bg_cas.h"

void fn_1_1013C4(void) {
    Obj_1_data_2A7E0_At3C *ptr = lbl_1_data_2A7E0.unk_3C;
    fn_1_9A508(&lbl_1_data_2A7E0);
    ptr->unk_0 = -1;
}
/* fzgx:end fn_1_1013C4 */

/* fzgx:begin fn_1_101400 */
// fn_1_101400: empty in retail (single blr).
void fn_1_101400(void) {
}
/* fzgx:end fn_1_101400 */

/* fzgx:begin fn_1_101404 */
void fn_1_101404(void) {
    fn_1_9AD54();
}
/* fzgx:end fn_1_101404 */

/* fzgx:begin fn_1_101424 */
// fn_1_101424: empty in retail (single blr).
void fn_1_101424(void) {
}
/* fzgx:end fn_1_101424 */

/* fzgx:begin fn_1_101428 */
void fn_1_101428(void) {
    fn_1_9AD88();
}
/* fzgx:end fn_1_101428 */

/* fzgx:begin fn_1_101448 */
// fn_1_101448: Empty function (blr only)
void fn_1_101448(void) {
}
/* fzgx:end fn_1_101448 */

/* fzgx:begin fn_1_10144C */
// fn_1_10144C: returns a constant.
int fn_1_10144C(void) {
    return 0;
}
/* fzgx:end fn_1_10144C */

/* fzgx:begin fn_1_101454 */
int fn_1_101454(int arg0, u32 *arg1) {
    Obj_1_data_2A7E0_At3C *entry;
    u8 *cursor;

    entry = lbl_1_data_2A7E0.unk_3C;
    switch (arg0) {
    case 0:
        cursor = (u8 *)lbl_1_bss_3BE0->unk_54;
        entry->unk_0 = 0;
        while (cursor != (u8 *)arg1) {
            entry->unk_0 += 1;
            cursor += 0x40;
        }
        *arg1 |= 1u << 31;
        break;
    default:
        goto done; /* The default case skips the zero-argument body. */
    }
done:
    return 1;
}
/* fzgx:end fn_1_101454 */
