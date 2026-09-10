#include "types.h"

extern s32 fn_800894FC(void);
extern void TRKGetBuffer(void);
extern void fn_80088764(void *, s32);
extern u32 lbl_801A5098[6];
extern void TRKPostEvent(void *);

struct TRKGetInput_Buffer {
    u32 unk_0;
    u32 unk_4;
    s32 unk_8;
};

void TRKGetInput(void) {
    struct TRKGetInput_Buffer buffer;
    s32 result;

    result = fn_800894FC();
    if (result != -1) {
        TRKGetBuffer();
        fn_80088764(&buffer, 2);
        lbl_801A5098[0] = -1;
        buffer.unk_8 = result;
        TRKPostEvent(&buffer);
    }
}
