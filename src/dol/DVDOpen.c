#include <types.h>
#include <dolphin/dvd.h>

typedef struct DVDFileInfo DVDFileInfo;

typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);

struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDCallback callback;
};

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

void OSReport(const char *msg, ...);

s32 fn_80016DF8(const char *pathPtr);

BOOL DVDGetCurrentDir(char *path, u32 maxlen);

extern FSTEntry *FstStart_801A68A4;

BOOL DVDOpen(const char *fileName, DVDFileInfo *fileInfo) {
    s32 entry;
    char currentDir[128];
    entry = fn_80016DF8(fileName);
    if (0 > entry) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n", fileName, currentDir);
        return 0;
    }
    if ((((FstStart_801A68A4[entry].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1)) {
        return 0;
    }
    fileInfo->startAddr = (FstStart_801A68A4[entry].parentOrPosition);
    fileInfo->length = (FstStart_801A68A4[entry].nextEntryOrLength);
    fileInfo->callback = (DVDCallback)0;
    fileInfo->cb.state = 0;
    return 1;
}
