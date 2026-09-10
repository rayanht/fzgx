#include "types.h"
#include "rel/main_rel/globals.h"

extern struct ArenaData lbl_1_data_8;
extern u32 OSGetArenaLo(void);
extern u32 OSGetArenaHi(void);
extern void OSSetArenaLo(u32 arena_lo);
extern u16 lbl_1_bss_990[28];
extern u8 lbl_1_bss_D78;
extern u8 lbl_1_bss_DA6;
extern u32 lbl_1_bss_DB0[2];
extern u32 lbl_1_bss_DA8;
extern void fn_1_43A4(void);
extern u32 lbl_1_data_2C70;
extern void fn_80008E84(u32 value);
extern u32 lbl_1_bss_DAC;
extern struct fn_1_634_lbl_1_bss_54 lbl_1_bss_54;
extern u32 fn_8006FFC4(u32);
extern u32 fn_1_48780(void);
extern u32 lbl_801A66B4;
extern u32 lbl_801A66BC;
extern struct fn_1_904_lbl_1_bss_4 lbl_1_bss_4;
extern struct fn_1_914_lbl_1_bss_0 lbl_1_bss_0;
extern u16 lbl_1_bss_96A;
extern u32 fn_1_37E98(void);
extern u32 lbl_1_bss_96C;
extern u32 camera_set_state_flag(u32);
extern u32 fn_1_D31E0(u32);
extern struct fn_1_12B4_lbl_1_bss_962 lbl_1_bss_962;
extern u32 lbl_1_data_2A20;
extern u32 lbl_1_data_7C0;
extern u32 fn_1_15659C(u32);
extern u32 fn_80008BEC(void *, u32, u32);
extern u8 lbl_1_bss_978[];
extern u32 lbl_1_data_2B78;
extern u32 OSGetTick(u32);
extern u32 lbl_1_bss_D7C;
extern u8 lbl_1_bss_DA4;
extern char lbl_1_data_2C9C[20];
extern char lbl_1_data_2CB0[31];
extern void OSPanic(const char *message, int line, const char *file, ...);
extern void fn_80009AA8(u32 value, u32 count, const char *file, int line);
extern u32 fn_1_156754(u32);
extern u32 fn_1_A5864(void);
extern u32 fn_1_F7578(void);
extern struct fn_1_3C98_lbl_1_bss_DA5 lbl_1_bss_DA5;
extern u32 fn_80008EC8(u32, u32, u32);
extern u32 fn_800793D4(u32, u32, u32);
extern struct fn_1_48B0_lbl_801A6CF8 lbl_801A6CF8;
extern u32 lbl_801A6CFC;

/* fzgx:begin fn_1_634 */
struct fn_1_634_lbl_1_bss_54 {
    u32 unk_0;
};

void * fn_1_634(void) {
    fn_8006FFC4(lbl_1_bss_54.unk_0);
    return &lbl_1_bss_54;
}
/* fzgx:end fn_1_634 */

/* fzgx:begin fn_1_668 */
struct ArenaData {
    u32 *arena_lo;
    u32 arena_lo_size;
    u32 *aligned_lo;
    u32 aligned_lo_size;
};

void fn_1_668(void) {
    u32 arena_lo;
    u32 aligned_lo;

    arena_lo = OSGetArenaLo();
    OSGetArenaHi();
    *lbl_1_data_8.arena_lo = arena_lo;
    aligned_lo = (arena_lo + lbl_1_data_8.arena_lo_size + 0x1f) & ~0x1f;
    *lbl_1_data_8.aligned_lo = aligned_lo;
    aligned_lo = (aligned_lo + lbl_1_data_8.aligned_lo_size + 0x1f) & ~0x1f;
    OSSetArenaLo(aligned_lo);
}
/* fzgx:end fn_1_668 */

/* fzgx:begin fn_1_6D4 */
extern u32 fn_80008BEC(void *, u32, u32);

