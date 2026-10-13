#include "types.h"

// A setter (the word at 0x20 = 3) followed by seven empty functions.

struct Fn8010A0E8Object {
	u8 unk00[0x20];
	s32 value; // 0x20
};

extern "C" void fn_8010A0E8(Fn8010A0E8Object* object)
{
	object->value = 3;
}

extern "C" void fn_8010A0F4(void) { }

extern "C" void fn_8010A0F8(void) { }

extern "C" void fn_8010A0FC(void) { }

extern "C" void fn_8010A100(void) { }

extern "C" void fn_8010A104(void) { }

extern "C" void fn_8010A108(void) { }

extern "C" void fn_8010A10C(void) { }
