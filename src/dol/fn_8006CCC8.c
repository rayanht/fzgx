#include "types.h"

extern f64 lbl_801A73A0;
extern u32 lbl_801A7398;
extern u32 lbl_801A6CF4;
extern u32 lbl_801A6CAC;
extern u32 lbl_801A6CA8;
extern f32 lbl_801A6CA4;
extern f32 lbl_801A6CA0;

struct Fn8006CCC8Data {
    u8 pad0[0xe];
    u16 value_e;
    u16 value_10;
};

void fn_8006CCC8(void) {
    struct Fn8006CCC8Data *data;
    u16 value_e;
    u16 value_10;

    data = (struct Fn8006CCC8Data *)lbl_801A6CF4;
    lbl_801A6CAC = 0;
    lbl_801A6CA8 = lbl_801A7398;
    value_e = data->value_e;
    lbl_801A6CA4 = (f32)value_e;
    value_10 = data->value_10;
    lbl_801A6CA0 = (f32)value_10;
}
