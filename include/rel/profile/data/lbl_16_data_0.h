#ifndef PROFILETEXTDATA_H
#define PROFILETEXTDATA_H

#include "types.h"

typedef struct {
    char biographies[41][6][2048];
    char machines[41][2][6][64];
} ProfileTextData;
extern ProfileTextData lbl_16_data_0;

#endif
