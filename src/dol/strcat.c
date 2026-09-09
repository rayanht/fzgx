#include "types.h"

char *strcat(char *dest, const char *src) {
    const unsigned char *s = (const unsigned char *)src - 1;
    unsigned char *d = (unsigned char *)dest - 1;

    while (*++d != 0) {
    }
    --d;
    while ((*++d = *++s) != 0) {
    }
    return dest;
}

