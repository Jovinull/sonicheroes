#include "types.h"

// Three getters on one object: its words at 0x1C, 0x14 and 0x8.

struct Fn80128224Object {
	u8 unk00[0x8];
	s32 value8; // 0x08
	u8 unk0C[0x8];
	s32 value14; // 0x14
	u8 unk18[0x4];
	s32 value1C; // 0x1C
};

extern "C" s32 fn_80128224(Fn80128224Object* object)
{
	return object->value1C;
}

extern "C" s32 fn_8012822C(Fn80128224Object* object)
{
	return object->value14;
}

extern "C" s32 fn_80128234(Fn80128224Object* object)
{
	return object->value8;
}
