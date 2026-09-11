#include "types.h"

typedef struct {
    s8 flag;
    u8 pad[0x237];
} Entry;

extern void fn_80056710(void *);
extern u32 lbl_80188A88[];
extern Entry lbl_80188A8C[16];
extern void fn_80057114(void *);
extern void *memset(void *, int, u32);
extern void fn_800566BC(int, int);
extern void fn_800566F0(void *);

void fn_80057378(void) {
    u8 local[16];
    int i;

    fn_80056710(local);
    if (--lbl_80188A88[0] == 0) {
        i = 0;
        do {
            if (lbl_80188A8C[i].flag == 1) {
                fn_80057114(&lbl_80188A8C[i]);
            }
            i++;
        } while (i < 0x10);
        memset(lbl_80188A8C, 0, 0x2380);
        fn_800566BC(0, 0);
    }
    fn_800566F0(local);
}
