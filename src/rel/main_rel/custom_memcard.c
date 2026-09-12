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

/* fzgx:begin fn_1_131558 noprologue */
#include "types.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[8];
    u32 unk_14;
    u8 pad_18[0x128];
    u8 unk_140[0x1800];
} CustomMemcardState;

extern CustomMemcardState lbl_1_bss_8CA40;
extern u8 lbl_1_data_40EA4[84];
extern char lbl_1_data_40F30[34];

extern void OSPanic(const char* arg0, s32 arg1, const char* arg2, ...);
extern void fn_80008BEC(void* dst, s32 value, u32 size);
extern void fn_1_AA6D8(s32 arg0, u8 arg1, void* arg2);

void fn_1_131558(void) {
    CustomMemcardState* state = &lbl_1_bss_8CA40;
    u8 request[0x24];

    if (state->unk_14 == 0) {
        OSPanic((const char*)lbl_1_data_40EA4, 0x197, (const char*)lbl_1_data_40F30);
        state->unk_00 = -1;
        state->unk_08 = -1;
    } else if (state->unk_08 == -1) {
        state->unk_00 = -1;
    } else {
        fn_80008BEC(state->unk_140, 0, 0x1800);
        fn_80008BEC(request, 0, 0x24);
        request[0] = 3;
        *(void**)((u8*)request + 0x0C) = state->unk_140;
        fn_1_AA6D8(4, (u8)state->unk_08, request);
        state->unk_04 = 7;
    }
}
/* fzgx:end fn_1_131558 */

/* fzgx:begin fn_1_1317B4 */
u32 fn_1_1317B4(void) {
    return lbl_1_bss_8CA6C[0];
}
/* fzgx:end fn_1_1317B4 */

/* fzgx:begin fn_1_1317C4 */
extern u32 lbl_801A6410;


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
        lbl_801A6410, 0x20700, (*(u8 (*)[84])&lbl_1_data_40EA4), 0x1f3);

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

/* fzgx:begin fn_1_132FB4 */
#include "font.h"

extern u32 lbl_1_rodata_8694[4];
extern u32 lbl_1_rodata_86A4[4];
extern const f64 lbl_1_rodata_8600;
extern const f32 lbl_1_rodata_85F0;
extern const f32 lbl_1_rodata_8658;
extern const f32 lbl_1_rodata_86B4;
extern const f32 lbl_1_rodata_86B8;
extern const f32 lbl_1_rodata_86BC;
extern const f32 lbl_1_rodata_86C0;
extern const f32 lbl_1_rodata_86C4;
extern const f32 lbl_1_rodata_86C8;
extern const f32 lbl_1_rodata_86CC;
extern const f32 lbl_1_rodata_86D0;
extern const f32 lbl_1_rodata_86D4;
extern f32 lbl_1_rodata_26F8[22];

extern u8 fn_1_D66B0(void);
extern u8 fn_1_D6740(u8);
extern void fn_80008BEC(void *, int, u32);
extern void fn_1_51564(u16, u16, u16, u16, u16, u16);
extern u32 fn_1_5158C(FontDrawPacket *, u32, u32, u32);
extern int fn_1_4F734(FontDrawPacket *);
extern char *strncpy(char *, const char *, size_t);
extern void fn_1_50164(f32, f32, f32, f32, void *);
extern void fn_1_49410(void);
extern void fn_1_496FC(f32, f32);
extern void fn_1_495C8(s32);
extern void fn_1_4955C(f32, f32);
extern void fn_1_49590(f32);
extern void fn_1_4965C(s32);
extern void fn_1_495B0(s32);
extern void fn_1_4CE48(Obj_1_bss_4B9CC *, f32);

#pragma opt_common_subs off
#pragma opt_propagation off
void fn_1_132FB4(void) {
    FontDrawPacket packet;
    char buf[17];
    u32 tblA[4];
    u32 tblB[4];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    char *pbuf;
    f32 lab_t0;
    u32 var_r26;
    f32 lab_t1;

    var_r29 = 0;
    var_r28 = 0;
    var_r26 = 0;
    var_r31 = 0x18;
    var_r30 = 0x43;

    tblA[0] = lbl_1_rodata_8694[0];
    tblA[1] = lbl_1_rodata_8694[1];
    tblA[2] = lbl_1_rodata_8694[2];
    tblA[3] = lbl_1_rodata_8694[3];
    tblB[0] = lbl_1_rodata_86A4[0];
    tblB[1] = lbl_1_rodata_86A4[1];
    tblB[2] = lbl_1_rodata_86A4[2];
    tblB[3] = lbl_1_rodata_86A4[3];

    pbuf = buf;

    do {
        if (var_r29 == fn_1_D66B0()) {
            var_r28 += 1;
            var_r26 += 4;
        } else if (fn_1_D6740(var_r29) != 0) {
            fn_80008BEC(pbuf, 0, 0x11);
            packet = *(FontDrawPacket *)lbl_1_rodata_26F8;
            packet.image = 0x10000 - 0x61EC;
            fn_1_51564(0, 0, 0x18, 0x14, 2, 2);
            fn_1_5158C(&packet, packet.image, (s16)(var_r28 % 2), (s16)(var_r28 / 2));
            packet.x = (f32)var_r31;
            packet.y = lbl_1_rodata_86B4;
            fn_1_4F734(&packet);
            strncpy(pbuf, (const char *)(*(u32 *)((u8 *)tblA + var_r26)), 0x10);
            packet = *(FontDrawPacket *)lbl_1_rodata_26F8;
            packet.image = 12;
            *(u32 *)((u8 *)&packet + 0x30) = 5;
            packet.x = (f32)var_r31;
            packet.y = lbl_1_rodata_86B8;
            fn_1_50164(lbl_1_rodata_86BC, lbl_1_rodata_86C0, lbl_1_rodata_86C4, lbl_1_rodata_86C4, &packet);
            fn_1_49410();
            fn_1_496FC((f32)var_r30, lbl_1_rodata_86C8);
            fn_1_495C8(1);
            fn_1_4955C(lbl_1_rodata_86CC, lbl_1_rodata_86CC);
            fn_1_49590(lbl_1_rodata_85F0);
            fn_1_4965C(2);
            fn_1_495B0((0x3u << 30));
            fn_1_4CE48((Obj_1_bss_4B9CC *)pbuf, lbl_1_rodata_86D0);
            fn_1_49410();
            lab_t0 = (f32)var_r30;
            fn_1_496FC(lab_t0, lbl_1_rodata_8658);
            fn_1_495C8(1);
            fn_1_4955C(lbl_1_rodata_86D4, lbl_1_rodata_86D4);
            fn_1_49590(lbl_1_rodata_85F0);
            fn_1_4965C(2);
            fn_1_495B0((0x3u << 30));
            lab_t1 = lbl_1_rodata_86D0;
            fn_1_4CE48((Obj_1_bss_4B9CC *)(*(u32 *)((u8 *)tblB + var_r26)), lab_t1);
            var_r31 += 0x57;
            var_r30 += 0x57;
            var_r28 += 1;
            var_r26 += 4;
        }
        var_r29 += 1;
    } while (var_r29 < 4);
}
#pragma opt_propagation reset

#pragma opt_common_subs reset
/* fzgx:end fn_1_132FB4 */

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
