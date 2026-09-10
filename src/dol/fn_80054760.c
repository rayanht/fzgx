
#include "types.h"

typedef enum CvFsStatus {
    CVFS_STATUS_IDLE = 0,
    CVFS_STATUS_COMPLETE = 1,
    CVFS_STATUS_TRANSFERRING = 2,
    CVFS_STATUS_ERROR = 3
} CvFsStatus;

typedef struct CvFsInterface CvFsInterface;

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

typedef struct CvFsDevice {
    CvFsInterface *interface;
    char name[9];
} CvFsDevice;

extern CvFsDevice lbl_80187574[32];

void fn_80054760(void) {
    int i;
    CvFsInterface *interface;
    for (i = 0; i < 32; i++) {
        interface = lbl_80187574[i].interface;
        if (interface != ((void *)0) && interface->ExecServer != ((void *)0)) {
            interface->ExecServer();
        }
    }
}
