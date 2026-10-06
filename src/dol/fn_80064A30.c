#include "types.h"

typedef struct Fn80064A30_Sample {
    u8 pad_0[0x6];
    u8 flags;
    u8 pad_7[0xE];
    u8 looped;
} Fn80064A30_Sample;

typedef struct Fn80064A30_Voice {
    u8 state;
    u8 mode;
    u8 channel;
    u8 flags;
    u8 pad_4[0x14];
    u32 group;
    Fn80064A30_Sample *sample;
    u8 pad_20[0xF8];
} Fn80064A30_Voice;

typedef struct Fn80064A30_Channel {
    u8 pad_0[0x1A];
    u8 sustain;
    u8 pad_1B[0x5];
} Fn80064A30_Channel;

typedef struct Fn80064A30_Synth {
    u8 pad_0[0x444];
    u32 group;
    u8 pad_448[0x138];
    Fn80064A30_Channel channels[16];
    u8 pad_780[0xC88];
    Fn80064A30_Voice voices[64];
} Fn80064A30_Synth;

extern Fn80064A30_Synth *lbl_801A6C80;
extern void fn_8005FBDC(u32 voice);
extern void fn_8005C9D8(u32 voice);
extern void fn_8005FCD8(u32 voice);
extern void fn_8005C478(u32 voice);
extern void fn_8005C298(u32 voice, s32 arg);
extern void fn_8005C7C0(u32 voice);
extern void fn_8005C5C8(u32 voice);

void fn_80064A30(u16 event, u32 mask) {
    u32 i;

    for (i = 0; i < 64; i++) {
        if (lbl_801A6C80->voices[i].state == 0xFF) {
            continue;
        }
        if (lbl_801A6C80->voices[i].state == 3) {
            continue;
        }
        if (lbl_801A6C80->voices[i].state == 4) {
            continue;
        }
        if ((lbl_801A6C80->group & mask) != (lbl_801A6C80->voices[i].group & mask)) {
            continue;
        }
        switch (event) {
        case 0x8000:
            if (lbl_801A6C80->voices[i].mode == 1 && (lbl_801A6C80->voices[i].flags & 8) != 8) {
                if (lbl_801A6C80->voices[i].flags & 1) {
                    lbl_801A6C80->voices[i].flags |= 2;
                } else {
                    fn_8005FBDC(i);
                }
            }
            break;
        case 0xA001:
        case 0xA004:
        case 0xA005:
        case 0xA010:
        case 0xA011:
        case 0xA034:
        case 0xA040:
            fn_8005C9D8(i);
            break;
        case 0xA002:
            if (lbl_801A6C80->voices[i].state == 1) {
                fn_8005FCD8(i);
            }
            break;
        case 0xA007:
            fn_8005C478(i);
            break;
        case 0xA01C:
            if (lbl_801A6C80->voices[i].state == 1) {
                fn_8005C9D8(i);
            }
            break;
        case 0xB001:
            fn_8005C298(i, 1);
            break;
        case 0xB002:
            fn_8005C298(i, 2);
            break;
        case 0xB007:
            fn_8005C9D8(i);
            break;
        case 0xB00A:
            if (lbl_801A6C80->voices[i].sample->flags & 0x80) {
                fn_8005C7C0(i);
            }
            break;
        case 0xB00D:
            if (lbl_801A6C80->voices[i].sample->looped != 0) {
                fn_8005C5C8(i);
            }
            break;
        case 0xB040:
            lbl_801A6C80->voices[i].flags &= ~1;
            if (lbl_801A6C80->channels[lbl_801A6C80->voices[i].channel].sustain != 0) {
                lbl_801A6C80->voices[i].flags |= 1;
            } else if (lbl_801A6C80->voices[i].flags & 2) {
                fn_8005FBDC(i);
            }
            break;
        case 0xB078:
            if ((lbl_801A6C80->voices[i].group & 0x0F000000) == (lbl_801A6C80->group & 0x0F000000)) {
                fn_8005FCD8(i);
            }
            break;
        case 0xE000:
            fn_8005C478(i);
            break;
        }
    }
}
