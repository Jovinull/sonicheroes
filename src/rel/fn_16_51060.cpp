#include "types.h"

struct Obj51060 {
	u8 unk0[0xC];
	void* unkC;
};

extern "C" {
void fn_802325F8(void* arg0, s32* arg1);
s32 fn_8023506C(s32 arg0, s32 arg1);
}

extern "C" void fn_16_51060(Obj51060* arg0)
{
	void* t;
	s32 off;
	s32 spC;
	char* sp8;

	t = arg0->unkC;
	fn_802325F8(t, &spC);
	off = fn_8023506C(spC, 0x01000004);
	sp8 = (char*)arg0 + off;
}
