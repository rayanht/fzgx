#include "types.h"

typedef u32 (*fn_8008D3D4_Fn0)(u32, u32);
struct fn_8008D3D4_gDBCommTable {
    u8 pad_0[0x10];
    u32 unk_10;
};

extern struct fn_8008D3D4_gDBCommTable gDBCommTable[];

s32 fn_8008D3D4(u32 arg0, u32 arg1) {
    u32 t0;
    t0 = ((fn_8008D3D4_Fn0)gDBCommTable[0].unk_10)(arg0, arg1);
    return ((s32)((-t0) | t0) >> 31);
}
