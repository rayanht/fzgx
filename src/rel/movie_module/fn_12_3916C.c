#include "types.h"
#include "sofdec/mwsfd.h"
#include "sofdec/mwsst.h"

typedef struct MovieModule {
    u8 pad00[0x8];
    s32 field08;
    s32 field0c;
    u8 pad10[0x30];
    void *sfd;
    void *stream;
    u8 pad48[0x28];
    u8 field70;
    u8 field71;
    s8 paused;
    u8 pad73[0x9];
    s32 field7c;
    s32 field80;
    s32 field84;
    u8 pad88[0xa0];
    s32 field128;
    u8 pad12c[0x10];
    s32 field13c;
    s32 field140;
    s32 field144;
    s32 field148;
    u8 pad14c[0xa0];
    MwsStHandle sound;
} MovieModule;

extern u8 lbl_12_rodata_2480[];

extern s32 fn_12_3A36C(void *);
extern void MWSFSVM_Error(const char *, ...);
extern void fn_12_3A888(void *);
extern s32 fn_12_2B358(void *);
extern void fn_12_38A0C(s32);
extern void fn_12_3B540(void *);
extern void fn_12_34EB0(void *);
extern u32 *fn_12_38DBC(void);
extern int MWSFCRE_ResetSfdHn(void *);
extern void fn_12_3B2EC(void *);
extern void fn_12_33A14(void *);
extern void fn_12_353C4(void *);
extern s32 fn_12_35418(void *);
extern void fn_12_353FC(void *);
extern s32 fn_12_2AD88(u32);
extern s32 fn_12_38AD0(void);
extern s32 fn_12_2D74C(u8 *, int, u32 *);
extern int fn_12_2AF5C(SfdHandle *, int);
extern void MWSST_Pause(MwsStHandle *, int);
extern void MWSST_StartSj(MwsStHandle *);
extern void fn_12_3858C(void *);

void fn_12_3916C(MovieModule *player, u32 arg1) {
    u8 *messages = (u8 *)&lbl_12_rodata_2480;
    void *sfd;
    s32 old;
    s32 pause_status;
    const char *state;

    if (fn_12_3A36C(player) == 0) {
        MWSFSVM_Error((const char *)(messages + 0x120));
        return;
    }
    sfd = player->sfd;
    if (sfd != 0) {
        fn_12_3A888(player);
        player->field08 = 0;
        if (fn_12_2B358(sfd) != 0) {
            fn_12_38A0C(-0x134);
            MWSFSVM_Error((const char *)(messages + 0x100));
        }
        fn_12_3B540(&player->sound);
        if (player->stream != 0) {
            fn_12_34EB0(player->stream);
        }
    }
    player->field128 = arg1;
    player->field13c = 2;
    player->field140 = 0;
    player->field144 = 0;
    player->field148 = 0;
    fn_12_38DBC();
    if (player->sfd != 0) {
        if (MWSFCRE_ResetSfdHn(player) != 0) {
            MWSFSVM_Error((const char *)(messages + 0x14c));
            goto finish; /* shared exit: retail branches to the common finish block */
        }
        fn_12_3B2EC(player);
        fn_12_33A14(player);
        fn_12_353C4(player);
        if (fn_12_35418(player) != 0) {
            MWSFSVM_Error((const char *)(messages + 0x178));
            goto finish; /* shared exit: retail branches to the common finish block */
        }
        fn_12_353FC(player);
    }
    player->field7c = 0;
    player->field80 = 0;
    if (fn_12_2AD88((u32)player->sfd) != 0) {
        fn_12_38A0C(-0x137);
        MWSFSVM_Error((const char *)(messages + 0x1a4));
    }
    old = player->paused;
    if (fn_12_3A36C(player) == 0) {
        MWSFSVM_Error((const char *)(messages + 0x84));
    } else {
        sfd = player->sfd;
        if (player->paused != 0 || old != 0) {
            if (fn_12_38AD0() == 1 && player->field0c == 1) {
                if (fn_12_2D74C((u8 *)sfd, 6, (u32 *)&pause_status) == 0) {
                    if (pause_status == 1) {
                        fn_12_3A888(player);
                    }
                } else {
                    fn_12_3A888(player);
                }
            }
            if (fn_12_2AF5C((SfdHandle *)sfd, old) != 0) {
                const char *state;
                const char *msg;
                fn_12_38A0C(-0x136);
                msg = (const char *)(messages + 0xac);
                state = (const char *)(messages + 0xd4);
                if (old == 1) {
                    state = (const char *)(messages + 0xd0);
                }
                MWSFSVM_Error(msg, state);
            }
            MWSST_Pause(&player->sound, (s8)old);
            player->paused = (s8)old;
        }
    }
    MWSST_Pause(&player->sound, 1);
    MWSST_StartSj(&player->sound);
    player->field84 = 0;
    player->field71 = 0;
    player->field08 = 1;
finish:
    fn_12_3858C(player);
}
