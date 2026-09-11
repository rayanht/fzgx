#include "types.h"

typedef struct Fn800647F0Object {
    u8 _pad0[0x14];
    u32 value;
} Fn800647F0Object;

typedef struct Fn800647F0Entry {
    u8 unk_0;
    u8 unk_1;
    u8 _pad2[7];
    u8 unk_9;
    u8 unk_a;
    u8 _padb[0xd];
    u32 unk_18;
    u32 _pad1c;
    u32 _pad20;
    u32 unk_24;
    u32 _pad28;
    u32 unk_2c;
    u8 unk_30[0xe8];
} Fn800647F0Entry;

typedef struct Fn800647F0Data {
    u8 _pad0[0x1408];
    Fn800647F0Entry entries[0x40];
} Fn800647F0Data;

extern Fn800647F0Data *lbl_801A6C80;
extern void fn_80060BDC(u32 value);
extern void fn_80028424(void *value);

s32 fn_800647F0(Fn800647F0Object *object) {
    u8 i;

    i = 0;
    while (i < 0x40) {
        if (lbl_801A6C80->entries[i].unk_24 == object->value &&
            lbl_801A6C80->entries[i].unk_0 != 0xff) {
            if (lbl_801A6C80->entries[i].unk_0 == 3) {
                fn_80060BDC(i);
            } else {
                fn_80028424(lbl_801A6C80->entries[i].unk_30);
            }
            lbl_801A6C80->entries[i].unk_2c = 0;
            lbl_801A6C80->entries[i].unk_0 = 0xff;
            lbl_801A6C80->entries[i].unk_18 = 0;
            lbl_801A6C80->entries[i].unk_1 = 0;
            if (lbl_801A6C80->entries[i].unk_9 != 0xff ||
                lbl_801A6C80->entries[i].unk_a != 0xff) {
                if (lbl_801A6C80->entries[i].unk_9 == i) {
                    lbl_801A6C80->entries[lbl_801A6C80->entries[i].unk_a].unk_9 =
                        0xff;
                    lbl_801A6C80->entries[lbl_801A6C80->entries[i].unk_a].unk_a =
                        0xff;
                } else if (lbl_801A6C80->entries[i].unk_a == i) {
                    lbl_801A6C80->entries[lbl_801A6C80->entries[i].unk_9].unk_9 =
                        0xff;
                    lbl_801A6C80->entries[lbl_801A6C80->entries[i].unk_9].unk_a =
                        0xff;
                }
            }
            lbl_801A6C80->entries[i].unk_9 = 0xff;
            lbl_801A6C80->entries[i].unk_a = 0xff;
            break;
        }
        i++;
    }
    return 0;
}
