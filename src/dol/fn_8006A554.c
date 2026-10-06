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

extern int fn_8007ED90(int c); /* tolower */

#define entryIsDir(i) (((FSTEntries[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FSTEntries[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FSTEntries[i].parentOrPosition)
#define nextDir(i) (FSTEntries[i].nextEntryOrLength)

static BOOL isSame(const char *path, const char *string) {
    while (*string != '\0') {
        if (fn_8007ED90(*path++) != fn_8007ED90(*string++)) {
            return FALSE;
        }
    }
    if ((*path == '/') || (*path == '\0')) {
        return TRUE;
    }
    return FALSE;
}

s32 fn_8006A554(ARCHandle *handle, const char *pathPtr) {
    const char *ptr;
    char *stringPtr;
    BOOL isDir;
    s32 length;
    u32 dirLookAt;
    u32 i;
    ARCEntry *FSTEntries;
    const char *origPathPtr = pathPtr; /* unused, as in the SDK arc.c */

    dirLookAt = handle->currDir;
    FSTEntries = (ARCEntry *)handle->FSTStart;

    while (1) {
        if (*pathPtr == '\0') {
            return (s32)dirLookAt;
        } else if (*pathPtr == '/') {
            dirLookAt = 0;
            pathPtr++;
            continue;
        } else if (*pathPtr == '.') {
            if (*(pathPtr + 1) == '.') {
                if (*(pathPtr + 2) == '/') {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                } else if (*(pathPtr + 2) == '\0') {
                    return (s32)parentDir(dirLookAt);
                }
            } else if (*(pathPtr + 1) == '/') {
                pathPtr += 2;
                continue;
            } else if (*(pathPtr + 1) == '\0') {
                return (s32)dirLookAt;
            }
        }

        for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
        }

        isDir = (*ptr == '\0') ? FALSE : TRUE;
        length = (s32)(ptr - pathPtr);

        ptr = pathPtr;

        for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
            if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
                continue;
            }

            stringPtr = handle->FSTStringStart + stringOff(i);

            if (isSame(ptr, stringPtr) == TRUE) {
                goto next_hier; // fzgx-allow: S1 leaves the entry scan to next_hier, verbatim from SDK arc.c
            }
        }

        return -1;

    next_hier:
        if (isDir == FALSE) {
            return (s32)i;
        }

        dirLookAt = i;
        pathPtr += length + 1;
    }
}
