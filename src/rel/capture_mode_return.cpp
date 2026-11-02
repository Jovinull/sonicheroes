#include "types.h"

// One of the capture enemy's mode hooks (captureModeReturn here), the same in
// the seven stage modules that carry the capture. Phase 0 sets the default
// rate, motion 0 and the start place as the aim; phase 1 first turns (as
// captureTurn does) until facing, then approaches (as captureApproach does,
// at its rate, stopping 2 away) and moves to mode 2 once stopped; phases 2
// and 3 do nothing.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Capture {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x2E];
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
	u8 unk1AC[0xC];
	f32 moveRate; // 0x1B8
	u8 unk1BC[0x4];
	RwV3d start; // 0x1C0
	RwV3d aim;   // 0x1CC
	u8 unk1D8[0x70];
	s32 mode; // 0x248
	u8 unk24C[0x30];
	f32 rate; // 0x27C
	u8 unk280[0x54];
	s32 turned; // 0x2D4
	u8 unk2D8[0x29C];
	s32 active; // 0x574
} Capture;

extern "C" const f32 captureZero;
extern "C" const f32 captureOneAndHalf;
extern "C" const f32 captureMinusOne;
extern "C" const f32 captureDefaultRate;
extern "C" const f32 captureReturnNear;

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

// captureApproach (rel/capture_approach.cpp), inlined.
static inline s32 captureApproachStep(Capture* object, f32 speed, f32 near)
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

extern "C" void captureModeReturn(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->rate     = captureDefaultRate;
			object->moveRate = object->rate;
			object->motion   = 0;
			object->aim.x    = object->start.x;
			object->aim.y    = object->start.y;
			object->aim.z    = object->start.z;
			object->turned   = 0;
			return;
		case 1:
			if (object->turned == 0) {
				if (captureTurnStep(object) != 0) {
					object->turned = 1;
				}
			}
			if (object->turned != 0) {
				if (captureApproachStep(object, object->rate, captureReturnNear) == 1) {
					object->mode = 2;
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}
