#include "types.h"

extern u32 __CARDSync(u32);
extern s32 CARDCreateAsync(u32, void *, void *, void *, void *);
extern void __CARDSyncCallback(void);

s32 CARDCreate(u32 arg0, void *arg1, void *arg2, void *arg3) {
    s32 result;

    result = CARDCreateAsync(arg0, arg1, arg2, arg3, (void *)__CARDSyncCallback);
    if (result < 0) {
        return result;
    }
    return __CARDSync(arg0);
}
