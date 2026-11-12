// Increments the callback data word and returns the atomic pointer unchanged.
#include "types.h"

extern "C" void* fn_8014F158(void* atomic, void* data)
{
	++*(s32*)data;
	return atomic;
}
