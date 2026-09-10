#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef struct OSBootInfo {
    DVDDiskID DVDDiskID;
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType;
    void *arenaLo;
    void *arenaHi;
    void *FSTLocation;
    u32 FSTMaxLength;
} OSBootInfo;

void OSRegisterVersion(const char *id);

void OSReport(const char *msg, ...);

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);

void OSInitThreadQueue(OSThreadQueue *queue);

extern OSThreadQueue __DVDThreadQueue;

void __DVDInitWA();

void __DVDInterruptHandler(__OSInterrupt interrupt, OSContext *context);

void __DVDClearWaitingQueue();

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

extern const char *__DVDVersion;

extern DVDDiskID *IDShouldBe_801A68C4;

extern OSBootInfo *bootInfo_801A68C8;

// Hardware or OS state can change asynchronously.
extern volatile BOOL FirstTimeInBootrom_801A68FC; // fzgx-allow: S2 SDK asynchronous state

extern BOOL DVDInitialized_801A6900;

void DVDInit() {
    if (DVDInitialized_801A6900) {
        return;
    }
    OSRegisterVersion(__DVDVersion);
    DVDInitialized_801A6900 = 1;
    __DVDFSInit();
    __DVDClearWaitingQueue();
    __DVDInitWA();
    bootInfo_801A68C8 = (OSBootInfo *)((void *)((u32)(0x0000) + (0x8000 << 16)));
    IDShouldBe_801A68C4 = &(bootInfo_801A68C8->DVDDiskID);
    __OSSetInterruptHandler(21, __DVDInterruptHandler);
    __OSUnmaskInterrupts(0x400);
    OSInitThreadQueue(&__DVDThreadQueue);
    __DIRegs[0] = 0x2a;
    __DIRegs[1] = 0;
    if (bootInfo_801A68C8->magic == 0xE5207C22) {
        OSReport("load fst\n");
        __fstLoad();
    } else if (bootInfo_801A68C8->magic != 0xD15EA5E) {
        FirstTimeInBootrom_801A68FC = 1;
    }
}
