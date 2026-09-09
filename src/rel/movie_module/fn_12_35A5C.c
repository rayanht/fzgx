#include "types.h"

typedef struct MovieContext {
    u8 pad[0xa8];
    void* movie;
} MovieContext;

typedef struct MovieData {
    void* data;
} MovieData;

extern int fn_12_3A36C(void);
extern char lbl_12_rodata_1C8C[51];
extern void MWSFSVM_Error(const char*, ...);
extern u8 lbl_12_rodata_1CC0[200];
extern void fn_12_35B08(MovieContext*, MovieData*, void*);
extern void fn_12_3054(void*, void*, void*);

void fn_12_35A5C(MovieContext* context, MovieData* data, void* arg) {
    u8 local[0x88];
    void* movie;

    if (fn_12_3A36C() == 0) {
        MWSFSVM_Error(lbl_12_rodata_1C8C);
    } else if (data->data == 0) {
        MWSFSVM_Error((const char*)lbl_12_rodata_1CC0);
    } else {
        movie = context->movie;
        fn_12_35B08(context, data, local);
        fn_12_3054(movie, local, arg);
    }
}
