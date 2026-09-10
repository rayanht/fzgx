#ifndef PROFILEBIOGRAPHYBUFFER_H
#define PROFILEBIOGRAPHYBUFFER_H

#include "types.h"

typedef struct {
    char biographies[41][6][2048];
} ProfileBiographyBuffer;
extern ProfileBiographyBuffer lbl_16_bss_B0B8;

#endif
