#include <types.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

void AISetStreamPlayState(u32 state);

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

void __AI_set_stream_sample_rate(u32 rate) {
    s32 oldInts;
    s32 state;
    u8 left;
    u8 right;
    s32 temp_r26;
    if (rate == AIGetStreamSampleRate()) {
        return;
    }
    state = AIGetStreamPlayState();
    left = AIGetStreamVolLeft();
    right = AIGetStreamVolRight();
    AISetStreamVolRight(0);
    AISetStreamVolLeft(0);
    temp_r26 = __AIRegs[0] & 0x40;
    __AIRegs[0] &= ~0x40;
    oldInts = OSDisableInterrupts();
    fn_8001E600();
    __AIRegs[0] |= temp_r26;
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
    __AIRegs[0] = (__AIRegs[0] & ~2) | (rate * 2);
    OSRestoreInterrupts(oldInts);
    AISetStreamPlayState(state);
    AISetStreamVolLeft(left);
    AISetStreamVolRight(right);
}
