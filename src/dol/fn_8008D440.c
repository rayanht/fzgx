#include "types.h"

typedef u32 (*fn_8008D440_Fn0)(void);
struct fn_8008D440_gDBCommTable {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x20];
};

extern struct fn_8008D440_gDBCommTable gDBCommTable[];
extern u8 TRK_Use_BBA[];

void fn_8008D440(void) {
    if (TRK_Use_BBA[0] == 0 && gDBCommTable[0].unk_4 != 0) {
        ((fn_8008D440_Fn0)gDBCommTable[0].unk_4)();
    }
}
