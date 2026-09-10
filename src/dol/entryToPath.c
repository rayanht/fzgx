#include <types.h>

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

extern FSTEntry *FstStart;

extern char *FstStringStart;

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
    name = FstStringStart + (FstStart[entry].isDirAndStringOff & ~0xff000000);
    loc = entryToPath((FstStart[entry].parentOrPosition), path, maxlen);
    if (loc == maxlen) {
        return loc;
    }
    *(path + loc++) = '/';
    loc += myStrncpy(path + loc, name, maxlen - loc);
    return loc;
}
