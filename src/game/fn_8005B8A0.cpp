#include "types.h"

// Clears the four words at 0x18 of the object.

struct Fn8005B8A0Object {
	u8 unk00[0x18];
	s32 values[4]; // 0x18
};

extern "C" void fn_8005B8A0(Fn8005B8A0Object* object)
{
	object->values[0] = 0;
	object->values[1] = 0;
	object->values[2] = 0;
	object->values[3] = 0;
}
