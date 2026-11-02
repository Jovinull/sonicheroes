#include "types.h"

// One of the capture enemy's mode hooks (captureModeRise here), the same in
// the seven stage modules that carry the capture. Phase 0 hides the search
// icon and starts motion 0; phase 1 rises (as captureRise does, inlined) and
// moves to mode 2 once at the top; phases 2 and 3 do nothing.

class TEnemyIconMan
{
public:
	void Off();
};

typedef struct Capture {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x6C];
	f32 y; // 0x144
	u8 unk148[0x7C];
	f32 top; // 0x1C4
	u8 unk1C8[0x80];
	s32 mode; // 0x248
	u8 unk24C[0xA8];
	TEnemyIconMan* searchIcon; // 0x2F4
	u8 unk2F8[0x27C];
	s32 active; // 0x574
} Capture;

extern "C" const f32 captureRiseSpeed;

// captureRise (rel/capture_rise.cpp), inlined.
static inline s32 captureRiseStep(Capture* object)
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

extern "C" void captureModeRise(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			if (object->searchIcon != NULL) {
				object->searchIcon->Off();
			}
			object->motion = 0;
			return;
		case 1:
			if (captureRiseStep(object) != 0) {
				object->mode = 2;
			}
			return;
		case 2:
		case 3:
			break;
	}
}