struct fn_1_6D4_Data {
    s16 unk_0;
    s16 unk_2;
    u16 unk_4;
    u16 unk_6;
    u16 unk_8;
    s16 unk_A;
    u8 unk_C[2];
    s16 unk_E;
    u8 pad_10[0x1e];
    s16 unk_2E;
    u8 pad_30[0x1e];
    s16 unk_4E;
    u8 pad_50[0x1e];
    s16 unk_6E;
    u8 pad_70[0x22];
    u16 unk_92;
    u8 pad_94[0xb];
    u8 unk_9F;
    u8 unk_A0;
    u8 unk_A1;
    u8 unk_A2;
    u8 pad_A3;
    u32 unk_A4;
    u8 pad_A8[0x84];
    u16 unk_12C;
    u16 unk_12E;
    u16 unk_130;
    u16 unk_132;
    u16 unk_134;
    u16 unk_136;
    u16 unk_138;
    u16 unk_13A;
    u16 unk_13C;
};

void fn_1_6D4(struct fn_1_6D4_Data *data) {
    fn_80008BEC(data, 0, 0x14c);
    data->unk_A4 = 0;
    fn_80008BEC(data->unk_C, 0, 0x80);
    data->unk_E = (u16)-1;
    data->unk_9F = 0;
    data->unk_2E = (u16)-1;
    data->unk_A0 = 0;
    data->unk_4E = (u16)-1;
    data->unk_A1 = 0;
    data->unk_6E = (u16)-1;
    data->unk_A2 = 0;
    data->unk_0 = (u16)-1;
    data->unk_2 = (u16)-1;
    data->unk_4 = 1;
    data->unk_6 = 0x1e;
    data->unk_8 = 0;
    data->unk_A = (u16)-1;
    data->unk_92 = 8;
    data->unk_12C = 0;
    data->unk_12E = 0;
    data->unk_130 = 0;
    data->unk_132 = 1;
    data->unk_134 = 1;
    data->unk_136 = 1;
    data->unk_138 = 1;
    data->unk_13C = 3;
    data->unk_13A = 0;
}
/* fzgx:end fn_1_6D4 */

/* fzgx:begin fn_1_8D4 */
void fn_1_8D4(void) {
    lbl_801A66B4 = lbl_801A66BC;
    fn_1_48780();
}
/* fzgx:end fn_1_8D4 */

/* fzgx:begin fn_1_904 */
struct fn_1_904_lbl_1_bss_4 {
    u32 unk_0;
};

u32 fn_1_904(void) {
    return lbl_1_bss_4.unk_0;
}
/* fzgx:end fn_1_904 */

/* fzgx:begin fn_1_914 */
struct fn_1_914_lbl_1_bss_0 {
    u32 unk_0;
};

u32 fn_1_914(void) {
    return lbl_1_bss_0.unk_0;
}
/* fzgx:end fn_1_914 */

/* fzgx:begin fn_1_924 */
u32 fn_1_924(void) {
    lbl_1_bss_96A = 36;
    return fn_1_37E98();
}
/* fzgx:end fn_1_924 */

/* fzgx:begin fn_1_950 */
// fn_1_950: empty in retail (single blr).
void fn_1_950(void) {
}
/* fzgx:end fn_1_950 */

/* fzgx:begin fn_1_954 */
// fn_1_954: empty in retail (single blr).
void fn_1_954(void) {
}
/* fzgx:end fn_1_954 */

/* fzgx:begin fn_1_958 */
// fn_1_958: empty in retail (single blr).
void fn_1_958(void) {
}
/* fzgx:end fn_1_958 */

/* fzgx:begin fn_1_E34 */
void fn_1_E34(void) {
    s32 v0;
    fn_1_A5864();
    fn_1_F7578();
    v0 = 0;
    do {
    fn_1_156754(v0);
    v0++;
    } while ((s32)v0 < 4);
}
/* fzgx:end fn_1_E34 */

/* fzgx:begin fn_1_E78 */
extern u32 fn_1_3BC0(u32);
extern u32 fn_1_A59AC(void);

void fn_1_E78(void) {
    u32 t0;
    t0 = fn_1_A59AC();
    fn_1_3BC0(t0);
}
/* fzgx:end fn_1_E78 */

