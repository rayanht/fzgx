#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/face.h"

extern u32 lbl_801A6410;
extern u32 lbl_1_bss_7ACEC;
extern u32 fn_1_45D0(u32, u32, void*, u32);
extern u32 fn_80008F88(void*, u32);
extern void fn_80009064(u32);
extern void fn_1_46B4(u32, u32, u8*, int);
extern void fn_1_D2F50(void);
extern void fn_80071718(u32);
extern void fn_800711A8(u32);
extern void fn_1_D2F84(void);
extern s16 fn_1_3F0C8(void *obj);
extern u32 fn_1_864E8(u32 value);
extern void OSPanic(char*, ...);
extern u32 fn_1_86810(u32);
extern void qsort(void*, u32, u32, void*);
extern s32 fn_1_D2E18(u8*, u8*);
extern u32 lbl_1_bss_7AD00;
extern u32 lbl_1_bss_7AD04;
extern u32 lbl_1_bss_7AD08[7];
extern u32 lbl_1_bss_7AD24[9];
extern u32 lbl_801A6CE0;
extern u32 lbl_801A6CFC;
extern void* fn_1_48E8(u32, u32);
extern void OSLink(void*, void*);
extern void OSReport(char*, ...);

/* fzgx:begin fn_1_D1780 */
void fn_1_D1780(void) {
    u32 result;

    lbl_1_bss_7ACEC = 0x40000;
    result = fn_1_45D0(lbl_801A6410, 0x40000, lbl_1_data_3DA2C, 0x14a);
    lbl_1_bss_7ACF0 = result;
    lbl_1_data_3D924 = fn_80008F88((void*)result, result + lbl_1_bss_7ACEC);
}
/* fzgx:end fn_1_D1780 */

/* fzgx:begin fn_1_D17E8 */
void fn_1_D17E8(void) {
    fn_80009064(lbl_1_data_3D924);
    fn_1_46B4(lbl_801A6410, lbl_1_bss_7ACF0, lbl_1_data_3DA2C, 0x152);
    lbl_1_data_3D924 = -1;
}
/* fzgx:end fn_1_D17E8 */

/* fzgx:begin fn_1_D1F88 */
void fn_1_D1F88(void) {
    Obj_1_bss_7ACD8_Target* state;
    s32 i;
    Obj_1_bss_7ACD8_Target* obj;
    u32 index;

    state = (Obj_1_bss_7ACD8_Target*)&lbl_1_bss_7ACD8;
    if ((s32)lbl_1_data_3D924 != -1) {
        fn_1_D2F50();
        i = 0;
        obj = (Obj_1_bss_7ACD8_Target*)state->unk_0;
        for (; i < 6; i++, obj = (Obj_1_bss_7ACD8_Target*)((u8*)obj + 0x64)) {
            if (obj->unk_60 != 0) {
                fn_1_46B4(lbl_801A6410, obj->unk_60, lbl_1_data_3DA2C, 0x271);
                obj->unk_60 = 0;
            }
            if (i < *(u8*)((u8*)state + 0xD)) {
                index = (obj->unk_4 & 0xFF) << 2;
                if (*(u32*)(state->unk_8 + index) != 0) {
                    fn_80071718(*(u32*)(state->unk_8 + index));
                    *(u32*)(state->unk_8 + index) = 0;
                }
                if (*(u32*)(state->unk_4 + index) != 0) {
                    fn_800711A8(*(u32*)(state->unk_4 + index));
                    *(u32*)(state->unk_4 + index) = 0;
                }
            }
        }
        if (state->unk_4 != 0) {
            fn_1_46B4(lbl_801A6410, state->unk_4, lbl_1_data_3DA2C, 0x277);
            state->unk_4 = 0;
        }
        if (state->unk_8 != 0) {
            fn_1_46B4(lbl_801A6410, state->unk_8, lbl_1_data_3DA2C, 0x278);
            state->unk_8 = 0;
        }
        if (state->unk_0 != 0) {
            fn_1_46B4(lbl_801A6410, state->unk_0, lbl_1_data_3DA2C, 0x27B);
            state->unk_0 = 0;
        }
        fn_1_D2F84();
    }
}
/* fzgx:end fn_1_D1F88 */

/* fzgx:begin fn_1_D2D24 */
Obj_1_bss_7ACD8_Target *fn_1_D2D24(s32 index) {
    return &lbl_1_bss_7ACD8[index];
}
/* fzgx:end fn_1_D2D24 */

/* fzgx:begin fn_1_D2D38 */
u32 fn_1_D2D38(void) {
    return lbl_1_bss_7ACE8;
}
/* fzgx:end fn_1_D2D38 */

/* fzgx:begin fn_1_D2D48 */
u8 fn_1_D2D48(void) {
    return lbl_1_bss_7ACE5;
}
/* fzgx:end fn_1_D2D48 */

/* fzgx:begin fn_1_D2D58 */
Obj_1_bss_7ACD8_Target *fn_1_D2D58(void *obj) {
    s32 i;

    for (i = 0; i < lbl_1_bss_7ACE5; i++) {
        if ((u32)obj == lbl_1_bss_7ACD8[i].unk_10) {
            if (fn_1_3F0C8(obj) == 0x29 &&
                (fn_1_864E8(lbl_1_bss_7ACD8[i].unk_4) & 0x20000880) != 0) {
                return 0;
            }
            return &lbl_1_bss_7ACD8[i];
        }
    }
    return 0;
}
/* fzgx:end fn_1_D2D58 */

