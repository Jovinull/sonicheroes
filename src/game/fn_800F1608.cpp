#include "types.h"

// Sets the motion's index (0x10) and its float at 0x24.

struct Fn800F1608Motion {
	u8 unk00[0x10];
	s16 index; // 0x10
	u8 unk12[0x12];
	f32 value; // 0x24
};

extern "C" void fn_800F1608(Fn800F1608Motion* motion, s32 index, f32 value)
{
	motion->index = index;
	motion->value = value;
}
