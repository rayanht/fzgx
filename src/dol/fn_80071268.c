#include "types.h"

extern void _savegpr_27(void);
extern void *fn_80083970(void *arg0, u32 arg1);
extern void _restgpr_27(void);

struct fn_80071268_Entry {
    void *unk_0;
    void *unk_4;
};

struct fn_80071268_Arg0 {
    s32 count;
    u8 pad_4[4];
    struct fn_80071268_Entry *entries;
};

void *fn_80071268(struct fn_80071268_Arg0 *arg0, u32 arg1) {
    u32 offset;
    s32 i;
    struct fn_80071268_Entry *entry;

    i = 0;
    offset = 0;
    while (i < arg0->count) {
        entry = (struct fn_80071268_Entry *)((u8 *)arg0->entries + offset);
        if (fn_80083970(entry->unk_4, arg1) != 0) {
            return entry->unk_0;
        }
        offset += 8;
        i += 1;
    }
    return 0;
}
