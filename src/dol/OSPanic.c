#include <dolphin/os.h>

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

typedef __va_list va_list;

void PPCHalt(void);

void OSReport(const char *msg, ...);

u32 fn_8000BFC0();

int vprintf(const char *, va_list);

void OSReport(const char *msg, ...);

void OSPanic(const char *file, int line, const char *msg, ...) {
    va_list marker;
    u32 i;
    u32 *p;
    OSDisableInterrupts();
    ((void)msg, __builtin_va_info(&marker));
    vprintf(msg, marker);
    (void)0;
    OSReport(" in \"%s\" on line %d.\n", file, line);
    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32 *)fn_8000BFC0(); p && (u32)p != 0xffffffff && i++ < 16; p = (u32 *)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
    PPCHalt();
}
