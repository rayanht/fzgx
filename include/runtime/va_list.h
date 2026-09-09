#ifndef RUNTIME_VA_LIST_H
#define RUNTIME_VA_LIST_H

/* CodeWarrior's PowerPC EABI argument cursor. */
typedef struct __va_list_struct {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char* input_arg_area;
    char* reg_save_area;
} __va_list[1];

#endif
