#include "types.h"

typedef struct Fn800674FC_State {
    u8 pad_0[0x240];
    u32 queue[64];
    u8 pad_340[0x101];
    u8 count;
    u8 pad_442[0x1];
    u8 head;
    u8 pad_444[0x20];
    s8 busy;
    u8 pad_465[0x55AD];
    s16 unk_5A12;
    u8 pad_5A14[0xA0];
    s16 unk_5AB4[16];
    s16 unk_5AD4[16];
} Fn800674FC_State;

extern Fn800674FC_State *lbl_801A6C80;
extern BOOL lbl_801A6C78;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);

s32 fn_800674FC(u32 id, s32 command, s16 value) {
    s32 result;
    u32 message;
    s32 i;
    u16 port;

    port = id;
    message = (id & 0x1F) + command;
    if (command & 0x00FF0000) {
        switch (command) {
        case 0xA0010000:
        case 0xA0040000:
        case 0xA0090000:
        case 0xA00A0000:
        case 0xA0100000:
        case 0xA0190000:
        case 0xA01C0000:
            message += (value & 0x7F) << 8;
            break;
        case 0xA0050000:
        case 0xA0070000:
        case 0xA0110000:
            message += ((value + 0x40) & 0x7F) << 8;
            break;
        case 0xA0280000:
        case 0xA0290000:
            message += ((value - 1) & 0xF) << 8;
            break;
        case 0xA0310000:
            lbl_801A6C80->unk_5A12 = value;
            break;
        case 0xA0340000:
            if (port & 0x10) {
                for (i = 0; i < 16; i++) {
                    lbl_801A6C80->unk_5AB4[i] = value;
                }
            } else {
                lbl_801A6C80->unk_5AB4[(u16)id] = value;
            }
            break;
        case 0xA0400000:
            if (port & 0x10) {
                for (i = 0; i < 16; i++) {
                    lbl_801A6C80->unk_5AD4[i] = value;
                }
            } else {
                lbl_801A6C80->unk_5AD4[(u16)id] = value;
            }
            break;
        case 0xA0020000:
        case 0xA0030000:
            break;
        default:
            return -2;
        }
    }

    result = 0;
    if (lbl_801A6C80->busy) {
        result = -3;
    } else {
        lbl_801A6C80->busy = -1;
        if (!(message & 0x80000000)) {
            result = -2;
        } else {
            lbl_801A6C78 = OSDisableInterrupts();
            if (lbl_801A6C80->count < 64 && lbl_801A6C80->queue[lbl_801A6C80->head] == 0) {
                lbl_801A6C80->queue[lbl_801A6C80->head] = message;
                lbl_801A6C80->head = (lbl_801A6C80->head + 1) & 0x3F;
                lbl_801A6C80->count++;
            } else {
                result = -1;
            }
            OSRestoreInterrupts(lbl_801A6C78);
        }
        lbl_801A6C80->busy = 0;
    }
    return result;
}
