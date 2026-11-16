#include "types.h"

extern "C" s32 fn_80020BD8(void* colli, u8 kind);
extern "C" u32 fn_16_D4C(void* colli, s32 hit);

extern "C" u32 fn_16_DC8(void* colli, u8 kind)
{
	return fn_16_D4C(colli, fn_80020BD8(colli, kind));
}
