#include "types.h"

typedef enum {
    Sig_TRKTargetInterrupt_NUBEVENT_Null = 0,
    Sig_TRKTargetInterrupt_NUBEVENT_Shutdown = 1,
    Sig_TRKTargetInterrupt_NUBEVENT_Request = 2,
    Sig_TRKTargetInterrupt_NUBEVENT_Breakpoint = 3,
    Sig_TRKTargetInterrupt_NUBEVENT_Exception = 4,
    Sig_TRKTargetInterrupt_NUBEVENT_Support = 5,
} Sig_TRKTargetInterrupt_NubEventType;

typedef struct Sig_TRKTargetInterrupt_TRKEvent {
    Sig_TRKTargetInterrupt_NubEventType eventType;
    u32 eventID;
    s32 msgBufID;
} Sig_TRKTargetInterrupt_TRKEvent;

struct TRKTargetInterrupt_lbl_8015B884 {
    s32 unk_0;
    s32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
};
struct TRKTargetInterrupt_gTRKCPUState {
    u8 pad_0[0x80];
    u32 unk_80;
    u8 pad_84[0x174];
    u32 unk_1F8;
    u8 pad_1FC[0xFC];
    u32 unk_2F8;
};
struct TRKTargetInterrupt_gTRKState {
    u8 pad_0[0x98];
    u32 unk_98;
};

extern s32 fn_8008AF58(s32);
extern struct TRKTargetInterrupt_gTRKCPUState gTRKCPUState;
extern struct TRKTargetInterrupt_gTRKState gTRKState;
extern struct TRKTargetInterrupt_lbl_8015B884 lbl_8015B884;
extern u32 lbl_80095BA8[];
extern u32 MWTRACE(u32, ...);

s32 TRKTargetInterrupt(Sig_TRKTargetInterrupt_TRKEvent * arg0) {
    struct TRKTargetInterrupt_gTRKCPUState *p_gTRKCPUState;
    s32 v0;
    s32 v1;
    s32 v3;

    v0 = 0;
    switch (arg0->eventType) {
    case Sig_TRKTargetInterrupt_NUBEVENT_Breakpoint:
    case Sig_TRKTargetInterrupt_NUBEVENT_Exception:
        if (lbl_8015B884.unk_0 != 0) {
            p_gTRKCPUState = (struct TRKTargetInterrupt_gTRKCPUState *)&gTRKCPUState;
            p_gTRKCPUState->unk_1F8 = p_gTRKCPUState->unk_1F8 & ~0x400;
            v1 = 1;
            if (lbl_8015B884.unk_0 != 0 && (p_gTRKCPUState->unk_2F8 & 0xFFFF) == 0xD00) {
                switch (lbl_8015B884.unk_4) {
                case 0:
                    if (lbl_8015B884.unk_8 != 0) {
                        v1 = 0;
                    }
                    break;
                case 1:
                    if (p_gTRKCPUState->unk_80 >= lbl_8015B884.unk_C &&
                        p_gTRKCPUState->unk_80 <= lbl_8015B884.unk_10) {
                        v1 = 0;
                    }
                    break;
                }
            }
            if (v1 != 0) {
                lbl_8015B884.unk_0 = 0;
            } else {
                lbl_8015B884.unk_0 = 1;
                MWTRACE(1, (u32)&lbl_80095BA8);
                v3 = lbl_8015B884.unk_4;
                p_gTRKCPUState->unk_1F8 = p_gTRKCPUState->unk_1F8 | 0x400;
                if (v3 == 0 || v3 == 16) {
                    lbl_8015B884.unk_8--;
                }
                gTRKState.unk_98 = 0;
            }
        }
        if (lbl_8015B884.unk_0 == 0) {
            gTRKState.unk_98 = 1;
            v0 = fn_8008AF58(0x90);
        }
        break;
    }
    return v0;
}
