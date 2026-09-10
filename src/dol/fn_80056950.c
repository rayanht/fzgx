#include "types.h"

extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 lbl_800921D0[];

typedef struct {
    s32 key;
    u8 unk04[0x14];
    s32 val;
    u8 unk1C[4];
} Entry;

typedef struct {
    u8 unk00[0x38];
    Entry entries[16];
} Table;

int fn_80056950(Table *tbl, int value) {
    int count;

    if (tbl == 0) {
        fn_800565FC((u32)&lbl_80092188);
        return -1;
    }

    for (count = 0; count < 16; count++) {
        if (tbl->entries[count].key == value) {
            break;
        }
    }

    if (count == 16) {
        fn_800565FC((u32)&lbl_800921D0);
        return -1;
    }

    return tbl->entries[count].val;
}
