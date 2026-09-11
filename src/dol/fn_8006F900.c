#include "types.h"

extern f32 lbl_801A6618;
extern f32 lbl_801A661C;
extern const f32 lbl_801A73F8;
extern const f32 lbl_801A7408;
extern const f32 lbl_801A740C;
extern const f64 lbl_801A7400;
extern void lbl_8006E1B0(void *, void *);

typedef struct {
    f32 value0;
    f32 value4;
    f32 value8;
} Fn8006F900Data;

void fn_8006F900(void *arg0, Fn8006F900Data *arg1, f32 arg2) {
    f32 value8;
    f32 factor;

    lbl_8006E1B0(arg0, arg1);
    value8 = arg1->value8;
    if (__fabsf(value8) > lbl_801A7400) {
        factor = lbl_801A73F8 / (value8 * arg2);
        arg1->value0 = factor * (arg1->value0 * (lbl_801A740C * lbl_801A661C / (lbl_801A740C * lbl_801A6618)));
        arg1->value4 = arg1->value4 * factor;
    } else {
        arg1->value0 = lbl_801A7408;
        arg1->value4 = lbl_801A7408;
    }
}
