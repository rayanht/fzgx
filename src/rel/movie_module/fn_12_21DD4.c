#include "types.h"

extern int fn_12_2F210(void *module, void *movie, int command, int value, int flags);

int fn_12_21DD4(void *module, int index, int value) {
    u8 *entry = (u8 *)module + index * 0x74;

    if (*(s32 *)(entry + 0x1144) == 0) {
        return fn_12_2F210(module, *(void **)(entry + 0x118c), 0xb, value, 0);
    }
    return 0;
}
