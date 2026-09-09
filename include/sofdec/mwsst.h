#ifndef SOFDEC_MWSST_H
#define SOFDEC_MWSST_H

#include "types.h"
#include "sofdec/sj.h"

typedef struct MwsStHandle MwsStHandle;

typedef struct MwsStManagerInterface {
    void *reserved_00;
    void (*finish)(void);
    void *reserved_08[2];
    void (*destroy)(MwsStHandle *handle);
    void (*start_sj)(void *backend, SJ *stream);
    void (*stop)(void *backend);
    int (*get_status)(void *backend);
    void *reserved_20;
    void (*pause)(void *backend, int paused);
    void (*set_volume)(void *backend, int volume);
    int (*get_volume)(void *backend);
} MwsStManagerInterface;

struct MwsStHandle {
    int active;
    unsigned char reserved_04[8];
    SJ *stream;
    int element_id;
    void *backend;
};

typedef struct MwsStManager {
    MwsStManagerInterface *interface;
    int active_count;
} MwsStManager;

void MWSST_Pause(MwsStHandle* handle, int paused);
int MWSST_GetStat(MwsStHandle* handle);
void MWSST_StartSj(MwsStHandle* handle);

#endif
