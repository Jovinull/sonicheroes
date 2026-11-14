#include "types.h"

struct Fn80124898Allocator {
	u8 unk00[0x140];
	void* (*allocateZeroed)(u32 count, u32 size); // 0x140
};

struct Fn80124898Object {
	u8 unk00[0xB4];
	void* unkB4; // 0xB4
	u8 unk_B8[0xD4 - 0xB8];
	u32 unkD4; // 0xD4
};

extern "C" Fn80124898Allocator* lbl_8042C9A4;

extern "C" void fn_80124898(Fn80124898Object* object)
{
	if (object->unkB4 == 0) {
		object->unkB4 = lbl_8042C9A4->allocateZeroed(object->unkD4, 0x63);
	}
}
