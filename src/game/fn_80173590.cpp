// Copies four floats into +0x9C of the object, scales them by lbl_8042F4A0 and sets flag bit 3 of
// the word at +0x8. Names are UNKNOWN. Returns the object.
#include "types.h"
#include "MSL_C/string.h"

struct Object80173590 {
	unsigned char pad0[0x8];
	unsigned int flags; // 0x8
	unsigned char padC[0x9C - 0xC];
	float value[4]; // 0x9C
};

extern "C" {
// .sdata2 scale constant (non-const: reloaded after each store).
extern float lbl_8042F4A0;

Object80173590* fn_80173590(Object80173590* object, const float* value)
{
	memcpy(object->value, value, sizeof(object->value));
	object->value[0] = object->value[0] * lbl_8042F4A0;
	object->value[1] = object->value[1] * lbl_8042F4A0;
	object->value[2] = object->value[2] * lbl_8042F4A0;
	object->value[3] = object->value[3] * lbl_8042F4A0;
	object->flags |= 8;
	return object;
}
}
