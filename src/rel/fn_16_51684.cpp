#include "types.h"

extern "C" {
void* fn_80239724(void* arg0);
void fn_802325F8(void* arg0, s32* arg1);
s32 fn_8023506C(s32 arg0, s32 arg1);
void fn_16_51704(void* arg0, s32 arg1);
}

extern "C" void* fn_16_51684(void* arg0, s32 arg1)
{
	char* temp;
	s32 sp8;
	void* handle;
	char* p;
	s32 spC;
	s32 off;

	sp8    = arg1;
	temp   = (char*)fn_80239724(arg0);
	handle = *(void**)(temp + 0xC);
	fn_802325F8(handle, &spC);
	off = fn_8023506C(spC, 4);
	if (off > 0) {
		p = temp + off;
		fn_16_51704(p, sp8);
	}
	return arg0;
}
