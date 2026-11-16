#include "types.h"

extern "C" {
void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
void* fn_16_51A34(void*);

void fn_16_519FC(void* clump, void* data)
{
	fn_8014FFBC(clump, fn_16_51A34, data);
}
}
