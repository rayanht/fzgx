#include "types.h"

typedef struct Fn800692A4_Voice {
    u8 active;
    u8 flags;
    u8 channel;
    u8 pad_3[0x25];
} Fn800692A4_Voice;

typedef struct Fn800692A4_State {
    u8 pad_0[0x1188];
    Fn800692A4_Voice voices[16];
} Fn800692A4_State;

extern Fn800692A4_State *lbl_801A6C80;

void fn_800692A4(u32 message) {
    u32 all;
    u32 channel;
    u8 i;

    if ((message & 0xFF00) > 0x1900) {
        return;
    }
    channel = message & 0xF;
    all = message & 0x80;
    switch (message & ~0xFF) {
    case 0xA0000100:
        for (i = 0; i < 16; i++) {
            if (all == 0) {
                lbl_801A6C80->voices[i].active = 0;
            } else if (channel == lbl_801A6C80->voices[i].channel) {
                if (lbl_801A6C80->voices[i].flags & 0x80) {
                    lbl_801A6C80->voices[i].active = 0;
                }
            } else {
                lbl_801A6C80->voices[i].active = 0;
            }
        }
        break;
    case 0xA0000200:
        for (i = 0; i < 16; i++) {
            if (!(lbl_801A6C80->voices[i].flags & 0x80)) {
                if (all == 0) {
                    lbl_801A6C80->voices[i].active = 0;
                } else if (channel != lbl_801A6C80->voices[i].channel) {
                    lbl_801A6C80->voices[i].active = 0;
                }
            }
        }
        break;
    case 0xA0000300:
        for (i = 0; i < 16; i++) {
            if (lbl_801A6C80->voices[i].flags & 0x80) {
                lbl_801A6C80->voices[i].active = 0;
            }
        }
        break;
    case 0xA0001100:
        for (i = 0; i < 16; i++) {
            if (channel == lbl_801A6C80->voices[i].channel) {
                if (all == 0) {
                    lbl_801A6C80->voices[i].active = 0;
                } else if (lbl_801A6C80->voices[i].flags & 0x80) {
                    lbl_801A6C80->voices[i].active = 0;
                }
            }
        }
        break;
    case 0xA0001200:
        if (all == 0) {
            for (i = 0; i < 16; i++) {
                if (channel == lbl_801A6C80->voices[i].channel && !(lbl_801A6C80->voices[i].flags & 0x80)) {
                    lbl_801A6C80->voices[i].active = 0;
                }
            }
        }
        break;
    case 0xA0001300:
        for (i = 0; i < 16; i++) {
            if (channel == lbl_801A6C80->voices[i].channel && (lbl_801A6C80->voices[i].flags & 0x80)) {
                lbl_801A6C80->voices[i].active = 0;
            }
        }
        break;
    }
}
