#include "types.h"

extern "C" void fn_8014FFBC(void* anim, void* callback, void* step);
extern "C" s32 fn_16_50174(s32 arg0);

extern "C" void fn_16_50200(s32 arg0, s32 arg1)
{
	fn_8014FFBC((void*)arg0, (void*)fn_16_50174, (void*)arg1);
}
