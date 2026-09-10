#include "types.h"
#include "dolphin/os/OSContext.h"

extern u8 lbl_8015CC10[160];
extern u32 lbl_801A6828;

struct Fn800134DCEntry {
    u8 unk0[0x14];
    void (*callback)();
    s32 status;
    u8 unk1[8];
    void (*callback2)();
};

void fn_800134DC(u32 arg0, u32 arg1, void *arg2) {
    struct Fn800134DCEntry *entry;
    u32 unused[2];
    OSContext context;

    entry = (struct Fn800134DCEntry *)((u8 *)&lbl_8015CC10 + arg0 * 40);
    if ((s32)lbl_801A6828 == 0) {
        if ((arg1 & 0x8) != 0) {
            entry->status = -1;
        } else if ((arg1 & 0x7) != 0) {
            entry->status = -3;
        } else {
            entry->status = 0;
        }
        if (entry->callback2 != 0) {
            void (*callback2)() = entry->callback2;
            entry->callback2 = 0;
            callback2(arg0);
        }
        if (entry->callback != 0) {
            OSClearContext(&context);
            OSSetCurrentContext(&context);
            {
                void (*cb)(u32, s32) = entry->callback;
                entry->callback = 0;
                cb(arg0, entry->status);
            }
            OSClearContext(&context);
            OSSetCurrentContext(arg2);
        }
    }
}
