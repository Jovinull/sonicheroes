#include "types.h"

// fn_800DA0C0 with 0x76.

extern "C" void fn_800DA0C0(void* self, s32 value);

extern "C" void fn_800DA09C(void* self)
{
	fn_800DA0C0(self, 0x76);
}
