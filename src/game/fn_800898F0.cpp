#include "types.h"

// Sets the word at 0x630 of the object.

struct Fn800898F0Object {
	u8 unk000[0x630];
	s32 value; // 0x630
};

extern "C" void fn_800898F0(Fn800898F0Object* object, s32 value)
{
	object->value = value;
}
