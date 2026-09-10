#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/som.h"

extern u32 lbl_1_bss_3BBC;
extern void sprintf(char *, const char *, ...);
extern void fn_1_465D0(char *, int);

/* fzgx:begin fn_1_1383C */
void fn_1_1383C(void) {
    lbl_1_bss_3BBC = 1;
}
/* fzgx:end fn_1_1383C */

/* fzgx:begin fn_1_13A28 */
typedef struct Fn1_13A28 Fn1_13A28;

struct Fn1_13A28 {
    u8 unk_00[4];
    Fn1_13A28 *unk_04;
    Fn1_13A28 *unk_08;
    s32 unk_0c;
    Fn1_13A28 *unk_10;
    u8 unk_14[0x10];
    Fn1_13A28 *unk_24;
    Fn1_13A28 *unk_28;
    Fn1_13A28 *unk_2c;
    Fn1_13A28 *unk_30;
    Fn1_13A28 *unk_34;
    Fn1_13A28 *unk_38;
    Fn1_13A28 *unk_3c;
    Fn1_13A28 *unk_40;
    Fn1_13A28 *unk_44;
    u8 unk_48[8];
};

void fn_1_13A28(Fn1_13A28 *arg0, s32 arg1) {
    Fn1_13A28 *child;

    if (arg0->unk_04 != 0) {
        arg0->unk_04 = (Fn1_13A28 *)((u8 *)arg0->unk_04 + arg1);
    }
    if (arg0->unk_08 != 0) {
        arg0->unk_08 = (Fn1_13A28 *)((u8 *)arg0->unk_08 + arg1);
    }
    if (arg0->unk_10 != 0) {
        arg0->unk_10 = (Fn1_13A28 *)((u8 *)arg0->unk_10 + arg1);
    }

    child = arg0->unk_04;
    if (child->unk_24 != 0) {
        child->unk_24 = (Fn1_13A28 *)((u8 *)child->unk_24 + arg1);
    }
    if (child->unk_28 != 0) {
        child->unk_28 = (Fn1_13A28 *)((u8 *)child->unk_28 + arg1);
    }
    if (child->unk_2c != 0) {
        child->unk_2c = (Fn1_13A28 *)((u8 *)child->unk_2c + arg1);
    }
    if (child->unk_30 != 0) {
        child->unk_30 = (Fn1_13A28 *)((u8 *)child->unk_30 + arg1);
    }
    if (child->unk_34 != 0) {
        child->unk_34 = (Fn1_13A28 *)((u8 *)child->unk_34 + arg1);
    }
    if (child->unk_38 != 0) {
        child->unk_38 = (Fn1_13A28 *)((u8 *)child->unk_38 + arg1);
    }
    if (child->unk_3c != 0) {
        child->unk_3c = (Fn1_13A28 *)((u8 *)child->unk_3c + arg1);
    }
    if (child->unk_40 != 0) {
        child->unk_40 = (Fn1_13A28 *)((u8 *)child->unk_40 + arg1);
    }
    if (child->unk_44 != 0) {
        child->unk_44 = (Fn1_13A28 *)((u8 *)child->unk_44 + arg1);
    }

    if (arg0->unk_0c > 0) {
        s32 i;
        Fn1_13A28 *entry = arg0->unk_10;
        for (i = 0; i < arg0->unk_0c; entry += 1) {
            fn_1_13A28(entry, arg1);
            i++;
        }
    }
}
/* fzgx:end fn_1_13A28 */

/* fzgx:begin fn_1_14D5C */
void fn_1_14D5C(char *arg0, int arg1) {
    char buffer[32];

    sprintf(buffer, (const char *)lbl_1_data_5194, arg0);
    if (arg1 != 0) {
        fn_1_465D0(buffer, 2);
    } else {
        fn_1_465D0(buffer, 1);
    }
}
/* fzgx:end fn_1_14D5C */
