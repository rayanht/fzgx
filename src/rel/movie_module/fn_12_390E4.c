#include "types.h"

extern void fn_12_3A888(void *);
extern s32 fn_12_2B358(void *);
extern void fn_12_38A0C(s32);
extern u8 lbl_12_rodata_2580[240];
extern void MWSFSVM_Error(const void *, ...);
extern void fn_12_3B540(void *);
extern void fn_12_34EB0(void *);

typedef struct MovieModule {
    u8 pad0[0x8];
    void *field8;
    u8 padc[0x34];
    void *field40;
    void *field44;
    u8 pad48[0x1a4];
    u8 field1ec;
} MovieModule;

void fn_12_390E4(MovieModule *module) {
    void *movie;

    movie = module->field40;
    if (movie != 0) {
        fn_12_3A888(module);
        module->field8 = 0;
        if (fn_12_2B358(movie) != 0) {
            fn_12_38A0C(-0x134);
            MWSFSVM_Error(lbl_12_rodata_2580);
        }
        fn_12_3B540(&module->field1ec);
        movie = module->field44;
        if (movie != 0) {
            fn_12_34EB0(movie);
        }
    }
}
