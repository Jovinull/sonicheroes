#include "types.h"
extern "C" void fn_16_E0A8(void* a, register char* b)
{
	s16* p = *(s16**)(b + 0x2C);
	if (*p < 0) {
		*p = 0;
	}
	if (*p > 0x7FFF) {
		*p = 0x7FFF;
	}
}
