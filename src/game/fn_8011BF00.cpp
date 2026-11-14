// Interpolates the five values of two key frames at the given time (HYPOTHESIS: a key-frame
// interpolation callback): blend = (time - a.time) / (b.time - a.time) and each value becomes
// blend * b + (lbl_8042EB30 - blend) * a, with lbl_8042EB30 the .sdata2 1.0f (HYPOTHESIS).
// Field names are inferred from this function only.
#include "types.h"

struct Key8011BF00 {
	u8 pad0[0x4];
	f32 time;    // 0x4
	f32 value8;  // 0x8
	f32 valueC;  // 0xC
	f32 value10; // 0x10
	f32 value14; // 0x14
	f32 value18; // 0x18
};

extern "C" {
extern f32 lbl_8042EB30;

void fn_8011BF00(Key8011BF00* out, const Key8011BF00* a, const Key8011BF00* b, f32 time)
{
	f32 blend   = (time - a->time) / (b->time - a->time);
	f32 inverse = lbl_8042EB30 - blend;

	out->value14 = blend * b->value14 + inverse * a->value14;
	out->value18 = blend * b->value18 + inverse * a->value18;
	out->valueC  = blend * b->valueC + inverse * a->valueC;
	out->value10 = blend * b->value10 + inverse * a->value10;
	out->value8  = blend * b->value8 + inverse * a->value8;
}
}
