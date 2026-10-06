#include "types.h"

typedef struct Fn8003A1CC_HuffTab {
    u8 *bits;
    u8 pad_4[0x8];
    u16 numVals;
    u8 pad_E[0x2];
    u8 *vals;
    u8 pad_14[0x94];
} Fn8003A1CC_HuffTab;

typedef struct Fn8003A1CC_Info {
    u8 pad_0[0x400];
    u8 *c;
    u8 pad_404[0x14];
    u8 validHuffmanTabs;
    u8 pad_419[0x7];
    Fn8003A1CC_HuffTab huffmanTabs[4];
} Fn8003A1CC_Info;

extern u8 fn_8003A4E8(Fn8003A1CC_Info *info, u8 tabIndex, u8 *bits);
extern u8 fn_8003A680(Fn8003A1CC_Info *info, u8 tabIndex);
extern void fn_8003A760(Fn8003A1CC_Info *info, u8 tabIndex);

u8 fn_8003A1CC(Fn8003A1CC_Info *info) {
    u8 tabClass;
    u8 id;
    u8 i;
    u8 tabIndex;
    u8 err;
    u8 byte;
    u8 *bits;
    u16 length;
    u16 numVals;

    length = (u16)((info->c[0] << 8) | info->c[1]);
    info->c += 2;
    length -= 2;

    do {
        byte = *info->c++;
        bits = info->c;
        tabClass = byte >> 4;
        id = byte & 0xF;
        if (tabClass > 1 || id >= 2) {
            return 7;
        }
        tabIndex = (id << 1) + tabClass;

        numVals = 0;
        for (i = 0; i < 16; i++) {
            numVals += *info->c++;
        }
        info->huffmanTabs[tabIndex].bits = bits;
        info->huffmanTabs[tabIndex].vals = info->c;
        info->huffmanTabs[tabIndex].numVals = numVals;
        for (i = 0; i < numVals; i++) {
            info->c++;
        }

        if ((err = fn_8003A4E8(info, tabIndex, bits)) != 0) {
            return err;
        }
        if ((err = fn_8003A680(info, tabIndex)) != 0) {
            return err;
        }
        fn_8003A760(info, tabIndex);
        length -= numVals + 17;
        info->validHuffmanTabs |= 1 << tabIndex;
    } while (length);

    return 0;
}
