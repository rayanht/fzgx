#include "types.h"

typedef struct ARCEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} ARCEntry;

typedef struct ARCHandle {
    void *archiveStartAddr;
    void *FSTStart;
    void *fileStart;
    u32 entryNum;
    char *FSTStringStart;
    u32 FSTLength;
    u32 currDir;
} ARCHandle;

typedef struct ARCFileInfo {
    ARCHandle *handle;
    u32 startOffset;
    u32 length;
} ARCFileInfo;

#define entryIsDir(i) (((FSTEntries[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FSTEntries[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FSTEntries[i].parentOrPosition)
#define nextDir(i) (FSTEntries[i].nextEntryOrLength)

extern s32 fn_8006A554(ARCHandle *handle, const char *pathPtr); /* ARCConvertPathToEntrynum */

BOOL fn_8006A9B4(ARCHandle *handle, const char *dirName) {
    s32 entry;
    ARCEntry *FSTEntries;

    entry = fn_8006A554(handle, dirName);
    FSTEntries = (ARCEntry *)handle->FSTStart;

    if ((entry < 0) || (entryIsDir(entry) == FALSE)) {
        return FALSE;
    }

    handle->currDir = (u32)entry;
    return TRUE;
}
