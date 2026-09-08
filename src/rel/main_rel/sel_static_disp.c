#include "types.h"
#include "rel/main_rel/globals.h"

/* fzgx:begin fn_1_133DBC */
extern void fn_1_133E04(void* arg0, s32 arg1);

void fn_1_133DBC(void* arg0) {
    fn_1_133E04(arg0, 0);
}
/* fzgx:end fn_1_133DBC */

/* fzgx:begin fn_1_137548 */
extern void fn_1_1375C0(int arg0, void* arg1, void* arg2, void* arg3, void* arg4);

void fn_1_137548(void* arg0, void* arg1, void* arg2, void* arg3) {
    fn_1_1375C0(1, arg0, arg1, arg2, arg3);
}
/* fzgx:end fn_1_137548 */

/* fzgx:begin fn_1_137584 */
extern void fn_1_1375C0(int arg0, void* arg1, void* arg2, void* arg3, void* arg4);

void fn_1_137584(void* arg0, void* arg1, void* arg2, void* arg3) {
    fn_1_1375C0(2, arg0, arg1, arg2, arg3);
}
/* fzgx:end fn_1_137584 */

/* fzgx:begin fn_1_13E054 */
extern void fn_1_13E080(void* arg0, void* arg1, void* arg2, int arg3);

void fn_1_13E054(void* arg0, void* arg1, void* arg2, int arg3) {
    u8* fixed = (u8*)0;
    fixed += 0xA204;
    fn_1_13E080(arg0, arg1, fixed, 31);
}
/* fzgx:end fn_1_13E054 */

/* fzgx:begin fn_1_13F81C */
extern u32 lbl_1_bss_8E3E4[8];

void fn_1_13F81C(void) {
    lbl_1_bss_8E3E4[0] = 0;
    lbl_1_bss_8E3E4[1] = 0;
    lbl_1_bss_8E3E4[2] = 0;
    lbl_1_bss_8E3E4[3] = 0;
    lbl_1_bss_8E3E4[4] = 0;
    lbl_1_bss_8E3E4[5] = 0;
    lbl_1_bss_8E3E4[6] = 0;
    lbl_1_bss_8E3E4[7] = 0;
}
/* fzgx:end fn_1_13F81C */

/* fzgx:begin fn_1_13F848 */
extern u32 lbl_801A6410;
extern char lbl_1_data_419E0[18];
extern u32 fn_1_45D0(u32 arg0, int arg1, void* arg2, int arg3);
extern u32 lbl_1_bss_8E3E4[8];
extern void fn_1_FC414(u32 arg0, int arg1);

void fn_1_13F848(u32 arg0) {
    u32 index = arg0 & 0xFF;

    lbl_1_bss_8E3E4[index] =
        fn_1_45D0(lbl_801A6410, 0x10440, lbl_1_data_419E0, 0x14F9);
    fn_1_FC414(lbl_1_bss_8E3E4[index], 1);
}
/* fzgx:end fn_1_13F848 */

/* fzgx:begin fn_1_13F974 */
extern u32 lbl_801A6410;
extern char lbl_1_data_419E0[18];
extern u32 fn_1_45D0(u32 arg0, int arg1, void* arg2, int arg3);
extern u32 lbl_1_bss_8E404[8];
extern u32 fn_80008BEC(u32 arg0, int arg1, int arg2);

u32 fn_1_13F974(u32 arg0) {
    u32* config = &lbl_801A6410;

    lbl_1_bss_8E404[arg0 & 0xFF] =
        fn_1_45D0(config[0], 0x440, lbl_1_data_419E0, 0x1528);
    return fn_80008BEC(lbl_1_bss_8E404[arg0 & 0xFF], 0, 0x440);
}
/* fzgx:end fn_1_13F974 */

/* fzgx:begin fn_1_13F9DC */
extern u32 lbl_1_bss_8E404[8];

u32 fn_1_13F9DC(u32 arg0) {
    return lbl_1_bss_8E404[arg0 & 0xFF];
}
/* fzgx:end fn_1_13F9DC */

/* fzgx:begin fn_1_149BF4 */
extern u32 lbl_1_bss_8E428;
extern void fn_1_149CA4(u32 arg0, u32 arg1, u32 arg2, u32 arg3);

