#include "types.h"

typedef struct MovieVTable MovieVTable;
typedef struct Movie Movie;

struct MovieVTable {
    u8 pad[0x3c];
    void (*update)(Movie *, void *);
};

struct Movie {
    MovieVTable *vtable;
    u8 pad_004[0x10c];
    void *resource;
    u8 pad_114[4];
    u32 loaded;
    u32 value0;
    u32 value1;
    u32 value2;
};

extern int fn_12_3A36C(void *);
extern u8 lbl_12_rodata_24D8[128];
extern void MWSFSVM_Error(void *, ...);
extern void *fn_12_39CA4(void *);
extern u8 lbl_12_rodata_2480[72];
extern int fn_8004F818(void *, void *, void *, u32 *, u32 *, u32 *);

void fn_12_38E24(Movie *movie, void *arg1, void *arg2) {
    u32 value0;
    u32 value2;
    u32 value1;

    if (fn_12_3A36C(movie) == 0) {
        MWSFSVM_Error(lbl_12_rodata_24D8);
    } else {
        movie->vtable->update(movie, fn_12_39CA4(movie));
        if (fn_8004F818(arg1, arg2, movie->resource, &value0, &value1, &value2) == 0) {
            movie->value0 = value0;
            movie->value1 = value1;
            movie->value2 = value2;
            movie->loaded = 1;
        } else {
            MWSFSVM_Error(lbl_12_rodata_2480);
        }
        movie->loaded = 1;
    }
}
