#include "types.h"

extern "C" {
void* fn_80239724(void* arg0);
void fn_802325F8(void* arg0, s32* arg1);
s32 fn_8023506C(s32 arg0, s32 arg1);
s32 fn_801A491C(void* texture);
}

extern "C" void* fn_16_50174(void* arg0)
{
	char* temp;
	char* p;
	s32 sp8;
	s32 off;

	temp = (char*)fn_80239724(arg0);
	fn_802325F8(*(void**)(temp + 0xC), &sp8);
	off = fn_8023506C(sp8, 1);
	p   = temp + off;
	if (*(u32*)(p + 0xA4) != 0) {
		fn_801A491C(*(void**)(p + 0xA4));
		*(u32*)(p + 0xA4) = 0;
	}
	return arg0;
}
