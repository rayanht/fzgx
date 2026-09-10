
#include "types.h"

int fn_80046D18(signed char *buffer, int buffer_len, short *data_len) {
    short code;
    int offset;
    int minimum;
    minimum = 0x7FFFFFFF;
    code = (short)0x8000;
    for (offset = 0; offset < buffer_len - 1; offset += 2) {
        if (*(short *)&buffer[offset] == code) {
            minimum = offset < minimum ? offset : minimum;
            break;
        }
    }
    if (minimum != 0x7FFFFFFF) {
        *data_len = (short)minimum;
        return 0;
    } else {
        *data_len = 0;
        return -1;
    }
}
