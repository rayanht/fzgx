#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/archive.h"

extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);
extern void fn_1_12A350(void *arg0, s32 arg1);
extern s32 fn_8006A480(void *arg0, void *arg1, void *arg2);
extern s32 fn_8006A998(void *arg0);
extern void fn_8006A9AC(void *arg0);
extern void fn_1_12AC28(void *arg0, s32 arg1, s32 arg2);
extern void fn_1_12ADC8(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void fn_1_12BB18(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4);
extern void fn_1_8D168(void *arg);
extern void fn_1_14DB48(void *arg0, void *arg1, u32 arg2);
extern void fn_1_14DBCC(void *arg);
extern u32 fn_1_95120(void *arg);
extern const struct Table lbl_1_rodata_8230;
extern u32 lbl_801A66A0;
extern void fn_1_7B2E8(u8 value);
extern void fn_1_13C1A0(void);
extern void *fn_1_3F8C(void *table, void (*callback)(void), void *arg1, void *arg2);
extern void fn_1_426C(s32 value);
extern void fn_1_7B4C0(void);
extern void fn_1_C2454(void);
extern s32 fn_1_C24A4(void);
extern u8 fn_1_B7C00(void);

extern s32 lbl_1_bss_897A4;
extern void *lbl_801A6410;
extern void fn_1_46B4(void *arg0, void *arg1, unsigned char *arg2, s32 arg3);
extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);

extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);
extern s32 lbl_1_bss_8CA44[10];

extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);
extern void fn_1_435C();

/* fzgx:begin fn_1_12A2D0 */
extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);

// Store the selected entry when it is valid; otherwise report an invalid entry.
void fn_1_12A2D0(s32 value) {
    Obj_1_bss_897AC *entry;

    entry = (Obj_1_bss_897AC *)((u8 *)&lbl_1_bss_897AC + value * 0x6c);
    if ((s32)entry->unk_0 == 1) {
        lbl_1_bss_897A0 = value;
    } else {
        extern void OSPanic(char *arg0, s32 arg1, ...);

        OSPanic((char *)lbl_1_data_40608, 0x5d, lbl_1_data_40614);
    }
}
/* fzgx:end fn_1_12A2D0 */

/* fzgx:begin fn_1_12A32C */
void fn_1_12A32C(void *arg0) {
    fn_1_12A350(arg0, 0);
}
/* fzgx:end fn_1_12A32C */

/* fzgx:begin fn_1_12A6D8 */
s32 fn_1_12A6D8(void *arg0) {
    u8 local[0x10];
    if (fn_8006A480((u8 *)&lbl_1_bss_897AC + lbl_1_bss_897A0 * 0x6c + 0x4c, arg0, local) != 0) {
        return fn_8006A998(local);
    }
    return 0;
}
/* fzgx:end fn_1_12A6D8 */

/* fzgx:begin fn_1_12A8A4 noprologue */
#include "types.h"
#include "rel/main_rel/archive.h"

extern u32 lbl_1_bss_897A0;
extern u32 lbl_801A6410;

typedef struct ArchiveState {
    s32 count;
    s32 loaded;
    u8 pad[4];
    u8 entries[1];
} ArchiveState;

extern s32 fn_8006A480(void *arg0, void *arg1, void *arg2);
extern void *fn_8006A998(void *arg0);
extern s32 fn_1_45730(void *arg0, void *arg1);
extern s32 fn_1_45B2C(void *arg0);
extern void *fn_1_45D0(u32 arg0, u32 arg1, void *arg2, u32 arg3);
extern void fn_1_458A0(void *arg0, void *arg1, u32 arg2, u32 arg3);
extern void fn_1_45850(void *arg0);
extern void OSPanic(u8 *arg0, s32 arg1, u8 *arg2, ...);

