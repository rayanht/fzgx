#include "types.h"

extern u8 lbl_801A6CB4;
extern void GXSetDrawDone(void);
extern u32 lbl_801A6CE0;
extern u32 fn_80032368(void);
extern u32 GXGetFifoPtrs(u32, u32 *, u32 *);
extern u32 fn_80032360(void);
extern void fn_80031FF4(void);
extern u32 fn_800700B4(void);
extern u32 fn_80070068(void);
typedef struct Fifo {
    u32 first;
    u8 pad[0x10];
    void *fifo;
} Fifo;

extern Fifo **lbl_801A6D30;
extern void GXSetGPFifo(void *);
extern u32 lbl_801A6CD8;
extern void fn_80072B28(u32);
extern u32 fn_8007001C(void);
extern u32 fn_80035110(u32, u32);
extern u32 fn_80070100(void);
extern u32 fn_8001BE6C(void);
extern u32 lbl_801A6CCC;
extern u32 OSGetTick(void);
extern u32 lbl_801A6CC8;
extern u16 lbl_801A6CC6;
extern u16 lbl_801A6CC4;
extern u32 lbl_801A6CB8;
extern u32 lbl_801A6CC0;
extern u16 lbl_801A6CBC;

void fn_8006FD1C(void) {
    Fifo **table;
    u32 index;
    u32 value_c;
    u32 value_8;

    lbl_801A6CB4 = 0;
    GXSetDrawDone();

    if ((lbl_801A6CE0 & 0x04) != 0) {
        GXGetFifoPtrs(fn_80032368(), &value_c, &value_8);
        fn_80032360();
        fn_80031FF4();
        fn_800700B4();
        GXSetGPFifo(lbl_801A6D30[fn_80070068() + 5]);
    }

    GXGetFifoPtrs(fn_80032360(), &value_c, &value_8);
    lbl_801A6CD8 = value_8;
    fn_80072B28(1);
    fn_8007001C();
    fn_80035110((u32)lbl_801A6D30[0], 1);
    fn_80070100();
    lbl_801A6CCC = fn_8001BE6C();
    lbl_801A6CC8 = OSGetTick();
    lbl_801A6CC6 = 0;
    lbl_801A6CC4 = 0;
    lbl_801A6CB8 = OSGetTick();
    lbl_801A6CC0 = 0;
    lbl_801A6CBC = 0;
}
