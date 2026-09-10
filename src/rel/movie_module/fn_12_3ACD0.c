#include "types.h"

typedef struct MovieObject {
    u8 _pad[0x10];
    s32 value;
    u8 _pad2[0x44];
    s32 state;
} MovieObject;

extern s32 fn_8004E580(MovieObject *self);
extern MovieObject *fn_12_38DBC(void);
extern s32 fn_12_3AB00(MovieObject *self);
extern s32 fn_12_34CC8(void);
extern u32 lbl_12_bss_1CC58;
extern u32 lbl_12_bss_1CC5C;
extern s32 lbl_12_bss_1B9DC[52];
extern s32 fn_12_34C44(s32 *state);
extern void fn_12_2CD6C(void);
extern void fn_12_34CA8(s32 result);

#pragma opt_lifetimes off
s32 fn_12_3ACD0(MovieObject *self) {
    register s32 result;

    result = 0;
    if (fn_8004E580(self) == 1) {
        if (fn_12_38DBC()->value == 1) {
            result = fn_12_3AB00(self);
        }
    } else {
        MovieObject *movie;
        result = fn_12_34CC8();
        lbl_12_bss_1CC58++;
        lbl_12_bss_1CC5C++;

        if (lbl_12_bss_1B9DC[0] == 1) {
            MovieObject *movie;
            movie = fn_12_38DBC();
            if (fn_12_34C44(&movie->state)) {
                if (lbl_12_bss_1B9DC[0] == 1) {
                    fn_12_2CD6C();
                }
                movie->state = 0;
            }
        }

        fn_12_34CA8(result);
        result = fn_12_3AB00(self);
    }

    return result;
}
#pragma opt_lifetimes reset

