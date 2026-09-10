#include "types.h"

struct fn_8006CDFC_Arg0 {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
};
struct fn_8006CDFC_lbl_801A6CA8 {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
};

extern struct fn_8006CDFC_lbl_801A6CA8 lbl_801A6CA8;

#pragma opt_propagation off
void fn_8006CDFC(struct fn_8006CDFC_Arg0 *arg0) {
    u8 v2;
    u8 v1;
    u8 v0;
    v0 = arg0->unk_0;
    v1 = arg0->unk_1;
    v2 = arg0->unk_2;
    lbl_801A6CA8.unk_0 = v0;
    lbl_801A6CA8.unk_1 = v1;
    lbl_801A6CA8.unk_2 = v2;
}
#pragma opt_propagation reset

