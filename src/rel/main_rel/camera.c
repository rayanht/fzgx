#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/camera.h"

extern void fn_1_BD54(void);
extern void fn_1_B870(void);
extern void camera_get_extended_state_storage(__typeof__(lbl_1_bss_F68));
extern void lbl_8006DBAC(void);
extern void fn_8006F038(void *, void *, s16);
extern void lbl_8006DCDC(void);
extern s16 fn_1_6B48(s16 value);
extern void fn_1_6D2C(u32);
extern s32 lbl_1_bss_F78;
extern void fn_1_A2DF4(u32, u32, u32);
extern s8 fn_1_86624(void);
extern s8 fn_1_86634(s32 index);
extern void OSPanic(u8 *file, int line, u8 *message, ...);
extern u8 lbl_1_bss_F74;
extern u8 lbl_1_bss_F75;
extern f32 lbl_1_rodata_188;
extern s32 fn_1_8708(u8 mode, f32 *value0, f32 *value1);
extern void fn_1_8A0C(s16 index);
extern void fn_1_A6FE8(void);
extern void fn_1_8D08(GameCameraEntry *value);
extern f32 lbl_1_bss_1040;
extern f32 lbl_1_bss_1044;
extern void OSReport(const unsigned char *, ...);
extern u8 lbl_1_bss_103C[4];
extern u8 lbl_1_bss_108C[52];
extern u8 lbl_1_bss_1014;

extern s8 fn_1_86624(void);
extern s8 fn_1_86634(s32 index);
extern void OSPanic(u8 *file, int line, u8 *message, ...);
extern void fn_1_8A0C(s16 index);
extern void OSReport(const unsigned char *, ...);

extern f32 lbl_1_rodata_2E0[32];
extern f32 lbl_8006D6FC(f32 *value, void *target);
u32 fn_1_6514(u32);
extern struct fn_1_6400_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern f64 lbl_1_rodata_478;
extern f32 lbl_1_rodata_49C;
extern f32 lbl_1_bss_10C0[6];

/* fzgx:begin fn_1_6400 */
struct fn_1_6400_lbl_801A6410 {
    u32 unk_0;
};
extern struct fn_1_6400_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern u8 lbl_1_data_3318[180];

typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
} F68State;

// Report and clear the three pending camera state values.
void fn_1_6400(void) {
    F68State *state;

    state = (F68State *)&lbl_1_bss_F68;
    fn_1_46B4(lbl_801A6410.unk_0, state->unk_8, lbl_1_data_3318, 0x396);
    fn_1_46B4(lbl_801A6410.unk_0, state->unk_4, lbl_1_data_3318, 0x397);
    fn_1_46B4(lbl_801A6410.unk_0, state->unk_0, lbl_1_data_3318, 0x398);
    state->unk_8 = 0;
    state->unk_4 = 0;
    state->unk_0 = 0;
}
/* fzgx:end fn_1_6400 */

/* fzgx:begin camera_get_state */
// Return the camera state byte, or -1 when no camera state is active.
s32 camera_get_state(void) {
    Obj_1_bss_F68_Target *camera = lbl_1_bss_F68;

    if (camera == 0) {
        return -1;
    }

    return camera->unk_48;
}
/* fzgx:end camera_get_state */

/* fzgx:begin camera_get_status */
// Return the camera status when a camera exists and is not marked inactive.
u32 camera_get_status(void) {
    Obj_1_bss_F68_Target *camera = lbl_1_bss_F68;
    u32 status;

    if (camera == 0) {
        status = 0;
    } else if ((camera->unk_0 & ((u32)1 << 31)) != 0) {
        status = 0;
    } else {
        status = camera->unk_4A;
    }

    return fn_1_6514(status);
}
/* fzgx:end camera_get_status */

/* fzgx:begin camera_get_flags */
u32 camera_get_flags(void) {
    // Reports the active camera object's top-bit flag, or zero when no object is active.
    if (lbl_1_bss_F68 != 0) {
        return lbl_1_bss_F68->unk_0 & (1u << 31);
    }

    return 0;
}
/* fzgx:end camera_get_flags */

/* fzgx:begin camera_update */
__typeof__(lbl_1_bss_F68) camera_get_state_object(void);

// Dispatches to the camera update routine selected by the returned camera state.
void camera_update(void) {
    __typeof__(lbl_1_bss_F68) state = camera_get_state_object();

    if (((state->unk_0 >> 30) & 1) != 0) {
        fn_1_BD54();
    } else {
        fn_1_B870();
    }
}
/* fzgx:end camera_update */

