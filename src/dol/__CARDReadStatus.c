#include "types.h"

extern s32 EXISelect(s32 chan, s32 dev, s32 freq);
extern s32 EXIImm(s32 chan, void *buf, s32 len, s32 type, void *callback);
extern s32 EXISync(s32 chan);
extern s32 EXIDeselect(s32 chan);

s32 __CARDReadStatus(s32 chan, void *status) {
    u32 command;
    s32 failed;

    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }

    command = 0x83000000;
    failed = !EXIImm(chan, &command, 2, 1, 0);
    failed |= !EXISync(chan);
    failed |= !EXIImm(chan, status, 1, 0, 0);
    failed |= !EXISync(chan);
    failed |= !EXIDeselect(chan);

    if (failed) {
        return -3;
    }
    return 0;
}
