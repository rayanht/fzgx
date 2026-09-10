#include "types.h"

typedef struct MovieObject {
    u8 pad[0x58];
    s32 state;
} MovieObject;

extern s32 fn_8004E580(MovieObject *self);
extern MovieObject *fn_12_34CC8(void);
extern u32 lbl_12_bss_1CC58;
extern u32 lbl_12_bss_1CC5C;
extern s32 lbl_12_bss_1B9DC[52];
extern MovieObject *fn_12_38DBC(void);
extern s32 fn_12_34C44(s32 *state);
extern void fn_12_2CD6C(void);
extern void fn_12_34CA8(MovieObject *movie);

s32 fn_12_3ADC4(MovieObject *self) {
    MovieObject *movie;
    MovieObject *manager;

    if (fn_8004E580(self) == 1) {
        movie = fn_12_34CC8();
        lbl_12_bss_1CC58++;
        lbl_12_bss_1CC5C++;
        if (lbl_12_bss_1B9DC[0] == 1) {
            manager = fn_12_38DBC();
            if (fn_12_34C44(&manager->state)) {
                if (lbl_12_bss_1B9DC[0] == 1) {
                    fn_12_2CD6C();
                }
                manager->state = 0;
            }
        }
        fn_12_34CA8(movie);
        return 0;
    }

    return 0;
}
