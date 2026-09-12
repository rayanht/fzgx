#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/load.h"

extern u32 lbl_1_bss_3DCE4[17];
extern void *fn_80006DFC(void *arg);
extern void fn_1_D3214(void);
extern s32 fn_8000700C(s32 arg0);
extern void fn_1_3BDC(s32 arg0);
extern void fn_8000659C(void);
extern u32 lbl_1_bss_384C4;
extern void fn_1_46A8C(u32 value);
extern u32 lbl_1_bss_3DCD8;
extern u32 lbl_1_bss_3DD28[179];
extern void fn_1_47EE4(s32);
extern void fn_1_485C8(s32);
extern void fn_1_48140(s32 value);
extern void fn_1_4DDC0(void);
extern void fn_1_4F724(void);

extern u8 lbl_1_bss_3E024[52];
extern char lbl_1_data_1A3AC[5];
extern void fn_80083DB0(void *arg0, void *arg1);
extern u32 fn_80006CE4(u32);
extern void *fn_80006DE8(void *);
extern u32 lbl_801A6410;
extern void *fn_1_4630(u32 arg0, u32 arg1, u8 *arg2, u32 arg3);
extern void *fn_1_46B4(u32 arg0, void *arg1, u8 *arg2, u32 arg3);
extern void strcat(void *arg0, void *arg1);
extern void fn_1_48004(s32 value, s32 arg);

/* fzgx:begin fn_1_45730 noprologue */
#include "types.h"
#include "rel/main_rel/load.h"

extern int fn_1_45E98(void *arg0, void **result);
extern int fn_8000700C(void *arg0);
extern int fn_80006C2C(int status, void *arg0);

typedef struct {
    u32 flags;
    s32 unk_4;
    u32 unk_8;
    u32 unk_C;
} LoadEntry;

typedef struct {
    u32 unk_0;
    u8 pad_4[0x48];
    LoadEntry entry;
} LoadResult;

int fn_1_45730(void *arg0, LoadResult *result) {
    LoadEntry *entry;
    int status;
    int i;

    status = fn_1_45E98(arg0, (void **)&entry);
    if (status >= 0) {
        result->unk_0 = 1;
        result->entry = *entry;
        return 1;
    }

    if (status < 0) {
        status = fn_8000700C(arg0);
    }
    if (status < 0) {
        return 0;
    }

    entry = (LoadEntry *)&lbl_1_bss_384D8;
    for (i = 0; i < 0x400; i++) {
        if ((entry->flags & 0x40000000) != 0 &&
            (entry->flags & 0x08000000) == 0 &&
            entry->unk_4 == status) {
            result->unk_0 = 1;
            result->entry = *entry;
            return 1;
        }
        entry++;
    }

    result->unk_0 = 0;
    return fn_80006C2C(status, (u8 *)result + 4);
}
/* fzgx:end fn_1_45730 */

/* fzgx:begin fn_1_45850 */
struct fn_1_45850_Arg0 {
    u32 unk_0;
};

u32 fn_1_45850(struct fn_1_45850_Arg0 *arg0) {
    u32 v0;
    u32 t0;

    v0 = (u32)arg0;
    switch ((s32)arg0->unk_0) {
    case 1:
        v0 = 1;
        break;
    case 0:
    default:
        v0 += 4;
        t0 = fn_80006CE4(v0);
        v0 = t0;
        break;
    }
    return v0;
}
/* fzgx:end fn_1_45850 */

/* fzgx:begin fn_1_45890 */
// Clear the load-state flag before starting a new load.
void fn_1_45890(void) {
    lbl_1_bss_384D0 = 0;
}
/* fzgx:end fn_1_45890 */

/* fzgx:begin fn_1_45AD4 */
// Reports whether loading is already active or any load slot is occupied.
int fn_1_45AD4(void) {
    s8 i;

    if ((s32)lbl_1_bss_384D0 != 0) {
        return 1;
    }

    for (i = 0; i < 16; i++) {
        if ((s32)lbl_1_bss_3DCE4[i] != 0) {
            return 1;
        }
    }

    return 0;
}
/* fzgx:end fn_1_45AD4 */

/* fzgx:begin fn_1_45B2C */
typedef struct Fn145B2CData {
    s32 kind;
    u8 pad[0x54];
    void *value;
} Fn145B2CData;

void *fn_1_45B2C(Fn145B2CData *data) {
    void *result;
    switch (data->kind) {
    case 1:
        result = data->value;
        break;
    default:
        result = fn_80006DE8(&data->kind + 1);
        break;
    }
    return result;
}
/* fzgx:end fn_1_45B2C */

