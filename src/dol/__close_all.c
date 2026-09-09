#include "types.h"

extern u8 __files[320];
extern u32 __begin_critical_region(u32);
extern void fn_8007FA0C(void *);
extern void fn_8007A150(void *);
extern u32 __end_critical_region(u32);

typedef struct File {
    u8 pad0[4];
    u16 unused0:7;
    u16 mode:3;
    u16 unused1:6;
    u8 pad6[6];
    u8 in_use;
    u8 padD[0x3f];
    struct File *next;
} File;

void __close_all(void) {
    File *file;

    file = (File *)&__files;
    __begin_critical_region(2);
    while (file != 0) {
        if (file->mode != 0) {
            fn_8007FA0C(file);
        }
        {
            File *current;
            current = file;
            file = file->next;
            if (current->in_use != 0) {
                fn_8007A150(current);
            } else {
                current->mode = 3;
                if (file != 0 && file->in_use != 0) {
                    current->next = 0;
                }
            }
        }
    }
    __end_critical_region(2);
}
