#include "types.h"

extern s32 __CARDSync(u32);
extern u32 CARDCheckExAsync(u32, void *, u32);
extern void __CARDSyncCallback(void);

s32 CARDCheck(u32 arg0) {
    u32 loc_C;
    s32 result;
    /* frame */
    result = CARDCheckExAsync(arg0, (void *)&loc_C, (u32)__CARDSyncCallback);
    if (result >= 0) {
        if ((u32)&loc_C == 0) {
            return result;
        }
        result = __CARDSync(arg0);
    }
    return result;
}