/* fzgx:begin fn_1_45B68 */
typedef struct Fn45B68Object {
    s32 state;
    u8 _pad[0x50];
    void *value;
} Fn45B68Object;

void *fn_1_45B68(Fn45B68Object *obj) {
    switch (obj->state) {
    case 1:
        return obj->value;
    default:
        return fn_80006DFC((u8 *)obj + 4);
    }
}
/* fzgx:end fn_1_45B68 */

/* fzgx:begin fn_1_45BA4 */
void fn_1_45BA4(s32 value) {
    fn_1_D3214();
    lbl_1_bss_384C8 = value & (value >> 31);
}
/* fzgx:end fn_1_45BA4 */

/* fzgx:begin fn_1_45BE0 */
void fn_1_45BE0(void) {
    lbl_1_bss_384C8 = 0;
}
/* fzgx:end fn_1_45BE0 */

/* fzgx:begin fn_1_45CD8 */
int fn_1_45CD8(int index) {
    s32 j;

    for (j = 0; j < 0x400; j++) {
        index++;
        if ((&lbl_1_bss_384D8.unk_0)[index * 4] == 0) {
            return index;
        }
        if (index >= 0x400) {
            index = 0;
        }
    }

    return index;
}
/* fzgx:end fn_1_45CD8 */

/* fzgx:begin fn_1_45D78 */
typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
} fn_1_45D78_LoadEntry;

int fn_1_45D78(u32 start, u32 size, u32 *out_end, s32 mode) {
    u32 limit;
    fn_1_45D78_LoadEntry *entry;
    u32 i;
    u32 total;
    u32 end;

    limit = start + size;
    entry = (fn_1_45D78_LoadEntry *)&lbl_1_bss_384D8;
    total = -1;
    for (i = 0; i < 0x400; i++, entry++) {
        if (entry->unk_0 != 0) {
            if (entry->unk_8 < limit) {
                end = entry->unk_8 + entry->unk_C;
                if (end > start) {
                    if (mode == 0 && (entry->unk_0 & 0x10000000) != 0) {
                        if (out_end != 0) {
                            *out_end = end;
                        }
                        return 0;
                    }
                    entry->unk_0 = 0;
                    if (total == (u32)-1) {
                        total = 0;
                    }
                    total += entry->unk_C;
                }
            }
        }
    }
    return total;
}
/* fzgx:end fn_1_45D78 */

/* fzgx:begin fn_1_45E84 */
s32 fn_1_45E84(s32 value) {
    value += 1;
    if (value >= 0x200) {
        value = 0;
    }
    return value;
}
/* fzgx:end fn_1_45E84 */

/* fzgx:begin fn_1_464BC */
typedef struct Fn464BCEntry {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} Fn464BCEntry;

typedef struct Fn464BCObject {
    u8 unk_00[4];
    Fn464BCEntry *unk_04;
    u8 unk_08[8];
    u8 *unk_10;
} Fn464BCObject;

extern u16 lbl_1_data_67CC;
extern void fn_80083DB0(void *arg0, void *arg1);

void fn_1_464BC(Fn464BCObject *object, u32 index, void *arg2, void *arg3) {
    void *result;
    Fn464BCEntry *base;
    Fn464BCEntry *entry;
    u32 value;
    s32 flag;

    base = object->unk_04;
    entry = &base[index];
    result = fn_1_4630(lbl_801A6410, (u32)arg3, (*(u8 (*)[76])&lbl_1_data_6730), 0x3f4);
    value = entry->unk_00;
    fn_80083DB0(arg2, object->unk_10 + (value & 0x00ffffff));

    while (entry > base) {
        value = entry->unk_00;
        flag = (value & 0xff000000) != 0;
        if (flag != 0) {
            fn_80083DB0(result, object->unk_10 + (value & 0x00ffffff));
            strcat(result, &lbl_1_data_67CC);
            strcat(result, arg2);
            fn_80083DB0(arg2, result);
            entry = &base[entry->unk_04];
        } else {
            entry--;
        }
    }

    fn_1_46B4(lbl_801A6410, result, (*(u8 (*)[76])&lbl_1_data_6730), 0x402);
}
/* fzgx:end fn_1_464BC */

