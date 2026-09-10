#include <types.h>

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

s32 fn_80016DF8(const char *pathPtr);

extern FSTEntry *FstStart_801A68A4;

extern u32 lbl_801A68B0;

BOOL fn_80017470(char *dirName) {
    s32 entry;
    entry = fn_80016DF8(dirName);
    if ((entry < 0) ||
        ((((FstStart_801A68A4[entry].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1) == 0)) {
        return 0;
    }
    lbl_801A68B0 = (u32)entry;
    return 1;
}
