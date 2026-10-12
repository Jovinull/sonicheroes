#include "types.h"

struct Fn80098710Data {
	u8 pad[0x150];
	s32 field150;
	s32 field154;
};

extern "C" s32 fn_80098710(Fn80098710Data* arg0)
{
	arg0->field150 = 0x15;
	return arg0->field154;
}

extern "C" s32 fn_80098720(Fn80098710Data* arg0)
{
	arg0->field150 = 0x17;
	return arg0->field154;
}
