#include "types.h"

extern int fn_12_24A88(void *module, int movie);

int fn_12_21E40(void *module, int index, int *movie_id) {
    u8 *entry = (u8 *)module + index * 0x74;

    *movie_id = 0;
    if (*(s32 *)(entry + 0x1144) == 0) {
        return fn_12_24A88(module, 0xff000000 + 0x401);
    }

    *movie_id = *(s32 *)(entry + 0x1154);
    return 0;
}
