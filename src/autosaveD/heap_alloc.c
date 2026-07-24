#include "types.h"

extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

extern "C" void* fn_2_1424(u32 size)
{
	return fn_80018A34(lbl_8042C148, size);
}
