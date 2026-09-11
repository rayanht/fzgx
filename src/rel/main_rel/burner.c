#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/burner.h"

extern u8 lbl_1_rodata_EB4[124];
extern void *lbl_801A6410;
extern void fn_1_46B4(void *, Obj_1_bss_6EA04_Target *, u8 *, u32);
extern f32 lbl_1_rodata_4104[59];
extern Obj_1_data_27DE0 *fn_1_986A4(Obj_1_data_27DE0 *obj);
extern void fn_800794F0(Obj_1_data_27DE0 *arg0, Obj_1_data_27DE0 *arg1, s32 arg2);
extern void fn_1_98804(Obj_1_data_27DE0 *obj);
extern void fn_1_9AF80(u32 arg0, u32 arg1, u32 arg2);
extern u32 lbl_1_rodata_4210;
extern void fn_80007AB4(u32 *arg0);
extern void fn_1_9CC6C(void *arg0, s32 arg1);
extern void lbl_8006D7B0(s32);
extern s32 lbl_8006D24C(f32, f32);
extern void mathutil_mtxA_rotate_x(s16);
extern void mathutil_mtxA_rotate_y(s32);
extern s32 strlen(const char *);
extern s32 fn_8006FC5C(const char *, const char *, s32);
extern s32 fn_8006FC1C(const char *, const char *);
extern u32 fn_1_9D260(void);
extern s32 fn_1_3F0C8(void);
extern u8 lbl_1_bss_8E51D;
extern u8 fn_1_7B074(void);
extern void fn_8006FDEC(void);
extern void fn_80071718(u32);
extern void fn_800711A8(u32);
extern void fn_1_55A84(void (*callback)(void), void *arg0, s32 arg1, s32 arg2);
extern void *fn_1_12F118(void);
extern void *fn_1_36AD0(void);
extern void fn_1_14F6F8(u8 arg0, u8 arg1, u8 arg2, void *arg3);
extern void fn_80008BA8(void *arg0, const void *arg1, int arg2);

extern u32 lbl_1_rodata_4210;
extern void fn_80007AB4(u32 *arg0);
extern void fn_1_9CC6C(void *arg0, s32 arg1);
extern void fn_1_9D360(void);

/* fzgx:begin fn_1_402A4 */
s16 fn_1_402A4(u32 index) {
    u8 *table0;
    u8 *table1;
    const s16 *table2;

    table0 = (u8 *)&lbl_1_data_2B0D4;
    table1 = lbl_1_data_2B144;
    table2 = (const s16 *)lbl_1_rodata_EB4;
    return table2[table1[table0[index]] - 1];
}
/* fzgx:end fn_1_402A4 */

/* fzgx:begin fn_1_981C4 noprologue */
#include "types.h"

struct fn_1_981C4_lbl_1_bss_6EA00 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};
struct fn_1_981C4_lbl_801A6410 {
    u32 unk_0;
};

extern struct fn_1_981C4_lbl_1_bss_6EA00 lbl_1_bss_6EA00;
extern struct fn_1_981C4_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_4630(u32, u32, u32, u32);
extern u32 lbl_1_data_27E08;

void fn_1_981C4(void) {
    struct fn_1_981C4_lbl_1_bss_6EA00 *p_lbl_1_bss_6EA00;
    u32 v0;
    u32 t0;
    p_lbl_1_bss_6EA00 = (struct fn_1_981C4_lbl_1_bss_6EA00 *)&lbl_1_bss_6EA00;
    t0 = fn_1_4630(lbl_801A6410.unk_0, (0x20000 + 12576), (u32)&lbl_1_data_27E08, 378);
    p_lbl_1_bss_6EA00->unk_4 = t0;
    *(u32 *)((u8 *)t0 + 4) = 0;
    v0 = p_lbl_1_bss_6EA00->unk_4;
    *(u32 *)((u8 *)v0 + 0) = 0;
    p_lbl_1_bss_6EA00->unk_8 = 0;
    p_lbl_1_bss_6EA00->unk_C = 0;
}
/* fzgx:end fn_1_981C4 */

