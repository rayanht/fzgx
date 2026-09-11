#include "types.h"
extern u32 lbl_3_bss_A2454;
extern u8 lbl_3_data_3D14[60];
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32, u32, u8 *, int);
extern u8 lbl_3_bss_A2438[28];
extern const f32 lbl_3_rodata_740;
extern void fn_3_1ABD8(void *arg0, s16 x1, s16 y1, s16 x2, s16 y2, u32 *value);
extern void fn_3_1B130(void *, s16, s16, u32 *);
extern void fn_3_149AC(void);
extern void fn_3_1BA20(void *target, s16 x, s16 y, s16 z, s16 w, s32 *value);
extern void fn_3_1BF08(void *, s16, s16, s16, s16, u32 *);
extern u8 lbl_3_bss_A2458[8];
extern void fn_3_BD98(void);
extern s32 lbl_3_bss_A179C;
extern void fn_3_BEF0(void);
extern void fn_3_BE88(void);
extern void fn_3_156A8(void);
extern s16 lbl_3_bss_A2460[4];
extern void fn_80074188(s16, s16, s16, s16);
extern s16 lbl_3_bss_A248C[21];
extern void fn_1_5233C(void *, void *);
extern u8 lbl_3_data_4648[1320];

/* fzgx:begin fn_3_19C50 */
void fn_3_19C50(void) {
    fn_1_46B4(lbl_801A6410, lbl_3_bss_A2454, lbl_3_data_3D14, 0x294);
}
/* fzgx:end fn_3_19C50 */

/* fzgx:begin fn_3_19C94 */
u8 fn_3_19C94(void) {
    return lbl_3_bss_A2438[0xe];
}
/* fzgx:end fn_3_19C94 */

/* fzgx:begin fn_3_19CA4 */
void fn_3_19CA4(void) {
    *(u32 *)(lbl_3_bss_A2438 + 4) = (u32)-2147483648;
}
/* fzgx:end fn_3_19CA4 */

/* fzgx:begin fn_3_19CB8 */
void fn_3_19CB8(void) {
    *(u32 *)(lbl_3_bss_A2438 + 4) = 0x20000000;
}
/* fzgx:end fn_3_19CB8 */

/* fzgx:begin fn_3_19CCC */
void fn_3_19CCC(void) {
    *(u32 *)(lbl_3_bss_A2438 + 4) = 0x40000000;
}
/* fzgx:end fn_3_19CCC */

/* fzgx:begin fn_3_19CE0 */
extern u8 lbl_3_bss_A2438[28];

u32 fn_3_19CE0(void) {
    u32 v0;
    s32 v1;

    v1 = 0;
    v0 = *(u32 *)(lbl_3_bss_A2438 + 4);
    if (v0 == 0x80000000 || v0 == 0x40000000) {
        v1 = 1;
    }
    return (v1 & 0xFF);
}
/* fzgx:end fn_3_19CE0 */

/* fzgx:begin fn_3_19D14 */
typedef struct fn_3_19D14_CustomizeData {
    u8 _pad08[0x08];
    u32 value_08;
    u8 _pad0c[0x04];
    s16 value_10;
    s16 value_12;
    u8 _pad14[0x0c];
    void *value_20;
} fn_3_19D14_CustomizeData;

extern void fn_3_1AB34(void *, s16, s16, u32 *);

void fn_3_19D14(fn_3_19D14_CustomizeData *data) {
    u32 value = data->value_08;
    fn_3_1AB34(data->value_20, data->value_10, data->value_12, &value);
}
/* fzgx:end fn_3_19D14 */

/* fzgx:begin fn_3_19D50 */
void fn_3_19D50(void) {
    lbl_3_bss_A2438[12] = (lbl_3_bss_A2438[12] + 1) % 5;
}
/* fzgx:end fn_3_19D50 */

/* fzgx:begin fn_3_19D88 */
typedef struct Fn319D88Object {
    u8 pad_00[0x10];
    s16 value_10;
    s16 value_12;
    u8 pad_14[0x0c];
    void *value_20;
} Fn319D88Object;

void fn_3_19D88(Fn319D88Object *object) {
    u32 value = *(const u32 *)&lbl_3_rodata_740;
    fn_3_1AB34(object->value_20, object->value_10, object->value_12,
               (const f32 *)&value);
}
/* fzgx:end fn_3_19D88 */

/* fzgx:begin fn_3_19DC8 */
extern u32 fn_3_17820(void *);
extern void fn_3_1ADA4(void *, int, int, int, int);
extern void fn_3_1AE40(void *, int, int, int, int);

