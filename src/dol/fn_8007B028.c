#include "types.h"

typedef struct FileNode {
    u8 pad00[4];
    u16 flags;
    u8 pad06[2];
    u8 type;
    u8 pad09[0x43];
    struct FileNode *next;
} FileNode;

extern u8 __files[320];
extern s32 fn_8007F8D4(FileNode *);

s32 fn_8007B028(void) {
    s32 result;
    FileNode *file;

    file = (FileNode *)&__files;
    result = 0;
    while (file != 0) {
        if (((*(u16 *)((u8 *)file + 4) >> 6) & 7) != 0 &&
            ((*(u8 *)((u8 *)file + 4) >> 1) & 1) != 0 &&
            (((u32)*(u8 *)((u8 *)file + 8) >> 5) & 7) == 1) {
            if (fn_8007F8D4(file) != 0) {
                result = -1;
            }
        }
        file = file->next;
    }
    return result;
}