// Load four values from BSS table and pass to fn_1_149CA4.
void fn_1_149BF4(void) {
    u8* base = (u8*)&lbl_1_bss_8E428;
    u32 arg0 = *(u32*)(base + 0x4);
    u32 arg1 = *(u32*)(base + 0x14);
    u32 arg2 = *(u32*)(base + 0x8);
    u32 arg3 = *(u32*)(base + 0x18);
    fn_1_149CA4(arg0, arg1, arg2, arg3);
}
/* fzgx:end fn_1_149BF4 */

/* fzgx:begin fn_1_14A000 */
// fn_1_14A000: empty in retail (single blr).
void fn_1_14A000(void) {
}
/* fzgx:end fn_1_14A000 */

/* fzgx:begin fn_1_14A004 */
// fn_1_14A004: empty in retail (single blr).
void fn_1_14A004(void) {
}
/* fzgx:end fn_1_14A004 */

/* fzgx:begin fn_1_14A008 */
// fn_1_14A008: empty in retail (single blr).
void fn_1_14A008(void) {
}
/* fzgx:end fn_1_14A008 */

/* fzgx:begin fn_1_14A278 */
// fn_1_14A278: empty in retail (single blr).
void fn_1_14A278(void) {
}
/* fzgx:end fn_1_14A278 */

/* fzgx:begin fn_1_14A27C */
// fn_1_14A27C: empty in retail (single blr).
void fn_1_14A27C(void) {
}
/* fzgx:end fn_1_14A27C */

/* fzgx:begin fn_1_14A280 */
// fn_1_14A280: empty in retail (single blr).
void fn_1_14A280(void) {
}
/* fzgx:end fn_1_14A280 */

/* fzgx:begin fn_1_14A9CC */
// fn_1_14A9CC: empty in retail (single blr).
void fn_1_14A9CC(void) {
}
/* fzgx:end fn_1_14A9CC */

/* fzgx:begin fn_1_14B1B8 */
// fn_1_14B1B8: empty in retail (single blr).
void fn_1_14B1B8(void) {
}
/* fzgx:end fn_1_14B1B8 */

/* fzgx:begin fn_1_14B4FC */
// fn_1_14B4FC: empty in retail (single blr).
void fn_1_14B4FC(void) {
}
/* fzgx:end fn_1_14B4FC */

/* fzgx:begin fn_1_14B8F8 */
// fn_1_14B8F8: empty in retail (single blr).
void fn_1_14B8F8(void) {
}
/* fzgx:end fn_1_14B8F8 */

/* fzgx:begin fn_1_14BC3C */
// fn_1_14BC3C: empty in retail (single blr).
void fn_1_14BC3C(void) {
}
/* fzgx:end fn_1_14BC3C */

/* fzgx:begin fn_1_14BD44 */
extern void fn_1_14BFD8(void *, void *, int);

void fn_1_14BD44(void *arg0, void *arg1) {
    fn_1_14BFD8(arg1, arg0, 0);
}
/* fzgx:end fn_1_14BD44 */

/* fzgx:begin fn_1_14BD74 */
extern void fn_1_14BFB8(void);

void fn_1_14BD74(void) {
    fn_1_14BFB8();
}
/* fzgx:end fn_1_14BD74 */

/* fzgx:begin fn_1_14C7F4 */
// fn_1_14C7F4: empty in retail (single blr).
void fn_1_14C7F4(void) {
}
/* fzgx:end fn_1_14C7F4 */

/* fzgx:begin fn_1_14C964 */
// fn_1_14C964: empty in retail (single blr).
void fn_1_14C964(void) {
}
/* fzgx:end fn_1_14C964 */

/* fzgx:begin fn_1_14CA3C */
// fn_1_14CA3C: empty in retail (single blr).
void fn_1_14CA3C(void) {
}
/* fzgx:end fn_1_14CA3C */

/* fzgx:begin fn_1_14CA40 */
// fn_1_14CA40: empty in retail (single blr).
void fn_1_14CA40(void) {
}
/* fzgx:end fn_1_14CA40 */

/* fzgx:begin fn_1_14CA44 */
// fn_1_14CA44: empty in retail (single blr).
void fn_1_14CA44(void) {
}
/* fzgx:end fn_1_14CA44 */

/* fzgx:begin fn_1_14CA48 */
// fn_1_14CA48: empty in retail (single blr).
void fn_1_14CA48(void) {
}
/* fzgx:end fn_1_14CA48 */

