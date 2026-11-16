#include "types.h"

extern "C" void fn_16_4E75C(void* p);

extern "C" void fn_16_4E384(u8* arg0)
{
	s32 i;

	i = 0;
	while (*(u32*)(arg0 + i * 12 + 8) != 0) {
		if (*(u32*)(arg0 + i * 12) != 0) {
			fn_16_4E75C(*(void**)(arg0 + i * 12));
		}
		i++;
	}
}
