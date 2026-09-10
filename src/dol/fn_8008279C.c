
#include "types.h"

extern void fn_8008279C(void *base, unsigned long count, unsigned long size,
                        int (*compare)(const void *, const void *));

void fn_8008279C(void *base, size_t count, size_t size,
                 int (*compare)(const void *, const void *)) {
    size_t root;
    size_t remaining;
    size_t child;
    unsigned char *bytes = base;
    unsigned char *root_ptr;
    unsigned char *end_ptr;
    unsigned char *parent_ptr;
    unsigned char *child_ptr;
    if (count < 2)
        return;
    remaining = count;
    root = count / 2 + 1;
    root_ptr = bytes + size * (root - 1);
    end_ptr = bytes + size * (count - 1);
    for (;;) {
        if (root > 1) {
            --root;
            root_ptr -= size;
        } else {
            signed char *destination = (signed char *)(end_ptr - 1);
            signed char *source = (signed char *)(root_ptr - 1);
            size_t index;
            int temporary;
            for (index = size + 1; --index != 0;) {
                temporary = source[1];
                source[1] = destination[1];
                destination[1] = temporary;
                ++source;
                ++destination;
            }
            --remaining;
            if (remaining == 1)
                return;
            end_ptr -= size;
        }
        child = root;
        child_ptr = bytes + size * (root - 1);
        while (child * 2 <= remaining) {
            child *= 2;
            parent_ptr = child_ptr;
            child_ptr = bytes + size * (child - 1);
            if (child < remaining) {
                unsigned char *next = child_ptr + size;
                if (compare(child_ptr, next) < 0) {
                    child_ptr = next;
                    ++child;
                }
            }
            if (compare(parent_ptr, child_ptr) < 0) {
                signed char *destination = (signed char *)(child_ptr - 1);
                signed char *source = (signed char *)(parent_ptr - 1);
                size_t index;
                int temporary;
                for (index = size + 1; --index != 0;) {
                    temporary = source[1];
                    source[1] = destination[1];
                    destination[1] = temporary;
                    ++source;
                    ++destination;
                }
            } else {
                break;
            }
        }
    }
}