/* fzgx:begin fn_1_1280 */
void fn_1_1280(u32 arg0) {
    lbl_1_bss_96C = arg0;
}
/* fzgx:end fn_1_1280 */

/* fzgx:begin fn_1_128C */
u32 fn_1_128C(void) {
    u32 t0;
    t0 = camera_set_state_flag(0);
    return fn_1_D31E0(t0);
}
/* fzgx:end fn_1_128C */

/* fzgx:begin fn_1_12B4 */
extern u32 OSReport(void *, ...);

struct fn_1_12B4_lbl_1_bss_962 {
    s16 unk_0;
};

void fn_1_12B4(void) {
    s16 v0;
    v0 = lbl_1_bss_962.unk_0;
    OSReport(&lbl_1_data_2A20, v0, ((u8 *)&lbl_1_data_7C0 + (v0 * 44)));
}
/* fzgx:end fn_1_12B4 */

/* fzgx:begin fn_1_12FC */
// fn_1_12FC: empty in retail (single blr).
void fn_1_12FC(void) {
}
/* fzgx:end fn_1_12FC */

/* fzgx:begin fn_1_1300 */
// fn_1_1300: empty in retail (single blr).
void fn_1_1300(void) {
}
/* fzgx:end fn_1_1300 */

/* fzgx:begin fn_1_3238 */
void fn_1_3238(void) {
    u8 *p_lbl_1_bss_978;
    u32 t9;
    p_lbl_1_bss_978 = (u8 *)&lbl_1_bss_978;
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 80), 0, 48);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 32), 0, 48);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 128), 0, 80);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 208), 0, 64);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 272), 0, 24);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 840), 0, 4);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 844), 0, 52);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 896), 0, 48);
    fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 944), 0, 48);
    t9 = fn_80008BEC(((u8 *)p_lbl_1_bss_978 + 24), 0, 8);
    fn_1_15659C(t9);
}
/* fzgx:end fn_1_3238 */

/* fzgx:begin fn_1_3BB0 */
u8 fn_1_3BB0(u32 arg0) {
    return *(u8 *)((u8 *)&lbl_1_data_2B78 + arg0);
}
/* fzgx:end fn_1_3BB0 */

/* fzgx:begin fn_1_3BC0 */
void fn_1_3BC0(void) {
    lbl_1_bss_990[0] = 0;
    lbl_1_bss_990[1] = 0;
    lbl_1_bss_990[2] = 0;
    lbl_1_bss_990[3] = 0;
}
/* fzgx:end fn_1_3BC0 */

/* fzgx:begin fn_1_3BDC */
void fn_1_3BDC(u32 arg0) {
    u32 t0;
    t0 = OSGetTick(arg0);
    *(u32 *)((u8 *)&lbl_1_bss_D7C + (arg0 << 2)) = t0;
}
/* fzgx:end fn_1_3BDC */

/* fzgx:begin fn_1_3C78 */
extern u8 lbl_1_bss_D78;

void fn_1_3C78(void) {
    if (lbl_1_bss_D78 == 0) { return; }
    lbl_1_bss_DA4 = 0;
}
/* fzgx:end fn_1_3C78 */

/* fzgx:begin fn_1_3C98 */
struct fn_1_3C98_lbl_1_bss_DA5 {
    u8 unk_0;
};

extern u8 lbl_1_bss_D78;

void fn_1_3C98(void) {
    if (lbl_1_bss_D78 == 0) { return; }
    if (lbl_1_bss_DA5.unk_0 != 0) { return; }
    lbl_1_bss_DA5.unk_0 = 1;
}
/* fzgx:end fn_1_3C98 */

/* fzgx:begin fn_1_3CC4 */
void fn_1_3CC4(void) {
    if (lbl_1_bss_D78 == 0) {
        return;
    }
    if (lbl_1_bss_DA6 == 0) {
        lbl_1_bss_DA6 = 1;
    }
}
/* fzgx:end fn_1_3CC4 */

/* fzgx:begin fn_1_3F8C */
typedef struct Fn1_3F8C_Entry Fn1_3F8C_Entry;