#pragma opt_propagation off
s32 fn_1_12A8A4(u32 arg0, void *arg1) {
    u8 *entries;
    s32 result;
    u8 work[12];
    u8 info[0x60];
    ArchiveState *state;

    state = (ArchiveState *)&lbl_1_bss_897A0;

    if (state->loaded != 0) {
        s32 count = state->count;
        entries = state->entries;
        if (fn_8006A480(entries + count * 0x6C + 0x4C,
                        (void *)arg0, work) != 0) {
            result = (s32)fn_8006A998(work);
        } else {
            result = 0;
        }
        *(void **)arg1 = (void *)result;
        if (*(void **)arg1 == 0) {
            return 0;
        }
    } else {
        if (fn_1_45730((void *)arg0, info) != 0) {
            s32 aligned;
            aligned = (fn_1_45B2C(info) + 0x1F) & ~0x1F;
            *(void **)arg1 = fn_1_45D0(lbl_801A6410, aligned,
                                       lbl_1_data_40608, 0x188);
            fn_1_458A0(info, *(void **)arg1, aligned, 0);
            fn_1_45850(info);
        } else {
            OSPanic(lbl_1_data_40608, 0x18C, lbl_1_data_40750);
        }
    }

    return 1;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_12A8A4 */

/* fzgx:begin fn_1_12A9BC noprologue */
#include "types.h"
#include "rel/main_rel/archive.h"

extern u32 lbl_1_bss_897A0;
extern u32 lbl_801A6410;

typedef struct ArchiveState {
    s32 count;
    s32 loaded;
    u8 pad[4];
    u8 entries[1];
} ArchiveState;

extern s32 fn_8006A480(void *arg0, void *arg1, void *arg2);
extern void *fn_8006A998(void *arg0);
extern s32 fn_1_45730(void *arg0, void *arg1);
extern s32 fn_1_45B2C(void *arg0);
extern void *fn_1_45D0(u32 arg0, u32 arg1, void *arg2, u32 arg3);
extern void fn_1_458A0(void *arg0, void *arg1, u32 arg2, u32 arg3);
extern void fn_1_45850(void *arg0);

#pragma opt_propagation off
s32 fn_1_12A9BC(void *arg0, void *arg1) {
    u8 *entries;
    s32 result;
    s32 ok = 1;
    u8 work[12];
    u8 info[0x50];
    ArchiveState *state;

    state = (ArchiveState *)&lbl_1_bss_897A0;

    if (state->loaded != 0) {
        s32 count = state->count;
        entries = state->entries;
        if (fn_8006A480(entries + count * 0x6C + 0x4C,
                        arg0, work) != 0) {
            result = (s32)fn_8006A998(work);
        } else {
            result = 0;
        }
        *(void **)arg1 = (void *)result;
        if (*(void **)arg1 == 0) {
            ok = 0;
        }
    } else {
        if (fn_1_45730(arg0, info) != 0) {
{
    s32 aligned;
            aligned = (fn_1_45B2C(info) + 0x1F) & ~0x1F;
            *(void **)arg1 = fn_1_45D0(lbl_801A6410, aligned,
                                       lbl_1_data_40608, 0x1AC);
            fn_1_458A0(info, *(void **)arg1, aligned, 0);
}
            fn_1_45850(info);
        } else {
            ok = 0;
        }
    }

    return ok;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_12A9BC */

/* fzgx:begin fn_1_12AAC8 */
void fn_1_12AAC8(void *arg0) {
    u8 local_8[0x18];
    u8 *obj;

    obj = (u8 *)&lbl_1_bss_897AC + lbl_1_bss_897A0 * 0x6C + 0x4C;
    if (fn_8006A480(obj, arg0, local_8) == 0) {
        OSPanic(lbl_1_data_40608, 0x1BE, lbl_1_data_4076C);
    }
    fn_8006A9AC(local_8);
}
/* fzgx:end fn_1_12AAC8 */

/* fzgx:begin fn_1_12ABB4 */
// Register the archive table only on its first use.
void fn_1_12ABB4(void *archive) {
    if (lbl_1_bss_897A4 == 0) {
        fn_1_46B4(lbl_801A6410, archive, lbl_1_data_40608, 0x1e0);
    }
}
/* fzgx:end fn_1_12ABB4 */

/* fzgx:begin fn_1_12AC00 */
void fn_1_12AC00(void *arg0) {
    fn_1_12AC28(arg0, 0, 0);
}
/* fzgx:end fn_1_12AC00 */

/* fzgx:begin fn_1_12ADA0 */
void fn_1_12ADA0(void *arg0, void *arg1) {
    fn_1_12ADC8(arg0, arg1, 0, 0);
}
/* fzgx:end fn_1_12ADA0 */

/* fzgx:begin fn_1_12AF50 */
u32 fn_1_12AF50(u32 value) {
    u32 old_value = lbl_1_data_40600;
    lbl_1_data_40600 = value;
    return old_value;
}
/* fzgx:end fn_1_12AF50 */

/* fzgx:begin fn_1_12AF64 */
u32 fn_1_12AF64(void) {
    u32 value;

    value = lbl_1_data_40600;
    lbl_1_data_40600 = -1;
    return value;
}
/* fzgx:end fn_1_12AF64 */

/* fzgx:begin fn_1_12B3BC */
typedef struct {
    u8 pad_0[0x4];
    void *unk_4;
    void *unk_8;
    u8 pad_C[0x10];
    void *unk_1C;
} FnObj;

void fn_1_12B3BC(FnObj *arg0, void *arg1, void *arg2, void *arg3,
                 void *arg4, void *arg5, void *arg6) {
    fn_1_12BB18(arg0->unk_4, arg0->unk_8, &lbl_1_bss_8B3A0,
                 arg0->unk_1C, arg6);
}
/* fzgx:end fn_1_12B3BC */

/* fzgx:begin fn_1_12B3F8 noprologue */
#include "types.h"

struct fn_1_12B3F8_Arg5 {
    u32 unk_0;
};
struct fn_1_12B3F8_lbl_1_bss_8B3A0 {
    u8 pad_0[0x94];
    u32 unk_94;
};
extern struct fn_1_12B3F8_lbl_1_bss_8B3A0 lbl_1_bss_8B3A0;
extern void * fn_1_435C(void *);
extern void fn_1_426C(u32);
extern u32 fn_1_12DAEC(u32, u32, u32, void *, u32, u32, u32);
extern u32 fn_1_12C524(u32);
extern void fn_1_12C000(void *, s16);


void fn_1_12B3F8(void *arg0, void *arg1, void *arg2, u32 arg3, u32 arg4, s32 *arg5, s32 arg_sp0) {
    s16 var_r30;

    if ((s32) (*(s32 *)((u8 *)(arg5) + 0)) != -1) {
        fn_1_435C((void *)(arg2));
        fn_1_426C((u32) (*(s32 *)((u8 *)(arg5) + 0)));
        (*(s32 *)((u8 *)(arg5) + 0)) = -1;
    }
    if (!(lbl_1_bss_8B3A0.unk_94 & 0x80000000)) {
        var_r30 = 4;
        fn_1_12DAEC(*(u32 *)((u8 *)(arg0) + 4), *(u32 *)((u8 *)(arg0) + 8), *(u32 *)((u8 *)(arg0) + 24), (void *)(arg1), arg3, arg4, *(u32 *)((u8 *)(arg0) + 52));
        fn_1_12C524(*(u32 *)((u8 *)(arg0) + 12));
        if (lbl_1_bss_8B3A0.unk_94 & 0x20000000) {
            var_r30 = 1;
        } else if (lbl_1_bss_8B3A0.unk_94 & 0x40000) {
            var_r30 = 2;
        }
        if (lbl_1_bss_8B3A0.unk_94 & 0x40000000) {
            fn_1_12C000((void *)(*(void **)((u8 *)(arg0) + 36)), 4);
        } else {
            fn_1_12C000((void *)(*(void **)((u8 *)(arg0) + 36)), var_r30);
        }
        fn_1_12C000((void *)(*(void **)((u8 *)(arg0) + 32)), var_r30);
    }
}
/* fzgx:end fn_1_12B3F8 */

/* fzgx:begin fn_1_12BF7C noprologue */
#include "types.h"

typedef struct {
    u8 pad[0x94];
    u32 unk94;
} GlobalState;

extern GlobalState lbl_1_bss_8B3A0;
extern void fn_1_8CED0(void *arg, u16 a, u16 b);
extern void fn_1_8D0A4(void *arg);

void fn_1_12BF7C(void *arg, s16 count, u32 a, u32 b) {
    u8 *p;
    s16 i;

    if ((lbl_1_bss_8B3A0.unk94 & 0x80000000) == 0) {
        p = (u8 *)arg;
        i = 0;
        while (i < count) {
            fn_1_8CED0(p, (u16)a, (u16)b);
            fn_1_8D0A4(p);
            p += 100;
            i++;
        }
    }
}
/* fzgx:end fn_1_12BF7C */

/* fzgx:begin fn_1_12C000 */
void fn_1_12C000(void *arg, s16 count) {
    u8 *p;
    s16 i;

    p = (u8 *)arg;
    i = 0;
    while (i < count) {
        fn_1_8D168(p);
        p += 100;
        i++;
    }
}
/* fzgx:end fn_1_12C000 */

/* fzgx:begin fn_1_12C060 */
typedef struct FnData FnData;

struct FnData {
    u16 unk0;
    u32 unk4;
    u8 unk8;
    u8 pad9[3];
    u8 (*unkC)(FnData *, u32);
    u32 unk10;
    s32 (*unk14)(FnData *, u32);
    u32 unk18;
};

s32 fn_1_12C060(FnData *arg) {
    if (arg->unk8 == 0) {
        return 0;
    }
    if (arg->unkC(arg, arg->unk10) == 1) {
        arg->unk8 = 0;
        arg->unk4 = 0;
        return arg->unk14(arg, arg->unk18);
    }
    arg->unk4++;
    return 0;
}
/* fzgx:end fn_1_12C060 */

/* fzgx:begin fn_1_12C0EC */
typedef struct {
    u16 unk0;
    u32 unk4;
    u8 unk8;
    u8 pad9[3];
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
} FnData;

void fn_1_12C0EC(FnData *arg) {
    arg->unk18 = 0;
    arg->unk14 = 0;
    arg->unk10 = 0;
    arg->unkC = 0;
    arg->unk8 = 0;
    arg->unk4 = 0;
    arg->unk0 = 0;
}
/* fzgx:end fn_1_12C0EC */

/* fzgx:begin fn_1_12C47C */
void fn_1_12C47C(void *arg0, void *arg1, s32 arg2) {
    void *entry;
    void *obj;
    u32 mask;
    s16 i;

    if ((lbl_1_bss_8B3A0.unk_94 & 0x02000000) != 0) {
        return;
    }
    entry = arg1;
    obj = arg0;
    i = 0;
    mask = 1 << arg2;
    while (i < 4) {
        if (((*(u32 *)entry & ((u32)1 << 31)) != 0) &&
            ((*(u32 *)entry & ((u32)1 << 30)) != 0)) {
            fn_1_14DB48(entry, obj, mask);
        }
        entry = (u8 *)entry + 0x81c0;
        obj = (u8 *)obj + 0xa20;
        i++;
    }
}
/* fzgx:end fn_1_12C47C */

/* fzgx:begin fn_1_12C6BC */
void fn_1_12C6BC(void *arg) {
    u8 *p;
    s16 i;

    p = (u8 *)arg;
    i = 0;
    while (i < 9) {
        fn_1_14DBCC(p);
        p += 0xa20;
        i++;
    }
}
/* fzgx:end fn_1_12C6BC */

/* fzgx:begin fn_1_12C710 */
extern s16 fn_1_12C930(s16 arg);

s16 fn_1_12C710(int arg) {
    s16 i;

    switch (arg) {
    case 0x15:
    case 0x29:
        return 0x15;
    case 0x21:
    case 0x2a:
    case 0x2b:
        return 0x21;
    }

    i = 0;
    while (i < 0x29) {
        if (arg == fn_1_12C930(i)) {
            return i;
        }
        i++;
    }
    return -1;
}
/* fzgx:end fn_1_12C710 */

/* fzgx:begin fn_1_12C7B8 */
typedef struct {
    u8 pad0[5];
    u8 id;
    u8 pad6[0x819a];
    u8 value;
    u8 pad_a1[0x1f];
} FnEntry;

extern FnEntry *fn_1_12F118(void);
extern FnEntry *fn_1_36AD0(void);

s16 fn_1_12C7B8(s16 arg) {
    FnEntry *table;
    s16 i;

    if (arg < 0x29) {
        return arg;
    }

    table = fn_1_12F118();
    if (table == 0) {
        return 6;
    }

    if (table != fn_1_36AD0()) {
        for (i = 0; i < 9; i++) {
            if (table[i].id == arg) {
                return table[i].value;
            }
        }
    } else if (arg >= 0x32 && arg <= 0x35) {
        return table[arg - 0x32].value;
    } else if (arg >= 0x36 && arg <= 0x39) {
        return table[arg - 0x36].value;
    } else {
        for (i = 0; i < 4; i++) {
            if (table[i].id == arg) {
                return table[i].value;
            }
        }
    }

    return 6;
}
/* fzgx:end fn_1_12C7B8 */

/* fzgx:begin fn_1_12CB04 */
typedef struct {
    u8 pad0[5];
    u8 id;
    u8 pad6[0x819a];
    u8 value;
    u8 pad_a1[0x1f];
} FnEntry;

extern FnEntry *fn_1_12F118(void);
extern FnEntry *fn_1_36AD0(void);

static inline s16 fn_1_12CB04_inline(s16 arg) {
    FnEntry *table;
    s16 i;

    if (arg < 0x29) {
        return arg;
    }

    table = fn_1_12F118();
    if (table == 0) {
        return 6;
    }

    if (table != fn_1_36AD0()) {
        for (i = 0; i < 9; i++) {
            if (table[i].id == arg) {
                return table[i].value;
            }
        }
    } else if (arg >= 0x32 && arg <= 0x35) {
        return table[arg - 0x32].value;
    } else if (arg >= 0x36 && arg <= 0x39) {
        return table[arg - 0x36].value;
    } else {
        for (i = 0; i < 4; i++) {
            if (table[i].id == arg) {
                return table[i].value;
            }
        }
    }

    return 6;
}

s32 fn_1_12CB04(s16 arg) {
    switch (fn_1_12CB04_inline(arg)) {
    case 0x15:
        return 1;
    case 0x21:
        return 2;
    }

    return 0;
}
/* fzgx:end fn_1_12CB04 */

/* fzgx:begin fn_1_12D254 noprologue */
#include "types.h"

extern u8 lbl_1_data_20D1C[180];
extern char lbl_1_data_40798[9];
extern u8 lbl_1_bss_8B4EC[128];

extern void fn_80083DB0(void *arg0, char *arg1);
extern void strcat(void *arg0, void *arg1);

#pragma opt_propagation off
u8 *fn_1_12D254(s32 arg0, s32 arg1) {
    char *base;
    void *value;

    base = lbl_1_data_40798;
    value = ((void **)lbl_1_data_20D1C)[arg0];
    fn_80083DB0(lbl_1_bss_8B4EC, base + 0x324);
    strcat(lbl_1_bss_8B4EC, value);
    strcat(lbl_1_bss_8B4EC, base + 0x330);

    switch (arg1) {
    case 0x40000000:
        strcat(lbl_1_bss_8B4EC, base + 0x338);
        break;
    case 0x20000000:
        strcat(lbl_1_bss_8B4EC, base + 0x340);
        break;
    case 0x10000000:
        strcat(lbl_1_bss_8B4EC, base + 0x348);
        break;
    }

    strcat(lbl_1_bss_8B4EC, base + 0x350);
    return lbl_1_bss_8B4EC;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_12D254 */

/* fzgx:begin fn_1_12D354 */
// Registers an object in the first available archive slot and reports overflow.
void fn_1_12D354(void *arg0, void *arg1, void *arg2) {
    u8 *archive_data = lbl_1_data_40798;
    u32 slot;

    if (arg2 == 0) {
        OSPanic(archive_data + 0x358, 0x388, archive_data + 0x368);
    }

    for (slot = 0; slot < 12; slot++) {
        if ((&lbl_1_bss_8B56C.unk_0)[slot * 2] == 0) {
            (&lbl_1_bss_8B56C.unk_0)[slot * 2] = (u32)arg2;
            (&lbl_1_bss_8B56C.unk_0)[slot * 2 + 1] = 0;
            return;
        }
    }

    OSPanic(archive_data + 0x358, 0x394, archive_data + 0x390);
}
/* fzgx:end fn_1_12D354 */

/* fzgx:begin fn_1_12E424 */
// Reports whether the archive state is active, otherwise querying the supplied entry.
u8 fn_1_12E424(void *arg0, u8 *arg1) {
    if (lbl_1_bss_8B3A0.unk_94 & (1u << 31)) {
        return 1;
    }
    return (u8)fn_1_95120(arg1 + 0x148);
}
/* fzgx:end fn_1_12E424 */

/* fzgx:begin fn_1_12EF24 */
struct Table {
    s16 values[66];
};

s16 fn_1_12EF24(s16 row, s16 column) {
    struct Table table = lbl_1_rodata_8230;
    return *(s16 *)((u8 *)table.values + row * 12 + column * 2);
}
/* fzgx:end fn_1_12EF24 */

/* fzgx:begin fn_1_12F028 */
typedef struct {
    s16 values[6];
} Entry;

typedef struct {
    Entry entries[11];
} EntryTable;

extern EntryTable lbl_1_rodata_8338;
extern s32 fn_1_F89E4(u8 value);

s16 fn_1_12F028(s16 value) {
    EntryTable table;
    s16 count;
    s16 i;

    table = lbl_1_rodata_8338;
    count = 0;
    if (value == 5) {
        i = 0;
        while (i < 6) {
            if (fn_1_F89E4((u8)i) != 0) {
                count++;
            }
            i++;
        }
    } else {
        i = 0;
        while (i < 6) {
            if (table.entries[value].values[i] != -1) {
                count++;
            }
            i++;
        }
    }
    return count;
}
/* fzgx:end fn_1_12F028 */

/* fzgx:begin fn_1_12F10C */
void fn_1_12F10C(u32 value) {
    lbl_1_bss_8B5EC = value;
}
/* fzgx:end fn_1_12F10C */

/* fzgx:begin fn_1_12F118 */
u32 fn_1_12F118(void) {
    return lbl_1_bss_8B5EC;
}
/* fzgx:end fn_1_12F118 */

/* fzgx:begin fn_1_12F128 */
// Stores the current global value in the indexed archive slot.
void fn_1_12F128(s16 index) {
    (&lbl_1_bss_8B3A0.unk_E0)[index] = lbl_801A66A0;
}
/* fzgx:end fn_1_12F128 */

/* fzgx:begin fn_1_12F150 */
// Store the timestamp and two values for one archive entry.
void fn_1_12F150(s16 index, u32 value_100, u32 value_110) {
    (&lbl_1_bss_8B3A0.unk_F0)[index] = lbl_801A66A0;
    (&lbl_1_bss_8B3A0.unk_100)[index] = value_100;
    (&lbl_1_bss_8B3A0.unk_110)[index] = value_110;
}
/* fzgx:end fn_1_12F150 */

/* fzgx:begin fn_1_12F17C */
void fn_1_12F17C(void) {
    lbl_1_bss_8B3A0.unk_120 = lbl_801A66A0;
}
/* fzgx:end fn_1_12F17C */

/* fzgx:begin fn_1_12F194 */
// Reset the archived state counters and values.
void fn_1_12F194(void) {
    lbl_1_bss_8B3A0.unk_120 = 0;
    lbl_1_bss_8B3A0.unk_F0 = 0;
    lbl_1_bss_8B3A0.unk_100 = 0;
    lbl_1_bss_8B3A0.unk_110 = 0;
    lbl_1_bss_8B3A0.unk_E0 = 0;
    lbl_1_bss_8B3A0.unk_F4 = 0;
    lbl_1_bss_8B3A0.unk_104 = 0;
    lbl_1_bss_8B3A0.unk_114 = 0;
    lbl_1_bss_8B3A0.unk_E4 = 0;
    lbl_1_bss_8B3A0.unk_F8 = 0;
    lbl_1_bss_8B3A0.unk_108 = 0;
    lbl_1_bss_8B3A0.unk_118 = 0;
    lbl_1_bss_8B3A0.unk_E8 = 0;
    lbl_1_bss_8B3A0.unk_FC = 0;
    lbl_1_bss_8B3A0.unk_10C = 0;
    lbl_1_bss_8B3A0.unk_11C = 0;
    lbl_1_bss_8B3A0.unk_EC = 0;
}
/* fzgx:end fn_1_12F194 */

/* fzgx:begin fn_1_12F1E8 */
typedef struct {
    u8 pad_0[0x94];
    u32 unk_94;
    u8 pad_98[0x8C];
    s32 unk_124;
    u8 unk_128;
} FnState;

void fn_1_12F1E8(s32 value) {
    if ((lbl_1_bss_8B3A0.unk_94 & 0x40000000) == 0) {
        return;
    }

    if (value == 0) {
        lbl_1_bss_8B3A0.unk_124 = -1;
    } else {
        lbl_1_bss_8B3A0.unk_124 = value;
    }
    lbl_1_bss_8B3A0.unk_128 = 0;
}
/* fzgx:end fn_1_12F1E8 */

/* fzgx:begin fn_1_12F228 */
u32 fn_1_12F228(void) {
    if ((lbl_1_bss_8B3A0.unk_94 & 0x40000000) == 0) {
        return 0;
    }
    return lbl_1_bss_8B3A0.unk_124 == -1;
}
/* fzgx:end fn_1_12F228 */

/* fzgx:begin fn_1_12F258 */
s32 fn_1_12F258(void) {
    s32 value = lbl_1_bss_8B3A0.unk_124;

    if ((lbl_1_bss_8B3A0.unk_94 & 0x40000000) == 0) {
        return -1;
    }
    if (value < 0) {
        return -1;
    }
    return value;
}
/* fzgx:end fn_1_12F258 */

/* fzgx:begin fn_1_12F28C */
void fn_1_12F28C(void *arg0, void **result, void *arg2, u8 *arg3) {
    fn_1_7B2E8(*arg3);
    fn_1_435C(arg0);
    *result = fn_1_3F8C(lbl_1_data_40BC0, fn_1_13C1A0, arg3, arg2);
}
/* fzgx:end fn_1_12F28C */

/* fzgx:begin fn_1_12F308 */
// fn_1_12F308: empty in retail (single blr).
void fn_1_12F308(void) {
}
/* fzgx:end fn_1_12F308 */

/* fzgx:begin fn_1_12F30C */
typedef struct Fn1_12F30CState {
    s32 value;
} Fn1_12F30CState;

extern void fn_1_435C(void *arg0, Fn1_12F30CState *state);

// Resets the active archive entry before advancing archive processing.
void fn_1_12F30C(void *arg0, Fn1_12F30CState *state) {
    if (state->value != -1) {
        fn_1_435C(arg0, state);
        fn_1_426C(state->value);
        state->value = -1;
    }
    fn_1_7B4C0();
}
/* fzgx:end fn_1_12F30C */

/* fzgx:begin fn_1_130EE8 noprologue */
#include "types.h"

struct fn_1_130EE8_lbl_1_bss_8CA40 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};

extern s32 fn_1_3F8C(u32, u32, u32, u32);
extern struct fn_1_130EE8_lbl_1_bss_8CA40 lbl_1_bss_8CA40;
extern u32 fn_1_435C(u32);
extern u32 lbl_1_data_40E7C;
extern u32 lbl_1_data_40E90;
extern void fn_1_130F98(void);
extern void fn_1_131000(void);

void fn_1_130EE8(u32 arg0, u32 arg1) {
    struct fn_1_130EE8_lbl_1_bss_8CA40 *p_lbl_1_bss_8CA40;
    u32 t1, t3;
    p_lbl_1_bss_8CA40 = (struct fn_1_130EE8_lbl_1_bss_8CA40 *)&lbl_1_bss_8CA40;
    p_lbl_1_bss_8CA40->unk_0 = -1;
    p_lbl_1_bss_8CA40->unk_4 = -1;
    p_lbl_1_bss_8CA40->unk_8 = -1;
    p_lbl_1_bss_8CA40->unk_C = 0;
    p_lbl_1_bss_8CA40->unk_10 = 0;
    p_lbl_1_bss_8CA40->unk_14 = 0;
    p_lbl_1_bss_8CA40->unk_18 = 0;
    p_lbl_1_bss_8CA40->unk_1C = arg0;
    p_lbl_1_bss_8CA40->unk_20 = arg1;
    fn_1_435C(arg0);
    t1 = fn_1_3F8C((u32)&lbl_1_data_40E7C, (u32)fn_1_130F98, 0, 8);
    p_lbl_1_bss_8CA40->unk_24 = t1;
    fn_1_435C(arg1);
    t3 = fn_1_3F8C((u32)&lbl_1_data_40E90, (u32)fn_1_131000, 0, 8);
    p_lbl_1_bss_8CA40->unk_28 = t3;
}
/* fzgx:end fn_1_130EE8 */

/* fzgx:begin fn_1_130F98 */
// Promote a pending archive operation, then invoke its selected handler.
void fn_1_130F98(void) {
    if (lbl_1_bss_8CA44[0] >= 0) {
        s32 pending_operation = lbl_1_bss_8CA44[0];

        lbl_1_bss_8CA44[0] = -1;
        lbl_1_bss_8CA40 = pending_operation;
    }

    {
        s32 operation = lbl_1_bss_8CA40;

        if (operation >= 0) {
            ((void (**)(void))lbl_1_data_40D50)[operation]();
        }
    }
}
/* fzgx:end fn_1_130F98 */

/* fzgx:begin fn_1_131000 */
// fn_1_131000: empty in retail (single blr).
void fn_1_131000(void) {
}
/* fzgx:end fn_1_131000 */

/* fzgx:begin fn_1_131004 */
struct Fn131004State {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};

void fn_1_131004(void) {
    struct Fn131004State *state = (struct Fn131004State *)&lbl_1_bss_8CA40;

    fn_1_435C(state->unk_1C);
    fn_1_426C(state->unk_24);
    fn_1_435C(state->unk_20);
    fn_1_426C(state->unk_28);
}
/* fzgx:end fn_1_131004 */

/* fzgx:begin fn_1_131050 */
void fn_1_131050(u32 value, u32 state) {
    u32* data = &lbl_1_bss_8CA40;
    s32 previous;

    if (value == 0) {
        return;
    }

    previous = *(s32*)data;
    data[3] = value;
    data[2] = state;
    data[11] = state;

    if (previous == -1) {
        data[1] = 2;
    }
}
/* fzgx:end fn_1_131050 */

/* fzgx:begin fn_1_131084 noprologue */
#include "types.h"

struct fn_1_131084_lbl_1_bss_8CA40 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0x4];
    u32 unk_10;
    u8 pad_14[0x18];
    u32 unk_2C;
};

