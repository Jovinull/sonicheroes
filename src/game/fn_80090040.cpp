#include "types.h"

// Whether the float at 0x608 is below the one at 0x604.

struct Fn80090040Object {
	u8 unk000[0x604];
	f32 limit; // 0x604
	f32 value; // 0x608
};

extern "C" u32 fn_80090040(Fn80090040Object* object)
{
	return object->value < object->limit;
}
