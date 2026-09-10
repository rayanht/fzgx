
#include "types.h"

enum {
    DS_NoError = 0x0,
    DS_StepError = 0x1,
    DS_ParameterError = 0x2,
    DS_EventQueueFull = 0x100,
    DS_NoMessageBufferAvailable = 0x300,
    DS_MessageBufferOverflow = 0x301,
    DS_MessageBufferReadError = 0x302,
    DS_DispatchError = 0x500,
    DS_InvalidMemory = 0x700,
    DS_InvalidRegister = 0x701,
    DS_CWDSException = 0x702,
    DS_UnsupportedError = 0x703,
    DS_InvalidProcessID = 0x704,
    DS_InvalidThreadID = 0x705,
    DS_OSError = 0x706,
    DS_Error800 = 0x800,
};

typedef int DSError;

typedef struct TRKBuffer {
    u32 mutex;
    BOOL isInUse;
    u32 length;
    u32 position;
    u8 data[(0x800 + 0x80)];
} TRKBuffer;

DSError TRKAppendBuffer(TRKBuffer *msg, const void *data, size_t length);

DSError TRKAppendBuffer1_ui32(TRKBuffer *buffer, const u32 data);

extern BOOL gTRKBigEndian;

void *fn_800035C0(void *dst, const void *src, size_t n);

static inline DSError TRKAppendBuffer(TRKBuffer *msg, const void *data, size_t length) {
    DSError error = DS_NoError;
    u32 bytesLeft;
    if (length == 0) {
        return DS_NoError;
    }
    bytesLeft = 0x880 - msg->position;
    if (bytesLeft < length) {
        error = DS_MessageBufferOverflow;
        length = bytesLeft;
    }
    if (length == 1) {
        msg->data[msg->position] = ((u8 *)data)[0];
    } else {
        fn_800035C0(msg->data + msg->position, data, length);
    }
    msg->position += length;
    msg->length = msg->position;
    return error;
}

static inline DSError TRKAppendBuffer1_ui32(TRKBuffer *buffer, const u32 data) {
    u8 *bigEndianData;
    u8 *byteData;
    u8 swapBuffer[sizeof(data)];
    if (gTRKBigEndian) {
        bigEndianData = (u8 *)&data;
    } else {
        byteData = (u8 *)&data;
        bigEndianData = swapBuffer;
        bigEndianData[0] = byteData[3];
        bigEndianData[1] = byteData[2];
        bigEndianData[2] = byteData[1];
        bigEndianData[3] = byteData[0];
    }
    return TRKAppendBuffer(buffer, (const void *)bigEndianData, sizeof(data));
}

DSError fn_80088DB4(TRKBuffer *buffer, const u32 *data, int count) {
    DSError err;
    int i;
    for (i = 0, err = DS_NoError; err == DS_NoError && i < count; i++) {
        err = TRKAppendBuffer1_ui32(buffer, data[i]);
    }
    return err;
}
