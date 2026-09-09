#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/enemy_ctrl.h"

extern u32 lbl_1_bss_7AC48[5];
extern void *lbl_801A6410;
extern void fn_1_46B4(void *, u32, void *, u32);
extern void fn_1_C489C(void);
extern u32 lbl_1_bss_7AC54[4];
extern u8 lbl_1_bss_7AC90[12];
extern u32 lbl_1_rodata_5D40[7];
extern u32 fn_1_5910(void *);
extern u8 fn_1_86810(void *);
extern u32 fn_1_3F7E0(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(u32);
extern const f32 lbl_1_rodata_5C3C;
extern const f32 lbl_1_rodata_5D18;
extern void fn_1_496FC(f32, f32);
extern void fn_1_495C8(u32);
extern void fn_1_49728(u32);
extern void fn_1_4AE0C(void *, ...);
extern const f32 lbl_1_rodata_5D5C;
extern const f32 lbl_1_rodata_5D60;
extern f32 lbl_1_rodata_26F8[22];
extern const f32 lbl_1_rodata_5D64;
extern const f32 lbl_1_rodata_5D68;
extern void fn_1_51E60(void *);
extern const f32 lbl_1_rodata_5D6C;
extern void fn_1_C8DC0(void);
extern void fn_80008E84(u32);
extern const f32 lbl_1_rodata_5D88;
extern const f32 lbl_1_rodata_5D8C;
extern void fn_1_4955C(f32, f32);
extern const f32 lbl_1_rodata_5CD4;
extern const f32 lbl_1_rodata_5D90;
extern void fn_1_4966C(f32, f32);

/* fzgx:begin fn_1_C47B4 */
void fn_1_C47B4(void) {
    u32 *p = lbl_1_bss_7AC48;

    if (p[0] != 0) {
        fn_1_46B4(lbl_801A6410, p[0], lbl_1_data_3D234, 0x4af);
    }
    fn_1_46B4(lbl_801A6410, p[4], lbl_1_data_3D234, 0x4b0);
    fn_1_46B4(lbl_801A6410, p[3], lbl_1_data_3D234, 0x4b1);
    fn_1_46B4(lbl_801A6410, p[2], lbl_1_data_3D234, 0x4b2);
    p[0] = 0;
    p[4] = 0;
    p[3] = 0;
    p[2] = 0;
}
/* fzgx:end fn_1_C47B4 */

/* fzgx:begin fn_1_C487C */
void fn_1_C487C(void) {
    fn_1_C489C();
}
/* fzgx:end fn_1_C487C */

/* fzgx:begin fn_1_C6ED4 */
typedef struct Fn1C6ED4Data {
    u32 flags;
    f32 value_4;
    f32 value_8;
    f32 value_c;
    f32 value_10;
    f32 value_14;
} Fn1C6ED4Data;

typedef struct Fn1C6ED4Enemy {
    u32 flags;
    u8 pad_4[0x1f0];
    f32 output_1f4;
    f32 output_1f8;
    f32 output_1fc;
    f32 output_200;
    f32 output_204;
    u8 pad_208[0x27c];
    Fn1C6ED4Data *data;
} Fn1C6ED4Enemy;

void fn_1_C6ED4(Fn1C6ED4Enemy *self) {
    Fn1C6ED4Data *data = self->data;

    self->output_1fc = data->value_4;
    self->output_1f4 = data->value_8;
    self->output_200 = data->value_c;
    self->output_204 = data->value_10;
    self->output_1f8 = data->value_14;

    if (data->flags >> 31) {
        self->flags |= 0x40;
        data->flags &= ~((u32)1 << 31);
    }
    if ((data->flags >> 30) & 1) {
        self->flags |= 0x1000;
        data->flags &= ~((u32)1 << 30);
    }
    if ((data->flags >> 20) & 1) {
        self->flags |= 0x8;
        data->flags &= ~((u32)1 << 20);
    }
}
/* fzgx:end fn_1_C6ED4 */

/* fzgx:begin fn_1_C6F70 */
u32 fn_1_C6F70(void) {
    return lbl_1_bss_7AC54[0];
}
/* fzgx:end fn_1_C6F70 */

/* fzgx:begin fn_1_C6F80 */
void fn_1_C6F80(u8 value) {
    lbl_1_bss_7AC90[0] = value;
}
/* fzgx:end fn_1_C6F80 */

/* fzgx:begin fn_1_CA218 */
typedef struct EnemyCtrl_CA218 {
    u32 value;
    u8 pad4[2];
    s16 state;
    u32 action;
} EnemyCtrl_CA218;

void fn_1_CA218(EnemyCtrl_CA218 *self) {
    u32 actions[7];

    actions[0] = lbl_1_rodata_5D40[0];
    actions[1] = lbl_1_rodata_5D40[1];
    actions[2] = lbl_1_rodata_5D40[2];
    actions[3] = lbl_1_rodata_5D40[3];
    actions[4] = lbl_1_rodata_5D40[4];
    actions[5] = lbl_1_rodata_5D40[5];
    actions[6] = lbl_1_rodata_5D40[6];

    if (self->state < 14) {
        self->action = actions[self->state / 2];
        self->state = self->state + 1;
    } else {
        self->value = 0;
    }
}
/* fzgx:end fn_1_CA218 */

/* fzgx:begin fn_1_CA2A4 */
typedef struct {
    u32 x[22];
} fn_1_CA2A4_LocalData;

void fn_1_CA2A4(void *self) {
    fn_1_CA2A4_LocalData local;
    s32 count;
    s32 max;

    if (((((u32 *)&lbl_1_data_3D544)[fn_1_5910(self)] >> 29) & 1) == 0) {
        return;
    }
    count = (u8)fn_1_86810(self) + 1;
    max = fn_1_3F7E0();
    if (count > max) {
        return;
    }
    fn_1_49410();
    fn_1_494DC(0xc);
    fn_1_496FC(lbl_1_rodata_5C3C, lbl_1_rodata_5D18);
    fn_1_495C8(1);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, count);
    fn_1_49410();
    fn_1_494DC(0xd);
    fn_1_496FC(lbl_1_rodata_5D5C, lbl_1_rodata_5D60);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, max);
    local = *(fn_1_CA2A4_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9429;
    ((f32 *)local.x)[1] = lbl_1_rodata_5D64;
    ((f32 *)local.x)[2] = lbl_1_rodata_5D68;
    fn_1_51E60(&local.x[0]);
    local = *(fn_1_CA2A4_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9405;
    ((f32 *)local.x)[1] = lbl_1_rodata_5D6C;
    ((f32 *)local.x)[2] = lbl_1_rodata_5D68;
    fn_1_51E60(&local.x[0]);
}
/* fzgx:end fn_1_CA2A4 */

/* fzgx:begin fn_1_CA690 */
extern u32 fn_1_5910(void *);
extern u8 fn_1_86810(void *);
extern u32 fn_1_3F7E0(void);
extern void fn_1_49410(void);
extern void fn_1_494DC(u32);
extern void fn_1_496FC(f32, f32);
extern void fn_1_49728(u32);
extern void fn_1_4AE0C(void *, ...);
extern f32 lbl_1_rodata_26F8[22];
extern void fn_1_51E60(void *);

typedef struct {
    u32 x[22];
} fn_1_CA690_LocalData;

void fn_1_CA690(void *self, s32 arg1, s32 arg2) {
    fn_1_CA690_LocalData local;
    s32 count;
    s32 max;

    if (((((u32 *)&lbl_1_data_3D544)[fn_1_5910(self)] >> 29) & 1) == 0) {
        return;
    }
    count = (u8)fn_1_86810(self) + 1;
    fn_1_49410();
    fn_1_494DC(0xc);
    fn_1_496FC(arg1, arg2);
    fn_1_4955C(lbl_1_rodata_5D88, lbl_1_rodata_5D8C);
    fn_1_4966C(lbl_1_rodata_5CD4, lbl_1_rodata_5D90);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, count);
    max = fn_1_3F7E0();
    fn_1_49410();
    fn_1_494DC(0xd);
    fn_1_496FC(arg1 + 0x5c, arg2 + 0x1a);
    fn_1_49728(1);
    fn_1_4AE0C(&lbl_1_data_3D574, max);
    local = *(fn_1_CA690_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9429;
    ((f32 *)local.x)[1] = arg1 + 0x4e;
    ((f32 *)local.x)[2] = arg2 + 0x1a;
    fn_1_51E60(&local.x[0]);
    local = *(fn_1_CA690_LocalData *)lbl_1_rodata_26F8;
    local.x[0] = 0x9405;
    ((f32 *)local.x)[1] = arg1 + 0x4e;
    ((f32 *)local.x)[2] = arg2 + 0xd;
    fn_1_51E60(&local.x[0]);
}
/* fzgx:end fn_1_CA690 */

/* fzgx:begin fn_1_CB404 */
// Set the state flag for the selected enemy-control entry.
void fn_1_CB404(u8 value) {
    (&lbl_1_bss_7ACA0.unk_8)[value * 0xc] = 0xf;
}
/* fzgx:end fn_1_CB404 */

/* fzgx:begin fn_1_CC27C */
// fn_1_CC27C: empty in retail (single blr).
void fn_1_CC27C(void) {
}
/* fzgx:end fn_1_CC27C */

/* fzgx:begin fn_1_CFA4C noprologue */
#include "types.h"
#include "font.h"

struct fn_1_CFA4C_Copy88 { u32 a[22]; };

extern f32 lbl_1_rodata_6010;
extern f64 lbl_1_rodata_5C00;
extern int fn_1_4F734(FontDrawPacket *);
extern u32 lbl_1_rodata_26F8;
extern void fn_1_52070(u32);
extern void fn_1_520A0(void);
extern void fn_1_520CC(void);

void fn_1_CFA4C(u32 arg0, u32 arg1) {
    f32 v0;
    u32 v1;
    f32 v2;
    FontDrawPacket loc_8;
    /* frame */
    fn_1_520A0();
    fn_1_52070(640);
    loc_8 = *(FontDrawPacket *)&lbl_1_rodata_26F8;
    v0 = (f32)(s32)(arg0 + 304);
    v1 = (0x10000 - 27620);
    loc_8.image = v1;
    v2 = (f32)(s32)(arg1 - 11);
    loc_8.x = v0;
    loc_8.y = v2;
    loc_8.z = lbl_1_rodata_6010;
    loc_8.flags = 7;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    fn_1_520CC();
}
/* fzgx:end fn_1_CFA4C */

/* fzgx:begin fn_1_D0790 */
void fn_1_D0790(void) {
    u32 *p = (u32 *)&lbl_1_data_3D544;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
}
/* fzgx:end fn_1_D0790 */

/* fzgx:begin fn_1_D07AC */
// Stores a value in the indexed enemy-control slot.
void fn_1_D07AC(u32 index, u32 value) {
    u32* slots = &lbl_1_bss_7ACA0.unk_0;
    slots[(index & 0xff) * 3] = value;
}
/* fzgx:end fn_1_D07AC */

/* fzgx:begin fn_1_D07C4 noprologue */
#include "types.h"

struct fn_1_D07C4_lbl_1_bss_7ACA0_0_E12 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x4];
};
struct fn_1_D07C4_lbl_1_bss_7ACA0 {
    struct fn_1_D07C4_lbl_1_bss_7ACA0_0_E12 unk_0[1];
};

