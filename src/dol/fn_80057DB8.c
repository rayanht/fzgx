#include "types.h"

typedef struct Fn80057DB8Object Fn80057DB8Object;
typedef void (*Fn80057DB8Callback)(void *, int);

struct Fn80057DB8Object {
    u8 pad_0x00[0x0c];
    int value_0c;
    int value_10;
    int value_14;
    int value_18;
    u8 pad_0x1c[0x04];
    int value_20;
    int value_24;
    u8 pad_0x28[0x10];
    Fn80057DB8Callback callback_38;
    void *callback_arg_3c;
};

extern void fn_80057728(Fn80057DB8Object *, int, int, int *);
extern void fn_800576DC(void);

int fn_80057DB8(Fn80057DB8Object *object, int mode, int limit, int *result) {
    int value;
    int clamped;

    fn_80057728(object, mode, limit, result);
    if (mode == 0) {
        value = object->value_24;
        value += object->value_20 - object->value_14;
        if (object->value_10 < value) {
            value = object->value_10;
        }
        clamped = limit;
        if (value < limit) {
            clamped = value;
        }
        mode = clamped;
    } else if (mode == 1) {
        value = object->value_24;
        value += object->value_20 - object->value_18;
        if (object->value_0c < value) {
            value = object->value_0c;
        }
        clamped = limit;
        if (value < limit) {
            clamped = value;
        }
        mode = clamped;
    } else {
        mode = 0;
        if (object->callback_38 != 0) {
            object->callback_38(object->callback_arg_3c, -3);
        }
    }
    *result = mode;
    fn_800576DC();
    return !(limit - mode);
}
