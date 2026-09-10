
#include "types.h"

typedef struct MkVaListState {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

typedef __va_list va_list;

typedef struct __OutStrCtrl {
    char *CharStr;
    size_t MaxCharCount;
    size_t CharsWritten;
} __OutStrCtrl;

int __pformatter(void *(*WriteProc)(void *, const char *, size_t), void *WriteProcArg,
                 const char *format_str, va_list arg);

void *fn_80080974(void *pCtrl, const char *pBuffer, size_t char_num);

static inline int vsnprintf(char *s, size_t n, const char *format, va_list arg) {
    int end;
    __OutStrCtrl osc;
    osc.CharStr = s;
    osc.MaxCharCount = n;
    osc.CharsWritten = 0;
    end = __pformatter(&fn_80080974, &osc, format, arg);
    if (s) {
        s[(end < n) ? end : n - 1] = '\0';
    }
    return end;
}

int sprintf(char *s, const char *format, ...) {
    va_list args;
    ((void)(format), __builtin_va_info(&(args)));
    return vsnprintf(s, 0xFFFFFFFF, format, args);
}
