#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/phys.h"

extern void lbl_8006DCA4(void *base, void *arg);
extern void fn_1_A71AC(void);
extern void fn_8006F828(void *base, f32 *out);
extern void fn_1_E4A38(void *base, s32 x, s32 y, void *arg);
extern void fn_80008BEC(void *dst, void *value, u32 size);
extern void fn_80008BA8(void *dst, void *value, u32 size);
extern f32 lbl_1_rodata_67A8;
extern u32 lbl_1_rodata_6A8C[3];
extern u32 fn_80083970(const u8* left, const char* right);
extern u32 strlen(const char* string);
extern void fn_1_8CED0(void* object, s32 value0, s32 value1);
extern void fn_1_8D0A4(void* object);
extern void fn_800734A8(u32, u32, u32, u32);
extern void fn_80072EDC(u32, s32);
extern void fn_800745A4(u32, s32, s32, u32, s32, s32);
extern void fn_80073778(void *, u32);
extern void fn_80015C1C(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void lbl_8006DFFC(void *, void *, void *);
extern void GXLoadTexMtxImm(void *, u32, s32);
extern f32 lbl_1_rodata_6780[236];
extern f32 fn_1_A6FE8(void);
extern void fn_1_E8938(void);
extern void fn_1_8D1C8(void *object, void (*callback)(void), int arg);
extern u32 fn_1_3F8C0(void);
extern u32 fn_80008E84(u32 value);
extern u32 lbl_1_bss_7C94C[67];
extern void fn_1_EE530(void);
extern u8 lbl_1_bss_7ECB4[72];
extern void fn_1_BC29C(u8 *);
extern void fn_1_B9C0C(void);
extern void fn_1_1596DC(s32);
extern void fn_1_484CC(s32);

extern void fn_80008BEC(void *dst, void *value, u32 size);
extern void fn_80008BA8(void *dst, void *value, u32 size);

extern f32 lbl_1_rodata_67A8;
extern u32 lbl_1_rodata_6A8C[3];
extern void fn_80008BA8(void *dst, void *value, u32 size);
extern void fn_1_12EF80(s16 arg, s16 *out_group, s16 *out_entry);

/* fzgx:begin fn_1_E38D4 */
extern void fn_1_9C724(void);
extern s16 fn_1_E5430(s16);
extern void *fn_1_E54A8(s16, s16);
extern void fn_1_DD890(void *);
extern void fn_1_9CC40(void);

typedef struct {
    u8 pad_0[0xA];
    s16 unk_A;
    u8 pad_C[0x2];
    s16 unk_E;
    u8 pad_10[0x128];
    u64 flags_138;
    u8 pad_140[0x68];
} PhysEntry;

void fn_1_E38D4(void) {
    PhysEntry *entry;
    s16 group;
    s16 count;
    s16 i;

    fn_1_9C724();
    for (group = 0; group < 6; group++) {
        count = fn_1_E5430(group);
        entry = (PhysEntry *)fn_1_E54A8(group, 0);
        if (entry != 0 && entry->unk_A == 4 &&
            (entry->flags_138 & 0x80000000000ULL) == 0) {
            fn_80077E0C(*(void **)((u8 *)*(void **)((u8 *)*(void **)((u8 *)lbl_1_bss_3BE0->unk_54 +
                (entry->unk_E << 6) + 8) + 8) + 8));
            fn_80076134();
        }
        for (i = 0; i < count; i++, entry++) {
            if ((entry->flags_138 & 0x80000000000ULL) == 0) {
                fn_1_DD890(entry);
            }
        }
    }
    fn_1_9CC40();
}
/* fzgx:end fn_1_E38D4 */

/* fzgx:begin fn_1_E49D4 */
extern u32 fn_1_E3C38(u32, u32);
extern u32 fn_1_E5430(u32);
extern u32 fn_1_E54A8(u32, u32);

void fn_1_E49D4(void) {
    s32 v0;
    u32 t0, t1;
    v0 = 0;
    while ((s16)v0 < 6) {
    fn_1_E3C38((fn_1_E54A8(v0, 0)), (fn_1_E5430(v0)));
    v0++;
    }
}
/* fzgx:end fn_1_E49D4 */

/* fzgx:begin fn_1_E50F0 */
void fn_1_E50F0(void *base, void *arg) {
    struct {
        f32 values[2];
        u32 pad[2];
    } locals;

    lbl_8006DCA4(base, arg);
    fn_1_A71AC();
    fn_8006F828((char *)base + 0x54, locals.values);
    fn_1_E4A38(base, (s32)locals.values[0], (s32)locals.values[1], arg);
}
/* fzgx:end fn_1_E50F0 */

/* fzgx:begin fn_1_E5430 */
s16 fn_1_E5430(s16 index) {
    Obj_1_bss_7AE88 *obj = &lbl_1_bss_7AE88;

    switch (index) {
    case 0:
        return obj->unk_4;
    case 1:
        return obj->unk_C;
    case 2:
        return obj->unk_14;
    case 3:
        return obj->unk_1C;
    case 4:
        return obj->unk_24;
    case 5:
        return obj->unk_2C;
    default:
        return -1;
    }
}
/* fzgx:end fn_1_E5430 */

/* fzgx:begin fn_1_E54A8 */
void *fn_1_E54A8(s16 type, s16 index) {
    Obj_1_bss_7AE88 *base = &lbl_1_bss_7AE88;

    switch (type) {
    case 0:
        return (void *)((char *)base->unk_0 + index * 0x1a8);
    case 1:
        return (void *)((char *)base->unk_8 + index * 0x1a8);
    case 2:
        return (void *)((char *)base->unk_10 + index * 0x1a8);
    case 3:
        return (void *)((char *)base->unk_18 + index * 0x1a8);
    case 4:
        return (void *)((char *)base->unk_20 + index * 0x1a8);
    case 5:
        return (void *)((char *)base->unk_28 + index * 0x1a8);
    default:
        return (void *)0;
    }
}
/* fzgx:end fn_1_E54A8 */

/* fzgx:begin fn_1_E5724 */
s16 fn_1_E5724(void *base) {
    return *(s16 *)((char *)base + 0x8);
}
/* fzgx:end fn_1_E5724 */

/* fzgx:begin fn_1_E572C */
s16 fn_1_E572C(void *base) {
    return *(s16 *)((char *)base + 0xA);
}
/* fzgx:end fn_1_E572C */

/* fzgx:begin fn_1_E5734 */
typedef struct {
    u32 unk0;
    f32 value;
} E5734Obj;

// Returns the float at offset 4 of the object.
f32 fn_1_E5734(E5734Obj *self) {
    return self->value;
}
/* fzgx:end fn_1_E5734 */

/* fzgx:begin fn_1_E573C */
typedef struct {
    u8 unk0[0x100];
    s32 value;
} E573CObj;

s16 fn_1_E573C(E573CObj *self) {
    return self->value;
}
/* fzgx:end fn_1_E573C */

/* fzgx:begin fn_1_E5748 */
// Returns a pointer to the member at offset 0x54.
u8 *fn_1_E5748(u8 *self) {
    return self + 0x54;
}
/* fzgx:end fn_1_E5748 */

/* fzgx:begin fn_1_E5750 */
// Returns a pointer to the member at offset 0x44.
u8 *fn_1_E5750(u8 *self) {
    return self + 0x44;
}
/* fzgx:end fn_1_E5750 */

/* fzgx:begin fn_1_E5758 */
f32 fn_1_E5758(u8 *self) {
    return *(f32 *)(self + 0x50);
}
/* fzgx:end fn_1_E5758 */

/* fzgx:begin fn_1_E5760 */
u8 *fn_1_E5760(u8 *self) {
    return self + 0x78;
}
/* fzgx:end fn_1_E5760 */

/* fzgx:begin fn_1_E5768 */
u8 *fn_1_E5768(u8 *self) {
    return self + 0xF4;
}
/* fzgx:end fn_1_E5768 */

/* fzgx:begin fn_1_E57A4 */
f32 fn_1_E57A4(void *base) {
    return *(f32 *)((char *)base + 0x18);
}
/* fzgx:end fn_1_E57A4 */

/* fzgx:begin fn_1_E57AC */
f32 fn_1_E57AC(void *base) {
    return *(f32 *)((char *)base + 0x1c);
}
/* fzgx:end fn_1_E57AC */

/* fzgx:begin fn_1_E57B4 */
f32 fn_1_E57B4(void *base) {
    return *(f32 *)((char *)base + 0x20);
}
/* fzgx:end fn_1_E57B4 */

/* fzgx:begin fn_1_E57BC */
f32 fn_1_E57BC(void *base) {
    return *(f32 *)((char *)base + 0x24);
}
/* fzgx:end fn_1_E57BC */

/* fzgx:begin fn_1_E57C4 */
u32 fn_1_E57C4(void *base) {
    return *(u32 *)((char *)base + 0x148);
}
/* fzgx:end fn_1_E57C4 */

/* fzgx:begin fn_1_E57CC */
void *fn_1_E57CC(void *base) {
    return (char *)base + 0x2c;
}
/* fzgx:end fn_1_E57CC */

/* fzgx:begin fn_1_E57D4 */
void *fn_1_E57D4(void *base) {
    return (char *)base + 0x38;
}
/* fzgx:end fn_1_E57D4 */

/* fzgx:begin fn_1_E57DC */
void *fn_1_E57DC(void *base) {
    return (char *)base + 0x6c;
}
/* fzgx:end fn_1_E57DC */

/* fzgx:begin fn_1_E57E4 */
f32 fn_1_E57E4(void *base) {
    return *(f32 *)((char *)base + 0x84);
}
/* fzgx:end fn_1_E57E4 */

/* fzgx:begin fn_1_E57EC */
f32 fn_1_E57EC(void *base) {
    return *(f32 *)((char *)base + 0x28);
}
/* fzgx:end fn_1_E57EC */

/* fzgx:begin fn_1_E57F4 */
void fn_1_E57F4(void *base, f32 value) {
    *(f32 *)((char *)base + 0x4) = value;
}
/* fzgx:end fn_1_E57F4 */

/* fzgx:begin fn_1_E57FC */
// Initializes the object's 12-byte value, clearing it or copying from the source.
void fn_1_E57FC(void *object, void *source) {
    if (source == 0) {
        fn_80008BEC((u8 *)object + 0x44, 0, 0xc);
    } else {
        fn_80008BA8((u8 *)object + 0x44, source, 0xc);
    }
}
/* fzgx:end fn_1_E57FC */

/* fzgx:begin fn_1_E5840 */
// Clears or copies the object's 12-byte value at offset 0x78.
void fn_1_E5840(void *base, const void *value) {
    if (value == 0) {
        fn_80008BEC((char *)base + 0x78, 0, 0xc);
    } else {
        fn_80008BA8((char *)base + 0x78, (void *)value, 0xc);
    }
}
/* fzgx:end fn_1_E5840 */

/* fzgx:begin fn_1_E5884 */
// Resets the object's three-component value or copies a replacement into it.
void fn_1_E5884(void *base, void *value) {
    if (value == 0) {
        f32 reset_value = lbl_1_rodata_67A8;

        *(f32 *)((char *)base + 0xfc) = reset_value;
        *(f32 *)((char *)base + 0xf8) = reset_value;
        *(f32 *)((char *)base + 0xf4) = reset_value;
    } else {
        fn_80008BA8((char *)base + 0xf4, value, 0xc);
    }
}
/* fzgx:end fn_1_E5884 */

/* fzgx:begin fn_1_E58CC */
// Copies the supplied three-word value, or the shared default when no value is provided.
void fn_1_E58CC(void *base, const void *value) {
    if (value == 0) {
        u32 default_value[3];

        default_value[0] = lbl_1_rodata_6A8C[0];
        default_value[1] = lbl_1_rodata_6A8C[1];
        default_value[2] = lbl_1_rodata_6A8C[2];
        fn_80008BA8((char *)base + 0x128, default_value, 0xc);
    } else {
        fn_80008BA8((char *)base + 0x128, (void *)value, 0xc);
    }
}
/* fzgx:end fn_1_E58CC */

/* fzgx:begin fn_1_E5930 */
void fn_1_E5930(void *base, u32 unused, u32 mask138, u32 mask13c) {
    u32 value13c = *(u32 *)((char *)base + 0x13c);
    u32 value138 = *(u32 *)((char *)base + 0x138);
    *(u32 *)((char *)base + 0x13c) = value13c | mask13c;
    *(u32 *)((char *)base + 0x138) = value138 | mask138;
}
/* fzgx:end fn_1_E5930 */

/* fzgx:begin fn_1_E5970 */
void fn_1_E5970(void *base, f32 value) {
    *(f32 *)((char *)base + 0x18) = value;
}
/* fzgx:end fn_1_E5970 */

/* fzgx:begin fn_1_E5978 */
void fn_1_E5978(void *base, f32 value) {
    *(f32 *)((char *)base + 0x1c) = value;
}
/* fzgx:end fn_1_E5978 */

/* fzgx:begin fn_1_E5980 */
// fn_1_E5980: Store float value at offset 0x20 in base pointer
void fn_1_E5980(void *base, f32 value) {
    *(f32 *)((char *)base + 0x20) = value;
}
/* fzgx:end fn_1_E5980 */

/* fzgx:begin fn_1_E5988 */
void fn_1_E5988(void *base, void *value) {
    if (value == NULL) {
        fn_80008BEC((void *)((char *)base + 0x54), NULL, 0xC);
    } else {
        fn_80008BA8((void *)((char *)base + 0x54), value, 0xC);
    }

    if (value == NULL) {
        fn_80008BEC((void *)((char *)base + 0x60), NULL, 0xC);
    } else {
        fn_80008BA8((void *)((char *)base + 0x60), value, 0xC);
    }
}
/* fzgx:end fn_1_E5988 */

/* fzgx:begin fn_1_E5A0C */
void fn_1_E5A0C(void *base, void *value) {
    if (value == NULL) {
        fn_80008BEC((void *)((char *)base + 0x2C), NULL, 0xC);
    } else {
        fn_80008BA8((void *)((char *)base + 0x2C), value, 0xC);
    }
}
/* fzgx:end fn_1_E5A0C */

/* fzgx:begin fn_1_E5A50 */
void fn_1_E5A50(void *base, void *value) {
    if (value == NULL) {
        fn_80008BEC((void *)((char *)base + 0x38), NULL, 0xC);
    } else {
        fn_80008BA8((void *)((char *)base + 0x38), value, 0xC);
    }
}
/* fzgx:end fn_1_E5A50 */

/* fzgx:begin fn_1_E5A94 */
void fn_1_E5A94(void *base, void *value) {
    if (value == NULL) {
        fn_80008BEC((void *)((char *)base + 0x6C), NULL, 0xC);
    } else {
        fn_80008BA8((void *)((char *)base + 0x6C), value, 0xC);
    }
}
/* fzgx:end fn_1_E5A94 */

/* fzgx:begin fn_1_E5AD8 */
void fn_1_E5AD8(void *base, f32 value) {
    *(f32 *)((char *)base + 0x28) = value;
}
/* fzgx:end fn_1_E5AD8 */

/* fzgx:begin fn_1_E86FC */
typedef struct StringValueEntry {
    u32 value;
    const u8* string;
} StringValueEntry;

typedef struct StringValueTable {
    s32 count;
    u32 unused;
    StringValueEntry* entries;
} StringValueTable;

u32 fn_1_E86FC(StringValueTable* table, const char* string) {
    StringValueEntry* entry;
    u32 best_value;
    s32 best_length;
    s32 count;

    if (table == 0) {
        return 0;
    }

    entry = table->entries;
    count = table->count;
    best_length = 0;
    best_value = 0;

    while (count > 0) {
        u32 length;

        if (fn_80083970(entry->string, string) != 0) {
            length = strlen(string);
            if (entry->string[length] == 0) {
                length++;
            }
            if ((s32)length > best_length) {
                best_value = entry->value;
                best_length = length;
            }
        }

        count--;
        entry++;
    }

    return best_value;
}
/* fzgx:end fn_1_E86FC */

/* fzgx:begin fn_1_E87A4 */
void fn_1_E87A4(f64 value0, f64 value1) {
    s32 converted0;
    s32 converted1;
    void* object;

    converted0 = (s32)value0;
    converted1 = (s32)value1;
    object = (u8*)&lbl_1_bss_7AEB8 + 0x210;
    fn_1_8CED0(object, converted0, converted1);
    fn_1_8D0A4(object);
}
/* fzgx:end fn_1_E87A4 */

/* fzgx:begin fn_1_E87FC */
typedef struct {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
} PhysObj;

void fn_1_E87FC(PhysObj *obj) {
    u8 *entry;
    s16 i;
    Obj_1_bss_7AEB8 *global;
    u8 work[0x30];

    fn_800734A8(obj->unk_C, obj->unk_10, obj->unk_18, 4);
    fn_80072EDC(obj->unk_C, 1);
    fn_800745A4(obj->unk_10, 0, 0, obj->unk_14, 0, 0x7d);
    fn_80073778((u8 *)&lbl_1_bss_7AEB8 + 0x274, obj->unk_18);
    global = &lbl_1_bss_7AEB8;

    i = 0;
    entry = (u8 *)global;
    while (i < global->unk_1E4) {
        f32 value = global->unk_20C;
        fn_80015C1C(work, global->unk_1EC, global->unk_1F0,
                    global->unk_1F4, global->unk_1F8, global->unk_1FC,
                    global->unk_200, global->unk_204, global->unk_208, value);
        lbl_8006DFFC(work, entry + 4, work);
        GXLoadTexMtxImm(work, obj->unk_14, 0);
        entry += 0x30;
        i++;
    }

    obj->unk_C++;
    obj->unk_18++;
    obj->unk_14++;
    obj->unk_10++;
}
/* fzgx:end fn_1_E87FC */

/* fzgx:begin fn_1_E95B4 */
typedef struct {
    u8 pad_0[0x8];
    f32 unk_8;
    f32 unk_C;
} Camera;

extern Camera *game_camera_get(void);

void fn_1_E95B4(void) {
    f32 *table = lbl_1_rodata_6780;
    Obj_1_bss_7AEB8 *state;
    Obj_1_bss_7AEB8 *state_after;
    Obj_1_bss_7AEB8 *state_final;
    Camera *camera;
    f32 camera_y;

    if ((lbl_1_bss_7AEB8.unk_0 & (0xFFFFFFFFu << 31)) == 0) {
        return;
    }

    camera = game_camera_get();
    state = &lbl_1_bss_7AEB8;
    state->unk_254 = camera->unk_8;
    camera = game_camera_get();
    camera_y = state->unk_254;
    state_after = &lbl_1_bss_7AEB8;
    state_after->unk_258 = camera->unk_C;

    if (camera_y < table[10] || camera_y > table[233]) {
        state->unk_254 = table[234];
        state_after->unk_258 = fn_1_A6FE8();
    }

    state_final = &lbl_1_bss_7AEB8;
    state_final->unk_25C = table[12];
    state_final->unk_260 = table[235];
    fn_1_8D1C8((u8 *)state_final + 0x210, fn_1_E8938, 0);
}
/* fzgx:end fn_1_E95B4 */

/* fzgx:begin fn_1_E9680 noprologue */
#include "types.h"
#include "rel/main_rel/phys.h"

extern void fn_80008BEC(void* dst, int value, int size);

void fn_1_E9680(void) {
    u8* base = (u8*)&lbl_1_bss_7B180;
    u32* p0;
    u32* p1;
    u32* p2;
    u32* p3;
    u32* p4;
    u32* p5;
    u32* p6;
    u32* p7;
    u32* p8;
    u32* p9;
    int i;

    fn_80008BEC(base + 0x2c, 0, 0x13d8);
    fn_80008BEC(base + 0x1404, 0, 0x1fc);

    p0 = (u32*)(base + 0x1600);
    p1 = (u32*)(base + 0x1614);
    p2 = (u32*)(base + 0x1628);
    p3 = (u32*)(base + 0x163c);
    p4 = (u32*)(base + 0x1650);
    p5 = (u32*)(base + 0x1664);
    p6 = (u32*)(base + 0x1678);
    p7 = (u32*)(base + 0x168c);
    p8 = (u32*)(base + 0x16a0);
    p9 = (u32*)(base + 0x16b4);

    for (i = 5; i != 0; i--) {
        *p0++ = 0;
        *p1++ = 0;
        *p2++ = 0;
        *p3++ = 0;
        *p4++ = 0;
        *p5++ = 0;
        *p6++ = 0;
        *p7++ = 0;
        *p8++ = 0;
        *p9++ = 0;
    }

    *(s32*)(base + 0x16c8) = -1;
    *(u8*)(base + 0x16cc) = 0xff;
    *(u32*)(base + 0x16d0) = 0;
}
/* fzgx:end fn_1_E9680 */

/* fzgx:begin fn_1_E9C68 */
// Updates the active physics callback and refreshes its associated state.
void fn_1_E9C68(void) {
    u32 value;

    if ((s32)lbl_1_bss_7B188 == 0) {
        return;
    }

    if (*(s16 *)&lbl_1_bss_960 == 9) {
        value = fn_80008E84(fn_1_3F8C0());
        lbl_1_bss_7C85C.unk_0 = value;
    }

    if ((s32)lbl_1_data_3E52C >= 0) {
        ((void (**)(void))lbl_1_data_3E434)[lbl_1_data_3E52C]();
    }

    if (*(s16 *)&lbl_1_bss_960 == 9) {
        fn_80008E84(lbl_1_bss_7C85C.unk_0);
    }
}
/* fzgx:end fn_1_E9C68 */

/* fzgx:begin fn_1_EB074 */
void fn_1_EB074(u32 value) {
    lbl_1_bss_7C94C[0] = value;
}
/* fzgx:end fn_1_EB074 */

/* fzgx:begin fn_1_EB080 */
// Preserve the previous mode when switching to mode 11, then update the active mode.
void fn_1_EB080(int mode) {
    u32* state = (u32*)lbl_1_data_3E358;

    if ((int)lbl_1_bss_7B188 == 0) {
        return;
    }

    if (mode == 11) {
        state[0x1e0 / 4] = state[0x1d4 / 4];
    }

    state[0x1d8 / 4] = mode;
}
/* fzgx:end fn_1_EB080 */

/* fzgx:begin fn_1_EB200 */
// Return whether the active state is one of the physics states.
int fn_1_EB200(void) {
    if ((s32)lbl_1_bss_7B188 == 0) {
        return 0;
    }

    if ((s32)lbl_1_data_3E52C == 14 ||
        (s32)lbl_1_data_3E52C == 16 ||
        (s32)lbl_1_data_3E52C == 15) {
        return 1;
    }

    return 0;
}
/* fzgx:end fn_1_EB200 */

/* fzgx:begin fn_1_EB248 */
// Return whether the current state is one of the supported race states.
int fn_1_EB248(void) {
    if ((s32)lbl_1_bss_7B188 == 0) {
        return 0;
    }

    {
        s32 state = lbl_1_data_3E52C;

        if ((u32)(state - 9) <= 4 ||
            (u32)(state - 5) <= 2 ||
            state == 8) {
            return 1;
        }
    }

    return 0;
}
/* fzgx:end fn_1_EB248 */

/* fzgx:begin fn_1_EF924 */
void fn_1_EF924(void) {
    fn_1_EE530();
    lbl_1_data_3E52C = lbl_1_data_3E538;
    fn_1_BC29C(lbl_1_bss_7ECB4);
    fn_1_B9C0C();
    fn_1_1596DC(2);
    fn_1_484CC(2);
}
/* fzgx:end fn_1_EF924 */

/* fzgx:begin fn_1_EFA1C */
void fn_1_EFA1C(void) {
    fn_1_EE530();
    lbl_1_data_3E52C = lbl_1_data_3E538;
}
/* fzgx:end fn_1_EFA1C */

/* fzgx:begin fn_1_F22E4 */
// Maps a course selection to its associated data value.
s16 fn_1_F22E4(s32 arg) {
    s16 group;
    s16 entry;
    s32 index;

    fn_1_12EF80((s16)arg, &group, &entry);
    index = (group - 1) * 6 + entry;
    return (s16)((s32 *)lbl_1_data_3E53C)[index];
}
/* fzgx:end fn_1_F22E4 */

/* fzgx:begin fn_1_F2338 noprologue */
#include "types.h"

extern void fn_1_12EF80(s16 value, s16 *arg1, s16 *arg2);
extern u32 lbl_1_data_3E5B4[30];

u32 fn_1_F2338(s32 value, u32 target) {
    s16 group;
    s16 entry;
    u32 packed;
    u32 hour;
    u32 minute;
    u32 low;

    value = (s16)value;
    fn_1_12EF80(value, &group, &entry);
    packed = lbl_1_data_3E5B4[(group - 1) * 6 + entry];
    minute = (packed >> 12) & 0xff;
    hour = (packed >> 20) & 0xff;
    minute += 0xa;
    low = packed & 0xfff;

    if (minute > 0x3c) {
        minute -= 0x3c;
        hour += 1;
    }

    packed = (hour << 20) | (minute << 12) | low;
    if (packed > target) {
        return 1;
    }
    return 0;
}
/* fzgx:end fn_1_F2338 */

/* fzgx:begin fn_1_F2740 */
u32 fn_1_F2740(u32 a, u32 b) {
    if (a >= 6) {
        return 0;
    }
    if (b >= 6) {
        return 0;
    }
    return ((u32 *)lbl_1_data_3E5B4)[(a - 1) * 6 + b];
}
/* fzgx:end fn_1_F2740 */
