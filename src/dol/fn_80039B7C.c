#include <types.h>
#include <dolphin/types.h>
#pragma scheduling off

extern u16 *__cpReg;

static inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;
    ctrH0 = (*(vu16 *)((vu16 *)(__cpReg) + (regAddrH)));
    do {
        ctrH1 = ctrH0;
        ctrL = (*(vu16 *)((vu16 *)(__cpReg) + (regAddrL)));
        ctrH0 = (*(vu16 *)((vu16 *)(__cpReg) + (regAddrH)));
    } while (ctrH0 != ctrH1);
    return (ctrH0 << 0x10) | ctrL;
}

void fn_80039B7C(u32 *xf_wait_in, u32 *xf_wait_out, u32 *ras_busy, u32 *clocks) {
    *ras_busy = __GXReadCPCounterU32(32, 33);
    *clocks = __GXReadCPCounterU32(34, 35);
    *xf_wait_in = __GXReadCPCounterU32(36, 37);
    *xf_wait_out = __GXReadCPCounterU32(38, 39);
}
