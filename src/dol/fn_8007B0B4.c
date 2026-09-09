#include "types.h"

typedef struct FileEntry {
    u8 pad00[4];
    u16 unk04;
    u8 pad06[0x46];
    struct FileEntry *next;
} FileEntry;

extern u8 __files[320];
extern s32 fn_8007F8D4(FileEntry *);

s32 fn_8007B0B4(void) {
    s32 result;
    FileEntry *entry;

    result = 0;
    entry = (FileEntry *)&__files;
    while (entry != 0) {
        if (((entry->unk04 >> 6) & 7) != 0) {
            if (fn_8007F8D4(entry) != 0) {
                result = -1;
            }
        }
        entry = entry->next;
    }
    return result;
}
