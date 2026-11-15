#include "types.h"

extern "C" {
u32 fn_8015E980(void*, void*);

void* fn_8015B46C(void* a, void* b, void* c)
{
	if (fn_8015E980(a, c) != 0) {
		return a;
	}
	return 0;
}
}