/* fzgx:begin fn_1_465D0 */
// Queues a completed load operation in the circular load queue.
s32 fn_1_465D0(s32 arg0, s32 arg1) {
    s32 *base = (s32 *)&lbl_1_bss_384C0;
    s32 result;
    s32 index;
    s32 *entry;
    s32 next;

    if (base[0x161A] != 0) {
        switch (arg1) {
        case 3:
        case 1:
        case 5:
            arg1++;
            break;
        }
    }

    result = fn_8000700C(arg0);
    if (result < 0) {
        return -1;
    }

    if (base[0] == base[1]) {
        fn_1_3BDC(2);
    }

    index = base[0];
    next = index + 1;
    if (next >= 0x200) {
        next = 0;
    }

    if (base[1] == next) {
        return -1;
    }

    entry = base + 0x1006;
    entry += index * 3;
    base[0] = next;
    entry[0] = arg1;
    entry[1] = result;
    return index;
}
/* fzgx:end fn_1_465D0 */

/* fzgx:begin fn_1_467F4 */
u32 fn_1_467F4(void) {
    u32 value;

    fn_8000659C();
    value = lbl_1_bss_384C4;
    return lbl_1_bss_384C0 != value;
}
/* fzgx:end fn_1_467F4 */

/* fzgx:begin fn_1_469BC noprologue */
#include "types.h"

extern u32 lbl_1_bss_384C0[];

// Clears invalid entries in the load table and mirrors its first value.
void fn_1_469BC(void) {
    u32 *base;
    u32 *entry;
    int i;

    base = lbl_1_bss_384C0;
    entry = base + 6;
    for (i = 0; i < 0x400;) {
        if (entry[0] == ((u32)1 << 31)) {
            entry[0] = 0;
            base[0x1606] = entry[2];
        }
        i++;
        entry += 4;
    }
    base[1] = base[0];
}
/* fzgx:end fn_1_469BC */

/* fzgx:begin fn_1_46A60 */
void fn_1_46A60(void) {
    fn_1_46A8C(lbl_1_bss_3DCDC);
}
/* fzgx:end fn_1_46A60 */

/* fzgx:begin fn_1_46A8C noprologue */
#include "types.h"

typedef struct {
    u32 type;
    u32 value;
    u32 unk_8;
} Entry;

typedef struct {
    u32 unk_0;
    u32 unk_4;
    u8 unk_8[0x4010];
    Entry entries[0x200];
} State;

extern u32 lbl_1_bss_384C0;
extern u32 fn_1_46EC8(void);
extern u32 fn_1_46ED8(void);

u32 fn_1_46A8C(u32 value) {
    State *base;
    s32 next;
    s32 current;
    u32 initial;
    u32 arg;
    Entry *entry;

    base = (State *)&lbl_1_bss_384C0;
    arg = value;
    initial = base->unk_0;
    next = initial + 1;
    current = initial;
    if (next >= 0x200) {
        next = 0;
    }

    if ((s32)base->unk_4 == next) {
        return -1;
    }

    if (arg < fn_1_46EC8() || arg > fn_1_46ED8()) {
        arg = fn_1_46EC8();
    }

    entry = base->entries;
    entry += base->unk_0;
    base->unk_0 = next;
    entry->type = 0xb;
    entry->value = arg;

    return current;
}
/* fzgx:end fn_1_46A8C */

/* fzgx:begin fn_1_46C60 */
u32 fn_1_46C60(void) {
    return lbl_1_bss_3DCD8;
}
/* fzgx:end fn_1_46C60 */

/* fzgx:begin fn_1_46C70 noprologue */
#include "rel/main_rel/load.h"

extern s32 fn_8000700C(void);

s32 fn_1_46C70(void) {
    s32 value;
    s32 i;
    Obj_1_bss_384D8 *entry;

    value = fn_8000700C();
    if (value == -1) {
        return -1;
    }

    entry = &lbl_1_bss_384D8;
    for (i = 0; i < 0x400; ) {
        if (entry->unk_0 != 0 && (s32)entry->unk_4 == value) {
            return entry->unk_8;
        }
        i++;
        entry = (Obj_1_bss_384D8 *)((u8 *)entry + 0x10);
    }
    return -1;
}
/* fzgx:end fn_1_46C70 */

/* fzgx:begin fn_1_46DC4 */
extern s32 fn_8000700C(s32 arg0);

s32 fn_1_46DC4(s32 value) {
    u8 *entry;
    s32 count;
    s32 i;

    count = 0;
    value = fn_8000700C(value);
    entry = (u8 *)&lbl_1_bss_384D8;
    for (i = 0; i < 1024; i++, entry += 0x10) {
        if ((((Obj_1_bss_384D8 *)entry)->unk_0 & 0x10000000) != 0 &&
            (s32)((Obj_1_bss_384D8 *)entry)->unk_4 == value) {
            ((Obj_1_bss_384D8 *)entry)->unk_0 &= ~0x10000000;
            count++;
        }
    }
    return count;
}
/* fzgx:end fn_1_46DC4 */

