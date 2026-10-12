#include "types.h"

extern "C" u8 __lower_map[];

extern "C" s32 fn_801BEFE8(s32 arg0)
{
	if (arg0 == -1) {
		return -1;
	}
	return __lower_map[(u8)arg0];
}
