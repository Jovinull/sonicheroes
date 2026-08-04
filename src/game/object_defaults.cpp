#include "types.h"

// Four adjacent virtual-style helpers operate on the same object layout. The
// implicit object argument and paired scalar accessors identify C++ ownership.

struct ObjectDefaults {
	u8 pad00[0x28];
	u32 state;
};

extern "C" {
extern f32 lbl_8042CFE8;

void fn_8001ED40(ObjectDefaults* object)
{
	object->state = 0;
}

void fn_8001ED4C() { }

f32 fn_8001ED50()
{
	return lbl_8042CFE8;
}

f32 fn_8001ED58()
{
	return lbl_8042CFE8;
}
}
