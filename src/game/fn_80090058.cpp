#include "types.h"

typedef struct V2_80090058 {
	f32 x;
	f32 y;
} V2_80090058;

typedef struct Obj80090058 {
	u8 pad000[0x29];
	s8 f29;
	u8 f2A;
	u8 pad02B[0x34 - 0x2B];
	f32 f34;
	V2_80090058 pos;
	u8 pad040[0x48 - 0x40];
	u8 col[4];
} Obj80090058;

extern "C" {
extern f32 lbl_8042D928;
void fn_800C4BB8(V2_80090058* pos, void* val, u8* col, f32 f);
}

extern "C" void fn_80090058(Obj80090058* o)
{
	V2_80090058 pos = o->pos;

	if (o->f29 != 0) {
		pos.x -= lbl_8042D928;
	}
	fn_800C4BB8(&pos, &o->f2A, o->col, o->f34);
}