struct Fn1_3F8C_Entry {
    u32 arg0;
    u32 arg1;
    Fn1_3F8C_Entry *next;
    Fn1_3F8C_Entry *prev;
    s32 result;
    u32 stamp;
    u32 reserved18;
    u32 reserved1c;
    u32 arg3;
};

typedef struct Fn1_3F8C_Table {
    Fn1_3F8C_Entry *head;
    u8 entries[0x14];
} Fn1_3F8C_Table;

// Retrieves an entry from the free list and links it into the indexed list.
s32 fn_1_3F8C(u32 arg3, u32 arg0, u32 arg1, u32 index) {
    Fn1_3F8C_Table *table = (Fn1_3F8C_Table *)lbl_1_bss_DAC;
    Fn1_3F8C_Entry *entry = table->head;
    u8 *slot;
    Fn1_3F8C_Entry *link;

    if (entry == 0) {
        return -1;
    }

    table->head = entry->next;
    slot = (u8 *)table + index * 4;
    link = *(Fn1_3F8C_Entry **)(slot + 0x18);
    entry->next = link->next;
    entry->prev = *(Fn1_3F8C_Entry **)(slot + 0x18);
    entry->arg1 = arg1;
    entry->arg0 = arg0;
    entry->reserved18 = 0;
    entry->reserved1c = 0;
    entry->arg3 = arg3;
    entry->stamp = lbl_1_bss_DB0[0];

    if (entry->next != 0) {
        entry->next->prev = entry;
    }

    link = *(Fn1_3F8C_Entry **)(slot + 0x18);
    link->next = entry;
    return entry->result;
}
/* fzgx:end fn_1_3F8C */

/* fzgx:begin fn_1_4010 */
extern u32 lbl_1_bss_DAC;

// Store a value in the indexed entry of the active table.
u32 fn_1_4010(u32 arg0, u32 arg1) {
    u32 *table = (u32 *)lbl_1_bss_DAC;
    u8 *entry = (u8 *)table[1] + arg0 * 36;

    *(u32 *)(entry + 24) = arg1;
    return (u32)entry;
}
/* fzgx:end fn_1_4010 */

/* fzgx:begin fn_1_4030 noprologue */
#include "types.h"

extern struct fn_1_4030_lbl_1_bss_DA8 lbl_1_bss_DA8;

struct fn_1_4030_lbl_1_bss_DA8 {
    u32 unk_0;
};

u32 fn_1_4030(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 v2;
    v0 = *(u32 *)((u8 *)lbl_1_bss_DA8.unk_0 + 8);
    v1 = *(u32 *)((u8 *)v0 + 0);
    v2 = arg0;
    if (v1 == 0) {
    v2 = 0;
    return v2;
    }
    *(u32 *)((u8 *)v0 + 0) = v2;
    v2 = v1;
    return v2;
}
/* fzgx:end fn_1_4030 */

/* fzgx:begin fn_1_4060 */
extern u32 lbl_1_bss_DA8;

u32 fn_1_4060(void) {
    u32 *base;
    u32 *slot;

    base = (u32 *)lbl_1_bss_DA8;
    slot = *(u32 **)((u8 *)base + 8);
    *slot = 0;
    return (u32)slot;
}
/* fzgx:end fn_1_4060 */

/* fzgx:begin fn_1_407C noprologue */
#include "types.h"

typedef u32 (*fn_1_407C_Fn0)(u32);
struct fn_1_407C_lbl_1_bss_DAC {
    s32 unk_0;
};
struct fn_1_407C_lbl_1_bss_DA8 {
    u32 unk_0;
};
extern struct fn_1_407C_lbl_1_bss_DA8 lbl_1_bss_DA8;
extern struct fn_1_407C_lbl_1_bss_DAC lbl_1_bss_DAC;
extern void fn_1_3BDC(u32);
extern u32 fn_1_3C18(s32);
extern void fn_1_43A4(void);