extern struct fn_1_D07C4_lbl_1_bss_7ACA0 lbl_1_bss_7ACA0;

void fn_1_D07C4(u32 arg0, u32 arg1) {
    lbl_1_bss_7ACA0.unk_0[(arg0 & 0xFF)].unk_4 = arg1;
}
/* fzgx:end fn_1_D07C4 */

/* fzgx:begin fn_1_D0D68 */
void fn_1_D0D68(void) {
    fn_1_C8DC0();
}
/* fzgx:end fn_1_D0D68 */

/* fzgx:begin fn_1_D0D88 */
u32 fn_1_D0D88(void) {
    return lbl_1_data_3D648.unk_0;
}
/* fzgx:end fn_1_D0D88 */

/* fzgx:begin fn_1_D0D98 */
u16* fn_1_D0D98(void) {
    return &lbl_1_data_3D648.unk_4;
}
/* fzgx:end fn_1_D0D98 */

/* fzgx:begin fn_1_D0DA8 */
// Return the address of the object's 16-bit field at offset 0x6.
u8* fn_1_D0DA8(void) {
    return (u8*)&lbl_1_data_3D648.unk_6;
}
/* fzgx:end fn_1_D0DA8 */

/* fzgx:begin fn_1_D0DB8 */
// Returns the byte address of the object's field at offset 0x8.
u8* fn_1_D0DB8(void) {
    return (u8*)&lbl_1_data_3D648.unk_8;
}
/* fzgx:end fn_1_D0DB8 */

