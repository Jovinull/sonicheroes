#include "types.h"

extern "C" {
f32 lbl_803A7028[12614];
u8 lbl_803B3540[0x1F801];
u8 lbl_803D2D41[57487];
u8 lbl_803E0DD0[1860];
u8 lbl_803E1514[23316];
extern const f32 lbl_8042E044;
extern const f32 lbl_8042E048;
extern const f64 lbl_8042E050;
double sin(double);
}

extern "C" void fn_800D7B18()
{
	u32 angle;
	f32* output = lbl_803A7028;
	u32 index   = 0;
	angle       = 0;
	for (; index < 0x10000; index++) {
		*output = (f32)sin(lbl_8042E044 * angle / lbl_8042E048);
		output++;
		angle += 2;
	}
}
