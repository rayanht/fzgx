#include "types.h"

typedef struct {
    u32 gpr_fpr;
    void *overflow;
    void *regsave;
} va_list[1];

#define va_start(ap, last) do { \
    (ap)[0].gpr_fpr = 0x1000000; \
    (ap)[0].overflow = (void *)((char *)&(ap) + 0x14); \
    (ap)[0].regsave = (void *)((char *)&(ap) - 0x64); \
} while (0)
#define va_end(ap) ((void)0)

extern s32 vprintf(const char *format, va_list args);

void OSReport(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
