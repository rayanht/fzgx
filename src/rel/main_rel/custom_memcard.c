#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/custom_memcard.h"

extern u32 lbl_801A6410;
extern u8 fn_1_B7C00(void);
extern s32 fn_1_B7CD4(void);
extern s32 fn_1_B7C5C(void);
extern void OSReport(const char* format, ...);
extern void fn_1_46B4(u32 arg0, void* arg1, u8* arg2, s32 arg3);
extern void fn_80008BA8(void*, void*, s32);
extern u32 lbl_1_bss_8CA6C[1605];
extern void fn_1_1324C4(void *arg0);
extern void fn_1_132774(void *arg0);

extern u32 lbl_801A6410;
extern u8 fn_1_B7C00(void);
extern s32 fn_1_B7CD4(void);
extern s32 fn_1_B7C5C(void);
extern void OSReport(const char* format, ...);
extern void fn_80008BA8(void*, void*, s32);
extern void fn_1_46B4(u32 arg0, void* arg1, u8* arg2, s32 arg3);

/* fzgx:begin fn_1_1312F0 */
// Reset the memcard state after reporting an unavailable card.

void fn_1_1312F0(void) {
    u8* state = (u8*)&lbl_1_bss_8CA40;
    void* memcard;

    if (fn_1_B7C00() == 0) {
        if (fn_1_B7CD4() == 0) {
            OSReport((const char*)lbl_1_data_40EF8, fn_1_B7C5C());
        }

        memcard = *(void**)(state + 0x18);
        *(s32*)(state + 0x00) = -1;
        *(s32*)(state + 0x08) = -1;
        *(s32*)(state + 0x0c) = 0;
        if (memcard != 0) {
            fn_1_46B4(lbl_801A6410, memcard, lbl_1_data_40EA4, 0x136);
            *(void**)(state + 0x18) = 0;
        }
    }
}
/* fzgx:end fn_1_1312F0 */

/* fzgx:begin fn_1_1314A4 */
// Reset the card state and release the card after an unavailable-card report.
void fn_1_1314A4(void) {
    u8* state = (u8*)&lbl_1_bss_8CA40;
    void* card;

    if (fn_1_B7C00() == 0) {
        if (fn_1_B7CD4() == 0) {
            OSReport((const char*)lbl_1_data_40EF8, fn_1_B7C5C());
        }

        fn_80008BA8(*(void**)(state + 0x10),
                    *(void**)(state + 0x18),
                    0x20700);

        card = *(void**)(state + 0x18);
        *(s32*)(state + 0x00) = -1;
        *(s32*)(state + 0x08) = -1;
        *(void**)(state + 0x10) = 0;

        if (card != 0) {
            fn_1_46B4(lbl_801A6410, card, lbl_1_data_40EA4, 0x188);
            *(void**)(state + 0x18) = 0;
        }
    }
}
/* fzgx:end fn_1_1314A4 */

/* fzgx:begin fn_1_1317B4 */
u32 fn_1_1317B4(void) {
    return lbl_1_bss_8CA6C[0];
}
/* fzgx:end fn_1_1317B4 */

/* fzgx:begin fn_1_1317C4 */
extern u32 lbl_801A6410;
extern u8 lbl_1_data_40EA4[84];
extern u32 fn_1_4630(u32 arg0, u32 arg1, u8 *arg2, u32 arg3);
extern void fn_80008BEC(void *arg0, u32 arg1, u32 arg2);
extern s32 fn_1_B7E98(s32 arg0);
extern void fn_1_AA6D8(s32 arg0, s32 arg1, void *arg2);

typedef struct {
    u8 unk_0;
    u8 pad_1[3];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u8 pad_10[0x14];
} MemcardRequest;

