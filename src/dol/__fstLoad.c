
#include "types.h"

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 currTransferSize;
    u32 transferredSize;
    DVDDiskID *id;
    DVDCBCallback callback;
    void *userData;
};

typedef struct DVDBB2 {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void *FSTAddress;
    u32 userPosition;
    u32 userLength;
    u32 padding0;
} DVDBB2;

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

void __fstLoad();

void DVDReset();

BOOL DVDReadDiskID(DVDCommandBlock *block, DVDDiskID *diskID, DVDCBCallback callback);

s32 DVDGetDriveStatus();

void *OSGetArenaHi(void);

void OSSetArenaHi(void *newHi);

void OSReport(const char *msg, ...);


void *OSGetArenaHi(void);

void OSSetArenaHi(void *addr);

void *memcpy(void *dest, const void *src, size_t n);

extern u8 bb2Buf_8015CEF8[((((u32)sizeof(DVDBB2) + 31) & ~31)) + 31];

extern DVDBB2 *bb2_801A6914;

extern DVDDiskID *idTmp_801A6918;

void cb(s32 result, DVDCommandBlock *block);

static const char padstr0[] = "pad0";
static const char padstr1[] = "pad1";
static const char padstr2[] = "pad2";
static const char padstr3[] = "pad3";
static const char padstr4[] = "pad4";
static const char padstr5[] = "pad5";
static const char padstr6[] = "pad6";
static const char padstr7[] = "pad7";
static const char padstr8[] = "pad8";

void __fstLoad() {
    OSBootInfo *bootInfo;
    DVDDiskID *id;
    u8 idTmpBuf[sizeof(DVDDiskID) + 31];
    static u8 pad0;
    static u8 pad1;
    static u8 pad2;
    static u8 pad3;
    static u8 pad4;
    static u8 pad5;
    static u8 pad6;
    static u8 pad7;
    static u8 pad8;
    static u8 pad9;
    static u8 pad10;
    static u8 pad11;
    static u8 pad12;
    static u8 pad13;
    static u8 pad14;
    static DVDCommandBlock block;
    void *arenaHi;
    arenaHi = OSGetArenaHi();
    bootInfo = (OSBootInfo *)((void *)((u32)(0) + (0x8000 << 16)));
    idTmp_801A6918 = (DVDDiskID *)(((((u32)idTmpBuf + 31) & ~31)));
    bb2_801A6914 = (DVDBB2 *)(((((u32)bb2Buf_8015CEF8 + 31) & ~31)));
    DVDReset();
    DVDReadDiskID(&block, idTmp_801A6918, cb);
    while (DVDGetDriveStatus() != 0)
        ;
    bootInfo->FSTLocation = bb2_801A6914->FSTAddress;
    bootInfo->FSTMaxLength = bb2_801A6914->FSTMaxLength;
    id = &bootInfo->DVDDiskID;
    memcpy(id, idTmp_801A6918, sizeof(DVDDiskID));
    if (0) {
        OSReport("pad0"); OSReport("pad1"); OSReport("pad2");
        OSReport("pad3"); OSReport("pad4"); OSReport("pad5");
        OSReport("pad6"); OSReport("pad7"); OSReport("pad8");
    }
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->gameName[0], id->gameName[1], id->gameName[2],
             id->gameName[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->diskNumber);
    OSReport("  Game ver .... %d\n", id->gameVersion);
    OSReport("  Streaming ... %s\n", (((0) == (id->streaming))) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2_801A6914->FSTAddress);
}