void fn_1_407C(s32 arg_sp0) {
    u32 var_r31;
    u32 temp_r30;
    s32 temp_r29;
    u8 temp_r28;
    s32 var_r27;
    void *var_r24;
    s32 (*temp_r23)(s32);

    var_r27 = 0;
    temp_r30 = lbl_1_bss_DAC.unk_0;
    var_r31 = temp_r30;
    temp_r29 = *(s32 *)((u8 *)(temp_r30) + 16);
    temp_r28 = (u8) (*(s32 *)((u8 *)(temp_r30) + 20));
    do {
        if (!(temp_r29 & (1 << var_r27))) {
            var_r24 = (void *)(*(void **)((u8 *)((*(void **)((u8 *)(var_r31) + 24))) + 8));
            while (var_r24 != NULL) {
                temp_r23 = (s32 (*)(s32))(*(s32 (**)(s32))((u8 *)(var_r24) + 0));
                (*(void **)((u8 *)(temp_r30) + 8)) = (void *)(var_r24);
                lbl_1_bss_DAC.unk_0 = temp_r30;
                lbl_1_bss_DA8.unk_0 = temp_r30;
                if (((temp_r28 == 0) || ((u8) (temp_r28 & (*(s32 *)((u8 *)(var_r24) + 20))) != 0)) && (temp_r23 != NULL)) {
                    fn_1_3BDC(5U);
                    temp_r23(*(s32 *)((u8 *)(var_r24) + 4));
                    (*(s32 *)((u8 *)(var_r24) + 28)) = (s32) ((*(s32 *)((u8 *)(var_r24) + 28)) + fn_1_3C18(5));
                }
                lbl_1_bss_DAC.unk_0 = temp_r30;
                lbl_1_bss_DA8.unk_0 = temp_r30;
                if ((void *) (*(void **)((u8 *)(temp_r30) + 8)) == var_r24) {
                    var_r24 = (void *)(*(void **)((u8 *)(var_r24) + 8));
                    if (temp_r23 == NULL) {
                        fn_1_43A4();
                    }
                } else {
                    var_r24 = (void *)(NULL);
                }
                            }
        }
        var_r27 += 1;
        var_r31 += 4;
    } while (var_r27 < 0x20);
    (*(void **)((u8 *)(temp_r30) + 8)) = (void *)(NULL);
    lbl_1_bss_DAC.unk_0 = temp_r30;
    lbl_1_bss_DA8.unk_0 = 0;
}
/* fzgx:end fn_1_407C */

/* fzgx:begin fn_1_41A8 */
typedef struct Node Node;
struct Node {
    u32 field_0;
    void *field_4;
    Node *next;
    u32 field_c;
    u32 field_10;
    u32 field_14;
    void (*callback)(void *, u32);
};

typedef struct List List;
struct List {
    u32 field_0;
    u32 field_4;
    Node *head;
};

typedef struct Manager Manager;
struct Manager {
    u32 field_0;
    u32 field_4;
    Node *head;
};

void fn_1_41A8(void) {
    Manager *entry;
    Manager *manager;
    u32 *dac;
    u32 *da8;
    int i;
    Node *node;
    void (*callback)(void *, u32);

    dac = &lbl_1_bss_DAC;
    manager = (Manager *)*dac;
    if (manager != 0) {
        da8 = &lbl_1_bss_DA8;
        entry = manager;
        i = 0;
        while (i < 32) {
            node = (*(List **)((u8 *)entry + 0x18))->head;
            while (node != 0) {
                callback = node->callback;
                manager->head = node;
                *dac = (u32)manager;
                *da8 = (u32)manager;
                if (callback != 0) {
                    callback(node->field_4, 1);
                }
                *dac = (u32)manager;
                *da8 = (u32)manager;
                node = node->next;
                fn_1_43A4();
            }
            i++;
            entry = (Manager *)((u8 *)entry + 4);
        }
        manager->head = 0;
        lbl_1_bss_DAC = (u32)manager;
        lbl_1_bss_DA8 = 0;
    }
}
/* fzgx:end fn_1_41A8 */

/* fzgx:begin fn_1_4310 */
extern u32 lbl_1_bss_DAC;

// Store the value in the shared state object's field.
void fn_1_4310(u32 arg0) {
    *(u32 *)((u8 *)lbl_1_bss_DAC + 16) = arg0;
}
/* fzgx:end fn_1_4310 */

