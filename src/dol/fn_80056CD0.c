#include "types.h"

extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 fn_8004AC58(u32);

typedef struct Fn80056CD0 {
    u8 pad0[1];
    s8 flag1;
    s8 flag2;
    u8 pad3[0x19];
    u32 field1c;
    u32 field20;
    u32 field24;
    u32 resource;
    u32 field2c;
    u8 pad30[4];
    u32 field34;
} Fn80056CD0;

void fn_80056CD0(Fn80056CD0 *arg0) {
    if (arg0 == 0) {
        fn_800565FC((u32)&lbl_80092188);
    } else if (arg0->flag1) {
        arg0->flag1 = 0;
        if (arg0->resource != 0 && arg0->flag2 == 1) {
            fn_8004AC58(arg0->resource);
            arg0->flag2 = 0;
        }
        arg0->field2c = 0;
        if (arg0 == 0) {
            fn_800565FC((u32)&lbl_80092188);
        } else if (!arg0->flag1) {
            arg0->field1c = 0;
            arg0->field20 = 0;
            arg0->field24 = 0;
        }
        arg0->field34 = 0;
    }
}
