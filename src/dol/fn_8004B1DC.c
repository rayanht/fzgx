
#include "types.h"

typedef struct Stream {
    s8 used;
    s8 status;
    s8 substatus;
    u8 pad0[5];
    void *handle;
    u8 pad1[0x14];
    u32 flags20;
    u8 pad2[0x1C];
    u8 pad3;
    s8 f41;
    s8 f42;
    s8 f43;
    s8 f44;
    s8 f45;
    u8 pad4[0x16];
} Stream;

extern void fn_800547C8(void *);
extern s32 fn_80059B44(void);
extern s32 fn_80059AB4(void);
extern s32 fn_80058A40(s32 *value);
extern u8 lbl_8017D6FC[];
extern Stream lbl_8017D708[40];
extern void fn_8004A5F4(Stream *);
extern void *memset(void *, int, u32);

static inline void endStatus(Stream *arg0) {
    fn_80059B44();
    if (arg0->status == 2 && arg0->substatus == 1) {
        arg0->f44 = 1;
        if (arg0->f43 == 1) {
            arg0->f43 = 0;
        }
    } else {
        arg0->status = 1;
    }
    fn_80059AB4();
}

static inline void stopStream(Stream *arg0) {
    if (arg0->handle != NULL && arg0->f42 == 0) {
        fn_800547C8(arg0->handle);
    }
    fn_80059B44();
    arg0->status = 1;
    arg0->substatus = 0;
    arg0->flags20 = 0;
    fn_80059AB4();
    endStatus(arg0);
}

static inline void execServer(void) {
    s32 index;

    if (fn_80058A40((s32 *)lbl_8017D6FC) != 0) {
        for (index = 0; index < 40; index++) {
            if (lbl_8017D708[index].used == 1) {
                fn_8004A5F4(&lbl_8017D708[index]);
            }
        }
        *(s32 *)lbl_8017D6FC = 0;
    }
}

void fn_8004B1DC(Stream *arg0) {
    if (arg0 != NULL) {
        stopStream(arg0);
        do {
            execServer();
        } while (arg0->status != 1 || arg0->flags20 != 0);
        stopStream(arg0);
        do {
            execServer();
        } while (arg0->status != 1 || arg0->flags20 != 0);
        endStatus(arg0);
        fn_80059B44();
        if (arg0->f45 == 1) {
            arg0->f42 = 1;
        }
        arg0->f41 = 0;
        fn_80059AB4();
        for (;;) {
            if (arg0->f45 == 0) {
                break;
            }
            execServer();
        }
        arg0->used = 0;
        memset(arg0, 0, 0x5C);
    }
}
