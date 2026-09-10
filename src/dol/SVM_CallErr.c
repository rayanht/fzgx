
#include "types.h"

typedef void (*SVMErrorFunction)(void *object, char *message);

typedef struct MkVaListState {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

typedef struct SVMErrorCallback {
    SVMErrorFunction function;
    void *object;
} SVMErrorCallback;

int fn_8008077C(char *output, const char *format, __va_list args);

extern char lbl_8018FEE0[128];

extern SVMErrorCallback lbl_8018FF60;

void SVM_CallErr(const char *message, ...) {
    __va_list arguments;
    memset(lbl_8018FEE0, 0, sizeof(lbl_8018FEE0));
    ((void)(message), __builtin_va_info(&(arguments)));
    fn_8008077C(lbl_8018FEE0, message, arguments);
    if (lbl_8018FF60.function != 0) {
        lbl_8018FF60.function(lbl_8018FF60.object, lbl_8018FEE0);
    }
    ((void)0);
}
