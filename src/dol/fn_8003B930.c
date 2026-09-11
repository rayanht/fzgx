#include "types.h"

typedef struct Fn8003B930Data {
    u8 pad_10[0x10];
    u32 field_10;
    u8 pad_14[0x48];
    u32 field_5c[];
} Fn8003B930Data;

extern int fn_8003D42C();

u8 fn_8003B930(int value, Fn8003B930Data* data) {
    u8* cursor;
    int result;
    int index;
    index = 1;
    result = fn_8003D42C(value);
    cursor = (u8*)data + 4;

    while (result > *(int*)(cursor + 0x14)) {
        result <<= 1;
        result |= fn_8003D42C(value);
        cursor += 4;
        index += 1;
    }
    return *(u8*)((((result) + (data->field_5c[index])) + (data->field_10)));
}
