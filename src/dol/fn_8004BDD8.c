#include "types.h"

typedef struct ADXFSpu {
    s8 used;
    u8 reserved[0xBF];
} ADXFSpu;

extern s32 lbl_8017E56C[8];
extern ADXFSpu lbl_80178CBC[16];

extern void fn_80046738(void);
extern void fn_80046718(void);
extern void fn_80041700(void);
extern void fn_8004D220(void *);
extern void fn_8004EE44(void);

void fn_8004BDD8(void) {
    s32 index;

    fn_80046738();
    if (lbl_8017E56C[0] != 0) {
        fn_80046718();
    } else {
        lbl_8017E56C[0] = 1;
        fn_80046718();
        fn_80046738();
        fn_80041700();
        lbl_8017E56C[0] = 2;
        for (index = 0; index < 16; index++) {
            if (lbl_80178CBC[index].used == 1) {
                fn_8004D220(&lbl_80178CBC[index]);
            }
        }
        lbl_8017E56C[0] = 3;
        fn_8004EE44();
        lbl_8017E56C[0] = 0;
        fn_80046718();
    }
}
