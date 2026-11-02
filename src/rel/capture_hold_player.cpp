#include "types.h"

// The capture enemy's hold (captureHoldPlayer here), the same in the seven
// stage modules that carry the capture: the held player is pulled toward a
// point below the enemy by the module's pull rate.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureTask {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} CaptureTask;

typedef struct Capture {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x12C];
	s32 player; // 0x278
} Capture;

extern "C" CaptureTask* lbl_802AD090[];
extern "C" const f32 captureHoldDrop;
extern "C" const f32 captureHoldPull;

void AdjustPoint(RwV3d* point, const RwV3d* goal, f32 rate);

extern "C" void captureHoldPlayer(Capture* object)
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
