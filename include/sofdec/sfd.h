#ifndef SOFDEC_SFD_H
#define SOFDEC_SFD_H

#include "types.h"

/* GX views: fields beyond the recovered accesses remain unnamed. */
typedef struct SfdPlaybackSettings {
    u8 unknown_00[0x14];
    int frame_rate_code;
} SfdPlaybackSettings;

typedef struct SfdHandle {
    u8 unknown_0000[0x44];
    int field_0044;
    int playback_state;
    u8 unknown_004C[0x8C0];
    SfdPlaybackSettings playback_settings;
} SfdHandle;

typedef struct SfdLibraryWork {
    u8 unknown_0000[0x204];
    SfdHandle* handles[8];
} SfdLibraryWork;

typedef struct SfdTimerSummary {
    long long total;
    long long minimum;
    long long maximum;
    int count;
    u8 unknown_1C[4];
} SfdTimerSummary;

int SFD_IsSvrWait(void);
void SFTIM_GetTimeOneFrmVideo(SfdHandle* handle, int* value, int* scale);
void SFTMR_AddTsum(SfdTimerSummary* summary, long long elapsed);

#endif