/* fzgx:begin fn_1_4324 */
extern u32 lbl_1_bss_DAC;

// Store the current value in the shared state block.
void fn_1_4324(u32 arg0) {
    *(u32 *)((u8 *)lbl_1_bss_DAC + 20) = arg0;
}
/* fzgx:end fn_1_4324 */

/* fzgx:begin fn_1_4338 */
struct fn_1_4338_target {
    u8 unk_0[20];
    u32 unk_14;
};

struct fn_1_4338_root {
    struct fn_1_4338_target *unk_0;
};

extern u32 lbl_1_bss_DAC;

// Return the value stored in the pointed-to object's field at offset 0x14.
u32 fn_1_4338(void) {
    return ((struct fn_1_4338_root *)&lbl_1_bss_DAC)->unk_0->unk_14;
}
/* fzgx:end fn_1_4338 */

/* fzgx:begin fn_1_434C */
extern u32 lbl_1_bss_DAC;

// fn_1_434C returns the current main-rel state value.
u32 fn_1_434C(void) {
    return lbl_1_bss_DAC;
}
/* fzgx:end fn_1_434C */

/* fzgx:begin fn_1_435C */
extern u32 lbl_1_bss_DAC;

u32 fn_1_435C(u32 value) {
    u32 old;

    old = lbl_1_bss_DAC;
    lbl_1_bss_DAC = value;
    return old;
}
/* fzgx:end fn_1_435C */

/* fzgx:begin fn_1_4370 */
// fn_1_4370: empty in retail (single blr).
void fn_1_4370(void) {
}
/* fzgx:end fn_1_4370 */

/* fzgx:begin fn_1_4374 */
typedef struct Node Node;
struct Node {
    u32 field_0;
    u32 field_4;
    Node *next;
    Node *prev;
};

void fn_1_4374(Node **list, Node *node) {
    Node *prev;
    Node *next;

    next = node->next;
    prev = node->prev;
    prev->next = next;
    if (next != 0) {
        next->prev = prev;
    }
    node->next = *list;
    node->field_0 = 0;
    *list = node;
}
/* fzgx:end fn_1_4374 */

/* fzgx:begin fn_1_43E8 */
extern u32 lbl_1_bss_DB0[2];

// Store the incoming value in the shared startup state.
void fn_1_43E8(u32 arg0) {
    lbl_1_bss_DB0[0] = arg0;
}
/* fzgx:end fn_1_43E8 */

/* fzgx:begin fn_1_43F4 */
extern u32 lbl_1_bss_DB0[2];

// Clear the first startup word used by the main REL state.
void fn_1_43F4(void) {
    lbl_1_bss_DB0[0] = 0;
}
/* fzgx:end fn_1_43F4 */

/* fzgx:begin fn_1_4404 noprologue */
#include "types.h"

extern struct fn_1_4404_lbl_1_bss_DC0 lbl_1_bss_DC0;
extern u32 fn_80008E84(u32);
extern u32 lbl_1_data_2C70;

struct fn_1_4404_lbl_1_bss_DC0 {
    u32 unk_0;
};

void fn_1_4404(void) {
    u32 t0;
    t0 = fn_80008E84(lbl_1_bss_DC0.unk_0);
    lbl_1_data_2C70 = t0;
}
/* fzgx:end fn_1_4404 */

/* fzgx:begin fn_1_4438 noprologue */
#include "types.h"

extern struct fn_1_4438_lbl_1_bss_DC4 lbl_1_bss_DC4;
extern u32 fn_80008E84(u32);
extern u32 lbl_1_data_2C70;

struct fn_1_4438_lbl_1_bss_DC4 {
    u32 unk_0;
};

void fn_1_4438(void) {
    u32 t0;
    t0 = fn_80008E84(lbl_1_bss_DC4.unk_0);
    lbl_1_data_2C70 = t0;
}
/* fzgx:end fn_1_4438 */

/* fzgx:begin fn_1_446C */
void fn_1_446C(void) {
    fn_80008E84(lbl_1_data_2C70);
    lbl_1_data_2C70 = (u32)-1;
}
/* fzgx:end fn_1_446C */