/* fzgx:begin fn_1_98230 */
typedef struct BurnerNode BurnerNode;
typedef struct BurnerEntry BurnerEntry;
typedef void (*BurnerCallback)(BurnerNode *, BurnerEntry *);

struct BurnerNode {
    u8 pad_0[0x4];
    BurnerNode *next;
    u32 index;
};

struct BurnerEntry {
    u8 pad_0[0x8];
    BurnerCallback callback;
    u8 pad_C[0x8];
};

/* Dispatchs each queued burner callback, then advances the burner frame. */
void fn_1_98230(void) {
    BurnerNode *node = (BurnerNode *)lbl_1_bss_6EA04->unk_4;

    while (node != 0) {
        BurnerNode *next = node->next;
        BurnerEntry *entry =
            (BurnerEntry *)((u8 *)&lbl_1_data_27DE0 + node->index * 0x14);

        entry->callback(node, entry);
        node = next;
    }

    lbl_1_bss_6EA08 += 1;
    if ((s32)lbl_1_bss_6EA08 >= 4) {
        lbl_1_bss_6EA08 = 0;
    }
}
/* fzgx:end fn_1_98230 */

/* fzgx:begin fn_1_982C4 */
extern Obj_1_bss_6EA04_Target *lbl_1_bss_6EA04;  // array of 0x4AC-byte records

typedef struct Fn1982C4Node Fn1982C4Node;

struct Fn1982C4Node {
    u8 pad_0[0x4];
    Fn1982C4Node *next;
    u32 index;
};

typedef struct {
    u8 pad_0[0x4];
    void (*callback)(Fn1982C4Node *);
    u8 pad_8[0xC];
} Fn1982C4Entry;

void fn_1_982C4(void) {
    Fn1982C4Node *node = (Fn1982C4Node *)lbl_1_bss_6EA04->unk_4;

    while (node != 0) {
        Fn1982C4Node *next = node->next;
        Fn1982C4Entry *entry = (Fn1982C4Entry *)&lbl_1_data_27DE0;
        entry = entry + node->index;
        entry->callback(node);
        node = next;
    }

    fn_1_46B4(lbl_801A6410, lbl_1_bss_6EA04, lbl_1_data_27E08, 0x1d0);
}
/* fzgx:end fn_1_982C4 */

/* fzgx:begin fn_1_9835C */
typedef struct BurnerNode BurnerNode;
typedef struct BurnerEntry BurnerEntry;

struct BurnerNode {
    u8 pad_0[0x4];
    BurnerNode *next;
    u32 index;
};

typedef void (*BurnerCallback)(BurnerNode *, BurnerEntry *);

struct BurnerEntry {
    u8 pad_0[0xC];
    BurnerCallback callback;
    u8 pad_10[0x4];
};

void fn_1_9835C(void) {
    BurnerNode *node = (BurnerNode *)lbl_1_bss_6EA04->unk_4;

    while (node != 0) {
        BurnerNode *next = node->next;
        BurnerEntry *entry =
            (BurnerEntry *)((u8 *)&lbl_1_data_27DE0 + node->index * 0x14);
        entry->callback(node, entry);
        node = next;
    }
}
/* fzgx:end fn_1_9835C */

/* fzgx:begin fn_1_983CC */
typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Fn1983CCVec3;

typedef struct {
    u8 unk_00[0x03];
    s8 unk_03;
    u8 unk_04[0x3C];
    s8 unk_40;
    u8 unk_41[0x03];
    Fn1983CCVec3 unk_44;
    Fn1983CCVec3 unk_50;
    f32 unk_5C;
    f32 unk_60;
    f32 unk_64;
    f32 unk_68;
    f32 unk_6C;
    f32 unk_70;
    f32 unk_74;
} Fn1983CCEntry;

