#include "types.h"

struct Object {
	u8 pad[0x28];
	s32 value;
};

extern "C" void fn_80128234(s32 arg0);

extern "C" void fn_801248F8(Object* arg0)
{
	fn_80128234(arg0->value);
}
