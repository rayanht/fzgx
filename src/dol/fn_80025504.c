#include "types.h"

typedef struct fn_80025504_BufferUpdate {
    s32 *left;
    s32 *right;
    s32 *surround;
} fn_80025504_BufferUpdate;

typedef struct fn_80025504_SrcInfo {
    s32 *dest;
    s32 *smpBase;
    s32 *old;
    u32 posLo;
    u32 posHi;
    u32 pitchLo;
    u32 pitchHi;
    u32 trigger;
    u32 target;
} fn_80025504_SrcInfo;

typedef struct fn_80025504_Chorus {
    s32 *lastLeft[3];
    s32 *lastRight[3];
    s32 *lastSur[3];
    u8 currentLast;
    s32 oldLeft[4];
    s32 oldRight[4];
    s32 oldSur[4];
    u32 currentPosLo;
    u32 currentPosHi;
    s32 pitchOffset;
    u32 pitchOffsetPeriodCount;
    u32 pitchOffsetPeriod;
    fn_80025504_SrcInfo src;
    u32 baseDelay;
    u32 variation;
    u32 period;
} fn_80025504_Chorus;

extern void fn_80024E6C(fn_80025504_SrcInfo *src);
extern void fn_80025004(fn_80025504_SrcInfo *src);

void fn_80025504(fn_80025504_BufferUpdate *bufferUpdate, fn_80025504_Chorus *chorus) {
    s32 *leftD;
    s32 *rightD;
    s32 *surD;
    s32 *leftS;
    s32 *rightS;
    s32 *surS;
    u32 i;
    u8 nextCurrentLast;

    nextCurrentLast = (chorus->currentLast + 1) % 3;
    leftD = chorus->lastLeft[nextCurrentLast];
    rightD = chorus->lastRight[nextCurrentLast];
    surD = chorus->lastSur[nextCurrentLast];
    leftS = bufferUpdate->left;
    rightS = bufferUpdate->right;
    surS = bufferUpdate->surround;
    for (i = 0; i < 160; i++) {
        *leftD++ = *leftS++;
        *rightD++ = *rightS++;
        *surD++ = *surS++;
    }
    chorus->src.pitchHi = (chorus->pitchOffset >> 16) + 1;
    chorus->src.pitchLo = (chorus->pitchOffset & 0xFFFF) << 16;
    if (--chorus->pitchOffsetPeriodCount == 0) {
        chorus->pitchOffsetPeriodCount = chorus->pitchOffsetPeriod;
        chorus->pitchOffset = -chorus->pitchOffset;
    }
    for (i = 0; i < 3; i++) {
        chorus->src.posHi = chorus->currentPosHi;
        chorus->src.posLo = chorus->currentPosLo;
        switch (i) {
        case 0:
            chorus->src.smpBase = chorus->lastLeft[0];
            chorus->src.dest = bufferUpdate->left;
            chorus->src.old = &chorus->oldLeft[0];
            break;
        case 1:
            chorus->src.smpBase = chorus->lastRight[0];
            chorus->src.dest = bufferUpdate->right;
            chorus->src.old = &chorus->oldRight[0];
            break;
        case 2:
            chorus->src.smpBase = chorus->lastSur[0];
            chorus->src.dest = bufferUpdate->surround;
            chorus->src.old = &chorus->oldSur[0];
            break;
        }
        switch (chorus->src.pitchHi) {
        case 0:
            fn_80024E6C(&chorus->src);
            break;
        case 1:
            fn_80025004(&chorus->src);
            break;
        }
    }
    chorus->currentPosHi = chorus->src.posHi % 480;
    chorus->currentPosLo = chorus->src.posLo;
    chorus->currentLast = nextCurrentLast;
}
