#include "types.h"
#include "sofdec/mwsst.h"

extern MwsStManager lbl_12_data_E90;

static inline int mwsst_IsValid(const MwsStHandle *handle) {
    if (lbl_12_data_E90.interface == 0) {
        return 0;
    }
    if (handle->active != 1) {
        return 0;
    }
    if (handle->backend == 0) {
        return 0;
    }
    return 1;
}

void MWSST_Pause(MwsStHandle *handle, int paused) {
    if (mwsst_IsValid(handle) == 1) {
        void *backend = handle->backend;
        if (lbl_12_data_E90.interface != 0 && lbl_12_data_E90.interface->pause != 0) {
            lbl_12_data_E90.interface->pause(backend, paused);
        }
    }
}
