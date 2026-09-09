#include "types.h"
typedef struct Sig_fn_12_2D470_MovieModuleState {
    u8 pad_0[0x78];
    s32 field_78;
    u8 pad_7c[0x8c];
    s32 field_108;
    u8 field_10c[1];
} Sig_fn_12_2D470_MovieModuleState;

typedef struct Sig_fn_12_3310C_MovieEntry {
    s32 used;
    u32 arg0;
    u32 arg1;
    u32 unk_0c;
} Sig_fn_12_3310C_MovieEntry;

struct Sig_fn_12_330E0_fn_12_330E0_Arg0 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};

struct fn_12_3379C_Arg0 {
    u8 pad_0[0x40];
    u32 unk_40;
};
extern s32 fn_12_2D470(Sig_fn_12_2D470_MovieModuleState *, void * *, u32 *);
extern Sig_fn_12_3310C_MovieEntry * fn_12_3310C(u32, u32);
extern int fn_12_32EAC(void *, u32 *);
extern u32 fn_12_330E0(struct Sig_fn_12_330E0_fn_12_330E0_Arg0 *);

s32 fn_12_321E8(Sig_fn_12_3310C_MovieEntry *, s32 *); /* extern */

s32 fn_12_3379C(void *arg0) {
    u32 sp14;
    void *sp10;
    u32 spC;
    s32 sp8;
    s32 var_r31;
    Sig_fn_12_3310C_MovieEntry *temp_r3;

    if (fn_12_2D470((Sig_fn_12_2D470_MovieModuleState *)(*(Sig_fn_12_2D470_MovieModuleState **)((u8 *)(arg0) + 64)), (void * *)(&sp10), (u32 *)(&sp14)) != 0) {
        return -1;
    }
    if ((sp14 < 0x800U) || (sp10 == NULL)) {
        return -1;
    }
    temp_r3 = (Sig_fn_12_3310C_MovieEntry *)(fn_12_3310C((u32)(sp10), sp14));
    if (temp_r3 == NULL) {
        return -1;
    }
    if ((fn_12_32EAC((void *)(temp_r3), (u32 *)(&spC)) == 0) || ((s32) spC == 0)) {
        fn_12_330E0((struct Sig_fn_12_330E0_fn_12_330E0_Arg0 *)((struct Sig_fn_12_330E0_fn_12_330E0_Arg0 *) temp_r3));
        return -1;
    }
    if (fn_12_321E8((Sig_fn_12_3310C_MovieEntry *)(temp_r3), (s32 *)(&sp8)) == 0) {
        var_r31 = -1;
    } else {
        var_r31 = sp8;
    }
    fn_12_330E0((struct Sig_fn_12_330E0_fn_12_330E0_Arg0 *)((struct Sig_fn_12_330E0_fn_12_330E0_Arg0 *) temp_r3));
    return var_r31;
}
