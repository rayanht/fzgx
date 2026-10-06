#include "types.h"

typedef struct Fn8003A4E8_HuffTab {
    u8 *bits;
    char *size;
    u8 pad_8[0x9C];
    s32 lastK;
} Fn8003A4E8_HuffTab;

typedef struct Fn8003A4E8_Info {
    u8 pad_0[0x420];
    Fn8003A4E8_HuffTab huffmanTabs[4];
    u8 pad_6C0[0xF4];
    u8 *buffer;
} Fn8003A4E8_Info;

u8 fn_8003A4E8(Fn8003A4E8_Info *info, u8 tabIndex, u8 *bits) {
    s32 p;
    s32 l;
    s32 i;
    s32 num;
    s32 n;

    num = 0;
    for (i = 1; i <= 16; i++) {
        num += bits[i - 1];
    }

    info->huffmanTabs[tabIndex].size = (char *)info->buffer;
    info->buffer += num + 1;

    p = 0;
    for (l = 1; l <= 16; l++) {
        n = bits[l - 1];
        while (n--) {
            info->huffmanTabs[tabIndex].size[p] = (char)l;
            p++;
        }
    }
    info->huffmanTabs[tabIndex].size[p] = 0;
    info->huffmanTabs[tabIndex].lastK = p;
    return 0;
}
