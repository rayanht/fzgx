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

typedef struct PADClampRegion {
    u8 minTrigger;
    u8 maxTrigger;
    s8 minStick;
    s8 maxStick;
    s8 xyStick;
    s8 minSubstick;
    s8 maxSubstick;
    s8 xySubstick;
    s8 radStick;
    s8 radSubstick;
} PADClampRegion;

extern const PADClampRegion lbl_8008FF40;

void ClampStick(s8 *px, s8 *py, s8 max, s8 xy, s8 min);

static inline void ClampTrigger(u8 *trigger, u8 min, u8 max) {
    if (*trigger <= min) {
        *trigger = 0;
        return;
    } else {
        if (max < *trigger) {
            *trigger = max;
        }
        *trigger -= min;
    }
}

void PADClamp(PADStatus *status) {
    int i;
    for (i = 0; i < 4; i++, status++) {
        if (status->err != 0) {
            continue;
        }
        ClampStick(&status->stickX, &status->stickY, lbl_8008FF40.maxStick, lbl_8008FF40.xyStick,
                   lbl_8008FF40.minStick);
        ClampStick(&status->substickX, &status->substickY, lbl_8008FF40.maxSubstick,
                   lbl_8008FF40.xySubstick, lbl_8008FF40.minSubstick);
        ClampTrigger(&status->triggerLeft, lbl_8008FF40.minTrigger, lbl_8008FF40.maxTrigger);
        ClampTrigger(&status->triggerRight, lbl_8008FF40.minTrigger, lbl_8008FF40.maxTrigger);
    }
}
