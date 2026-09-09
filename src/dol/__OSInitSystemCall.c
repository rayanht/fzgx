#include "sdk_addresses.h"
#include <dolphin/os.h>
#pragma peephole off

void __OSSystemCallVectorStart();

void __OSSystemCallVectorEnd();

void __OSInitSystemCall() {
    void *addr = ((void *)FZGX_ADDR___OSSystemCallVectorAddress);
    memcpy(addr, __OSSystemCallVectorStart,
           (size_t)__OSSystemCallVectorEnd - (size_t)__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
