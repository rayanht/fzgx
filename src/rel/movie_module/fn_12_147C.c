#include "types.h"
typedef struct Sig_fn_12_740_MovieModule {
    u8 pad[0x60];
    int value;
} Sig_fn_12_740_MovieModule;

typedef struct Sig_fn_12_49D8_MovieState {
    u8 pad[0x58];
    s32 value;
} Sig_fn_12_49D8_MovieState;

struct Sig_fn_12_49AC_fn_12_49AC_Arg0 {
    u8 pad_0[0x58];
    u32 unk_58;
};

struct Sig_fn_12_738_MovieData {
    u8 pad[0x64];
    int value;
};

struct Sig_fn_12_13D0_fn_12_13D0_Arg1 {
    u8 pad_0[0x48];
    u32 unk_48;
};

extern s32 fn_12_307C(void);
extern int fn_12_740(Sig_fn_12_740_MovieModule *);
extern int fn_12_49D8(Sig_fn_12_49D8_MovieState *);
extern s32 fn_12_49AC(struct Sig_fn_12_49AC_fn_12_49AC_Arg0 *);
extern int fn_12_738(struct Sig_fn_12_738_MovieData *);
extern void fn_12_13D0(u32, struct Sig_fn_12_13D0_fn_12_13D0_Arg1 *, void *);
extern u32 fn_12_132C(u32, u32, void *);


void fn_12_147C(Sig_fn_12_740_MovieModule *arg0, struct Sig_fn_12_13D0_fn_12_13D0_Arg1 *arg1, void *arg2) {
    s32 temp_r3;
    s32 var_r31;

    if (fn_12_307C() == 0) {
        temp_r3 = fn_12_740((Sig_fn_12_740_MovieModule *)(arg0));
        switch (temp_r3) {                          /* irregular */
        case -1:
            var_r31 = 0;
            if ((fn_12_49D8((Sig_fn_12_49D8_MovieState *)((Sig_fn_12_49D8_MovieState *) arg0)) == 1) && (fn_12_49AC((struct Sig_fn_12_49AC_fn_12_49AC_Arg0 *)((struct Sig_fn_12_49AC_fn_12_49AC_Arg0 *) arg0)) == 1) && (fn_12_738((struct Sig_fn_12_738_MovieData *)((struct Sig_fn_12_738_MovieData *) arg0)) == 0)) {
                var_r31 = 1;
            }
            break;
        case 0:
            var_r31 = 0;
            break;
        case 1:
            var_r31 = 1;
            break;
        default:
            var_r31 = 0;
            break;
        }
        if (var_r31 == 1) {
            fn_12_13D0((u32)((u32)(arg0)), (struct Sig_fn_12_13D0_fn_12_13D0_Arg1 *)(arg1), (void *)(arg2));
            return;
        }
        goto block_16; /* Preserves the retail branch. */
    }
block_16:
    fn_12_132C((u32)((u32)(arg0)), (u32)((u32)(arg1)), (void *)(arg2));
}
