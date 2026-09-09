#include "types.h"

typedef struct MovieModule {
    u8 pad_0x00[0x40];
    void* player;
    u8 pad_0x44[0xE4];
    void* movie;
    void* movie_data_alt;
    u32 movie_data_alt_1;
    u32 movie_data_alt_2;
    u32 movie_data_alt_3;
    u32 movie_data_1;
    u32 movie_data_2;
    u32 movie_data_3;
    u32 movie_data_4;
    void* movie_data;
    u32 movie_data_5;
    u32 movie_data_6;
} MovieModule;

typedef struct MovieRequest {
    u32 flags;
    void* movie;
    u32 data;
    u32 data_size;
    u32 data_type;
    u32 data_flags;
} MovieRequest;

extern s32 fn_12_2B188(void*, MovieRequest*);
extern void fn_12_38A0C(s32);
extern char lbl_12_rodata_221C[33];
extern void MWSFSVM_Error(char*, ...);

void fn_12_3858C(MovieModule* module) {
    void* movie;
    void* player;
    MovieRequest request;

    movie = module->movie;
    player = module->player;
    if (movie != NULL) {
        if (movie == module->movie_data) {
            request.flags = 1;
            request.movie = movie;
            request.data = module->movie_data_5;
            request.data_size = module->movie_data_6;
            request.data_type = 0;
            request.data_flags = 0;
        } else if (movie == module->movie_data_alt) {
            request.flags = 0;
            request.movie = movie;
            request.data = module->movie_data_alt_1;
            request.data_size = module->movie_data_alt_2;
            request.data_type = module->movie_data_alt_3;
            request.data_flags = 0;
        } else {
            request.flags = module->movie_data_1;
            request.movie = movie;
            request.data = module->movie_data_2;
            request.data_size = module->movie_data_3;
            request.data_type = module->movie_data_4;
            request.data_flags = 0;
        }
        if (fn_12_2B188(player, &request) != 0) {
            fn_12_38A0C(-0x138);
            MWSFSVM_Error(lbl_12_rodata_221C);
        }
    }
}
