#include "types.h"

extern f64 fn_80087E80(f32);

f32 fn_80088624(f32 arg0) {
    u32 t0;
    return (f32)(fn_80087E80(arg0));
}
