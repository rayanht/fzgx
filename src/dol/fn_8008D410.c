#include "types.h"

typedef u32 (*fn_8008D410_Fn0)(void);
struct fn_8008D410_gDBCommTable {
    u8 pad_0[0xC];
    u32 unk_C;
};

extern struct fn_8008D410_gDBCommTable gDBCommTable[];

void fn_8008D410(void) {
    ((fn_8008D410_Fn0)gDBCommTable[0].unk_C)();
}
