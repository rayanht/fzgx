#include "types.h"
#include "dolphin/os/OSAlarm.h"

typedef struct {
    u8 unk00;
    u8 pad01[0x0B];
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u8 pad24[0x0C];
    u32 unk30;
    u8 pad34[0x7C];
} Entry;

typedef struct {
    Entry *entries;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
} Slot;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 level);
extern s32 lbl_801A6584;
extern u32 lbl_801A6C44;
extern Slot *lbl_801A6C4C;
extern u32 fn_8000A050(void);
extern u32 fn_8003D588(void *, u32);
extern OSAlarm lbl_80178BF0;

void fn_8003E958(void) {
    u32 level;

    level = OSDisableInterrupts();
    if (lbl_801A6584 >= 0) {
        lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk10 = fn_8000A050();
        fn_8003D588(&lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584], 1);
    }
    OSCancelAlarm(&lbl_80178BF0);
    OSRestoreInterrupts(level);
}
