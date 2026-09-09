#include "types.h"
struct fn_80075D48_Arg0 {
    u32 unk_0;
};
extern void fn_80073C6C(s32);
extern void fn_80072AB0(s32, s32, s32);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern void fn_80072E20(s32, s32, s32, s32, u8, s32);
extern void fn_80073620(s32, s32);

s32 fn_80072CC4(s32, s32, s32, s32, s32); /* extern */
s32 fn_80072D64(s32, s32, s32, s32, s32, s32); /* extern */
s32 fn_800734A8(s32, s32, s32, s32);        /* extern */

void fn_80075D48(void *arg0, void *arg1) {
    s16 temp_r0;
    s16 temp_r0_2;

    fn_80073C6C(*(s32 *)((u8 *)(arg0) + 0));
    fn_80072AB0(*(s32 *)((u8 *)(arg0) + 0), 0, 0);
    fn_800734A8(*(s32 *)((u8 *)(arg0) + 0), *(s32 *)((u8 *)(arg0) + 4), *(s32 *)((u8 *)(arg0) + 12), 4);
    temp_r0 = *(s16 *)((u8 *)(arg1) + 16);
    switch (temp_r0) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), 0xF, 8, 0xC, *(s32 *)((u8 *)(arg1) + 8));
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1, 0);
        break;
    case 2:                                         /* switch 1 */
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), 0xF, 8, 0xC, *(s32 *)((u8 *)(arg1) + 8));
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 1, 0, 0, 1, 0);
        break;
    case 0:                                         /* switch 1 */
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), 0xF, 8, *(s32 *)((u8 *)(arg1) + 8), 0xF);
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1, 0);
        break;
    case 4:                                         /* switch 1 */
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), 0xF, 8, 0xA, 0xF);
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1, 3);
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 7, 7, 7, *(s32 *)((u8 *)(arg1) + 12));
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        (*(s32 *)((u8 *)(arg0) + 0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0)) + 1);
        fn_80073C6C(*(s32 *)((u8 *)(arg0) + 0));
        fn_80072AB0(*(s32 *)((u8 *)(arg0) + 0), 0, 0);
        fn_800734A8(*(s32 *)((u8 *)(arg0) + 0), *(s32 *)((u8 *)(arg0) + 4), *(s32 *)((u8 *)(arg0) + 12), 0xFF);
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), *(s32 *)((u8 *)(arg1) + 8), 6, 9, 0xF);
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1, 0);
        break;
    case 3:                                         /* switch 1 */
        fn_80072C24(*(s32 *)((u8 *)(arg0) + 0), 0xF, 0xF, 0xF, *(s32 *)((u8 *)(arg1) + 8));
        fn_80072D64(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1, 0);
        break;
    }
    temp_r0_2 = *(s16 *)((u8 *)(arg1) + 18);
    switch (temp_r0_2) {                            /* switch 2; irregular */
    case 1:                                         /* switch 2 */
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 4, 7, 7, *(s32 *)((u8 *)(arg1) + 12));
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        break;
    case 2:                                         /* switch 2 */
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 4, 7, 7, *(s32 *)((u8 *)(arg1) + 12));
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 1, 0, 0, 1U, 0);
        break;
    case 0:                                         /* switch 2 */
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 7, 4, *(s32 *)((u8 *)(arg1) + 12), 7);
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        break;
    case 4:                                         /* switch 2 */
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 7, 7, 7, 4);
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        break;
    case 5:                                         /* switch 2 */
        fn_80073620(*(s32 *)((u8 *)(arg0) + 0), 0);
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 7, 7, 7, 6);
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        break;
    case 3:                                         /* switch 2 */
        fn_80072CC4(*(s32 *)((u8 *)(arg0) + 0), 7, 7, 7, *(s32 *)((u8 *)(arg1) + 12));
        fn_80072E20(*(s32 *)((u8 *)(arg0) + 0), 0, 0, 0, 1U, 0);
        break;
    }
    (*(s32 *)((u8 *)(arg0) + 0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0)) + 1);
    (*(s32 *)((u8 *)(arg0) + 4)) = (s32) ((*(s32 *)((u8 *)(arg0) + 4)) + 1);
}
