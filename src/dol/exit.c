
#include "types.h"

typedef void (*ExitFunction)(void);

void __begin_critical_region(int region);

void __end_critical_region(int region);

void __kill_critical_regions(void);

extern void __destroy_global_chain(void);

extern void _ExitProcess(void);

extern ExitFunction _dtors[];

extern ExitFunction __atexit_funcs[64];

extern ExitFunction __console_exit;

extern ExitFunction __stdio_exit;

extern int __atexit_curr_func;

extern int __aborting;

void exit(int status) {
    ExitFunction *destructor;
    if (!__aborting) {
        __begin_critical_region(0);
        __end_critical_region(0);
        __destroy_global_chain();
        destructor = _dtors;
        while (*destructor != 0) {
            (*destructor)();
            ++destructor;
        }
        if (__stdio_exit != 0) {
            __stdio_exit();
            __stdio_exit = 0;
        }
    }
    __begin_critical_region(0);
    while (__atexit_curr_func > 0)
        __atexit_funcs[--__atexit_curr_func]();
    __end_critical_region(0);
    __kill_critical_regions();
    if (__console_exit != 0) {
        __console_exit();
        __console_exit = 0;
    }
    _ExitProcess();
}
