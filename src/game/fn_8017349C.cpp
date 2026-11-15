#include "types.h"

struct RwV3d_ {
	f32 x;
	f32 y;
	f32 z;
};

struct Cam8017349C {
	u8 pad0[8];
	u32 flags;      // 0x8
	RwV3d_ padC[1]; // 0xC (matrix base)
};

extern "C" {
extern volatile f32 lbl_8042F498;
void* fn_80195E44(void* m, const RwV3d_* v, s32 c);

void* fn_8017349C(void* arg0, f32 f1, f32 f2)
{
	Cam8017349C* o = (Cam8017349C*)arg0;
	volatile RwV3d_ v;

	v.x = f1;
	v.y = f2;
	v.z = lbl_8042F498;
	fn_80195E44(&o->padC[0], (const RwV3d_*)&v, 1);
	o->flags |= 2;
	return o;
}
}
