#include "types.h"

struct Obj {
	u8 pad[0xA8];
	s32 unkA8;
};

extern "C" s32 fn_80128218(Obj** arg0)
{
	return (*arg0)->unkA8;
}
