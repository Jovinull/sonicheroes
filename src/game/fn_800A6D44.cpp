#include "types.h"

struct Fn800A6D44Data {
	u8 pad[0x210];
	f32 field210;
};

extern "C" u32 fn_800A6D44(Fn800A6D44Data* arg0, f32 arg1)
{
	return arg1 < arg0->field210;
}