/* fzgx:begin camera_update_state */
// Updates the camera state through the active or standard camera path.
void camera_update_state(__typeof__(lbl_1_bss_F68) state) {
    if ((state->unk_0 >> 30) & 1) {
        camera_get_extended_state_storage(state);
        lbl_8006DBAC();
    } else {
        fn_8006F038(&state->unk_4, &state->unk_4 + 6,
                     *((s16 *)&state->unk_4 + 14));
    }

    lbl_8006DCDC();
}
/* fzgx:end camera_update_state */

/* fzgx:begin camera_get_mode */
// Return the normalized camera status, treating inactive states as zero.
s16 camera_get_mode(void) {
    Obj_1_bss_F68_Target *state = lbl_1_bss_F68;
    s16 value;

    if (state == 0) {
        value = 0;
    } else if ((state->unk_0 & ((s32)1 << 31)) != 0) {
        value = 0;
    } else {
        value = state->unk_4A;
    }

    value = fn_1_6B48(value);
    if (value == 0xff) {
        value = -1;
    }

    return value;
}
/* fzgx:end camera_get_mode */

/* fzgx:begin camera_get_output */
s16 camera_get_output(void) {
    Obj_1_bss_F68_Target *state = lbl_1_bss_F68;
    u32 result;

    // Return the camera output only when the state is active and ready.
    if ((s8)state->unk_48 == 6) {
        if (state == 0) {
            result = 0;
        } else if ((state->unk_0 & ((s32)1 << 31)) != 0) {
            result = 0;
        } else {
            result = state->unk_4A;
        }

        if (result == 3) {
            return live_camera->unk_6;
        }
    }

    return -1;
}
/* fzgx:end camera_get_output */

/* fzgx:begin camera_set_result */
void camera_set_result(s16 value) {
    // Update the camera result only while the camera state is active.
    if (lbl_1_bss_F68 != 0) {
        game_camera_entries->unk_2 = value;
    }
}
/* fzgx:end camera_set_result */

/* fzgx:begin camera_forward_status */
// Forward the camera state's status to the next update stage.
void camera_forward_status(void) {
    Obj_1_bss_F68_Target *state = lbl_1_bss_F68;
    u32 value;

    if (state == 0) {
        value = 0;
    } else if ((state->unk_0 & ((u32)1 << 31)) != 0) {
        value = 0;
    } else {
        value = state->unk_4A;
    }

    fn_1_6D2C(value);
}
/* fzgx:end camera_forward_status */

/* fzgx:begin fn_1_6EC0 */
u32 fn_1_6EC0(u8 index) {
    Obj_1_bss_F68_Target *state = lbl_1_bss_F68;

    if (state == 0) {
        return 0;
    }
    if ((state->unk_0 & ((u32)1 << 31)) != 0) {
        return 0;
    }

    switch ((s8)state->unk_48) {
    case 9:
    case 10:
        return 0;
    }

    return game_camera_entries[index].unk_A8 == 0;
}
/* fzgx:end fn_1_6EC0 */

/* fzgx:begin camera_is_mode_0x0b */
// Return whether the camera state is active and has the expected mode.
u32 camera_is_mode_0x0b(void) {
    Obj_1_bss_F68_Target *state = lbl_1_bss_F68;

    if (state == 0) {
        return 0;
    }
    if ((state->unk_0 & ((u32)1 << 31)) != 0) {
        return 0;
    }
    return (s8)state->unk_48 == 0x0B;
}
/* fzgx:end camera_is_mode_0x0b */

/* fzgx:begin camera_set_entry_field_0xa8 */
void camera_set_entry_field_0xa8(u8 index, s16 value) {
    // Store the selected camera entry's parameter.
    game_camera_entries[index].unk_A8 = value;
}
/* fzgx:end camera_set_entry_field_0xa8 */

/* fzgx:begin fn_1_715C */
void fn_1_715C(u8 index, s16 value) {
    // Toggle the camera effect associated with this entry before storing its state.
    if (game_camera_entries[index].unk_A8 == 0 && index < 4) {
        if (value == 0) {
            if (lbl_1_bss_F78 == 0) {
                fn_1_A2DF4(index, 0xa5000000, 8);
                lbl_1_bss_F78 = 1;
            }
        } else if (game_camera_entries[index].unk_A4 == 0 &&
                   lbl_1_bss_F78 != 0) {
            fn_1_A2DF4(index, 0xa5000000,
                       (&lbl_1_bss_6F1E4.unk_8)[index * 10]);
            lbl_1_bss_F78 = 0;
        }
    }

    game_camera_entries[index].unk_A4 = value;
}
/* fzgx:end fn_1_715C */

