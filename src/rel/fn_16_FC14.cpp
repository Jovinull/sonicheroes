#include "types.h"
extern "C" void* fn_800210C4(void* colli);
extern "C" u32 fn_16_D4C(void* colli, void* hit);

extern "C" void fn_16_FC14(register void* colli)
{
	fn_16_D4C(colli, fn_800210C4(colli));
}
