#include "types.h"

struct Obj8008A01C {
	u8 pad0[0x628];
	s32 f628; // 0x628
	u8 pad1[0x6F6 - 0x62C];
	s16 f6F6; // 0x6F6
	u8 pad2[0x774 - 0x6F8];
	s16 f774; // 0x774
};

extern "C" {
s32 fn_8008915C(Obj8008A01C* o);

bool fn_8008A01C(Obj8008A01C* arg0)
{
	if (fn_8008915C(arg0) != 0) {
		return 0;
	}
	if ((arg0->f6F6 & 0x2000) != 0) {
		return 0;
	}
	return arg0->f774 <= 0;
}
}