/* fzgx:begin fn_1_14CA4C noprologue */
#include "types.h"
extern u8 lbl_1_bss_8E518[5];
extern u8 lbl_1_bss_3C30[5308];
extern void fn_1_A2D84(u32, u8 *);

void fn_1_14CA4C(void) {
    u8 *state = lbl_1_bss_8E518;
    if (state[4] == 0) {
        u8 limit;

        state[4] = 1;
        if (state[5] == 4) {
            limit = lbl_1_bss_3C30[8];
        } else {
            limit = lbl_1_bss_3C30[9];
        }
        if (limit > state[0x30]) {
            fn_1_A2D84(0xA9010400, state);
        }
    }
}
/* fzgx:end fn_1_14CA4C */

/* fzgx:begin fn_1_14D6D8 */
extern u32 lbl_1_rodata_99D8[75];

typedef struct {
    u32 values[75];
} Table75;

u32 fn_1_14D6D8(s16 index) {
    Table75 values = *(Table75 *)lbl_1_rodata_99D8;

    return values.values[index];
}
/* fzgx:end fn_1_14D6D8 */

/* fzgx:begin fn_1_14E054 */
extern void fn_1_14E09C(void *arg0, void *arg1, void *arg2, int arg3);

void fn_1_14E054(void *arg0, void *arg1, void *arg2) {
    fn_1_14E09C(arg0, arg1, arg2, 0);
}
/* fzgx:end fn_1_14E054 */

/* fzgx:begin fn_1_14E198 */
extern void fn_1_14E1E0(void *arg0, void *arg1, void *arg2, int arg3);

void fn_1_14E198(void *arg0, void *arg1, void *arg2) {
    fn_1_14E1E0(arg0, arg1, arg2, 0);
}
/* fzgx:end fn_1_14E198 */

/* fzgx:begin fn_1_14E8A4 */
typedef struct {
    s16 value;
    s16 sort_key;
} Fn1_14E8A4Entry;

int fn_1_14E8A4(const Fn1_14E8A4Entry *arg0, const Fn1_14E8A4Entry *arg1) {
    if (arg0->sort_key == arg1->sort_key) {
        return arg0->value - arg1->value;
    }
    return arg0->sort_key - arg1->sort_key;
}
/* fzgx:end fn_1_14E8A4 */

/* fzgx:begin fn_1_14F014 */
// fn_1_14F014: returns a constant.
int fn_1_14F014(void) {
    return 75;
}
/* fzgx:end fn_1_14F014 */

/* fzgx:begin fn_1_14F118 */
extern s16 fn_1_14F01C(s16 category);
extern s16 fn_1_14F090(s16 category, s16 occurrence);

s16 fn_1_14F118(s16 record_id, s16 category) {
    s16 occurrence;

    for (occurrence = 0; occurrence < fn_1_14F01C(category); occurrence++) {
        if (record_id == fn_1_14F090(category, occurrence)) {
            return occurrence;
        }
    }
    return -1;
}
/* fzgx:end fn_1_14F118 */

/* fzgx:begin fn_1_14F344 */
extern u8 lbl_1_rodata_C6E8[1200];

typedef struct {
    u8 unk0[2];
    s16 value;
    u8 unk4[12];
} Entry;

typedef struct {
    Entry entries[75];
} Table;

s16 fn_1_14F344(s16 index) {
    Table table;

    table = *(Table *)lbl_1_rodata_C6E8;
    return table.entries[index].value;
}
/* fzgx:end fn_1_14F344 */

/* fzgx:begin fn_1_14FCE4 */
extern u8 lbl_1_rodata_CCDC[308];
extern void fn_1_14FD7C(u32 *data, u32 count);
extern void fn_80008BA8(u32 arg0, u32 *data, s32 offset);

typedef struct {
    u32 words[77];
} Data;

void fn_1_14FCE4(u32 arg0, s16 arg1) {
    Data data;

    data = *(Data *)lbl_1_rodata_CCDC;
    fn_1_14FD7C(data.words, 77);
    fn_80008BA8(arg0, data.words, (s32)arg1 << 2);
}
/* fzgx:end fn_1_14FCE4 */

/* fzgx:begin fn_1_14FD6C */
s32 fn_1_14FD6C(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}
/* fzgx:end fn_1_14FD6C */

