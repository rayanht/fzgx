
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

DSError TRKAppendBuffer1_ui8(TRKBuffer *buffer, const u8 data);

static inline DSError TRKAppendBuffer1_ui8(TRKBuffer *buffer, const u8 data) {
    if (buffer->position >= (0x800 + 0x80)) {
        return DS_MessageBufferOverflow;
    }
    buffer->data[buffer->position++] = data;
    buffer->length++;
    return DS_NoError;
}

DSError TRKAppendBuffer_ui8(TRKBuffer *buffer, const u8 *data, int count) {
    DSError err;
    int i;
    for (i = 0, err = DS_NoError; err == DS_NoError && i < count; i++) {
        err = TRKAppendBuffer1_ui8(buffer, data[i]);
    }
    return err;
}