void fn_1_1317C4(void) {
    MemcardRequest request;

    lbl_1_bss_8E384.unk_0 = fn_1_4630(
        lbl_801A6410, 0x20700, lbl_1_data_40EA4, 0x1f3);

    fn_80008BEC(&request, 0, 0x24);
    request.unk_4 = 4;
    request.unk_4 |= 0x4000;
    request.unk_4 |= 0x2000;
    request.unk_0 = 3;
    request.unk_C = lbl_1_bss_8E384.unk_0;
    request.unk_8 = 0;

    if (fn_1_B7E98(0) != 0) {
        fn_1_AA6D8(2, 0, &request);
    } else if (fn_1_B7E98(1) != 0) {
        fn_1_AA6D8(2, 1, &request);
    } else {
        fn_1_AA6D8(2, 0, &request);
    }

    lbl_1_bss_8E380 = 1;
}
/* fzgx:end fn_1_1317C4 */

/* fzgx:begin fn_1_1318B8 */
u8 fn_1_1318B8(void) {
    return lbl_1_bss_8E380 != 0;
}
/* fzgx:end fn_1_1318B8 */

/* fzgx:begin fn_1_1318D4 */
// Completes the pending memory-card operation and clears its active flag.
s32 fn_1_1318D4(void) {
    s32 error;

    if (lbl_1_bss_8E380 == 0) {
        return 0;
    }

    if (fn_1_B7C00() != 0) {
        return 1;
    }

    if (fn_1_B7CD4() == 0) {
        error = fn_1_B7C5C();
        OSReport((const char*)lbl_1_data_40EF8, error);
    }

    if (lbl_1_bss_8E384.unk_0 != 0) {
        fn_1_46B4(lbl_801A6410, (void*)lbl_1_bss_8E384.unk_0,
                   lbl_1_data_40EA4, 0x22b);
        lbl_1_bss_8E384.unk_0 = 0;
    }

    lbl_1_bss_8E380 = 0;
    return 1;
}
/* fzgx:end fn_1_1318D4 */

/* fzgx:begin fn_1_131B90 */
typedef struct Obj Obj;

struct Obj {
    s16 index;
    u8 pad_2[2];
    u32 field_4;
    u32 field_8;
    u8 pad_c[0x2c];
    u32 field_38;
    u32 field_3c;
    u32 field_40;
    u32 field_44;
    u32 field_48;
    u32 field_4c;
    u32 field_50[1];
};

extern void fn_1_13198C(s16, u32*, u32*, u32, u32, u32);

#pragma opt_propagation off
s32 fn_1_131B90(Obj* obj) {
    u32 local_a[3];
    u32 local_b[3];
    u32 a0;
    u32 a1;
    u32 b0;
    u32 b1;
    s16 index;

    a1 = obj->field_44;
    a0 = obj->field_48;
    local_b[0] = a1;
    local_b[1] = a0;
    local_b[2] = obj->field_4c;
    b1 = obj->field_38;
    b0 = obj->field_3c;
    local_a[0] = b1;
    local_a[1] = b0;
    local_a[2] = obj->field_40;
    index = obj->index;
    fn_1_13198C(index, local_a, local_b, obj->field_4, obj->field_8,
                obj->field_50[index]);
    return 0;
}
#pragma opt_propagation reset
/* fzgx:end fn_1_131B90 */

/* fzgx:begin fn_1_132488 */
void fn_1_132488(void *arg0) {
    if ((lbl_1_bss_8B3A0.unk_94 & 0x40000000) != 0) {
        fn_1_1324C4(arg0);
    } else {
        fn_1_132774(arg0);
    }
}
/* fzgx:end fn_1_132488 */

/* fzgx:begin fn_1_137364 */
// Writes the indexed three-byte value, or the fallback value when the index is out of range.
void fn_1_137364(s16 arg0, u8* arg1, u8* arg2, u8* arg3) {
    if (arg0 < 0x29) {
        u32* values = (u32*)&lbl_1_data_416B8;

        *arg1 = values[arg0 * 3];
        *arg2 = values[arg0 * 3 + 1];
        *arg3 = values[arg0 * 3 + 2];
    } else {
        *arg2 = 2;
        *arg1 = 2;
        *arg3 = 2;
    }
}
/* fzgx:end fn_1_137364 */

/* fzgx:begin fn_1_13F7F8 */
u32 fn_1_13F7F8(s16 arg0, s16 arg1) {
    return ((u32 (*)[6])&lbl_1_data_414D8)[arg0][arg1];
}
/* fzgx:end fn_1_13F7F8 */
