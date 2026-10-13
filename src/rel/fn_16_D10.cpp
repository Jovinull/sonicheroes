#include "types.h"

// Passes the collision's first hit (fn_800211A8) to fn_16_D4C.

extern "C" s32 fn_800211A8(s32 colli);
extern "C" void fn_16_D4C(s32 colli, s32 hit);

extern "C" void fn_16_D10(s32 colli)
{
	fn_16_D4C(colli, fn_800211A8(colli));
}
