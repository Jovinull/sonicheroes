#include "types.h"

// One of the capture enemy's mode hooks (captureModeFace here), the same in
// the seven stage modules that carry the capture: in phase 1 it aims at the
// nearest team leader's place and, while active, turns toward its goal (as
// captureTurn does); the other phases do nothing.

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
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x4];
	s32 angle; // 0x150
	u8 unk154[0x20];
	s32 goal; // 0x174
	u8 unk178[0x8];
	s32 speed; // 0x180
	u8 unk184[0x48];
	RwV3d aim; // 0x1CC
	u8 unk1D8[0x9C];
	s32 found; // 0x274
	u8 unk278[0x2FC];
	s32 active; // 0x574
} Capture;

extern "C" CaptureTask* lbl_802AD090[];
extern "C" const f32 captureFarAway;

extern "C" s32 fn_800A5A54(Capture* object);
s32 AdjustAngle(s32 angle, s32 goal, s32 speed);

extern "C" void captureModeFace(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			break;
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
			if (object->active != 0) {
				s32 left      = fn_800A5A54(object);
				object->angle = AdjustAngle(object->angle, object->goal, object->speed);
				if (left < 0x80) {
					object->angle = object->goal;
				}
			}
			break;
		}
		case 2:
		case 3:
			break;
	}
}
