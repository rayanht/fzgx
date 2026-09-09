#include "types.h"

typedef struct {
    u32 unk_0;
    u8 pad_4[4];
    u32 unk_8;
    u8 pad_C[0x2C];
    u32 unk_38;
    u8 pad_3C[0x10];
} Fn800542C8;

extern void fn_800504BC(u32);
extern void fn_8005174C(u32);
extern u32 memset(u32, u32, u32);
extern u32 lbl_801873EC[];

void fn_800542C8(Fn800542C8 *obj) {
    u32 index;
    u32 value;

    if (obj != 0) {
        value = obj->unk_8;
        index = obj->unk_38;
        if (value != 0) {
            obj->unk_8 = 0;
            fn_800504BC(value);
        }
        value = obj->unk_0;
        if (value != 0) {
            obj->unk_0 = 0;
            fn_8005174C(value);
        }
        memset((u32)obj, 0, 0x4C);
        lbl_801873EC[index] = 0;
    }
}
