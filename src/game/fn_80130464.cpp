#include "types.h"

struct Fn80130464Data {
	u8 pad[4];
	s32 field4;
};

extern "C" Fn80130464Data* lbl_8042C778;

extern "C" void fn_80130464(s32 arg0)
{
	if (lbl_8042C778 != 0) {
		lbl_8042C778->field4 = arg0;
	}
}
