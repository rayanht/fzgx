
#include "types.h"

typedef enum CvFsStatus {
    CVFS_STATUS_IDLE = 0,
    CVFS_STATUS_COMPLETE = 1,
    CVFS_STATUS_TRANSFERRING = 2,
    CVFS_STATUS_ERROR = 3
} CvFsStatus;

typedef struct CvFsInterface CvFsInterface;

typedef struct CvFsObject CvFsObject;

typedef void (*CvFsErrorCallback)(void *object, const char *message, void *handle);

struct CvFsInterface {
    union {
        unsigned char padding_extent[104];
        struct {
            unsigned char padding_Seek[32];
            int (*Seek)(void *object, int offset, int origin);
        } view_Seek;
    } fields;
};

struct CvFsObject {
    union {
        unsigned char padding_extent[8];
        struct {
            CvFsInterface *interface;
        } view_interface;
        struct {
            unsigned char padding_object[4];
            void *object;
        } view_object;
    } fields;
};

extern const char lbl_80091CEC[28];

extern const char lbl_80091D08[24];

extern CvFsErrorCallback lbl_80187430;

extern void *lbl_80187434;

static inline void cvFsError(const char *message) {
    if (lbl_80187430 != ((void *)0)) {
        lbl_80187430(lbl_80187434, message, ((void *)0));
    }
}

int fn_80054870(CvFsObject *handle, int offset, int origin) {
    int result;
    if (handle == ((void *)0)) {
        cvFsError(lbl_80091CEC);
        return 0;
    }
    if (handle->fields.view_interface.interface->fields.view_Seek.Seek != ((void *)0)) {
        result = handle->fields.view_interface.interface->fields.view_Seek.Seek(
            handle->fields.view_object.object, offset, origin);
    } else {
        result = 0;
        cvFsError(lbl_80091D08);
    }
    return result;
}
