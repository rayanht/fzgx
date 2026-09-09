#include "types.h"

typedef u32 (*ReserveEXI2Port_Fn0)(void);
struct ReserveEXI2Port_gDBCommTable {
    u8 pad_0[0x24];
    u32 unk_24;
};

extern struct ReserveEXI2Port_gDBCommTable gDBCommTable[];

void ReserveEXI2Port(void) {
    ((ReserveEXI2Port_Fn0)gDBCommTable[0].unk_24)();
}
