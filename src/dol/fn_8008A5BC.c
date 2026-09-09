#include "types.h"

extern void *memset(void *dest, int value, u32 size);
extern void fn_8008D398(void *arg0, u32 arg1);
extern void fn_8008D028(void);

struct Fn8008A5BCData {
    u32 field0;
    u8 field4;
    u8 padding5[3];
    u8 field8;
    u8 padding9[0x38];
};

int fn_8008A5BC(void) {
    struct Fn8008A5BCData data;
    u32 size = 0x40;

    memset(&data, 0, size);
    data.field4 = 0x80;
    data.field0 = size;
    data.field8 = 0;
    fn_8008D398(&data, size);
    fn_8008D028();
    return 0;
}
