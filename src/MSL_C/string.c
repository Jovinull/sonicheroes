#include "types.h"

// Order follows the original binary, which for this compiler is source order.
// The Metrowerks source walks a pointer decremented by one and pre-incremented
// in the loop, the same idiom as mem.c, so the length counter starts at -1.

u32 strlen(const char* str)
{
	const char* p = str - 1;
	u32 len       = -1;
	do {
		len++;
	} while (*++p);
	return len;
}
