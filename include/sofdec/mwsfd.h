#ifndef SOFDEC_MWSFD_H
#define SOFDEC_MWSFD_H

#include "sofdec/mwsst.h"

/* GX layout: name only fields used by recovered player routines. */
typedef struct SfdHandle SfdHandle;

typedef struct MwsPlayer {
    u8 unknown_000[0x0c];
    int playback_mode;
    u8 unknown_010[0x30];
    SfdHandle *sfd;
    u8 unknown_044[0x2e];
    s8 paused;
    u8 unknown_073[0x179];
    MwsStHandle sound;
} MwsPlayer;

void mwSfdPause(MwsPlayer* player, int paused);

#endif
