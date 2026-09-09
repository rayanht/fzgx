#ifndef DOLPHIN_EXI_EXIPRIV_H
#define DOLPHIN_EXI_EXIPRIV_H
#include <dolphin/exi.h>
#include <dolphin/os.h>

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback tcCallback;
    EXICallback extCallback;
    vu32 state;
    int immLen;
    u8 *immBuf;
    u32 dev;
    u32 id;
    s32 idTime;
    int items;
    struct {
        u32 dev;
        EXICallback callback;
    } queue[3];
} EXIControl;
#endif
