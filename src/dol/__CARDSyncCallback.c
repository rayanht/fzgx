#include "types.h"

extern u32 OSWakeupThread(u32);
extern u32 lbl_80177960[];

void __CARDSyncCallback(u32 arg0) {
    s32 v0;
    v0 = (arg0 * 272);
    OSWakeupThread((u32)((u8 *)((u8 *)&lbl_80177960 + v0) + 140));
}
