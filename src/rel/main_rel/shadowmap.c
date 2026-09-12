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
extern f32 lbl_1_rodata_28B4[16];
extern void *GXGetTexBufferSize(int, int, int, int, int);
extern void *fn_1_45D0(void *, int, char *, int);
extern void GXInitTexObj(void *, void *, int, int, int, int, int, int);
extern void GXInitTexObjLOD(void *, int, int, f32, f32, f32, int, int, int);
extern void fn_80073778(void *, u32);
extern void fn_800724C8(void);
extern void fn_800745A4(u32, s32, s32, s32, s32, s32);
extern void fn_80072AB0(s32, s32, s32);
extern u32 fn_800371F8(u32, void *);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern void fn_80072D64(s32, s32, s32, s32, u8, s32);
extern void fn_80072CC4(s32, s32, s32, s32, s32);
extern void fn_80072E20(s32, s32, s32, s32, u8, s32);
extern void fn_80072864(u32);
extern void GXSetAlphaCompare(u32, u32, u32, u32, u32);
extern void fn_80074918(u8, s32, u8);
extern void lbl_8006D758(void);
extern void GXLoadPosMtxImm(void *arg0, int arg1);
extern void fn_8003462C(u32 size, u32 heap, u32 alignment);
extern void *lbl_801A6D00;
extern f32 lbl_1_rodata_28F4[23];
extern void fn_1_57DC0(void);
extern void *fn_1_548AC(u32 size);
extern void *fn_1_5448C(void *arg);
extern void fn_1_57E84(void);
extern void fn_1_5489C(void *arg0, void *arg1);
extern void lbl_8006DB74(void *arg);
extern void fn_80008BA8(void *dst, void *src, u32 size);

/* fzgx:begin fn_1_5672C */
#include "types.h"

typedef struct fn_1_5672C_ShadowMapEntry {
    int field_00;
    int field_04;
    f32 field_08;
    char unk_0c[0x30];
    void *field_3c;
    void *field_40;
    int field_44;
    int field_48;
} fn_1_5672C_ShadowMapEntry;

void fn_1_5672C(fn_1_5672C_ShadowMapEntry *entries, int count) {
    void *buffer;
    int i;
    fn_1_5672C_ShadowMapEntry *entry;
    f32 zero = lbl_1_rodata_28B4[0];

    entry = entries;
    i = 0;
    while (i < count) {
        buffer = GXGetTexBufferSize(0x40, 0x40, 0, 0, 0);
        entry->field_00 = 0;
        entry->field_04 = 0;
        entry->field_08 = zero;
        entry->field_3c = fn_1_45D0(lbl_801A6410, 0x20, (*(char (*)[12])&lbl_1_data_1C660), 0x67);
        entry->field_40 = fn_1_45D0(lbl_801A6410, (int)buffer, (*(char (*)[12])&lbl_1_data_1C660), 0x68);
        entry->field_44 = 0;
        entry->field_48 = 0;
        GXInitTexObj(entry->field_3c, entry->field_40, 0x40, 0x40, 0, 0, 0, 0);
        GXInitTexObjLOD(entry->field_3c, 1, 1, lbl_1_rodata_28B4[0],
                        lbl_1_rodata_28B4[0], lbl_1_rodata_28B4[0], 0, 0, 0);
        i++;
        entry++;
    }
}
/* fzgx:end fn_1_5672C */

/* fzgx:begin fn_1_56858 */
typedef struct fn_1_56858_ShadowMapEntry {
    char pad_00[0x3c];
    void *unk_3c;
    void *unk_40;
    char pad_44[0x08];
} fn_1_56858_ShadowMapEntry;