typedef struct {
    u8 unk_00[0x08];
    s32 unk_08;
    Fn1983CCVec3 unk_0C;
    Fn1983CCVec3 unk_18;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    u8 unk_40[0x08];
    void *unk_48;
    u8 unk_4C[0x458];
    f32 unk_4A4;
} Fn1983CCWorkData;

typedef union {
    Fn1983CCWorkData data;
    u8 raw[0x4B0];
} Fn1983CCWork;

extern const f32 lbl_1_rodata_4100;
extern void *memset(void *dest, int value, u32 size);
extern void fn_1_98640(Fn1983CCWork *work);

void fn_1_983CC(void *arg0, Fn1983CCEntry *entries) {
    Fn1983CCWork work;
    Fn1983CCEntry *entry;
    s32 i;

    memset(&work, 0, 0x4AC);
    work.data.unk_48 = arg0;
    entry = entries;
    for (i = 0; i < entries->unk_03; i++) {
        work.data.unk_08 = entry->unk_40;
        work.data.unk_18 = entry->unk_50;
        work.data.unk_0C = entry->unk_44;
        work.data.unk_24 = entry->unk_5C / lbl_1_rodata_4100;
        work.data.unk_28 = entry->unk_60;
        work.data.unk_2C = entry->unk_64;
        work.data.unk_30 = entry->unk_68;
        work.data.unk_34 = entry->unk_6C;
        work.data.unk_38 = entry->unk_70;
        work.data.unk_3C = entry->unk_74;
        work.data.unk_4A4 = lbl_1_bss_6EA00;
        fn_1_98640(&work);
        entry = (Fn1983CCEntry *)((u8 *)entry + 0x38);
    }
}
/* fzgx:end fn_1_983CC */

/* fzgx:begin fn_1_984F0 */
typedef struct BurnerNode BurnerNode;

struct BurnerNode {
    u8 pad_0[0x4];
    BurnerNode *next;
    u32 index;
    u8 pad_C[0x3C];
    u32 key;
};

typedef void (*BurnerCallback)(BurnerNode *, void *);

extern void fn_1_98840(BurnerNode *node);
extern void fn_1_987D0(BurnerNode *node);

void fn_1_984F0(void *object) {
    BurnerNode *node = (BurnerNode *)lbl_1_bss_6EA04->unk_4;
    u8 *table = (u8 *)&lbl_1_data_27DE0;

    while (node != 0) {
        BurnerNode *next = node->next;

        if (node->key == (u32)object) {
            BurnerCallback callback = *(BurnerCallback *)(table + node->index * 0x14 + 0x4);
            callback(node, table + node->index * 0x14);
            fn_1_98840(node);
            fn_1_987D0(node);
        }

        node = next;
    }
}
/* fzgx:end fn_1_984F0 */

/* fzgx:begin fn_1_98590 */
typedef struct Fn198590Node Fn198590Node;

struct Fn198590Node {
    u8 unk_00[0x04];
    Fn198590Node *next;
    u8 unk_08[0x6C];
    f32 unk_74;
    u8 unk_78[0x42C];
    f32 unk_4A4;
};

// Reset each linked burner's timing values and advance the shared update slot.
void fn_1_98590(void) {
    Fn198590Node *node = (Fn198590Node *)lbl_1_bss_6EA04->unk_4;
    f32 value = lbl_1_rodata_4104[0];

    while (node != 0) {
        Fn198590Node *next = node->next;

        node->unk_74 = value;
        node->unk_4A4 = value;
        node = next;
    }

    lbl_1_bss_6EA08 += 1;
    if ((s32)lbl_1_bss_6EA08 >= 4) {
        lbl_1_bss_6EA08 = 0;
    }
}
/* fzgx:end fn_1_98590 */

/* fzgx:begin fn_1_985EC */
typedef struct BurnerEntry BurnerEntry;

struct BurnerEntry {
    u8 unk_00[0x04];
    BurnerEntry *next;
    u8 unk_08[0x40];
    u32 key;
    u8 unk_4C[0x28];
    f32 value;
    u8 unk_78[0x430];
    u32 flags;
};

