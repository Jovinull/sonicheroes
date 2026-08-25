#include "types.h"

extern "C" {
f32 lbl_803A7028[0x10000];
double sin(double);
}

extern "C" void fn_800D7B18()
{
    s32 angle = 0;
    for (s32 index = 0; index < 0x10000; index++) {
        lbl_803A7028[index] = (f32)sin(3.141592f * angle / 65536.0f);
        angle += 2;
    }
}
