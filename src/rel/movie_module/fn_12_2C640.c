#include "types.h"

typedef struct Fn12_2C640_Ply {
    u8 pad_0[0x48];
    s32 state;
    s32 kind;
    u8 pad_50[0x964];
    s32 video_on;
    s32 audio_on;
    u8 pad_9BC[0x1C];
    s32 unk_9D8;
    s32 unk_9DC;
    u8 pad_9E0[0x74];
    s32 unk_A54;
    u8 pad_A58[0x4D4];
    s32 unk_F2C;
    u8 pad_F30[0x18];
    s32 unk_F48;
} Fn12_2C640_Ply;

extern s32 fn_12_2D73C(Fn12_2C640_Ply *ply, s32 param);
extern s32 fn_12_2F1F0(Fn12_2C640_Ply *ply, s32 index);
extern s32 fn_12_2F1D0(Fn12_2C640_Ply *ply, s32 index);
extern s32 fn_12_21E94(Fn12_2C640_Ply *ply, s32 type);
extern s32 fn_12_21F28(Fn12_2C640_Ply *ply, s32 type);
extern void fn_12_2D420(Fn12_2C640_Ply *ply, s32 video, s32 audio);
extern void fn_12_2D7DC(Fn12_2C640_Ply *ply, s32 param, s32 value);
extern void fn_12_2F210(Fn12_2C640_Ply *ply, s32, s32, s32, s32);

s32 fn_12_2C640(Fn12_2C640_Ply *ply) {
    s32 ready_b;
    s32 ready_a;
    s32 kind;
    s32 mask;
    s32 end_a;
    s32 finished;
    s32 ready;
    s32 state;
    s32 done;
    s32 value;
    s32 end_b;

    state = ply->state;
    kind = ply->kind;
    if (fn_12_2D73C(ply, 5) == 0) {
        ready_a = 1;
    } else {
        end_a = fn_12_2F1F0(ply, 6);
        ready_a = end_a | fn_12_2F1D0(ply, 6);
    }
    if (fn_12_2D73C(ply, 6) == 0) {
        ready_b = 1;
    } else {
        end_a = fn_12_2F1F0(ply, 7);
        ready_b = end_a | fn_12_2F1D0(ply, 7);
    }
    if (ready_a == 0 || ready_b == 0) {
        ready = 0;
    } else {
        ready = 1;
    }
    if (ready == 0) {
        return state;
    }

    if (ply->video_on == 1 && fn_12_21E94(ply, 1) == 0 && fn_12_21F28(ply, 1) == 0) {
        ply->video_on = 0;
    }
    if (ply->audio_on == 1 && fn_12_21E94(ply, 2) == 0 && fn_12_21F28(ply, 2) == 0) {
        ply->audio_on = 0;
    }
    fn_12_2D420(ply, ply->video_on, ply->audio_on);
    if (ply->audio_on == 0 && ply->unk_9DC == 2) {
        fn_12_2D7DC(ply, 15, 1);
    }
    if (ply->video_on == 0 && ply->unk_9DC == 1) {
        fn_12_2D7DC(ply, 15, 2);
    }

    mask = 0;
    if (ply->audio_on == 1) {
        mask |= 1;
    }
    if (ply->video_on == 1) {
        mask |= 2;
    }
    switch (mask) {
    case 1:
        value = 1;
        break;
    case 2:
        value = 2;
        break;
    case 3:
        value = fn_12_2D73C(ply, 25);
        break;
    default:
        value = 3;
        break;
    }
    fn_12_2D7DC(ply, 25, value);

    switch (kind) {
    case 2:
        state = 2;
        break;
    case 3:
        state = 3;
        break;
    case 4:
    case 6:
        if (ply->unk_9D8 == 0) {
            done = 1;
        } else if (ply->video_on == 0) {
            done = 1;
        } else if (ply->unk_F2C != 0) {
            done = 1;
        } else if (ply->unk_F48 >= ply->unk_A54) {
            done = 1;
        } else {
            if (ply->audio_on == 0 && ply->video_on == 0) {
                finished = 1;
            } else {
                finished = 0;
                value = fn_12_2F1D0(ply, 6);
                end_a = fn_12_2F1D0(ply, 7);
                switch (fn_12_2D73C(ply, 25)) {
                case 1:
                    finished = end_a;
                    break;
                case 2:
                    finished = value;
                    break;
                case 3:
                    finished = end_a | value;
                    break;
                case 0:
                    finished = end_a & value;
                    break;
                }
            }
            if (finished != 0) {
                done = 1;
            } else {
                done = 0;
            }
        }
        if (done != 0) {
            fn_12_2F210(ply, 7, 6, 0, 0);
            state = 4;
        } else {
            state = 3;
        }
        break;
    }
    return state;
}