// Reset matching burner entries while walking the global entry list.
void fn_1_985EC(u32 key) {
    BurnerEntry *node = (BurnerEntry *)lbl_1_bss_6EA04->unk_4;
    f32 value = lbl_1_rodata_4104[0];
    u32 zero = 0;

    while (node != 0) {
        BurnerEntry *next = node->next;
        if (node->key == key) {
            node->value = value;
            node->flags = zero;
        }
        node = next;
    }
}
/* fzgx:end fn_1_985EC */

/* fzgx:begin fn_1_98634 */
void fn_1_98634(f32 value) {
    lbl_1_bss_6EA00 = value;
}
/* fzgx:end fn_1_98634 */

/* fzgx:begin fn_1_98640 */
void fn_1_98640(Obj_1_data_27DE0 *obj) {
    Obj_1_data_27DE0 *result = fn_1_986A4(obj);

    fn_800794F0(result, obj, 0x4ac);
    fn_1_98804(result);
    ((void (*)(Obj_1_data_27DE0 *))(*(u32 *)((u8 *)&lbl_1_data_27DE0 +
        result->unk_8 * 0x14)))(result);
}
/* fzgx:end fn_1_98640 */

/* fzgx:begin fn_1_987D0 */
void fn_1_987D0(u32 address) {
    Obj_1_bss_6EA04_Target *object;
    u32 offset;

    object = lbl_1_bss_6EA04;
    offset = (address - ((u32)object + 0x80)) / 1196;
    object->pad_8[offset] = 0;
}
/* fzgx:end fn_1_987D0 */

/* fzgx:begin fn_1_98804 noprologue */
#include "types.h"

extern struct fn_1_98804_lbl_1_bss_6EA04 lbl_1_bss_6EA04;

struct fn_1_98804_Arg0 {
    u32 unk_0;
    u32 unk_4;
};
struct fn_1_98804_lbl_1_bss_6EA04 {
    u32 unk_0;
};

void fn_1_98804(struct fn_1_98804_Arg0 *arg0) {
    u32 v0;
    v0 = *(u32 *)((u8 *)lbl_1_bss_6EA04.unk_0 + 4);
    arg0->unk_4 = v0;
    arg0->unk_0 = lbl_1_bss_6EA04.unk_0;
    if (v0 != 0) {
    *(u32 *)((u8 *)v0 + 0) = (u32)arg0;
    }
    *(u32 *)((u8 *)lbl_1_bss_6EA04.unk_0 + 4) = (u32)arg0;
}
/* fzgx:end fn_1_98804 */

/* fzgx:begin fn_1_98840 */
typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

void fn_1_98840(Node *node) {
    Node *next = node->next;
    Node *prev = node->prev;

    prev->next = next;
    if (next != 0) {
        next->prev = prev;
    }
}
/* fzgx:end fn_1_98840 */

/* fzgx:begin fn_1_988D8 */
// fn_1_988D8: empty in retail (single blr).
void fn_1_988D8(void) {
}
/* fzgx:end fn_1_988D8 */

/* fzgx:begin fn_1_9A0A4 */
// fn_1_9A0A4: empty in retail (single blr).
void fn_1_9A0A4(void) {
}
/* fzgx:end fn_1_9A0A4 */

/* fzgx:begin fn_1_9A578 */
// Advances the burner state and invokes the callback for the active entry.
void fn_1_9A578(void) {
    void (**callback)(void);

    if (lbl_1_data_2A7E0.unk_0 > 0) {
        fn_1_10302C();
        callback = (void (**)(void))&lbl_1_data_2ABAC;
        callback[lbl_1_data_2A7E0.unk_0 * 9 + 2]();
    }
}
/* fzgx:end fn_1_9A578 */

/* fzgx:begin fn_1_9A770 */
typedef void (*fn_1_9A770_callback)(void);

// Invokes the registered burner callback when one is installed.
void fn_1_9A770(void) {
    fn_1_9A770_callback callback = (fn_1_9A770_callback)lbl_1_data_2A7E0.unk_38;

    if (callback != 0) {
        callback();
    }
}
/* fzgx:end fn_1_9A770 */

