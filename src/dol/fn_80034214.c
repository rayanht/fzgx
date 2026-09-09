#include "types.h"

 // Hardware register pointer; accesses must not be cached.
extern volatile u16 *__peReg;

void fn_80034214(u8 value) {
    __peReg[1] = (u16)((__peReg[1] & ~0x10) | ((u32)value << 4));
}