/* fzgx:begin fn_1_D2E18 */
// fn_1_D2E18: 3-way byte comparison (a > b returns 1, a < b returns -1, a == b returns 0)
s32 fn_1_D2E18(u8* a, u8* b) {
    u8 va = *a;
    u8 vb = *b;
    s32 d1;
    s32 d2;
    if (va > vb) {
        return 1;
    }
    d1 = va - vb;
    d2 = vb - va;
    return (d1 | d2) >> 31;
}
/* fzgx:end fn_1_D2E18 */

/* fzgx:begin fn_1_D2E44 */
s32 fn_1_D2E44(u32 index) {
    u8 values[4];
    u32 j;
    u32 i;

    if ((s32)lbl_1_bss_7ACE8 != 0) {
        if (index >= 4) {
            OSPanic((char*)lbl_1_data_3DA2C, 0x4f3, (char*)lbl_1_data_3DB2C);
        }
        for (i = 0; (u8)i < lbl_1_bss_7ACE5; i++) {
            values[(u8)i] = fn_1_86810((u8)i);
        }
        qsort(values, lbl_1_bss_7ACE5, 1, fn_1_D2E18);
        for (j = 0; (u8)j < lbl_1_bss_7ACE5; j++) {
            if (values[(u8)j] == (u8)fn_1_86810(index)) {
                return j;
            }
        }
        return values[index];
    }
    return fn_1_86810(index);
}
/* fzgx:end fn_1_D2E44 */

/* fzgx:begin fn_1_D2FB0 */
u32 fn_1_D2FB0(void) {
    return lbl_1_data_3D924;
}
/* fzgx:end fn_1_D2FB0 */

/* fzgx:begin fn_1_D2FC0 noprologue */
#include "types.h"

extern u32 fn_1_D3020(void *, void *);
extern u8 lbl_1_bss_7ACF8[8];
extern void fn_80083DB0(void *, void *);
extern void strcat(void *, void *);

extern void OSReport(const char *, ...);
#pragma section code_type ".fzgxpool"
static void fzgx_string_layout(void) {
    /* fzgx-allow: S2 layout primer: MWCC emits string literals in first-use order; the section is dropped at integration */
    OSReport("fze.");
    OSReport("window");
    OSReport(".rel");
}
#pragma section code_type ".text"

void fn_1_D2FC0(void) {
    struct {
        u32 a[16];
    } loc_8;

    
    fn_80083DB0((void *)&loc_8, (void *)(u32)("fze."));
    strcat((void *)&loc_8, (void *)(u32)("window"));
    strcat((void *)&loc_8, (void *)(u32)(".rel"));
    fn_1_D3020((void *)&loc_8, (void *)&lbl_1_bss_7ACF8);
}
/* fzgx:end fn_1_D2FC0 */

/* fzgx:begin fn_1_D3020 */
#include "types.h"

typedef struct LocalData {
    u8 unk_0[0x34];
    u32 size;
} LocalData;

typedef struct Output {
    void* data;
    void* aux;
} Output;

typedef struct Allocated {
    u8 unk_0[0x20];
    u32 size;
    u8 unk_24[0x10];
    void (*init)(void);
} Allocated;

extern int DVDOpen(void*, LocalData*);
extern int fn_80006354(LocalData*, void*, u32, u32);
extern void DVDClose(LocalData*);

void fn_1_D3020(void* unused, Output* output) {
    LocalData local;
    Allocated* object;
    s32 size;

    if ((lbl_801A6CE0 & 0x8) == 0) {
        return;
    }
    output->data = 0;
    output->aux = 0;
    if (DVDOpen(unused, &local) == 0) {
        return;
    }
    size = (local.size + 0x1f) & ~0x1f;
    if (lbl_801A6CFC < 0x82000000) {
        object = fn_1_48E8(size, 0x20);
        output->data = object;
    } else {
        OSReport((*(char (*)[51])&lbl_1_data_3DB58));
        return;
    }
    if (fn_80006354(&local, output->data, size, 0) != 0) {
        object = output->data;
        size = 0x20;
        if (object->size != 0) {
            size = object->size;
        }
        output->aux = fn_1_48E8(size, 0x20);
        OSLink(output->data, output->aux);
        object = output->data;
        object->init();
    } else {
        OSReport((*(char (*)[51])&lbl_1_data_3DB8C));
        output->data = 0;
    }
    DVDClose(&local);
}
/* fzgx:end fn_1_D3020 */

/* fzgx:begin fn_1_D3144 */
// fn_1_D3144: Conditionally call function pointer from BSS
void fn_1_D3144(void) {
    u32 fn_ptr = lbl_1_bss_7AD00;
    if (fn_ptr != 0) {
        ((void (*)(void))fn_ptr)();
    }
}
/* fzgx:end fn_1_D3144 */

/* fzgx:begin fn_1_D3178 */
void fn_1_D3178(void) {
    u32 fn_ptr = lbl_1_bss_7AD04;
    if (fn_ptr != 0) {
        ((void (*)(void))fn_ptr)();
    }
}
/* fzgx:end fn_1_D3178 */

/* fzgx:begin fn_1_D31AC */
void fn_1_D31AC(void) {
    u32 fn_ptr = lbl_1_bss_7AD08[0];
    if (fn_ptr != 0) {
        ((void (*)(void))fn_ptr)();
    }
}
/* fzgx:end fn_1_D31AC */

/* fzgx:begin fn_1_D31E0 */
void fn_1_D31E0(void) {
    u32 fn_ptr = lbl_1_bss_7AD24[0];
    if (fn_ptr != 0) {
        ((void (*)(void))fn_ptr)();
    }
}
/* fzgx:end fn_1_D31E0 */