/* fzgx:begin fn_1_9A7A8 */
void fn_1_9A7A8(u32 *value) {
    *(u32 *)((u8 *)&lbl_1_data_2A7E0 + 2) = *value;
}
/* fzgx:end fn_1_9A7A8 */

/* fzgx:begin fn_1_9AD20 */
void fn_1_9AD20(void) {
    fn_1_9AF80(lbl_1_bss_3BE0->unk_54, lbl_1_bss_3BE0->unk_48, 1);
}
/* fzgx:end fn_1_9AD20 */

/* fzgx:begin fn_1_9AD54 */
void fn_1_9AD54(void) {
    fn_1_9AF80(lbl_1_bss_3BE0->unk_54, lbl_1_bss_3BE0->unk_48, 0);
}
/* fzgx:end fn_1_9AD54 */

/* fzgx:begin fn_1_9AD88 */
// Seed the temporary value, then notify the active burner using its shared state.
void fn_1_9AD88(void) {
    u32 value = lbl_1_rodata_4210;

    fn_80007AB4(&value);
    fn_1_9CC6C((void *)lbl_1_bss_3BE0->unk_54, lbl_1_bss_3BE0->unk_48);
}
/* fzgx:end fn_1_9AD88 */

/* fzgx:begin fn_1_9ADCC */
typedef struct {
    u8 pad_0[0x8];
    u8 unk_8;
    u8 unk_9;
    u8 pad_A;
    s8 unk_B;
    s32 slots[4];
} BurnerEntry;

typedef struct {
    u8 pad_0[0x24];
    u32 unk_24;
} BurnerParent;

extern void fn_1_862D4(u32 arg0, void *arg1);
extern u32 fn_1_1FB80(void *arg0, s32 arg1);
extern u32 fn_1_41488(u32 arg0, void *arg1);
extern void fn_1_4270C(void *arg0, u32 arg1, u32 arg2);

void fn_1_9ADCC(Obj_1_data_2A7E0_At3C *arg0, s32 arg1) {
    s32 i;
    BurnerEntry *entry;
    s32 *slotp;
    s32 value;
    u32 temp_word;
    u8 temp[3];
    u32 ret;

    entry = (BurnerEntry *)arg0->unk_C;
    i = 0;
    while (i < (s32)arg0->unk_8) {
        if ((entry->unk_9 & lbl_1_data_2A7E0.unk_48) != 0 &&
            (arg1 == 0 || entry->unk_B >= 0)) {
            slotp = &entry->slots[lbl_1_data_2A7E0.unk_60];
            if (*slotp == -1) {
                if (arg1 == 0) {
                    if (entry->unk_B < 0) {
                        value = 1;
                    } else {
                        value = 0;
                    }
                } else {
                    fn_1_862D4(lbl_1_data_2A7E0.unk_5C, &temp_word);
                    if ((1 << (entry->unk_B + 0x10)) & fn_1_1FB80(&temp_word, -65536)) {
                        value = 1;
                    } else {
                        value = 0;
                    }
                }
                if (value) {
                    s32 j;
                    BurnerEntry *scan;
                    s32 slot;
                    u8 c;

                    scan = (BurnerEntry *)arg0->unk_C;
                    j = 0;
                    while (j < (s32)arg0->unk_8) {
                        slot = lbl_1_data_2A7E0.unk_60;
                        if (scan->slots[slot] >= 0) {
                            if ((scan->unk_9 & 1) != 0) {
                                scan->slots[slot] = -2;
                            } else {
                                scan->slots[slot] = -1;
                            }
                        }
                        j++;
                        scan = (BurnerEntry *)((u8 *)scan + 0x1c);
                    }
                    *slotp = 0;
                    arg0 = (Obj_1_data_2A7E0_At3C *)arg0->unk_4;
                    c = entry->unk_8;
                    temp[0] = 0x4d;
                    temp[1] = (u8)(c + 0x30);
                    temp[2] = 0;
                    ret = fn_1_41488(((BurnerParent *)arg0)->unk_24, temp);
                    if (ret == 0xffffffff) {
                        ret = 0;
                    }
                    fn_1_4270C(arg0, 0, ret & 0xffff);
                    return;
                }
            }
        }
        i++;
        entry = (BurnerEntry *)((u8 *)entry + 0x1c);
    }
}
/* fzgx:end fn_1_9ADCC */

