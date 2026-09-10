
#include "types.h"

void (*DVDLowClearCallback())(u32);

void Decode(unsigned char *s, unsigned char *d) {
    int i;
    int j;
    int k;
    int p;
    int q;
    int r7;
    int r25;
    int cnt;
    int os;
    unsigned int flag;
    unsigned int code;
    os = *(int *)(s + 0x4);
    r7 = *(int *)(s + 0x8);
    r25 = *(int *)(s + 0xC);
    q = 0;
    flag = 0;
    p = 16;
    do {
        if (flag == 0) {
            code = *(u32 *)(s + p);
            p += sizeof(u32);
            flag = sizeof(u32) * 8;
        }
        if (code & 0x80000000) {
            d[q++] = s[r25++];
        } else {
            j = s[r7] << 8 | s[r7 + 1];
            r7 += sizeof(u16);
            k = q - (j & 0x0FFF);
            cnt = j >> 12;
            if (cnt == 0) {
                cnt = s[r25++] + 0x12;
            } else {
                cnt += 2;
            }
            for (i = 0; i < cnt; i++, q++, k++) {
                d[q] = d[k - 1];
            }
        }
        code <<= 1;
        flag--;
    } while (q < os);
}