// Register each entry's resources, then clear it for reuse.
void fn_1_56858(fn_1_56858_ShadowMapEntry *entries, u32 count) {
    u32 index;
    fn_1_56858_ShadowMapEntry *current_entry;

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

/* fzgx:begin fn_1_571E8 */
#include "types.h"

typedef union fn_1_571E8_GXFifo {
    volatile f32 f32; /* write-gather FIFO: writes have side effects */
    volatile u8 u8;   /* write-gather FIFO: writes have side effects */
} fn_1_571E8_GXFifo;

enum { GX_FIFO_ADDR = 0xCC008000 }; /* fzgx-allow: A1 GX write-gather FIFO hardware address */
#define GXWGFifo (*(fn_1_571E8_GXFifo *)GX_FIFO_ADDR)

typedef struct fn_1_571E8_Vec3 {
    f32 x;
    f32 y;
    f32 z;
} fn_1_571E8_Vec3;

typedef struct fn_1_571E8_Arg0 {
    u8 pad_0[8];
    fn_1_571E8_Vec3 p0;
    fn_1_571E8_Vec3 p1;
    fn_1_571E8_Vec3 p2;
    fn_1_571E8_Vec3 p3;
    u32 unk_38;
    u32 unk_3C;
    u32 unk_40;
} fn_1_571E8_Arg0;

void fn_1_571E8(fn_1_571E8_Arg0 *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 x3;
    f32 y3;
    f32 z3;
    f32 x4;
    f32 y4;
    f32 z4;
    u32 loc_8;

    fn_80073778((void *)arg0->unk_38, 0);
    fn_800724C8();
    fn_8007245C(0x2200);
    fn_80074788(0);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(0);
    fn_80073C6C(0);
    fn_800745A4(0, 1, 4, 0x3C, 0, 0x7D);
    fn_800734A8(0, 0, 0, 0xFF);
    fn_80072AB0(0, 0, 0);
    loc_8 = arg0->unk_3C;
    fn_800371F8(1, &loc_8);
    fn_80072C24(0, 0xF, 0xF, 0xF, 2);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 7, 7, 4);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_800720B0(0);
    fn_80072864(2);
    GXSetAlphaCompare(4, 0x4F, 0, 3, 0xFF);
    fn_800728A8(1, 7, 6, 0);
    fn_80074918(1, arg0->unk_40, 0);
    lbl_8006D758();
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    fn_8003462C(0x80, 0, 4);

    z = arg0->p0.z;
    y = arg0->p0.y;
    x = arg0->p0.x;
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.f32 = lbl_1_rodata_28B4[0];
    GXWGFifo.f32 = lbl_1_rodata_28B4[0];

    z2 = arg0->p1.z;
    y2 = arg0->p1.y;
    x2 = arg0->p1.x;
    GXWGFifo.f32 = x2;
    GXWGFifo.f32 = y2;
    GXWGFifo.f32 = z2;
    GXWGFifo.f32 = lbl_1_rodata_28F4[0];
    GXWGFifo.f32 = lbl_1_rodata_28B4[0];

    z3 = arg0->p2.z;
    y3 = arg0->p2.y;
    x3 = arg0->p2.x;
    GXWGFifo.f32 = x3;
    GXWGFifo.f32 = y3;
    GXWGFifo.f32 = z3;
    GXWGFifo.f32 = lbl_1_rodata_28F4[0];
    GXWGFifo.f32 = lbl_1_rodata_28F4[0];

    z4 = arg0->p3.z;
    y4 = arg0->p3.y;
    x4 = arg0->p3.x;
    GXWGFifo.f32 = x4;
    GXWGFifo.f32 = y4;
    GXWGFifo.f32 = z4;
    GXWGFifo.f32 = lbl_1_rodata_28B4[0];
    GXWGFifo.f32 = lbl_1_rodata_28F4[0];

    fn_80074918(1, 3, 1);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
}
/* fzgx:end fn_1_571E8 */

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

/* fzgx:begin fn_1_5773C */
typedef union fn_1_5773C_GXFifo {
    volatile f32 f32; /* write-gather FIFO: writes have side effects */
    volatile u8 u8;   /* write-gather FIFO: writes have side effects */
} fn_1_5773C_GXFifo;

enum { GX_FIFO_ADDR = 0xCC008000 }; /* fzgx-allow: A1 GX write-gather FIFO hardware address */
#define GXWGFifo (*(fn_1_5773C_GXFifo *)GX_FIFO_ADDR)

typedef struct fn_1_5773C_Vec3 {
    f32 x;
    f32 y;
    f32 z;
} fn_1_5773C_Vec3;

void fn_1_5773C(fn_1_5773C_Vec3 *arg0, fn_1_5773C_Vec3 *arg1, u8 *arg2) {
    u32 color;
    f32 y;
    f32 z;
    f32 x;
    f32 y2;
    f32 z2;
    f32 x2;

    fn_1_57DC0();
    color = *(u32 *)arg2;
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    fn_8003462C(0xA8, 0, 2);
    z = arg0->z;
    y = arg0->y;
    x = arg0->x;
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.u8 = ((u8 *)&color)[0];
    GXWGFifo.u8 = ((u8 *)&color)[1];
    GXWGFifo.u8 = ((u8 *)&color)[2];
    GXWGFifo.u8 = ((u8 *)&color)[3];
    z2 = arg1->z;
    y2 = arg1->y;
    x2 = arg1->x;
    GXWGFifo.f32 = x2;
    GXWGFifo.f32 = y2;
    GXWGFifo.f32 = z2;
    GXWGFifo.u8 = ((u8 *)&color)[0];
    GXWGFifo.u8 = ((u8 *)&color)[1];
    GXWGFifo.u8 = ((u8 *)&color)[2];
    GXWGFifo.u8 = ((u8 *)&color)[3];
}
/* fzgx:end fn_1_5773C */

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

/* fzgx:begin fn_1_57CD0 */
typedef struct {
    u8 pad_0[0x4];
    void (*unk_4)(void);
    u8 pad_8[0x30];
    u32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    void *unk_40;
    Obj_1_data_1C670 unk_44;
} Fn1_57CD0_Object;

void fn_1_57CD0(u32 value, void *arg) {
    u32 size;
    Fn1_57CD0_Object *object;
    void *created;
    void *buffer;

    if ((u16)value < 2) {
        return;
    }

    object = fn_1_548AC(0x60);
    if (object == 0) {
        return;
    }

    size = (value & 0xffff) << 4;
    buffer = fn_1_548AC(size);
    if (buffer == 0) {
        return;
    }

    created = fn_1_5448C(arg);
    object->unk_4 = fn_1_57E84;
    object->unk_38 = 0xa8;
    object->unk_3C = (u16)value;
    object->unk_44 = lbl_1_data_1C670;
    fn_80008BA8(buffer, arg, size);
    object->unk_40 = buffer;
    lbl_8006DB74(object->pad_8);
    fn_1_5489C(created, object);
}
/* fzgx:end fn_1_57CD0 */

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
