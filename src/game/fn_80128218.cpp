#include "types.h"

// The word at 0xA8 of the object the argument points to.

struct Fn80128218Object {
	u8 unk00[0xA8];
	s32 value; // 0xA8
};

extern "C" s32 fn_80128218(Fn80128218Object** object)
{
	return (*object)->value;
}
