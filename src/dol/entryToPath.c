#include <types.h>

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

extern FSTEntry *FstStart_801A68A4;

extern char *FstStringStart_801A68A8;

static inline u32 myStrncpy(char *dest, char *src, u32 maxlen) {
    u32 i = maxlen;
    while ((i > 0) && (*src != 0)) {
        *dest++ = *src++;
        i--;
    }
    return (maxlen - i);
}

u32 entryToPath(u32 entry, char *path, u32 maxlen) {
    char *name;
    u32 loc;
    if (entry == 0) {
        return 0;
    }
    name = FstStringStart_801A68A8 + (FstStart_801A68A4[entry].isDirAndStringOff & ~0xff000000);
    loc = entryToPath((FstStart_801A68A4[entry].parentOrPosition), path, maxlen);
    if (loc == maxlen) {
        return loc;
    }
    *(path + loc++) = '/';
    loc += myStrncpy(path + loc, name, maxlen - loc);
    return loc;
}
