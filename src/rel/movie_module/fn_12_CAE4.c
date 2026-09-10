#include "types.h"

typedef s32 MovieCallback;

typedef struct MovieObject {
    u8 pad_0000[0x188];
    s32 state;
    u8 pad_018c[4];
    MovieCallback callbacks[1];
} MovieObject;

typedef struct MovieManager {
    u8 pad_0000[0x54];
    s32 count;
    MovieObject *objects;
} MovieManager;

extern void fn_12_CBC4(void);
extern u32 lbl_12_bss_528C[25];
extern u32 lbl_12_bss_5280[3];
extern s32 fn_12_A660(s32, s32);

s32 fn_12_CAE4(MovieObject *movie, s32 index, MovieCallback callback) {
    MovieCallback *callbacks = 0;
    MovieManager *manager;
    s32 count;
    MovieObject *object;
    s32 i;
    s32 result;
    MovieCallback value;

    value = callback;
    if (index == 8 && callback == 0) {
        value = (s32)fn_12_CBC4;
    }
    if (movie == 0) {
        manager = (MovieManager *)lbl_12_bss_528C;
        count = manager->count;
        object = manager->objects;
        for (i = 0; i < count; i++) {
            if (object->state == 2) {
                object->callbacks[index] = value;
            }
            object = (MovieObject *)((u8 *)object + 0x2000);
        }
        callbacks = (MovieCallback *)lbl_12_bss_528C;
    } else {
        lbl_12_bss_5280[0] = (u32)movie;
        if (movie == 0) {
            result = -1;
        } else if (movie->state != 2) {
            result = -1;
        } else {
            result = 0;
        }
        if (result != 0) {
            return fn_12_A660(0, 0xff030202);
        }
        callbacks = movie->callbacks;
    }
    callbacks[index] = value;
    return 0;
}
