#include "types.h"

// One of the capture enemy's mode hooks (captureModeCarryHome here), the same
// in the seven stage modules that carry the capture. Phase 0 takes the kind's
// rate, a far range, the home marker as the aim, moves on to the next marker
// and starts the spin with motion 0; phase 1 holds the player (as
// captureHoldPlayer does), updates the bubbles and, while active, turns (as
// captureTurn does) and flies home at its rate, moving to mode 0x2E with
// sound 0x4015 on arrival; phases 2 and 3 do nothing.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureTask {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} CaptureTask;

typedef struct Capture {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x4];
	s32 angle; // 0x150
	u8 unk154[0x20];
	s32 goal; // 0x174
	u8 unk178[0x8];
	s32 speed; // 0x180
	u8 unk184[0x34];
	f32 moveRate; // 0x1B8
	u8 unk1BC[0x10];
	RwV3d aim; // 0x1CC
	u8 unk1D8[0x38];
	f32 range; // 0x210
	u8 unk214[0x34];
	s32 mode; // 0x248
	u8 unk24C[0x2C];
	s32 player; // 0x278
	f32 rate;   // 0x27C
	u8 unk280[0xC];
	s32 spin; // 0x28C
	u8 unk290[0x18];
	RwV3d home; // 0x2A8
	s32 homeId; // 0x2B4
	u8 unk2B8[0x2BC];
	s32 active; // 0x574
	u8 unk578[0x10];
	f32 kindRate; // 0x588
} Capture;

extern "C" CaptureTask* lbl_802AD090[];
extern "C" void* lbl_8042C388;
extern "C" const f32 captureHoldDrop;
extern "C" const f32 captureHoldPull;
extern "C" const f32 captureCarryRange;

extern "C" void captureBubbleUpdate(Capture* object);
extern "C" s32 fn_800A5A54(Capture* object);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);
s32 AdjustAngle(s32 angle, s32 goal, s32 speed);
s32 AdjustPoint(RwV3d* point, const RwV3d* goal, f32 rate);

// captureHoldPlayer (rel/capture_hold_player.cpp), inlined.
static inline void captureHold(Capture* object)
{
	s32 player = object->player;

	if (player != -1) {
		CaptureTask* task = lbl_802AD090[player];

		if (task != NULL) {
			RwV3d at = object->pos;

			at.y += captureHoldDrop;
			AdjustPoint(&task->pos, &at, captureHoldPull);
		}
	}
}

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

extern "C" void captureModeCarryHome(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->rate     = object->kindRate;
			object->moveRate = object->rate;
			object->range    = captureCarryRange;
			object->aim.x    = object->home.x;
			object->aim.y    = object->home.y;
			object->aim.z    = object->home.z;
			object->homeId++;
			object->spin   = 1;
			object->motion = 0;
			return;
		case 1:
			captureHold(object);
			captureBubbleUpdate(object);
			if (object->active != 0) {
				captureTurnStep(object);
				if (AdjustPoint(&object->pos, &object->home, object->rate) != 0) {
					object->mode = 0x2E;
					if (lbl_8042C388 != NULL) {
						fn_800B4A38(lbl_8042C388, 0x4015, &object->pos, NULL, 1, 0, 0);
					}
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}
