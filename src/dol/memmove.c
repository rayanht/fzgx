
#include "types.h"

extern void fn_80080458(void *destination, const void *source, size_t count);

extern void fn_800803AC(void *destination, const void *source, size_t count);

extern void fn_800805C0(void *destination, const void *source, size_t count);

extern void fn_80080518(void *destination, const void *source, size_t count);

void *memmove(void *destination, const void *source, size_t count) {
    unsigned char *source_byte;
    unsigned char *destination_byte;
    int reverse = (unsigned int)source < (unsigned int)destination;
    if (count >= 32) {
        if (((unsigned int)destination ^ (unsigned int)source) & 3) {
            if (!reverse)
                fn_80080458(destination, source, count);
            else
                fn_800803AC(destination, source, count);
        } else if (!reverse) {
            fn_800805C0(destination, source, count);
        } else {
            fn_80080518(destination, source, count);
        }
        return destination;
    }
    if (!reverse) {
        source_byte = (unsigned char *)source - 1;
        destination_byte = (unsigned char *)destination - 1;
        ++count;
        while (--count > 0)
            *++destination_byte = *++source_byte;
    } else {
        source_byte = (unsigned char *)source + count;
        destination_byte = (unsigned char *)destination + count;
        ++count;
        while (--count > 0)
            *--destination_byte = *--source_byte;
    }
    return destination;
}
