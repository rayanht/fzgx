#include "types.h"
#include "dol/globals.h"

extern void fn_8003742C(s32, s32, s32);

void fn_80072AB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 *entry;

    entry = (s32 *)(lbl_801A6D38 + (arg0 << 3) + 0x6c);
    if (entry[0] != arg1 || entry[1] != arg2) {
        fn_8003742C(arg0, arg1, arg2);
        entry[0] = arg1;
        entry[1] = arg2;
    }
}
