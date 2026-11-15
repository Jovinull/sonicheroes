#include "types.h"

struct Obj155BE4 {
	u8 pad0[4];
	u16 count; // 0x4
	u8 pad6[6];
	u32 offset; // 0xC
};

extern "C" void* fn_80155BE4(Obj155BE4* obj, u32 (*cb)(void*, Obj155BE4*, s32), s32 arg)
{
	s32 offset = obj->offset;
	s32 n      = obj->count;
	u8* p      = (u8*)obj + offset;
	p += 0x10;

	while (n-- != 0) {
		if (cb(p, obj, arg) == 0) {
			return obj;
		}
		p += 0xC;
	}
	return obj;
}
