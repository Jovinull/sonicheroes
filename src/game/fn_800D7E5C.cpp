#include "types.h"

extern "C" {
extern f32 lbl_803A7028[0x10000];
}

extern "C" void fn_800D7E5C(u32 angle, f32 scale, f32* sine, f32* cosine)
{
    *sine = scale * lbl_803A7028[(u16)angle];
    *cosine = scale * lbl_803A7028[(u16)(angle + 0x4000)];
}
