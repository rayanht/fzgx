#include "types.h"
typedef struct Sig_fn_12_3A384_Fn12_3A384_Object {
    u8 _pad[0x44];
    u32 value;
} Sig_fn_12_3A384_Fn12_3A384_Object;

struct fn_12_38DC8_Arg0 {
    u8 pad_0[0x134];
    u32 unk_134;
};
extern f64 lbl_12_rodata_24C8;
extern f64 lbl_12_rodata_24D0;
extern void fn_12_3A384(Sig_fn_12_3A384_Fn12_3A384_Object *, u32, u32);


void fn_12_38DC8(Sig_fn_12_3A384_Fn12_3A384_Object *arg0) {
    s32 temp_r5;

    temp_r5 = *(s32 *)((u8 *)(arg0) + 308);
    fn_12_3A384((Sig_fn_12_3A384_Fn12_3A384_Object *)(arg0), (u32)((u32) (s32) ((*(f64 *)((u8 *)(&lbl_12_rodata_24C8) + 0)) * (f64) temp_r5)), (u32)((u32) temp_r5));
}