/* fzgx:begin camera_get_entry_field_0xa8 */
s16 camera_get_entry_field_0xa8(u32 index) {
    // Return the selected camera entry's stored value.
    return game_camera_entries[(u8)index].unk_A8;
}
/* fzgx:end camera_get_entry_field_0xa8 */

/* fzgx:begin camera_get_entry_field_0xa4 */
s16 camera_get_entry_field_0xa4(u32 index) {
    // Return the selected camera entry's stored value.
    return game_camera_entries[(u8)index].unk_A4;
}
/* fzgx:end camera_get_entry_field_0xa4 */

/* fzgx:begin camera_compare_values */
s32 camera_compare_values(const u8 *lhs_index, const u8 *rhs_index) {
    f32 *camera_values = &lbl_1_bss_6F524.unk_0;
    f32 lhs_value = camera_values[*lhs_index];
    f32 rhs_value = camera_values[*rhs_index];

    // Orders two camera indices by their associated values.
    if (lhs_value < rhs_value) {
        return -1;
    }
    if (lhs_value == rhs_value) {
        return 0;
    }
    return 1;
}
/* fzgx:end camera_compare_values */

/* fzgx:begin fn_1_8298 */
extern GameCameraEntry *game_camera_entries;  // array of 0x1FC-byte records

// Initializes camera entry selections and updates the camera mode from the available entries.
void fn_1_8298(void) {
    s8 found;
    s8 count;
    s32 i;

    found = 0;
    count = fn_1_86624();

    for (i = 0; i < 4; i++) {
        game_camera_entries[i].unk_2 = -1;
    }

    for (i = 0; i < count; i++) {
        s8 index = fn_1_86634(i);

        if (index != -1) {
            found++;
            game_camera_entries[index].unk_2 = i;
        }
    }

    switch (found) {
    case 0:
        OSPanic(lbl_1_data_3318, 0x7d2, lbl_1_data_35E8);
        break;
    case 1:
        lbl_1_bss_F68->unk_48 = 0;
        break;
    case 2:
        switch (lbl_1_bss_F68->unk_4B) {
        case 0:
            lbl_1_bss_F68->unk_48 = 1;
            break;
        case 1:
            lbl_1_bss_F68->unk_48 = 2;
            break;
        }
        break;
    case 3:
        switch (lbl_1_bss_F68->unk_4C) {
        case 0:
            lbl_1_bss_F68->unk_48 = 3;
            break;
        case 1:
            lbl_1_bss_F68->unk_48 = 4;
            break;
        case 2:
            lbl_1_bss_F68->unk_48 = 5;
            break;
        case 3:
            lbl_1_bss_F68->unk_48 = 6;
            break;
        case 4:
            lbl_1_bss_F68->unk_48 = 6;
            break;
        }
        break;
    case 4:
        lbl_1_bss_F68->unk_48 = 8;
        break;
    }
}
/* fzgx:end fn_1_8298 */

/* fzgx:begin fn_1_847C noprologue */
#include "types.h"

typedef struct {
    u8 pad_0[0x48];
    u8 unk_48;
} CameraObject;

typedef struct {
    u8 pad_0[0x6];
    s16 unk_6;
    u8 pad_8[0x4];
    u32 unk_C;
    u8 pad_10[0x8];
    s32 unk_18;
} CameraTable;

typedef struct {
    u8 pad_0[0x2];
    s16 unk_2;
} CameraEntry;

typedef struct {
    CameraObject *unk_0;
    CameraEntry *unk_4;
    CameraTable *unk_8;
    u8 pad_C[0x8];
    s8 unk_14;
} CameraState;

extern CameraState lbl_1_bss_F68;
extern s8 fn_1_86624(s8 mode);
extern s8 fn_1_86634(s32 index);

#pragma opt_propagation off
void fn_1_847C(s8 mode) {
    CameraState *state;
    s32 i;

    state = &lbl_1_bss_F68;
    state->unk_14 = fn_1_86624(mode);
    state->unk_8->unk_6 = -1;
    i = 0;
    while (i < state->unk_14) {
        if (fn_1_86634(i) == 0) {
            state->unk_8->unk_6 = (s16)i;
            break;
        }
        i++;
    }
    if (state->unk_8->unk_18 != 0) {
        state->unk_8->unk_C |= 0x100000;
    }
    if (mode == 1) {
        state->unk_0->unk_48 = 9;
    } else if (mode == 2) {
        state->unk_0->unk_48 = 10;
        state->unk_4->unk_2 = state->unk_8->unk_6;
    } else if (mode == 4) {
        state->unk_0->unk_48 = 9;
    }
}
#pragma opt_propagation reset
/* fzgx:end fn_1_847C */

