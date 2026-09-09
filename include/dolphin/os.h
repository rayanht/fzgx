#ifndef DOLPHIN_OS_H
#define DOLPHIN_OS_H

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSModule.h>
#include <dolphin/os/OSReset.h>


void OSClearContext(register OSContext *context);
void OSClearStack(u8 val);
void OSDumpContext(OSContext *context);
u32 OSGetResetCode(void);
u16 OSGetWirelessID(s32 channel);
BOOL OSIsThreadTerminated(OSThread *thread);
void OSPanic(const char *file, int line, const char *msg, ...);
void OSSetProgressiveMode(u32 mode);
void OSSetWirelessID(s32 channel, u16 id);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);
BOOL OSUnlink(OSModuleInfo *oldModule);
void __OSCacheInit();
void __OSContextInit(void);
OSTime __OSGetSystemTime(void);
void __OSInitAudioSystem(void);
void __OSInitMemoryProtection();
void __OSInitSram(void);
void __OSInitSystemCall();
OSInterruptMask __OSMaskInterrupts(OSInterruptMask global);
void __OSModuleInit(void);
void __OSStopAudioSystem(void);
OSTime __OSTimeToSystemTime(OSTime time);
OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask global);
#endif
