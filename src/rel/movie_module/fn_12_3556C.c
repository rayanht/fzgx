#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *movie;
} MovieModuleState;

extern s32 fn_12_3A36C(MovieModuleState *self);
extern char lbl_12_rodata_18CC[51];
extern void MWSFSVM_Error(const char *format, ...);
extern void fn_12_8B4(void *movie, void *arg1, void *arg2);

void fn_12_3556C(MovieModuleState *self, void *arg1, void *arg2) {
    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error(lbl_12_rodata_18CC);
    } else {
        fn_12_8B4(self->movie, arg1, arg2);
    }
}
