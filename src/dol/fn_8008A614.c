#include "types.h"

extern void *memset(void *dest, int value, u32 size);
extern void fn_8008D398(void *data, u32 size);
extern void fn_80005518(void);

typedef struct InitData {
    u32 size;
    u8 type;
    u8 padding0[3];
    u8 flag;
    u8 padding1[0x3b];
} InitData;

int fn_8008A614(void) {

{
    InitData data;
    memset(&data, 0, 0x40);
    data.type = 0x80;
    data.size = 0x40;
    data.flag = 0;
    fn_8008D398(&data, 0x40);
}
    fn_80005518();
    return 0;
}
