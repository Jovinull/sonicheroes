#include "types.h"

// One step of the capture enemy's approach (captureApproach here), the same in
// the seven stage modules that carry the capture. While active it stops
// (fn_800A4668, result 1) once closer than the given distance or told to
// (flag 4), and otherwise moves on at the given speed (fn_800A4A8C); its
// vertical speed is cleared, the ground check (fn_800A5C6C) runs, a small
// rise is dropped on flag 2, and fn_800A5888 reporting a fall ends the step
// with fn_800A5B50 (result 2).

typedef struct Capture {
	u8 unk000[0x106];
	u16 flags; // 0x106
	u8 unk108[0x54];
	f32 rise; // 0x15C
	u8 unk160[0x48];
	f32 height; // 0x1A8
	u8 unk1AC[0x3C8];
	s32 active; // 0x574
} Capture;

extern "C" const f32 captureZero;
extern "C" const f32 captureOneAndHalf;
extern "C" const f32 captureMinusOne;

extern "C" f32 fn_800A5AC0(Capture* object);
extern "C" void fn_800A4668(Capture* object);
extern "C" void fn_800A4A8C(Capture* object, f32 speed);
extern "C" void fn_800A5C6C(Capture* object, s32 mask);
extern "C" s32 fn_800A5888(Capture* object, f32 limit);
extern "C" void fn_800A5B50(Capture* object, s32 mask);

extern "C" s32 captureApproach(Capture* object, f32 speed, f32 near)
{
	s32 result = 0;

	if (object->active == 0) {
		return 0;
	}
	if (fn_800A5AC0(object) < near || (object->flags & 4) != 0) {
		fn_800A4668(object);
		result = 1;
	} else {
		fn_800A4A8C(object, speed);
	}
	object->rise = captureZero;
	fn_800A5C6C(object, 0xF00);
	if ((object->flags & 2) != 0 && object->rise < captureOneAndHalf * object->height) {
		object->rise = captureZero;
	}
	if (fn_800A5888(object, captureMinusOne) != 0) {
		fn_800A5B50(object, 0xF00);
		result = 2;
	}
	return result;
}
