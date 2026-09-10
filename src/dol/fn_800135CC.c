#include "types.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/si.h"

extern u8 lbl_8015CC10[160];
extern u32 lbl_801A6828[2];
extern BOOL SITransfer(s32, void *, u32, void *, u32, SICallback, OSTime);
extern void fn_800134DC(void);
extern OSContext *fn_8000BE5C(void);
extern void OSClearContext(OSContext *);
extern void OSSetCurrentContext(OSContext *);
extern void __OSReschedule(void);

struct SITransferSlot {
    u8 pad0[0xC];
    u32 unk_C;
    u32 unk_10;
    void (*unk_14)(s32, u32);
    s32 unk_18;
    u8 pad1C[0x8];
    void (*unk_24)(s32);
};

void fn_800135CC(s32 chan, u32 type) {
    struct SITransferSlot *entry;

    entry = (struct SITransferSlot *)lbl_8015CC10 + chan;
    if ((s32)lbl_801A6828[0] != 0) {
        return;
    }
    if ((type & 0xFFFF0000) == 0x08000000) {
        if (SITransfer(chan, entry, entry->unk_C, (u8 *)entry + 3, entry->unk_10,
                       (SICallback)fn_800134DC, 0) != 0) {
            return;
        }
        entry->unk_18 = -2;
    } else {
        entry->unk_18 = -1;
    }
    if (entry->unk_24 != 0) {
        void (*cb)(s32) = entry->unk_24;
        entry->unk_24 = 0;
        cb(chan);
    }
    if (entry->unk_14 != 0) {
        OSContext *saved = fn_8000BE5C();
        void (*cb2)(s32, u32);

{
    OSContext context;
        OSClearContext(&context);
        OSSetCurrentContext(&context);
        cb2 = entry->unk_14;
        entry->unk_14 = 0;
        cb2(chan, entry->unk_18);
        OSClearContext(&context);
}
        OSSetCurrentContext(saved);
        __OSReschedule();
    }
}
