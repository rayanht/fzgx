#include <dolphin/si/SIPriv.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/si.h>

extern u32 Type_80123BA8[4];

extern u32 lbl_801A6818;

static unsigned char Packet_8015CA10[128];

static unsigned char gap____bss_0_80[160];

static OSTime TypeTime[4];

static unsigned char gap____bss_0_140[32];

static SITypeAndStatusCallback TypeCallback[4][4];

static unsigned char gap____bss_0_1a0[80];

static u32 cmdFixDevice[4];

static void layout____bss_0(void) {
// Hardware or OS state can change asynchronously.
    volatile unsigned char sink; // fzgx-allow: S2 SDK asynchronous state
    sink = *(unsigned char *)&Packet_8015CA10;
    sink = *(unsigned char *)&gap____bss_0_80;
    sink = *(unsigned char *)&TypeTime;
    sink = *(unsigned char *)&gap____bss_0_140;
    sink = *(unsigned char *)&TypeCallback;
    sink = *(unsigned char *)&gap____bss_0_1a0;
    sink = *(unsigned char *)&cmdFixDevice;
}

static inline void CallTypeAndStatusCallback(s32 chan, u32 type) {
    SITypeAndStatusCallback callback;
    int i;
    for (i = 0; i < 4; ++i) {
        callback = TypeCallback[chan][i];
        if (callback) {
            TypeCallback[chan][i] = 0;
            callback(chan, type);
        }
    }
}

void GetTypeCallback(s32 chan, u32 error, OSContext *context) {

    u32 type;
    u32 chanBit;
    BOOL fix;
    u32 id;
    Type_80123BA8[chan] &= ~0x0080;
    Type_80123BA8[chan] |= error;
    TypeTime[chan] = __OSGetSystemTime();
    type = Type_80123BA8[chan];
    chanBit = 0x80000000 >> chan;
    fix = (BOOL)(lbl_801A6818 & chanBit);
    lbl_801A6818 &= ~chanBit;
    if ((error & (0x0001 | 0x0002 | 0x0008 | 0x0004)) || (type & 0x18000000u) != 0x08000000u ||
        !(type & 0x80000000) || (type & 0x04000000)) {
        OSSetWirelessID(chan, 0);
        CallTypeAndStatusCallback(chan, Type_80123BA8[chan]);
        return;
    }
    id = (u32)(OSGetWirelessID(chan) << 8);
    if (fix && (id & 0x00100000)) {
        cmdFixDevice[chan] = 0x4Eu << 24 | (id & (0x000f0000 | 0x00c0ff00)) | 0x00100000;
        Type_80123BA8[chan] = 0x0080;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type_80123BA8[chan], 3, GetTypeCallback, 0);
        return;
    }
    if (type & 0x00100000) {
        if ((id & (0x000f0000 | 0x00c0ff00)) != (type & (0x000f0000 | 0x00c0ff00))) {
            if (!(id & 0x00100000)) {
                id = type & (0x000f0000 | 0x00c0ff00);
                id |= 0x00100000;
                OSSetWirelessID(chan, (u16)((id >> 8) & 0xffff));
            }
            cmdFixDevice[chan] = 0x4E << 24 | id;
            Type_80123BA8[chan] = 0x0080;
            SITransfer(chan, &cmdFixDevice[chan], 3, &Type_80123BA8[chan], 3, GetTypeCallback, 0);
            return;
        }
    } else if (type & 0x40000000) {
        id = type & (0x000f0000 | 0x00c0ff00);
        id |= 0x00100000;
        OSSetWirelessID(chan, (u16)((id >> 8) & 0xffff));
        cmdFixDevice[chan] = 0x4E << 24 | id;
        Type_80123BA8[chan] = 0x0080;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type_80123BA8[chan], 3, GetTypeCallback, 0);
        return;
    } else {
        OSSetWirelessID(chan, 0);
    }
    CallTypeAndStatusCallback(chan, Type_80123BA8[chan]);
}