/* fzgx:begin fn_1_857C noprologue */
#include "types.h"

typedef struct {
    u32 unk_0;
    u16 entries[15];
    s16 unk_22;
    u16 unk_24;
    u8 pad_26[0x1E];
    s16 unk_44;
    u16 unk_46;
    u8 unk_48;
    u8 unk_49;
    u8 unk_4A;
    u8 unk_4B;
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[2];
    u32 unk_50;
} CameraState;

extern u32 lbl_1_bss_7ADE8[40];
extern void *lbl_1_data_3310;
extern CameraState *lbl_1_bss_F68;
extern char lbl_1_data_35FC[14];

extern void fn_1_A6FE8(void);
extern void fn_1_DCE60(void *);
extern void fn_1_435C(u32);
extern s16 fn_1_3F8C(char *, void *, void *, int);
extern void fn_1_DCED0(void);

#pragma opt_propagation off
void fn_1_857C(void) {
    s16 index;
    s16 result;

    lbl_1_bss_F68->unk_48 = 0xb;
    lbl_1_data_3310 = lbl_1_bss_7ADE8;
    fn_1_A6FE8();
    fn_1_DCE60(lbl_1_data_3310);
    fn_1_435C(lbl_1_bss_F68->unk_50);
    result = fn_1_3F8C(lbl_1_data_35FC, fn_1_DCED0, lbl_1_data_3310, 0x14);
    {
        CameraState *camera = lbl_1_bss_F68;
        index = camera->unk_22;
        camera->unk_22 = index + 1;
        camera->entries[index] = result;
    }
}
#pragma opt_propagation reset
/* fzgx:end fn_1_857C */

/* fzgx:begin camera_get_entry_field_0x2 */
// Returns the selected camera entry value for an 8-bit camera index.
s16 camera_get_entry_field_0x2(u32 index) {
    return game_camera_entries[(u8)index].unk_2;
}
/* fzgx:end camera_get_entry_field_0x2 */

/* fzgx:begin camera_set_selected_value */
// Cache the selected camera value for subsequent camera processing.
void camera_set_selected_value(u8 value) {
    lbl_1_bss_F74 = value;
}
/* fzgx:end camera_set_selected_value */

/* fzgx:begin camera_set_state_flag */
// Store the camera state flag used by subsequent camera updates.
void camera_set_state_flag(u8 value) {
    lbl_1_bss_F75 = value;
}
/* fzgx:end camera_set_state_flag */

/* fzgx:begin camera_get_values */
// Reads the camera values, falling back when the camera state cannot provide them.
s32 camera_get_values(f32 *value0, f32 *value1) {
    f32 result0;
    f32 result1;
    u8 mode;
    Obj_1_bss_F68_Target *obj;
    f32 fallback;

    obj = lbl_1_bss_F68;
    if (obj == 0) {
        mode = 0;
    } else if ((obj->unk_0 & ((u32)1 << 31)) != 0) {
        mode = 0;
    } else {
        mode = obj->unk_4A;
    }

    if (fn_1_8708(mode, &result0, &result1) != 0) {
        *value0 = result0;
        *value1 = result1;
        return 1;
    }

    fallback = lbl_1_rodata_188;
    *value0 = fallback;
    *value1 = fallback;
    return -1;
}
/* fzgx:end camera_get_values */

/* fzgx:begin live_camera_set_shake */
// Marks the camera state active, accumulates a position delta, and tracks the highest value.
void live_camera_set_shake(s32 value, const f32 *delta) {
    LiveCamera *state;

    if (live_camera == 0) {
        OSPanic(lbl_1_data_3318, 0x89a, lbl_1_data_360C);
    }

    state = live_camera;
    state->unk_AC = 1;
    state->unk_CC += delta[0];
    state->unk_D0 += delta[1];
    state->unk_D4 += delta[2];

    if (value < 0 || (s32)state->unk_B0 < 0) {
        state->unk_B0 = -1;
    } else if ((s32)state->unk_B0 < value) {
        state->unk_B0 = value;
    }
}
/* fzgx:end live_camera_set_shake */

/* fzgx:begin game_camera_set_shake */
extern GameCameraEntry *game_camera_entries;  // array of 0x1FC-byte records

