#include "types.h"

// Sets the word at 0x4 of the object in lbl_8042C778, when there is one.

struct Fn80130464Object {
	u8 unk0[0x4];
	s32 value; // 0x4
};

extern "C" Fn80130464Object* lbl_8042C778;

extern "C" void fn_80130464(s32 value)
{
	if (lbl_8042C778 != 0) {
		lbl_8042C778->value = value;
	}
}
