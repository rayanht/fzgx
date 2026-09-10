#include <types.h>

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

extern FSTEntry *FstStart_801A68A4;

extern u32 lbl_801A68B0;

u32 fn_8001724C(u32 entry, char *path, u32 maxlen);

static inline BOOL DVDConvertEntrynumToPath(s32 entrynum, char *path, u32 maxlen) {
    u32 loc;
    loc = fn_8001724C((u32)entrynum, path, maxlen);
    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return 0;
    }
    if ((((FstStart_801A68A4[entrynum].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return 0;
        }
        path[loc++] = '/';
    }
    path[loc] = '\0';
    return 1;
}

BOOL fn_800173AC(char *path, u32 maxlen) {
    return DVDConvertEntrynumToPath((s32)lbl_801A68B0, path, maxlen);
}
