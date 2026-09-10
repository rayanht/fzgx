#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __AIRegs[8] : FZGX_ADDR___AIRegs;

void AISetStreamVolLeft(u8 volume) { __AIRegs[1] = (__AIRegs[1] & ~0xFF) | (volume & 0xFF); }
