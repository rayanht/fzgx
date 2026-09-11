#include "types.h"

typedef struct TRKExceptionStatus {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
} TRKExceptionStatus;

extern TRKExceptionStatus gTRKExceptionStatus;
extern u8 gTRKCPUState[];

extern u32 fn_8008D154(u32);
extern u32 fn_8008C87C(const void *, u32, u32);
extern u32 fn_8008B0E0(void);
extern void fn_8008AFF0(u32, u32);
extern void fn_8008B0F0(u32, u32, u32, u32, u32);

s32 fn_8008C730(u32 arg0, u32 arg1, u32 *arg2, u32 arg3, s32 arg4) {
    TRKExceptionStatus *status;
    TRKExceptionStatus save;
    u32 v0;
    u32 v1;

    status = &gTRKExceptionStatus;
    save = *status;
    status->unkD = 0;

    v0 = fn_8008D154(arg1);
    v1 = fn_8008C87C((const void *)v0, *arg2, arg4 == 0);
    if (v1 != 0) {
        *arg2 = 0;
    } else {
        u32 v2;
        u32 f;
        v2 = fn_8008B0E0();
        f = v2 | (*(u32 *)(gTRKCPUState + 0x1f8) & 0x10);
        if (arg4 != 0) {
            fn_8008B0F0(arg0, v0, *arg2, v2, f);
        } else {
            fn_8008B0F0(v0, arg0, *arg2, f, v2);
            fn_8008AFF0(v0, *arg2);
            if (arg1 != v0) {
                fn_8008AFF0(arg1, *arg2);
            }
        }
    }
    if (status->unkD != 0) {
        *arg2 = 0;
        v1 = 0x702;
    }
    gTRKExceptionStatus = save;
    return v1;
}
