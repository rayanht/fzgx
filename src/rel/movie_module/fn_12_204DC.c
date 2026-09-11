#include "types.h"

extern u32 lbl_12_bss_6990[8];
extern u32 fn_12_2B348(void);
extern u32 lbl_12_bss_7C64[137];
extern void fn_8004CAC8(void *arg0);
extern void ADXT_Stop(void *arg0);

typedef struct MovieModule {
    u8 pad_0000[0x1b74];
    void *movie_data;
} MovieModule;

typedef struct MovieData {
    void *movie;
    void *movie_controller;
    u32 field_0008;
    u32 field_000c;
    u32 field_0010;
    u32 field_0014;
    u32 field_0018;
    u32 field_001c;
    u32 field_0020;
} MovieData;

typedef struct MovieHeader {
    u32 field_0008;
    u32 field_000c;
    u32 field_0010;
    u32 field_0014;
    u32 field_0018;
    u32 field_001c;
    u32 field_0020;
} MovieHeader;

typedef struct MovieControllerVtable {
    u8 pad_0000[0xc];
    void (*field_000c)(void *self);
} MovieControllerVtable;

typedef struct MovieController {
    MovieControllerVtable *vtable;
} MovieController;

int fn_12_204DC(MovieModule *arg0) {
    MovieData *movie_data;
    void *movie;
    MovieController *movie_controller;
    int result;

    movie_data = (MovieData *)arg0->movie_data;
    movie = movie_data->movie;
    movie_controller = (MovieController *)movie_data->movie_controller;
    if (movie == 0) {
        return 0;
    }

    *(MovieHeader *)lbl_12_bss_6990 = *(MovieHeader *)((u8 *)movie_data + 8);

    result = fn_12_2B348();
    if (result != 1) {
        fn_8004CAC8(movie);
        result = 0;
    } else {
        ADXT_Stop(*(void **)arg0->movie_data);
        lbl_12_bss_7C64[128] = (u32)movie;
        result = 0;
    }

    movie_controller->vtable->field_000c(movie_controller);
    return result;
}
