#include "types.h"

// Passes the object's word at 0x28 to fn_80128234.

struct Fn801248F8Object {
	u8 unk00[0x28];
	s32 value; // 0x28
};

extern "C" void fn_80128234(s32 value);

extern "C" void fn_801248F8(Fn801248F8Object* object)
{
	fn_80128234(object->value);
}