/* fzgx:begin fn_1_150518 */
extern void fn_1_9A508(Obj_1_data_2A7E0 *state);
extern void fn_1_150C8C(Obj_1_data_2A7E0_At3C *obj);
extern void fn_1_150F30(Obj_1_data_2A7E0_At3C *obj);

// Reset the active object's counters and re-run its two setup passes.
void fn_1_150518(void) {
    Obj_1_data_2A7E0_At3C *obj = lbl_1_data_2A7E0.unk_3C;

    obj->unk_84 = 0;
    obj->unk_2724 = 0;
    fn_1_9A508(&lbl_1_data_2A7E0);
    fn_1_150C8C(obj);
    fn_1_150F30(obj);
    obj->unk_0 = 1;
}
/* fzgx:end fn_1_150518 */

/* fzgx:begin fn_1_150570 */
// fn_1_150570: empty in retail (single blr).
void fn_1_150570(void) {
}
/* fzgx:end fn_1_150570 */

/* fzgx:begin fn_1_150574 noprologue */
#include "types.h"
extern u32 lbl_1_data_2A7E0[62];
extern void fn_1_150CEC(u32 arg);
extern void fn_1_151668(u32 arg);

void fn_1_150574(void) {
    u32 value = *(u32*)((u8*)lbl_1_data_2A7E0 + 0x3c);
    fn_1_150CEC(value);
    fn_1_151668(value);
}
/* fzgx:end fn_1_150574 */

/* fzgx:begin fn_1_1505B4 noprologue */
#include "types.h"
extern u32 lbl_1_data_2A7E0[62];
extern u32 fn_1_9AD54(void);
extern u32 fn_1_9D260(void);
extern void fn_1_150D3C(u32 arg0, u32 arg1);
extern void fn_1_150654(void);
extern void fn_1_151054(u32 arg);

void fn_1_1505B4(void) {
    u32 value;
    u32 result;

    value = *(u32*)((u8*)lbl_1_data_2A7E0 + 0x3c);
    fn_1_9AD54();
    result = fn_1_9D260();
    fn_1_150D3C(value, result);
    fn_1_150654();
    fn_1_151054(value);
}
/* fzgx:end fn_1_1505B4 */

/* fzgx:begin fn_1_150608 noprologue */
#include "types.h"
extern u32 lbl_1_data_2A7E0[62];
extern void fn_1_9AD88(void);
extern u32 fn_1_9D260(void);
extern void fn_1_150ED0(u32 arg0, u32 arg1);

// fn_1_150608: Load data value, call two setup functions, then call main function with value and result
void fn_1_150608(void) {
    u32 value;
    u32 result;
    
    value = *(u32*)((u8*)lbl_1_data_2A7E0 + 0x3c);
    fn_1_9AD88();
    result = fn_1_9D260();
    fn_1_150ED0(value, result);
}
/* fzgx:end fn_1_150608 */

/* fzgx:begin fn_1_150650 */
// fn_1_150650: empty in retail (single blr).
void fn_1_150650(void) {
}
/* fzgx:end fn_1_150650 */

/* fzgx:begin fn_1_150C8C */
extern void fn_1_103090(void *entry);

typedef struct Entry {
    u8 pad[0x68];
    u32 active;
    u8 tail[0x40];
} Entry;

typedef struct Object {
    u8 pad_84[0x84];
    s32 count;
    Entry entries[1];
} Object;

void fn_1_150C8C(Object *obj) {
    s32 count;
    Entry *entry;

    count = obj->count;
    entry = obj->entries;
    while (count > 0) {
        entry->active = 1;
        fn_1_103090(entry);
        count -= 1;
        entry += 1;
    }
}
/* fzgx:end fn_1_150C8C */

/* fzgx:begin fn_1_150ED0 */
extern void fn_1_103264(void *entry, void *arg);

typedef struct Entry {
    u8 data[0xac];
} Entry;

typedef struct Object {
    u8 pad_84[0x84];
    s32 count;
    Entry entries[1];
} Object;

void fn_1_150ED0(Object *obj, void *arg) {
    s32 count;
    Entry *entry;

    count = obj->count;
    entry = obj->entries;
    while (count > 0) {
        fn_1_103264(entry, arg);
        count -= 1;
        entry += 1;
    }
}
/* fzgx:end fn_1_150ED0 */

/* fzgx:begin fn_1_151764 */
// fn_1_151764: returns a constant.
int fn_1_151764(void) {
    return 1;
}
/* fzgx:end fn_1_151764 */
