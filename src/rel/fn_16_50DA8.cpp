#include "types.h"

extern "C" {
s32 fn_16_51BF4(s32 arg0);
void* fn_80239724(s32 arg0);
s32 fn_8023506C(s32 arg0, s32 arg1);
}

extern "C" void* fn_16_50DA8(s32 arg0)
{
	char* obj;
	char* sub;
	s32 idx;
	s32 tbl;
	s32 off;
	char* p;

	idx = fn_16_51BF4(arg0);
	obj = (char*)fn_80239724(idx);
	sub = *(char**)(obj + 0xC);
	tbl = *(s32*)(sub + 0x10);
	off = fn_8023506C(tbl, 6);
	p   = obj + off;
	return p;
}