extern struct fn_1_131084_lbl_1_bss_8CA40 lbl_1_bss_8CA40;

void fn_1_131084(u32 arg0, u32 arg1) {
    struct fn_1_131084_lbl_1_bss_8CA40 *p_lbl_1_bss_8CA40;
    p_lbl_1_bss_8CA40 = (struct fn_1_131084_lbl_1_bss_8CA40 *)&lbl_1_bss_8CA40;
    if (arg0 == 0) { return; }
{
    u32 v0;
    v0 = p_lbl_1_bss_8CA40->unk_0;
    p_lbl_1_bss_8CA40->unk_10 = arg0;
    p_lbl_1_bss_8CA40->unk_8 = arg1;
    p_lbl_1_bss_8CA40->unk_2C = arg1;
    if ((s32)v0 != -1) { return; }
}
    p_lbl_1_bss_8CA40->unk_4 = 4;
}
/* fzgx:end fn_1_131084 */

/* fzgx:begin fn_1_1310B8 noprologue */
#include "types.h"

struct State {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0x20];
    u32 unk_2C;
};

extern struct State lbl_1_bss_8CA40;

#pragma peephole off
void fn_1_1310B8(void) {
    struct State *state;
    u32 status;

    state = &lbl_1_bss_8CA40;
    status = state->unk_0;
    if ((s32)status != -1) {
        return;
    }
    state->unk_4 = 0;
    state->unk_8 = 0;
    state->unk_2C = 0;
}
#pragma peephole reset
/* fzgx:end fn_1_1310B8 */

/* fzgx:begin fn_1_1310E0 */
s32 fn_1_1310E0(void) {
    return lbl_1_bss_8CA40 != -1;
}
/* fzgx:end fn_1_1310E0 */

/* fzgx:begin fn_1_1310FC */
void fn_1_1310FC(void) {
    u8* ptr = (u8*)&lbl_1_bss_8CA40;
    
    if (*(s32*)(ptr + 0x8) == -1) {
        *(u32*)(ptr + 0x0) = (u32)-1;
    } else {
        fn_1_C2454();
        *(u32*)(ptr + 0x4) = 1;
        *(u8*)(ptr + 0x30) = 0;
    }
}
/* fzgx:end fn_1_1310FC */

/* fzgx:begin fn_1_131154 */
void fn_1_131154(void) {
    if (fn_1_C24A4() == 0 && fn_1_B7C00() == 0) {
        lbl_1_bss_8CA40 = -1;
    }
}
/* fzgx:end fn_1_131154 */
