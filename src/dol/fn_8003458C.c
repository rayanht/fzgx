#include "types.h"

struct fn_8003458C_gx_T {
    u8 pad_0[0x4F4];
    u32 unk_4F4;
};

extern struct fn_8003458C_gx_T *gx;
extern u32 fn_80032B8C(void);
extern u32 fn_80032BE0(void);
extern u32 fn_80033650(void);
extern u32 fn_80034918(void);
extern u32 fn_8003666C(void);
extern u32 fn_80036F24(void);

void fn_8003458C(void) {
    if ((gx->unk_4F4 & 0x1) != 0) {
    fn_8003666C();
    }
    if ((gx->unk_4F4 & 0x2) != 0) {
    fn_80036F24();
    }
    if ((gx->unk_4F4 & 0x4) != 0) {
    fn_80034918();
    }
    if ((gx->unk_4F4 & 0x8) != 0) {
    fn_80032B8C();
    }
    if ((gx->unk_4F4 & 0x10) != 0) {
    fn_80033650();
    }
    if ((gx->unk_4F4 & 0x18) != 0) {
    fn_80032BE0();
    }
    gx->unk_4F4 = 0;
}
