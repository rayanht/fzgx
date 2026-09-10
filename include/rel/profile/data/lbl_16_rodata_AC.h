#ifndef DATA_LBL_16_RODATA_AC_H
#define DATA_LBL_16_RODATA_AC_H

#include "types.h"

typedef union {
    u32 bits[76];
    f32 values[76];
} Data_lbl_16_rodata_AC;
extern const Data_lbl_16_rodata_AC lbl_16_rodata_AC;

#endif
