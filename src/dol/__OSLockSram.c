#include "types.h"

struct OSLockSram_Scb_8015BFC0 {
    u8 pad_0[0x44];
    u32 unk_44;
    s32 unk_48;
};

extern struct OSLockSram_Scb_8015BFC0 Scb_8015BFC0;
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);

struct OSLockSram_Scb_8015BFC0 *__OSLockSram(void) {
    struct OSLockSram_Scb_8015BFC0 *p_Scb_8015BFC0;
    u32 v0;

    p_Scb_8015BFC0 = (struct OSLockSram_Scb_8015BFC0 *)&Scb_8015BFC0;
    v0 = OSDisableInterrupts();
    {
        s32 *p_unk_48;

        p_unk_48 = &p_Scb_8015BFC0->unk_48;
        if (*p_unk_48 != 0) {
            OSRestoreInterrupts(v0);
            p_Scb_8015BFC0 = 0;
        } else {
            p_Scb_8015BFC0->unk_44 = v0;
            *p_unk_48 = 1;
        }
    }
    return p_Scb_8015BFC0;
}