/* fzgx:begin fn_1_D0DC8 */
u8* fn_1_D0DC8(void) {
    return (u8*)&lbl_1_data_3D648 + 0xc;
}
/* fzgx:end fn_1_D0DC8 */

/* fzgx:begin fn_1_D0DD8 */
// Return the address of the enemy-control value at offset 0x10.
u8* fn_1_D0DD8(void) {
    return (u8*)&lbl_1_data_3D648.unk_10;
}
/* fzgx:end fn_1_D0DD8 */

/* fzgx:begin fn_1_D0DE8 */
// Return the address of the object's field at offset 0x12.
u8* fn_1_D0DE8(void) {
    return (u8*)&lbl_1_data_3D648.unk_12;
}
/* fzgx:end fn_1_D0DE8 */

/* fzgx:begin fn_1_D0DF8 */
// Return the enemy-control field at offset 0x14.
u16* fn_1_D0DF8(void) {
    return &lbl_1_data_3D648.unk_14;
}
/* fzgx:end fn_1_D0DF8 */

/* fzgx:begin fn_1_D0E08 */
// Return the address of the enemy-control field at offset 0x16.
u8* fn_1_D0E08(void) {
    return (u8*)&lbl_1_data_3D648.unk_16;
}
/* fzgx:end fn_1_D0E08 */

