#include "types.h"

extern "C" {
void* fn_80239724(s32 arg0);
void fn_8023239C(s32 a, s32 b, void* c);
void fn_802344D8(s32 a, s32 b, void* c);

s32 fn_16_5198C(s32 arg0, void* arg1)
{
	char* p    = (char*)arg1;
	char* temp = (char*)fn_80239724(arg0);
	s32 a      = *(s32*)(temp + 0xC);
	s32 b      = *(s32*)(temp + 0x18);
	fn_8023239C(a, *(s32*)p, p + 0x88);
	fn_802344D8(b, *(s32*)(p + 0x10C), p + 0x164);
	return arg0;
}
}
