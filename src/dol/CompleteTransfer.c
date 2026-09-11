#include <dolphin/si/SIPriv.h>
#include <dolphin/os.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

struct SIBiosData {
    unsigned char padding_0[68];
    SIControl Si;
    u32 Type[4];
};

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern OSTime TypeTime[4];

extern OSTime lbl_8015CB50[4];

extern struct SIBiosData lbl_80123B50;

static inline void SIClearTCInterrupt() {
    u32 reg;
    reg = __SIRegs[13];
    reg |= 0x80000000;
    reg &= ~0x00000001;
    __SIRegs[13] = reg;
}

u32 CompleteTransfer() {
    u32 *inputBytesField;

    struct SIBiosData *data = &lbl_80123B50;

    u32 sr;
    u32 i;
    u32 rLen;
    u8 *input;
    sr = __SIRegs[14];
    SIClearTCInterrupt();
    if ((data->Si).chan != -1) {
        lbl_8015CB50[(data->Si).chan] = __OSGetSystemTime();
        input = (data->Si).input;
        inputBytesField = (u32 *)((u8 *)data + (u32) & ((struct SIBiosData *)0)->Si.inputBytes);
        rLen = (*inputBytesField) / 4;
        for (i = 0; i < rLen; i++) {
            *(u32 *)input = __SIRegs[32 + i];
            input += 4;
        }
        rLen = (*inputBytesField) & 3;
        if (rLen) {
            u32 temp = __SIRegs[32 + i];
            for (i = 0; i < rLen; i++) {
                *input++ = (u8)((temp >> ((3 - i) * 8)) & 0xff);
            }
        }
        if (__SIRegs[13] & 0x20000000) {
            sr >>= 8 * (3 - (data->Si).chan);
            sr &= 0xf;
            if ((sr & 0x0008) && !((data->Type)[(data->Si).chan] & 0x0080)) {
                (data->Type)[(data->Si).chan] = 0x0008;
            }
            if (sr == 0) {
                sr = 0x0004;
            }
        } else {
            TypeTime[(data->Si).chan] = __OSGetSystemTime();
            sr = 0;
        }
        (data->Si).chan = -1;
    }
    return sr;
}
