#include "types.h"

// One step of the capture enemy's turn (captureTurn here), the same in the
// seven stage modules that carry the capture: while active its angle turns
// toward the goal by its turn speed, and snaps to the goal once fn_800A5A54
// gives less than 0x80. Returns whether it snapped.

typedef struct Capture {
	u8 unk000[0x150];
	s32 angle; // 0x150
	u8 unk154[0x20];
	s32 goal; // 0x174
	u8 unk178[0x8];
	s32 speed; // 0x180
	u8 unk184[0x3F0];
	s32 active; // 0x574
} Capture;

extern "C" s32 fn_800A5A54(Capture* object);
s32 AdjustAngle(s32 angle, s32 goal, s32 speed);

extern "C" s32 captureTurn(Capture* object)
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
