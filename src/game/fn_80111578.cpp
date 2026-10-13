#include "types.h"

// fn_8011137C with -1 as its first value.

extern "C" void fn_8011137C(void* self, s32 a, s32 b);

extern "C" void fn_80111578(void* self, s32 value)
{
	fn_8011137C(self, -1, value);
}