typedef struct Fn319DC8Object {
    u8 pad_00[0x04];
    u32 flags_04;
    u32 value_08;
    u8 pad_0c[0x14];
    void *value_20;
} Fn319DC8Object;

void fn_3_19DC8(Fn319DC8Object *object) {
    object->value_08 = fn_3_17820(object);
    if (object->flags_04 & 0xc0000000u) {
        fn_3_1ADA4(object->value_20, 0, 0, 64, 64);
    } else if (object->flags_04 & 0x30000000u) {
        fn_3_1AE40(object->value_20, 0, 0, 64, 64);
    }
}
/* fzgx:end fn_3_19DC8 */

/* fzgx:begin fn_3_19E40 */
typedef struct CustomizeData {
    u32 unk_00[2];
    u32 unk_08;
    u8 pad_0c[0x14];
    void *unk_20;
} CustomizeData;

extern u32 fn_3_17820(CustomizeData *);
extern void fn_3_1AEE4(void *, u32, u32, u32, u32);
extern void fn_3_1B008(void *, u32, u32, u32, u32);

void fn_3_19E40(CustomizeData *self) {
    self->unk_08 = fn_3_17820(self);
    if (self->unk_00[1] & 0x20000000) {
        fn_3_1AEE4(self->unk_20, 0, 0, 0x40, 0x40);
    } else if (self->unk_00[1] & 0x10000000) {
        fn_3_1B008(self->unk_20, 0, 0, 0x40, 0x40);
    }
}
/* fzgx:end fn_3_19E40 */

/* fzgx:begin fn_3_19EB8 */
typedef struct fn_3_19EB8_CustomizeData {
    u32 unk_00[2];
    u32 unk_08;
    s16 unk_0c;
    s16 unk_0e;
    s16 unk_10;
    s16 unk_12;
    u8 unk_14[0x0c];
    void *unk_20;
} fn_3_19EB8_CustomizeData;

void fn_3_19EB8(fn_3_19EB8_CustomizeData *self) {
    u32 local = self->unk_08;
    fn_3_1ABD8(self->unk_20, self->unk_0c, self->unk_0e, self->unk_10, self->unk_12, &local);
}
/* fzgx:end fn_3_19EB8 */

/* fzgx:begin fn_3_19EFC */
typedef struct fn_3_19EFC_CustomizeTool {
    u8 unk00[8];
    u32 unk08;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    s16 unk12;
    u8 unk14[12];
    void *unk20;
} fn_3_19EFC_CustomizeTool;

void fn_3_19EFC(fn_3_19EFC_CustomizeTool *self) {
    u32 value = self->unk08;
    fn_3_1ACE4(self->unk20, self->unk0c, self->unk0e, self->unk10, self->unk12, &value);
}
/* fzgx:end fn_3_19EFC */

/* fzgx:begin fn_3_19F40 */
typedef struct CustomizeObject {
    u8 pad08[8];
    u32 value08;
    u8 pad0c[4];
    s16 value10;
    s16 value12;
    u8 pad14[12];
    void *value20;
} CustomizeObject;

void fn_3_19F40(CustomizeObject *self) {
    u32 value;
    value = self->value08;
    fn_3_1B130(self->value20, self->value10, self->value12, &value);
}
/* fzgx:end fn_3_19F40 */

/* fzgx:begin fn_3_19F7C */
void fn_3_19F7C(void) {
    fn_3_149AC();
}
/* fzgx:end fn_3_19F7C */

/* fzgx:begin fn_3_19F9C */
typedef struct fn_3_19F9C_CustomizeTool {
    u8 pad00[8];
    u32 value08;
    s16 value0c;
    s16 value0e;
    s16 value10;
    s16 value12;
    u8 pad14[12];
    void *value20;
} fn_3_19F9C_CustomizeTool;

void fn_3_19F9C(fn_3_19F9C_CustomizeTool *tool) {
    u32 value;

    value = tool->value08;
    fn_3_1B4BC(tool->value20, tool->value0c, tool->value0e,
               tool->value10, tool->value12, &value);
}
/* fzgx:end fn_3_19F9C */

/* fzgx:begin fn_3_19FE0 */
typedef struct Fn319FE0Data {
    u8 _pad0[0x8];
    s32 value;
    s16 x;
    s16 y;
    s16 z;
    s16 w;
    u8 _pad14[0xC];
    void *target;
} Fn319FE0Data;

void fn_3_19FE0(Fn319FE0Data *data) {
    s32 value = data->value;
    fn_3_1BA20(data->target, data->x, data->y, data->z, data->w, &value);
}
/* fzgx:end fn_3_19FE0 */

