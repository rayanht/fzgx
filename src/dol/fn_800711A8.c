#include "types.h"

typedef void (*fn_800711A8_Fn)(void *);

extern fn_800711A8_Fn lbl_801A6D08;

struct fn_800711A8_Entry {
    u8 pad_00[0x24];
    void *field_24;
};

struct fn_800711A8_Arg0 {
    s32 count;
    u8 pad_04[4];
    struct fn_800711A8_Entry **entries;
    u8 pad_0C[4];
    u32 field_10;
    void *field_14;
};

void fn_800711A8(struct fn_800711A8_Arg0 *arg0) {
    struct fn_800711A8_Entry *entry;
    s32 offset;
    s32 i;

    offset = 0;
    i = 0;
    while (i < arg0->count) {
        entry = *(struct fn_800711A8_Entry **)((u8 *)arg0->entries + offset);
        if (arg0->field_14 == 0 && entry != 0) {
            void *p = entry->field_24;
            if (p != 0) {
                lbl_801A6D08(p);
            }
        }
        offset += 8;
        i += 1;
    }
    if (arg0->field_14 != 0) {
        lbl_801A6D08(arg0->field_14);
    }
    if (!(arg0->field_10 & 1)) {
        lbl_801A6D08(arg0);
    }
}
