#include "types.h"

// One of the capture enemy's mode hooks (captureModeChase here), the same in
// the seven stage modules that carry the capture. Phase 0 takes the kind's
// rate; phase 1 aims at the nearest team leader's place (as captureModeFace
// does), turns and approaches it (as captureTurnApproach does, stopping 10
// away) and moves to mode 9 once stopped; phases 2 and 3 do nothing. (The
// module's 10 is the constant captureShadowWidth names.)

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

namespace nSearchPlayer
{
s32 GetNearestLeaderNum(const RwV3d* pos, f32 distance);
}

typedef struct CaptureTask {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} CaptureTask;

typedef struct Capture {
	u8 unk000[0x106];
	u16 flags; // 0x106
	u8 unk108[0x38];
	RwV3d pos; // 0x140
	u8 unk14C[0x4];
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
	u8 unk1BC[0x10];
	RwV3d aim; // 0x1CC
	u8 unk1D8[0x70];
	s32 mode; // 0x248
	u8 unk24C[0x28];
	s32 found; // 0x274
	u8 unk278[0x4];
	f32 rate; // 0x27C
	u8 unk280[0x2F4];
	s32 active; // 0x574
	u8 unk578[0x10];
	f32 kindRate; // 0x588
} Capture;

extern "C" CaptureTask* lbl_802AD090[];
extern "C" const f32 captureZero;
extern "C" const f32 captureOneAndHalf;
extern "C" const f32 captureMinusOne;
extern "C" const f32 captureFarAway;
extern "C" const f32 captureShadowWidth;

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

// captureTurnApproach (rel/capture_turn_approach.cpp), inlined.
static inline s32 captureTurnApproachStep(Capture* object, f32 speed, f32 near)
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

extern "C" void captureModeChase(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->rate     = object->kindRate;
			object->moveRate = object->rate;
			return;
		case 1: {
			s32 found;

			object->found = nSearchPlayer::GetNearestLeaderNum(&object->pos, captureFarAway);
			found         = object->found;
			if (found != -1) {
				CaptureTask* task = lbl_802AD090[found];

				if (task != NULL) {
					object->aim.x = task->pos.x;
					object->aim.y = task->pos.y;
					object->aim.z = task->pos.z;
				}
			}
			if (captureTurnApproachStep(object, object->rate, captureShadowWidth) == 0) {
				object->mode = 9;
			}
			return;
		}
		case 2:
		case 3:
			break;
	}
}
