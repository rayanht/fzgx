#include "sofdec/mwsfd.h"

struct MwsPauseMessages {
    char unknown_000[0x84];
    char invalid_handle[40];
    char pause_failed[35];
    char padding_0cf;
    char on[3];
    char padding_0d3;
    char off[4];
};

int fn_12_2D74C(SfdHandle *handle, int condition, int *value);

extern int fn_12_38AD0(void);

extern int fn_12_3A36C(MwsPlayer *player);

extern int fn_12_38A0C(int error);

extern void MWSFSVM_Error(const char *message, ...);

extern void MWSST_Pause(MwsStHandle *sound, int paused);

extern int fn_12_2AF5C(SfdHandle *handle, int paused);

extern void fn_12_3A888(MwsPlayer *player);

extern struct MwsPauseMessages lbl_12_rodata_2480;

void mwSfdPause(MwsPlayer *player, int paused) {
    struct MwsPauseMessages *messages = &lbl_12_rodata_2480;

    SfdHandle *sfd;
    int pause_status;
    if (fn_12_3A36C(player) == 0) {
        MWSFSVM_Error((messages->invalid_handle));
        return;
    }
    sfd = player->sfd;
    if (player->paused == 0 && paused == 0) {
        return;
    }
    if (fn_12_38AD0() == 1 && player->playback_mode == 1) {
        if (fn_12_2D74C(sfd, 6, &pause_status) == 0) {
            if (pause_status == 1) {
                fn_12_3A888(player);
            }
        } else {
            fn_12_3A888(player);
        }
    }
    if (fn_12_2AF5C(sfd, paused) != 0) {
        fn_12_38A0C(-0x136);
        {
            const char *format = messages->pause_failed;
            const char *state = messages->off;
            if (paused == 1) {
                state = messages->on;
            }
            MWSFSVM_Error(format, state);
        }
    }
    MWSST_Pause(&player->sound, paused);
    player->paused = paused;
}
