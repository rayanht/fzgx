#include "types.h"

extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 lbl_800921D0[];

typedef struct {
    u32 key;
    u8 unk04[0x18];
    u32 val;
} Entry;

typedef struct {
    u8 unk00[0x38];
    Entry entries[16];
} Table;

u32 fn_80056850(u32 arg0, u32 arg1) {
    u32 v0;
    s32 v3;
    Table *tbl;

    v0 = arg0;
    if (arg0 == 0) {
    v0 = (u32)&lbl_80092188;
    fn_800565FC((u32)v0);
    v0 = 0;
    } else {
    tbl = (Table *)arg0;
    for (v3 = 0; v3 < 16; v3++) {
    if ((s32)tbl->entries[v3].key == (s32)arg1) {
    break;
    }
    }
    if (v3 == 16) {
    v0 = (u32)&lbl_800921D0;
    fn_800565FC((u32)v0, arg1);
    v0 = 0;
    } else {
    v0 = tbl->entries[v3].val;
    }
    }
    return v0;
}