/* fzgx:begin fn_1_9CC40 */
typedef struct {
    u8 pad[0x30];
    u32 unk_30;
    u32 unk_34;
} GlobalState;

extern GlobalState *lbl_801A66CC;

void fn_1_9CC40(void) {
    lbl_801A66CC->unk_30 = lbl_1_data_2A7E0.unk_68;
    lbl_801A66CC->unk_34 = lbl_1_data_2A7E0.unk_6C;
}
/* fzgx:end fn_1_9CC40 */

/* fzgx:begin fn_1_9CC6C */
extern Obj_1_data_2A7E0_At3C *lbl_801A66CC;

// Initializes the burner state and copies the current burner position into the global state.
void fn_1_9CC6C(void *arg0, s32 arg1) {
    if (arg0 != 0) {
        fn_1_9DB04();
        fn_1_9C724();
        fn_1_9BBE4(arg0, 0, arg1 - 1, 0);
        lbl_801A66CC->unk_30 = lbl_1_data_2A7E0.unk_68;
        lbl_801A66CC->unk_34 = lbl_1_data_2A7E0.unk_6C;
    }
}
/* fzgx:end fn_1_9CC6C */

/* fzgx:begin fn_1_9CCE8 */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern void fn_8006E294(Vec3 *);

void fn_1_9CCE8(s32 arg0) {
    Vec3 value;
    s32 result;

    switch (arg0) {
    case 1:
        lbl_8006D7B0(arg0);
        break;
    case 2:
        fn_8006E294(&value);
        result = lbl_8006D24C(value.z, value.y);
        mathutil_mtxA_rotate_x((s16)(result - 0x4000));
        break;
    case 3:
        fn_8006E294(&value);
        result = lbl_8006D24C(value.x, value.z);
        mathutil_mtxA_rotate_y(result);
        break;
    default:
        break;
    }
}
/* fzgx:end fn_1_9CCE8 */

/* fzgx:begin fn_1_9CD6C */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct {
    u8 pad[0x60];
} GlobalState;

extern f32 lbl_1_rodata_4260[16];
extern GlobalState *lbl_801A6D00;

extern void lbl_8006E1B0(void *, Vec3 *);
extern f32 lbl_8006D0B4(f32);
extern void lbl_8006DB74(void *);
extern void lbl_8006D848(f32);
extern void lbl_8006DFC4(void *);