/* fzgx:begin fn_3_1A024 */
typedef struct Fn3_1A024Data {
    u8 pad_00[8];
    u32 value_08;
    s16 value_0c;
    s16 value_0e;
    s16 value_10;
    s16 value_12;
    u8 pad_14[12];
    void *value_20;
} Fn3_1A024Data;

void fn_3_1A024(Fn3_1A024Data *data) {
    u32 value = data->value_08;
    fn_3_1BF08(data->value_20, data->value_0c, data->value_0e,
               data->value_10, data->value_12, &value);
}
/* fzgx:end fn_3_1A024 */

/* fzgx:begin fn_3_1A068 */
void fn_3_1A068(void) {
    if (lbl_3_bss_A2458[0] != 0) {
        fn_3_BD98();
        lbl_3_bss_A2458[0] = 0;
    } else if (lbl_3_bss_A179C != 0) {
        fn_3_BEF0();
        lbl_3_bss_A2458[0] = 1;
        *(u32 *)&lbl_3_bss_A2438[4] = 0x40000000;
        lbl_3_bss_A2438[0xE] = 0;
        lbl_3_bss_A179C = 0;
    } else {
        fn_3_BE88();
    }
}
/* fzgx:end fn_3_1A068 */

/* fzgx:begin fn_3_1A1B8 */
void fn_3_1A1B8(void) {
    fn_3_156A8();
}
/* fzgx:end fn_3_1A1B8 */

/* fzgx:begin fn_3_1A1D8 noprologue */
#include "types.h"

extern struct fn_3_1A1D8_lbl_1_bss_9F8 lbl_1_bss_9F8;
extern struct fn_3_1A1D8_lbl_3_bss_A2438 lbl_3_bss_A2438;
extern u32 fn_3_141A8(u32);
extern u32 fn_3_1441C(void);

struct fn_3_1A1D8_lbl_1_bss_9F8_0_E20 {
    u8 pad_0[0x10];
    u16 unk_10;
    u8 pad_12[0x2];
};
struct fn_3_1A1D8_lbl_3_bss_A2438 {
    u8 unk_0;
    u8 pad_1[0x3];
    u32 unk_4;
    u8 pad_8[0x6];
    u8 unk_E;
};
struct fn_3_1A1D8_lbl_1_bss_9F8 {
    struct fn_3_1A1D8_lbl_1_bss_9F8_0_E20 unk_0[1];
};

u32 fn_3_1A1D8(void) {
    u32 v0;
    u32 t0, t1;
    if (((lbl_1_bss_9F8.unk_0[lbl_3_bss_A2438.unk_0].unk_10 >> 8) & 0x1) != 0) {
    t0 = fn_3_1441C();
    v0 = t0;
    if ((t0 & 0xFF) == 0) {
    v0 = 0x80000000;
    t1 = fn_3_141A8(v0);
    v0 = t1;
    }
    }
    v0 = (u32)&lbl_1_bss_9F8;
    v0 = (u32)((u8 *)v0 + (lbl_3_bss_A2438.unk_0 * 20));
    if (((*(u16 *)((u8 *)v0 + 8) >> 9) & 0x1) != 0) {
    v0 = 0x40000000;
    lbl_3_bss_A2438.unk_4 = v0;
    lbl_3_bss_A2438.unk_E = 0;
    }
    return v0;
}
/* fzgx:end fn_3_1A1D8 */

/* fzgx:begin fn_3_1A264 noprologue */
#include "types.h"

struct fn_3_1A264_lbl_1_bss_9F8_10_E20 {
    u16 unk_0;
    u8 pad_2[0x12];
};
struct fn_3_1A264_lbl_3_bss_A2438 {
    u8 unk_0;
    u8 pad_1[0x3];
    u32 unk_4;
    u8 pad_8[0x6];
    u8 unk_E;
};
struct fn_3_1A264_lbl_1_bss_9F8 {
    u8 pad_0[0x10];
    struct fn_3_1A264_lbl_1_bss_9F8_10_E20 unk_10[1];
};

extern struct fn_3_1A264_lbl_1_bss_9F8 lbl_1_bss_9F8;
extern struct fn_3_1A264_lbl_3_bss_A2438 lbl_3_bss_A2438;
extern u32 fn_3_141A8(u32);
extern u32 fn_3_1443C(void);

