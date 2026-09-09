#include "types.h"

extern s32 __CARDSync(u32);
extern s32 CARDMountAsync(u32, void *, void *, void *);
extern void __CARDSyncCallback(void);

s32 fn_8002DFE0(u32 arg0, u32 arg1, u32 arg2) {
    s32 status;

    status = CARDMountAsync(arg0, (void *)arg1, (void *)arg2, (void *)__CARDSyncCallback);
    if (status < 0) {
        return status;
    }
    status = __CARDSync(arg0);
    return status;
}
