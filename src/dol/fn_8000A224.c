#include <dolphin/os.h>
#include <dolphin/dvd.h>
#pragma peephole off

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

extern OSBootInfo *BootInfo_801A6748;

u32 fn_8000A224() {
    if (BootInfo_801A6748 == ((void *)0) || BootInfo_801A6748->consoleType == 0) {
        return 0x10000002;
    }
    return BootInfo_801A6748->consoleType;
}
