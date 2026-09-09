#ifndef SOFDEC_VA_LIST_H
#define SOFDEC_VA_LIST_H

#include "types.h"

typedef struct SofdecVaListState {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

#endif
