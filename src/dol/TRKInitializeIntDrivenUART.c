#include "types.h"

typedef u32 (*TRKInitializeIntDrivenUART_Fn0)(u32, u32, u32, u32);
typedef u32 (*TRKInitializeIntDrivenUART_Fn1)(void);
struct TRKInitializeIntDrivenUART_gDBCommTable {
    u32 unk_0;
    u8 pad_4[0x14];
    u32 unk_18;
};

extern struct TRKInitializeIntDrivenUART_gDBCommTable gDBCommTable[];
extern void TRKEXICallBack(void);

s32 TRKInitializeIntDrivenUART(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    ((TRKInitializeIntDrivenUART_Fn0)gDBCommTable[0].unk_0)(arg3, (u32)TRKEXICallBack, arg2, arg3);
    ((TRKInitializeIntDrivenUART_Fn1)gDBCommTable[0].unk_18)();
    return 0;
}
