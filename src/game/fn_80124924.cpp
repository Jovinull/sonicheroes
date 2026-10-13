#include "types.h"

// Whether the object's word at 0xBC is set.

struct Fn80124924Object {
	u8 unk00[0xBC];
	s32 flag; // 0xBC
};

extern "C" s32 fn_80124924(Fn80124924Object* object)
{
	return object->flag != 0;
}