/* fzgx:begin fn_1_D0E18 */
// Return the address of the enemy-control field at offset 0x18.
u16* fn_1_D0E18(void) {
    return &lbl_1_data_3D648.unk_18;
}
/* fzgx:end fn_1_D0E18 */

/* fzgx:begin fn_1_D0E28 */
// Return the enemy-control data block.
Obj_1_data_3D648* fn_1_D0E28(void) {
    return &lbl_1_data_3D648;
}
/* fzgx:end fn_1_D0E28 */

/* fzgx:begin fn_1_D0E34 */
// Returns the status-byte array beginning at the shared enemy data block.
u8* fn_1_D0E34(void) {
    return &lbl_1_data_3D648.unk_20;
}
/* fzgx:end fn_1_D0E34 */

/* fzgx:begin fn_1_D0E44 */
// Return the address of the enemy controller's status byte.
u8* fn_1_D0E44(void) {
    return &lbl_1_data_3D648.unk_21;
}
/* fzgx:end fn_1_D0E44 */

/* fzgx:begin fn_1_D0E54 */
// Returns the address of this object's byte flag.
u8* fn_1_D0E54(void) {
    return &lbl_1_data_3D648.unk_22;
}
/* fzgx:end fn_1_D0E54 */

/* fzgx:begin fn_1_D0E64 */
// Returns the address of the enemy-control byte at offset 0x23.
u8* fn_1_D0E64(void) {
    return &lbl_1_data_3D648.unk_23;
}
/* fzgx:end fn_1_D0E64 */

/* fzgx:begin fn_1_D2F50 */
// Stores the initialized enemy-control handle for later subsystem updates.
void fn_1_D2F50(void) {
    u32 fn_80008E84(u32);

    lbl_1_data_3D928.unk_0 = fn_80008E84(lbl_1_data_3D924);
}
/* fzgx:end fn_1_D2F50 */

/* fzgx:begin fn_1_D2F84 */
void fn_1_D2F84(void) {
    fn_80008E84(lbl_1_data_3D928.unk_0);
}
/* fzgx:end fn_1_D2F84 */