/* fzgx:begin fn_1_46EA8 */
void fn_1_46EA8(u32 value) {
    lbl_1_bss_3DD28[0] = value;
}
/* fzgx:end fn_1_46EA8 */

/* fzgx:begin fn_1_46EB4 */
void fn_1_46EB4(u32 value, u32 value2) {
    lbl_1_bss_3DCDC = value;
    lbl_1_bss_3DFF4.unk_0 = value2;
}
/* fzgx:end fn_1_46EB4 */

/* fzgx:begin fn_1_46EC8 */
// Returns the current load-state value.
u32 fn_1_46EC8(void) {
    return lbl_1_bss_3DCDC;
}
/* fzgx:end fn_1_46EC8 */

/* fzgx:begin fn_1_46ED8 */
u32 fn_1_46ED8(void) {
    return lbl_1_bss_3DFF4.unk_0;
}
/* fzgx:end fn_1_46ED8 */

/* fzgx:begin fn_1_47184 */
u32 fn_1_47184(void) {
    return lbl_1_bss_3DFF4.unk_0 - lbl_1_bss_3DCDC;
}
/* fzgx:end fn_1_47184 */

/* fzgx:begin fn_1_471A0 */
#include "types.h"



u32 fn_1_471A0(void) {
    u32 *p;
    u32 i;
    u32 total;

    total = 0;
    p = (*(u32 (*)[5632])&lbl_1_bss_384D8);
    for (i = 0; i < 0x400; i++, p += 4) {
        if ((p[0] & 0x64000000) != 0) {
            total += p[3];
        }
    }
    return total;
}
/* fzgx:end fn_1_471A0 */

/* fzgx:begin fn_1_47268 */
#include "types.h"



u32 fn_1_47268(void) {
    u32 *p;
    u32 i;
    u32 total;

    total = 0;
    p = (*(u32 (*)[])&lbl_1_bss_384D8);
    for (i = 0; i < 0x400; i++, p += 4) {
        if ((p[0] & 0x10000000) != 0) {
            total += p[3];
        }
    }
    return total;
}
/* fzgx:end fn_1_47268 */

/* fzgx:begin fn_1_479B0 */
// Reset the loading state and clear the associated resource markers.
void fn_1_479B0(void) {
    fn_1_47EE4(0);
    fn_1_485C8(0);
    lbl_1_data_6CA0.unk_0 = -1;
    *(u32 *)&lbl_1_data_6CA0.pad_C[0] = -1;
    *(u32 *)&lbl_1_data_6CA0.pad_C[0xc] = -1;
}
/* fzgx:end fn_1_479B0 */

/* fzgx:begin fn_1_479F0 */
void fn_1_479F0(s16 index) {
    s32 *entry;
    s32 i;

    entry = (s32 *)&lbl_1_data_67F0.unk_0 + index * 20;
    for (i = 0; i < 10; i++, entry += 2) {
        if (entry[0] != -1) {
            fn_1_48004(entry[0], entry[1]);
        } else {
            return;
        }
    }
}
/* fzgx:end fn_1_479F0 */

/* fzgx:begin fn_1_47A60 */
// Process the ten load entries associated with the selected index.
void fn_1_47A60(s16 index) {
    s32 *entry;
    s32 i;

    entry = (s32 *)&lbl_1_data_67F0.unk_0 + index * 20;
    for (i = 0; i < 10; i++) {
        if (entry[i * 2] != -1) {
            fn_1_48140(entry[i * 2]);
        } else {
            fn_1_4DDC0();
            fn_1_4F724();
            break;
        }
    }
}
/* fzgx:end fn_1_47A60 */

/* fzgx:begin fn_1_485E8 */
// Find the resource matching value, load its data, and return the destination buffer.
void *fn_1_485E8(s32 index, s32 value) {
    s32 entry = 0;

    while (((s16 **)lbl_1_data_19FC4)[index][entry] != -1) {
        if (((s16 **)lbl_1_data_19FC4)[index][entry] == value) {
            fn_80083DB0(lbl_1_bss_3E024,
                        ((void ***)lbl_1_data_19098)[index][entry]);
            return lbl_1_bss_3E024;
        }
        entry++;
    }

    fn_80083DB0(lbl_1_bss_3E024, lbl_1_data_1A3AC);
    return lbl_1_bss_3E024;
}
/* fzgx:end fn_1_485E8 */
