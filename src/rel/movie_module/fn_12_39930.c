#include "types.h"

extern s32 fn_12_3A36C(void *object);
extern char lbl_12_rodata_2670[46];
extern void MWSFSVM_Error(const char *format, ...);
extern char lbl_12_rodata_26A0[41];
extern void fn_12_39678(void *object, void *argument, s32 arg2, s32 arg3);

void fn_12_39930(void *object, void *argument) {
    if (fn_12_3A36C(object) == 0) {
        MWSFSVM_Error(lbl_12_rodata_2670);
    } else if (argument == 0) {
        MWSFSVM_Error(lbl_12_rodata_26A0);
    } else {
        fn_12_39678(object, argument, 0, -1);
    }
}
