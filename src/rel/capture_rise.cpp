#include "types.h"

// One step of the capture enemy's rise (captureRise here), the same in the
// seven stage modules that carry the capture: while active it climbs by the
// module's rise speed and stops at its top height. Returns whether it is
// there (always, while inactive).

typedef struct Capture {
	u8 unk000[0x144];
	f32 y; // 0x144
	u8 unk148[0x7C];
	f32 top; // 0x1C4
	u8 unk1C8[0x3AC];
	s32 active; // 0x574
} Capture;

extern "C" const f32 captureRiseSpeed;

extern "C" s32 captureRise(Capture* object)
{
	s32 done = 1;
	f32 top;

	if (object->active == 0) {
		return 1;
	}
	top = object->top;
	object->y += captureRiseSpeed;
	if (object->y >= top) {
		object->y = top;
	} else {
		done = 0;
	}
	return done;
}
