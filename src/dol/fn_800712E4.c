#include "types.h"

extern void _savegpr_23(void);
extern void _restgpr_23(void);
extern void fn_800718BC(void *child, u32 offset, void *arg1);

struct fn_800712E4_Tbl {
    u16 key;
    u16 value;
};

struct fn_800712E4_Child {
    u32 flags;
    u16 key;
    u16 pad_06;
    u32 field_08;
    u8 pad_0C[0x14];
};

struct fn_800712E4_Entry {
    u8 pad_00[0x18];
    u16 count;
    u8 pad_1A[0xA];
    u32 field_24;
};

struct fn_800712E4_Arg0 {
    s32 count;
    u8 pad_04[4];
    struct fn_800712E4_Entry **entries;
};

struct fn_800712E4_Arg1 {
    u8 pad_00[4];
    u32 field_04;
};

void fn_800712E4(struct fn_800712E4_Arg0 *arg0, struct fn_800712E4_Arg1 *arg1,
                 struct fn_800712E4_Tbl *arg2) {
    struct fn_800712E4_Child *child;
    s32 inner;
    s32 offset;
    s32 i;
    s32 j;
    struct fn_800712E4_Entry *entry;
    struct fn_800712E4_Tbl *p;
    s32 idx;
    u16 v;

    i = 0;
    offset = 0;
    while (i < arg0->count) {
        entry = *(struct fn_800712E4_Entry **)((u8 *)arg0->entries + offset);
        if (entry != 0) {
            child = (struct fn_800712E4_Child *)((u8 *)entry + 0x40);
            j = 0;
            inner = 0;
            while (j < entry->count) {
                if (child->flags & 0x200000) {
                    v = child->key;
                    p = arg2;
                    idx = 0;
                    while (p->key != 0xFFFF) {
                        if (v == p->key) {
                            v = arg2[idx].value;
                            break;
                        }
                        p++;
                        idx++;
                    }
                    child->field_08 = entry->field_24 + inner;
                    fn_800718BC(child, arg1->field_04 + (v << 4), arg1);
                }
                child++;
                inner += 0x20;
                j++;
            }
        }
        offset += 8;
        i++;
    }
}
