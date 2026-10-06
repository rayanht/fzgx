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
extern BOOL fn_8006A8CC(ARCHandle *handle, char *path, u32 maxlen); /* ARCGetCurrentDir */
extern void OSReport(const char *msg, ...);
extern char lbl_801327AC[]; /* "Warning: ARCOpen(): file '%s' was not found under %s in the archive.\n" */

BOOL fn_8006A480(ARCHandle *handle, const char *fileName, ARCFileInfo *af) {
    s32 entry;
    char currentDir[128];
    ARCEntry *FSTEntries;

    FSTEntries = (ARCEntry *)handle->FSTStart;
    entry = fn_8006A554(handle, fileName);

    if (0 > entry) {
        fn_8006A8CC(handle, currentDir, 128);
        OSReport(lbl_801327AC, fileName, currentDir);
        return FALSE;
    }

    if ((entry < 0) || entryIsDir(entry)) {
        return FALSE;
    }

    af->handle = handle;
    af->startOffset = FSTEntries[entry].parentOrPosition;
    af->length = FSTEntries[entry].nextEntryOrLength;

    return TRUE;
}
