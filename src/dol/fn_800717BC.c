#include "types.h"


u32 fn_800717BC(u32 arg0, u32 arg1) {
    s32 i;
    s32 c0;
    s32 c1;
    s32 v;
    s32 n;
    c1 = 0;
    c0 = 0;
    for (i = 0; i < 10; i++) {
    if ((arg0 & (1u << i)) != 0) {
    c0++;
    }
    if ((arg1 & (1u << i)) != 0) {
    c1++;
    }
    }
    v = (s32)arg0;
    if (c0 > 1 || c1 > 1) {
    return -1;
    }
    if (v > (s32)arg1) {
    v = (s32)arg1;
    }
    n = 0;
    while (v > 4) {
    v = (v >> 1);
    n++;
    }
    return n;
}
