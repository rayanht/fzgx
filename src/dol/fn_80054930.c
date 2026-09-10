
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
    void (*ExecServer)(void);
    void (*EntryErrFunc)(CvFsErrorCallback callback, void *object);
    int (*GetFileSize)(const char *filename);
    int (*GetFreeSize)(void);
    void *(*Open)(const char *filename, void *parameter, int mode);
    void (*Close)(void *object);
    int (*Seek)(void *object, int offset, int origin);
    int (*Tell)(void *object);
    int (*ReqRd)(void *object, int sectors, void *buffer);
    int (*ReqWr)(void *object, int sectors, void *buffer);
    void (*StopTr)(void *object);
    CvFsStatus (*GetStat)(void *object);
    int (*GetSctLen)(void *object);
    void (*SetSctLen)(void *object, int sector_length);
    int (*GetNumTr)(void *object);
    int (*ChangeDir)(const char *dirname);
    int (*IsExistFile)(const char *filename);
    int (*GetNumFiles)(void);
    int (*LoadDirInfo)(const char *dirname, void *info, int count);
    int (*GetMaxByteRate)(void *object);
    int (*MakeDir)(const char *dirname);
    int (*RemoveDir)(const char *dirname);
    int (*DeleteFile)(const char *filename);
    int (*GetFileSizeEx)(const char *filename, void *parameter);
    int (*OptFn1)(void *object, int operation, int arg2, int arg3);
    int (*OptFn2)(void *object, int arg1, int arg2, int arg3);
};

struct CvFsObject {
    CvFsInterface *interface;
    void *object;
};

extern const char lbl_80091D20[28];

extern const char lbl_80091D3C[24];

extern CvFsErrorCallback lbl_80187430;

extern void *lbl_80187434;

static inline void cvFsError(const char *message) {
    if (lbl_80187430 != ((void *)0)) {
        lbl_80187430(lbl_80187434, message, ((void *)0));
    }
}

int fn_80054930(CvFsObject *handle, int offset, int origin) {
    int result;
    if (handle == ((void *)0)) {
        cvFsError(lbl_80091D20);
        return 0;
    }
    if (handle->interface->Seek != ((void *)0)) {
        result = handle->interface->Seek(handle->object, offset, origin);
    } else {
        result = 0;
        cvFsError(lbl_80091D3C);
    }
    return result;
}
