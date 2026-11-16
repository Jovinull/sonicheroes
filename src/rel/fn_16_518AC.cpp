#include "types.h"

extern "C" {
void* fn_80239724(s32 arg0);
void fn_8023239C(void* arg0, s32 arg1, void* arg2);
void fn_802344D8(s32 arg0, s32 arg1, void* arg2);
}

extern "C" s32 fn_16_518AC(s32 arg0, void* arg1)
{
	void* sp8;
	void* temp_r3;
	s32 temp_r29;
	s32 temp_r28;

	sp8      = arg1;
	temp_r3  = fn_80239724(arg0);
	temp_r29 = *(s32*)((char*)temp_r3 + 0xC);
	temp_r28 = *(s32*)((char*)temp_r3 + 0x18);
	fn_8023239C((void*)temp_r29, *(s32*)sp8, (char*)sp8 + 4);
	fn_802344D8(temp_r28, *(s32*)((char*)sp8 + 0x10C), (char*)sp8 + 0x110);
	return arg0;
}