// Updates the selected camera state with a movement delta and tracks its highest value.
void game_camera_set_shake(s16 index, s16 mode, s32 value, const f32 *delta) {
    GameCameraEntry *camera;

    if (index < 0) {
        return;
    }

    if (game_camera_entries + index == 0) {
        OSPanic(lbl_1_data_3318, 0x8d1, lbl_1_data_3654);
    }

    camera = game_camera_entries + index;
    if (mode != camera->unk_2) {
        fn_1_8A0C(index);
        return;
    }

    camera->unk_10C = 1;
    camera->unk_12C += delta[0];
    camera->unk_130 += delta[1];
    camera->unk_134 += delta[2];
    camera->unk_150 += delta[2];
    camera->unk_154 += delta[1];
    camera->unk_158 += delta[0];

    if (value < 0 || (s32)camera->unk_110 < 0) {
        camera->unk_110 = -1;
    } else if ((s32)camera->unk_110 < value) {
        camera->unk_110 = value;
    }
}
/* fzgx:end game_camera_set_shake */

/* fzgx:begin camera_init */
// Initialize camera state before passing the shared camera object onward.
void camera_init(void) {
    fn_1_A6FE8();
    fn_1_8D08(game_camera_entries);
}
/* fzgx:end camera_init */

/* fzgx:begin live_camera_get */
// Return the shared camera object used by the camera system.
LiveCamera *live_camera_get(void) {
    return live_camera;
}
/* fzgx:end live_camera_get */

/* fzgx:begin game_camera_get */
// Return the current camera target object.
GameCameraEntry *game_camera_get(void) {
    return game_camera_entries;
}
/* fzgx:end game_camera_get */

/* fzgx:begin fn_1_AA54 noprologue */
#include "types.h"

struct fn_1_AA54_Arg0 {
    u8 pad_0[0x2];
    s16 unk_2;
};
struct fn_1_AA54_lbl_1_rodata_388 {
    f64 unk_0;
};
extern f64 lbl_1_rodata_360;
extern s16 lbl_1_bss_960;
extern struct fn_1_AA54_lbl_1_rodata_388 lbl_1_rodata_388;
extern u8 fn_1_86678(int);
extern s8 fn_1_86634(int);
extern s16 camera_get_entry_field_0xa8(u32);
extern u32 fn_1_864E8(int);
extern void camera_set_entry_field_0xa8(u8, s16);
extern u16 fn_1_8664C(int);


void fn_1_AA54(void *arg0) {
    s16 temp_r28;
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fn_1_86678((s32) (*(s16 *)((u8 *)(arg0) + 2)));
    temp_r3 = fn_1_86634((s32) (*(s16 *)((u8 *)(arg0) + 2)));
    temp_r28 = camera_get_entry_field_0xa8((u32) temp_r3);
    if (((s16) (*(s16 *)((u8 *)(&lbl_1_bss_960) + 0)) != 9) && (fn_1_864E8((s32) (*(s16 *)((u8 *)(arg0) + 2))) & 0x10000)) {
        camera_set_entry_field_0xa8(temp_r3, 2);
        return;
    }
    if (!(fn_1_864E8((s32) (*(s16 *)((u8 *)(arg0) + 2))) & 1)) {
        if (fn_1_864E8((s32) (*(s16 *)((u8 *)(arg0) + 2))) & 0x800) {
            camera_set_entry_field_0xa8(temp_r3, 5);
            return;
        }
        if (!(fn_1_864E8((s32) (*(s16 *)((u8 *)(arg0) + 2))) & 0x80)) {
            goto block_7; /* Preserves the retail branch. */
        }
    } else {
block_7:
        if ((f64) (*(f64 *)((u8 *)(&lbl_1_rodata_360) + 0)) == (f64) (f64) fn_1_8664C((s32) (*(s16 *)((u8 *)(arg0) + 2)))) {
            camera_set_entry_field_0xa8(temp_r3, 3);
            return;
        }
        if (fn_1_8664C((s32) (*(s16 *)((u8 *)(arg0) + 2))) == 0x14) {
            camera_set_entry_field_0xa8(temp_r3, 0);
            return;
        }
        if ((s8) temp_r31 >= 0) {
            camera_set_entry_field_0xa8(temp_r3, temp_r28);
        }
    }
}
/* fzgx:end fn_1_AA54 */

/* fzgx:begin camera_get_position_delta */
typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern void fn_1_862D4(u8 index, Vec3 *out);
extern void fn_1_8658C(u8 index, Vec3 *out);

