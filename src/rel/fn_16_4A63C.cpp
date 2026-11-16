#include "types.h"

typedef struct Obj {
	u8 unk0[0x178];  // 0x000
	s32 unk178;      // 0x178
	u8 unk17C[0x0C]; // 0x17C
	s32 unk188;      // 0x188
	s32 unk18C;      // 0x18C
} Obj;

extern "C" void fn_16_4ACF4(void* arg0, s32 arg1);

extern "C" void fn_16_4A63C(Obj* arg0)
{
	if (arg0->unk178 > arg0->unk18C) {
		fn_16_4ACF4(arg0, 2);
		return;
	}
}
