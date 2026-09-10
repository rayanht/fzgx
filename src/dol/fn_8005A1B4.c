
#include "types.h"

typedef enum MfCiStatus {
    MFCI_STATUS_IDLE = 0,
    MFCI_STATUS_COMPLETE = 1,
    MFCI_STATUS_TRANSFERRING = 2
} MfCiStatus;

typedef struct MfCiObject {
    signed char used;
    signed char status;
    unsigned char reserved_02[2];
    int sector_length;
    int file_size;
    int sector_count;
    int sector_position;
    int transfer_length;
    int request_sectors;
    char filename[20];
    int source_offset;
    int request_length;
} MfCiObject;

typedef void (*MfCiErrorCallback)(void *object, const char *message, void *handle);

void fn_80059B44(void);

void fn_80059AB4(void);

void *memset(void *destination, int value, unsigned long size);

void mfCiStopTr(void *object);

extern MfCiErrorCallback lbl_80190178;

extern void *lbl_8019017C;

static inline void mfCiStopTr(void *object) {
    MfCiObject *handle = (MfCiObject *)object;
    if (handle == 0) {
        if (lbl_80190178 != 0) {
            lbl_80190178(lbl_8019017C, "E0092912:handl is null.", 0);
        }
        return;
    }
    fn_80059B44();
    handle->status = MFCI_STATUS_IDLE;
    fn_80059AB4();
}

void fn_8005A1B4(void *object) {
    MfCiObject *handle = (MfCiObject *)object;
    if (handle != 0) {
        mfCiStopTr(handle);
        if (handle->used == 1) {
            handle->used = 0;
            memset(handle, 0, sizeof(*handle));
        }
    }
}
