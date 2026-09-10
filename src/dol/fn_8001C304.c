#include <types.h>

typedef struct PADStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

u32 SIGetType(s32 chan);

extern u32 lbl_801A64B8;

extern u32 lbl_801A64BC;

extern PADStatus lbl_8015D0C0[4];

void fn_8001C304(s32 chan) {
    PADStatus *origin;
    u32 chanBit = 0x80000000 >> chan;
    origin = &lbl_8015D0C0[chan];
    switch (lbl_801A64BC & 0x00000700u) {
    case 0x00000000u:
    case 0x00000500u:
    case 0x00000600u:
    case 0x00000700u:
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000100u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000200u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        break;
    case 0x00000300u:
        break;
    case 0x00000400u:
        break;
    }
    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;
    if (lbl_801A64B8 & chanBit) {
        if (64 < origin->stickX && (SIGetType(chan) & 0xffff0000) == (0x08000000u | 0x01000000)) {
            origin->stickX = 0;
        }
    }
}
