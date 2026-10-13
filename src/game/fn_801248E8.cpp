#include "types.h"

// The object's word at 0xD8 + index * 4.

struct Fn801248E8Object {
	u8 unk00[0xD8];
	s32 values[1]; // 0xD8
};

extern "C" s32 fn_801248E8(Fn801248E8Object* object, s32 index)
{
	return object->values[index];
}
