#include "types.h"

struct Fn80125530Data {
	u8 pad[0xBC];
	s32 fieldBC;
	s32 unkC0;
	s32 fieldC4;
};

extern "C" s32 fn_80125530(Fn80125530Data* arg0)
{
	if (arg0->fieldBC == 0) {
		return arg0->fieldC4;
	}
	return 0;
}
