#include "types.h"

typedef u32 (*__init_cpp_Fn)(void);

extern u32 _ctors[];

#pragma peephole off
void __init_cpp(void) {
    __init_cpp_Fn *p = (__init_cpp_Fn *)&_ctors;
    while (*p != 0) {
        (*p)();
        p++;
    }
}
#pragma peephole reset

