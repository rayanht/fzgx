#include "types.h"

extern void fn_80071C04(void *, u32);

struct fn_800713E0_Entry {
    u8 pad_0[0x18];
    u16 count;
};

struct fn_800713E0_Arg0 {
    s32 count;
    u8 pad_4[0x4];
    struct fn_800713E0_Entry **entries;
};

void fn_800713E0(struct fn_800713E0_Arg0 *arg0, u32 arg1) {
    u8 *child;
    s32 offset;
    s32 i;
    s32 j;
    struct fn_800713E0_Entry *entry;

    i = 0;
    offset = 0;
    while (i < arg0->count) {
        entry = *(struct fn_800713E0_Entry **)((u8 *)arg0->entries + offset);
        if (entry != 0) {
            child = (u8 *)entry + 0x40;
            j = 0;
            while (j < entry->count) {
                fn_80071C04(child, arg1);
                child += 0x20;
                j++;
            }
        }
        offset += 8;
        i++;
    }
}