void fn_3_1A264(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 t0, t1;
    if (((lbl_1_bss_9F8.unk_10[lbl_3_bss_A2438.unk_0].unk_0 >> 8) & 0x1) != 0) {
    t0 = fn_3_1443C();
    v0 = t0;
    if ((t0 & 0xFF) == 0) {
    v0 = 0x40000000;
    t1 = fn_3_141A8(v0);
    v0 = t1;
    }
    }
    v1 = arg0;
    if (((lbl_1_bss_9F8.unk_10[lbl_3_bss_A2438.unk_0].unk_0 >> 9) & 0x1) != 0) {
    v1 = 0x40000000;
    lbl_3_bss_A2438.unk_4 = v1;
    lbl_3_bss_A2438.unk_E = 0;
    }
}
/* fzgx:end fn_3_1A264 */

/* fzgx:begin fn_3_1AB34 */
extern u8 lbl_3_bss_A2438[28];
extern void fn_3_146C0(void *, s16, s16, s16, u32 *);

void fn_3_1AB34(void *obj, s16 start, s16 base, u32 *items) {
    s32 x;
    s16 width;
    s32 y;
    s32 half;
    s16 i;
    u16 size;
    u32 item;

    size = lbl_3_bss_A2438[0xc] * 2 + 1;
    half = size >> 1;
    i = -half;
    x = base + i;
    y = start - half;
    width = size;

    while (i <= half) {
        item = *items;
        fn_3_146C0(obj, y, x, width, &item);
        x++;
        i++;
    }
}
/* fzgx:end fn_3_1AB34 */

/* fzgx:begin fn_3_1ABD8 */
extern void fn_3_1B4BC(void *, s16, s16, s16, s16, u32 *);

void fn_3_1ABD8(void *arg0, s16 x1, s16 y1, s16 x2, s16 y2, u32 *value) {
    u32 result1;
    u32 result2;
    u32 result3;
    u32 result4;

    if (x1 > x2) {
        s16 temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y1 > y2) {
        s16 temp = y1;
        y1 = y2;
        y2 = temp;
    }

    result1 = *value;
    fn_3_1B4BC(arg0, x1, y1, x2, y1, &result1);
    result2 = *value;
    fn_3_1B4BC(arg0, x1, y2, x2, y2, &result2);
    result3 = *value;
    fn_3_1B4BC(arg0, x1, y1, x1, y2, &result3);
    result4 = *value;
    fn_3_1B4BC(arg0, x2, y1, x2, y2, &result4);
}
/* fzgx:end fn_3_1ABD8 */

/* fzgx:begin fn_3_1ACE4 */
extern void fn_3_1B4BC(void *, s32, s32, s32, s32, u32 *);

void fn_3_1ACE4(void *data, s32 first_a, s32 second_a, s32 first_b, s32 second_b,
                u32 *values) {
    s16 current;
    s16 limit;
    s16 count;
    u32 value;

    if ((s16)first_a > (s16)first_b) {
        s32 temp = first_a;
        first_a = first_b;
        first_b = temp;
    }
    if ((s16)second_a > (s16)second_b) {
        s32 temp = second_a;
        second_a = second_b;
        second_b = temp;
    }

    current = (s16)second_a;
    count = 0;
    limit = (s16)(second_b - current);
    while ((s16)count <= limit) {
        value = *values;
        fn_3_1B4BC(data, first_a, current, first_b, current, &value);
        current++;
        count++;
    }
}
/* fzgx:end fn_3_1ACE4 */

/* fzgx:begin fn_3_1F81C */
extern const f32 lbl_3_rodata_8F0[28];
extern const f32 lbl_3_rodata_990[297];
extern u32 lbl_801A66A0;

typedef struct CustomizeObject CustomizeObject;

typedef struct {
    u32 flags;
    u8 pad[0x1c];
} CustomizeEntry;

struct CustomizeObject {
    u8 pad0[0x18];
    u16 count;
    u8 pad1[0x26];
    CustomizeEntry entries[1];
    u8 pad2[0xc];
    f32 value;
};

typedef struct {
    CustomizeObject *object;
} CustomizeSlot;

typedef struct {
    u8 pad0[8];
    CustomizeSlot *slot;
} CustomizeManager;

typedef struct {
    u8 pad0[0xc];
    CustomizeManager *manager;
} CustomizeRoot;

extern CustomizeRoot lbl_1_bss_38460;
extern CustomizeObject *lbl_801A6D00;

extern void fn_1_56018(s32);
extern void lbl_8006D784(void *);
extern f32 lbl_8006D188(s16);
extern void fn_1_560F0(s32, void *);
extern void fn_80072558(void);
extern void fn_1_55210(CustomizeObject *);

