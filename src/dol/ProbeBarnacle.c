#include <dolphin/exi/EXIPriv.h>

BOOL ProbeBarnacle(s32 chan, u32 dev, u32 *revision) {
    BOOL err;
    u32 cmd;
    if (chan != 2 && dev == 0 && !EXIAttach(chan, ((void *)0))) {
        return 0;
    }
    err = !EXILock(chan, dev, ((void *)0));
    if (!err) {
        err = !EXISelect(chan, dev, 0);
        if (!err) {
            cmd = 0x20011300;
            err = 0;
            err |= !EXIImm(chan, &cmd, 4, 1, ((void *)0));
            err |= !EXISync(chan);
            err |= !EXIImm(chan, revision, 4, 0, ((void *)0));
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (chan != 2 && dev == 0) {
        EXIDetach(chan);
    }
    if (err) {
        return 0;
    }
    return (*revision != 0xFFFFFFFF) ? 1 : 0;
}
