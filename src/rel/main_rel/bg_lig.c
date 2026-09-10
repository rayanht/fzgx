#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_lig.h"

extern void fn_80008BA8(void *arg0, void *arg1, int arg2);
extern u32 lbl_1_rodata_6490[4];
extern u32 lbl_801A63D0;
extern u32 fn_1_76504(s32, void *, s32);
extern void fn_1_7269C(u32, s32, u32);
extern void fn_1_5948(s32 index);
extern void fn_1_D8388(void *obj);
extern void fn_1_627C(s32 index);
extern void *fn_1_9D260(Obj_1_data_2A7E0 *data);
extern void fn_1_D7B7C(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_9AD88(void);
extern void *memset(void *dst, int value, u32 size);
extern void fn_1_D7EF4(void *, u32);
extern f32 lbl_1_rodata_6594[];
extern f32 lbl_1_rodata_6524[];
extern void lbl_8006DCA4(void);
extern s32 fn_1_54E34(void *obj, f32 value);
extern void *fn_1_54448(s32 value);
extern void *fn_1_548AC(s32 value);
extern void fn_1_D8878(void);
extern void fn_1_5489C(void *obj, void *arg);
extern void fn_1_D83E4(Obj_1_data_2A7E0_At3C *obj, s32 index);
extern void fn_1_D7A10(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_D8D58(Obj_1_data_2A7E0_At3C *obj, Obj_1_data_2A7E0_At3C *arg);
extern void fn_1_D9D8C(Obj_1_bss_7AD78 *obj, u32 arg, s32 index);
extern void fn_1_DA3A0(Obj_1_bss_7AD78 *obj);
extern void fn_1_E87FC(void);

/* fzgx:begin fn_1_D6680 */
// fn_1_D6680: returns a constant.
int fn_1_D6680(void) {
    return 0;
}
/* fzgx:end fn_1_D6680 */

/* fzgx:begin fn_1_D6688 */
// fn_1_D6688: returns a constant.
int fn_1_D6688(void) {
    return 1;
}
/* fzgx:end fn_1_D6688 */

/* fzgx:begin fn_1_D6690 */
// fn_1_D6690: returns a constant.
int fn_1_D6690(void) {
    return 0;
}
/* fzgx:end fn_1_D6690 */

/* fzgx:begin fn_1_D6698 */
// fn_1_D6698: returns a constant.
int fn_1_D6698(void) {
    return 0;
}
/* fzgx:end fn_1_D6698 */

/* fzgx:begin fn_1_D66A0 */
// fn_1_D66A0: returns a constant.
int fn_1_D66A0(void) {
    return 0;
}
/* fzgx:end fn_1_D66A0 */

/* fzgx:begin fn_1_D66A8 */
// fn_1_D66A8: returns a constant.
int fn_1_D66A8(void) {
    return 0;
}
/* fzgx:end fn_1_D66A8 */

/* fzgx:begin fn_1_D66B0 */
// fn_1_D66B0: returns a constant.
int fn_1_D66B0(void) {
    return 0;
}
/* fzgx:end fn_1_D66B0 */

/* fzgx:begin fn_1_D66B8 */
// fn_1_D66B8: empty in retail (single blr).
void fn_1_D66B8(void) {
}
/* fzgx:end fn_1_D66B8 */

/* fzgx:begin fn_1_D66BC */
int fn_1_D66BC(void *unused, void *arg)
{
    fn_80008BA8(arg, lbl_1_data_3DC38, 0x10);
    return 1;
}
/* fzgx:end fn_1_D66BC */

/* fzgx:begin fn_1_D66F4 */
// fn_1_D66F4: empty in retail (single blr).
void fn_1_D66F4(void) {
}
/* fzgx:end fn_1_D66F4 */

/* fzgx:begin fn_1_D66F8 */
struct fn_1_D66F8_Arg1 {
    u8 unk_0;
};
struct fn_1_D66F8_Arg2 {
    u8 unk_0;
};
struct fn_1_D66F8_lbl_801A66A0 {
    u32 unk_0;
};
extern struct fn_1_D66F8_lbl_801A66A0 lbl_801A66A0;
extern u32 lbl_1_rodata_6358;

void fn_1_D66F8(u8 arg0, u8 *arg1, s8 *arg2) {
    u32 sp8;

    sp8 = *(u32 *)((u8 *)(&lbl_1_rodata_6358) + 0);
    (*(u8 *)((u8 *)(arg1) + 0)) = *(u8 *)((u8 *)(((u8 *)(&sp8) + arg0)) + 0);
    (*(s8 *)((u8 *)(arg2) + 0)) = ((u32) lbl_801A66A0.unk_0 / (u32) ((arg0 + 1) * 0x1E)) & 3;
}
/* fzgx:end fn_1_D66F8 */

/* fzgx:begin fn_1_D6740 */
// fn_1_D6740: returns a constant.
int fn_1_D6740(void) {
    return 1;
}
/* fzgx:end fn_1_D6740 */

/* fzgx:begin fn_1_D720C */
void fn_1_D720C(void) {
    u32 local[4];
    u32 result;

    local[0] = lbl_1_rodata_6490[0];
    local[1] = lbl_1_rodata_6490[1];
    local[2] = lbl_1_rodata_6490[2];
    local[3] = lbl_1_rodata_6490[3];
    result = fn_1_76504(0x1d, local, 0);
    fn_1_7269C(result, 0, lbl_801A63D0);
}
/* fzgx:end fn_1_D720C */

/* fzgx:begin fn_1_D744C */
extern void fn_80008BA8(void *arg0, void *arg1, int arg2);
extern u32 lbl_1_rodata_6490[4];
extern u32 lbl_801A63D0;
extern u32 fn_1_76504(s32, void *, s32);
extern void fn_1_7269C(u32, s32, u32);
extern void fn_1_5948(s32 index);
extern void fn_1_D8388(void *obj);
extern void fn_1_627C(s32 index);
extern void *fn_1_9D260(Obj_1_data_2A7E0 *data);
extern void fn_1_D7B7C(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_9AD88(void);
extern void *memset(void *dst, int value, u32 size);
extern void fn_1_D7EF4(void *, u32);
extern f32 lbl_1_rodata_6594[];
extern f32 lbl_1_rodata_6524[];
extern void lbl_8006DCA4(void);
extern s32 fn_1_54E34(void *obj, f32 value);
extern void *fn_1_54448(s32 value);
extern void *fn_1_548AC(s32 value);
extern void fn_1_D8878(void);
extern void fn_1_5489C(void *obj, void *arg);

extern s32 fn_1_58C4(void);
extern void fn_1_5948(s32 index);
extern void fn_1_D8388();
extern void fn_1_627C(s32 index);

// Initializes each available background-light entry.
void fn_1_D744C(void) {
    Obj_1_data_2A7E0_At3C *obj;
    s32 count;
    s32 i;

    obj = lbl_1_data_2A7E0.unk_3C;
    count = fn_1_58C4();
    for (i = 0; i < count; i++) {
        fn_1_5948(i);
        fn_1_D8388(obj, i);
        fn_1_627C(i);
    }
}
/* fzgx:end fn_1_D744C */

/* fzgx:begin fn_1_D74C4 */
// Initializes background-light data and installs the completion callback.
void fn_1_D74C4(void) {
    Obj_1_bss_7AD78 *tmp;
    Obj_1_data_2A7E0_At3C *obj;
    Obj_1_data_2A7E0_At3C *arg;
    s32 count;
    s32 i;

    obj = lbl_1_data_2A7E0.unk_3C;
    arg = (Obj_1_data_2A7E0_At3C *)fn_1_9D260(&lbl_1_data_2A7E0);
    fn_1_9AD54();
    count = fn_1_58C4();
    for (i = 0; i < count; i++) {
        fn_1_5948(i);
        fn_1_D83E4(obj, i);
        fn_1_627C(i);
    }

    fn_1_D7A10(obj);
    fn_1_D8D58(obj, arg);
    if (obj->unk_1C58 != 0) {
        fn_1_D9D8C(&lbl_1_bss_7AD78, obj->unk_1C58, 0);
        fn_1_DA3A0(&lbl_1_bss_7AD78);
    }
    if (obj->unk_1C5C != 0) {
        tmp = (Obj_1_bss_7AD78 *)((u8 *)&lbl_1_bss_7AD78 + 0x20);
        fn_1_D9D8C(tmp, obj->unk_1C5C, 1);
        fn_1_DA3A0(tmp);
    }
    lbl_1_data_2A7E0.unk_2C = (u32)fn_1_E87FC;
}
/* fzgx:end fn_1_D74C4 */

/* fzgx:begin fn_1_D75CC noprologue */
#include "types.h"

typedef struct {
    u8 data[0xac];
} Sig_fn_1_D8D08_fn_1_D8D08_LigEntry;

typedef struct {
    u8 pad[0x6d4];
    s32 count;
    Sig_fn_1_D8D08_fn_1_D8D08_LigEntry entries[1];
} Sig_fn_1_D8D08_LigContainer;

struct fn_1_D75CC_lbl_1_data_2A7E0 {
    u8 pad_0[0x3C];
    u32 unk_3C;
};
extern struct fn_1_D75CC_lbl_1_data_2A7E0 lbl_1_data_2A7E0;
extern u32 lbl_1_bss_7AD78;
extern void fn_1_4404(void);
extern u32 fn_1_DA6A8(void *, u32);
extern void fn_80008BEC(void *, int, u32);
extern void fn_1_446C(void);
extern void fn_1_76BF8(void);
extern void fn_1_72648(void);
extern void fn_1_D8D08(Sig_fn_1_D8D08_LigContainer *);

void fn_1_D75CC(void) {
    u32 *temp_r31;
    u32 temp_r30;
    u32 temp_r4;
    u32 temp_r4_2;

    temp_r30 = lbl_1_data_2A7E0.unk_3C;
    fn_1_4404();
    temp_r4 = *(u32 *)((u8 *)(temp_r30) + 7256);
    if (temp_r4 != 0) {
        fn_1_DA6A8((void *)(&lbl_1_bss_7AD78), temp_r4);
        fn_80008BEC((void *)(&lbl_1_bss_7AD78), 0, 0x20U);
        (*(u32 *)((u8 *)(temp_r30) + 7256)) = 0U;
    }
    temp_r4_2 = *(u32 *)((u8 *)(temp_r30) + 7260);
    if (temp_r4_2 != 0) {
        temp_r31 = (u32 *)((u8 *)(&lbl_1_bss_7AD78) + 0x20);
        fn_1_DA6A8((void *)(temp_r31), temp_r4_2);
        fn_80008BEC((void *)(temp_r31), 0, 0x20U);
        (*(u32 *)((u8 *)(temp_r30) + 7260)) = 0U;
    }
    fn_1_446C();
    fn_1_76BF8();
    fn_1_72648();
    fn_1_D8D08((Sig_fn_1_D8D08_LigContainer *)((Sig_fn_1_D8D08_LigContainer *)(temp_r30)));
}
/* fzgx:end fn_1_D75CC */

/* fzgx:begin fn_1_D7688 */
extern void fn_1_D8784(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_D8EEC(Obj_1_data_2A7E0_At3C *obj, void *value);

void fn_1_D7688(void) {
    Obj_1_data_2A7E0_At3C *obj = lbl_1_data_2A7E0.unk_3C;
    void *value = fn_1_9D260(&lbl_1_data_2A7E0);
    fn_1_D8784(obj);
    fn_1_D7B7C(obj);
    fn_1_D8EEC(obj, value);
    fn_1_9AD88();
}
/* fzgx:end fn_1_D7688 */

/* fzgx:begin fn_1_D76EC */
// fn_1_D76EC: empty in retail (single blr).
void fn_1_D76EC(void) {
}
/* fzgx:end fn_1_D76EC */

/* fzgx:begin fn_1_D76F0 */
// Copies a three-component float vector into the indexed light buffer entry.
void fn_1_D76F0(const f32 *src, s16 index) {
    f32 *dst = (f32 *)lbl_1_data_2A7E0.unk_3C;

    dst[index * 3] = src[0];
    dst += index * 3;
    dst[1] = src[1];
    dst[2] = src[2];
}
/* fzgx:end fn_1_D76F0 */

/* fzgx:begin fn_1_D7724 */
typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Vec3Bits;

// Copies the indexed three-word light entry to the caller-provided buffer.
void fn_1_D7724(Vec3Bits *dst, s16 index) {
    u32 *base = (u32 *)lbl_1_data_2A7E0.unk_3C;
    Vec3Bits *src = (Vec3Bits *)(base + index * 3);

    *dst = *src;
}
/* fzgx:end fn_1_D7724 */

/* fzgx:begin fn_1_D79E4 */
void fn_1_D79E4(void *obj) {
    memset((u8 *)obj + 0x30, 0, 0x3c0);
}
/* fzgx:end fn_1_D79E4 */

/* fzgx:begin fn_1_D7B7C noprologue */
#include "types.h"

typedef struct {
    u8 pad0[0x24];
    f32 value;
    u8 pad28[0x4];
    s16 count;
    u8 pad2e[0x2];
} LigEntry;

typedef struct {
    u8 pad0[0x4];
    void (*callback)(void);
    LigEntry *entry;
} LigEvent;

extern void lbl_8006DCA4(void);
extern f32 lbl_1_rodata_6524[28];
extern s32 fn_1_54E34(LigEntry *entry, f32 value);
extern void *fn_1_5448C(LigEntry *entry);
extern LigEvent *fn_1_548AC(s32 size);
extern void fn_1_D7C44(void);
extern void fn_1_5489C(void *data, void *event);

void fn_1_D7B7C(LigEntry *base) {
    void *data;
    LigEntry *entry;
    s32 i;
    LigEvent *event;

    lbl_8006DCA4();

    for (i = 0; i < 0x14; i++) {
        entry = base + i + 1;
        if (entry->count > 0 &&
            fn_1_54E34(entry, lbl_1_rodata_6524[0] * entry->value)) {
            data = fn_1_5448C(entry);
            event = fn_1_548AC(0xc);
            if (event != 0) {
                event->callback = fn_1_D7C44;
                event->entry = entry;
                fn_1_5489C(data, event);
            }
        }
    }
}
/* fzgx:end fn_1_D7B7C */

/* fzgx:begin fn_1_D8388 */
extern u32 fn_1_58C4(void);

// Initializes each lighting entry while the lighting system is available.
void fn_1_D8388(void *obj) {
    u8 *entry = (u8 *)obj;
    s32 i;

    if (fn_1_58C4() < 2) {
        i = 0;
        do {
            fn_1_D7EF4(entry + 0x3f0, 0);
            i++;
            entry += 0x30;
        } while (i < 0xf);
    }
}
/* fzgx:end fn_1_D8388 */

/* fzgx:begin fn_1_D8784 */
typedef void (*LigCallback)(void);

typedef struct {
    u32 unk_00;
    LigCallback callback;
    void *data;
} LigCallbackObject;

typedef struct {
    u8 pad_000[0x3f0];
    u8 callback_data[0x24];
    f32 scale;
} fn_1_D8784_LigEntry;

typedef struct {
    u8 pad_000[0x6c0];
    f32 threshold;
} fn_1_D8784_LigObject;

extern u32 fn_1_58C4(fn_1_D8784_LigObject *obj);

// Queues callbacks for eligible lig entries.
void fn_1_D8784(fn_1_D8784_LigObject *obj) {
    void *callback_data;
    void *owner;
    u8 i;
    f32 factor;
    fn_1_D8784_LigEntry *entry;

    if (fn_1_58C4(obj) >= 2) {
        return;
    }
    if (obj->threshold < lbl_1_rodata_6594[0]) {
        return;
    }

    factor = lbl_1_rodata_6524[0];
    i = 0;
    for (; i < 0xf; i++) {
        lbl_8006DCA4();
        entry = (fn_1_D8784_LigEntry *)((u8 *)obj + (i * 0x30));
        callback_data = entry->callback_data;
        if (fn_1_54E34(callback_data, factor * entry->scale) != 0) {
            owner = fn_1_54448(0);
            {
                LigCallbackObject *callback = (LigCallbackObject *)fn_1_548AC(0xc);
                if (callback != 0) {
                    callback->callback = fn_1_D8878;
                    callback->data = callback_data;
                    fn_1_5489C(owner, callback);
                }
            }
        }
    }
}
/* fzgx:end fn_1_D8784 */

/* fzgx:begin fn_1_D8CA8 */
typedef struct {
    u8 pad_00[0x68];
    u32 field_68;
    u8 pad_6c[0x40];
} fn_1_D8CA8_LigEntry;

typedef struct {
    u8 pad_00[0x6d4];
    s32 count;
    fn_1_D8CA8_LigEntry entries[1];
} fn_1_D8CA8_LigObject;

extern void fn_1_103090(fn_1_D8CA8_LigEntry *entry);

void fn_1_D8CA8(fn_1_D8CA8_LigObject *obj) {
    s32 count = obj->count;
    fn_1_D8CA8_LigEntry *entry = obj->entries;

    while (count > 0) {
        entry->field_68 = 1;
        fn_1_103090(entry);
        count--;
        entry++;
    }
}
/* fzgx:end fn_1_D8CA8 */

/* fzgx:begin fn_1_D8D08 */
typedef struct {
    u8 data[0xac];
} fn_1_D8D08_LigEntry;

typedef struct {
    u8 pad[0x6d4];
    s32 count;
    fn_1_D8D08_LigEntry entries[1];
} LigContainer;

extern void fn_1_1030A4(fn_1_D8D08_LigEntry *entry);

void fn_1_D8D08(LigContainer *container) {
    s32 count = container->count;
    fn_1_D8D08_LigEntry *entry = container->entries;

    while (count > 0) {
        fn_1_1030A4(entry);
        count--;
        entry++;
    }
}
/* fzgx:end fn_1_D8D08 */

/* fzgx:begin fn_1_D8EEC */
typedef struct {
    u8 unk_0[0xac];
} fn_1_D8EEC_LigEntry;

typedef struct {
    u8 unk_0[0x6d4];
    s32 unk_6d4;
    fn_1_D8EEC_LigEntry unk_6d8[1];
} fn_1_D8EEC_LigObject;

extern void fn_1_103264(fn_1_D8EEC_LigEntry *entry, void *arg);

// Applies the operation to each entry in the object.
void fn_1_D8EEC(fn_1_D8EEC_LigObject *obj, void *arg) {
    s32 count = obj->unk_6d4;
    fn_1_D8EEC_LigEntry *entry = obj->unk_6d8;

    while (count > 0) {
        fn_1_103264(entry, arg);
        count--;
        entry++;
    }
}
/* fzgx:end fn_1_D8EEC */

/* fzgx:begin fn_1_D8F4C */
typedef struct {
    u8 pad_0[0x24];
    u32 unk_24;
} FnInputData;

typedef struct {
    FnInputData *unk_0;
} FnInput;

u32 fn_1_D8F4C(s32 index, FnInput *input) {
    FnInputData *data = input->unk_0;
    Obj_1_data_2A7E0_At3C *state = lbl_1_data_2A7E0.unk_3C;
    u32 value = data->unk_24;

    switch (index) {
    case 0:
        state->unk_6CC = value;
        break;
    case 1:
        state->unk_6D0 = value;
        break;
    case 2:
        if (state->unk_1C58 == 0) {
            state->unk_1C58 = (u32)data;
        }
        break;
    case 3:
        if (state->unk_1C5C == 0) {
            state->unk_1C5C = (u32)data;
        }
        break;
    }

    return 1;
}
/* fzgx:end fn_1_D8F4C */
