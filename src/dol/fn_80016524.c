#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDBuffer {
    void *addr;
    u32 length;
    u32 offset;
} DVDBuffer;

typedef struct DVDCommand {
    s32 cmd;
    void *addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);

void OSCreateAlarm(OSAlarm *alarm);

DVDDiskID *fn_80019C48();

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

extern BOOL lbl_801A6468;

// Hardware or OS state can change asynchronously.
extern volatile u32 WorkAroundType_801A687C; // fzgx-allow: S2 SDK asynchronous state

// Hardware or OS state can change asynchronously.
extern volatile OSTime lbl_801A6888; // fzgx-allow: S2 SDK asynchronous state

extern vu32 NextCommandNumber_801A689C;

void fn_80016394(void *addr, u32 length, u32 offset, DVDLowCallback callback);

void fn_800162A0(OSAlarm *alarm, OSContext *context);

static DVDCommand CommandList[3];

static unsigned char gap____bss_0_3c[4];

static OSAlarm AlarmForWA;

static unsigned char gap____bss_0_68[80];

static DVDBuffer Prev;

static DVDBuffer Curr;

#pragma section code_type ".fzgxpool"
static void layout____bss_0(void) {
// Hardware or OS state can change asynchronously.
    volatile unsigned char sink; // fzgx-allow: S2 SDK asynchronous state
    sink = *(unsigned char *)&CommandList;
    sink = *(unsigned char *)&gap____bss_0_3c;
    sink = *(unsigned char *)&AlarmForWA;
    sink = *(unsigned char *)&gap____bss_0_68;
    sink = *(unsigned char *)&Prev;
    sink = *(unsigned char *)&Curr;
}
#pragma section code_type ".text"

static inline BOOL HitCache(DVDBuffer *cur, DVDBuffer *prev) {
    u32 uVar1 = (prev->offset + prev->length - 1) >> 15;
    u32 uVar2 = (cur->offset >> 15);
    u32 iVar3 = (fn_80019C48()->streaming ? 1 : 0) ? 5 : 15;
    if ((uVar2 > uVar1 - 2) || (uVar2 < uVar1 + iVar3 + 3)) {
        return 1;
    }
    return 0;
}

static inline void DoJustRead(void *addr, u32 length, u32 offset, DVDLowCallback callback) {
    CommandList[0].cmd = -1;
    NextCommandNumber_801A689C = 0;
    fn_80016394(addr, length, offset, callback);
}

void fn_800164A4(void *addr, u32 length, u32 offset, DVDLowCallback callback);

static inline void WaitBeforeRead(void *addr, u32 length, u32 offset, DVDLowCallback callback,
                                  OSTime timeout) {
    CommandList[0].cmd = 1;
    CommandList[0].addr = addr;
    CommandList[0].length = length;
    CommandList[0].offset = offset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = -1;
    NextCommandNumber_801A689C = 0;
    OSCreateAlarm(&AlarmForWA);
    OSSetAlarm(&AlarmForWA, timeout, fn_800162A0);
}

BOOL fn_80016524(void *addr, u32 length, u32 offset, DVDLowCallback callback) {
    OSTime diff;
    u32 prev;
    __DIRegs[6] = length;
    Curr.addr = addr;
    Curr.length = length;
    Curr.offset = offset;
    if (WorkAroundType_801A687C == 0) {
        DoJustRead(addr, length, offset, callback);
    } else if (WorkAroundType_801A687C == 1) {
        if (lbl_801A6468) {
            fn_800164A4(addr, length, offset, callback);
        } else {
            if (!HitCache(&Curr, &Prev)) {
                DoJustRead(addr, length, offset, callback);
            } else {
                prev = (Prev.offset + Prev.length - 1) >> 15;
                if (prev == Curr.offset >> 15 || prev + 1 == Curr.offset >> 15) {
                    diff = __OSGetSystemTime() - lbl_801A6888;
                    if (((5) * (((u32)__OSBusClock / 4) / 1000)) < diff) {
                        DoJustRead(addr, length, offset, callback);
                    } else {
                        WaitBeforeRead(addr, length, offset, callback,
                                       ((5) * (((u32)__OSBusClock / 4) / 1000)) - diff +
                                           (((500) * (((u32)__OSBusClock / 4) / 125000)) / 8));
                    }
                } else {
                    fn_800164A4(addr, length, offset, callback);
                }
            }
        }
    }
    return 1;
}
