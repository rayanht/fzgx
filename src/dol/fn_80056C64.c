#include "types.h"

extern void fn_80056710(void *);
extern void fn_800566F0(void *);
extern void fn_80057494(void *);

typedef struct Fn80056C64_Entry {
    s8 flag;
    u8 pad[0x237];
} Fn80056C64_Entry;

extern Fn80056C64_Entry lbl_80188A8C[16];

void fn_80056C64(void) {
    u8 local[16];
    s32 i;

    fn_80056710(local);
    i = 0;
    do {
        if (lbl_80188A8C[i].flag == 1) {
            fn_80057494(&lbl_80188A8C[i]);
        }
        i++;
    } while (i < 0x10);
    fn_800566F0(local);
}
