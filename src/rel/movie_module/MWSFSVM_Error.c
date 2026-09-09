#include "types.h"
#include "runtime/va_list.h"

void* memset(void* destination, int value, size_t size);

void fn_800595A4(const char *message);

int fn_8008077C(char *output, const char *format, __va_list args);

extern char lbl_12_bss_1B8A0[256];

void MWSFSVM_Error(const char *format, ...) {
    __va_list arguments;
    memset(lbl_12_bss_1B8A0, 0, sizeof(lbl_12_bss_1B8A0));
    ((void)(format), __builtin_va_info(&(arguments)));
    fn_8008077C(lbl_12_bss_1B8A0, format, arguments);
    fn_800595A4(lbl_12_bss_1B8A0);
    ((void)0);
}
