#include "types.h"

typedef void (*fn_80059D68_Fn0)(u32, void *, u32);

extern u32 lbl_80190178[];
extern u32 lbl_8019017C[637];
extern char lbl_80092634[24];
extern void fn_80059B44(void);
extern void fn_80059AB4(void);

typedef struct Fn80059D68 {
    u8 unk00;
    u8 unk01;
} Fn80059D68;

void fn_80059D68(Fn80059D68 *self) {
    if (self == 0) {
        if (lbl_80190178[0] != 0) {
            ((fn_80059D68_Fn0)lbl_80190178[0])(
                lbl_8019017C[0], &lbl_80092634, 0);
        }
    } else {
        fn_80059B44();
        self->unk01 = 0;
        fn_80059AB4();
    }
}
