#include "types.h"

// One of the capture enemy's mode hooks (captureModeRelease here), the same in
// the seven stage modules that carry the capture. Phase 0 starts the mode with
// motion 1 and a 50-frame timer, playing sound 0x4013; phase 1, while active,
// once the timer runs out lets the held player go (mode 0xF), clears flag
// 0x10 of its collision and plays sound 0x4014, only once; phase 3 sets the
// flag back.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureCollision {
	u8 unk00[0x34];
	u32 flags; // 0x34
} CaptureCollision;

typedef struct Capture {
	u8 unk000[0x38];
	CaptureCollision* collision; // 0x038
	u8 unk03C[0x98];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x12C];
	s32 player; // 0x278
	u8 unk27C[0x24];
	s32 timer;    // 0x2A0
	s32 released; // 0x2A4
	u8 unk2A8[0x2CC];
	s32 active; // 0x574
} Capture;

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" void captureModeRelease(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->released = 0;
			object->timer    = 0x32;
			object->motion   = 1;
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4013, &object->pos, NULL, 1, 0, 0);
			}
		case 2:
			return;
		case 1:
			if (object->active != 0 && --object->timer < 0 && object->released == 0) {
				object->released = 1;
				if (object->player != -1) {
					fn_800E1208(object->player, 0xF, 0);
					object->player = -1;
				}
				object->collision->flags &= ~0x10;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4014, &object->pos, NULL, 1, 0, 0);
					return;
				}
			}
			break;
		case 3:
			object->collision->flags |= 0x10;
			break;
	}
}