// Computes the displacement between two camera positions.
void camera_get_position_delta(u32 index, Vec3 *out) {
    u8 idx = (u8)index;
    Vec3 first;
    Vec3 second;

    fn_1_862D4(idx, &first);
    fn_1_8658C(idx, &second);
    out->x = first.x - second.x;
    out->y = first.y - second.y;
    out->z = first.z - second.z;
}
/* fzgx:end camera_get_position_delta */

/* fzgx:begin camera_reset_transition */
typedef struct camera_reset_transition_Camera {
    u8 pad_00[0xA4];
    s16 unk_A4;
} camera_reset_transition_Camera;

extern void fn_1_AEB8(camera_reset_transition_Camera *);

// Resets the camera transition state before refreshing the camera.
void camera_reset_transition(camera_reset_transition_Camera *camera) {
    camera->unk_A4 = 0;
    fn_1_AEB8(camera);
}
/* fzgx:end camera_reset_transition */

/* fzgx:begin camera_update_transition */
typedef struct camera_update_transition_Camera {
    u8 pad_00[0x78];
    s16 unk_78;
    u8 pad_7A[0x2A];
    s16 unk_A4;
} camera_update_transition_Camera;

extern void fn_1_AEB8(camera_update_transition_Camera *);
extern void fn_1_AFC8(camera_update_transition_Camera *);

// Advances the camera's transition state and updates its active view.
void camera_update_transition(camera_update_transition_Camera *camera) {
    if (camera->unk_78 == 0) {
        camera->unk_A4++;
        if (camera->unk_A4 >= camera_transition_count) {
            camera->unk_A4 = 0;
        }
        fn_1_AEB8(camera);
    }

    fn_1_AFC8(camera);

    if (camera->unk_78 != 0) {
        camera->unk_78--;
    }
}
/* fzgx:end camera_update_transition */

/* fzgx:begin camera_get_target_orientation */
typedef struct Transform {
    u8 pad_08[0x8];
    f32 unk_08;
    u8 pad_0c[0xc];
    f32 unk_18;
    u8 pad_1c[0xc];
    f32 unk_28;
    u8 pad_2c[0x24];
    u8 unk_50[0x2c];
    u32 unk_7C;
} Transform;

typedef struct CameraStateLocal {
    u8 pad_d4[0xd4];
    f32 unk_D4;
    f32 unk_D8;
    f32 unk_DC;
} CameraStateLocal;

typedef struct CameraObject {
    u8 pad_49c[0x49c];
    Transform *unk_49C;
} CameraObject;

extern Transform *lbl_801A6D00;
extern CameraStateLocal *lbl_801A66CC;

// Updates the camera orientation from the active target transform.
f32 camera_get_target_orientation(CameraObject *camera) {
    Transform *target = camera->unk_49C;

    if (target == 0) {
        return lbl_1_rodata_2E0[0];
    }
    if ((target->unk_7C & 0x01800000) == 0) {
        return lbl_1_rodata_2E0[0];
    }

    lbl_801A66CC->unk_D4 = -lbl_801A6D00->unk_08;
    lbl_801A66CC->unk_D8 = -lbl_801A6D00->unk_18;
    lbl_801A66CC->unk_DC = -lbl_801A6D00->unk_28;
    return lbl_8006D6FC(&lbl_801A66CC->unk_D4, &target->unk_50);
}
/* fzgx:end camera_get_target_orientation */

/* fzgx:begin fn_1_B81C */
struct fn_1_B81C_Copy12 { u32 a[3]; };

void fn_1_B81C(struct fn_1_B81C_Copy12 *first, struct fn_1_B81C_Copy12 *second, u32 value) {
    *(struct fn_1_B81C_Copy12 *)((u8 *)&camera_state + 4) = *first;
    *(struct fn_1_B81C_Copy12 *)((u8 *)&camera_state + 16) = *second;
    camera_state.unk_20 = value;
}
/* fzgx:end fn_1_B81C */

/* fzgx:begin camera_save_parameters */
// Saves the two current camera parameters for later processing.
void camera_save_parameters(f32 first_parameter, f32 second_parameter) {
    lbl_1_bss_1040 = first_parameter;
    lbl_1_bss_1044 = second_parameter;
}
/* fzgx:end camera_save_parameters */

