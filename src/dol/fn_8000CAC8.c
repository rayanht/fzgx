
#include "types.h"

typedef enum {
    OS_FONT_ENCODE_ANSI,
    OS_FONT_ENCODE_SJIS,
    OS_FONT_ENCODE_2,
    OS_FONT_ENCODE_UTF8,
    OS_FONT_ENCODE_UTF16,
    OS_FONT_ENCODE_UTF32,
    OS_FONT_ENCODE_MAX
} OSFontEncode;

u16 fn_8000CDD8(void);

void (*DVDLowClearCallback())(u32);

extern u16 lbl_80122F50[];

extern u16 lbl_801230D0[];

static inline BOOL IsSjisTrailByte(u8 c) { return (0x40 <= c && c <= 0xFC) && (c != 0x7F); }

int fn_8000CAC8(u16 code) {
    u16 encode = fn_8000CDD8();
    if (encode == OS_FONT_ENCODE_SJIS) {
        if (code >= 0x20 && code <= 0xDF) {
            return lbl_80122F50[code - 0x20];
        }
        if (code > 0x889E && code <= 0x9872) {
            int i = ((code >> 8) - 0x88) * 188;
            int j = (code & 0xFF);
            if (!IsSjisTrailByte(j)) {
                return 0;
            }
            j -= 0x40;
            if (j >= 0x40) {
                j--;
            }
            return (i + j + 0x2BE);
        }
        if (code >= 0x8140 && code < 0x879E) {
            int i = ((code >> 8) - 0x81) * 188;
            int j = (code & 0xFF);
            if (!IsSjisTrailByte(j)) {
                return 0;
            }
            j -= 0x40;
            if (j >= 0x40) {
                j--;
            }
            return lbl_801230D0[i + j];
        }
    } else if (code > 0x20 && code <= 0xFF) {
        return code - 0x20;
    }
    return 0;
}
