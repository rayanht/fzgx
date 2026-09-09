#include "types.h"
#include "dol/globals.h"

extern u32 OSDisableInterrupts(void);
extern void EXISetExiCallback(s32 chan, void *callback);
extern void EXIDetach(s32 chan);
extern void fn_8000AF78(void *arg);
extern void OSRestoreInterrupts(u32 level);

void DoUnmount(s32 chan, void *callback) {
    Obj_80177960 *card;
    u32 level;

    card = (Obj_80177960 *)((u8 *)&lbl_80177960 + chan * 0x110);
    level = OSDisableInterrupts();
    if ((s32)card->unk_0 != 0) {
        EXISetExiCallback(chan, 0);
        EXIDetach(chan);
        fn_8000AF78((u8 *)card + 0xe0);
        card->unk_0 = 0;
        card->unk_4 = (u32)callback;
        card->unk_24 = 0;
    }
    OSRestoreInterrupts(level);
}
