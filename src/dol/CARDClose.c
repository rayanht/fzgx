#include "types.h"

struct CARDFileInfo {
    s32 chan;
};

extern s32 __CARDGetControlBlock(s32 chan, void *control);
extern s32 __CARDPutControlBlock(void *control, s32 result);

s32 CARDClose(struct CARDFileInfo *fileInfo) {
    void *control;
    s32 result;

    result = __CARDGetControlBlock(fileInfo->chan, &control);
    if (result < 0) {
        return result;
    }
    fileInfo->chan = -1;
    result = __CARDPutControlBlock(control, 0);
    return result;
}
