#include "types.h"

struct Unk801560C0A {
	u8 pad0[4]; // 0x0
	u16 f4;     // 0x4
	u8 pad6[2]; // 0x6
	u32 f8;     // 0x8
};

struct Unk801560C0B {
	u8 f0;      // 0x0
	u8 pad1[7]; // 0x1
	u32 f8;     // 0x8
};

extern "C" s32 fn_801560C0(Unk801560C0A* a, Unk801560C0B* b)
{
	u32 t = b->f0;
	s32 s;

	if ((t == 8 && (b->f8 & 0x01000000)) || (t == 7 && (b->f8 & 0x01000000))) {
		return a->f4 * 8 + 0xC;
	}
	s = a->f4 * 8;
	s += a->f8 * 4;
	return s + 0xC;
}