#pragma opt_common_subs off
void fn_1_9CD6C(void *arg0, f32 arg1) {
    Vec3 value;
    f32 squared;
    f32 length;

    lbl_8006E1B0(arg0, &value);
    squared = value.x * value.x;
    squared = value.y * value.y + squared;
    squared = value.z * value.z + squared;
    length = lbl_8006D0B4(squared);

    if (length > lbl_1_rodata_4260[0] + arg1) {
        lbl_8006DB74((u8 *)lbl_801A6D00 + 0x60);
        lbl_8006D848((length - arg1) / length);
        lbl_8006DFC4((u8 *)lbl_801A6D00 + 0x60);
    }
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_9CD6C */

/* fzgx:begin fn_1_9CE1C */
typedef struct {
    u32 unk_00;
    const char *name;
} fn_1_9CE1C_BurnerEntry;

typedef struct {
    s32 count;
    u32 unk_04;
    fn_1_9CE1C_BurnerEntry *entries;
} fn_1_9CE1C_BurnerTable;

s32 fn_1_9CE1C(const char *arg0, s32 arg1) {
    fn_1_9CE1C_BurnerTable *table;
    fn_1_9CE1C_BurnerEntry *entries;
    s32 found;
    s32 count;
    const char *entry;
    s32 input_length;
    s32 entry_length;

    table = *(fn_1_9CE1C_BurnerTable **)&lbl_1_bss_384B4;
    if (table == 0) {
        return 0;
    }

    entries = table->entries;
    found = 0;

    switch (arg1) {
    case 0:
        count = table->count;
        while (count > 0) {
            entry = entries->name;
            if (fn_8006FC5C(entry, arg0, strlen(arg0)) != 0) {
                found = 1;
                break;
            }
            count--;
            entries++;
        }
        break;
    case 1:
        count = table->count;
        while (count > 0) {
            if (fn_8006FC1C(entries->name, arg0) != 0) {
                found = 1;
                break;
            }
            count--;
            entries++;
        }
        break;
    default:
        count = table->count;
        while (count > 0) {
            entry = entries->name;
            entry_length = strlen(entry);
            input_length = strlen(arg0);
            if (input_length <= entry_length &&
                fn_8006FC5C(entry + (entry_length - input_length), arg0, input_length) != 0) {
                found = 1;
                break;
            }
            count--;
            entries++;
        }
        break;
    }

    if (found != 0) {
        return (s32)entries;
    }
    return 0;
}
/* fzgx:end fn_1_9CE1C */

/* fzgx:begin fn_1_9D230 */
u32 fn_1_9D230(void) {
    return (fn_1_9D260() & 0xC) != 0;
}
/* fzgx:end fn_1_9D230 */

/* fzgx:begin fn_1_9D260 */
u32 fn_1_9D260(void) {
    u32 mode;
    u32 result;

    mode = lbl_1_data_2A7E0.unk_88;
    if (mode >= 1 && mode <= 4) {
        result = 1 << (mode - 1);
    } else {
        result = 1;
    }

    if (mode == 1 && (s16)fn_1_3F0C8() == 0x2a &&
        lbl_1_bss_8E51D != 0xa && lbl_1_bss_8E51D != 0x8) {
        result = 2;
    }

    return result;
}
/* fzgx:end fn_1_9D260 */

/* fzgx:begin fn_1_9D2EC */
void fn_1_9D2EC(void) {
    if (!fn_1_7B074()) {
        fn_8006FDEC();
        if (lbl_1_bss_384B8 != 0) {
            fn_80071718(lbl_1_bss_384B8);
            lbl_1_bss_384B8 = 0;
        }
        if (lbl_1_bss_384B4 != 0) {
            fn_800711A8(lbl_1_bss_384B4);
            lbl_1_bss_384B4 = 0;
        }
    }
}
/* fzgx:end fn_1_9D2EC */

/* fzgx:begin fn_1_9D360 noprologue */
#include "types.h"

typedef struct {
    u8 pad[0x1e];
    u8 count;
} Burner;

typedef struct {
    u8 pad[8];
    u8 *entries;
} fn_1_9D360_BurnerTable;

extern void *fn_80077A18(Burner *);
extern void fn_80077F8C(Burner *);

// Builds the burner's entry pointers from its index list, then finalizes it.
void fn_1_9D360(Burner *burner, fn_1_9D360_BurnerTable *table, u8 *indices) {
    void **out;
    s32 i;

    out = (void **)fn_80077A18(burner);
    i = 0;
    while (i < burner->count) {
        *out = table->entries + 0x88 + indices[i] * 0x18c;
        out++;
        i++;
    }
    fn_80077F8C(burner);
}
/* fzgx:end fn_1_9D360 */

/* fzgx:begin fn_1_9D3E8 */
void fn_1_9D3E8(void *arg0, s32 arg1, s32 arg2) {
    fn_1_55A84(fn_1_9D360, arg0, arg1, arg2);
}
/* fzgx:end fn_1_9D3E8 */

/* fzgx:begin fn_1_13EE60 */
typedef struct {
    u32 flags;
    u8 pad_4[0x819c];
    u8 unk_81a0;
    u8 pad_81a1[3];
    u8 unk_81a4;
    u8 pad_81a5[7];
    u8 unk_81ac;
    u8 pad_81ad[7];
    u8 unk_81b4;
    u8 pad_81b5[0xb];
} fn_1_13EE60_BurnerEntry;

void fn_1_13EE60(s16 arg0, s16 arg1, void *arg2) {
    void *base;
    fn_1_13EE60_BurnerEntry *entry;

    if (arg0 >= 0x29) {
        base = fn_1_12F118();
        if (base == fn_1_36AD0()) {
            entry = &((fn_1_13EE60_BurnerEntry *)base)[arg1];
        } else {
            entry = &((fn_1_13EE60_BurnerEntry *)base)[arg0 - 0x29];
        }
        if ((entry->flags & 0x40000000) != 0) {
            fn_1_14F6F8(entry->unk_81a4, entry->unk_81ac,
                        entry->unk_81b4, arg2);
        } else {
            fn_80008BA8(arg2,
                        (const u8 *)&lbl_1_data_28060 +
                            entry->unk_81a0 * 0xb4,
                        0xb4);
        }
    } else {
        fn_80008BA8(arg2,
                    (const u8 *)&lbl_1_data_28060 + arg0 * 0xb4,
                    0xb4);
    }
}
/* fzgx:end fn_1_13EE60 */

/* fzgx:begin fn_1_140EE8 */
extern f32 lbl_1_rodata_26F8[22];
extern u32 lbl_1_rodata_9194[10];
extern u8 lbl_1_data_2B144[24];
extern u8 lbl_1_rodata_85AC[60];
extern const f32 lbl_1_rodata_8658;
extern const f32 lbl_1_rodata_8BA8;
extern const f32 lbl_1_rodata_8A4C;
extern s8 fn_1_A5DC4(void);
extern const f32 lbl_1_rodata_91BC;
extern void fn_1_4E724(void *);

typedef struct {
    u32 words[22];
} LocalObj;

void fn_1_140EE8(u8 arg0, int arg1, int arg2) {
    u32 choices[10];
    LocalObj obj = *(LocalObj *)lbl_1_rodata_26F8;
    int index;
    if (arg2 != 0) {
        choices[0] = lbl_1_rodata_9194[0];
        choices[1] = lbl_1_rodata_9194[1];
        choices[2] = lbl_1_rodata_9194[2];
        choices[3] = lbl_1_rodata_9194[3];
        choices[4] = lbl_1_rodata_9194[4];
        choices[5] = lbl_1_rodata_9194[5];
        choices[6] = lbl_1_rodata_9194[6];
        choices[7] = lbl_1_rodata_9194[7];
        choices[8] = lbl_1_rodata_9194[8];
        choices[9] = lbl_1_rodata_9194[9];
        index = arg0 - 0x24;
        obj.words[0] = choices[index < 0 ? 0 : index > 9 ? 9 : index];
    } else {
        obj.words[0] = ((u32 *)lbl_1_rodata_85AC)[
            lbl_1_data_2B144[((u8 *)&lbl_1_data_2B0D4)[arg0]]
        ];
    }
    *(f32 *)&obj.words[1] = lbl_1_rodata_8658;
    *(f32 *)&obj.words[2] = lbl_1_rodata_8BA8;
    if (arg1 == 0) {
        ((u8 *)&obj)[0x3A] = 0xB4;
        ((u8 *)&obj)[0x39] = 0xB4;
        ((u8 *)&obj)[0x38] = 0xB4;
    }
    *(f32 *)&obj.words[11] = lbl_1_rodata_8A4C;
    obj.words[12] = 10;
    if ((s8)fn_1_A5DC4() || arg1 != 0) {
        *(f32 *)&obj.words[4] *= lbl_1_rodata_91BC;
        *(f32 *)&obj.words[5] *= lbl_1_rodata_91BC;
    }
    fn_1_4E724(&obj);
}
/* fzgx:end fn_1_140EE8 */
