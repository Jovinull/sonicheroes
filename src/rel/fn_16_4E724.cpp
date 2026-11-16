#include "types.h"

extern "C" void fn_8014FFBC(void* clump, void* callback, s32 data);
extern "C" void SetAtomicCustomFXData__FP8RpAtomicPv(void);

extern "C" void fn_16_4E724(s32 arg0, s32 arg1)
{
	fn_8014FFBC((void*)arg1, (void*)SetAtomicCustomFXData__FP8RpAtomicPv, arg0);
}
