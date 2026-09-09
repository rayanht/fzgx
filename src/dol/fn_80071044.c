#include "types.h"

extern u32 lbl_801A6D0C;
extern u8 lbl_8015AB70[80];
extern char lbl_8015ABC0[10];

extern void fn_8007174C(void *, char *);
extern void DCInvalidateRange(void *, u32);
extern u32 ARGetDMAStatus(void);
extern void ARStartDMA(u32, void *, u32, u32);
extern void fn_80078DA8(void *, void *, u32);

void *fn_80071044(u32 arg0, u32 size, u32 arg2) {
    s32 rounded_size;
    void *buffer;
    void *data;

    rounded_size = (size + 0x1f) & ~0x1f;
    buffer = ((void *(*)(u32))lbl_801A6D0C)(rounded_size + 0x20);
    if (buffer == 0) {
        fn_8007174C(lbl_8015AB70, lbl_8015ABC0);
    }
    data = (u8 *)buffer + 0x20;
    DCInvalidateRange(data, rounded_size);
    while (ARGetDMAStatus() != 0) {
    }
    ARStartDMA(1, data, arg0, size);
    while (ARGetDMAStatus() != 0) {
    }
    fn_80078DA8(buffer, data, arg2);
    return buffer;
}
