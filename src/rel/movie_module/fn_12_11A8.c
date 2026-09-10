#include "types.h"
typedef struct Sig_fn_12_748_MovieModule {
    u8 pad30[0x30];
    int value;
} Sig_fn_12_748_MovieModule;

struct fn_12_11A8_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
};
extern u32 lbl_12_rodata_28C;
extern int fn_12_748(Sig_fn_12_748_MovieModule *);
extern u32 fn_12_F70(u32, u32, void *, u32);
extern u32 fn_12_3D968(u32);
extern u32 fn_12_3D740(u32);
extern void fn_12_309C(u32, u32, u32);


void fn_12_11A8(Sig_fn_12_748_MovieModule *arg0, u32 arg1, void *arg2) {
    s32 temp_r0;
    s32 var_r0;
    s32 temp_r3;
    s32 var_r0_2;
    s32 temp_r3_2;

    temp_r0 = *(s32 *)((u8 *)(arg0) + 4);
    switch (temp_r0) {                              /* irregular */
    case 0x11:
        if (fn_12_748((Sig_fn_12_748_MovieModule *)(arg0)) != 1) {
            fn_12_F70((u32)((u32)(arg0)), (u32)(arg1), (void *)(arg2), (u32)(0U));
            return;
        }
        temp_r3 = *(s32 *)((u8 *)(arg0) + 52);
        var_r0 = 1;
        if (temp_r3 == 0x64) {
            var_r0 = 0;
        } else if (temp_r3 == 0x16) {
            var_r0 = 0;
        }
        if (var_r0 == 1) {
            (*(s32 *)((u8 *)(arg0) + 52)) = 0x16;
            fn_12_3D968((u32)(*(u32 *)((u8 *)(arg0) + 56)));
        }
        fn_12_F70((u32)((u32)(arg0)), (u32)(arg1), (void *)(arg2), (u32)(1U));
        return;
    case 0x101:
        fn_12_F70((u32)((u32)(arg0)), (u32)(arg1), (void *)(arg2), (u32)(0U));
        return;
    case 0x1001:
        temp_r3_2 = *(s32 *)((u8 *)(arg0) + 52);
        var_r0_2 = 1;
        if (temp_r3_2 == 0x64) {
            var_r0_2 = 0;
        } else if (temp_r3_2 == 0x15) {
            var_r0_2 = 0;
        }
        if (var_r0_2 == 1) {
            (*(s32 *)((u8 *)(arg0) + 52)) = 0x15;
            fn_12_3D740((u32)(*(u32 *)((u8 *)(arg0) + 56)));
        }
        fn_12_F70((u32)((u32)(arg0)), (u32)(arg1), (void *)(arg2), (u32)(1U));
        return;
    default:
    case 0x41:
    case 0xF1:
    case 0x21:
    case 0x31:
        fn_12_309C((u32)((u32)(arg0)), (u32)(arg1), (u32)((u32)(&lbl_12_rodata_28C)));
        return;
    }
}
