#include "types.h"

// One of the capture enemy's mode hooks (captureModeCarry here), the same in
// the seven stage modules that carry the capture: phase 0 starts the spin and
// motion 0; phase 1 pulls the held player as captureModeHold does and updates
// the bubbles (captureBubbleUpdate, left as assembly); phases 2 and 3 do
// nothing.

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
	u8 unk14C[0x12C];
	s32 player; // 0x278
	u8 unk27C[0x10];
	s32 spin; // 0x28C
} Capture;

extern "C" CaptureTask* lbl_802AD090[];
extern "C" const f32 captureHoldDrop;
extern "C" const f32 captureHoldPull;

extern "C" void captureBubbleUpdate(Capture* object);
void AdjustPoint(RwV3d* point, const RwV3d* goal, f32 rate);

// Pulls the held player toward a point below the enemy.
static inline void captureHoldPlayer(Capture* object)
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

extern "C" void captureModeCarry(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->spin   = 1;
			object->motion = 0;
			return;
		case 1:
			captureHoldPlayer(object);
			captureBubbleUpdate(object);
			return;
		case 2:
		case 3:
			break;
	}
}
