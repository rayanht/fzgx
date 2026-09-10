#include "types.h"

extern u32 fn_80006BDC(u32, ...);
extern u32 DVDFastOpen(u32, u32);
extern u32 lbl_801220E0[];
extern u32 lbl_801220CC[];

u32 fn_80006C4C(s32 arg0, u32 arg1) {
    u32 result = 0;

    if (arg0 < 0) {
        return 0;
    }

    fn_80006BDC((u32)&lbl_801220E0, arg0);
    if ((arg0 & 0x7fff0000) == 0) {
        fn_80006BDC((u32)&lbl_801220CC);
        result = DVDFastOpen(arg0, arg1 + 4);
        if (result != 0) {
            *(u32 *)arg1 = 0;
        }
    }

    return result;
}
