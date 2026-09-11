#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bitmap.h"

extern void fn_1_48214(int index, int enabled);
extern void fn_1_4DDC0(void);
extern void fn_1_4F724(void);
extern s32 lbl_801A6410;
extern void OSPanic(const unsigned char *, ...);
extern int fn_1_45D0(int, int, const unsigned char *, int);
extern int fn_80008F88(int, int);
extern void fn_8006FDEC(void);
extern void fn_80009064(u32 value);
extern void fn_1_46B4(u32 arg0, u32 arg1, char *arg2, s32 arg3);
extern void *fn_1_48730(u32 value);
extern void fn_1_47AD4(Obj_1_data_FCD4 *obj, u8 value, int arg2, int arg3);
extern f32 lbl_1_rodata_10C0[5];
extern f32 lbl_1_bss_3E05C;

extern void *fn_1_48730(u32 value);

/* fzgx:begin fn_1_47EE4 noprologue */
#include "rel/main_rel/bitmap.h"

typedef struct {
    s32 unk_0;
    u8 pad_4[0x24];
} Fn147EE4Entry;

extern void OSPanic(const unsigned char *, ...);
extern void fn_1_47AD4(Fn147EE4Entry *object, s32 arg1, s32 arg2, s32 arg3);

void fn_1_47EE4(s32 index) {
    Fn147EE4Entry *object;
    s32 valid;

    object = (Fn147EE4Entry *)((u8 *)&lbl_1_data_FCD4 + index * 0x28);
    if (index > 0xbb) {
        valid = 0;
    } else {
        valid = index >= 0;
    }
    if (valid == 0) {
        OSPanic(lbl_1_data_1A368, 0x1a8, lbl_1_data_1A374);
    }
    if (object->unk_0 == 0) {
        fn_1_47AD4(object, 0, 1, 1);
    }
}
/* fzgx:end fn_1_47EE4 */

/* fzgx:begin fn_1_47F74 noprologue */
#include "rel/main_rel/bitmap.h"

typedef struct {
    s32 unk_0;
    u8 pad_4[0x24];
} Fn147F74Entry;

extern void OSPanic(const unsigned char *, ...);
extern void fn_1_47AD4(Fn147F74Entry *object, s32 arg1, s32 arg2, s32 arg3);

void fn_1_47F74(s32 index) {
    Fn147F74Entry *object;
    s32 valid;

    object = (Fn147F74Entry *)((u8 *)&lbl_1_data_FCD4 + index * 0x28);
    if (index > 0xbb) {
        valid = 0;
    } else {
        valid = index >= 0;
    }
    if (valid == 0) {
        OSPanic(lbl_1_data_1A368, 0x1b5, lbl_1_data_1A374);
    }
    if (object->unk_0 == 0) {
        fn_1_47AD4(object, 0, 0, 1);
    }
}
/* fzgx:end fn_1_47F74 */

/* fzgx:begin fn_1_4811C */
// Enables the bitmap entry identified by the caller.
void fn_1_4811C(int arg) {
    fn_1_48214(arg, 1);
}
/* fzgx:end fn_1_4811C */

/* fzgx:begin fn_1_48140 */
// Disables the bitmap entry supplied by the caller.
void fn_1_48140(int index) {
    fn_1_48214(index, 0);
}
/* fzgx:end fn_1_48140 */

/* fzgx:begin fn_1_48164 */
// Enables matching bitmap entries in the shared bitmap table.
void fn_1_48164(int value) {
    s16 index;
    Obj_1_data_FCD4 *entry;

    index = 1;
    entry = (Obj_1_data_FCD4 *)((u8 *)&lbl_1_data_FCD4 + 0x28);
    for (; index < 0xbc; index++, entry = (Obj_1_data_FCD4 *)((u8 *)entry + 0x28)) {
        if ((s32)entry->unk_0 != 0 && entry->unk_24 == value) {
            fn_1_48214(index, 1);
        }
    }
}
/* fzgx:end fn_1_48164 */

/* fzgx:begin fn_1_481E8 */
// Initializes the bitmap entry and refreshes the related bitmap state.
void fn_1_481E8(int arg0) {
    fn_1_48214(arg0, 0);
    fn_1_4DDC0();
    fn_1_4F724();
}
/* fzgx:end fn_1_481E8 */

/* fzgx:begin fn_1_48418 */
typedef struct {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
} BitmapSlot;

void fn_1_48418(int index) {
    BitmapSlot *obj = (BitmapSlot *)&lbl_1_data_6CA0 + index;
    int valid;
    if (index > 2) {
        valid = 0;
    } else {
        valid = index >= 0;
    }
    if (valid == 0) {
        OSPanic(lbl_1_data_1A368, 0x248, lbl_1_data_1A390);
    }
    if (obj->unk_0 == -1) {
        obj->unk_4 = fn_1_45D0(lbl_801A6410, obj->unk_8, lbl_1_data_1A368, 0x250);
        obj->unk_0 = fn_80008F88(obj->unk_4, obj->unk_4 + obj->unk_8);
    }
}
/* fzgx:end fn_1_48418 */

