#include "types.h"

struct fn_8005190C_lbl_80187110 {
    u32 unk_0;
};

extern struct fn_8005190C_lbl_80187110 lbl_80187110[];
extern u32 lbl_80187330[16];
extern u32 memset(u32, u32, u32);
extern void fn_80053BB4(void);

void fn_8005190C(void) {
    struct fn_8005190C_lbl_80187110 *counter;
    u32 count;

    counter = &lbl_80187110[0];
    count = counter->unk_0 - 1;
    counter->unk_0 = count;
    if (count == 0) {
        memset((u32)&lbl_80187330, 0, 64);
        fn_80053BB4();
    }
}
