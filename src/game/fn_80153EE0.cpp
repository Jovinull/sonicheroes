// Stores four words (copied as plain words) at +0x18 of the object and sets the byte at +0x3 when
// the first three, read back as floats, are equal. Field names are UNKNOWN.
// Built with GC/2.0 (configure.py): GC/1.3.2 interleaves the four-word copy differently (2 words
// differ). HYPOTHESIS: this is RenderWare code built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

struct Words80153EE0 {
	u32 w[4];
};

struct Object80153EE0 {
	u8 pad0[0x3];
	u8 uniform; // 0x3
	u8 pad4[0x18 - 0x4];
	f32 value[4]; // 0x18
};

extern "C" {
void fn_80153EE0(Object80153EE0* object, const Words80153EE0* value)
{
	*(Words80153EE0*)object->value = *value;
	if (object->value[0] == object->value[1] && object->value[0] == object->value[2]) {
		object->uniform = 1;
	} else {
		object->uniform = 0;
	}
}
}
