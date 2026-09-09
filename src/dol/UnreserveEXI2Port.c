#include "types.h"

typedef u32 (*UnreserveEXI2Port_Fn0)(void);
struct UnreserveEXI2Port_gDBCommTable {
    u8 pad_0[0x20];
    u32 unk_20;
};

extern struct UnreserveEXI2Port_gDBCommTable gDBCommTable[];

void UnreserveEXI2Port(void) {
    ((UnreserveEXI2Port_Fn0)gDBCommTable[0].unk_20)();
}
