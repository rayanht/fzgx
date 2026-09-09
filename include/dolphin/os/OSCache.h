#ifndef DOLPHIN_OS_OSCACHE_H
#define DOLPHIN_OS_OSCACHE_H
#include <dolphin/types.h>

void DCInvalidateRange(void* addr, u32 nBytes);
void DCFlushRange(void* addr, u32 nBytes);
void DCFlushRangeNoSync(void* addr, u32 nBytes);
void ICInvalidateRange(void* addr, u32 nBytes);
void LCLoadBlocks(void* dest, void* src, u32 nBlocks);
#endif