/* fzgx:begin fn_1_44A4 */
extern struct fn_1_44A4_lbl_1_bss_DC4 lbl_1_bss_DC4;

struct fn_1_44A4_lbl_1_bss_DC4 {
    u32 unk_0;
};

u32 fn_1_44A4(void) {
    return lbl_1_bss_DC4.unk_0;
}
/* fzgx:end fn_1_44A4 */

/* fzgx:begin fn_1_44B4 */
extern struct fn_1_44B4_lbl_1_bss_DB8 lbl_1_bss_DB8;
extern u32 OSGetArenaHi(void);
extern u32 OSGetArenaLo(void);
extern u32 fn_80008F60(u32, u32);

struct fn_1_44B4_lbl_1_bss_DB8 {
    u8 pad_0[0x8];
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
};

void fn_1_44B4(void) {
    struct fn_1_44B4_lbl_1_bss_DB8 *p_lbl_1_bss_DB8;
    u32 t0, t1, t2, t3;
    p_lbl_1_bss_DB8 = (struct fn_1_44B4_lbl_1_bss_DB8 *)&lbl_1_bss_DB8;
    t0 = OSGetArenaHi();
    t1 = OSGetArenaLo();
    t2 = fn_80008EC8(t1, t0, 8);
    p_lbl_1_bss_DB8->unk_10 = t2;
    t3 = fn_80008F60(t2, ((t2 + 0xE0000) - 2848));
    p_lbl_1_bss_DB8->unk_C = t3;
    p_lbl_1_bss_DB8->unk_8 = -1;
}
/* fzgx:end fn_1_44B4 */

/* fzgx:begin fn_1_451C noprologue */
#include "types.h"

struct fn_1_451C_lbl_1_bss_DB8 {
    u8 pad_0[0x8];
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
};

extern struct fn_1_451C_lbl_1_bss_DB8 lbl_1_bss_DB8;
extern u32 OSGetArenaHi(void);
extern u32 OSGetArenaLo(void);
extern u32 fn_1_481E8(u32);
extern u32 fn_1_566DC(void);
extern u32 fn_80008E84(void);
extern u32 fn_80008F60(u32, u32);
extern u32 fn_80009064(u32);
extern u32 fn_80009FA4(u32);
extern u32 fn_80077848(void);
extern u32 fn_8007785C(u32, u32);

u32 fn_1_451C(void) {
    u32 t9;
    u32 t8;
    u32 t7;
    u32 t6;
    u32 t5;
    u32 t4;
    u32 t3;
    u32 t0;
    u32 v2;
    u32 v1;
    u32 v0;
    struct fn_1_451C_lbl_1_bss_DB8 *p_lbl_1_bss_DB8;
    p_lbl_1_bss_DB8 = (struct fn_1_451C_lbl_1_bss_DB8 *)&lbl_1_bss_DB8;
    t0 = OSGetArenaHi();
    OSGetArenaLo();
    fn_1_481E8(188);
    v0 = (p_lbl_1_bss_DB8->unk_C + 1);
    v1 = v0;
    while ((s32)v1 < 8) {
    t3 = fn_80009FA4(v1);
    v2 = t3;
    if ((t3 + 0x10000) != 65535) {
    v2 = v1;
    t4 = fn_80009064(v2);
    v2 = t4;
    }
    v1++;
    }
    v2 = p_lbl_1_bss_DB8->unk_10;
    v2 = (v2 + 0xE0000);
    v2 -= 2848;
    t5 = fn_80008F60(v2, t0);
    v2 = t5;
    p_lbl_1_bss_DB8->unk_8 = v2;
    t6 = fn_80008E84();
    v2 = t6;
    t7 = fn_80077848();
    v2 = t7;
    t8 = fn_1_566DC();
    v2 = t8;
    t9 = fn_8007785C(v2, 0);
    v2 = t9;
    v2 = p_lbl_1_bss_DB8->unk_8;
    return v2;
}
/* fzgx:end fn_1_451C */

/* fzgx:begin fn_1_45D0 */
extern u32 OSReport(u32, ...);
extern u32 fn_800090A4(u32);
extern u32 fn_80009830(u32);
extern u32 lbl_1_data_2C74;

