#include "types.h"

// One step of the capture enemy's turn and approach (captureTurnApproach
// here), the same in the seven stage modules that carry the capture: while
// active it turns (as captureTurn does, inlined) and approaches as
// captureApproach does. Returns 0 once it stopped or fell, 1 otherwise.

typedef struct Capture {
	u8 unk000[0x106];
	u16 flags; // 0x106
	u8 unk108[0x48];
	s32 angle; // 0x150
	u8 unk154[0x8];
	f32 rise; // 0x15C
	u8 unk160[0x14];
	s32 goal; // 0x174
	u8 unk178[0x8];
	s32 speed; // 0x180
	u8 unk184[0x24];
	f32 height; // 0x1A8
	u8 unk1AC[0x3C8];
	s32 active; // 0x574
} Capture;

extern "C" const f32 captureZero;
extern "C" const f32 captureOneAndHalf;
extern "C" const f32 captureMinusOne;

extern "C" s32 fn_800A5A54(Capture* object);
extern "C" f32 fn_800A5AC0(Capture* object);
extern "C" void fn_800A4668(Capture* object);
extern "C" void fn_800A4A8C(Capture* object, f32 speed);
extern "C" void fn_800A5C6C(Capture* object, s32 mask);
extern "C" s32 fn_800A5888(Capture* object, f32 limit);
extern "C" void fn_800A5B50(Capture* object, s32 mask);
s32 AdjustAngle(s32 angle, s32 goal, s32 speed);

// captureTurn (rel/capture_turn.cpp), inlined.
static inline s32 captureTurnStep(Capture* object)
{
	s32 left;

	if (object->active == 0) {
		return 0;
	}
	left          = fn_800A5A54(object);
	object->angle = AdjustAngle(object->angle, object->goal, object->speed);
	if (left < 0x80) {
		object->angle = object->goal;
		return 1;
	}
	return 0;
}

extern "C" s32 captureTurnApproach(Capture* object, f32 speed, f32 near)
{
	s32 result = 1;

	if (object->active == 0) {
		return 1;
	}
	captureTurnStep(object);
	if (fn_800A5AC0(object) < near || (object->flags & 4) != 0) {
		fn_800A4668(object);
		result = 0;
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
		result = 0;
	}
	return result;
}