/* fzgx:begin fn_1_484CC */
// Releases a bitmap and invalidates dependent texture records.
void fn_1_484CC(s32 index) {
    u8 *texture_record;
    s16 texture_index;
    u32 *bitmap_entry;

    bitmap_entry = (u32 *)((u8 *)&lbl_1_data_6CA0 + index * 12);
    if (*(s32 *)bitmap_entry == -1) {
        return;
    }

    fn_8006FDEC();
    texture_index = 1;
    texture_record = (u8 *)&lbl_1_data_FCD4 + 0x28;
    while (texture_index < 188) {
        if (*(s32 *)texture_record != 0 && texture_record[0x24] == index) {
            fn_1_48214(texture_index, 1);
        }
        texture_index++;
        texture_record += 0x28;
    }

    fn_80009064(bitmap_entry[0]);
    fn_1_46B4(lbl_801A6410, bitmap_entry[1],
              (char *)lbl_1_data_1A368, 0x265);
    bitmap_entry[0] = (u32)-1;
}
/* fzgx:end fn_1_484CC */

/* fzgx:begin fn_1_485A8 */
u32 fn_1_485A8(s32 index) {
    return ((Obj_1_data_FCD4 *)((u8 *)&lbl_1_data_FCD4 + index * 0x28))->unk_0 != 0;
}
/* fzgx:end fn_1_485A8 */

/* fzgx:begin fn_1_485C8 noprologue */
#include "types.h"

extern struct fn_1_485C8_lbl_1_data_FCD4 lbl_1_data_FCD4;
extern u32 lbl_1_bss_3E020;

struct fn_1_485C8_lbl_1_data_FCD4_0_E40 {
    u8 pad_0[0x20];
    u32 unk_20;
    u8 pad_24[0x4];
};
struct fn_1_485C8_lbl_1_data_FCD4 {
    struct fn_1_485C8_lbl_1_data_FCD4_0_E40 unk_0[1];
};

void fn_1_485C8(u32 arg0) {
    lbl_1_bss_3E020 = lbl_1_data_FCD4.unk_0[arg0].unk_20;
}
/* fzgx:end fn_1_485C8 */

/* fzgx:begin fn_1_48690 */
// Return the current bitmap width, or the default width when no bitmap is active.
u16 fn_1_48690(u32 unused) {
    void *bitmap = fn_1_48730(unused);

    if (bitmap != 0) {
        return *(u16 *)((u8 *)bitmap + 8);
    }

    return 8;
}
/* fzgx:end fn_1_48690 */

/* fzgx:begin fn_1_486C4 */
// Return the current bitmap height, or the default height when no bitmap is active.
u16 fn_1_486C4(u32 value) {
    void *bitmap = (void *)fn_1_48730(value);

    if (bitmap != 0) {
        return *(u16 *)((u8 *)bitmap + 0xA);
    }
    return 8;
}
/* fzgx:end fn_1_486C4 */

/* fzgx:begin fn_1_486F8 */
// Return the bitmap entry flags for the slot identified by value.
u32 fn_1_486F8(u32 value) {
    void *bitmap = fn_1_48730(value);

    if (bitmap != 0) {
        return *(u32 *)bitmap & 0x1F;
    }
    return 0;
}
/* fzgx:end fn_1_486F8 */

/* fzgx:begin fn_1_48730 */
// Look up the bitmap data for the table and slot encoded in value.
void *fn_1_48730(u32 value) {
    u32 table_index = (value >> 8) & 0xffff;
    u32 slot_index = value & 0xff;
    Obj_1_data_FCD4 *entry =
        (Obj_1_data_FCD4 *)((u8 *)&lbl_1_data_FCD4 + table_index * 0x28);

    if (entry != 0 && (s32)entry->unk_0 == 1 && entry->unk_20 != 0) {
        return (u8 *)entry->unk_20->unk_4 + ((u8)slot_index << 4);
    }
    return 0;
}
/* fzgx:end fn_1_48730 */

/* fzgx:begin fn_1_4877C */
// fn_1_4877C: empty in retail (single blr).
void fn_1_4877C(void) {
}
/* fzgx:end fn_1_4877C */

/* fzgx:begin fn_1_48780 */
void fn_1_48780(void) {
    Obj_1_data_FCD4 *obj;
    int i;

    obj = (Obj_1_data_FCD4 *)((u8 *)&lbl_1_data_FCD4 + 0x28);
    for (i = 1; i < 0xBC; i++) {
        if ((int)obj->unk_0 != 0) {
            fn_1_47AD4(obj, obj->unk_24, 0, 0);
        }
        obj = (Obj_1_data_FCD4 *)((u8 *)obj + 0x28);
    }
}
/* fzgx:end fn_1_48780 */

/* fzgx:begin fn_1_4AEE8 */
u32 fn_1_4AEE8(u32 value) {
    u32 previous = lbl_1_data_1BCC4;

    lbl_1_bss_3E05C = lbl_1_rodata_10C0[0];
    lbl_1_data_1BCC4 = value;

    return previous;
}
/* fzgx:end fn_1_4AEE8 */
