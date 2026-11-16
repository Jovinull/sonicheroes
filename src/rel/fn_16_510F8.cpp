#include "types.h"

extern "C" {
void* fn_80239724(void* arg0);
void fn_16_51060(void* arg0);
}

extern "C" void* fn_16_510F8(void* arg0)
{
	void* p;

	p = fn_80239724(arg0);
	fn_16_51060(p);
	return arg0;
}
