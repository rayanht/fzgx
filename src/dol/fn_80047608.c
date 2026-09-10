#include "types.h"
struct fn_80047608_lbl_8017B158 {
    u32 unk_0;
};
extern struct fn_80047608_lbl_8017B158 lbl_8017B158[];
extern u32 fn_80046738(void);
extern void fn_80046718(void);
extern u32 fn_8004A578(void);
extern u32 fn_80054760(void);
extern u32 fn_8004FAA8(void);


void fn_80047608(void) {
    fn_80046738();
    if ((s32) lbl_8017B158->unk_0 != 0) {
        fn_80046718();
        return;
    }
    lbl_8017B158->unk_0 = 1;
    fn_80046718();
    fn_8004A578();
    lbl_8017B158->unk_0 = 2;
    fn_80054760();
    lbl_8017B158->unk_0 = 5;
    fn_8004A578();
    lbl_8017B158->unk_0 = 6;
    fn_8004FAA8();
    lbl_8017B158->unk_0 = 0;
}