/* fzgx:begin fn_1_C038 */
void fn_1_C038(s32 value, f32 start, f32 end) {
    f32 difference;
    f32 ratio;
    f32 converted;

    difference = end - start;
    ratio = difference / (f32)(((u32)(value * value)) >> 2);

    lbl_1_bss_10C0[0] = start;
    lbl_1_bss_10C0[1] = end;
    lbl_1_bss_10C0[4] = lbl_1_rodata_49C;

    lbl_1_bss_10C0[5] = ratio;
    converted = (f32)(u32)value;
    lbl_1_bss_10C0[3] = converted;
    lbl_1_bss_10C0[2] = converted;
}
/* fzgx:end fn_1_C038 */

/* fzgx:begin camera_save_slot */
typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
} CameraSlot;

// Copies the current camera parameters into the selected camera slot.
void camera_save_slot(u8 index) {
    CameraSlot *dst = (CameraSlot *)&lbl_1_bss_10D8 + index;

    dst->unk_0 = camera_state.unk_0;
    dst->unk_4 = camera_state.unk_4;
    dst->unk_8 = camera_state.unk_8;
    dst->unk_C = camera_state.unk_C;
    dst->unk_10 = camera_state.unk_10;
    dst->unk_14 = camera_state.unk_14;
    dst->unk_18 = camera_state.unk_18;
    dst->unk_1C = camera_state.unk_1C;
    dst->unk_20 = *(u32 *)&camera_state.unk_20;
}
/* fzgx:end camera_save_slot */

/* fzgx:begin fn_1_C178 noprologue */
#include "types.h"

typedef struct { u8 pad_0[0x4]; f32 unk_4; u32 unk_8; f32 unk_C; } Bss_104C;
typedef struct {
    u8 pad_0[0x4]; f32 unk_4; f32 unk_8; f32 unk_C; f32 unk_10; f32 unk_14; f32 unk_18; f32 unk_1C;
    s16 unk_20; u8 pad_22[0x6]; f32 unk_28; f32 unk_2C; f32 unk_30; f32 unk_34; f32 unk_38; f32 unk_3C; f32 unk_40;
    s16 unk_44; u8 pad_46[0x2A];
} Obj_1_bss_10D8;
extern Bss_104C lbl_1_bss_104C;
extern char lbl_1_data_406C[91];
extern char lbl_1_data_40C8[96];
extern Obj_1_bss_10D8 lbl_1_bss_10D8;
extern void OSReport(char *, ...);

void fn_1_C178(void *self) {
    OSReport(lbl_1_data_406C, lbl_1_bss_104C.unk_8, lbl_1_bss_104C.unk_C,
        lbl_1_bss_10D8.unk_4, lbl_1_bss_10D8.unk_8, lbl_1_bss_10D8.unk_C,
        lbl_1_bss_10D8.unk_10, lbl_1_bss_10D8.unk_14, lbl_1_bss_10D8.unk_18,
        lbl_1_bss_10D8.unk_1C, lbl_1_bss_10D8.unk_20);
    OSReport(lbl_1_data_40C8, lbl_1_bss_10D8.unk_28, lbl_1_bss_10D8.unk_2C,
        lbl_1_bss_10D8.unk_30, lbl_1_bss_10D8.unk_34, lbl_1_bss_10D8.unk_38,
        lbl_1_bss_10D8.unk_3C, lbl_1_bss_10D8.unk_40, lbl_1_bss_10D8.unk_44,
        self);
}
/* fzgx:end fn_1_C178 */

/* fzgx:begin camera_report_position */
// Reports the camera's current position values for debugging.
void camera_report_position(void) {
    OSReport(lbl_1_data_4128, lbl_1_bss_10D8.unk_10,
             lbl_1_bss_10D8.unk_14, lbl_1_bss_10D8.unk_18);
}
/* fzgx:end camera_report_position */

/* fzgx:begin fn_1_C304 */
// Reports the camera parameters and caller-supplied value for debugging.
void fn_1_C304(s32 arg) {
    OSReport(lbl_1_data_4198,
             lbl_1_bss_10D8.unk_4, lbl_1_bss_10D8.unk_8,
             lbl_1_bss_10D8.unk_C, lbl_1_bss_10D8.unk_10,
             lbl_1_bss_10D8.unk_14, lbl_1_bss_10D8.unk_18,
             lbl_1_bss_10D8.unk_20, arg,
             lbl_1_bss_10D8.unk_1C);
}
/* fzgx:end fn_1_C304 */

/* fzgx:begin camera_snapshot noprologue */
#include "types.h"

typedef struct CameraGlobals {
    u8 pad_00[0x08];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0x10];
    u32 unk_3C;
    u8 pad_40[0x88];
    u32 unk_C8;
    u32 unk_CC;
    u32 unk_D0;
    u32 unk_D4;
    u32 unk_D8;
    u32 unk_DC;
    u32 unk_E0;
    u32 unk_E4;
    u32 unk_E8;
} CameraGlobals;

