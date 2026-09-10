#include "types.h"

struct fn_8003B8A8___table_T {
    u8 pad_0[0x10];
    u32 unk_10;
    s32 unk_14[0x12];
    u32 unk_5c[0x13];
};

struct fn_8003B8A8___root_T {
    u8 pad_0[0x420];
    struct fn_8003B8A8___table_T table[0x100];
};

extern s32 fn_8003D42C(void *);

u8 fn_8003B8A8(struct fn_8003B8A8___root_T *self, u8 index) {
    struct fn_8003B8A8___table_T *table;
    s32 value;
    u32 i;

    table = &self->table[index];
    i = 1;
    value = fn_8003D42C(self);
    while (value > table->unk_14[i]) {
        value <<= 1;
        value |= fn_8003D42C(self);
        i++;
    }
    return ((u8 *)(value + table->unk_5c[i]))[table->unk_10];
}
