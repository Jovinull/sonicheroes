#include "types.h"

// Clears the four words at 0x678 of the object.

struct Fn800487A0Object {
	u8 unk000[0x678];
	s32 values[4]; // 0x678
};

extern "C" void fn_800487A0(Fn800487A0Object* object)
{
	object->values[0] = 0;
	object->values[1] = 0;
	object->values[2] = 0;
	object->values[3] = 0;
}