extern CameraGlobals lbl_1_bss_1010;

// Copies the live camera state into its snapshot and resets the snapshot flag.
void camera_snapshot(void) {
    lbl_1_bss_1010.unk_08 = lbl_1_bss_1010.unk_C8;
    lbl_1_bss_1010.unk_0C = lbl_1_bss_1010.unk_CC;
    lbl_1_bss_1010.unk_10 = lbl_1_bss_1010.unk_D0;
    lbl_1_bss_1010.unk_14 = lbl_1_bss_1010.unk_D4;
    lbl_1_bss_1010.unk_18 = lbl_1_bss_1010.unk_D8;
    lbl_1_bss_1010.unk_1C = lbl_1_bss_1010.unk_DC;
    lbl_1_bss_1010.unk_20 = lbl_1_bss_1010.unk_E0;
    lbl_1_bss_1010.unk_24 = lbl_1_bss_1010.unk_E4;
    lbl_1_bss_1010.unk_28 = lbl_1_bss_1010.unk_E8;
    lbl_1_bss_1010.unk_3C = 0;
}
/* fzgx:end camera_snapshot */

/* fzgx:begin camera_get_state_object */
// Returns the camera state object's base address.
CameraState* camera_get_state_object(void) {
    return &camera_state;
}
/* fzgx:end camera_get_state_object */

/* fzgx:begin camera_get_state_field_0x4 */
// Returns the address of the camera state field at offset 4.
u32* camera_get_state_field_0x4(void) {
    return &camera_state.unk_4;
}
/* fzgx:end camera_get_state_field_0x4 */

/* fzgx:begin camera_get_state_field_0x8 */
// Returns the address of the camera state field at offset 0x8.
u32* camera_get_state_field_0x8(void) {
    return &camera_state.unk_8;
}
/* fzgx:end camera_get_state_field_0x8 */

/* fzgx:begin camera_get_state_field_0xc */
// Returns a pointer to the camera object's field at offset 0xC.
u32* camera_get_state_field_0xc(void) {
    return &camera_state.unk_C;
}
/* fzgx:end camera_get_state_field_0xc */

/* fzgx:begin camera_get_state_field_0x10 */
// Returns a pointer to the camera object's state field.
u32* camera_get_state_field_0x10(void) {
    return &camera_state.unk_10;
}
/* fzgx:end camera_get_state_field_0x10 */

/* fzgx:begin camera_get_state_field_0x14 */
// Returns a pointer to the camera object's field at offset 0x14.
u32* camera_get_state_field_0x14(void) {
    return &camera_state.unk_14;
}
/* fzgx:end camera_get_state_field_0x14 */

/* fzgx:begin camera_get_state_field_0x18 */
// Returns a pointer to the camera object's state field at offset 0x18.
u32* camera_get_state_field_0x18(void) {
    return &camera_state.unk_18;
}
/* fzgx:end camera_get_state_field_0x18 */

/* fzgx:begin camera_get_state_storage */
// Returns the camera state storage used by the surrounding camera code.
u8* camera_get_state_storage(void) {
    return lbl_1_bss_103C;
}
/* fzgx:end camera_get_state_storage */

/* fzgx:begin camera_get_extended_state_storage noprologue */
#include "types.h"

extern u8 lbl_1_bss_108C[52];

// Returns the storage reserved for the camera's extended state.
u8* camera_get_extended_state_storage(void) {
    return lbl_1_bss_108C;
}
/* fzgx:end camera_get_extended_state_storage */

/* fzgx:begin camera_get_state_flag */
// Returns the current camera state flag.
u8 camera_get_state_flag(void) {
    return lbl_1_bss_1014;
}
/* fzgx:end camera_get_state_flag */

/* fzgx:begin camera_enable_flags */
// Enables the camera state flags.
void camera_enable_flags(void) {
    camera_flag_1 = 1;
    camera_flag_0 = 1;
}
/* fzgx:end camera_enable_flags */

/* fzgx:begin camera_disable_flags */
// Clears the camera state flags.
void camera_disable_flags(void) {
    camera_flag_1 = 0;
    camera_flag_0 = 0;
}
/* fzgx:end camera_disable_flags */

/* fzgx:begin camera_are_flags_enabled */
// Returns whether the camera state flag is set.
u8 camera_are_flags_enabled(void) {
    return camera_flag_1;
}
/* fzgx:end camera_are_flags_enabled */
