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

extern u32 fn_8006A768(ARCHandle *handle, u32 entry, char *path, u32 maxlen); /* entryToPath */

static BOOL ARCConvertEntrynumToPath(ARCHandle *handle, s32 entrynum, char *path, u32 maxlen) {
    u32 loc;
    ARCEntry *FSTEntries;

    FSTEntries = (ARCEntry *)handle->FSTStart;
    loc = fn_8006A768(handle, (u32)entrynum, path, maxlen);

    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (entryIsDir(entrynum)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }
        path[loc++] = '/';
    }

    path[loc] = '\0';
    return TRUE;
}

BOOL fn_8006A8CC(ARCHandle *handle, char *path, u32 maxlen) {
    return ARCConvertEntrynumToPath(handle, (s32)handle->currDir, path, maxlen);
}
