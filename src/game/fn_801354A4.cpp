#include "types.h"

// Whether neither flag 0x80 nor 0x8000 is set in the object's flags (0x18).

struct Fn801354A4Object {
	u8 unk00[0x18];
	u32 flags; // 0x18
};

extern "C" s32 fn_801354A4(Fn801354A4Object* object)
{
	return (u32)__cntlzw(object->flags & 0x8080) >> 5;
}
