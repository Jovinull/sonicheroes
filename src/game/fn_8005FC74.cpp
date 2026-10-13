#include "types.h"

// fn_8005FBBC with -1 as its third argument.

extern "C" void fn_8005FBBC(void* self, void* arg, s32 index);

extern "C" void fn_8005FC74(void* self, void* arg)
{
	fn_8005FBBC(self, arg, -1);
}
