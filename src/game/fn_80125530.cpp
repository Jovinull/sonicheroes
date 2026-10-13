#include "types.h"

// The object's word at 0xC4 while the one at 0xBC is clear, 0 otherwise.

struct Fn80125530Object {
	u8 unk00[0xBC];
	s32 flag;  // 0xBC
	s32 unkC0; // 0xC0
	s32 value; // 0xC4
};

extern "C" s32 fn_80125530(Fn80125530Object* object)
{
	if (object->flag == 0) {
		return object->value;
	}
	return 0;
}
