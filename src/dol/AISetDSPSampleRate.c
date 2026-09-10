#include <types.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

u32 AIGetDSPSampleRate();

u32 AIGetStreamPlayState();

u32 AIGetStreamSampleRate();

void AISetStreamVolLeft(u8 vol);

void AISetStreamVolRight(u8 vol);

u8 AIGetStreamVolLeft();

u8 AIGetStreamVolRight();

vu32 __AIRegs[8] : FZGX_ADDR___AIRegs;

void fn_8001E600(void);

static inline u32 AIGetStreamPlayState() { return __AIRegs[0] & 1; }

void AISetStreamVolLeft(u8 volume);

void AISetStreamVolRight(u8 volume);

void AISetDSPSampleRate(u32 rate) {
    u32 state;
    s32 oldInts;
    u8 left;
    u8 right;
    u32 sampleRate;
    if (rate == AIGetDSPSampleRate()) {
        return;
    }
    __AIRegs[0] &= ~0x40;
    if (rate == 0) {
        left = AIGetStreamVolLeft();
        right = AIGetStreamVolRight();
        state = AIGetStreamPlayState();
        sampleRate = AIGetStreamSampleRate();
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        oldInts = OSDisableInterrupts();
        fn_8001E600();
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & ~2) | (sampleRate * 2);
        __AIRegs[0] = (__AIRegs[0] & ~1) | state;
        __AIRegs[0] |= 0x40;
        OSRestoreInterrupts(oldInts);
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}
