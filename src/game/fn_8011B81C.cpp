#include "types.h"

// Passes the object's second word to fn_8020D02C and returns 1.

struct Fn8011B81CObject {
	u32 unk0;
	s32 value; // 0x4
};

extern "C" void fn_8020D02C(s32 value);

extern "C" s32 fn_8011B81C(Fn8011B81CObject* object)
{
	fn_8020D02C(object->value);
	return 1;
}
