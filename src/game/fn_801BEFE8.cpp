#include "types.h"

// tolower for one character through MSL's __lower_map; -1 (EOF) stays -1.

extern "C" u8 __lower_map[];

extern "C" s32 fn_801BEFE8(s32 c)
{
	if (c == -1) {
		return -1;
	}
	return __lower_map[(u8)c];
}