s32 fn_1_45D0(u32 arg0, u32 arg1) {
    u32 v0;
    u32 t0, t1, t2;
    v0 = arg0;
    if ((s32)arg1 == 0) {
    v0 = (u32)&lbl_1_data_2C74;
    t0 = OSReport((u32)v0, arg1);
    v0 = t0;
    v0 = 0;
    } else {
    t1 = fn_80009830(v0);
    v0 = t1;
    if (v0 == 0) {
    v0 = arg0;
    t2 = fn_800090A4(v0);
    v0 = t2;
    v0 = 0;
    }
    }
    return v0;
}
/* fzgx:end fn_1_45D0 */

/* fzgx:begin fn_1_4630 */
extern u32 OSReport(u32, ...);
extern u32 fn_800090A4(u32);
extern u32 fn_80009830(void);
extern u32 lbl_1_data_2C74;

u32 fn_1_4630(u32 arg0, u32 arg1) {
    u32 v0;
    u32 v1;
    u32 t0, t1, t2, t3;
    v0 = arg0;
    v1 = arg0;
    if (arg1 == 0) {
    v0 = (u32)&lbl_1_data_2C74;
    t0 = OSReport((u32)v0, arg1);
    v0 = t0;
    v1 = 0;
    } else {
    t1 = fn_80009830();
    v0 = t1;
    if (v0 == 0) {
    v0 = v1;
    t2 = fn_800090A4(v0);
    v0 = t2;
    v1 = 0;
    } else {
    v1 = v0;
    }
    }
    v0 = v1;
    t3 = fn_800793D4(v0, 0, arg1);
    v0 = t3;
    v0 = v1;
    return v0;
}
/* fzgx:end fn_1_4630 */

/* fzgx:begin fn_1_46B4 */
extern char lbl_1_data_2C9C[20];
extern void OSPanic(const char *message, int line, const char *file, ...);
extern void fn_80009AA8(u32 value, u32 count, const char *file, int line);

void fn_1_46B4(u32 arg0, u32 arg1, const char *arg2, int arg3) {
    if (arg1 == 0) {
        OSPanic(arg2, arg3, lbl_1_data_2C9C);
    }
    fn_80009AA8(arg0, arg1, arg2, arg3);
}
/* fzgx:end fn_1_46B4 */

/* fzgx:begin fn_1_4730 */
typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} Fn1_4730Entry;

extern Fn1_4730Entry lbl_1_bss_DCC[32];

void fn_1_4730(u32 value, u32 count, u32 size, const char *file, int line) {
    s32 remaining;
    Fn1_4730Entry *entry;

    if (count == 0) {
        OSPanic(file, line, lbl_1_data_2C9C);
    }
    if (size == 0) {
        if (count == 0) {
            OSPanic(file, line, lbl_1_data_2C9C);
        }
        fn_80009AA8(value, count, file, line);
    }

    entry = lbl_1_bss_DCC;
    remaining = 0x20;
    while (remaining > 0) {
        if (entry->unk_08 == 0) {
            break;
        }
        remaining--;
        entry++;
    }
    if (remaining == 0) {
        OSPanic(file, line, lbl_1_data_2CB0);
    }
    entry->unk_00 = value;
    entry->unk_04 = size;
    entry->unk_08 = count;
}
/* fzgx:end fn_1_4730 */

/* fzgx:begin fn_1_48B0 */
struct fn_1_48B0_lbl_801A6CF8 {
    u32 unk_0;
};

s32 fn_1_48B0(u32 arg0, u32 arg1) {
    s32 v0;
    v0 = (arg1 * ((u32)(lbl_801A6CF8.unk_0 - arg0) / (u32)arg1));
    if ((u32)(arg1 * ((u32)(lbl_801A6CF8.unk_0 - arg0) / (u32)arg1)) < lbl_801A6CFC) {
    v0 = 0;
    return v0;
    }
    lbl_801A6CF8.unk_0 = v0;
    return v0;
}
/* fzgx:end fn_1_48B0 */