void fn_3_1F81C(void) {
    s16 i;
    CustomizeObject *obj;
    CustomizeEntry *entry;
    u32 n;

    i = 0;
    obj = lbl_1_bss_38460.manager->slot->object;
    entry = obj->entries;
    for (; i < obj->count; i++, entry++) {
        if (entry->flags & 0x20000) {
            fn_1_56018(1);
            lbl_8006D784(&lbl_801A6D00->pad2[0]);
            n = lbl_801A66A0;
            lbl_801A6D00->value = lbl_3_rodata_8F0[0] -
                lbl_8006D188((s16)((s32)(lbl_3_rodata_990[0] * (f32)(n % 180)) + 0x4000));
            fn_1_560F0(0, &lbl_801A6D00->pad2[0]);
        }
    }
    fn_80072558();
    fn_1_55210(obj);
}
/* fzgx:end fn_3_1F81C */

/* fzgx:begin fn_3_2406C */
void fn_3_2406C(void) {
    fn_80074188(lbl_3_bss_A2460[0], lbl_3_bss_A2460[1],
                lbl_3_bss_A2460[2], lbl_3_bss_A2460[3]);
}
/* fzgx:end fn_3_2406C */

/* fzgx:begin fn_3_240A4 */
void fn_3_240A4(void) {
    fn_80074188(lbl_3_bss_A248C[0], lbl_3_bss_A248C[1],
                lbl_3_bss_A248C[2], lbl_3_bss_A248C[3]);
}
/* fzgx:end fn_3_240A4 */

/* fzgx:begin fn_3_240DC */
void fn_3_240DC(void *arg0, void *arg1) {
    fn_80074188(lbl_3_bss_A2460[0],
                lbl_3_bss_A2460[1],
                lbl_3_bss_A2460[2],
                lbl_3_bss_A2460[3]);
    fn_1_5233C(arg0, arg1);
}
/* fzgx:end fn_3_240DC */

/* fzgx:begin fn_3_268D0 */
extern f32 lbl_3_rodata_768[38];
extern void fn_80008BA8(u32 *, void *, s32);
extern u8 fn_1_151E20(u32, s32);
extern void fn_1_A9868(void);
extern s8 fn_1_A5DC4(void);
extern void fn_1_AA188(s32, s32, s32, s32, void *, void *, void *, void *);
extern void fn_1_AA538(void);
extern void fn_1_4E0F4(void);

typedef struct CustomizeObject {
    u8 pad000[4];
    f32 x;
    f32 y;
    u8 pad00c[0x2c];
    u32 resource;
    u8 pad03c[0x18];
    u8 pad054[0];
} CustomizeObject;

typedef union Color {
    u8 bytes[4];
    u32 word;
} Color;

void fn_3_268D0(CustomizeObject *self) {
    f32 *table = lbl_3_rodata_768;
    Color color;
    u32 value;
    s32 x0;
    s32 y0;

    fn_80008BA8(&value, &self->pad054, 4);
    color.bytes[0] = fn_1_151E20(value, 0);
    color.bytes[1] = fn_1_151E20(value, 1);
    color.bytes[2] = fn_1_151E20(value, 2);
    color.bytes[3] = 0xff;

    if (fn_1_A9868(), fn_1_A5DC4()) {
        u32 a;
        u32 b;
        u32 c;
        u32 d;

        f32 fx = self->x - table[317];
        f32 fy = self->y - table[29];
        d = self->resource;
        c = color.word;
        b = c;
        a = d;
        fn_1_AA188((s32)fx, (s32)fy, 0x81, 0xb, &a, &b, &c, &d);
    } else {
        u32 a;
        u32 b;
        u32 c;
        u32 d;

        f32 fx = self->x - table[338];
        f32 fy = self->y - table[29];
        d = self->resource;
        c = color.word;
        b = c;
        a = d;
        fn_1_AA188((s32)fx, (s32)fy, 0xaa, 0xb, &a, &b, &c, &d);
    }
    fn_1_AA538();
    fn_1_4E0F4();
}
/* fzgx:end fn_3_268D0 */

/* fzgx:begin fn_3_2B750 */
u32 fn_3_2B750(s16 arg0, s16 arg1) {
    return *(u32 *)(lbl_3_data_4648 + arg0 * 0x18 + arg1 * 4);
}
/* fzgx:end fn_3_2B750 */

/* fzgx:begin fn_3_2B774 */
// fn_3_2B774: empty in retail (single blr).
void fn_3_2B774(void) {
}
/* fzgx:end fn_3_2B774 */
