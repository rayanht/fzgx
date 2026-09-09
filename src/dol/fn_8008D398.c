#include "types.h"

typedef u32 (*fn_8008D398_Fn0)(u32, u32);
struct fn_8008D398_gDBCommTable {
    u8 pad_0[0x14];
    u32 unk_14;
};

extern struct fn_8008D398_gDBCommTable gDBCommTable[];

s32 fn_8008D398(u32 arg0, u32 arg1) {
    u32 t0;
    t0 = ((fn_8008D398_Fn0)gDBCommTable[0].unk_14)(arg0, arg1);
    return ((s32)((-t0) | t0) >> 31);
}
