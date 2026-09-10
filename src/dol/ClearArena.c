#include "sdk_addresses.h"

#pragma peephole off
#include "types.h"

void *OSGetArenaHi(void);

void *OSGetArenaLo(void);

void *OSGetArenaHi(void);

void *OSGetArenaLo(void);

extern void *__OSSavedRegionStart;

extern void *__OSSavedRegionEnd;

extern u32 BOOT_REGION_START : FZGX_ADDR_BOOT_REGION_START;

extern u32 BOOT_REGION_END : FZGX_ADDR_BOOT_REGION_END;

void ClearArena(void) {
    if ((u32)(OSGetResetCode() + 0x80000000) != 0U) {
        __OSSavedRegionStart = 0U;
        __OSSavedRegionEnd = 0U;
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }
    __OSSavedRegionStart = (void *)BOOT_REGION_START;
    __OSSavedRegionEnd = (void *)BOOT_REGION_END;
    if (BOOT_REGION_START == 0U) {
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }
    if ((u32)OSGetArenaLo() < (u32)__OSSavedRegionStart) {
        if ((u32)OSGetArenaHi() <= (u32)__OSSavedRegionStart) {
            memset((u32)OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
            return;
        }
        memset(OSGetArenaLo(), 0U, (u32)__OSSavedRegionStart - (u32)OSGetArenaLo());
        if ((u32)OSGetArenaHi() > (u32)__OSSavedRegionEnd) {
            memset((u32)__OSSavedRegionEnd, 0, (u32)OSGetArenaHi() - (u32)__OSSavedRegionEnd);
        }
    }
}
